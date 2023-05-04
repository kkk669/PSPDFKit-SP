//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFShapeTemplate.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAbstractShapeAnnotation, PSPDFPageInfo;

/// Transforms a detected template into an annotation by analyzing the points in raw drawing.
/// This is an abstract class, use `+[PSPDFShapeTemplateTransformer transfomerForTemplate:points:]` to retrieve an instance of a concrete subclass for a given template.
PSPDF_TEST_CLASS_SWIFT(ShapeTemplateTransformer)
@interface PSPDFShapeTemplateTransformer : NSObject<PSPDFOverrideProvider>

/// Initializes a shape template transformer.
///
/// @param shapeTemplateIdentifier The shape template identifier for which the transformer is being initialized.
/// @return An instance of `PSPDFShapeTemplateTransformer`.
///
/// @note This method should only be called by subclasses, and will assert otherwise.
- (instancetype)initWithTemplateIdentifier:(PSPDFShapeTemplateIdentifier)shapeTemplateIdentifier NS_DESIGNATED_INITIALIZER;

/// The template identifier for which the receiver was created.
@property (nonatomic, readonly) PSPDFShapeTemplateIdentifier shapeTemplateIdentifier;

/// Set this if you want to provide custom overrides for annotations that you want the receiver
/// to use when creating the transformed annotation.
@property (nonatomic, weak) id<PSPDFOverrideProvider> overrideDelegate;

/// Transforms the passed in points into an annotation if possible.
///
/// @param points The flattened list of points, in view coordinates, that was used to draw the shape. We pass this in to help performance in case a
/// transformer needs to access a flattened list of all the points in `pointSequences`.
/// @param pointSequences An array of arrays, where the internal arrays each contain the points in a stroke.
/// These points must be the same as `points`, but split into sequences based on the strokes in the gesture.
/// @param bounds The bounds of the view that `points` are created in.
/// @param pageInfo The pageInfo for the page on which the annotation is to be added. Used for setting the annotation's location on the page.
/// @param error A pointer to an error that is set if the transformation fails.
/// @return The annotation created from the input points.
///
/// @note This is an abstract method, and must be overridden in a subclass. In addition it is not be called externally,
/// but will be called by a `PSPDFDrawingSwapper` when required.
- (nullable PSPDFAbstractShapeAnnotation *)annotationByTransformingPoints:(PSPDFCGPointArray *)points pointSequences:(NSArray<PSPDFCGPointArray *> *)pointSequences inBounds:(CGRect)bounds pageInfo:(PSPDFPageInfo *)pageInfo error:(NSError *_Nullable*)error;

@end

NS_ASSUME_NONNULL_END
