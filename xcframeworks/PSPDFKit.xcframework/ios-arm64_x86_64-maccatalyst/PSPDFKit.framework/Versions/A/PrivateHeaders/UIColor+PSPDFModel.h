//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFLocalizedStringKeys.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (PSPDFModel)

// @name Localization

/// Returns the name of the current color, also handles clear and nil colors
///
/// In general, this should be avoided. If you want to describe a specific (hardcoded) color, then also hardcode the
/// most appropriate localized string key. If you want to describe an arbitrary color, use `UIColor.accessibilityName`.
+ (PSPDFLocalizedStringKey)pspdf_closestAnnotationColorNameForColor:(nullable UIColor *)color;

/// Returns name of the current color (compared against an internal database)
///
/// In general, this should be avoided. If you want to describe a specific (hardcoded) color, then also hardcode the
/// most appropriate localized string key. If you want to describe an arbitrary color, use `UIColor.accessibilityName`.
@property (nonatomic, readonly) PSPDFLocalizedStringKey pspdf_closestAnnotationColorName;

// @name Predefined colors

/// "Gray" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_grayColor;

/// "Light gray" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_lightGrayColor;

/// "Dark gray" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_darkGrayColor;

/// "Brown" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_brownColor;

/// "Red" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_redColor;

/// "Dark red" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_darkRedColor;

/// "Orange" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_orangeColor;

/// "Yellow" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_yellowColor;

/// "Green" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_greenColor;

/// "Light green" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_lightGreenColor;

/// "Cyan" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_cyanColor;

/// "Blue" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_blueColor;

/// "Dark blue" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_darkBlueColor;

/// "Purple" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_purpleColor;

/// "Magenta" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_magentaColor;

/// "Pink" color from the unified color palette.
@property (class, nonatomic, readonly) UIColor *pspdf_pinkColor;

@end

NS_ASSUME_NONNULL_END
