//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDrawView.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFAbstractShapeAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDrawLayer, PSPDFMeasurementSnapper;

/// A delegate that is notified with the changes made to the annotation by the `DrawLayer`.
/// The delegate is responsible for persisting these changes of the annotation to the document.
PSPDF_PROTOCOL_SWIFT(DrawLayerDelegate)
@protocol PSPDFDrawLayerDelegate<NSObject>

/// The draw layer is asking the delegate to add an annotation to the document.
///
/// @param drawLayer The draw layer that's rendering the annotation.
/// @param annotation The annotation that should be added to the document.
- (void)drawLayer:(PSPDFDrawLayer *)drawLayer wantsToAddAnnotation:(PSPDFAnnotation *)annotation;

/// The draw layer is asking the delegate to modify an annotation using the given block.
/// This can be in the form of appending a stroke or erasing.
///
/// @param drawLayer The draw layer that's rendering the annotation.
/// @param annotation The annotation that should be modified.
/// @param scope The block that modifies `annotation`. The delegate is responsible for executing it.
- (void)drawLayer:(PSPDFDrawLayer *)drawLayer wantsToModifyAnnotation:(PSPDFAnnotation *)annotation inScope:(void (^)(void))scope;

/// The draw layer is asking the delegate to delete an annotation from the document.
///
/// @param drawLayer The draw layer that's rendering the annotation.
/// @param annotation The annotation that should be deleted from the document.
- (void)drawLayer:(PSPDFDrawLayer *)drawLayer wantsToDeleteAnnotation:(PSPDFAnnotation *)annotation;

@end

/// `DrawLayer` holds the drawing information for a single shape (Ink, Square, Circle, Polygon, etc.) during
/// annotation creation. Instances of this class contain both the model-level data for new annotation creation (`pointSequences`)
/// as well as the necessary `CALayer` objects used for temporary shape drawing during creation and editing.
///
/// `DrawLayer` class is meant to be used in combination with `DrawView`. You usually don't need to create
/// new instances of this class your own. They will be created for you by `DrawView`.
///
/// Unless otherwise noted, boxed points need to be of type `DrawingPoint`.
PSPDF_CLASS_SWIFT(DrawLayer)
@interface PSPDFDrawLayer : CALayer<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Used for new annotation creation.
- (instancetype)initWithType:(PSPDFAnnotationType)annotationType variant:(nullable PSPDFAnnotationVariantString)annotationVariant NS_DESIGNATED_INITIALIZER;

/// Initializer for existing annotations including the rendering options on how the annotation should be rendered. (e.g. for night mode)
- (instancetype)initWithAnnotation:(PSPDFAbstractShapeAnnotation *)annotation renderOptions:(nullable PSPDFRenderOptions *)renderOptions;

/// Annotation type for this draw layer. Set during initialization.
@property (nonatomic, readonly) PSPDFAnnotationType annotationType;

/// The selected tool variant. Applied to new annotations.
@property (nonatomic, readonly, nullable) PSPDFAnnotationVariantString annotationVariant;

/// Setting this property prepares the data structures and display for drawing or eraser input.
/// `PSPDFDrawViewInputModeErase` only affects Ink annotations.
///
/// @note Set the correct mode before calling drawing or erase methods.
@property (nonatomic) PSPDFDrawViewInputMode inputMode;

/// Reference to the draw view that created this draw action.
@property (nonatomic, weak) PSPDFDrawView *drawView;

/// The `DrawLayer` delegate which should handle updating the Document with the changes made to the annotations.
@property (nonatomic, weak) id<PSPDFDrawLayerDelegate> drawingDelegate;

/// Updates layer content.
- (void)recalculate;

// MARK: Annotation

/// The annotation on which the draw layer is based off. Set during initialization.
/// Important for annotation creation (`PSPDFClassForClass`).
@property (nonatomic, readonly, nullable) PSPDFAbstractShapeAnnotation *annotation;

/// The document provider used for annotation generation.
@property (nonatomic, weak) PSPDFDocumentProvider *documentProvider;

/// The absolute PDF page index of the draw layer.
@property (nonatomic) PSPDFPageIndex pageIndex;

// MARK: Data

/// Point sequences that are in this draw layer. An array of arrays holding `NSValue`s boxing `PSPDFDrawingPoint`s.
///
/// If the owning draw view is attached to a page view then the points are in the coordinate space of the PDF page that the page
/// view is displaying, so the origin is in the bottom-left. Alternatively, if the owning draw view is not attached to a page
/// view then the points are in the coordinate space of the draw view but scaled by `scale`, so the origin is in the top-left.
///
/// Point sequences are `nil` until `endDrawing` is invoked, unless the layer was created using an existing annotation.
@property (nonatomic, copy, readonly, nullable) NSArray<NSArray<NSValue *> *> *pointSequences;

/// Checks if the draw layer data is valid and can be used to create a new annotation
/// (for example if we have the required point count for the selected annotation type).
@property (nonatomic, getter=isValid, readonly) BOOL valid;

// MARK: Rendering

/// Affine transform used to convert `pointSequences` into view coordinates during path rendering.
@property (nonatomic) CGAffineTransform renderTransform;

/// Scale value for the page on which drawing occurs.
/// Used to compute approximate line widths during drawing. Defaults to 1.
@property (nonatomic) CGFloat scale;

// MARK: Sublayers

/// Shape layers used for stroke path rendering.
///
/// For annotation types except ink, there will just be one stroke layer containing all the drawn points.
///
/// For ink annotations, multiple stroke layers may be created to improve rendering performance,
/// and the stroke layers do not include the stroke currently being drawn.
@property (nonatomic, readonly) NSMutableArray<CAShapeLayer *> *strokeLayers;

/// Shape layer used for fill path rendering (if a fill color is selected).
@property (nonatomic, readonly) CAShapeLayer *fillLayer;

// MARK: Drawing

/// Starts the drawing session (point collection and display).
///
/// @param location should be provided in PDF coordinates.
/// @note For polyline and polygon annotations this method can be called several times, before `endDrawing` is called.
- (void)startDrawingAtPoint:(PSPDFDrawingPoint)location;

/// Continues the drawing session at the given coordinates and updates the preview layers.
///
/// @param locations Boxed `PSPDFDrawingPoint` objects. Should be provided in PDF coordinates.
/// @param predictedLocations Boxed `PSPDFDrawingPoint` objects. Should be provided in PDF coordinates. May be empty.
- (void)continueDrawingAtPoints:(NSArray<NSValue *> *)locations predictedPoints:(NSArray<NSValue *> *)predictedLocations;

/// Commits the drawing operation and saves the drawn points into `pointSequences`.
- (void)endDrawing;

/// Discards the latest data and does not update `pointSequences`.
- (void)cancelDrawing;

/// Defines how aggressively shapes snap to square aspect ratio.
/// Set to 0.0 to disable guides (default).
@property (nonatomic) CGFloat guideSnapAllowance;

// MARK: Erase

/// Performs an erase at the given coordinates. A separate `startEraseAtPoint:` method is not needed when erasing.
///
/// @param points The center coordinates for the erase in PDF coordinates, as `NSValue` objects wrapping `PSPDFDrawingPoint`s.
/// @param radiusSqr the squared eraser radius (should be already adjusted for the page / zoom scale)
- (void)eraseAt:(NSArray<NSValue *> *)points withRadius:(CGFloat)radiusSqr;

/// Ends the erase operation and commits the changes to the annotation.
- (void)endErase;

/// Discards the latest erasing and updates the layer to redraw the points.
- (void)cancelErase;

/// Returns YES if erasing changed the layer points.
@property (nonatomic, readonly) BOOL didErase;

// MARK: Styling properties

/// Current stroke color.
@property (nonatomic, nullable) UIColor *strokeColor;

/// Current fill color.
@property (nonatomic, nullable) UIColor *fillColor;

/// Current line width.
@property (nonatomic) CGFloat lineWidth;

/// Natural drawing
@property (nonatomic) BOOL naturalDrawingEnabled;

/// Starting line end type for lines and polylines.
@property (nonatomic) PSPDFLineEndType lineEnd1;

/// Ending line end type for lines and polylines.
@property (nonatomic) PSPDFLineEndType lineEnd2;

/// The stroke dash pattern. Draws a solid line when `nil` (default).
@property (nonatomic, copy, nullable) NSArray<NSNumber *> *dashArray;

/// The border effect style.
@property (nonatomic) PSPDFAnnotationBorderEffect borderEffect;

/// The border effect intensity (if set to cloudy)
@property (nonatomic) CGFloat borderEffectIntensity;

/// Defines a custom blend mode. Supported values include
/// `kCGBlendModeNormal` to `kCGBlendModeExclusion`.
@property (nonatomic) CGBlendMode blendMode;

/// Guide color.
@property (nonatomic, nullable) UIColor *guideBorderColor;

/// Snapper used to snap measurement annotation line points to PDF objects.
@property (nonatomic, nullable) PSPDFMeasurementSnapper *measurementSnapper;

@end

NS_ASSUME_NONNULL_END
