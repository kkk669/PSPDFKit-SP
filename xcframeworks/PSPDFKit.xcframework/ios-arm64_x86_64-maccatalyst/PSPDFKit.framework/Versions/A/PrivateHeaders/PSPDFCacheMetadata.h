//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFCache.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFCacheInfo;

/// `PDFCacheMetadata` is used by the cache stores as the in memory representation
/// of the cache metadata. It does not contain the data (the image) itself as this
/// is stored in different locations depending on the type of the store; this class
/// keeps track of the metadata and therefore of what is part of the cache and what
/// is not. Think of it as a list of `PSPDFCacheInfo` objects.
///
/// The cache metadata class is very tightly coupled with the stores. It is not thread
/// safe and is meant to be used in a concurrent read / single write environment. Its
/// method names inform you about the kind of lock required to call a method. It even
/// provides you with the `accessQueue` to use, however locking itself needs to be
/// done by the caller; this is implemented in this way because usually the caller
/// needs to do their own bookkeeping of the data linked to an entry in the metadata
/// class and changes on the data and the metadata usually need to be atomic.
///
/// Methods starting with a `queue_` should be called on a single queue but can be
/// called concurrently on that queue. Methods starting with `barrier_` on the other
/// hand have to be called from a barrier block and require serial execution.
NS_SWIFT_NAME(PDFCacheMetadata)
@interface PSPDFCacheMetadata : NSObject

@property (nonatomic, readonly) dispatch_queue_t accessQueue;
@property (nonatomic, readonly) NSHashTable<PSPDFCacheInfo *> *queue_dirtyCacheInfos;

- (instancetype)initWithIdentifier:(NSString *)identifier NS_DESIGNATED_INITIALIZER;

// Cost
@property (nonatomic, readonly) long long queue_cost;
- (void)barrier_reduceCostTo:(long long)allowedCost markDirty:(BOOL)dirty cleanupHandler:(nullable void (^)(PSPDFCacheInfo *info))cleanupHandler;

// Set access
@property (nonatomic, readonly) NSUInteger queue_count;
- (void)queue_enumerateObjectsUsingBlock:(void (^)(PSPDFCacheInfo *info, BOOL *stop))block;
- (BOOL)queue_containsObject:(PSPDFCacheInfo *)cacheInfo;

/// @return Returns a cache info that matches the request and sizing options, or nil if no matching object was found.
- (nullable PSPDFCacheInfo *)queue_cacheInfoForRequest:(PSPDFRenderRequest *)request imageSizeMatching:(PSPDFCacheImageSizeMatching)imageSizeMatching;

/// @note The cache info is copied once when necessary.
- (void)barrier_addCacheInfo:(PSPDFCacheInfo *)info markDirty:(BOOL)dirty;
- (void)barrier_removeCacheInfo:(PSPDFCacheInfo *)info markDirty:(BOOL)dirty;
- (void)barrier_clearCache;

@end

NS_ASSUME_NONNULL_END
