//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFDatabaseQueue.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFDatabaseQueue.h"
#endif

@class PSPDFDatabaseManager;
@protocol PSPDFFileManager;
@protocol PSPDFDatabaseEncryptionProvider;

NS_ASSUME_NONNULL_BEGIN
NS_SWIFT_NAME(DatabaseManager.Delegate)
@protocol PSPDFDatabaseManagerDelegate <NSObject>

/// Create tables
- (void)databaseManager:(PSPDFDatabaseManager *)databaseManager createTablesInDatabase:(PSPDFDatabase *)db;

/// Destroy tables
- (void)databaseManager:(PSPDFDatabaseManager *)databaseManager destroyTablesInDatabase:(PSPDFDatabase *)db;

@optional

/// Model version/migration
- (NSUInteger)modelVersionForDatabaseManager:(PSPDFDatabaseManager *)databaseManager;

/// Return YES to handle the migration yourself
- (BOOL)databaseManager:(PSPDFDatabaseManager *)databaseManager shouldMigrateDatabase:(PSPDFDatabase *)database withVersion:(NSUInteger)databaseVersion;

/// Returns the comment that will be written into the migration table of the database manager.
- (NSString *)commentForMigrationForDatabaseManager:(PSPDFDatabaseManager *)databaseManager;

@end

/// Possible states that a database manager instance can be in.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFDatabaseStatus) {
    /// Tables not yet created.
    PSPDFDatabaseStatusUnknown,
    /// Old format.
    PSPDFDatabaseStatusRequiresMigration,
    /// Format is newer than internal definition.
    PSPDFDatabaseStatusFormatTooNew,
    /// Everything's good.
    PSPDFDatabaseStatusReady
} NS_SWIFT_NAME(DatabaseManager.Status);

/// The database manager is a simple management layer on top of FMDB to help with common tasks.
/// Subclass to add your own tasks.
PSPDF_APP_CLASS_SWIFT(DatabaseManager)
@interface PSPDFDatabaseManager : PSPDFDatabaseQueue

// Initialize with path.
- (instancetype)initWithPath:(NSString *)path PSPDF_UNAVAILABLE("Use initWithPath:fileManager:delegate:encryptionKey: instead.");
- (instancetype)initWithPath:(NSString *)path fileManager:(id<PSPDFFileManager>)fileManager delegate:(id<PSPDFDatabaseManagerDelegate>)delegate encryptionKey:(nullable NSData *)key databaseEncryptionProvider:(nullable id<PSPDFDatabaseEncryptionProvider>)databaseEncryptionProvider;

// Throw away current database and create a new one.
// @note This does not delete the database file.
- (void)destroyAndRecreateDatabase;

// Delete current database and create a new one.
- (BOOL)deleteAndRecreateDatabaseWithError:(NSError **)error;

// Deletes the database file.
- (BOOL)deleteDatabaseWithError:(NSError **)error;

// Queries the database status.
@property (atomic, readonly) PSPDFDatabaseStatus databaseStatus;

// Delegate.
@property (nonatomic, weak, readonly) id <PSPDFDatabaseManagerDelegate> delegate;

@end
NS_ASSUME_NONNULL_END
