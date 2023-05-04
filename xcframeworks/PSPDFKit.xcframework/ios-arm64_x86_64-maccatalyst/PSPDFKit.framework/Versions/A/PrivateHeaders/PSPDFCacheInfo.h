//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFRenderRequest;

/// PSPDFCacheInfo contains all the data that is relevant for uniquely identifying
/// an image in the cache and nothing more. It is designed so that it can be used as
/// a key in a dictionary to quickly look up data; its `isEqual:` and `hash` implementations
/// are optimized for fast lookups.
PSPDF_APP_EXPORT @interface PSPDFCacheInfo : NSObject<NSCopying, NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Reads the relevant data from the request and initializes a new cache info object
///
/// @param request The request to create a cache info from.
/// @param error Error when the cache info can't be determined, because the render request is invalid.
/// @return A newly initialized cache info or `nil` if the request is not eligible for caching.
+ (nullable instancetype)cacheInfoForRequest:(PSPDFRenderRequest *)request error:(NSError **)error;

/// Initializes a cache info with its required values.
///
/// This is the designated initializer.
///
/// @param uid The document's unique identifier.
/// @param pageIndex The page index in the document.
/// @param size The actual size of the rendered image.
/// @param optionsHash A hash that uniquely describes additional options that were used to create the image.
- (instancetype)initWithDocumentUID:(NSString *)uid pageIndex:(PSPDFPageIndex)pageIndex size:(CGSize)size optionsHash:(NSUInteger)optionsHash NS_DESIGNATED_INITIALIZER;

/// The document's uid.
@property (nonatomic, readonly) NSString *uid;

/// The page index in the document.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

/// The actual size of the rendered image in pixels.
@property (nonatomic, readonly) CGSize size;

/// An identifier that uniquely describes additional options that were used to create the image.
@property (nonatomic, readonly) NSUInteger optionsHash;

/// Set to `true` by a cache if the document was evicted from the cache.
///
/// @note You should not set this value yourself from outside a cache implementation.
@property (atomic) BOOL evicted;

/// The cost of the image in the cache.
///
/// Typically this could be the amount of space used on a disk or the number of pixels
/// of the image.
@property (atomic) long long cost;

/// A hash describing the version of the document.
///
/// Defaults to 0.
@property (atomic) NSUInteger documentHash;

@end

NS_ASSUME_NONNULL_END
