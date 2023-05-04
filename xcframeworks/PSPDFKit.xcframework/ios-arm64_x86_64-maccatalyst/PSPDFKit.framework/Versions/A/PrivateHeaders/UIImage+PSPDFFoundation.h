//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// The maximum area (width x height) that an image might have to be preloaded by default.
PSPDF_SDK_EXPORT const CGFloat PSPDFImagePreloadThresholdArea NS_SWIFT_NAME(PDFImagePreloadThresholdArea);

/// Converts the given CGImagePropertyOrientation to its corresponding UIImageOrientation value.
PSPDF_SDK_EXPORT UIImageOrientation PSPDFUIImageOrientationForCGImagePropertyOrientation(CGImagePropertyOrientation cgImageOrientation) NS_SWIFT_NAME(UIImageOrientation(_:));

/// Converts the given UIImageOrientation to its corresponding CGImagePropertyOrientation value.
PSPDF_SDK_EXPORT CGImagePropertyOrientation PSPDFCGImagePropertyOrientationForUIImageOrientation(UIImageOrientation uiImageOrientation) NS_SWIFT_NAME(CGImagePropertyOrientation(_:));

@interface UIImage (PSPDFFoundation)

/// Check if there are transparent parts in the image.
- (BOOL)pspdf_hasAlpha NS_SWIFT_NAME(hasAlpha());

/// Returns a copy of this image that is cropped to the given bounds.
/// The bounds will be adjusted using CGRectIntegral.
/// This method does not ignore the image's imageOrientation setting.
- (UIImage *)pspdf_croppedImage:(CGRect)bounds NS_SWIFT_NAME(cropped(toBounds:));

/// Returns a new image that is resize to bounds.
/// Supported content modes: `UIViewContentModeScaleAspectFill`, `UIViewContentModeScaleAspectFit`, `UIViewContentModeScaleToFill`.
/// if `honorScaleFactor` is set to NO, resulting image will not be retina scaled.
- (UIImage *)pspdf_imageResizedToSize:(CGSize)size usingContentMode:(UIViewContentMode)contentMode interpolationQuality:(CGInterpolationQuality)quality honorScaleFactor:(BOOL)honorScaleFactor NS_SWIFT_NAME(resized(to:contentMode:interpolationQuality:honorScaleFactor:));

/// Returns a new image rotated to fix its orientation.
///
/// @note Returns the same image if the orientation is already upright.
@property (nonatomic, readonly) UIImage *pspdf_imageWithUprightOrientation NS_SWIFT_NAME(uprightOrientation);

/// Returns a transform for a resized upright orientation image considering the current image orientation.
+ (CGAffineTransform)pspdf_transformForOrientation:(UIImageOrientation)currentOrientation newSize:(CGSize)newSize NS_SWIFT_NAME(transform(forOrientation:newSize:));

/// Returns a transform performing operations on initial transform supplied for a resized image with upright orientation.
+ (CGAffineTransform)pspdf_transformForOrientation:(UIImageOrientation)currentOrientation newSize:(CGSize)newSize transform:(CGAffineTransform)initialTransform NS_SWIFT_NAME(transform(forOrientation:newSize:initialTransform:));

/// Returns whether the image drawing for the given orientation should be transposed or not.
+ (BOOL)pspdf_shouldDrawTransposedForOrientation:(UIImageOrientation)imageOrientation NS_SWIFT_NAME(shouldDrawTransposed(_:));

/// Returns an image resized for use as a landscapePhone image with toolbar button items.
@property (nonatomic, readonly) UIImage *pspdf_landcapePhoneResizedImage NS_SWIFT_NAME(landcapePhoneResized);

/// Decompresses the current image.
- (void)pspdf_preloadImage NS_SWIFT_NAME(preload());

/// Redraws the image into an argb context. In case of an error, this returns the receiver.
@property (nonatomic, readonly) UIImage *pspdf_argbImage NS_SWIFT_NAME(argb);

/// Returns a size in points that fits the image into the given constraints by scaling it with
/// respect to content ratio while ensuring that the entire image is visible.
- (CGSize)pspdf_sizeThatFits:(CGSize)constraints NS_SWIFT_NAME(sizeThatFits(_:));

/// Allows you to assign the underlying, compressed image data to an image.
/// This is necessary because it is impossible to extract that without decompressing
/// the image first.
@property (nonatomic, nullable) NSData *pspdf_imageData NS_SWIFT_NAME(data);

#if !TARGET_OS_OSX
/// Same as scale, but there for macOS compatibility.
@property (nonatomic, readonly) CGFloat pspdf_scale;
#endif

/// For image stamps, Adobe sets a name that begins with a "#" and resembles a MD5 hash of the image data.
/// If we don't do this, the image stamp annotation could lose its appearance when it's rotated
/// by Adobe Acrobat. See https://github.com/PSPDFKit/PSPDFKit/issues/20165
///
/// This property returns a "Name" for an image stamp annotation.
@property (nonatomic, readonly) NSString *pspdf_imageStampName NS_SWIFT_NAME(stampName);

@end

NS_ASSUME_NONNULL_END
