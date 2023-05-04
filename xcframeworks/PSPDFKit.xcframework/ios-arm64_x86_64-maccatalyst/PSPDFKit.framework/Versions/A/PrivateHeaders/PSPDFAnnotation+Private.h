//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationAuthorState.h>
#import <PSPDFKit/PSPDFAnnotationGroupItem.h>
#import <PSPDFKit/PSPDFAnnotationReplyType.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFreeTextAnnotation.h>
#import <PSPDFKit/PSPDFGeometry.h>
#import <PSPDFKit/PSPDFModelObject+NSCoding.h>
#import <PSPDFKit/PSPDFRenderOptions+Private.h>
#import <PSPDFKit/PSPDFRenderRequest.h>
#import <PSPDFKit/PSPDFUndoDiffable.h>

#ifdef __cplusplus
#import <mutex>
#endif

@class PSPDFStream, PSPDFPointArray, PSPDFPageInfo;
@protocol PSPDFAnnotationReviewSummary, PSPDFDetachedUndoRecorder;

// The internal property lock ensures that threaded read/writes to properties do not crash (e.g. by creating an over-release)
// Careful with using the property lock, it is not allowed to run any code that might create other locks once this is held!
// We sometimes use the property lock to ensure the object doesn't change between e.g. an equality check or hash
// In other operations, holding a lock would be fatal (e.g. in shouldDrawNoteIconWithOptions when .hasReplies is called that uses another lock)
// If in doubt, only lock property access and do not lock compound edit operations. This is just a recipe for deadlocks.
// Nothing that is potentially expensive should hold this lock either.
// Locking is hard and we're basically declaring bankruptcy here. https://github.com/PSPDFKit/PSPDFKit/pull/27088#discussion_r532576397
#define PROPERTY_LOCK_GUARD std::lock_guard<std::recursive_mutex> propertyLocker(self->_propertyLock);

#define PROPERTY_LOCK_LOCK self->_propertyLock.lock();
#define PROPERTY_LOCK_UNLOCK self->_propertyLock.unlock();

#define PROPERTY_LOCKED_GETTER(type, name) PROPERTY_LOCKED_GETTER_CUSTOM(type, name, _##name)
#define PROPERTY_LOCKED_GETTER_CUSTOM(type, name, ivar) - (type)name { PROPERTY_LOCK_GUARD return ivar; }

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_EXPORT const CGSize PSPDFAnnotationDefaultMinimumSize;
PSPDF_SDK_EXPORT const CGSize PSPDFAnnotationDefaultMinimumMeasurementSize;

static const NSUInteger PSPDFInstantCommentOperationsOffset = 16;

@interface PSPDFAnnotation () {
@public
    NSUInteger _page;

#ifdef __cplusplus
    // Property lock can be used to protect internal properties.
    // Only use this in subclasses — or when attaching to core
    // mutex cannot be a spinlock - needs to be recursive.
    std::recursive_mutex _propertyLock;
#endif
}

/// Editable version of `typeString`. Only to be used in special cases! (e.g. Instant)
@property (atomic, copy) PSPDFAnnotationString typeString;

@end

PSPDF_SDK_EXPORT const PSPDFAnnotationType PSPDFAnnotationTypeLineOrPolyLine;

/// Private `UIPasteboard` support.
PSPDF_SDK_EXPORT NSString *const PSPDFAnnotationPasteboardPrivateData;

/// Converts a `PSPDFAnnotationType` into the format the core understands.
PSPDF_EXTERN NSArray<NSNumber *> *PDFCAnnotationTypesFromPSPDFAnnotationType(PSPDFAnnotationType type);

// MARK: - Creation

@interface PSPDFAnnotation ()

/// Use this to create custom user annotations.
- (instancetype)initWithType:(PSPDFAnnotationType)annotationType NS_DESIGNATED_INITIALIZER;

/// We inherit NSSecureCoding from `PSPDFModel` — and support it ourselves…
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Use to create a new annotation that is identical to passed annotation. It works like a copy but the uuid is different.
+ (PSPDFAnnotation *)annotationWithAnnotation:(PSPDFAnnotation *)annotation;

/// Common init method.
- (void)commonInit NS_REQUIRES_SUPER;

// MARK: -

/// Whether or not this annotation is backed by Instant.
///
/// Some annotations have to behave differently when they are backed by Instant. Since there are multiple
/// paths for instantiating (subclasses of) `PSPDFAnnotation`, and these instances need not immediately be
/// backed by a core annotation, the value of this property can change when we attach the annotation to
/// an annotation provider.
@property (nonatomic, getter = isBackedByInstant) BOOL backedByInstant;

/// The number of Instant Comments attached to the annotation.
///
/// Instant’s comments are different to annotation replies in various ways. The most important one is that they are not
/// annotations. This property is updated whenever we refresh the annotation from core. It can also be set to `YES` when
/// creating a new markup annotation.
@property (nonatomic) BOOL isInstantCommentThreadRoot;

/// The operations supported by this annotation in the context of Instant.
///
/// This value is orthogonal to the `flags` property, which reflects things defined in the PDF that can be synced using
/// Instant. (See the Instant JSON schema for annotations.)
/// Being a server-driven value, we have well-defined time points when this property may change — namely at the end of
/// a successful authentication, and at the end of a successful sync. Because of this benign nature, it does not — and
/// in fact: should not — use the `PDFDocumentFeature` mechanism, avoiding the complex locking implications of its
/// asynchronous writing semantics. Instead, this property can be read from at any point in time without acquiring any
/// additional locks.
/// Just uses NSUInteger to expose this privately. Internally this uses PSPDFInstantRecordOperations.
@property (nonatomic, readonly) NSUInteger instantRecordOperations;

/// Record group of the annotation for use in Instant Collaboration Permissions.
@property (atomic, copy, nullable) NSString *instantRecordGroup;

/// Color with added alpha value.
@property (nonatomic, readonly, nullable) UIColor *colorWithAlpha;

/// Fill color with added alpha value.
@property (nonatomic, readonly, nullable) UIColor *fillColorWithAlpha;

/// Border color with added alpha value.
@property (nonatomic, readonly, nullable) UIColor *borderColorWithAlpha;

/// Fast internal representation of the points.
@property (nonatomic, nullable) PSPDFPointArray *pointArray;

/// A stable unique identifier used to associate replies with their parents.
/// Different when copied.
@property (nonatomic) NSString *uuidForReplies;

/// Defines if the annotation is rendered using core or not.
@property (class, nonatomic, readonly) BOOL isRenderedUsingCore;

/// Returns YES if this annotation type has a fixed size, no matter the internal bounding box.
@property (nonatomic, readonly) BOOL isFixedSize;

/// Whether the stored points do not have the page transform applied.
///
/// We used untransformed PDF coordinates before 8.0. This property is YES
/// when old archives are read. The points will be transformed and this
/// property set to NO when the annotation is added to a page.
@property (nonatomic) BOOL requiresCoordinateTransformation;

/// The icon name for the annotation. May return a string for which no image can be found.
@property (nonatomic, readonly) NSString *annotationIconName;

/// Corresponding `PSPDFDocumentProvider`.
@property (atomic, weak) PSPDFDocumentProvider *documentProvider;

/// The variant type that best matches the annotation’s current properties.
///
/// This does not consider the variant of the tool used to create the annotation, which is stored in the `variant` property.
/// The user could make an annotation with a tool variant and then modify the properties of the annotation so it’s more like another variant.
///
/// Defaults to nil.
/// This is intended to be overridden by subclasses that support variants. There is not expected to be any need to call this directly.
@property (nonatomic, readonly, nullable) PSPDFAnnotationVariantString effectiveVariant;

/// A user-facing string describing the type of the annotation. For example Arrow, Stamp, or Callout.
///
/// This is will use variant types, but based on the actual annotation properties rather than the variant assigned to the
/// tool that created this annotation. For example line annotations with arrow heads will be called arrows regardless of
/// the tool variant used to create the annotation, or even if the annotation was created by Acrobat or whatever.
///
/// This is intended to be called, not overridden. To customize variant types override `effectiveVariant`.
@property (nonatomic, readonly) NSString *localizedType;

/// A string that describes the annotation as it appears on the page. This is nil for the base class. For overriding.
@property (nonatomic, readonly, nullable) NSString *localizedAppearanceDescription;

/// Subclasses should override this to return YES if the `localizedAppearanceDescription` does not work well on its own. This is NO for the base class.
@property (nonatomic, readonly) BOOL shouldIncludeTypeAndAppearanceDescriptionInLocalizedDescription;

/// Value indicating if the annotation wants to display a note icon if it has non empty `contents`.
/// Subclasses can opt-out by returning NO if they render the `contents` string themselves, ex. in the case of measurement annotations.
/// Defaults to YES.
///
/// @note Check `shouldDrawNoteIconIfNeeded` for more details on how this value is used.
@property (nonatomic, readonly) BOOL contentsWantNoteIcon;

// MARK: - More Appearance Stream Goodies

/// Will create PDF data from the drawingBlock.
+ (NSData *)createAppearanceStreamDataWithRect:(CGRect)boundingBox rotation:(PSPDFRotation)pageRotation options:(nullable PSPDFRenderOptions *)options drawingBlock:(void (^)(CGContextRef context, PSPDFRenderOptions *_Nullable options))drawingBlock;

/// Whether or not `drawInContext:options:` should take precedence over an existing appearance stream.
/// Defaults to `NO`.
///
/// For most annotation types, this is a compile time constant. For stamps, however, the value of this
/// property depends on the internal state of the annotation.
/// To prevent drawing the appearance stream for an annotation type, prefer overriding this property
/// instead of `drawAppearanceStreamInContext:options:`. Otherwise, you’ll make it extra hard for
/// subclasses to get an existing appearance stream drawn.
@property (nonatomic, readonly) BOOL prefersCustomDrawing;

/// Draws the receiver’s appearance stream — IFF `options` and `prefersCustomDrawing` allow.
///
/// Override point that allows suppressing the drawing of an existing appearance stream based on the
/// `options`. By default, this method bails if `prefersCustomDrawing` is `YES`, or if the blend mode
/// should be ignored. You should not call this method directly! Instead, this method is called by
/// `lockAndRenderInContext:options:` IFF:
///
/// - `maybeRenderCustomAppearanceStreamWithContext:options:` returned `NO`,
/// - the receiver’s class is _not_ rendered using core, and
/// - the receiver’s class reports any supported annotation types
///
/// @return Whether the appearance stream has actually been drawn.
/// @note Avoid overriding this method in abstract annotation classes, or classes that we subclass
/// ourselves: Otherwise, our subclasses will have a hard time to get back to the default behavior…
- (BOOL)drawAppearanceStreamInContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)options NS_REQUIRES_SUPER;

// MARK: - Tests

/// Indicates whether lazy loading of additionalActions has already been performed or not.
@property (nonatomic, readonly) BOOL additionalActionsLoaded;

@end

// MARK: - Private Drawing

/// Private drawing hooks for subclasses inside the framework.
///
/// @note **Important:** Although `PSPDFAnnotation` _can be_ subclassed by customers, these methods are
/// internal, and only called by our own implementations of `drawInContext:withOptions:`. By ensuring
/// our own implementations of that method hold the property lock while using the methods from this
/// category, we remove the burden of acquiring the property lock from their implementations without
/// jeopardizing consistency.
@interface PSPDFAnnotation (PrivateDrawing)

/// Draw the note icon, if there's a note or replies for the annotation.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (BOOL)drawNoteIconIfNeededInContext:(nullable CGContextRef)context withOptions:(nullable PSPDFRenderOptions *)options;

/// In general, overriding `noteIconPoint` is better.
@property (nonatomic, readonly) CGRect noteIconRect;

/// Whether or not the note icon should be displayed with the given options.
///
/// @note Subclasses **must** acquire the property lock when overriding. (`PSPDFAnnotationView` uses
/// this method. So not all callers are annotations…)
- (BOOL)shouldDrawNoteIconWithOptions:(nullable PSPDFRenderOptions *)options;

/// The alpha the note icon should be drawn with. Defaults to 0.7.
@property (nonatomic, readonly) CGFloat noteIconAlpha;

/// Draw the bounding box.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (void)drawBoundingBox:(CGContextRef)context;

/// Helps with drawing annotation content with opacity.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (void)drawWithTransparencyLayerInContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)options block:(void (^)(void))drawBlock;

/// Helper that will prepare the context for the border style.
///
/// If you relied on this method to apply line dashing to `context` please see `pathByDashingPathIfNecessary:`.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
/// @see pathByDashingPathIfNecessary:
- (void)prepareBorderStyleInContext:(CGContextRef)context withOptions:(nullable PSPDFRenderOptions *)options;

/// Helper to apply the current annotation's `lineDashArray` to `path`.
///
/// Use this method to get the final path you should draw in your annotations, do not rely on `prepareBorderStyleInContext:` to adjust the context's line dash style.
///
/// @return An autoreleased path.
/// @note Not all legitimate callers of this method are `PSPDFAnnotation` objects. As such this method
/// _does_ acquire the property lock.
- (CGPathRef)pathByDashingPathIfNecessary:(CGPathRef)path;

/// Optionally returns an unrounded bounding box rect (used to improve PSPDFResizableView accuracy).
///
/// @note Not all legitimate callers of this method are `PSPDFAnnotation` objects. As such this method
/// _does_ acquire the property lock.
- (CGRect)boundingBoxForPageRect:(CGRect)pageRect rounded:(BOOL)rounded;

/// Applies the correct filters for color inversion to the context.
///
/// @param context The context to apply the filters to.
/// @param boundingBox The box in which to apply the filters.
/// @param options The render options that define the filter options.PSPDFAnnotation.mm
- (void)applyMatchingFiltersToContext:(CGContextRef)context rect:(CGRect)boundingBox options:(nullable PSPDFRenderOptions *)options;

/// Can be overridden by annotation subclasses to return an annotation style that
/// better represents the on screen annotation appearance than `borderStyle`.
/// e.g., `PSPDFAnnotationBorderStyleNone` is essentially equal to
/// `PSPDFAnnotationBorderStyleSolid` for line annotations
@property (nonatomic, readonly) PSPDFAnnotationBorderStyle effectiveBorderStyle;

@end

// MARK: - Helper

@interface PSPDFAnnotation (Helper)

- (NSComparisonResult)compareByPositionOnPage:(PSPDFAnnotation *)otherAnnotation;

/// Helper that queries the page rotation.
@property (nonatomic, readonly) PSPDFRotation pageRotation;

/// Draw border.
///
/// @note Acquiring the property lock is the caller’s responsibility. In general, this should be
/// `drawInContext:withOptions:`.
- (void)drawBorderInContext:(CGContextRef)context withOptions:(nullable PSPDFRenderOptions *)options;

/// Checks if the annotation should be drawn with the specified options.
/// This will ensure that the annotation has not been deleted as well.
///
/// @param options The options dictionary passed in for drawing.
/// @return `true` if the receiver should be rendered, else `false`.
- (BOOL)shouldDrawWithOptions:(nullable PSPDFRenderOptions *)options;

/// Will be called after document and page have been set.
///
/// @note **Important:** This method is meant to be called **exactly once** in the lifetime of an
/// annotation! (During the initialization and setup phase after deserializing in an annotation
/// provider.)
/// All implementations will therefore assume that there cannot be any concurrent reads/writes to the
/// state of the annotation. In other words: No additional locking is attempted, nor should it be.
- (void)parse;

/// Converts annotations into other classes (e.g. highlight to underscore)
///
/// Tries to save as much properties as possible.
- (PSPDFAnnotation *)convertIntoAnnotationType:(PSPDFAnnotationType)annotationType;

/// Checks whether the supplied annotation can be copied to clipboard.
///
/// @return Returns YES if the document has permissions to extract content and the annotation is of NOT of the following kind: form element, ink signature, file and redaction
///
/// @note Please make sure to also check if the annotation type is supported in the current PSPDFConfiguration before copying it to the clipboard.
@property (nonatomic, readonly) BOOL supportsCopyToClipboard;

/// Clipboard operations need to run on the main thread.
- (instancetype)copyForClipboard;
- (void)didUnarchiveFromClipboard;

/// Helper that checks if the dash array is valid.
///
/// @see "The dash array’s elements shall be numbers that specify the lengths of alternating dashes and gaps; the numbers shall be nonnegative and not all zero". See PDF Reference §8.4.3.6 (Table 55).
///
/// @note a nil or missing (empty) dash array is considered valid.
@property (nonatomic, readonly) BOOL hasValidDashArray;

@end

@interface PSPDFAnnotation ()

/// Whether the user is allowed to delete this annotation in the UI.
///
/// For this, the annotation must be deletable and not a form element.
///
/// This check does not consider licence restrictions or `editableAnnotationTypes` from the configuration.
@property (nonatomic, readonly) BOOL isDeletableByUser;

@end

// MARK: - IndexWriting

@interface PSPDFAnnotation (IndexWriting)

@end

// MARK: - WritingSupport

@interface PSPDFAnnotation (WritingSupport)

/// Can be set to NO to nil out any AP stream.
@property (nonatomic) BOOL hasAppearanceStream;

/// Some annotations may have a popupIndex. Defaults to -1.
@property (nonatomic) NSInteger popupIndex;

@end

/// Fonts
PSPDF_SDK_EXPORT NSString *const PSPDFAnnotationDefaultTextFontName;
PSPDF_SDK_EXPORT const NSUInteger PSPDFAnnotationDefaultFontSize;

// MARK: - FontsPrivate

@interface PSPDFAnnotation (FontsPrivate)

/// Returns font attributes — including annotation color — while honoring the given `options`.
- (NSDictionary<NSString *, id> *)fontAttributesWithColorAndFontForOptions:(nullable PSPDFRenderOptions *)options;

@end

// MARK: - AdvancedPrivate

@interface PSPDFAnnotation (AdvancedPrivate)

/// HACK. Processor uses this.
- (void)setDirtyWithoutChecks:(BOOL)dirty;

/// Defines the alignment of a fixed size annotation within its bounding box.
- (PSPDFRectAlignment)fixedSizeAlignmentForSize:(CGSize)size;

/// Adjust the bounding box so it is appropriate for a fixed size annotation.
- (CGRect)fixedSizeBoundingBoxForBoundingBox:(CGRect)boundingBox;

/// Returns the adjusted `boundingBox` for fixed size annotations in the specified page environment.
/// Returns `boundingBox` for non-fixed size annotations.
- (CGRect)fixedSizeBoundingBoxWithPageInfo:(PSPDFPageInfo *)pageInfo pageBounds:(CGRect)bounds zoomLevel:(CGFloat)zoom;

/// Returns the annotation type strings that are supported. Implemented in each subclass.
+ (NSArray<PSPDFAnnotationString> *)supportedTypes;

/// Doesn't reset the appearance stream when the dirty flag is set.
- (void)performBlockWithoutResettingAnnotationStream:(NS_NOESCAPE dispatch_block_t)block;

/// Recalculates the bounding box of the annotation. The default implementation does nothing. Override in subclasses to provide your custom implementation.
- (void)recalculateBoundingBox;

@end

// MARK: - ImmutablePrivate

@interface PSPDFAnnotation (ImmutablePrivate)

/// startup
@property (nonatomic, getter=isInitializing, readonly) BOOL initializing;
- (void)startInitializing; // Used in XFDF parser
- (void)finishInitializing; // Used in XFDF parser
- (void)performInitializationBlock:(void (^)(void))block;

/// Sets the dirty flag, optionally without changing the modification date.
- (void)setDirty:(BOOL)dirty updateModificationDate:(BOOL)updateModificationDate;

/// Intermediate flag to check when overriding `-setDirty:`/in property observers of `isDirty`.
///
/// Some changes, like moving an annotation without resizing it, do not invalidate its appearance.
/// While such changes often have to set `isDirty`, some transient properties don’t need to be
/// reset during such changes, while other transient properties **must not** be reset!
/// To avoid potentially harmful re-computation of such transient properties, **always** check
/// `isPerformingAppearanceNeutralChange` to figure out whether you may actually resetting them
/// in overrides of `-setDirty:` or the `willSet`/`didSet` property observers of the `isDirty`
/// property.
@property (nonatomic, readonly) BOOL isPerformingAppearanceNeutralChange;

/// Checks if the annotation is synced to the core already.
@property (nonatomic, getter=isSyncedToCore, readonly) BOOL syncedToCore;

@end

// MARK: - Replies

@interface PSPDFAnnotation ()

/// Whether the annotation should be rendered on the page when it’s in reply to another annotation — defaults to `true`.
///
/// For most annotation types, rendering should not depend on whether or not they refer to another annotation (via the
/// `inReplyToAnnotation` property).
/// Subclasses that should only be rendered when not in reply to another annotation can override this property to hide
/// themselves when they are part of an annotation replies thread.
@property (nonatomic, readonly) BOOL shouldBeRenderedWhenInReplyTo;

/// Annotations on the same page that have the receiver set as their in-reply-to annotation. Ordered by date.
///
/// Returns an empty array and logs a warning if `Features.annotationReplies` is not enabled.
@property (nonatomic, readonly) NSArray<PSPDFAnnotation *> *directReplies;

/// Cached value. Use this instead of counting the elements in `directReplies`, as that can be quite expensive.
@property (atomic, readonly) BOOL hasReplies;

/// Returns annotations on the page that in reply to the receiver, and annotations that are in reply to those,
/// and so on until the end of the reply tree. Ordered by date.
/// Returns an empty array and logs a warning if `Features.annotationReplies` is not enabled.
///
/// @param replyType Determines which reply types should be included in the returned annotations.
/// @return The replies.
- (NSArray<PSPDFAnnotation *> *)flattenedRepliesForReplyType:(PSPDFAnnotationReplyType)replyType;

/// This is the same as flattenedRepliesForReplyType: but without license checks.
///
/// We need to be able to clean up, even if this feature is not licensed otherwise
/// deleting an annotation with replies leaves the document in a weird state.
///
/// @param replyType Determines which reply types should be included in the returned annotations.
/// @return The replies.
- (NSArray<PSPDFAnnotation *> *)annotationsForDeletionForReplyType:(PSPDFAnnotationReplyType)replyType;

/// A summary the information about the annotation’s review state. Exactly the info we want in our UI.
/// Returns nil and logs a warning if `Features.annotationReplies` is not enabled.
@property (nonatomic, readonly, nullable) id<PSPDFAnnotationReviewSummary> reviewSummary;

/// Adds a review state or marked state attached to this annotation, using the
/// `defaultAnnotationUsername` from the document. Does nothing and logs a
/// warning if `Features.annotationReplies` is not enabled.
///
/// @param authorState New author state to add.
/// @param undoRecorder An optional undo recorder used to record adding the new
/// author state. If the call is coming from UI, you should ask the document for
/// an undo recorder and pass it here. Otherwise, this can be `nil`.
- (void)addAuthorState:(PSPDFAnnotationAuthorState)authorState withUndoRecorder:(nullable id<PSPDFDetachedUndoRecorder>)undoRecorder;

@end

// MARK: - Measurements

static const CGFloat PSPDFDefaultMeasurementLabelDistanceFromLine = 5.0f;

@interface PSPDFAnnotation ()

PSPDF_EXTERN CGFloat PSPDFAnnotationDefaultMeasurementLabelDistanceFromLine NS_SWIFT_NAME(Annotation.defaultMeasurementLabelDistanceFromLine);
PSPDF_EXTERN CGFloat PSPDFAnnotationDefaultMeasurementLabelInsetForShapes NS_SWIFT_NAME(Annotation.defaultMeasurementLabelInsetForShapes);

/// Returns `true` If the annotation is a measurement.
///
/// Use of `isMeasurement` requires `Features.measurementTools`.
/// If your license key does not include this feature, reading `isMeasurement` always returns `false`.
@property (nonatomic, readonly) BOOL isMeasurement;

/// If the annotation is a measurement annotation, this returns the `MeasurementInfo` object associated with the annotation, otherwise it returns `nil`.
///
/// Use of `measurementInfo` requires `Features.measurementTools`.
/// If your license key does not include this feature, reading `measurementInfo` always returns `nil`.
///
/// Attempting to set a new value will do nothing except logging a warning.
@property (nonatomic, nullable) PSPDFMeasurementInfo *measurementInfo;

/// Converts the annotation into a measurement annotation by setting the measurement scale, precision and mode.
- (void)setMeasurementInfoWithScale:(PSPDFMeasurementScale *)scale precision:(PSPDFMeasurementPrecision)precision mode:(PSPDFMeasurementMode)mode;

/// Measurement calibration object. Calculated from the current measurement info scale.
@property (nonatomic, nullable) PSPDFMeasurementCalibration *measurementCalibration;

/// Convenience accessor for the measurement info measurement scale object. Used by the annotation inspector to read and write measurement scale data.
@property (nonatomic, nullable) PSPDFMeasurementScale *measurementScale;

/// Convenience accessor for the measurement info measurement precision value. Used by the annotation inspector to read and write measurement precision data.
@property (nonatomic) PSPDFMeasurementPrecision measurementPrecision;

@end

// MARK: -  Accessibility

@interface PSPDFAnnotation ()

/// This is for the UI to attach a UIAccessibilityElement to the annotation.
/// The UI could also use associated objects or some other approach, but having a property here seemed neater.
@property (nonatomic) id accessibilityElementStorage;

@end

// MARK: - Undo

@interface PSPDFAnnotation () <PSPDFUndoDiffable>
@end

// MARK: -  Signature Licensing

/// Ink annotations and stamp annotations have a property for whether they are signatures or not.
/// This function is a convenience to avoid checking for those types.
/// This always returns NO for other annotation types.
PSPDF_SDK_EXPORT BOOL PSPDFIsSignatureAnnotation(PSPDFAnnotation *annotation);

/// Checks PSPDFFeatureMaskAnnotationEditing or PSPDFFeatureMaskElectronicSignatures for signature annotations.
/// Checks PSPDFFeatureMaskAnnotationEditing for other annotation types.
/// Does not log a warning if the license feature is not available.
/// This currently does not check for the Forms or Redaction features for those annotation types.
PSPDF_SDK_EXPORT BOOL PSPDFCanLicenseEditAnnotation(PSPDFAnnotation *annotation) NS_REFINED_FOR_SWIFT;

/// Whether all of the passed in annotations can be editing according to the license.
///
/// Checks PSPDFFeatureMaskAnnotationEditing or PSPDFFeatureMaskElectronicSignatures for signature annotations.
/// Checks PSPDFFeatureMaskAnnotationEditing for other annotation types.
/// If warn is true then this logs a warning if the license feature is not available for any of the annotations.
/// This currently does not check for the Forms or Redaction features for those annotation types.
PSPDF_SDK_EXPORT BOOL PSPDFCanLicenseEditAnnotations(NSArray<PSPDFAnnotation *> *annotations, BOOL warn) NS_REFINED_FOR_SWIFT;

// MARK: -

/// Helper to properly escape ASCII strings.
PSPDF_EXTERN NSString *PSPDFEscapedString(NSString *_Nullable string);

/// Returns the unified rect for all given annotations.
PSPDF_EXTERN CGRect PSPDFBoundingBoxForAnnotations(NSArray<PSPDFAnnotation *> *annotations);

/// Applies a maximum size that an annotation should be rendered at, to avoid excessive memory use.
PSPDF_EXTERN CGSize PSPDFAnnotationRenderSizeForSize(CGSize requestedSize, CGFloat scale);

/// Returns a set of classes that can be used as font attributes. Includes NSFont for Mac-Support.
PSPDF_EXTERN NSSet *PSPDFFontAttributeClassSet(void);

/// Send change notifications. Can be called from any thread. Sends on main thread.
PSPDF_SDK_EXPORT void PSPDFSendChangeNotificationForAnnotations(NSArray<PSPDFAnnotation *> *annotations, NSArray<NSString *> *_Nullable properties, NSDictionary *_Nullable options) NS_SWIFT_NAME(SendChangeNotification(annotations:properties:options:));
PSPDF_SDK_EXPORT void PSPDFSendChangeNotificationForAnnotation(PSPDFAnnotation *annotation, NSString *_Nullable property, NSDictionary *_Nullable options) NS_SWIFT_NAME(SendChangeNotification(annotation:property:options:));

/// Sends `PSPDFAnnotationBatchUpdatesWillBeginNotification` or `PSPDFAnnotationBatchUpdatesDidEndNotification`
/// (depending on `sendBegin`) for a set of annotations.
PSPDF_SDK_EXPORT void PSPDFSendBatchUpdatesNotificationForAnnotations(id<NSFastEnumeration> annotations, NSArray<NSString *> *_Nullable properties, BOOL sendBegin) NS_SWIFT_NAME(SendBatchUpdatesNotification(annotations:properties:sendBegin:));
/// Sends `PSPDFAnnotationBatchUpdatesWillBeginNotification` or `PSPDFAnnotationBatchUpdatesDidEndNotification`
/// (depending on `sendBegin`) for a single annotation.
PSPDF_SDK_EXPORT void PSPDFSendBatchUpdatesNotificationForAnnotation(PSPDFAnnotation *annotation, NSString *_Nullable property, BOOL sendBegin) NS_SWIFT_NAME(SendBatchUpdatesNotification(annotation:property:sendBegin:));

/// Filters Dictionaries of annotations via a block.
PSPDF_SDK_EXPORT NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *PSPDFFilteredAnnotationDictionaryWithBlock(NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *annotationDict, BOOL (^annotationFilterBlock)(PSPDFAnnotation *annotation)) NS_SWIFT_NAME(FilteredAnnotationDictionary(annotationDict:annotationFilterBlock:));

/// Filters Dictionaries of annotations via the type.
PSPDF_EXTERN NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *PSPDFFilterAnnotationDictionaryAllowingTypes(NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *annotationDict, PSPDFAnnotationType allowedAnnotationTypes) NS_SWIFT_NAME(FilterAnnotationDictionary(annotationDict:allowedAnnotationTypes:));

NS_ASSUME_NONNULL_END
