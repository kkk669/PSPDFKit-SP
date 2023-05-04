//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <CoreSpotlight/CoreSpotlight.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationManager.h>
#import <PSPDFKit/PSPDFBookmark.h>
#import <PSPDFKit/PSPDFCache.h>
#import <PSPDFKit/PSPDFCoordinatedFileDataProviding.h>
#import <PSPDFKit/PSPDFDataProviding.h>
#import <PSPDFKit/PSPDFDocumentProvider.h>
#import <PSPDFKit/PSPDFDocumentSecurityOptions.h>
#import <PSPDFKit/PSPDFFileConflictResolution.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFPageBinding.h>
#import <PSPDFKit/PSPDFRenderManager.h>
#import <PSPDFKit/PSPDFRenderRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotationManager;
@class PSPDFBookmarkManager;
@class PSPDFCompletionCallingProgress;
@class PSPDFDocumentCheckpointer;
@class PSPDFDocumentFeatures;
@class PSPDFDocumentProvider;
@class PSPDFEmbeddedFile;
@class PSPDFFile;
@class PSPDFFormParser;
@class PSPDFOutlineElement;
@class PSPDFOutlineParser;
@class PSPDFPageInfo;
@class PSPDFRenderReceipt;
@class PSPDFTextParser;
@class PSPDFTextSearch;
@class PSPDFViewController;

@protocol PSPDFDocumentDelegate;
@protocol PSPDFUndoController;

/// Document page number.
typedef NSNumber *PSPDFDocumentPageNumber;

/// When saving a document, you can provide various save options as outlined
/// below.
typedef NSString *PSPDFDocumentSaveOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PDFDocumentSaveOption);

/// Set to @YES to force saving, even though there are no dirty objects.
/// This is useful in combination with a rewrite, to remove unreferenced objects:
/// `PSPDFDocumentSaveOptionStrategy = @(PSPDFDocumentSaveStrategyRewrite)`
PSPDF_EXPORT PSPDFDocumentSaveOption const PSPDFDocumentSaveOptionForceSaving;

/// Defines the save strategy. Defaults to `PSPDFDocumentSaveStrategyAppend`
PSPDF_EXPORT PSPDFDocumentSaveOption const PSPDFDocumentSaveOptionStrategy;

/// Document saving strategy.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFDocumentSaveStrategy) {
    /// Fast save operation, appends new data. File grows with every save.
    PSPDFDocumentSaveStrategyAppend,
    /// Slower operation, rewrites file, removes unreferenced objects.
    PSPDFDocumentSaveStrategyRewrite,
    /// Optimizes the file size and rewrites the file. This is the slowest option of the three, but it offers the smallest file size. If you need to optimize for saving performance, use `PSPDFDocumentSaveStrategyAppend` instead.
    PSPDFDocumentSaveStrategyRewriteAndOptimizeFileSize,
} PSPDF_ENUM_SWIFT(Document.SaveStrategy);

/// A `PSPDFDocumentSecurityOptions` instance, specifies the security options to
/// use when saving the document. Not passing this options means the current
/// security options will be used.
///
/// @note Requires `Features.documentEditing` to be part of your license.
PSPDF_EXPORT PSPDFDocumentSaveOption const PSPDFDocumentSaveOptionSecurityOptions;

/// A `BOOL` value wrapped in an `NSNumber`. If set to YES, applies all redactions
/// in the document and removes the content underneath them.
/// Not passing this option means redactions are not
/// applied, and redaction annotations will stay in the document.
///
/// @note Requires `Features.redaction` to be part of your license.
PSPDF_EXPORT PSPDFDocumentSaveOption const PSPDFDocumentSaveOptionApplyRedactions;

/// A document posts an underlying file changed notification each time one of the
/// backing files of the document is changed and the change did not originate from
/// the document itself. When a file deletion can be detected, the same notification
/// will be sent with a `PSPDFDocumentUnderlyingFileWillBeDeletedKey` in the user info.
/// The notification will be sent on the main thread.
PSPDF_EXPORT NSNotificationName const PSPDFDocumentUnderlyingFileChangedNotification;

typedef NSString *PSPDFDocumentUnderlyingFileChangedNotificationOptions NS_TYPED_ENUM NS_SWIFT_NAME(Document.UnderlyingFileChangedNotificationOption);

/// The underlying file url key identifies the file url of the changed file inside
/// a `PSPDFDocumentUnderlyingFileChangedNotification`'s user info dictionary. It
/// is of type `URL`.
PSPDF_EXPORT PSPDFDocumentUnderlyingFileChangedNotificationOptions const PSPDFDocumentUnderlyingFileURLKey NS_SWIFT_NAME(changedFileURL);

/// The underlying file url key identifies the data provider that registered the change inside
/// a `PSPDFDocumentUnderlyingFileChangedNotification`'s user info dictionary. It
/// is of type `id<PSPDFCoordinatedFileDataProviding>`.
PSPDF_EXPORT PSPDFDocumentUnderlyingFileChangedNotificationOptions const PSPDFDocumentUnderlyingDataProvider;

/// A boolean `NSNumber` indicating that the underlying file is about to be deleted.
PSPDF_EXPORT PSPDFDocumentUnderlyingFileChangedNotificationOptions const PSPDFDocumentUnderlyingFileWillBeDeletedKey NS_SWIFT_NAME(deleteFile);

/// The `Document` class represents a set of PDF sources that are displayed as one document.
///
/// The PDF sources are internally represented as data providers (implementations of the `DataProviding` protocol).
/// The typical use case is to initialize the document with a single `fileURL`, which creates an implicit
/// `PSPDFCoordinatedFileDataProvider` by default. You can also opt to use `Data` or custom implementations of
/// `DataProviding` as sources during initialization.
///
/// This object can be created on any thread. Accessing properties is thread safe but might take some time,
/// as the underlying PDF documents need to be processed to fetch data like `pageCount` or `title`.
/// The document builds an internal cache, so subsequent access is faster.
/// For this reason, ensure that document objects are not created/destroyed randomly for maximum efficiency.
///
/// `Document` supports `NSFastEnumeration` by enumerating over its `documentProviders`. The document
/// providers are internal wrappers around the data providers created during initialization.
///
/// @note Not all state is archived with `NSCoder`.
///
/// @note Ensure that a `Document` is only opened by one `PDFViewController` at any time.
/// Also ensure that subclasses do not implement their own equality semantics, and instead use the `UID` property to check if two documents are equal.
PSPDF_CLASS_SWIFT(Document)
@interface PSPDFDocument : NSObject<PSPDFDocumentProviderDelegate, PSPDFOverridable, NSCopying, NSSecureCoding, NSFastEnumeration, PSPDFFileCoordinationDelegate>

// MARK: Initialization

/// Initialize `Document` with a single local file URL or remote URL.
///
/// This convenience initializer creates either a `CoordinatedFileDataProvider` or `FileDataProvider`.
/// depending on if `PSPDFSettingKeyFileCoordinationEnabled` is set on the `PSPDFKit` shared object.
///
/// If the URL is a remote URL, `URLDataProvider` is used.
/// Remote URLs set `.annotationSaveMode` to `.disabled` by default to protect against potential annotation data loss.
///
/// If you subclass `Document` with a custom initializer and want an equivalent of `init(url:)`
/// for a local file URL, you need to call the designated initializer as
/// `super.init(dataProviders: [CoordinatedFileDataProvider(fileURL: url)], loadCheckpointIfAvailable: false)`.
///
/// @note If you are expecting to encounter symlinks or alias files, you need to resolve those using NSURL APIs before
/// passing the URLs to `Document`. `Document` won't automatically resolve them for performance reasons.
///
/// @param url A local file URL or a remote URL of a PDF document.
- (instancetype)initWithURL:(NSURL *)url;

/// Initialize `Document` with one or multiple `dataProviders` conforming to `DataProviding`.
///
/// Does not load from a checkpoint even if one exists.
///
/// @param dataProviders An array of data providers that supply the PDF document content.
- (instancetype)initWithDataProviders:(NSArray<id<PSPDFDataProviding>> *)dataProviders;

/// Initialize `Document` with one or multiple `dataProviders` conforming to `DataProviding`, optionally enabling restoring from a checkpoint.
///
/// To load from a local file, use `CoordinatedFileDataProvider`.
/// To load from `Data`, use `DataContainerProvider`.
///
/// Data providers conforming to `CoordinatedFileDataProviding` will get their `coordinationDelegate` automatically assigned to the document.
///
/// @note It's currently not possible to add the same file multiple times. This will fail to display correctly.
///
/// @warning Using a large number of data providers (50+) can negatively impact performance. The exact number of well-performing data providers varies: It is dependent on the complexity of the used PDFs, and on the device. Such configurations should be tested, and the PDFs should be combined, if performance issues arise.
///
/// @param dataProviders An array of data providers that supply the PDF document content.
/// @param loadCheckpoint Specifies whether an available checkpoint should be loaded.
- (instancetype)initWithDataProviders:(NSArray<id<PSPDFDataProviding>> *)dataProviders loadCheckpointIfAvailable:(BOOL)loadCheckpoint NS_DESIGNATED_INITIALIZER;

/// Initialize a document via `NSSecureCoding`.
///
/// Document support secure coding and serializes all data providers automatically.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Creates a new document with all the data providers of the receiver plus those in `dataProviders`.
///
/// @note This uses `NSCopying` to preserve custom settings.
///
/// @param dataProviders An array containing objects conforming to `DataProviding` to be added to the new document.
/// @return A new document object.
- (instancetype)documentByAppendingDataProviders:(NSArray<id<PSPDFDataProviding>> *)dataProviders;

// MARK: General

/// The document delegate to control saving and annotation path resolving.
///
/// @note This can be freely set and is not directly used inside PSPDFKit.
@property (nonatomic, weak) id<PSPDFDocumentDelegate> delegate;

/// Returns YES if the document data source can be accessed and the PDF has at least one page and is unlocked.
/// Might need file operations to parse the document.
///
/// @note Password protected documents will return NO here until the correct password is set.
/// Check for `isLocked` to see if it's a protected document.
@property (nonatomic, readonly, getter=isValid) BOOL valid;

/// If the document can not be opened and thus is in an error state, the error is propagated through this property.
@property (nonatomic, readonly, nullable) NSError *error;

/// Compare two documents for equality. Will check if the source definitions are the same.
/// This will not detect two different files that are the same - for that better do a custom file comparison.
- (BOOL)isEqualToDocument:(PSPDFDocument *)otherDocument;

/// The features this document allows and enables.
///
/// Features are a set of functionality that are enabled or disabled based on the document's
/// permissions, the file path, the PSPDFKit license in use or other technical limitations.
///
/// This object can be used to check these conditions at a central point and enable
/// or disable buttons or other UI elements accordingly or change the behavior of certain
/// functions in an app based on these conditions.
@property (nonatomic, readonly) PSPDFDocumentFeatures *features;

// MARK: Files

/// Convenience accessor for the first fileURL of the document.
@property (nonatomic, readonly, nullable) NSURL *fileURL;

/// Return all file URLs. Returns an empty array if the documents contains no file data providers (`FileDataProviding`).
@property (nonatomic, readonly) NSArray<NSURL *> *fileURLs;

/// The document itself can be comprised out of multiple files, therefore it can't be a file
/// presenter on its own. Instead, you can use this property to get a list of the data providers’
/// file presenters.
/// Returns an empty array if the document has no data providers that have file presenters.
@property (nonatomic, readonly) NSArray<id<NSFilePresenter>> *filePresenters;

/// A combined parent progress object for all registered data providers.
/// This can be used to cancel any active progress operations when the document is dismissed.
///
/// @note The progress is cancelled when all registered data providers’ progresses are cancelled.
///
/// @warning Do not override this property. It returns a private `NSProgress` subclass with added functionality.
/// Both this and other PSPDFKit classes rely on that behavior.
/// Setting the `completedUnitCount`, `totalUnitCount`, or adding children is not supported.
@property (nonatomic, readonly) NSProgress *progress;

/// In some cases, the PDF document is a converted document from an Word, Excel or other file.
/// If `originalFile` is set, then some actions such as Open In or Send via Email has the option to use the original file.
///
/// @note The "Open In" feature of iOS needs an `URL` - `Data` does not work here.
@property (nonatomic, nullable) PSPDFFile *originalFile;

/// Returns path for a single page (in case pages are split up). Page starts at 0.
///
/// @note Subclassing Note: Uses `fileIndexForPageAtIndex:` and `URLForFileIndex:` internally.
- (nullable NSURL *)pathForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Returns the position inside the internal documentProviders array. Page starts at 0.
- (PSPDFFileIndex)fileIndexForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Returns the URL corresponding to the `fileIndex`.
- (nullable NSURL *)URLForFileIndex:(PSPDFFileIndex)fileIndex NS_SWIFT_NAME(urlForFile(at:));

/// Gets the file name for page 0. @see fileNameForPageAtIndex:
@property (nonatomic, readonly, nullable) NSString *fileName;

/// Helper that gets a suggested filename for a specific page. Page starts at 0.
///
/// @note Guarantees to return a string (even if pageIndex is out of bounds)
- (nullable NSString *)fileNameForPageAtIndex:(PSPDFPageIndex)pageIndex NS_SWIFT_NAME(fileName(forPageAtIndex:));

/// Deletes the underlying files from the disk, including the document itself and
/// all cache and metadata files.
///
/// 1) [self.pspdfkit.cache removeCacheForDocument:self];
/// 2) All files for set file URLs
/// 3) The `dataDirectory`
///
/// @warning You should make sure that the receiver is no longer accessed after calling this method!
///
/// @param error The error, if one occurred.
///
/// @return YES if the deletion was successful, NO otherwise.
- (BOOL)deleteFiles:(NSError **)error;

// MARK: Data

/// PDF data when initialized with `PSPDFDataContainerProvider` otherwise nil.
/// This is a shortcut to the first entry of `dataArray`.
@property (nonatomic, readonly, nullable) NSData *data;

/// The data of any `PSPDFDataContainerProvider`s in `dataProviders`.
///
/// @note If writing annotations is enabled, the `dataArray`'s content will change after a save.
/// Returns an empty array there are no `PSPDFDataContainerProvider`-based data providers.
@property (nonatomic, readonly) NSArray<NSData *> *dataArray;

/// Returns an ordered dictionary with filename : NSData objects.
/// Will memory-map data files.
///
/// @note If there is no file name available, this will use the PDF title or "Untitled PDF" if all fails.
/// Uses `PSPDFDocumentProviders dataRepresentationWithError:`. Errors are only logged.
@property (nonatomic, readonly) NSDictionary<NSString *, NSData *> *fileNamesWithDataDictionary;

// MARK: Providers

/// PDF `dataProviders` are used to read and write PDF data from various sources.
///
/// When initializing a document with a file URL, a suitable data provider will be
/// automatically created to read data from the file.
///
/// A data provider is the object that handles reading and writing actual data from
/// and to a source such as a file or a remote location. It is always available even
/// when the document is not loaded.
///
/// @note Data providers can also be used to dynamically decrypt a document.
@property (nonatomic, readonly) NSArray<id<PSPDFDataProviding>> *dataProviders;

/// Get an array of document providers to easily manage documents with multiple files.
///
/// A document provider is a representation of an actual PDF file. It uses a data provider
/// to access the file's data and gives access to a file's model, such as pages, annotations,
/// text, etc.
///
/// Accessing this property will load the document if it is not loaded yet. It will
/// then create the document providers representing the receiver.
///
/// Document Providers parse PDF files and can take up considerable memory.
/// They are freed in various conditions:
/// - low-memory situations as long as there is no PDFViewController showing them and there are no unsaved changes.
/// - Saving when redactions are applied
/// - When clearCache is called
/// - When the document is unlocked with a password or locked
@property (nonatomic, readonly) NSArray<PSPDFDocumentProvider *> *documentProviders;

/// Get the document provider for a specific page. Page starts at 0.
- (nullable PSPDFDocumentProvider *)documentProviderForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Get the page offset from a specific `documentProvider`.
/// Can be used to calculate from the document provider page to the `Document` page.
- (NSUInteger)pageOffsetForDocumentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Reloads document providers from this document.
///
/// All document providers that are reloaded will be replaced with a new instance.
///
/// @param documentProviders The document providers to be replaced. They must be part of the current document. The document providers will be replaced with new during the reload.
/// @param dataProviderOverride A block that offers a chance to replace the data provider during the document provider reload.
- (void)reloadDocumentProviders:(NSArray<PSPDFDocumentProvider *> *)documentProviders
           dataProviderOverride:(id<PSPDFDataProviding> (^_Nullable)(PSPDFDocumentProvider *))dataProviderOverride  NS_SWIFT_NAME(reload(documentProviders:dataProviderOverride:));

// MARK: Identifiers

/// Returns a document identifier (inferred from a document provider if possible).
/// A permanent identifier based on the contents of the file at the time it was originally created.
/// If a document identifier is not available, generated UID value is returned.
///
/// @note This value will stay persistent, if the document is modified, moved to a different location or duplicated. Therefore,
/// it's not guaranteed to be unique among multiple documents.
@property (nonatomic, copy, readonly, nullable) NSData *documentId;

/// Returns a string representation of `documentId`.
@property (nonatomic, copy, readonly, nullable) NSString *documentIdString;

/// The unique UID for the document.
///
/// By default, the UID is created automatically based on the content sources that are configured. If you already have
/// unique identifiers for your documents, from a cloud storage provider, or other content management system, you can set a
/// custom value here as well.
///
/// When using custom UIDs, however, you should set them before the document is used/cached/displayed and have to make sure
/// that the values are actually unique:<br>
/// Since the UID is used internally for the page renderer cache, and defines the filename for external annotation storage,
/// UID collisions will cause problems down the line. And even when your custom UIDs are collision-free, you will either
/// have to set a new UID or clear the cache if you change the PDF *contents* outside of PSPDFKit.
///
/// @note This value might change, if the document is modified or moved to a different location.
/// @warning Using the same UID for two or more documents that are backed by different PDF files is unsupported, and leads
/// to undefined behavior. Modifying documents that suffer from a UID collision will likely result in data corruption!
@property (nonatomic, copy, null_resettable) NSString *UID;

// MARK: Page Info Data

/// Return pdf page count. Can be called from any thread.
///
/// @warning Might need file operations to parse the document (slow)
@property (nonatomic, readonly) PSPDFPageCount pageCount;

/// Cached rotation and aspect ratio data for specific page. Page starts at 0.
/// Override the methods in `PSPDFDocumentProvider` instead.
///
/// If multiple `PSPDFDocumentProvider`s are used in one `Document` the returned
/// `PSPDFPageInfo`'s `page` property can no longer be relied on to always equal to
/// the supplied `page` argument, since `PSPDFPageInfo`'s `page` property is
/// `PSPDFDocumentProvider`-relative, while the `page` argument is relative to
/// all `PSPDFDocumentProvider`s in the `Document`.
- (nullable PSPDFPageInfo *)pageInfoForPageAtIndex:(PSPDFPageIndex)pageIndex;

// MARK: Saving a Document

/// Saves the document synchronously.
///
/// Saves the document and all of its linked data, including bookmarks and
/// annotations, synchronously.
///
/// Calling this method when the document has not been modified is fast and will not result in writing to disk.
///
/// We recommend only calling this when the user is not actively annotating the document.
/// If this is called while an annotation is being added (e.g. drawing) then the most
/// recent input may be discarded. By default PDFViewController from PSPDFKitUI will save
/// automatically at appropriate times, so there is no need to call this method explicitly.
///
/// @param options Passing `nil` for options is equivalent to passing an empty
/// dictionary `@{}`. Available options are `PDFDocumentSaveOptionForceSaving`,
/// `PDFDocumentSaveOptionStrategy` and `PDFDocumentSaveOptionSecurityOptions`,
/// see their documentation for more details.
///
/// @param error Pointer to an error object if the document couldn't be saved,
/// otherwise the pointer remains unassigned.
///
/// @return `true` if the save operation completed successfully, otherwise `false`
/// together with the `error` parameter set to a valid error object.
///
/// @throws `NSInternalInconsistencyException` if save options are not valid.
///
/// @see `PDFDocumentSaveOptionForceSaving`
/// @see `PDFDocumentSaveOptionStrategy`
/// @see `PDFDocumentSaveOptionSecurityOptions`
/// @see `PDFDocumentSaveOptionApplyRedactions`
/// @see `saveWithOptions:completionHandler:`
- (BOOL)saveWithOptions:(nullable NSDictionary<PSPDFDocumentSaveOption, id> *)options error:(NSError *_Nullable *)error NS_REFINED_FOR_SWIFT;

/// Saves the document asynchronously.
///
/// An asynchronous version for `saveWithOptions:error:`. Does not block the
/// calling thread.
///
/// We recommend only calling this when the user is not actively annotating the document.
/// If this is called while an annotation is being added (e.g. drawing) then the most
/// recent input may be discarded. By default PDFViewController from PSPDFKitUI will save
/// automatically at appropriate times, so there is no need to call this method explicitly.
///
/// @param options A dictionary with save options. See `saveWithOptions:error:` for
/// details on the available options.
///
/// @param completionHandler Called on the *main thread* after the save operation
/// finishes. If there was an error during the save operation, an `error` object is
/// passed to the completion handler, otherwise `error` is `nil`. All saved
/// annotations are also passed to the completion handler.
///
/// @throws `NSInternalInconsistencyException` if save options are not valid.
- (void)saveWithOptions:(nullable NSDictionary<PSPDFDocumentSaveOption, id> *)options completionHandler:(nullable void (^)(NSError *_Nullable error, NSArray<__kindof PSPDFAnnotation *> *savedAnnotations))completionHandler NS_REFINED_FOR_SWIFT;

/// The object used for handling checkpoints. Change its `strategy` to get the behavior you require.
///
/// Learn More: https://pspdfkit.com/guides/ios/features/document-checkpointing/
@property (nonatomic, readonly) PSPDFDocumentCheckpointer *checkpointer;

/// Convenience getter for the documents' outline.
///
/// @note Only evaluates the first file if multiple files are set.
@property (nonatomic, readonly, nullable) PSPDFOutlineElement *outline;

/// User activity that is associated with the document.
/// Needs to be set externally.
///
/// @note This activity will be attached to drag sessions originating from a tab containing this document in `PSPDFTabbedViewController`.
@property (nonatomic, nullable) NSUserActivity *userActivity;

// MARK: Undo

/// An object that keeps track of undoable commands and works together with the
/// system undo manager to provide the undo/redo functionality.
@property (nonatomic, readonly) id<PSPDFUndoController> undoController;

@end

@interface PSPDFDocument (Caching)

/// Will clear all cached objects (`documentProviders`, `annotations`, `pageCount`, `outline`, `textParser`, ...)
///
/// @warning Calling this method will also destroy any unsaved annotations. It will, however, **not**
/// automatically reload the `PDFViewController`. For that, manually call `reloadData` afterwards.
- (void)clearCache;

/// Creates internal cache for faster display. override to provide custom caching.
///
/// @note This is thread safe and usually called on a background thread.
- (void)fillCache;

/// Path where metadata like annotations are saved, if they cannot be stored in the PDF document.
/// Defaults to `&lt;AppDirectory&gt;/Library/PrivateDocuments/PSPDFKit`. Cannot be nil.
///
/// This property is asymmetric. When setting this property, you should not include the document UID.
/// When reading this property, the document UID will be appended as the last path component.
/// This means you must not set this property to its own value because that would end up with the UID twice.
@property (nonatomic, copy) NSString *dataDirectory;

/// Make sure 'dataDirectory' exists. Returns error if creation is not possible.
- (BOOL)ensureDataDirectoryExistsWithError:(NSError **)error;

/// Controls if the disk cache should be used for this document.
///
/// https://pspdfkit.com/guides/ios/customizing-the-interface/using-the-render-queue/
///
/// By default this returns YES, unless any data provider disables `useDiskCache`,
/// or if any document provider is encrypted, in which case this returns NO.
/// Can always be manually set to NO.
@property (nonatomic) BOOL useDiskCache;

@end

@interface PSPDFDocument (Security)

/// Unlock documents with a password.
///
/// If the password is correct, this method returns YES. Once unlocked, you cannot use this function to re-lock the document.
///
/// If you attempt to unlock an already unlocked document, one of the following occurs:
/// If the document is unlocked with full owner permissions, `unlockWithPassword:` does nothing and returns YES. The password string is ignored.
/// If the document is unlocked with only user permissions, `unlockWithPassword:` attempts to obtain full owner permissions with the password string.
/// If the string fails, the document maintains its user permissions. In either case, this method returns YES.
///
/// After unlocking a document, you need to call `reloadData` on the `PDFViewController`.
///
/// If you're using multiple files or `appendFile:`, all new files will be unlocked with the password.
/// This doesn't harm if the document is already unlocked.
///
/// If you have a mixture of files with multiple different passwords, you need to subclass `didCreateDocumentProvider:` and unlock the `documentProvider` directly there.
///
/// @note `password` is not exposed as a property on purpose.
/// Ideally store the password securely in the keychain and set only when needed.
///
/// @warning This will re-create the document providers.
- (BOOL)unlockWithPassword:(NSString *)password;

/// Will re-lock a document if it has a password set.
///
/// @warning Make sure it is not currently displayed anywhere or call `reloadData` on the pdfController afterwards.
- (void)lock;

/// Indicates if the PDF document is encrypted. (= password protected)
///
/// @note Only evaluates the first file if multiple files are set.
/// Some documents can be encrypted but have an empty password set, which PSPDFKit will automatically unlock.
@property (readonly) BOOL isEncrypted;

/// Has the PDF file been unlocked? (is it still locked?).
///
/// @note Only evaluates the first file if multiple files are set.
@property (readonly) BOOL isLocked;

/// Specifies if the document has been unlocked with full access.
@property (readonly) BOOL isUnlockedWithFullAccess;

/// Specifies what functions are allowed for a PDF document.
///
/// @note This replaces `allowsCopying` and `allowsPrinting` from earlier versions of the SDK.
/// @note Only evaluates the first file if multiple files are set.
@property (readonly) PSPDFDocumentPermissions permissions;

/// A flag that indicates whether changing existing annotations or creating new annotations are allowed
///
/// @note Searches and checks the digital signatures on the first call (caches the result for subsequent calls)
@property (readonly) BOOL allowAnnotationChanges;

@end

@interface PSPDFDocument (Bookmarks)

/// Globally enable or disable bookmarks.
///
/// This value controls whether bookmarks should be enabled. There might be other things
/// preventing bookmarks from being enabled. Check the document's `features` to see
/// if bookmarks can be modified.
///
/// Defaults to YES.
@property (nonatomic, getter=areBookmarksEnabled) BOOL bookmarksEnabled;

/// Accesses the bookmark manager.
/// Bookmarks are handled on document level, not on `documentProvider`.
///
/// @note Bookmarks are loaded from the document by default. The document must be valid
/// for the manager to be loaded - otherwise it's nil.
@property (readonly, nullable) PSPDFBookmarkManager *bookmarkManager;

/// Returns the bookmarks.
///
/// @note The `Bookmark` objects themselves are not changed, only those who are not visible are filtered out.
@property (readonly) NSArray<PSPDFBookmark *> *bookmarks;

@end

@interface PSPDFDocument (PageLabels)

/// Set to NO to disable the custom PDF page labels and simply use page numbers. Defaults to YES.
@property (getter=arePageLabelsEnabled) BOOL pageLabelsEnabled;

/// Page labels for the current document. Page starts at 0.
/// Page labels may be used to set a different page number/index than what is inferred from the document by default.
/// Might be nil if the PageLabels dictionary isn't set in the PDF.
/// If `substituteWithPlainLabel` is set to YES then this always returns a valid string.
///
/// @note If `pageLabelsEnabled` is set to NO, then this method will either return nil or the plain label if `substitute` is YES.
- (nullable NSString *)pageLabelForPageAtIndex:(PSPDFPageIndex)pageIndex substituteWithPlainLabel:(BOOL)substitute;

/// Find page of a page label.
- (PSPDFPageIndex)pageForPageLabel:(NSString *)pageLabel partialMatching:(BOOL)partialMatching;

@end

/// Returns if JavaScript code can execute on this document.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFJavaScriptStatus) {
    /// JavaScript is disabled.
    PSPDFJavaScriptStatusDisabled,
    /// JavaScript is enabled.
    PSPDFJavaScriptStatusEnabled,
    /// JavaScript is enabled, but it won't show any alert message. If a
    /// programs wants to alert, the message will be printed to the console log
    /// instead. This is useful in the batch processing of form fields that may have validation scripts attached.
    PSPDFJavaScriptStatusEnabledDoNotDisturb,
} PSPDF_ENUM_SWIFT(Document.JavaScriptStatus);

@interface PSPDFDocument (Forms)

/// Set to NO to disable displaying/editing AcroForms. Defaults to YES.
///
/// @note Not all PSPDFKit variants do support AcroForms.
/// @warning For `formsEnabled` to work, you need to also set `annotationsEnabled` to YES, since forms are simply a special sub-type of Widget annotations.
@property (getter=areFormsEnabled) BOOL formsEnabled;

/// Control JavaScript processing. Defaults to `PSPDFJavaScriptStatusEnabled`.
///
/// https://pspdfkit.com/guides/ios/features/javascript/
///
/// @note Processing JavaScript can be slow for documents with a large number of
/// document providers or scripts. Disabling in most cases will not have any
/// negative effects.
@property PSPDFJavaScriptStatus javaScriptStatus;

/// Returns if JavaScript is enabled on this document.
@property (nonatomic, readonly) BOOL isJavaScriptStatusEnabled;

/// AcroForm parser for the document.
@property (readonly, nullable) PSPDFFormParser *formParser;

@end

@interface PSPDFDocument (EmbeddedFiles)

/// Returns all embedded file objects. (`PSPDFEmbeddedFile`)
@property (readonly) NSArray<PSPDFEmbeddedFile *> *allEmbeddedFiles;

@end

/// Annotations can be saved in the PDF or alongside in an external file.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationSaveMode) {
    /// Saving will be disabled. When this setting is used, annotation editing UI will be disabled.
    /// Otherwise there would be data loss because the user could make edits that would then not be saved.
    PSPDFAnnotationSaveModeDisabled,
    /// Will save to an external file. Uses `save/loadAnnotationsWithError:` in `PSPDFAnnotationManager`.
    PSPDFAnnotationSaveModeExternalFile,
    /// Will only save directly into the PDF.
    PSPDFAnnotationSaveModeEmbedded,
    /// Tries to save into the PDF if the file is writable, else falls back to external file.
    PSPDFAnnotationSaveModeEmbeddedWithExternalFileAsFallback
} PSPDF_ENUM_SWIFT(Document.AnnotationSaveMode);

@interface PSPDFDocument (Annotations)

/// Master switch to completely disable annotation display/parsing on a document. Defaults to YES.
///
/// If you change this property after the document is loaded, make sure you also call `clearCache`.
/// This is an expensive operation, so consider setting the `isHidden` property on each annotation instead.
///
/// @note This will disable the creation of the `PSPDFAnnotationManager`.
/// @warning This will also disable links and forms. In most cases, this is not what you want.
/// To disable editing features, instead customize `editableAnnotationTypes` in `PDFConfiguration`.
@property (nonatomic, getter=areAnnotationsEnabled) BOOL annotationsEnabled;

/// Add `annotations` to the current document (and the backing store `PSPDFAnnotationProvider`)
///
/// @note Uses each annotation’s `absolutePageIndex` property to determine which page it should be added to. As a result, the
/// `pageIndex` property of any added annotation will change when multiple `documentProviders` are set, and the annotation’s
/// `absolutePageIndex` falls outside the page range managed by the first document provider.
///
/// @param annotations An array of `PSPDFAnnotation` objects to be inserted.
/// @param options Insertion options (see the `PSPDFAnnotationOption...` constants in `PSPDFAnnotationManager.h`).
/// @return When all annotations could be added to the document, this method returns `true` and all objects in the array are
/// guaranteed to be contained in the value returned by `-allAnnotationsOfType:` when passing `PSPDFAnnotationTypeAll`,
/// until they are removed from the document. (Either by programmatically calling `removeAnnotations:options:` or by
/// deleting the annotation through UI.)
- (BOOL)addAnnotations:(NSArray<PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options NS_SWIFT_NAME(add(annotations:options:));

/// Insert `annotation` to the current document (and the backing store `PSPDFAnnotationProvider`) at the specified z-index.
///
/// @note Uses each annotation’s `absolutePageIndex` property to determine which page it should be added to. As a result, the
/// `pageIndex` property of any added annotation will change when multiple `documentProviders` are set, and the annotation’s
/// `absolutePageIndex` falls outside the page range managed by the first document provider.
///
/// @param annotation An `PSPDFAnnotation` object to be inserted.
/// @param destinationIndex The z-index the annotation should be inserted at.
/// @param options Insertion options (see the `PSPDFAnnotationOption...` constants in `PSPDFAnnotationManager.h`).
/// @return When all annotations could be added to the document, this method returns `true` and all objects in the array are
/// guaranteed to be contained in the value returned by `-allAnnotationsOfType:` when passing `PSPDFAnnotationTypeAll`,
/// until they are removed from the document. (Either by programmatically calling `removeAnnotations:options:` or by
/// deleting the annotation through UI.)
- (BOOL)insertAnnotation:(PSPDFAnnotation *)annotation atZIndex:(NSUInteger)destinationIndex options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options error:(NSError **)error;

/// Remove `annotations` from the backing `PSPDFAnnotationProvider` object(s).
///
/// If the annotations have replies, those will be removed too. If you don’t want this copy the annotations you want to keep and add them back.
///
/// @param annotations An array of PSPDFAnnotation objects to be removed.
/// @param options Deletion options (see the `PSPDFAnnotationOption...` constants in `PSPDFAnnotationManager.h`).
/// @return When all annotations could be removed, this method returns `true` and they will no longer be contained in the
/// value returned by `-allAnnotationsOfType:` when passing `PSPDFAnnotationTypeAll`. If one or more annotations could not
/// be deleted, this method will return `false`. This might be the case for form annotations or other objects that return `false`
/// for `isDeletable`.
- (BOOL)removeAnnotations:(NSArray<PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options NS_SWIFT_NAME(remove(annotations:options:));

/// Returns annotations for a specific `pageIndex`. Page starts at 0.
///
/// Returns an empty array if there are no matching annotations on the given `pageIndex`, or if `pageIndex` is invalid.
- (NSArray<__kindof PSPDFAnnotation *> *)annotationsForPageAtIndex:(PSPDFPageIndex)pageIndex type:(PSPDFAnnotationType)type;

/// Returns all annotations in this document.
/// Will not add key entries for pages without annotations.
///
/// @note To check for all annotations, but not links or forms, you will want to use `PSPDFAnnotationTypeAll&~(PSPDFAnnotationTypeLink|PSPDFAnnotationTypeWidget)` (Objective-C) or `PSPDFAnnotationType.All.subtract([.Link, .Widget])` (Swift).
/// @warning Parsing annotations can take some time. Can be called from a background thread.
- (NSDictionary<PSPDFDocumentPageNumber, NSArray<__kindof PSPDFAnnotation *> *> *)allAnnotationsOfType:(PSPDFAnnotationType)annotationType;

/// Returns true if the document contains annotations.
/// This scans the document in an efficient way and exits early as soon as an annotation was found.
///
/// @note This call checks for all annotation types except Link and Widget (Forms).
/// Annotations that are soft-deleted will be ignored.
///
/// Internally, this method simply calls `annotationsForPageAtIndex:type:` and stops as soon as annotations within the filter criteria are found.
@property (nonatomic, readonly) BOOL containsAnnotations;

@end

@interface PSPDFDocument (AnnotationSaving)

/// Called before the document starts to save annotations. Use to save any unsaved changes.
PSPDF_EXPORT NSNotificationName const PSPDFDocumentWillSaveAnnotationsNotification NS_SWIFT_NAME (Document.willSaveAnnotations);

/// Tests if we can embed annotations into this PDF. Certain PDFs (e.g. with encryption, or broken xref index) are readonly.
///
/// @note Only evaluates the first file if multiple files are set.
/// @warning This might block for a while, the PDF needs to be parsed to determine this.
@property (readonly) BOOL canEmbedAnnotations;

/// Returns YES if annotations can be saved, either in the PDF or in an external file.
/// Also returns YES when one of the `documentProviders` is not using the default annotation provider.
///
/// @note This largely depends on `canEmbedAnnotations` and `annotationSaveMode`.
@property (readonly) BOOL canSaveAnnotations;

/// Controls if and where annotations will be saved.
/// The default is `PSPDFAnnotationSaveModeEmbeddedWithExternalFileAsFallback`.
/// To prevent data loss, annotation editing will be disabled in the UI if this is set to `PSPDFAnnotationSaveModeDisabled`.
///
/// @note PSPDFKit automatically saves the document for various events. See `autosaveEnabled` in `PDFConfiguration`.
@property (atomic) PSPDFAnnotationSaveMode annotationSaveMode;

/// `NSUserDefaults` key for the default global annotation author name.
PSPDF_EXPORT NSString *const PSPDFDocumentDefaultAnnotationUsernameKey;

/// Default annotation user name for new annotations.
///
/// This property is initialized to the value stored in `UserDefaults.standard` under the
/// `PSPDFDocumentDefaultAnnotationUsernameKey`. If no value is stored in user defaults, then this property
/// will initially be:
///
/// - nil on iOS 16 and later
/// - based on the device name on iOS 15 and earlier
/// - the same as the user account name on Mac Catalyst
///
/// Written as the "T" (title/user) property of newly created annotations.
///
/// This value is also used by `NoteAnnotationViewController` to determine
/// if comments and reviews were left by the current user.
@property (atomic, copy, nullable) NSString *defaultAnnotationUsername;

/// Annotation write options.
typedef NSString *PSPDFAnnotationWriteOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(Document.AnnotationWriteOption);

/// Contains the boxed `PSPDFAnnotationType` to control appearance stream generation for each type.
PSPDF_EXPORT PSPDFAnnotationWriteOption const PSPDFAnnotationWriteOptionGenerateAppearanceStreamForType;

/// Allows control over what annotation should get an AP stream.
/// AP (Appearance Stream) generation takes more time but will maximize compatibility with PDF Viewers that don't implement the complete spec for annotations.
/// The default value for this dict is `@{PSPDFAnnotationWriteOptionGenerateAppearanceStreamForType: @(PSPDFAnnotationTypeFreeText|PSPDFAnnotationTypeInk|PSPDFAnnotationTypePolygon|PSPDFAnnotationTypePolyLine|PSPDFAnnotationTypeLine|PSPDFAnnotationTypeSquare|PSPDFAnnotationTypeCircle|PSPDFAnnotationTypeStamp|PSPDFAnnotationTypeWidget)}`
@property (atomic, copy, nullable) NSDictionary<PSPDFAnnotationWriteOption, NSNumber *> *annotationWritingOptions;

/// Returns YES if there are unsaved annotations.
///
/// @note This might not include unsaved open annotation creation operations, like a partial drawing. First set `pdfController.annotationStateManager.state = nil` to make sure you're not in an editing mode before evaluating this.
@property (nonatomic, readonly) BOOL hasDirtyAnnotations;

@end

@interface PSPDFDocument (Rendering)

/// Renders the page or a part of it with default display settings into a new image.
///
/// @param pageIndex     The index of the page that will be rendered. Starts at 0.
/// @param size          The size of the page, in pixels, if it was rendered without clipping.
/// @param clipRect      A rectangle, relative to size, that specifies the area of the page that should be rendered. CGRectZero = automatic.
/// @param annotations   Annotations that should be rendered with the view.
/// @param options       Dictionary with options that modify the render process (see PSPDFRenderOption). Will be merged with renderOptions of the document, with options taking precedence over renderOptions.
/// @param error         Returns an error object. (Then image will be nil).
/// @return              A new UIImage with the rendered page content.
- (nullable UIImage *)imageForPageAtIndex:(PSPDFPageIndex)pageIndex size:(CGSize)size clippedToRect:(CGRect)clipRect annotations:(nullable NSArray<PSPDFAnnotation *> *)annotations options:(nullable PSPDFRenderOptions *)options error:(NSError **)error;

/// Draw a page into a specified context. If for some reason renderPage: doesn't return a Render Receipt, an error occurred.
///
/// @param pageIndex     The index of the page that will be rendered. Starts at 0.
/// @param size          The size of the page, in pixels, if it was rendered without clipping.
/// @param clipRect      A rectangle, relative to size, that specifies the area of the page that should be rendered. CGRectZero = automatic.
/// @param annotations   Annotations that should be rendered with the view.
/// @param options       Dictionary with options that modify the render process (see PSPDFRenderOption). Will be merged with renderOptions of the document, with options taking precedence over renderOptions.
/// @return              YES if the operation succeeded, NO otherwise.
/// @note if `annotations` is nil, they will be auto-fetched. Add an empty array if you don't want to render annotations.
- (BOOL)renderPageAtIndex:(PSPDFPageIndex)pageIndex context:(CGContextRef)context size:(CGSize)size clippedToRect:(CGRect)clipRect annotations:(nullable NSArray<PSPDFAnnotation *> *)annotations options:(nullable PSPDFRenderOptions *)options error:(NSError **)error;

///  Set custom render options.
///
///  If the document is being displayed by a `PDFViewController` then you should call
///  `reloadData` on the view controller after updating the render options.
///
///  If you are working with primarily dark documents, consider setting the `backgroundFill`
///  property to `UIColor.blackColor` to work around white/gray hairlines at document borders.
///
///  @param options The render options to set. Will reset to defaults if set to nil.
///  @param type    The type you want to change. There are different render operation types.
- (void)setRenderOptions:(nullable PSPDFRenderOptions *)options type:(PSPDFRenderType)type;

///  Updates the render options with the instance returned from `block`. The `PSPDFRenderOptions`
///  passed to `block` is a copy, and modifying it does not affect the options in the document.
///
///  If the document is being displayed by a `PDFViewController` then you should call
///  `reloadData` on the view controller after updating the render options.
///
///  @param type     The type you want to change.
///  @param block    A closure that modifies the render options to apply to the given type.
- (void)updateRenderOptionsForType:(PSPDFRenderType)type withBlock:(void (^)(PSPDFRenderOptions *options))block;

///  Returns the render options for a specific type of operation.
///
///  @param type    The specific operation type.
///
///  @return The render options object. Guaranteed to always return a valid instance.
- (PSPDFRenderOptions *)renderOptionsForType:(PSPDFRenderType)type NS_SWIFT_NAME(renderOptions(forType:));

/// Set what annotations should be rendered. Defaults to `PSPDFAnnotationTypeAll`.
///
/// Non-rendered annotations will not be shown on pages and will not be exposed to accessibility
/// (e.g. VoiceOver) but will still be included in the annotation list (`AnnotationTableViewController`)
/// and may be shown on pages if selected using the annotation list.
///
/// After changing this, the render cache should be cleared using `PSPDFKit.SDK.shared.cache.remove(for: document)`.
/// If the document is displayed by a `PDFViewController` you should call `reloadData` on the view controller.
@property (atomic) PSPDFAnnotationType renderAnnotationTypes;

@end

/// APIs for importing and exporting Instant JSON from the document.
@interface PSPDFDocument (InstantJSON)

/// Generates Instant JSON representing current changes in the `documentProvider`.
///
/// @param documentProvider The document provider from which the JSON should be generated.
/// @param error A pointer to an NSError object that is set if an error occurred when generating the JSON.
/// @return The generated JSON as an `Data` object, or nil if there are no changes in the document currently, or on error occurred.
- (nullable NSData *)generateInstantJSONFromDocumentProvider:(PSPDFDocumentProvider *)documentProvider error:(NSError *__autoreleasing*)error;

/// Attempts to update the document provider applying the JSON received from the data provider.
///
/// The `lenient` parameter controls the behavior when the JSON contains (partially) invalid entries:
///
/// If `false` is passed, applying the JSON fails, and the document provider remains unmodified.
/// The error will contain a detailed report of all the inconsistencies that have been found in the JSON.
/// In general, this is the behavior you want to use in your production environment.
///
/// If `true` is passed as the `lenient` parameter, all data from the JSON that could still be used is applied to the document provider.
/// Inconsistencies that are encountered are merely logged as warnings, and the call will “succeed” as long as the JSON has more or less the expected structure.
/// This behavior is mostly useful during development, and should only be used in production with great caution.
/// It is meant as a “use at your own risk” last resort in data recovery scenarios after a call that passed `false` has failed, in order to preserve as much information from the JSON as possible.
///
/// @note A call where `lenient` is `true` can still fail!
/// One such occasion would be if the data provider does not contain a JSON object.
///
/// @param dataProvider The data provider from which to extract the JSON data. For common use cases,
/// see `PSPDFFileDataProvider` or `PSPDFDataContainerProvider`.
/// @param documentProvider The document provider (from the receiver’s `documentProviders` array to
/// which the JSON needs to be applied.
/// @param lenient Whether (partially) invalid JSON should still be applied. When in doubt, pass `false`!
/// @return `true` if application succeeded, else `false`.
- (BOOL)applyInstantJSONFromDataProvider:(id<PSPDFDataProviding>)dataProvider toDocumentProvider:(PSPDFDocumentProvider *)documentProvider lenient:(BOOL)lenient error:(NSError **)error;

@end

/// Creates annotations based on the text content. See `annotationsByDetectingLinkTypes:forPagesAtIndexes:options:progress:error:`.
typedef NS_OPTIONS(NSUInteger, PSPDFTextCheckingType) {
    /// Don't detect anything in text.
    PSPDFTextCheckingTypeNone = 0,
    /// Detect links in text.
    PSPDFTextCheckingTypeLink = 1 << 0,
    /// Detect phone numbers in text.
    PSPDFTextCheckingTypePhoneNumber = 1 << 1,
    /// Detect all available types in text.
    PSPDFTextCheckingTypeAll = NSUIntegerMax,
} NS_SWIFT_NAME(TextCheckingType);

@interface PSPDFDocument (Metadata)

/// The document’s user-facing title.
///
/// If the `PDFConfiguration` property `allowToolbarTitleChange` is enabled, then a
/// `PDFViewController` will sets its title to the title of the current document.
/// The title will then be shown in the navigation bar.
///
/// If this is not set programmatically, PSPDFKit looks for a title in the PDF metadata.
/// If there's no metadata, the file name is used. ".pdf" endings will be removed either way.
///
/// @note Can be set to a custom value, in that case this overrides the PDF metadata.
/// Custom titles don't get saved into the PDF.
/// Setting the custom title to nil will again use the predefined PDF contents.
@property (nonatomic, copy, nullable) NSString *title;

/// Whether the title has been parsed from the PDF file.
///
/// Title might need to parse the file and is potentially slow.
/// Use this to check if title is loaded and access title in a thread if not.
@property (readonly, getter=isTitleLoaded) BOOL titleLoaded;

/// Returns a pre-set attribute set for easier Spotlight integration. Thumbnail rendering is optional and might take some time.
///
/// @param renderThumbnail Specifies whether the thumbnail should be rendered and included in the attribute set.
/// @return An attribute set with properties set to match the PDFs metadata, as available. This does not contain the document's text content. If the document is not a valid PDF, the method returns nil.
/// @note Because this method might take a nontrivial amount of time to render the thumbnail image, you should call it from a background thread.
- (nullable CSSearchableItemAttributeSet *)searchableItemAttributeSetWithThumbnail:(BOOL)renderThumbnail;

/// The methods in this section provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: - Subclassing Hooks

/// Use this to use specific subclasses instead of the default PSPDF* classes.
/// e.g. add an entry of `PSPDFAnnotationManager.class` / `MyCustomAnnotationManager.class` to use the custom subclass.
/// (`MyCustomAnnotationManager` must be a subclass of `PSPDFAnnotationManager`)
///
/// @throws an exception if the overriding class is not a subclass of the overridden class.
/// @note Does not get serialized when saved to disk. Only set from the main thread, before you first use the object.
/// Set up your class overrides before calling any other method on the document.
- (void)overrideClass:(Class<PSPDFOverridable>)builtinClass withClass:(nullable Class)subclass;

/// Hook to modify/return a different document provider.
/// Called each time a documentProvider is created. (Which is usually on first access, and cached afterwards.)
///
/// During `Document` lifetime, document providers might be created at any time,
/// lazily, and destroyed when memory is low.
///
/// This might be used to change the delegate of the `PSPDFDocumentProvider`.
///
/// @warning: If `reloadDocumentProvider:dataProvider:` is used, this must return the same document provider as passed in. Modifying properties is allowed.
- (PSPDFDocumentProvider *)didCreateDocumentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Register a block that is called in `didCreateDocumentProvider:`
///
/// @warning This needs to be set very early, before the document providers have been created.
/// (Thus, before accessing any properties like pageCount or setting it to the view controller.)
@property (nonatomic, copy, nullable) void (^didCreateDocumentProviderBlock)(PSPDFDocumentProvider *documentProvider);

/// Override to customize file name for the send via email feature.
- (nullable NSString *)fileNameForIndex:(PSPDFFileIndex)fileIndex;

@end

// MARK: - Measurements

@interface PSPDFDocument ()

/// The currently active `measurementScale` settings. This value is used as the default measurement scale when creating new measurement annotations.
@property (nonatomic) PSPDFMeasurementScale *measurementScale;

/// Currently active `measurementPrecision` setting. This value is used as the default measurement precision when creating new measurement annotations.
@property (nonatomic) PSPDFMeasurementPrecision measurementPrecision;

@end

// MARK: - Advanced

@interface PSPDFDocument (Advanced)

/// To calculate pages between multiple document providers.
- (PSPDFPageIndex)relativePageIndexForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Page binding describes the side on which a book would have its binding. It is used
/// to describe the scroll direction and page layout in various views through out the
/// framework.
///
/// A page binding of `PSPDFPageBindingRightEdge` usually is found on PDFs with right
/// to left writing systems as their main content, such as Arabic and Hebrew. Some
/// languages such as Chinese, Japanese, and Korean are sometimes written vertically
/// and right to left. For example, this is common with manga.
///
/// If you are not familiar with the differences between right-to-left (RTL/R2L) and
/// left-to-right (LTR/L2R) writing systems, imagine a stack of paper. If you want
/// to create a book out of this stack, you can add a binding either on the left or
/// on the right side of the stack. If the writing on the pages has a RTL reading direction
/// you would usually add the binding on the right side, if it has a LTR reading direction,
/// you would usually add the binding on the left. This property controls exactly this,
/// as a PDF is just a stack of pages.
///
/// The default value is read from the PDF and is set to `PSPDFPageBindingUnknown`
/// if the PDF does not provide this value, which will make the UI fall back to a default
/// page layout.
///
/// You can set this property to force a specific page binding on a document.
///
/// @note If you set this property, make sure to call `reloadData` on any `PDFViewController`
/// currently displaying this document.
@property (nonatomic) PSPDFPageBinding pageBinding;

/// Attached PSPDFKit singleton instance.
@property (nonatomic, readonly) PSPDFKitGlobal *pspdfkit;

@end

@interface PSPDFDocument (JavaScript)

/// Load document-level JavaScript actions.
- (BOOL)loadDocumentLevelJavaScriptActionsWithError:(NSError **)error;

@end

@interface PSPDFDocument (ConflictResolution)

/// Performs conflict resolution on the provided data provider and updates internal
/// document state and caches.
///
/// @note Passing `PSPDFFileConflictResolutionSave` does nothing if a file copy is not
/// currently available on the data provider (`isConflictResolutionAvailable == NO`).
///
/// @param dataProvider The document's data provider that detected the file change.
/// @param resolution The conflict resolution option that should be performed.
/// @param error An optional error describing the failure.
/// @return YES, if the resolution was successful and no otherwise.
- (BOOL)resolveFileConflictForDataProvider:(id<PSPDFCoordinatedFileDataProviding>)dataProvider withResolution:(PSPDFFileConflictResolution)resolution error:(NSError * __autoreleasing *)error;

@end

/// Delegate to receive events regarding `Document`.
///
/// This delegate offers callbacks for custom actions after save events.
PSPDF_PROTOCOL_SWIFT(PDFDocumentDelegate)
@protocol PSPDFDocumentDelegate<NSObject>

@optional

/// PDF files can contain actions to other PDF files (`PSPDFRemoteGoToAction`).
/// Usually, these are attached to link annotations, but actions can also be connected to outline or forms.
///
/// PSPDFKit automatically tries to find the linked files based on the relative path.
/// There are also built-in tokens such as `Documents`, `Cache`, `Library`, `Bundle` and `PSBundle`
/// that help to navigate inside the typical iOS/macOS application folder structure.
///
/// This delegate allows custom tokens to be resolved, such as /MyAppToken.
/// This delegate will only get called for unknown tokens, not any built-in ones.
///
/// @see `PSPDFDocumentProvider resolveTokenizedPath:alwaysLocal:`
///
/// Return nil if the token cannot be resolved.
- (NSString *)pdfDocument:(PSPDFDocument *)document resolveCustomAnnotationPathToken:(NSString *)pathToken;

/// Called after saving was successful.
/// If document wasn't modified, delegate will not be called.
///
/// This is called in response to `Document.save(options:)` or `Document.save(options:completion:)`, which saves
/// changes like editing annotations. This includes auto-saving from `PDFViewController`. On the other hand, the
/// document editor performs structural operations like reordering pages and uses a different saving mechanism.
/// Therefore, this delegate method is not called when saving using `PDFDocumentEditor` or the document editor UI.
///
/// @warning Might be called from a background thread.
- (void)pdfDocumentDidSave:(PSPDFDocument *)document;

/// Called after saving failed.
///
/// @warning Might be called from a background thread.
- (void)pdfDocument:(PSPDFDocument *)document saveDidFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
