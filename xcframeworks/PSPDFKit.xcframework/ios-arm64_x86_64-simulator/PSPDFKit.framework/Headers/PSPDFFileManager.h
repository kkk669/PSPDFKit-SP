//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
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

@protocol PSPDFDataProviding;

/// Wraps file system calls. Internal class cluster.
/// Can be replaced with Enterprise SDK wrappers like Good Technology or MobileIron AppConnect.
PSPDF_PROTOCOL_SWIFT(FileManagerProtocol)
@protocol PSPDFFileManager<NSObject>

/// If YES, then we can't use certain more optimized methods like `UIGraphicsBeginPDFContextToFile` since they would use write methods that we can't override.
@property (nonatomic, readonly) BOOL usesEncryption;

/// We query the file manager for exceptions where we require unencrypted files on disk.
/// This method expects to return YES for any type if `usesEncryption` returns NO.
/// Various features in PSPDFKit require unencrypted files while usage (Open In, QuickLook, Audio Recording)
- (BOOL)allowsPolicyEvent:(NSString *)policyEvent;

/// Copies a file to an unencrypted location if the security check passes.
- (nullable NSURL *)copyFileToUnencryptedLocationIfRequired:(nullable NSURL *)fileURL policyEvent:(NSString *)policyEvent error:(NSError **)error;

/// Cleans up a temporary file. Searches both in encrypted store (if encrypted) and default disk store.
- (BOOL)cleanupIfTemporaryFile:(NSURL *)url;

/// This method creates a data provider pointing to temporary data storage that is writable.
/// Especially when processing documents, it might be necessary to create temporary files and using this, you can secure the
/// temporary files however you like. By default, this creates a `PSPDFFileDataProvider` pointing to a temporary file.
- (id<PSPDFDataProviding>)createTemporaryWritableDataProviderWithPrefix:(nullable NSString *)prefix;

// MARK: Directories

/// Current user's Library directory path (~/Library).
@property (nonatomic, readonly) NSString *libraryDirectory;

/// Current user's Application Support directory path (~/Library/Application Support).
@property (nonatomic, readonly) NSString *applicationSupportDirectory;

/// Current user's Caches directory path (~/Library/Caches).
@property (nonatomic, readonly) NSString *cachesDirectory;

/// Current user's Documents directory path (~/Documents).
@property (nonatomic, readonly) NSString *documentDirectory;

/// Current user's Caches directory URL (~/Library/Caches).
@property (nonatomic, readonly) NSURL *cachesURL;

/// Current user's Documents directory URL (~/Documents).
@property (nonatomic, readonly) NSURL *documentURL;

/// Creates and returns the path to a new directory in the Temporary directory for the current user with specified UID.
/// This directory may or may not be encrypted.
/// For an unencrypted directory, please see `-[PSPDFFileManager unencryptedTemporaryDirectoryWithUID:]`.
- (NSString *)temporaryDirectoryWithUID:(nullable NSString *)UID;

/// Creates and returns the path to a new unencrypted directory in the Temporary directory for the current user with specified UID.
/// Alternately, please see `-[PSPDFFileManager temporaryDirectoryWithUID:]` for a possibly encrypted directory.
- (nullable NSString *)unencryptedTemporaryDirectoryWithUID:(nullable NSString *)UID;

/// Creates and returns the path to a new directory in the Cache directory (/Library/Caches).
- (NSString *)cacheDirectoryWithPath:(nullable NSString *)path;

/// This method should return `false` for any special paths that represent resources outside
/// of the native device file systems and `true` in all other cases.
///
/// An example of a special path in the context of this method would be a file path
/// managed by MDM software. This check will be used by components such as `PSPDFProcessor`
/// and `PSPDFConversionOperation`. When the method returns `false` for a given path, PSPDFKit
/// will use a file manager operation to write (/ move / copy) the file into the non-native
/// destination. You should make sure that all file manager operations correctly handle those paths.
- (BOOL)isNativePath:(nullable NSString *)path;

// MARK: Existence checks
- (BOOL)fileExistsAtPath:(nullable NSString *)path;
- (BOOL)fileExistsAtPath:(nullable NSString *)path isDirectory:(nullable BOOL *)isDirectory;
- (BOOL)fileExistsAtURL:(nullable NSURL *)url;
- (BOOL)fileExistsAtURL:(nullable NSURL *)url isDirectory:(nullable BOOL *)isDirectory;

// MARK: Creation
- (BOOL)createFileAtPath:(NSString *)path contents:(nullable NSData *)data attributes:(nullable NSDictionary<NSString *, id> *)attributes;
- (BOOL)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(BOOL)createIntermediates attributes:(nullable NSDictionary<NSString *, id> *)attributes error:(NSError **)error;

/* createDirectoryAtURL:withIntermediateDirectories:attributes:error: creates a directory at the specified URL. If you pass 'NO' for withIntermediateDirectories, the directory must not exist at the time this call is made. Passing 'YES' for withIntermediateDirectories will create any necessary intermediate directories. This method returns YES if all directories specified in 'url' were created and attributes were set. Directories are created with attributes specified by the dictionary passed to
 * 'attributes'. If no dictionary is supplied, directories are created according to the umask of the process. This method returns NO if a failure occurs at any stage of the operation. If an error parameter was provided, a presentable NSError will be returned by reference.
 */
- (BOOL)createDirectoryAtURL:(NSURL *)url withIntermediateDirectories:(BOOL)createIntermediates attributes:(nullable NSDictionary<NSString *, id> *)attributes error:(NSError **)error;

// MARK: Writing
- (BOOL)writeData:(NSData *)data toFile:(NSString *)path options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)error;
- (BOOL)writeData:(NSData *)data toURL:(NSURL *)fileURL options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)error;

// MARK:  Reading
- (nullable NSData *)dataWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)error;
- (nullable NSData *)dataWithContentsOfURL:(NSURL *)fileURL options:(NSDataReadingOptions)readOptionsMask error:(NSError **)error;

// MARK:  Copy / Move
- (BOOL)copyItemAtURL:(NSURL *)sourceURL toURL:(NSURL *)destinationURL error:(NSError **)error;
- (BOOL)moveItemAtURL:(NSURL *)sourceURL toURL:(NSURL *)destinationURL error:(NSError **)error;

// MARK:  Replace

/// Replaces the item at the original location with the item at the supplied location.
///
/// @param originalItemURL URL of the item to be replaced.
/// @param newItemURL URL of the item replacing the original item.
/// @param backupItemName Name of the backup item of the original item being replaced.
/// @param options Options to be used while replacing the original item.
/// @param resultingURL Pointer to a URL containing the location of the new item. Can be different than `originalItemURL` in case writing to the original location is not allowed.
/// @param error Pointer to an error object. Set to the error occured while replacing the item.
///
/// @return YES if the replacement was successful or NO if an error occurred.
- (BOOL)replaceItemAtURL:(NSURL *)originalItemURL withItemAtURL:(NSURL *)newItemURL backupItemName:(nullable NSString *)backupItemName options:(NSFileManagerItemReplacementOptions)options resultingItemURL:(NSURL *__nullable *__nullable)resultingURL error:(NSError **)error;

// MARK:  Deletion
- (BOOL)removeItemAtPath:(NSString *)path error:(NSError **)error;
- (BOOL)removeItemAtURL:(NSURL *)url error:(NSError **)error;

// MARK:  File Statistics
- (nullable NSDictionary<NSString *, id> *)attributesOfFileSystemForPath:(NSString *)path error:(NSError **)error;
- (nullable NSDictionary<NSString *, id> *)attributesOfItemAtPath:(nullable NSString *)path error:(NSError **)error;
- (BOOL)isDeletableFileAtPath:(NSString *)path;
- (BOOL)isWritableFileAtPath:(NSString *)path;

// MARK:  Directory Query
- (NSArray<NSString *> *)contentsOfDirectoryAtPath:(NSString *)path error:(NSError **)error;
- (NSArray<NSString *> *)subpathsOfDirectoryAtPath:(NSString *)path error:(NSError **)error;

// MARK:  Misc
- (NSDirectoryEnumerator<NSString *> *)enumeratorAtPath:(NSString *)path;
- (NSDirectoryEnumerator<NSURL *> *)enumeratorAtURL:(NSURL *)url includingPropertiesForKeys:(NSArray<NSString *> *)keys options:(NSDirectoryEnumerationOptions)mask errorHandler:(nullable BOOL (^)(NSURL *url, NSError *error))handler;
- (NSString *)destinationOfSymbolicLinkAtPath:(NSString *)path error:(NSError **)error;

/// Returns the absolute path as C string.
- (const char *)fileSystemRepresentationForPath:(NSString *)path NS_RETURNS_INNER_POINTER;

// MARK:  NSFileHandle

- (BOOL)fileHandleForReadingFromURL:(NSURL *)url error:(NSError **)error withBlock:(BOOL (^)(NSFileHandle *))reader;

@required

// MARK: iCloud

/* Changes whether the item for the specified URL is ubiquitous and moves the item to the destination URL. When making an item ubiquitous, the destination URL must be prefixed with a URL from -URLForUbiquityContainerIdentifier:. Returns YES if the change is successful, NO otherwise.
 */
- (BOOL)setUbiquitous:(BOOL)flag itemAtURL:(NSURL *)url destinationURL:(NSURL *)destinationURL error:(NSError **)error;

/* Returns YES if the item for the specified URL is ubiquitous, NO otherwise.
 */
- (BOOL)isUbiquitousItemAtURL:(NSURL *)url;

/* Start downloading a local instance of the specified ubiquitous item, if necessary. Returns YES if the download started successfully or wasn't necessary, NO otherwise.
 */
- (BOOL)startDownloadingUbiquitousItemAtURL:(NSURL *)url error:(NSError **)error;

/* Removes the local instance of the ubiquitous item at the given URL. Returns YES if removal was successful, NO otherwise.
 */
- (BOOL)evictUbiquitousItemAtURL:(NSURL *)url error:(NSError **)error;

/* Returns a file URL for the root of the ubiquity container directory corresponding to the supplied container ID. Returns nil if the mobile container does not exist or could not be determined.
 */
- (nullable NSURL *)URLForUbiquityContainerIdentifier:(nullable NSString *)containerIdentifier;

/* Returns a URL that can be shared with other users to allow them download a copy of the specified ubiquitous item. Also returns the date after which the item will no longer be accessible at the returned URL. The URL must be prefixed with a URL from -URLForUbiquityContainerIdentifier:.
 */
- (nullable NSURL *)URLForPublishingUbiquitousItemAtURL:(NSURL *)url expirationDate:(NSDate *_Nullable *_Nullable)outDate error:(NSError **)error;

/* Returns an opaque token that represents the current ubiquity identity. This object can be copied, encoded, or compared with isEqual:. When ubiquity containers are unavailable because the user has disabled them, or when the user is simply not logged in, this method will return nil. The NSUbiquityIdentityDidChangeNotification notification is posted after this value changes.

 If you don't need the container URL and just want to check if ubiquity containers are available you should use this method instead of checking -URLForUbiquityContainerIdentifier:.
 */
@property (nullable, readonly, copy) id<NSObject, NSCopying, NSCoding> ubiquityIdentityToken;

/// If the file manager is coordinated, this will temporarily disable coordination for more control.
- (void)performBlockWithoutCoordination:(void (^)(void))block;

@end

typedef NSString *PSPDFFileManagerOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(DefaultFileManager.Option);

/// Specifies whether the file manager should use file coordination when performing operations. Expects a boolean NSNumber.
PSPDF_EXPORT PSPDFFileManagerOption const PSPDFFileManagerOptionCoordinatedAccess;

/// The optional `NSFilePresenter` object to pass to the internally created `NSFileCoordinator` when performing coordinated operations. 
/// See the `NSFileCoordinator` documentation for details. This is only relevant when `PSPDFFileManagerOptionCoordinatedAccess` is enabled. 
PSPDF_EXPORT PSPDFFileManagerOption const PSPDFFileManagerOptionFilePresenter;

/// The default file manager implementation is a thin wrapper around NSFileManager.
PSPDF_CLASS_SWIFT(DefaultFileManager)
@interface PSPDFDefaultFileManager : NSObject<PSPDFFileManager>

- (instancetype)initWithOptions:(nullable NSDictionary<PSPDFFileManagerOption, id> *)options NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
