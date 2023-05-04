//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFEraseOverlay;

/// Specifies how the eraser overlay should look and behave.
PSPDF_PROTOCOL_SWIFT(EraseOverlayDataSource)
@protocol PSPDFEraseOverlayDataSource<NSObject>

/// The current zoom scale, for sharp rendering while zoomed in
- (CGFloat)zoomScaleForEraseOverlay:(PSPDFEraseOverlay *)overlay;

@end

/// Draws a circle shape representing the user touch during erasing.
PSPDF_CLASS_SWIFT(EraseOverlay)
@interface PSPDFEraseOverlay : UIView<PSPDFOverridable>

/// Defines if circle is visible. Defaults to YES.
@property (nonatomic) BOOL circleVisible UI_APPEARANCE_SELECTOR;

/// Defines the circle line width. Defaults to 3.
@property (nonatomic) CGFloat circleLineWidth UI_APPEARANCE_SELECTOR;

/// Defines the circle radius. Defaults to 25.
@property (nonatomic) CGFloat circleRadius UI_APPEARANCE_SELECTOR;

/// Defines the circle color. Defaults to black.
@property (nonatomic) UIColor *circleColor UI_APPEARANCE_SELECTOR;

/// The internal shape layer (matches self.layer)
@property (nonatomic, readonly) CAShapeLayer *shapeLayer;

/// Indicated touch position.
@property (nonatomic) CGPoint touchPosition;

/// Set to `true` before starting sending `touchPosition` updates and set back to `false` afterwards.
@property (nonatomic) BOOL tracking;

/// Enabled or disables tracking and optionally animates the overlay in or out (animating the line width)
- (void)setTracking:(BOOL)tracking animated:(BOOL)animated;

/// Data source (zoom support)
@property (nonatomic, weak) id<PSPDFEraseOverlayDataSource> dataSource;

@end

NS_ASSUME_NONNULL_END
