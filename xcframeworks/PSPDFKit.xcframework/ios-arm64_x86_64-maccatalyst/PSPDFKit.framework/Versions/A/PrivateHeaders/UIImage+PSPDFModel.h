//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (PSPDFModel)

/// Load images via path, looking automatically for a @2x/@3x option.
+ (nullable UIImage *)pspdf_imageWithContentsOfResolutionDependentFile:(NSString *)path NS_SWIFT_NAME(image(contentsOfResolutionDependentFile:));

/// Tint the receiver, using it's alpha channel as a mask.
///
/// @param color The color used for tinting. Returns the receiver if `color` is `nil`.
/// @param fraction If > 0, then the destination image is drawn on top using `kCGBlendModeSourceAtop`
/// with the alpha set to fraction. Useful to preserve image details.
- (UIImage *)pspdf_imageTintedWithColor:(nullable UIColor *)color fraction:(CGFloat)fraction NS_SWIFT_NAME(imageTinted(color:fraction:));

/// Tint the receiver, using it's alpha channel as a mask.
///
/// @param color The color used for tinting. Returns the receiver if `color` is `nil`.
/// @param fraction If > 0, then the destination image is drawn on top using `kCGBlendModeSourceAtop`
/// with the alpha set to fraction. Useful to preserve image details.
/// @param prerender If `true` the image content will immediately be calculated instead of possibly deferring it to render time. Don't use this for symbol images.
- (UIImage *)pspdf_imageTintedWithColor:(nullable UIColor *)color fraction:(CGFloat)fraction prerender:(BOOL)prerender NS_SWIFT_NAME(imageTinted(color:fraction:prerender:));

/// Loads the image from the given URL using ImageIO.
///
/// @param loadDownscaled Whether a downscaled version of the image should be loaded. Downscaling limits to 2000 pixels.
+ (nullable UIImage *)pspdf_imageFromURL:(NSURL *)url loadDownscaled:(BOOL)loadDownscaled NS_SWIFT_NAME(image(URL:loadDownscaled:));

@end

NS_ASSUME_NONNULL_END
