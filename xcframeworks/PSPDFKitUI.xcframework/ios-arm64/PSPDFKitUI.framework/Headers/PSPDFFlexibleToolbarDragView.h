//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Toolbar drag & drop indicator view.
PSPDF_CLASS_SWIFT(FlexibleToolbarDragView)
@interface PSPDFFlexibleToolbarDragView : UIView

/// Color used for the circle bar indicators or as the background color in inverted mode.
/// Defaults to `tintColor` in UIKit.
@property (nonatomic) UIColor *barColor;

/// Inverts the bar and background color (can be used to indicate selection).
@property (nonatomic) BOOL inverted;

/// Inverts the bar and background color and optionally fades the transition.
- (void)setInverted:(BOOL)inverted animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
