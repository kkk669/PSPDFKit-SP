//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

typedef UIBezierPath *_Nonnull (^PSPDFPathCreationBlock)(CGRect frame);

/// A view that can draw a provided path and optionally animate it.
PSPDF_CLASS_SWIFT(SymbolView)
@interface PSPDFSymbolView : UIView

/// Preset view with a checkmark path.
+ (instancetype)checkMarkSymbolView;

/// Preset view with a X (error) path.
+ (instancetype)xMarkSymbolView;

PSPDF_DEFAULT_VIEW_INIT_UNAVAILABLE

/// Crates a new symbol with the provided path block.
- (instancetype)initWithPathBlock:(PSPDFPathCreationBlock)pathBlock NS_DESIGNATED_INITIALIZER;

/// A block that creates the path for a given rect.
@property (nonatomic, copy, readonly) PSPDFPathCreationBlock pathBlock;

/// The internal shape layer used to draw the path.
///
/// @note Its `strokeColor` is automatically set based on the view `tintColor`.
@property (nonatomic, readonly) CAShapeLayer *shapeLayer;

/// Inset from the view edge to the path symbol. Defaults to 6pt on every side.
@property (nonatomic) UIEdgeInsets pathInsets;

/// If `true`, the view is animated shortly after being inserted to the view hierarchy.
/// Defaults to `true`.
@property (nonatomic) BOOL animateWhenAddingToSuperview;

/// Delay for `animateWhenAddingToSuperview`. Defaults to 0.3.
@property (nonatomic) NSTimeInterval superviewInsertionAnimationDelay;

@end

NS_ASSUME_NONNULL_END
