//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFButton.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFButtonStyle) {
    /// Single color.
    PSPDFButtonStyleFlat,
    /// Uses blur.
    PSPDFButtonStyleModern,
} PSPDF_ENUM_SWIFT(StyleButton.Style);

/// Button that can use a modern (blurred) or flat style.
///
/// You can use UIAppearance to customize the main properties.
/// ```
/// [PSPDFStyleButton appearance].buttonStyle = PSPDFButtonStyleFlat;
/// [PSPDFStyleButton appearance].backgroundColor = [UIColor colorWithWhite:0.1 alpha:0.8];
/// [PSPDFStyleButton appearance].tintColor = UIColor.whiteColor;
/// ```
///
/// @note The background color can be customized by setting the standard `backgroundColor`
/// `UIView` property. If you want to customize the background color, it is recommended
/// that you use `PSPDFLabelStyleFlat`, as using the blur effect with a non-translucent
/// background color might produce unexpected results.
///
/// If you are customizing this view, you might also want to apply similar changes to
/// `PSPDFLabelView`.
PSPDF_CLASS_SWIFT(StyleButton)
@interface PSPDFStyleButton : PSPDFButton

/// Customize the button style. Defaults to `PSPDFButtonStyleModern`.
/// The styles match the `labelStyle` values on `PSPDFLabelView`.
@property (nonatomic) PSPDFButtonStyle buttonStyle UI_APPEARANCE_SELECTOR;

/// Customize the blur effect style used.
/// Defaults to `UIBlurEffectStyleExtraLight`.
///
/// @note Only honored if `buttonStyle` is set to `PSPDFButtonStyleModern`.
@property (nonatomic) UIBlurEffectStyle blurEffectStyle UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END
