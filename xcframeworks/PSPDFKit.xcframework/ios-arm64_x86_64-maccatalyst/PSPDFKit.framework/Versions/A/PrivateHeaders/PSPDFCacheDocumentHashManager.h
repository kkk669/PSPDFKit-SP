//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFCacheDocumentHashManager;
@protocol PSPDFCacheDocumentHashManagerDelegate <NSObject>

/// Called when the cache manager updated the cache infos of its associated metadata
/// store.
///
/// Guaranteed to be called on the metadata queue in a barrier block.
///
/// @param manager The manager that updated cache infos.
- (void)cacheDocumentHashManagerDidUpdateCacheInfo:(PSPDFCacheDocumentHashManager *)manager;

@end

@class PSPDFCacheMetadata;

/// The cache hash manager is used to update the documentHash entries of all cache
/// infos that are stored by a particular instance of `PSPDFCacheMetadata`. It listens
/// for changes in document hashes and updates all entries in the cache accordingly.
/// It also ensures that on loading cache entries that don't have matching document
/// hashes will be purged.
NS_SWIFT_NAME(PDFCacheDocumentHashManager)
@interface PSPDFCacheDocumentHashManager : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new document hash manager with the given metadata object.
///
/// @param metadata The metadata object of the cache that owns the receiver after initialization.
- (instancetype)initWithMetadata:(PSPDFCacheMetadata *)metadata NS_DESIGNATED_INITIALIZER;

/// The delegate of the cash hash manager that is used to notify about updates in cache
/// infos.
@property (nonatomic, weak) id<PSPDFCacheDocumentHashManagerDelegate> delegate;

@end
