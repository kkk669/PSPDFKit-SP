//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDrawView.h>
#import <PSPDFKitUI/PSPDFDrawLayer.h>
#import <PSPDFKitUI/PSPDFAnimatableShapeUpdates.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFRenderRequest.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFMeasurementSnapper.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFEraseOverlay, PSPDFAbstractShapeAnnotation, PSPDFDrawGestureRecognizer;

PSPDF_EXTERN NSNotificationName const PSPDFDrawViewDidChangePointSequencesNotification NS_SWIFT_NAME (DrawViewDidChangePointSequences);

/// Datasource for draw view magnifying glass operations.
PSPDF_PROTOCOL_SWIFT(DrawLayerDataSource)
@protocol PSPDFDrawViewDataSource<NSObject>

@optional

/// Called when the draw view needs a reference view for the magnifying glass loupe. Return `nil` to prevent display of the loupe.
- (nullable UIView *)loupeReferenceViewForDrawView:(PSPDFDrawView *)drawView;

@end

/**
 The class holds an array of `DrawLayer` objects that will
 later be converted into PDF annotations.

 The conversion from draw layers to annotations isn't necessary 1:1.
 Some draw layers can be left out
 (for instance if there are validation errors like too few points for the annotation).
 */
@interface PSPDFDrawView () <PSPDFAnimatableShapeUpdates, PSPDFOverrideProvider>

@property (nonatomic) PSPDFEraseOverlay *circleShape;

/// Defines how the annotation will be rendered.
@property (nonatomic, copy, nullable) PSPDFRenderOptions *renderOptions;

/// Adds draw layers for the passed in annotations.
///
/// @param annotations The annotations for which the draw view should assume responsibility.
/// @param insertOnTop Specifies whether the annotations should be inserted at the top. If `false`, then annotations are inserted at the bottom.
///
/// @return An array of inserted draw layers. Will be empty if no layers are inserted.
- (NSArray<PSPDFDrawLayer *> *)updateForAnnotations:(NSArray<PSPDFAbstractShapeAnnotation *> *)annotations insertNewLayersOnTop:(BOOL)insertOnTop;

/// Hides the draw layers corresponding to the given annotations.
/// When selecting an annotation during drawing (can happen only with stylus) this method allows us to temporarily hide the draw layer.
/// Helps avoid the bug in https://github.com/PSPDFKit/PSPDFKit/issues/21833
///
/// @param annotations The annotations for which the draw layers should be hidden.
- (void)hideDrawLayersForSelectedAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Shows the draw layers corresponding to the given annotations.
/// When deselecting an annotation during drawing (can happen only with stylus) this method allows us to show the draw layers again.
/// Helps avoid the bug in https://github.com/PSPDFKit/PSPDFKit/issues/21833
///
/// @param annotations The annotations for which the draw layers should be shown.
- (void)showDrawLayersForSelectedAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

@property (nonatomic, copy) NSArray<NSNumber /* UITouchType */ *> *allowedTouchTypes;

/// The layer currently being drawn into. Only non-nil in between a touch beginning and ending.
@property (nonatomic, nullable) PSPDFDrawLayer *currentDrawLayer;
@property (nonatomic, copy) NSArray<PSPDFDrawLayer *> *drawLayers;

/// Measurement snapper for measurement annotation drawing.
@property (nonatomic, nullable) PSPDFMeasurementSnapper *measurementSnapper;

/// Used to create a new layer for ink strokes after selecting an annotation during draw mode. (Only relevant for stylus drawing)
/// Helps avoid: https://github.com/PSPDFKit/PSPDFKit/pull/22734#issuecomment-570044020
@property (nonatomic) BOOL canMergeNextStroke;

/// Returns `drawGestureRecognizer` with the actual type used.
@property (nonatomic, readonly) PSPDFDrawGestureRecognizer *internalDrawGestureRecognizer;

/// The `DrawView` datasource which is responsible for providing the content view for magnification.
@property (nonatomic, weak) id<PSPDFDrawViewDataSource> dataSource;

/// Cancels drawing or finishes erasing.
/// TODO: Split cancellation and finishing.
- (void)cancelCurrentInput;

- (BOOL)shouldReceiveTouch:(UITouch *)touch;
- (CGPoint)convertToPDFPointAndConstraintToBounds:(CGPoint)viewPoint;
- (void)eraseAt:(NSArray<NSValue *> *)locations;
- (void)endErase;
- (void)updateDrawLayersForAppearanceModeChange;

- (void)enableAutoScalingWithReferenceWidth:(CGFloat)referenceWidth;

/// Find a draw layer for the given annotation.
- (nullable PSPDFDrawLayer *)drawLayerForAnnotation:(PSPDFAnnotation *)annotation;

@end

NS_ASSUME_NONNULL_END
