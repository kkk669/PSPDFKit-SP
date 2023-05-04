//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAction.h>
#import <PSPDFKit/PSPDFDataSink.h>
#import <PSPDFKit/PSPDFDataProviding.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFAppearanceStreamGenerating.h>

NS_ASSUME_NONNULL_BEGIN

/// PDF Annotation types.
///
/// These options can be combined for fetching several types of annotations from a document or annotation provider.
/// However, a single annotation must have a single type.
typedef NS_OPTIONS(NSUInteger, PSPDFAnnotationType) {
    /// No annotation type.
    PSPDFAnnotationTypeNone = 0,
    /// Any annotation whose type couldn't be recognized.
    PSPDFAnnotationTypeUndefined = 1 << 0,
    /// Links and PSPDFKit multimedia extensions.
    PSPDFAnnotationTypeLink = 1 << 1,
    /// Highlight annotation.
    PSPDFAnnotationTypeHighlight = 1 << 2,
    /// Strikeout annotation.
    PSPDFAnnotationTypeStrikeOut = 1 << 17,
    /// Underline annotation.
    PSPDFAnnotationTypeUnderline = 1 << 18,
    /// Squiggly annotation.
    PSPDFAnnotationTypeSquiggly = 1 << 19,
    /// Free text annotation. Includes callout annotation.
    PSPDFAnnotationTypeFreeText = 1 << 3,
    /// Ink annotation. Drawing. Includes ink signatures.
    PSPDFAnnotationTypeInk = 1 << 4,
    /// Square annotation.
    PSPDFAnnotationTypeSquare = 1 << 5,
    /// Circle annotation.
    PSPDFAnnotationTypeCircle = 1 << 20,
    /// Line annotation.
    PSPDFAnnotationTypeLine = 1 << 6,
    /// Note annotation.
    PSPDFAnnotationTypeNote = 1 << 7,
    /// Stamp annotation. Can be an image as well.
    PSPDFAnnotationTypeStamp = 1 << 8,
    /// Caret annotation.
    PSPDFAnnotationTypeCaret = 1 << 9,
    /// Embedded PDF video.
    PSPDFAnnotationTypeRichMedia = 1 << 10,
    /// Embedded PDF video.
    PSPDFAnnotationTypeScreen = 1 << 11,
    /// Widget annotation. Includes PDF Forms.
    PSPDFAnnotationTypeWidget = 1 << 12,
    /// File attachment.
    PSPDFAnnotationTypeFile = 1 << 13,
    /// Sound annotation.
    PSPDFAnnotationTypeSound = 1 << 14,
    /// Polygon annotation.
    PSPDFAnnotationTypePolygon = 1 << 15,
    /// Poly-line annotation.
    PSPDFAnnotationTypePolyLine = 1 << 16,
    /// Redaction annotation.
    PSPDFAnnotationTypeRedaction = 1 << 25,
    /// Popup annotation. Not yet supported.
    PSPDFAnnotationTypePopup = 1 << 21,
    /// Watermark annotation. Not yet supported.
    PSPDFAnnotationTypeWatermark = 1 << 22,
    /// TrapNet annotation. Not yet supported.
    PSPDFAnnotationTypeTrapNet = 1 << 23,
    /// 3D annotation. Not yet supported.
    PSPDFAnnotationTypeThreeDimensional = 1 << 24,
    /// All annotation types.
    PSPDFAnnotationTypeAll = NSUIntegerMax,
} PSPDF_ENUM_SWIFT(Annotation.Kind);

/// Available annotation types. Set in `editableAnnotationTypes` of `PDFConfiguration`.
typedef NSString *PSPDFAnnotationString NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(Annotation.Tool);

/// Tool for adding links.
///
/// This annotation type also includes PSPDFKit multimedia extensions.
///
/// @see This tool creates `PSPDFLinkAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringLink;
/// Tool for highlighting text.
///
/// @see This tool creates `PSPDFHighlightAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringHighlight;
/// Tool for striking through text.
///
/// @see This tool creates `PSPDFStrikeOutAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringStrikeOut;
/// Tool for underlining text.
///
/// @see This tool creates `PSPDFUnderlineAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringUnderline;
/// Tool for underlining text with a squiggly line.
///
/// @see This tool creates `PSPDFSquigglyAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringSquiggly;
/// Tool for adding a note (AKA a comment) to a document.
///
/// This shows an icon on the page and the full text of the comment
/// (including any replies) are shown in a popup when tapping the icon.
///
/// @see This tool creates `PSPDFNoteAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringNote;
/// Tool for adding text annotations.
///
/// Text annotations show their text overlaid over the page itself rather than in a popup (as note annotations do).
///
/// Callout annotations are a variant of text annotations (`PSPDFAnnotationVariantStringFreeTextCallout`).
///
/// @see This tool creates `FreeTextAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringFreeText;
/// Tool for freehand drawing, writing or highlighting.
///
/// Ink signatures created using `Annotation.Tool.signature` will have this regular
/// ink type after creation. You can check if an ink annotation is a signature using the
/// `isSignature` property, which is a proprietary PSPDFKit extension stored in the PDF.
///
/// @see This tool creates `PSPDFInkAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringInk;
/// Tool for adding rectangles.
///
/// @see This tool creates `PSPDFSquareAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringSquare;
/// Tool for adding ellipses.
///
/// @see This tool creates `PSPDFCircleAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringCircle;
/// Tool for adding lines or arrows.
///
/// @see This tool creates `PSPDFLineAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringLine;
/// Tool for adding polygons (closed shapes).
///
/// @see This tool creates `PSPDFPolygonAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringPolygon;
/// Tool for adding joined straight lines (open shapes).
///
/// @see This tool creates `PSPDFPolyLineAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringPolyLine;
/// Tool for adding electronic signatures.
///
/// Signatures end up as either drawings (`InkAnnotation`/`Annotation.Tool.ink`) or image annotations (`StampAnnotation`/`Annotation.Tool.stamp`).
/// You can check if an annotation is a signature using the `isSignature` property,
/// which is a proprietary PSPDFKit extension stored in the PDF.
///
/// Check out https://pspdfkit.com/guides/ios/signatures/overview/ for more general information about signatures.
///
/// This requires Electronic Signatures to be enabled in your license.
/// (This tool is also available for licenses with Annotations obtained in April 2021 or earlier.
/// In that case, it will offer a more limited signing UI that only supports drawing.)
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringSignature;
/// Tool for adding stamps.
///
/// Images added using `PSPDFAnnotationStringImage` will end up with this type.
///
/// Stamps display text or certain predefined vector images.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringStamp;

/// Special tool for erasing parts of drawings (ink annotations).
///
/// There is no corresponding annotation type.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringEraser;

/// Tool for adding sound annotations.
///
/// Can be played back and recorded by default, but by default playback and recording will not work when the host app is in the background. If you want to enable background playback and recording, you'll need to add the "audio" entry to the `UIBackgroundModes` array in the app's Info.plist. If you do not add this, then recording will be stopped and playback will be silenced when your app is sent into the background.
///
/// @see This tool creates `PSPDFSoundAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringSound;

/// Tool for adding images.
///
/// After being added to a document, an image will have the `typeString` `PSPDFAnnotationStringStamp`.
/// `UIImagePickerController` will be used to pick an image. This will throw a `UIApplicationInvalidInterfaceOrientation` exception if your app does not include portrait in `UISupportedInterfaceOrientations` (Info.plist). For landscape only apps, we suggest enabling portrait orientation(s) in your Info.plist and rejecting these in `UIViewController`’s auto-rotation methods. This way, you can be landscape only for your view controllers and still be able to use `UIImagePickerController`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringImage;

/// Tool for adding redaction annotations.
///
/// @see This tool creates `PSPDFRedactionAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringRedaction;

/// A type for widget annotations, which are used for PDF forms.
///
/// This is a non-writable annotation type. There is no tool for creating form elements.
/// Instead presence or absence of this value in the `editableAnnotationTypes` of the configuration
/// of `PDFViewController` determines whether users can interact with PDF form elements,
/// which edits the *values* of the form fields, but does not change the form elements themselves.
///
/// @see The corresponding annotation types are `PSPDFWidgetAnnotation` and `PSPDFFormElement`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringWidget;
/// File attachment.
///
/// This is a non-writable annotation type. There is no tool for creating file attachments.
///
/// @see The corresponding annotation type is `PSPDFFileAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringFile;
/// Embedded PDF video.
///
/// This is a non-writable annotation type. There is no tool for creating embedded media.
///
/// @see The corresponding annotation type is `PSPDFRichMediaAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringRichMedia;
/// Embedded PDF video.
///
/// This is a non-writable annotation type. There is no tool for creating screen annotations.
///
/// @see The corresponding annotation type is `PSPDFScreenAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringScreen;
/// Caret annotation.
///
/// This is a non-writable annotation type. There is no tool for creating caret annotations.
///
/// @see The corresponding annotation type is `PSPDFCaretAnnotation`.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringCaret;

/// Popup annotation. Placeholder. Not yet supported.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringPopup;
/// Watermark annotation. Placeholder. Not yet supported.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringWatermark;
/// TrapNet annotation. Placeholder. Not yet supported.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringTrapNet;
/// 3D annotation. Placeholder. Not yet supported.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationString3D;

/// Available variants for annotations.
typedef NSString *PSPDFAnnotationVariantString NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(Annotation.Variant);

/// Unique identifier for different annotation types. Amalgamation of annotation type and its variant.
/// Use `PSPDFAnnotationToolVariantIDMake` to generate an identifier in Objective-C.
/// Use `Annotation.ToolVariantID(tool:variant:)` to generate an identifier in Swift.
typedef NSString *PSPDFAnnotationStateVariantID NS_TYPED_ENUM NS_SWIFT_NAME(Annotation.ToolVariantID);

/// Converts an annotation type into the string representation.
/// Swift: `Annotation.Tool(annotationType)`
PSPDF_EXPORT PSPDFAnnotationString _Nullable PSPDFStringFromAnnotationType(PSPDFAnnotationType annotationType) NS_REFINED_FOR_SWIFT;

/// Converts the annotation type string representation to an annotation type.
PSPDF_EXPORT PSPDFAnnotationType PSPDFAnnotationTypeFromString(PSPDFAnnotationString _Nullable string) NS_REFINED_FOR_SWIFT;

/// Localizes the annotation type / variant string. If you have an annotation object, use the `localizedType` property instead of this function.
PSPDF_EXPORT NSString *PSPDFLocalizeAnnotationType(PSPDFAnnotationString type, PSPDFAnnotationVariantString _Nullable variant) NS_REFINED_FOR_SWIFT PSPDF_PURE;

/// Annotation border style types.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAnnotationBorderStyle) {
    /// No border style.
    PSPDFAnnotationBorderStyleNone,
    /// Solid border style.
    PSPDFAnnotationBorderStyleSolid,
    /// Dashed border style. Dashed style can be customized using the dash array.
    PSPDFAnnotationBorderStyleDashed,
    /// Beveled border style. Looks like an "elevated" solid border.
    PSPDFAnnotationBorderStyleBeveled,
    /// Inset border style. Similar to beveled, but is "elevated" into the opposite direction.
    PSPDFAnnotationBorderStyleInset,
    /// Underline border style.
    PSPDFAnnotationBorderStyleUnderline,
    /// Border style can't be determined. Will fallback to solid.
    PSPDFAnnotationBorderStyleUnknown,
} PSPDF_ENUM_SWIFT(Annotation.BorderStyle);

/// Border effect names. See PDF Reference 1.5, 1.6. (Table 167).
typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationBorderEffect) {
    /// No border effect.
    PSPDFAnnotationBorderEffectNoEffect = 0,
    /// Cloudy border effect. Can be customized using `borderEffectIntensity`.
    PSPDFAnnotationBorderEffectCloudy,
} PSPDF_ENUM_SWIFT(Annotation.BorderEffect);

/// `NSValueTransformer` to convert between `PSPDFAnnotationBorderStyle` enum and string value.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFAnnotation` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFBorderStyleTransformerName NS_SWIFT_NAME(borderStyle);

/// `NSValueTransformer` to convert between `PSPDFAnnotationBorderEffect` enum and string value.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFAnnotation` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFBorderEffectTransformerName NS_SWIFT_NAME(borderEffect);

/// A set of flags specifying various characteristics of the annotation.
/// PSPDFKit doesn't support all of those flag settings.
typedef NS_OPTIONS(NSUInteger, PSPDFAnnotationFlags) {
    /// If set, ignore annotation AP stream if there is no handler available.
    PSPDFAnnotationFlagInvisible = 1 << 0,
    /// If set, do not display or print the annotation or allow it to interact with the user.
    PSPDFAnnotationFlagHidden = 1 << 1,
    /// If set, print the annotation when the page is printed.
    PSPDFAnnotationFlagPrint = 1 << 2,
    /// [IGNORED] If set, don't scale the annotation’s appearance to match the magnification of the page.
    PSPDFAnnotationFlagNoZoom = 1 << 3,
    /// [IGNORED] If set, don't rotate the annotation’s appearance to match the rotation of the page.
    PSPDFAnnotationFlagNoRotate = 1 << 4,
    /// If set, don't display the annotation on the screen. (But printing might be allowed)
    PSPDFAnnotationFlagNoView = 1 << 5,
    /// If set, don’t allow the annotation to be deleted or its properties to be modified, including `contents`.
    ///
    /// This is ignored for widget annotations (form elements).
    /// For widget annotations the `isReadOnly` property of the associated form field should be used instead.
    ///
    /// This flag only restricts the PSPDFKit UI and does not impact programmatic modification of the annotation.
    ///
    /// This flag does not restrict adding replies to the annotation, although the replies themselves are
    /// also annotations so may be marked as read-only.
    ///
    /// To transiently make an annotation read-only, use the `isEditable` property instead.
    PSPDFAnnotationFlagReadOnly = 1 << 6,
    /// If set, don’t allow the annotation to be deleted or its properties to be modified, except for `contents`.
    ///
    /// This means the text of free text annotations can still be edited and forms can still be filled.
    /// To prevent editing the `contents`, enable the `.readOnly` flag or enable both the `.locked` and `.lockedContents` flags.
    ///
    /// PSPDFKit follows the PDF reference for this flag by not restricting editing `contents` when this flag
    /// is enabled. This does not match the behavior of Adobe Acrobat, which seems to treat this flag the same
    /// as `.readOnly` by also restricting editing `contents` when this flag is set (except for form elements).
    ///
    /// The Adobe Acrobat UI allows the user to lock and unlock annotations. PSPDFKit does not include any similar UI.
    ///
    /// This flag only restricts the PSPDFKit UI and does not impact programmatic modification of the annotation.
    PSPDFAnnotationFlagLocked = 1 << 7,
    /// [IGNORED] If set, invert the interpretation of the `.noView` flag for certain events.
    PSPDFAnnotationFlagToggleNoView = 1 << 8,
    /// If set, don't allow the `contents` of the annotation to be modified by the user.
    ///
    /// To prevent editing other properties or deleting, enable the `.readOnly` flag or enable both the `.locked` and `.lockedContents` flags.
    ///
    /// This is ignored for widget annotations (form elements).
    /// For widget annotations the `isReadOnly` property of the associated form field should be used instead.
    ///
    /// This flag only restricts the PSPDFKit UI and does not impact programmatic modification of the annotation.
    ///
    /// This flag does not restrict adding replies to the annotation, although the replies themselves are
    /// also annotations so may have their contents locked.
    PSPDFAnnotationFlagLockedContents = 1 << 9
} PSPDF_ENUM_SWIFT(Annotation.Flag);

/// Trigger events for certain viewer actions. See PDF Reference 1.7, 423ff.
typedef NS_CLOSED_ENUM(UInt8, PSPDFAnnotationTriggerEvent) {
    /// Cursor Enters. (Unsupported) E (0)
    PSPDFAnnotationTriggerEventCursorEnters,
    /// Cursor Exits. (Unsupported) X  (1)
    PSPDFAnnotationTriggerEventCursorExits,
    /// Triggered on `touchesBegan:` D  (2)
    PSPDFAnnotationTriggerEventMouseDown,
    /// Triggered on `touchesEnded:` U  (3)
    PSPDFAnnotationTriggerEventMouseUp,
    /// Triggers when the annotation is tapped. Fo (4)
    PSPDFAnnotationTriggerEventReceiveFocus,
    /// Triggers when the annotation is tapped. Bl (5)
    PSPDFAnnotationTriggerEventLoseFocus,
    /// Page opens. (Unsupported) PO (6)
    PSPDFAnnotationTriggerEventPageOpened,
    /// Page closes. (Unsupported) PC (7)
    PSPDFAnnotationTriggerEventPageClosed,
    /// Page becomes visible. (Unsupported) PV (8)
    PSPDFAnnotationTriggerEventPageVisible,

    // Form extensions

    /// Form value changes. K  (9)
    PSPDFAnnotationTriggerEventFormChanged,
    /// Form is formatted. F (10)
    PSPDFAnnotationTriggerEventFieldFormat,
    /// Form is validated. V (11)
    PSPDFAnnotationTriggerEventFormValidate,
    /// Form is calculated. C (12)
    PSPDFAnnotationTriggerEventFormCalculate,
} PSPDF_ENUM_SWIFT(Annotation.TriggerEvent);

/// Defines the z-index position where an annotation should be moved to.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationZIndexMove) {
    /// Move the annotation to the front of the z-index stack.
    PSPDFAnnotationZIndexMoveToFront,
    /// Move the annotation one position forward on the z-index stack.
    PSPDFAnnotationZIndexMoveForward,
    /// Move the annotation one position backward on the z-index stack.
    PSPDFAnnotationZIndexMoveBackward,
    /// Move the annotation to the back of the z-index stack.
    PSPDFAnnotationZIndexMoveToBack,
} PSPDF_ENUM_SWIFT(Annotation.ZIndexMove);

/// `NSValueTransformer` to convert between `PSPDFAnnotation.TriggerEvent` enum and string value.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFAnnotation` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFAnnotationTriggerEventTransformerName NS_SWIFT_NAME(annotationTriggerEvent);

/// Default value for non-fixed-sized annotations
PSPDF_EXPORT const CGSize PSPDFAnnotationFixedSizeDisabled NS_SWIFT_NAME(Annotation.fixedSizeDisabled);

@class PSPDFDocument, PSPDFDocumentProvider, PSPDFRenderOptions;

/// `Annotation` is the base class for all PDF annotations and form elements.
///
/// Don't directly make an instance of this class, use subclasses like `NoteAnnotation` or `LinkAnnotation`.
/// This class will return `nil` if initialized directly, unless with the type `.undefined`.
///
/// `AnnotationManager` searches the runtime for subclasses of `Annotation` and builds up a dictionary using `supportedTypes`.
///
/// As well as the various annotation subclasses, there are two types to model annotation types:
///
/// - `Annotation.Kind` is mostly used for the type of an existing annotation. As an option set, it can be convenient to add and remote types from certain API such as the `PDFConfiguration`’s `editableAnnotationTypes`.
/// - `Annotation.Tool` is mostly used as the type of a tool for creating annotations. As well as annotation types it includes pure tools such as `.eraser`. The tools are activated in the UI with `AnnotationToolbar` and `AnnotationStateManager`.
///
/// @note Thread safety:
/// Annotation objects should only ever be edited on the main thread. Modify properties on the main thread only if they are already active
/// (for creation, it doesn't matter which thread creates them). Before rendering, obtain a copy of the annotation to ensure it's not mutated while properties are read.
/// Once the `documentProvider` is set, modifying properties on a background thread will throw an exception.
///
/// Annotation properties are specified in normalized PDF coordinates: they take page rotation and `CropBox` offset into account.
/// Prior to PSPDFKit 8 for iOS and PSPDFKit 3 for macOS properties were specified in PDF coordinates: not taking the page rotation
/// and offset into account. After unarchiving annotations from `NSCoder` archives created with older versions of PSPDFKit, the
/// properties will be untransformed, and will be modified to apply the page transform when the annotation is added to a document.
///
/// Annotations contain internal state once they are attached to a document. Don't take them and add them to another document.
/// Instead, create a new annotation and set the properties relevant for you, and add this annotation.
///
/// For efficiency and control, you must manually notify PSPDFKit after modifying the properties
/// of annotations. After changing any annotation properties, post an `.PSPDFAnnotationChanged`
/// notification to ensure the annotation is re-rendered and the UI is updated. If you change
/// multiple properties at once, you just need to post the notification once.
///
/// @warning Annotations are mutable objects. Do not store them in `NSSet` or other objects that require a hash-value that does not change.
PSPDF_CLASS_SWIFT(Annotation)
@interface PSPDFAnnotation : PSPDFModel

/// Annotation can be deleted under following rules:
///
/// - is editable
/// - is not locked
///
/// For UI implementations, you might want to perform following additional checks that are not part of this helper:
/// - document is savable.
/// - annotation is part of editableAnnotationTypes on the document.
///
/// @note Both annotations and forms (widgets) can be deleted. For forms, most of the time a reset is more appropriate though.
/// Deleting forms/widgets requires licensing the Forms component. Deleting annotations requires the Annotation component.
@property (nonatomic, readonly) BOOL isDeletable;

/// Returns the size of a fixed-size annotation. Defaults to `PSPDFAnnotationFixedSizeDisabled` for non-fixed-sized annotations.
@property (atomic, readonly) CGSize fixedSize;

/// Returns YES if the annotation wants a selection border. Defaults to YES.
@property (atomic, readonly) BOOL wantsSelectionBorder;

/// Returns YES if this annotation requires an implicit popup annotation.
@property (atomic, readonly) BOOL requiresPopupAnnotation;

/// This is a convenience property that checks for `.readOnly` in `flags`.
///
/// @see `PSPDFAnnotationFlagReadOnly`
@property (atomic, getter=isReadOnly, readonly) BOOL readOnly;

/// This is a convenience property that checks for `.locked` in `flags`.
///
/// @see `PSPDFAnnotationFlagLocked`
@property (atomic, getter=isLocked, readonly) BOOL locked;

/// This is a convenience property that checks for `.lockedContents` in `flags`.
///
/// @see `PSPDFAnnotationFlagLockedContents`
@property (atomic, readonly, getter=isContentsLocked) BOOL contentsLocked;

/// Returns YES if this annotation type is moveable.
@property (atomic, getter=isMovable, readonly) BOOL movable;

/// Returns YES if this annotation type is resizable (all but note and sound annotations usually are).
@property (atomic, getter=isResizable, readonly) BOOL resizable;

/// Whether the annotation should maintain its aspect ratio when resized.
///
/// Defaults to false for most annotations. Defaults to true for drawn signatures (ink signatures), stamps, and images (including image signatures).
///
/// This constraint is enforced by `ResizableView`, not by the annotation itself.
/// If you resize an annotation programmatically, you may want to implement honoring this property.
@property (atomic, readonly) BOOL shouldMaintainAspectRatio;

/// Returns the minimum size that an annotation can properly display. Defaults to (16, 16).
@property (atomic, readonly) CGSize minimumSize;

/// Check if `point` is inside the annotation area, while making sure that the hit area is at least `minDiameter` wide.
/// The default implementation performs hit testing based on the annotation bounding box, but concrete subclasses can (and do)
/// override this behavior in order to perform custom checks (e.g., path-based hit testing).
///
/// @note The usage of `minDiameter` is annotation specific.
- (BOOL)hitTest:(CGPoint)point minDiameter:(CGFloat)minDiameter;

/// The annotation position on the current page in the coordinate space of a `UIView` displaying the page.
///
/// @param pageRect The bounds of a `UIView` that displays the page the annotation is on, where the page fills the view bounds exactly.
///
/// @return The annotation bounding box in the coordinate space of the `UIView` whose bounds were passed in.
- (CGRect)boundingBoxForPageRect:(CGRect)pageRect;

/// The annotation type.
@property (nonatomic, readonly) PSPDFAnnotationType type;

/// Page index for current annotation. Page is relative to `documentProvider`. First page in the document is page 0.
///
/// @warning Only set the page at creation time and don't change it later on. This would break internal caching. If you want to move an annotations to a different page, copy an annotation, add it again and then delete the original.
/// @note When an annotation is serialized as JSON using `PSPDFJSONAdapter` the value of this property is written with the key `page` for backwards compatibility.
@property (atomic) PSPDFPageIndex pageIndex;

/// Page index relative to the document. First page in the document is page 0.
///
/// @note Will be calculated each time from `pageIndex` and the current `documentProvider` and will change `pageIndex` if set.
@property (atomic) PSPDFPageIndex absolutePageIndex;

/// Corresponding `PSPDFDocumentProvider`.
@property (atomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

/// Document is inferred from the `documentProvider` (Convenience method)
@property (atomic, weak, readonly) PSPDFDocument *document;

/// If this annotation isn't backed by the PDF, it's dirty by default.
/// After the annotation has been written to the file, this will be reset until the annotation has been changed.
@property (atomic, getter=isDirty) BOOL dirty;

/// If YES, the annotation will be rendered as a overlay. If NO, it will be statically rendered within the PDF content image.
/// Rendering as overlay is more performant if you frequently change it, but might delay page display a bit.
///
/// @note `PSPDFAnnotationTypeLink` and `PSPDFAnnotationTypeNote` currently are rendered as overlay.
/// If `overlay` is set to YES, you must also register the corresponding *annotationView class to render (override `PSPDFAnnotationManager`’s `defaultAnnotationViewClassForAnnotation:`)
@property (atomic, getter=isOverlay) BOOL overlay;

/// By default, annotations are editable when `isReadOnly` returns `false`. This property can be used
/// to temporarily lock annotations that are originally editable. (menu won't be shown)
/// Setting `editable` to `true` will have no effect if `isReadOnly` is true. To ignore `isReadOnly`
/// and make an annotation editable regardless, override the getter and make it always return `true`.
///
/// The `editable` property also behaves a little differently for form elements. For them, the `editable`
/// property refers to the form fields attached to the elements.
///
/// @note This is a strictly transient property that is not written to the backing data store.
/// To persistently disable editing, enable the `.readOnly` flag instead.
@property (atomic, getter=isEditable) BOOL editable;

/// Indicator if annotation has been soft-deleted (Annotation may already be deleted locally, but not written back.)
///
/// @note Doesn't check for the `isDeletable` property. Use `removeAnnotations:` on `Document` to delete annotations.
@property (atomic, getter=isDeleted) BOOL deleted;

/// Annotation type string as defined in the PDF.
/// Usually read from the annotDict. Don't change this unless you know what you're doing.
@property (atomic, copy, readonly) PSPDFAnnotationString typeString;

/// The tool variant, that was used during the annotation creation. Defaults to nil.
/// This is a proprietary extension and saved into the PDF as `PSPDF:Variant` key.
///
/// @note The style inspector stores previously used styles based on type + variant.
/// See `PSPDFAnnotationGroupItem.h` for `PSPDFAnnotationVariantString` defaults.
@property (atomic, copy, nullable) PSPDFAnnotationVariantString variant;

/// The opacity of the annotation from 0 to 1.
/// This is independent of the `color` and `fillColor` and applies to the whole annotation.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic) CGFloat alpha;

/// Color associated with the annotation or `nil` if there is no color.
/// This is the text color for `FreeTextAnnotation`, `PSPDFTextFieldFormElement`, and `PSPDFChoiceFormElement`.
///
/// @note The annotation will only store the RGB part and discard the alpha channel set here. Annotation opacity is set via the `alpha` property.
/// Setting `UIColor.clearColor` is equivalent to setting `nil`.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, nullable) UIColor *color;

/// Border Color usually redirects to color, unless overridden to have a real backing ivar.
/// (`PSPDFWidgetAnnotation` has such a backing store)
///
/// A nil border color means the border is black.
///
/// @note If the dash array is invalid, the border will not be rendered. See PDF Reference §8.4.3.6 (Table 55).
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, nullable) UIColor *borderColor;

/// Fill color. Only used for certain annotation types. ("IC" key, e.g. Shape Annotations)
/// Fill color might be `nil` - treat like `clearColor` in that case.
///
/// @note The annotation will only store the RGB part and discard the alpha channel set here. Annotation opacity is set via the `alpha` property.
/// Setting `UIColor.clearColor` is equivalent to setting `nil`.
/// Apple Preview.app will not show you transparency in the `fillColor`.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, nullable) UIColor *fillColor;

/// Defines a custom blend mode.
///
/// Supported values include `kCGBlendModeNormal` to `kCGBlendModeExclusion`.
///
/// @note The blend mode is not defined in the PDF spec, therefore it's not stored as part of the annotation dictionary, but in the annotation's appearance stream.
/// If another editor/viewer does not use appearance stream or ends up regenerating them to redraw then the blend mode set here might not be preserved.
///
/// @b See Appearance Stream https://pspdfkit.com/blog/2018/what-are-appearance-streams/.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic) CGBlendMode blendMode;

/// Various annotation types may contain text. Optional.
///
/// For most annotation types, this is displayed as a note/comment in a popup. For free text annotations the `contents` is the text shown on the page.
///
/// PSPDFKit’s UI will disallow editing this if `.lockedContents` is enabled in `flags`. However even in that case this property may still be changed programmatically.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, copy, nullable) NSString *contents;

/// Subject property (corresponding to "Subj" key).
/// Text representing a short description of the subject being addressed by the annotation.
/// Prior to PSPDFKit 8.1 for iOS and 3.1 for macOS, this was used as the text displayed by a stamp annotation.
/// It no longer has any effect on rendering.
@property (atomic, copy, nullable) NSString *subject;

/// Dictionary for additional action types.
/// The key is of type `Annotation.TriggerEvent`.
@property (nonatomic, copy, nullable) NSDictionary<NSNumber *, __kindof PSPDFAction *> *additionalActions NS_REFINED_FOR_SWIFT;

/// (Optional; inheritable) The field’s value, whose format varies depending on the field type. See the descriptions of individual field types for further information.
@property (atomic, copy, nullable) id value;

/// An annotation’s flags property is an option set that encompasses various properties which
/// may be used to alter visibility or restrict editing in the UI. Defaults to `.print`.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic) PSPDFAnnotationFlags flags;

/// This is a convenience property that checks for `.hidden` in `flags`.
///
/// @see `PSPDFAnnotationFlagHidden`
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic, getter=isHidden) BOOL hidden;

/// The annotation name, a text string uniquely identifying it among all the annotations on its page.
/// (Optional; PDF1.4, "NM" key)
///
/// @note We generate a unique identifier for newly created annotations.
@property (nonatomic, copy, nullable) NSString *name;

/// The name of the user who created the annotation (AKA annotation author). Also sometimes called the title of the annotation, since this is the "T" property in the PDF.
@property (nonatomic, copy, nullable) NSString *user;

/// Annotation group key. May be used to have multiple annotations that behave as single one, if their `group` string is equal. Only works within one page.
/// This is a proprietary extension and saved into the PDF as "PSPDF:GROUP" key.
@property (nonatomic, copy, nullable) NSString *group;

/// A unique in-memory identifier for each annotation. Stays the same when the object is copied via NSCopying.
/// Generated at runtime, therefore not persisted (in the PDF).
///
/// In contrast with `name`, this is guaranteed to be always set, even for existing annotations in a document.
@property (nonatomic, readonly) NSString *uuid;

/// Date when the annotation was created. Might be nil.
/// PSPDFKit will set this for newly created annotations.
///
/// @note Due to PDF standard limitations, the sub-second precision of NSDate is lost,
/// if the annotation is saved and subsequently re-read from a PDF. This also impacts annotation equality checks.
@property (nonatomic, nullable) NSDate *creationDate;

/// Date when the annotation was last modified. Might be nil.
/// Saved into the PDF as the "M" property (Optional, since PDF 1.1)
///
/// @note This property is updated anytime a different property is modified.
/// Due to PDF standard limitations, the sub-second precision of NSDate is lost,
/// if the annotation is saved and subsequently re-read from a PDF.
@property (atomic, nullable) NSDate *lastModified;

/// Border Line Width (only used in certain annotations)
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic) CGFloat lineWidth;

/// Annotation border style.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic) PSPDFAnnotationBorderStyle borderStyle;

/// (Optional; valid only if the value of `borderStyle` is `PSPDFAnnotationBorderStyleDashed`)
/// Array of boxed integer-values defining the dash style.
///
/// Values |        Dash
/// --------------------------------
/// []   |   ━━━━━━━━━━━━━━━━━━━━
/// [3]  |   ━   ━━━   ━━━   ━━━
/// [2]  |   ━  ━  ━  ━  ━  ━  ━
/// [2,1]|   ━━ ━━ ━━ ━━ ━━ ━━ ━━
/// [3,5]|   ━━━     ━━━     ━━
/// [2,3]|   ━   ━━   ━━   ━━   ━
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic, copy, nullable) NSArray<NSNumber *> *dashArray NS_REFINED_FOR_SWIFT;

/// Border effect. Currently supports No Effect or Cloudy.
///
/// @note `borderEffectIntensity` should be set to non-zero (e.g. 1.0) for Cloudy border to be displayed.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic) PSPDFAnnotationBorderEffect borderEffect;

/// (Optional; valid only if the value of `borderEffect` is `PSPDFAnnotationBorderEffectCloudy`)
/// A number describing the intensity of the effect. The value is suggested to be between 0 and 2 but other values are valid as well. Defaults to: 0.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic) CGFloat borderEffectIntensity;

/// The annotation’s size and location on the page, specified in page coordinates.
///
/// @note Other properties might be adjusted, depending what `shouldTransformOnBoundingBoxChange` returns.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic) CGRect boundingBox;

/// Certain annotation types like highlight can have multiple rects.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic, copy, nullable) NSArray<NSValue /* CGRect */ *> *rects NS_REFINED_FOR_SWIFT;

/// Line, Polyline and Polygon annotations have points.
/// Contains `NSValue` objects that box a `CGPoint`.
///
/// @note These values might be generated on the fly from an internal, optimized representation.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (nonatomic, copy, nullable) NSArray<NSValue /* CGPoint */ *> *points NS_REFINED_FOR_SWIFT;

/// The PDF object number.
/// If this is -1, the object is not referenced in the PDF yet.
@property (nonatomic, readonly) NSInteger objectNumber;

/// Returns `self.contents` or something appropriate per annotation type to describe the object.
@property (nonatomic, readonly) NSString *localizedDescription;

/// Return icon for the annotation, if there's one defined.
@property (nonatomic, readonly, nullable) UIImage *annotationIcon;

/// YES if the annotation is a reply to another.
///
/// This is specified by the presence of an IRT (in-reply-to) entry on the annotation in the PDF.
///
/// The default is NO for newly created annotations.
///
/// Calling this is faster than `annotation.inReplyToAnnotation != nil` and does
/// not need `Features.annotationReplies`. So if your license does not
/// include this feature and the annotation is a reply, `inReplyToAnnotation` will
/// be nil but this property will still be YES.
///
/// If you have a custom page rendering component you can use this property to hide
/// replies on the page.
@property (nonatomic, readonly, getter=isReply) BOOL reply;

/// The annotation the receiver is a reply to. This is the IRT (in-reply-to) entry on the annotation in the PDF.
///
/// This property is nil if this annotation is not a reply. The default is nil for newly created annotations.
///
/// When setting this, the annotation being set must have been added to the document.
///
/// This requires `Features.annotationReplies`. If that license feature
/// is not available the getter will return nil and the setter will do nothing.
///
/// To check if an annotation is a reply, it is faster to use `isReply` than to
/// check if this property is nil.
@property (nonatomic, nullable) PSPDFAnnotation *inReplyToAnnotation;

/// Annotations can store additional user-specified data.
///
/// PSPDFKit will not use or evaluate `customData` in the UI directly.
/// You have full control over this property. For a new annotation, this defaults to nil.
///
/// Custom data will be serialized via NSCoder, InstantJSON, XFDF and PDF saving.
/// Setting customData will create a copy of the root object.
/// Ensure to not store mutable objects that could be mutated externally.
///
/// @note Following types are allowed:
/// `NSArray`, `NSDictionary`, `NSString`, `NSNull` and `NSNumber` (and their Swift equivalents).
/// For storing boolean values, use `(id)kCFBooleanTrue`, `(id)kCFBooleanFalse`, `@YES`, `@NO`, or an `NSNumber` initialized using `+numberWithBool:`.
/// Only unique strings as dictionary keys are allowed, see `NSJSONSerialization` for details on object restrictions.
/// Adding any other datatype will cause an assertion when setting this property.
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *customData;

/// Compare.
- (BOOL)isEqualToAnnotation:(PSPDFAnnotation *)otherAnnotation;

// MARK: - Appearance Stream

/// Returns YES if a custom appearance stream is attached to this annotation.
///
/// @note An appearance stream is a custom representation for annotations, much like a PDF within a PDF.
@property (nonatomic, readonly) BOOL hasAppearanceStream;

/// Clears any appearance stream, if set.
///
/// @see hasAppearanceStream to check if one is set.
- (void)clearAppearanceStream;

/// Allows you to override the appearance stream generation method of this annotation. The `appearanceStreamGenerator`
/// will be called when necessary to generate the annotations appearance stream.
///
/// By default, this is set to `+[PSPDFDrawingContextAppearanceStreamGenerator defaultDrawingContextAppearanceStreamGenerator]` for all
/// types except `PSPDFFormElement`. `PSPDFStampAnnotations` may in certain situations set
/// `PSPDFRetainExistingAppearanceStreamGenerator` to prevent regeneration of an appearance stream if it would overwrite data.
///
/// Setting a custom appearance stream generator will completely override the default design, and thus ignores any custom set properties such as `fillColor` or `lineWidth`.
/// Therefore custom appearance stream generators should only be used for vector stamp annotations. Use with other annotation types is not supported.
///
/// @note This does NOT automatically remove the existing appearance stream and replace it with the generated one. The
/// appearance stream only gets generated if the annotation has been modified.
/// @note `appearanceStreamGenerator` is not supported on `SignatureFormElement`. Please use `PDFSignatureAppearance`.
/// @note If you intend to use `appearanceStreamGenerator` on a annotation subclass that has `draw(context:options:)` overridden, you have to
/// call `maybeRenderCustomAppearanceStream(with:options:)` and return if it returns true.
@property (atomic, nullable) id<PSPDFAppearanceStreamGenerating> appearanceStreamGenerator;

/// This method checks if a custom `appearanceStreamGenerator` is set and if it should be used to render the given annotation. If so,
/// it might call the `appearanceStreamGenerator` and render the resulting appearance stream.
///
/// This needs to be called in the beginning of `drawInContext:options:` and if it returns YES, no further drawing should be
/// done in the method.
- (BOOL)maybeRenderCustomAppearanceStreamWithContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)options;

// MARK: - Undo

/// A set of properties to be taken into account when performing undo.
///
/// This set doesn't necessarily need to be a subset of `propertyKeys`. It can
/// contain additional keys, as long as they they are read-write and conform to
/// the KVC naming convention.
///
/// This set can be overridden by subclasses to provide additional keys on top
/// of the default ones. Remember to union the sets with `super`.
@property (class, nonatomic, readonly) NSSet<NSString *> *propertyKeysForUndo;

/// A variant of `setValue:forKeyPath:` that is used when performing undo.
///
/// This method can be overridden by subclasses to customize the behavior of
/// setting certain properties when performing undo (e.g. to disable cascading
/// changes).
- (void)setUndoneValue:(nullable id)value forKeyPath:(NSString *)keyPath;

@end

@interface PSPDFAnnotation (Drawing)

/// Acquires all relevant locks, prepares the context for rendering, and then renders the receiver into
/// it — either using the appearance stream, or by calling through to `drawInContext:options:`.
///
/// @note When in doubt, prefer calling this method over `drawInContext:options:`. The latter is meant
/// to be called when an AP stream is unavailable.
- (void)lockAndRenderInContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)options;

/// The drawing primitive used when rendering the annotation. Can be overridden to customize the
/// appearance of an annotation class.
///
/// PSPDFKit will call this method when an annotation needs to be rendered in a graphics context —
/// either for immediate display, or to preserve the exact appearance in the PDF file (also known as
/// generating an appearance stream).
/// This method expects to be called with a `context` that uses the normalized PDF coordinate space.
/// Therefore, overrides that want to customize drawing by including additional view elements need to
/// transform coordinates accordingly. Furthermore, you should either call `super` at the beginning of
/// your override, or undo any coordinate transforms applied to `context` before calling `super` to
/// avoid unexpected behavior.
///
/// @param context A graphics context that uses the normalized PDF coordinate space.
/// @param options Optionally contains details about how to draw the annotation, and for what purpose.
///
/// @note You should not call this method yourself! If you want to manually render an annotation,
/// please use `image(size:options:)` instead.
- (void)drawInContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)options NS_SWIFT_NAME(draw(context:options:));

/// Renders the annotation as an image.
///
/// Will return nil if `size` is doesn’t have positive width and height.
/// To avoid exhausting memory, this will return a smaller image than requested if `size` is extremely large.
- (nullable UIImage *)imageWithSize:(CGSize)size options:(nullable PSPDFRenderOptions *)options NS_SWIFT_NAME(image(size:options:));

/// Point for the note icon. Override to customize.
@property (nonatomic, readonly) CGPoint noteIconPoint;

/// Configures if the note icon, that indicates an attached note or replies to the annotation,
/// should be drawn. Defaults to YES.
///
/// @note Additional checks are honored, to determine if the note icon should be rendered:
/// - The annotation has `contents` set or has replies.
/// - The annotation is not rendered for flattening (`PSPDFAnnotationDrawFlattenedKey` is not used).
/// - The annotation author is not 'AutoCAD SHX Text'. See https://knowledge.autodesk.com/support/autocad/learn-explore/caas/CloudHelp/cloudhelp/2016/ENU/AutoCAD-Core/files/GUID-56EA988C-A1DA-4E85-8765-B3F31A01AB02-htm.html
@property (nonatomic, readonly) BOOL shouldDrawNoteIconIfNeeded;

@end

@interface PSPDFAnnotation (Advanced)

/// Some annotations might change their points/lines/size when the bounding box changes.
/// This returns NO by default.
@property (nonatomic, readonly) BOOL shouldUpdatePropertiesOnBoundsChange;
@property (nonatomic, readonly) BOOL shouldUpdateOptionalPropertiesOnBoundsChange;

- (void)updatePropertiesWithTransform:(CGAffineTransform)transform isSizeChange:(BOOL)isSizeChange meanScale:(CGFloat)meanScale;
- (void)updateOptionalPropertiesWithTransform:(CGAffineTransform)transform isSizeChange:(BOOL)isSizeChange meanScale:(CGFloat)meanScale;

/// Manually controls if with setting the `boundingBox` it should be transformed as well.
- (void)setBoundingBox:(CGRect)boundingBox transform:(BOOL)transform includeOptional:(BOOL)optionalProperties;

/// Copy annotation object to `UIPasteboard` (multiple formats).
- (void)copyToClipboard;

@end

/// Key for attributed string attribute that contains the font size - this is set if the font size is defined.
PSPDF_EXPORT NSString *const PSPDFFontSizeName;

/// Key for vertical text alignment in `fontAttributes`.
PSPDF_EXPORT NSString *const PSPDFVerticalAlignmentName;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFVerticalAlignment) {
    PSPDFVerticalAlignmentTop = 0,
    PSPDFVerticalAlignmentCenter = 1,
    PSPDFVerticalAlignmentBottom = 2,
    PSPDFVerticalAlignmentNone = 3
} PSPDF_ENUM_SWIFT(Annotation.VerticalAlignment);

/// Key for the original font name when a fallback font is used to draw the annotation’s content.
///
/// When the font specified for an annotation with text contents isn’t available on the device, a
/// fallback font will be used to render that text. In order to preserve this data, even when updating
/// other aspects of the annotation, the original font name will be stored as an `NSString` under this
/// key in the `fontAttributes` dictionary of the annotation while the fallback is in effect.
///
/// As PSPDFKit will attempt to load the original font when possible, this value may be cleared later
/// when the font has successfully been downloaded, and display of the annotation updated accordingly.
PSPDF_EXPORT NSString *const PSPDFOriginalFontNameAttributeName;

/// Constant to convert `PSPDFVerticalAlignment` into `NSString` and back.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFAnnotation` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFVerticalAlignmentTransformerName NS_SWIFT_NAME(verticalAlignment);

/// This defines properties for annotations with styled text.
/// Valid for `FreeTextAnnotation`, `PSPDFTextFieldFormElement`, and `PSPDFChoiceFormElement`.
/// Several of the properties here are shortcuts for accessing data in the `fontAttributes` dictionary.
@interface PSPDFAnnotation (Fonts)

/// Supports attributes for the text rendering, similar to the attributes in `NSAttributedString`.
///
/// @note Supported keys are:
/// `NSUnderlineStyleAttributeName` and `NSStrikethroughStyleAttributeName`, valid values `NSUnderlineStyleNone` and `NSUnderlineStyleSingle`.
/// A font can either be underline or strikethrough, not both.
/// `UIFontDescriptorTraitsAttribute` takes a boxed value of `UIFontDescriptorSymbolicTraits`, valid options are `UIFontDescriptorTraitItalic` and `UIFontDescriptorTraitBold`.
///
/// Setting `NSForegroundColorAttributeName` will also update the `color` property.
/// Several other properties on this class are shortcuts for accessing data in this dictionary.
/// Further attributes might be rendered and saved, but are not persisted in the PDF.
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *fontAttributes;

/// The font name, if defined.
///
/// @note Shortcut for `[self.fontAttributes[NSFontAttributeName] familyName]`.
@property (nonatomic, copy, nullable) NSString *fontName;

/// Font size, if defined. Setting this to 0 will use the default size or (for forms) attempt auto-sizing the text.
///
/// @note Shortcut for `self.fontAttributes[PSPDFFontSizeName]`.
@property (nonatomic) CGFloat fontSize;

/// Text justification. Allows `NSTextAlignmentLeft`, `NSTextAlignmentCenter` and `NSTextAlignmentRight`.
///
/// @note This is a shortcut for the data saved in `fontAttributes` (`NSParagraphStyleAttributeName`) and will modify `fontAttributes`.
@property (nonatomic) NSTextAlignment textAlignment;

/// Vertical text alignment. Defaults to `PSPDFVerticalAlignmentNone`.
///
/// @note Shortcut for `self.fontAttributes[PSPDFVerticalAlignmentName]`.
/// @warning This is not defined in the PDF spec. (PSPDFKit extension), and is only supported for use with Free Text Annotations. This value is ignored for all other types of annotations.
@property (nonatomic) PSPDFVerticalAlignment verticalTextAlignment;

/// Return a default font size if not defined in the annotation.
- (CGFloat)defaultFontSize;

/// Return a default font name (Helvetica) if not defined in the annotation.
- (NSString *)defaultFontName;

/// Returns the currently set font (calculated from defaultFontSize)
- (UIFont *)defaultFont;

/// Attributed string, used for free text, and text and choice form elements.
@property (nonatomic, readonly, nullable) NSAttributedString *attributedString;

/// This helper creates the attribute string.
/// There are multiple events that can lead to a re-creation of the attributed string (such as background copies).
/// Override this to fine-customize the properties for rendering.
///
/// @note Rendering uses CoreText, so certain UIKit-only attributes such as `NSBackgroundColorAttributeName` will not be rendered.
- (nullable NSAttributedString *)attributedStringWithContents:(nullable NSString *)contents options:(nullable PSPDFRenderOptions *)options;

/// Convenience forwarding `contents` and no `options` to `attributedStringWithContents:options:`.
- (nullable NSAttributedString *)attributedStringWithContents:(nullable NSString *)contents;

@end

/// This defines the methods for serialization to, and deserialization from, Instant JSON.
@interface PSPDFAnnotation (InstantJSON)

/// Creates an annotation from JSON data that follows our Instant JSON specification.
///
/// @param instantJSON A `Data` object containing the Instant Annotation JSON. For example, `NSData *data = [jsonString dataUsingEncoding:NSUTF8StringEncoding];`
/// @param documentProvider The document provider from which this annotation is to be generated.
/// @param error A pointer to an `NSError` object that is set when an error occurs.
/// @return Returns nil if an annotation could not be read from the JSON data and sets `error`.
+ (nullable PSPDFAnnotation *)annotationFromInstantJSON:(NSData *)instantJSON documentProvider:(PSPDFDocumentProvider *)documentProvider error:(NSError **)error;

/// Generates the JSON for the receiver according to the Instant Annotation JSON specification.
///
/// @note In order to generate the JSON serialization for an annotation, the annotation has to be added to a document.
///
/// @param error A pointer to an error object that is set to an actual error if an error occurs.
/// @return A `Data` object containing the Instant JSON representation of the receiver. Can be converted into JSON string like so: `NSString *jsonString = [[NSString alloc] initWithData:result encoding:NSUTF8StringEncoding];`
- (nullable NSData *)generateInstantJSONWithError:(NSError *__autoreleasing*)error;

/// Checks if this annotation has a binary Instant JSON attachment. For example, a stamp annotation with an image has one.
///
/// You can use `writeBinaryInstantJSONAttachmentToDataSink:error:` to fetch the attachment.
@property (nonatomic, readonly) BOOL hasBinaryInstantJSONAttachment;

/// If this annotation has a binary Instant JSON attachment, writes it into the `dataSink`.
///
/// @param dataSink The data sink the binary attachment will be written to. See `PSPDFFileDataSink` or `PSPDFDataContainerSink`.
/// @return The mime type of the attachment if successful, otherwise nil.
- (nullable NSString *)writeBinaryInstantJSONAttachmentToDataSink:(id<PSPDFDataSink>)dataSink error:(NSError **)error;

/// Attaches a binary Instant JSON attachment to the annotation. Can be generated using `writeBinaryInstantJSONAttachmentToDataSink:error:`.
///
/// @param dataProvider The data provider with the binary Instant JSON data.
/// @return YES if successful, otherwise NO.
- (BOOL)attachBinaryInstantJSONAttachmentFromDataProvider:(id<PSPDFDataProviding>)dataProvider error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
