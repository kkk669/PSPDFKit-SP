//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, PDFCCacheOptions) {
    /// No option.
    PDFCCacheOptionsNone              = 0,
    
    /// Specifies that the file can be moved instead of copied.
    PDFCCacheOptionsMoveFile          = 1 << 0,
};

/// A disk cache implementation.
/// Overridden visibility for the PSPDFKit App.
__attribute__((visibility("default"))) @interface PDFCFilesCache : NSObject

/// Initializes the cache with the given directoryURL, maxCacheSize and version.
/// maxCacheSize specifies the maximum size of the cache in bytes.
/// version specifies the version of the cache. F.e. you can increase this number on every app release and the cache gets purged if the version changes, to prevent bugged cached data to persist.
- (nullable instancetype)initWithDirectoryURL:(NSURL *)directoryURL maxCacheSize:(uint64_t)maxCacheSize version:(int)version error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/// The current cache size.
@property (nonatomic, readonly) uint64_t currentCacheSize;

/// The maximum cache size. When you set it, the cache will try to conform to the size and it might take a while.
@property (nonatomic) uint64_t maxCacheSize;

/// Puts a file into the cache. This method blocks until the file is saved.
- (BOOL)setFileURL:(NSURL *)fileURL forKey:(NSString *)key options:(PDFCCacheOptions)options error:(NSError *__autoreleasing *)error;

/// Gets the file URL for the given key.
- (nullable NSURL *)filePathForKey:(NSString *)key error:(NSError *__autoreleasing *)error;

/// Deletes the file for the specified key. Waits until done.
- (BOOL)removeFileForKey:(NSString *)key error:(NSError *__autoreleasing *)error;

/// Checks if the cache has a file for the specified key.
- (BOOL)hasFileForKey:(NSString *)key;

/// Clears the cache and all the files.
- (void)clear;

@end

NS_ASSUME_NONNULL_END
