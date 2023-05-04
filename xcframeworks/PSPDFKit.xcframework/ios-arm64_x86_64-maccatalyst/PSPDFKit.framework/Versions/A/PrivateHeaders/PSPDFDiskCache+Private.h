//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFCacheStore.h>
#import <PSPDFKit/PSPDFDiskCache.h>

NS_ASSUME_NONNULL_BEGIN

/// HEIF container with HEVC encoding. If unavailable, this will fall back to JPEG.
static PSPDFDiskCacheFileFormat const PSPDFDiskCacheFileFormatHEIC = (PSPDFDiskCacheFileFormat)2;

@class PSPDFCacheInfo, PSPDFCacheMetadata, PSPDFDiskCacheDatabase;

@interface PSPDFDiskCache () <PSPDFCacheStore>

/// Initializes the disk cache with the specified directory and the file format.
///
/// @param cacheDirectory The directory that should be used for this cache, relative to the app's cache directory.
/// @param fileFormat The file format to use for storing images to disk.
/// @param settings The settings used to create the cache.
- (instancetype)initWithCacheDirectory:(NSString *)cacheDirectory fileFormat:(PSPDFDiskCacheFileFormat)fileFormat settings:(PSPDFKitGlobal *)settings NS_DESIGNATED_INITIALIZER;

/// Used for tests. See CacheTests.swift and DiskCacheTests.swift
@property (nonatomic) PSPDFDiskCacheDatabase *database;
@property (nonatomic, readonly) PSPDFCacheMetadata *metadata;
@property (nonatomic, readonly) NSString *fullCacheDirectory;
- (void)bumpLastUsedDateForFile:(NSString *)path;
- (nullable NSDate *)lastUsedDateForFile:(NSString *)path;

- (NSString *)queue_pathForCacheInfo:(PSPDFCacheInfo *)cacheInfo;

@end

NS_ASSUME_NONNULL_END
