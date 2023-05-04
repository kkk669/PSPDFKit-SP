//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (PSPDFCompatible)

/// Creates a dynamic color, given light and dark mode variants.
///
/// @param lightModeColor Color to be used in light mode trait environment.
/// @param darkModeColor Color to be used in dark mode trait environment.
+ (UIColor *)pspdf_dynamicColorForLightMode:(UIColor *)lightModeColor darkMode:(UIColor *)darkModeColor NS_SWIFT_NAME(dynamicColor(lightMode:darkMode:));

/// Creates a dynamic color, given ARGB values of light and dark mode variants.
///
/// @param lightModeValue ARGB value of light mode color variant.
/// @param darkModeValue ARGB value of dark mode color variant.
+ (UIColor *)pspdf_dynamicColorWithARGB32ForLightMode:(int32_t)lightModeValue darkMode:(int32_t)darkModeValue NS_SWIFT_NAME(dynamicColor(ARGB32lightMode:ARGB32darkMode:));

@end

NS_ASSUME_NONNULL_END
