//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFContainerView.h>
#import <PSPDFKitUI/PSPDFAnnotationPresenting.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKit/PSPDFSignatureBiometricProperties.h>
#import <QuartzCore/QuartzCore.h>
#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFDrawingPoint.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFPolygonAnnotation.h>
#import <PSPDFKit/PSPDFSquareAnnotation.h>

@class PSPDFDrawView, PSPDFPageView, PSPDFInkAnnotation;

typedef NS_CLOSED_ENUM(NSInteger, PSPDFDrawViewInputMode) {
    /// Touches perform drawing operations.
    PSPDFDrawViewInputModeDraw,

    /// Touches perform erase operations.
    PSPDFDrawViewInputModeErase
} PSPDF_ENUM_SWIFT(DrawView.InputMode);

NS_ASSUME_NONNULL_BEGIN

/// A delegate that is notified when the draw view begins or ends drawing a stroke.
/// The implementation of these calls should persist the annotation changes to the document as well as
/// recording the changes for undo.
PSPDF_PROTOCOL_SWIFT(DrawViewDelegate)
@protocol PSPDFDrawViewDelegate<NSObject>

/// Called when the draw view detects a touch and begins drawing or erasing an annotation.
/// This is the suggested place to begin recording an undo command.
///
/// @param drawView The draw view in which the drawing is being carried out.
/// @param inputMode Whether the draw view is adding a new stroke or performing erasing.
- (void)drawView:(PSPDFDrawView *)drawView didBeginDrawingInMode:(PSPDFDrawViewInputMode)inputMode;

/// Called when the draw view finishes drawing or erasing an annotation.
/// This is the suggested place to commit recording an undo command.
///
/// @param drawView The draw view in which the drawing is being carried out.
/// @param inputMode Whether the draw view was adding a new stroke or performing erasing.
/// @param didFinish Whether the drawing stroke was carried out successfully. `false` when the drawing stroke fails or is cancelled.
- (void)drawView:(PSPDFDrawView *)drawView didEndDrawingInMode:(PSPDFDrawViewInputMode)inputMode finished:(BOOL)didFinish;

/// The draw view is asking the delegate to add an annotation to the document.
/// This is also the suggested place to record an undo command for adding the annotation.
///
/// @param drawView The draw view in which the annotation was drawn.
/// @param annotation The annotation that should be added to the document.
- (void)drawView:(PSPDFDrawView *)drawView wantsToAddAnnotation:(PSPDFAnnotation *)annotation;

/// The draw view is asking the delegate to modify an annotation using the given block.
/// This can be in the form of appending a stroke or erasing.
/// This is also the suggested place to record an undo command for changing the annotation.
///
/// @param drawView The draw view in which the annotation is drawn.
/// @param annotation The annotation that should be modified.
/// @param scope The block that modifies `annotation`. The delegate is responsible for executing it.
- (void)drawView:(PSPDFDrawView *)drawView wantsToModifyAnnotation:(PSPDFAnnotation *)annotation inScope:(void (^)(void))scope;

/// The draw view is asking the delegate to delete an annotation from the document.
/// This is also the suggested place to record an undo command for deleting the annotation.
///
/// @param drawView The draw view in which the annotation was deleted.
/// @param annotation The annotation that should be deleted from the document.
- (void)drawView:(PSPDFDrawView *)drawView wantsToDeleteAnnotation:(PSPDFAnnotation *)annotation;

@end

/// `PSPDFDrawView` allows drawing or erasing on top of a `PDFPageView`
/// and handles new annotation creation.
///
/// Unless otherwise noted, boxed points need to be of type `PSPDFDrawingPoint`.
PSPDF_CLASS_SWIFT(DrawView)
@interface PSPDFDrawView : PSPDFContainerView <PSPDFAnnotationPresenting, PSPDFOverridable>

/// The `DrawView` delegate which is responsible for updating the Document with the changes made to the annotations.
@property (nonatomic, weak) id<PSPDFDrawViewDelegate> delegate;

/// Current annotation type that is being created/edited.
@property (nonatomic) PSPDFAnnotationType annotationType;

/// The selected tool variant. Applied to new annotations.
@property (nonatomic, nullable) PSPDFAnnotationVariantString annotationVariant;

/// Determines what effect touch events have. Defaults to `PSPDFDrawViewInputModeDraw`.
/// `PSPDFDrawViewInputModeErase` only affects Ink annotations.
@property (nonatomic) PSPDFDrawViewInputMode inputMode;

/// The gesture recognizer used to detect drawings.
///
/// Setting its `allowedTouchTypes` property can be used to limit the allowed types
/// however the draw view may still ignore touches even if they are in the list of
/// allowed types. This is used for Apple Pencil support.
///
/// The default `allowedTouchTypes`s are `direct`, `pencil`, and `indirectPointer`.
///
/// @see -[PSPDFAnnotationStateManager stylusMode]
@property (nonatomic, readonly) UIGestureRecognizer *drawGestureRecognizer;

/// Defines how ink annotations are created.
///
/// This determines whether a new annotation is created when a stroke ends.
///
/// @see `PDFConfiguration` for details.
/// @note The default value for this setting is read from the current active `PDFConfiguration` object.
@property (nonatomic) PSPDFDrawCreateMode drawCreateMode;

/// Enables natural drawing via tracking the pressure sensitivity of the points.
///
/// @see `PDFConfiguration` for details.
/// @note The default value for this setting is read from the current active `PDFConfiguration` object.
@property (nonatomic) BOOL naturalDrawingEnabled;

/// Enables the use of predictive touches. Defaults to NO.
/// Enabling this for ink annotation improves the drawing experience.
@property (nonatomic) BOOL predictiveTouchesEnabled;

/// Used to compute approximate line widths during drawing.
/// When a `pageView` is associated this will automatically be set to it's `scaleForPageView`.
/// Defaults to 1.
@property (nonatomic) CGFloat scale;

/// Draw view zoom scale, used for zoom dependent eraser sizing.
/// When a `pageView` is associated this will automatically be set to it's `scrollView.zoomScale`.
/// Defaults to 1.
@property (nonatomic) CGFloat zoomScale;

// MARK: Styling properties

/// Current stroke color.
@property (nonatomic, nullable) UIColor *strokeColor;

/// Current fill color.
@property (nonatomic, nullable) UIColor *fillColor;

/// Current line width.
@property (nonatomic) CGFloat lineWidth;

/// Starting line end type for lines and polylines.
@property (nonatomic) PSPDFLineEndType lineEnd1;

/// Ending line end type for lines and polylines.
@property (nonatomic) PSPDFLineEndType lineEnd2;

/// The stroke dash pattern. Draws a solid line when `nil` (default).
@property (nonatomic, copy, nullable) NSArray<NSNumber *> *dashArray;

/// The border effect style.
@property (nonatomic) PSPDFAnnotationBorderEffect borderEffect;

/// The border effect intensity (if set to cloudy).
/// A number describing the intensity of the effect, in the range 0 to 2. Default value: 0.
@property (nonatomic) CGFloat borderEffectIntensity;

/// Defines a custom blend mode. Supported values include
/// `kCGBlendModeNormal` to `kCGBlendModeExclusion`.
@property (nonatomic) CGBlendMode blendMode;

/// Guide color. Defaults to `UIColor.pspdf_guideColor`.
@property (nonatomic, nullable) UIColor *guideBorderColor UI_APPEARANCE_SELECTOR;

// MARK: Annotation handling

/// All annotations currently managed by the draw view.
@property (nonatomic, readonly) NSArray<PSPDFAnnotation *> *annotations;

/// Adds the provided annotations to the draw view, making them available for editing.
///
/// @note Currently only supports Ink annotations (to facilitate ink erasing).
- (void)updateForAnnotations:(NSArray<PSPDFInkAnnotation *> *)annotations;

/// Clears all drawings, associated annotations and biometric data.
- (void)clear;

// MARK: Points and Biometric Properties

/// Point sequences that are in this draw view. An array of arrays holding `NSValue`s boxing `PSPDFDrawingPoint`s.
///
/// If this draw view is attached to a `PSPDFPageView` then the points are in the coordinate space of the PDF page that
/// the page view is displaying, so the origin is in the bottom-left. Use `PSPDFPageView.pdfCoordinateSpace` to convert these
/// points to the coordinate space of the draw view. Alternatively, if this draw view is not attached to a `PSPDFPageView`
/// then the points are in the coordinate space of the draw view but scaled by `scale`, so the origin is in the top-left.
///
/// Point sequences is an empty array until `endDrawing` is invoked, unless the view was created using an existing annotation.
@property (nonatomic, readonly) NSArray<NSArray<NSValue *> *> *pointSequences NS_REFINED_FOR_SWIFT;

/// An array of boxed floating point values. Representing the intensity of each touch.
/// Includes the same number of objects as `timePoints` and `touchRadii`.
///
/// @note Predictive touches are not tracked.
@property (nonatomic, readonly) NSArray<NSNumber *> *pressureList;

/// An array of boxed `NSTimeInterval`s. Representing the timestamp of each touch.
/// Includes the same number of objects as `pressureList` and `touchRadii`.
///
/// @note Predictive touches are not tracked.
@property (nonatomic, readonly) NSArray<NSNumber *> *timePoints;

/// An array of boxed floating point values. Representing the radius of each touch (or the altitude if an Apple Pencil was used).
/// Includes the same number of objects as `pressureList` and `timePoints`.
///
/// @note Predictive touches are not tracked.
@property (nonatomic, readonly) NSArray<NSNumber *> *touchRadii;

/// The device that was used to create the signature.
///
/// When signing a document with the default UI, this is set to the last used input method of the created ink signature.
@property (nonatomic, readonly) PSPDFDrawInputMethod inputMethod;

// MARK: Drawing

/// Starts a drawing operation at the given point.
/// The `inputMode` needs to be set to `PSPDFDrawViewInputModeDraw`.
- (void)startDrawingAtPoint:(PSPDFDrawingPoint)location;

/// Continues a drawing operation at with the given points and optional predicted points.
/// The `inputMode` needs to be `PSPDFDrawViewInputModeDraw`.
///
/// @param locations Boxed `PSPDFDrawingPoint` objects.
/// @param predictedLocations Boxed `PSPDFDrawingPoint` objects.
- (void)continueDrawingAtPoints:(NSArray<NSValue *> *)locations predictedPoints:(NSArray<NSValue *> *)predictedLocations;

/// Commits the drawing.
/// The `inputMode` needs to be set to `PSPDFDrawViewInputModeDraw`.
- (void)endDrawing;

/// Cancels the drawing.
/// The `inputMode` needs to be set to `PSPDFDrawViewInputModeDraw`.
- (void)cancelDrawing;

/// Defines how aggressively shapes snap to square aspect ratio. Defaults to 20.
/// Set to zero to disable guides.
@property (nonatomic) CGFloat guideSnapAllowance;

// MARK: Erase

/// Performs an erase at the given locations. Boxed `PSPDFDrawingPoint` objects.
/// The `inputMode` needs to be set to `PSPDFDrawViewInputModeErase`.
- (void)eraseAt:(NSArray<NSValue *> *)locations;

/// Commits the erase operation.
/// The `inputMode` needs to be set to `PSPDFDrawViewInputModeErase`.
- (void)endErase;

/// Cancels the erasing.
/// The `inputMode` needs to be set to `PSPDFDrawViewInputModeErase`.
///
/// @note Discards any erasing performed after the last `endErase` call.
- (void)cancelErase;

@end

NS_ASSUME_NONNULL_END
