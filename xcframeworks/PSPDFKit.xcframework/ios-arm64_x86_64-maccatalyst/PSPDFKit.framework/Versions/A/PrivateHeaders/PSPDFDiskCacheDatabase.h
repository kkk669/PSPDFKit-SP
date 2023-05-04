//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFDatabaseManager.h>

#ifdef __cplusplus
#include <list>
#endif

NS_ASSUME_NONNULL_BEGIN

PSPDF_EXTERN NSString *const PSPDFDiskCacheDatabaseDidSaveInfo;

@class PSPDFCacheInfo;
@protocol PSPDFFileManager;

@interface PSPDFDiskCacheDatabase : NSObject <PSPDFDatabaseManagerDelegate>

PSPDF_EMPTY_INIT_UNAVAILABLE

- (instancetype)initWithDatabaseDirectory:(NSString *)path fileManager:(id<PSPDFFileManager>)fileManager NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) NSString *databaseFileName;
@property (nonatomic, readonly) NSString *databaseDirectoryPath;
@property (nonatomic, readonly) NSString *databaseFilePath;

#ifdef __cplusplus
@property (nonatomic, readonly) std::list<PSPDFCacheInfo *> loadLRUList;
#endif

- (void)saveCachedObjects:(NSSet<PSPDFCacheInfo *> *)cachedObjects;
- (void)clearDatabase;

// Used as convenience helper to bridge the C++ list. Used in CacheTests.swift.
@property (nonatomic, readonly) NSArray<PSPDFCacheInfo *> *lruArray;

@end

NS_ASSUME_NONNULL_END
