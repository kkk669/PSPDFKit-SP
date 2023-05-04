//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFCache.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CacheStore)
@protocol PSPDFCacheStore <NSObject>

/// Requests an image from the cache store.
///
/// The image is returned synchronously. The request's size is treated according to
/// the `imageSizeMatching` parameter.
///
/// @param request The request that describes the image.
/// @param imageSizeMatching The rule how to interprete the request's size.
/// @return An image if there is one in the cache that matches the request or `nil` otherwise.
- (nullable UIImage *)imageForRequest:(PSPDFRenderRequest *)request imageSizeMatching:(PSPDFCacheImageSizeMatching)imageSizeMatching;

/// Saves an image into the cache store.
///
/// @param image The image to store.
/// @param request The request that matches the image.
- (void)saveImage:(UIImage *)image forRequest:(PSPDFRenderRequest *)request;

/// Invalidates all images in the cache, completely emptying it.
- (void)invalidateAll;

/// Invalidates all images in the cache that match the passed in predicate description.
///
/// @param cacheInfoPredicate A predicate that evaluates objects of the type `PSPDFCacheInfo`.
- (void)invalidateMatching:(NSPredicate *)cacheInfoPredicate;

@end

NS_ASSUME_NONNULL_END
