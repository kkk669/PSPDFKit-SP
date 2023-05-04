//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFLibrary, PSPDFLibraryPreviewResult, PSPDFTextParser;

/// The library version.
PSPDF_EXPORT const NSUInteger PSPDFLibraryVersion;

// MARK: - Notifications

/// Posted when the library begins indexing a document.
///
/// The `object` of this notification will be the `PDFLibrary` instance that posts it. The UID of the document about to be
/// indexed can be found in the `userInfo` under `PSPDFLibraryNotificationUIDKey`.
PSPDF_EXPORT NSNotificationName const PSPDFLibraryWillStartIndexingDocumentNotification;

/// Posted when the library completed or failed indexing a document.
///
/// The `object` of this notification will be the `PDFLibrary` instance that posts it. The UID of the indexed document can
/// be found in the `userInfo` under `PSPDFLibraryNotificationUIDKey`, while `PSPDFLibraryNotificationSuccessKey` holds a
/// `Bool`, indicting whether indexing completed successfully.
PSPDF_EXPORT NSNotificationName const PSPDFLibraryDidFinishIndexingDocumentNotification;

/// Posted when the library removed a document from the index.
///
/// The `object` of this notification will be the `PDFLibrary` instance that posts it. The UID of the indexed document can
/// be found in the `userInfo` under `PSPDFLibraryNotificationUIDKey`.
PSPDF_EXPORT NSNotificationName const PSPDFLibraryDidRemoveDocumentNotification;

/// Posted when the library did complete clearing all its indexes.
///
/// The `object` of this notification will be the `PDFLibrary` on which `clearAllIndexes()` has been called. No `userInfo`
/// will be provided.
PSPDF_EXPORT NSNotificationName const PSPDFLibraryDidClearIndexesNotification;

/// In document-specific notifications posted by `PDFLibrary`, the `userInfo` key under which the UID of that document can
/// be found.
PSPDF_EXPORT NSString *const PSPDFLibraryNotificationUIDKey;

/// In `PSPDFLibraryDidFinishIndexingDocumentNotification`, the `userInfo` key holding the success state of the operation
/// as a `Bool`.
PSPDF_EXPORT NSString *const PSPDFLibraryNotificationSuccessKey;

// MARK: - Other Constants

/// The name of the exception thrown when an invalid operation occurs.
PSPDF_EXPORT NSExceptionName const PSPDFLibraryInvalidOperationException;

/// The name of PSPDFKit's custom porter tokenizer.
PSPDF_EXPORT NSString *const PSPDFLibraryPorterTokenizerName;

/// The name of PSPDFKit's custom Unicode tokenizer. This tokenizer wraps around SQLite's `unicode61` tokenizer to
/// add full case folding to the indexed text.
///
/// @warning This tokenizer is only available when the library supports FTS5. Specifying this as the value
/// for the `PSPDFLibrary.tokenizer` property will result in an error when trying to create the library.
PSPDF_EXPORT NSString *const PSPDFLibraryUnicodeTokenizerName NS_SWIFT_NAME(PDFLibrary.UnicodeTokenizerName);

/// Represents the status of a document in the library.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFLibraryIndexStatus) {
    /// Not in library.
    PSPDFLibraryIndexStatusUnknown,
    /// The document is queued for indexing.
    PSPDFLibraryIndexStatusQueued,
    /// The document has been partially indexed.
    PSPDFLibraryIndexStatusPartial,
    /// The document has been partially indexed, and is currently being indexed.
    PSPDFLibraryIndexStatusPartialAndIndexing,
    /// The document is indexed.
    PSPDFLibraryIndexStatusFinished,
} PSPDF_ENUM_SWIFT(PDFLibrary.IndexStatus);

/// Specifies the version of FTS the PSPDFLibrary should use.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFLibraryFTSVersion) {
    /// The library will use the highest version of FTS available
    PSPDFLibraryFTSVersionHighestAvailable,
    /// The library will use FTS 4
    PSPDFLibraryFTSVersion4,
    /// The library will use FTS 5
    PSPDFLibraryFTSVersion5
} PSPDF_ENUM_SWIFT(PDFLibrary.FTSVersion);

/// Specifies the priority indexing takes in task scheduling.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFLibraryIndexingPriority) {
    /// Specifies that the indexing must be done on a background priority queue.
    PSPDFLibraryIndexingPriorityBackground,
    /// Specifies that indexing must be done on a low priority queue.
    PSPDFLibraryIndexingPriorityLow,
    /// Specifies that indexing must be done on a high priority queue.
    PSPDFLibraryIndexingPriorityHigh
} PSPDF_ENUM_SWIFT(PDFLibrary.IndexingPriority);

/// Specifies what data is to be indexed to Spotlight.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFLibrarySpotlightIndexingType) {
    /// Spotlight is completely disabled.
    PSPDFLibrarySpotlightIndexingDisabled = 0,
    /// Only document metadata will be indexed in spotlight.
    PSPDFLibrarySpotlightIndexingEnabled = 1,
    /// The entire document will be indexed, including its text.
    PSPDFLibrarySpotlightIndexingEnabledWithFullText = 2
} PSPDF_ENUM_SWIFT(PDFLibrary.SpotlightIndexingType);

@protocol PSPDFLibraryDataSource;

/// `PSPDFLibrary` implements a sqlite-based full-text-search engine.
/// You set a data source that provides the documents to be indexed by the library, and then call -updateIndex, which performs its work asynchronously.
/// Then, you can search for keywords within that collection. Typically, you use a `PSPDFLibraryFileSystemDataSource`.
/// There can be multiple libraries, although usually one is enough for the common use case.
/// Furthermore, when using multiple libraries with spotlight indexing enabled could lead to duplicates in users' spotlight results.
/// See https://pspdfkit.com/guides/ios/features/indexed-full-text-search/ for further documentation.
///
/// @note Requires the `Features.indexedFTS` feature flag.
PSPDF_CLASS_SWIFT(PDFLibrary)
@interface PSPDFLibrary : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

// MARK: Initialization

/// If no library for the given path exists yet, this method will create and return one. All subsequent calls
/// will return the same instance. Hence there will only be one instance per path.
/// This method will return nil for invalid paths.
///
/// @param path The path for which the library is to be retrieved or created if it does not exist already.
/// @param error A pointer to an error that will be set if the library could not be retrieved or created
/// @return A library for the specified path
///
/// @note If a library is created, it will be with the default tokenizer and the highest version of FTS available.
+ (nullable instancetype)libraryWithPath:(NSString *)path error:(NSError **)error;

/// If no library for the given path exists yet, this method will create and return one. All subsequent calls
/// will return the same instance. Hence there will only be one instance per path.
/// This method will return nil for invalid paths.
///
/// @param path The path for which the library is to be retrieved or created if it does not exist already.
/// @param tokenizer See `PSPDFLibrary.tokenizer`
/// @param error A pointer to an error that will be set if the library could not be retrieved or created.
/// @return A library for the specified path.
+ (nullable instancetype)libraryWithPath:(NSString *)path tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

/// If no library for the given path exists yet, this method will create and return one. All subsequent calls
/// will return the same instance. Hence there will only be one instance per path.
/// This method will return nil for invalid paths.
///
/// @param path The path for which the library is to be retrieved or created if it does not exist already.
/// @param tokenizer See `PSPDFLibrary.tokenizer`
/// @param ftsVersion The version of FTS this library is to use. If the specified version is unavailable, the library will not be created.
/// @param error A pointer to an error that will be set if the library could not be retrieved or created.
/// @return A library for the specified path.
+ (nullable instancetype)libraryWithPath:(NSString *)path ftsVersion:(PSPDFLibraryFTSVersion)ftsVersion tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

/// If no library for the given path exists yet, this method will create and return one. All subsequent calls
/// will return the same instance. Hence there will only be one instance per path.
/// This method will return nil for invalid paths.
///
/// @param path The path for which the library is to be retrieved or created if it does not exist already.
/// @param priority The priority of the internal queue to be used for indexing.
/// @param ftsVersion The version of FTS this library is to use. If the specified version is unavailable, the library will not be created.
/// @param tokenizer See `PSPDFLibrary.tokenizer`
/// @param error A pointer to an error that will be set if the library could not be retrieved or created.
/// @return A library for the specified path.
+ (nullable instancetype)libraryWithPath:(NSString *)path indexingPriority:(PSPDFLibraryIndexingPriority)priority ftsVersion:(PSPDFLibraryFTSVersion)ftsVersion tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

// MARK: Properties

/// Returns the default path of the library used in `PSPDFKitGlobal.sharedInstance.library`.
+ (NSString *)defaultLibraryPath;

/// Path to the current database.
@property (nonatomic, copy, readonly) NSString *path;

/// Specifies whether the documents should also be indexed to Spotlight.
/// If Spotlight indexing is not supported on the device, that is, `+[CSSearchableIndex isIndexingAvailable]` returns NO, then this property is ignored.
/// Defaults to `PSPDFLibrarySpotlightIndexingTypeDisabled`.
@property (atomic) PSPDFLibrarySpotlightIndexingType spotlightIndexingType;

/// Specifies whether the contents of annotations in documents added to the library should be indexed by the library.
/// Defaults to `true`.
///
/// @note Changing this property does not affect already indexed documents.
@property (atomic) BOOL shouldIndexAnnotations;

/// This property shows what tokenizer is used currently. You can set it in the initializers.
/// When nil (the default), a PSPDFKit custom porter tokenizer that allows better CJK indexing is used.
/// This tokenizer also comes with a few drawbacks, like much more lax matching of words (Searching for "Dependency" will also return "Dependencies").
/// If that is a problem, we suggest using the 'UNICODE61' tokenizer. The UNICODE61 tokenizer allows searching inside text with diacritics. http://swwritings.com/post/2013-05-04-diacritics-and-fts
/// Sadly, Apple doesn't ship this tokenizer with their sqlite builds but there is a support article how to enable it: https://pspdfkit.com/guides/ios/memory-and-storage/how-to-enable-the-unicode61-tokenizer/
///
/// @warning Once the database is created, changing the `tokenizer` property will assert.
@property (nonatomic, nullable, copy, readonly) NSString *tokenizer;

/// Will save a reversed copy of the original page text. Defaults to YES.
///
/// @note If enabled, the sqlite cache will be about 2x bigger, but ends-with matches will be enabled.
/// @note This doesn't change indexes that already exist.
@property (atomic) BOOL saveReversedPageText;

/// Suspends the operations queues.
@property (nonatomic) BOOL suspended;

/// On iOS, the system watchdog automatically kills any process taking using large amounts of CPU for extended periods of time.
/// When indexing a very large amount of documents at the same time, it is possible to go over this limit. To prevent this from happening,
/// `PSPDFLibrary` periodically pauses indexing if it has been going on for a long enough period, and then resumes it after a short break.
/// Typically, if indexing is taking longer than `maximumContiguousIndexingTime`, the library will pause itself (by setting `suspended` to `true`), and
/// resume after the `automaticPauseDuration`.
///
/// Defaults to `true` on iOS devices. Set to `false` to disable this behavior.
@property (nonatomic) BOOL automaticallyPauseLongRunningTasks;

/// The amount of time (in seconds) that indexing can run uninterrupted when `automaticallyPauseLongRunningTasks` is set to `true`.
/// Defaults to 140.
@property (atomic) NSTimeInterval maximumContiguousIndexingTime;

/// The amount of time indexing should be paused when suspended `automaticallyPauseLongRunningTasks` is set to `true`.
/// Defaults to 40 seconds.
@property (atomic) NSTimeInterval automaticPauseDuration;

// MARK: Library Operations

/// Available options which can be used while searching text using the `PDFLibrary`.
typedef NSString *PSPDFLibraryOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PDFLibrary.Option);

/// Option keys. Limit the number of document results.
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionMaximumSearchResultsTotal;
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionMaximumSearchResultsPerDocument;

/// Limit the number of preview results.
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionMaximumPreviewResultsTotal;
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionMaximumPreviewResultsPerDocument;

/// Set this to @YES to restrict search to exact word matches instead of beginsWith/endsWith checks.
///
/// @warning If the default tokenizer is used, this will impact performance. If you find it is too slow, consider using a different `tokenizer`. See https://pspdfkit.com/guides/ios/features/indexed-full-text-search/
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionMatchExactWordsOnly;

/// Set this to @YES to restrict search to exact phrase matches. This means that "Lorem ipsum dolor"
/// only matches that phrase and not something like "Lorem sit ipsum dolor".
///
/// @warning If the default tokenizer is used, this will impact performance. If you find it is too slow, consider using a different `tokenizer`. See https://pspdfkit.com/guides/ios/features/indexed-full-text-search/
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionMatchExactPhrasesOnly;

/// Set this to @YES to exclude annotations from the search.
/// By default, indexed annotations will be searched.
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionExcludeAnnotations;

/// Set this to @YES to exclude document text from the search.
/// By default, indexed document text will be searched.
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionExcludeDocumentText;

/// Customizes the range of the preview string. Defaults to 20/160.
PSPDF_EXPORT PSPDFLibraryOption const PSPDFLibraryOptionPreviewRange;

/// See `documentUIDsMatchingString:options:completionHandler:previewTextHandler:`.
- (void)documentUIDsMatchingString:(NSString *)searchString options:(nullable NSDictionary<PSPDFLibraryOption, id> *)options completionHandler:(void (^)(NSString *searchString, NSDictionary<NSString *, NSIndexSet *> *resultSet))completionHandler;

/// Queries the database for matches of `searchString`. Only direct matches, begins-with and ends-with matches are supported.
/// Returns in the `completionHandler`.
/// If you provide an optional `previewTextHandler`, a text preview for all search results will be
/// extracted from the matching documents and a dictionary of UID -> sets of `LibraryPreviewResult` will
/// be returned in the `previewTextHandler`.
///
/// By default the number of search and preview results is limited to 500 to keep maximum search times reasonable. Use `options` to modify both limits.
///
/// @param searchString The string to search for in the FTS database.
/// @param options The options for the search.
/// @param completionHandler A closure to be executed on completion of the search. It's arguments are the input search string and a dictionary of UID -> `IndexSet` of matching page numbers. This will be called on a background thread, likely not on the calling thread.
/// @param previewTextHandler A closure to executed with a text preview argument for all the search results. A dictionary of UID -> sets of `LibraryPreviewResult` will be passed in as the argument. This will be called on a background thread, likely not on the calling thread.
///
/// @note At least one of `completionHandler` and `previewTextHandler` must be non-nil.
/// @note Ends-with matches are only possible if `saveReversedPageText` has been YES while the document was indexed.
- (void)documentUIDsMatchingString:(NSString *)searchString options:(nullable NSDictionary<PSPDFLibraryOption, id> *)options completionHandler:(nullable void (^)(NSString *searchString, NSDictionary<NSString *, NSIndexSet *> *resultSet))completionHandler previewTextHandler:(nullable void (^)(NSString *searchString, NSDictionary<NSString *, NSSet<PSPDFLibraryPreviewResult *> *> *resultSet))previewTextHandler;

// MARK: Index Status

/// Checks the indexing status of the document. If status is `PSPDFLibraryIndexStatusPartialAndIndexing` progress will be set as well.
///
/// @param UID The UID of the document whose index status is to be retrieved.
/// @param outProgress A pointer to a CGFloat that, on return, will point to the current indexing progress if the document is currently being indexed.
/// @return The current indexing status of the document with the specified UID.
- (PSPDFLibraryIndexStatus)indexStatusForUID:(NSString *)UID withProgress:(nullable CGFloat *)outProgress;

/// Returns YES if library is currently indexing, and is not suspended. This property will return `false` if
/// indexing is suspended automatically because `automaticallyPauseLongRunningTasks` is set to `true`.
@property (nonatomic, getter=isIndexing, readonly) BOOL indexing;

/// Returns all queued and indexing UIDs.
@property (nonatomic, readonly) NSOrderedSet<NSString *> *queuedUIDs;

/// Returns all the indexed UIDs, or nil if we were unable to fetch the data.
@property (nonatomic, readonly, nullable) NSOrderedSet<NSString *> *indexedUIDs;

/// Specifies the number of indexed UIDs, or -1 if it was unable to be retrieved.
@property (nonatomic, readonly) NSInteger indexedUIDCount;

/// Retrieves a document with the specified UID from the data source, if any.
/// Using this method is preferred to directly interacting with the data source's PSPDFLibraryDataSource methods.
///
/// @param UID The UID of the document to be fetched.
/// @return The document for the specified UID, if it exists, else nil.
///
/// @warning This method might be slow, as it depends on the data source's ability to provide the document.
- (nullable PSPDFDocument *)indexedDocumentWithUID:(NSString *)UID;

// MARK: Indexing Operations

/// The library's data source. Note that this object will be retained
@property (atomic, strong, nullable) id<PSPDFLibraryDataSource> dataSource;

/// Updates the index based on information provided by the data source. If there is not data source set, this method will raise `PSPDFLibraryInvalidOperationException`.
/// Any currently queued documents will be removed.
///
/// If indexing is running at background priority (the default) and you run tests on continuous integration
/// machines that may run multiple tasks, be aware that indexing may be resource starved and take unexpectedly
/// long to complete. Therefore we recommend using a long timeout such as 60 seconds for waiting for
/// completion in tests, even if indexing runs much faster than this on a local development machine.
///
/// @param completionHandler The block to call after all indexing operations have been completed. This may be called on a background queue.
/// @see dataSource.
- (void)updateIndexWithCompletionHandler:(nullable dispatch_block_t)completionHandler;

/// Removes the indexed contents for document with a matching `UID`.
///
/// @param UID The UID of the document whose content is to be removed from the index.
/// @warning This method performs its work synchronously, and will block until the database call completes.
- (void)removeIndexForUID:(NSString *)UID;

/// Removes all indexed content by deleting the database and recreating it.
///
/// @warning This method is synchronous and will block until the database call completes.
- (void)clearAllIndexes;

// MARK: Spotlight Helpers

/// Fetches the document specified by the user activity
///
/// @param userActivity The userActivity received in your application delegate’s `application:continueUserActivity:restorationHandler:` as a result of the user selecting a spotlight search result.
/// @param completionHandler The block to call if the document corresponding to the userActivity has been indexed in Spotlight.
- (void)fetchSpotlightIndexedDocumentForUserActivity:(NSUserActivity *)userActivity completionHandler:(void (^)(PSPDFDocument *_Nullable document))completionHandler;

// MARK: Queue Operations

/// Cancels all pending preview text operations.
///
/// @note The `previewTextHandler` of cancelled operations will not be called.
- (void)cancelAllPreviewTextOperations;

@end

/// This category allows you to encrypt the database file of your `PSPDFLibrary` instances.
/// To use this functionality, you need third-party software that implement the `sqlite3_key`
/// and `sqlite3_rekey` functions. An example for this is SQLCipher: https://www.zetetic.net/sqlcipher/
/// Information on the necessary configuration and setup can be found here:
/// https://www.zetetic.net/sqlcipher/sqlcipher-binaries-ios-and-osx/
/// You also need to enable encryption support. To do this, provide register an encryption provider by
/// calling `-[PSPDFKitGlobal databaseEncryptionProvider:]`.
@interface PSPDFLibrary (EncryptionSupport)

/// Returns an encrypted library for this given path. The `encryptionKeyProvider` is used to access
/// the encryption key when necessary. This allows us to not keep the encryption key around in memory.
/// Your implementation of encryption key provider should therefore always load the key from secure storage,
/// e.g. Apple's keychain. An encryption key provider must also be side-effect free in the sense
/// that it always returns the same encryption key on every call.
/// This method will return `nil` for invalid paths.
///
/// @note In contrast to `libraryWithPath:`, this method will not return the same instance when calling
/// it with an already used path.
///
/// @warning This method will return `nil` if the given encryption key provider was invalid.
+ (instancetype)encryptedLibraryWithPath:(NSString *)path encryptionKeyProvider:(nullable NSData * (^)(void))encryptionKeyProvider error:(NSError **)error;

/// Returns an encrypted library for this given path. The `encryptionKeyProvider` is used to access
/// the encryption key when necessary. This allows us to not keep the encryption key around in memory.
/// Your implementation of encryption key provider should therefore always load the key from secure storage,
/// e.g. Apple's keychain. An encryption key provider must also be side-effect free in the sense
/// that it always returns the same encryption key on every call.
/// This method will return `nil` for invalid paths.
///
/// You can also specify a custom `tokenizer` -- see the `tokenizer` property.
///
/// @note In contrast to `libraryWithPath:`, this method will not return the same instance when calling
/// it with an already used path.
///
/// @warning This method will return `nil` if the given encryption key provider was invalid.
+ (instancetype)encryptedLibraryWithPath:(NSString *)path encryptionKeyProvider:(nullable NSData * (^)(void))encryptionKeyProvider tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

/// Returns an encrypted library for this given path. The `encryptionKeyProvider` is used to access
/// the encryption key when necessary. This allows us to not keep the encryption key around in memory.
/// Your implementation of encryption key provider should therefore always load the key from secure storage,
/// e.g. Apple's keychain. An encryption key provider must also be side-effect free in the sense
/// that it always returns the same encryption key on every call.
/// This method will return `nil` for invalid paths.
///
/// You can also specify the FTS Version to use and a custom `tokenizer` -- see the `tokenizer` property.
///
/// @note In contrast to `libraryWithPath:`, this method will not return the same instance when calling
/// it with an already used path.
///
/// @warning This method will return `nil` if the given encryption key provider was invalid.
+ (instancetype)encryptedLibraryWithPath:(NSString *)path encryptionKeyProvider:(nullable NSData * (^)(void))encryptionKeyProvider ftsVersion:(PSPDFLibraryFTSVersion)ftsVersion tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

/// Returns an encrypted library for this given path. The `encryptionKeyProvider` is used to access
/// the encryption key when necessary. This allows us to not keep the encryption key around in memory.
/// Your implementation of encryption key provider should therefore always load the key from secure storage,
/// e.g. Apple's keychain. An encryption key provider must also be side-effect free in the sense
/// that it always returns the same encryption key on every call.
/// This method will return `nil` for invalid paths.
///
/// You can also specify the FTS Version to use and a custom `tokenizer` -- see the `tokenizer` property.
///
/// @note In contrast to `libraryWithPath:`, this method will not return the same instance when calling
/// it with an already used path.
///
/// @warning This method will return `nil` if the given encryption key provider was invalid.
+ (instancetype)encryptedLibraryWithPath:(NSString *)path encryptionKeyProvider:(nullable NSData * (^)(void))encryptionKeyProvider indexingPriority:(PSPDFLibraryIndexingPriority)priority ftsVersion:(PSPDFLibraryFTSVersion)ftsVersion tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

/// Indicates if the library instance uses encryption.
@property (nonatomic, readonly, getter=isEncrypted) BOOL encrypted;

@end

/// The PSPDFLibraryDataSource protocol is adopted by an object that provides the documents to be indexed by a `PSPDFLibrary`.
/// These methods will not be called on the main queue, and can take long to execute. If you are implementing this protocol yourself and not using `PSPDFLibraryFileSystemDataSource`,
/// please read the documentation carefully.
PSPDF_PROTOCOL_SWIFT(LibraryDataSource)
@protocol PSPDFLibraryDataSource<NSObject>

@optional

/// Notifies the data source that the library is about to begin the indexing process. Perform any required setup here.
///
/// @param library The library that is about to begin indexing.
- (void)libraryWillBeginIndexing:(PSPDFLibrary *)library;

/// Called after the library indexes a document.
///
/// @note Implement this method on your data source instead of listening for the `PSPDFLibraryDidFinishIndexingDocument` notification.
/// If the given document is the last one to be indexed, the library calls the completion handler passed in to its
/// `-updateIndexWithCompletionHandler:` methods. This method gives your data source a chance to finish any bookkeeping so as to ensure that
/// its state is up to date when the completion handler is called.
///
/// @param library The library that finished indexing the document.
/// @param UID The UID of the document that finished indexing.
/// @param success Specifies whether the library successfully indexed the document.
- (void)library:(PSPDFLibrary *)library didFinishIndexingDocumentWithUID:(NSString *)UID success:(BOOL)success;

/// Called after the library removes a document from its index.
///
/// @param library The library that removed the document.
/// @param UID The UID of the document that was removed.
- (void)library:(PSPDFLibrary *)library didRemoveDocumentWithUID:(NSString *)UID;

@required

/// Asks the data source for the UIDs of the documents to be indexed by the library. This method should not return any uids that are already indexed, or they will be reindexed.
/// This is useful in cases when the document was modified, and its contents changed and therefore need the index to be updated as well.
///
/// @param library The library object requesting this information.
/// @return An array of `NSString`s each corresponding to the a `Document` UID.
- (NSArray<NSString *> *)uidsOfDocumentsToBeIndexedByLibrary:(PSPDFLibrary *)library;

/// Asks the data source for the UIDs for documents to be removed. This method will be called by the library at the start of its indexing process to allow for removal of any non-existing documents.
/// This is especially necessary when the `indexToSpotlight` property is set to YES, as having deleted documents show up in indexed spotlight search is not good.
///
/// @param library The library object requesting this information.
/// @return An array of `NSString`s each corresponding to a previously indexed `Document` UID.
- (NSArray<NSString *> *)uidsOfDocumentsToBeRemovedFromLibrary:(PSPDFLibrary *)library;

/// Asks the data source for a document with the specified UID.
///
/// @param library The library that requires the document.
/// @param UID     The UID of the requested document.
/// @return A document with a matching UID, or `nil` if no such document exists.
///
/// @warning This method may be called even without `libraryWillBeginIndexing:` being called first, if a document is required for Spotlight.
- (nullable PSPDFDocument *)library:(PSPDFLibrary *)library documentWithUID:(NSString *)UID;

@end

NS_ASSUME_NONNULL_END
