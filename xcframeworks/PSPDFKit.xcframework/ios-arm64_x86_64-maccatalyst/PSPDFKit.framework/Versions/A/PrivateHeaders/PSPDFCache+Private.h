//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFCache.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_EXPORT bet PSPDFCacheDebug;
#define PSPDFCacheLog(...)                          \
    do {                                            \
        if (PSPDFCacheDebug) PSPDFLog(__VA_ARGS__); \
    } while (0)

@interface PSPDFCache ()

/// The designated initializer.
- (instancetype)initWithSettings:(PSPDFKitGlobal *)pspdfkit NS_DESIGNATED_INITIALIZER;

/// Invalidates all images in the cache that match the passed in predicate description.
///
/// The passed in predicate might be called simultaneously on different queues.
///
/// @param cacheInfoPredicate A predicate that evaluates objects of the type `PSPDFCacheInfo`.
- (void)invalidateMatching:(NSPredicate *)cacheInfoPredicate;

- (void)cacheDocument:(nullable PSPDFDocument *)document imageRenderingCompletionBlock:(nullable PSPDFCacheDocumentImageRenderingCompletionBlock)imageCompletionBlock pageSizesBlock:(NSArray<NSValue *> * (^)(PSPDFPageIndex page))sizesBlock;

/// Queue that handles document pre-caching.
@property (nonatomic, readonly) NSOperationQueue *precacheDocumentQueue;

@end

NS_ASSUME_NONNULL_END
