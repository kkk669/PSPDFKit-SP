//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFAnnotationStyleManager.h>

NS_ASSUME_NONNULL_BEGIN

/// Model class used to define custom color presets.
///
/// @see `PSPDFStyleManager`
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ColorPreset)
@interface PSPDFColorPreset : PSPDFModel <PSPDFStylePreset>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates a new preset with a `nil` `fillColor` and `alpha` set to 1.
+ (PSPDFColorPreset *)presetWithColor:(nullable UIColor *)color;

/// Creates a new custom preset.
+ (PSPDFColorPreset *)presetWithColor:(nullable UIColor *)color fillColor:(nullable UIColor *)fillColor alpha:(CGFloat)alpha;

/// The primary preset color (the content color).
///
/// @note The color will be standardized to the RGB color space with an alpha value of 1.
@property (nonatomic, readonly, nullable) UIColor *color;

/// The `color` with added `alpha`.
@property (nonatomic, readonly, nullable) UIColor *colorWithAlpha;

/// The secondary preset color (fill color).
///
/// @note The color will be standardized to the RGB color space with an alpha value of 1.
@property (nonatomic, readonly, nullable) UIColor *fillColor;

/// The `fillColor` with added `alpha`.
@property (nonatomic, readonly, nullable) UIColor *fillColorWithAlpha;

/// The preset alpha.
@property (nonatomic, readonly) CGFloat alpha;

@end

NS_ASSUME_NONNULL_END
