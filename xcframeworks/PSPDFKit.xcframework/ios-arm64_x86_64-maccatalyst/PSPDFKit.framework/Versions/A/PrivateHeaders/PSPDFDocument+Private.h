//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFMetadataName.h>

#if defined(__cplusplus)
#include <mutex>
#endif

@class PSPDFPage, PSPDFPageInfo, PSPDFResourceManager, PSPDFRedactionTracker;
@protocol PSPDFJSPlatformDelegate;

NS_ASSUME_NONNULL_BEGIN

/// Notification that is sent before document saving starts.
/// Similar to the public PSPDFDocumentWillSaveAnnotationsNotification, however no thread guarantees!
PSPDF_EXPORT NSNotificationName const PSPDFDocumentWillSaveNotification NS_SWIFT_NAME (Document.willSaveNotification);

/// This notification is triggered whenever the core document is loaded and attached
/// to the document posting this notification.
PSPDF_EXTERN NSNotificationName const PSPDFDocumentDidLoadCoreDocumentNotification;

/// This notification is triggered whenever the document is saved either to disk or to the attached data providers.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFDocumentDidSaveNotification NS_SWIFT_NAME (Document.didSaveNotification);

/// This notification is triggered when saving fails. Error is in the "error" key of the user dict.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFDocumentSaveDidFailNotification NS_SWIFT_NAME (Document.saveDidFailNotification);

/// This notification is triggered when the creation of new document provider is finished.
///
/// @note This notification can be called on a background thread when a document's validity, that does not have any document providers created, is checked.
/// For example: When PSPDFLibrary accesses the document on a background thread.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFDocumentDidCreateDocumentProvidersNotification;

/// This notification is triggered when the existing document providers of a document are destroyed.
/// This notification is used by `testDocumentMemoryFreedOnReceivingMemoryWarning` to verify that the
/// memory is being freed.
///
/// @note Threading of this notification isn' guaranteed. This notification can be called on a background
/// thread when the document providers of a document are released on receiving memory warning notification.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFDocumentDidDestroyDocumentProvidersNotification;

/// Special notification that is sent when a subset of document provider changes.
/// This can be used for intermediary caches to clear content that involves page rendering.
/// `object` an array of new document provider objects.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFDocumentDidChangeDocumentProvidersNotification NS_SWIFT_NAME (Document.didChangeDocumentProviders);

/// Sent before rendering an image via imageForPageAtIndex: starts.
/// Object is the document, userInfo contains additional render data.
PSPDF_APP_EXPORT NSNotificationName const PSPDFDocumentWillStartRenderingNotification;

/// Sent after rendering finishes.
/// Object is the document, userInfo contains additional render data.
PSPDF_APP_EXPORT NSNotificationName const PSPDFDocumentDidFinishRenderingNotification;

@interface PSPDFDocument () <PSPDFOverrideProvider>

/// Returns YES of pageInfo for page is available
- (BOOL)hasPageInfoForPageAtIndex:(PSPDFPageIndex)pageIndex;

- (nullable PSPDFPageInfo *)pageInfoForPageIndexNoFetching:(PSPDFPageIndex)pageIndex;

/// Makes a search beginning from page 0 for the nearest pageInfo.
/// Does not calculate/block the thread.
- (nullable PSPDFPageInfo *)nearestPageInfoForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Receives the page for the page index.
/// Will raise an exception if index is out of bounds. Indices are zero-based.
- (nullable PSPDFPage *)pageAtIndex:(PSPDFPageIndex)pageIndex;

/// Force UID generation.
- (void)generateUIDIfNeeded;

/// Returns a hash that is specific to the underlying data of the document provider.
///
/// @note A document provider might have unsaved changes like edited annotations which
/// are therefore not part of the underlying data and thus to not have an impact
/// on the hash returned.
@property (nonatomic, readonly) NSUInteger dataHash;

/// Returns file name without ending.
@property (nonatomic, readonly, nullable) NSString *fileNameWithoutType;

/// Any view controllers that currently have this document set.
/// Used for freeing up resources when the document is not being used.
///
/// This is also currently used to output a warning if the document is being set on multiple view controllers.
/// This is not recommended because a few things don’t work correctly. The plan is to lift
/// this restriction at some point. https://github.com/PSPDFKit/PSPDFKit/issues/21434
///
/// Controllers are referenced weakly.
- (void)connectViewController:(PSPDFViewController *)controller;

/// Disconnect a view controller that presents this document.
- (void)disconnectViewController:(PSPDFViewController *)controller;

/// Returns the number of connected view controllers that display the document.
- (NSInteger)numberOfConnectedViewControllers;

/// Returns a strongly referenced list of all view controllers.
- (NSArray<PSPDFViewController *> *)connectedViewControllers;

/// Indicates if the core document has been loaded and basic data is available.
@property (nonatomic, readonly) BOOL isCoreDocumentLoaded;

/// Checks if the underlying files have unsaved changes that would need to be persisted
/// on disk in order to be able to restore the current state at a later point.
///
/// @note This checks the underlying documents / files. It does not take into account
/// things like dirty annotations that have not yet been synced with the document.
@property (nonatomic, readonly) BOOL hasUnsavedChanges;

/// Returns `true` if all annotations are stored inside PDF files.
@property (nonatomic, readonly) BOOL hasAllAnnotationsInsidePDFFile;

/// Returns the resource manager for the current document.
@property (nonatomic, readonly) PSPDFResourceManager *resourceManager;

/// Configures the platform delegate of the JavaScript executor.
- (void)configureJavaScriptPlatformDelegate:(id<PSPDFJSPlatformDelegate>)platformDelegate;

/// Update form fields via executing JavaScript.
- (BOOL)updateCalculatedFieldsWithError:(NSError **)error;

/// Returns the document level javascript objects, if any.
/// Once loaded we don't need to go down to pdfium so we don't lock.
@property (nonatomic, readonly) NSArray<NSString *> *documentLevelJavaScripts;

/// Returns the password used to `unlock` the document, if any
@property (nonatomic, readonly, nullable, copy) NSString *password;

/// Returns the permissions status of the PDF document. You have PSPDFDocumentPermissionsLevelNone status for an encrypted
/// document that you have not supplied either a valid user or owner password. For a document with no encryption, you
/// automatically have PSPDFDocumentPermissionsLevelOwner status.
@property (nonatomic, readonly) PSPDFDocumentPermissionsLevel permissionsLevel;

/// Validates a document. Returns YES if `isValid` is true and the document is unlocked.
- (BOOL)validateDocument:(NSError **)error;

/// Whether annotations are already loaded.
- (BOOL)hasLoadedAnnotationsForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Returns an operation that loads annotations.
- (nullable NSOperation *)loadAnnotationsOperationForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// @param legacy      Use old path when calling this directly, from outside a render queue.
- (nullable UIImage *)imageForPageAtIndex:(PSPDFPageIndex)pageIndex size:(CGSize)size clippedToRect:(CGRect)clipRect scale:(CGFloat)scale annotations:(nullable NSArray<PSPDFAnnotation *> *)annotations options:(nullable PSPDFRenderOptions *)options usingLegacyAPI:(BOOL)legacy cancellationToken:(nullable NSNumber *)cancellationToken error:(NSError **)error;

- (NSString *)userFacingTitleUsingDocumentTitle:(BOOL)useDocumentTitle;

/// Returns YES if all data providers support secure coding.
- (BOOL)dataProvidersSupportSecureCoding;

/// Called when the metadata is changed for the specified key.
///
/// @param metadataName The key that was changed.
/// @param documentProviderIndex The index of the document provider for which the key was changed.
- (void)metadataChangedForName:(PSPDFMetadataName)metadataName forDocumentProviderAtIndex:(NSUInteger)documentProviderIndex;

/// Returns the state of the global `PSPDFSettingKeyFileCoordinationEnabled` key. Can be subclassed.
@property (nonatomic, class, readonly) BOOL useFileCoordination;

/// Checks if the receiver contains annotations of a type in the passed in bitmask.
///
/// @param type A `PSPDFAnnotationType` bitmask indicating which types are to be checked.
/// @param pageLimit The number of pages to check before returning. Pass in `0` to check all pages.
/// @return `true` if an annotation of the specified type is found, else `false`.
- (BOOL)containsAnnotationsOfType:(PSPDFAnnotationType)type pageLimit:(PSPDFPageIndex)pageLimit;

/// Checks, asynchronously, if the receiver contains annotations of a type in the provided bitmask, and reports progress.
///
/// @note Both the search itself and the progress/completion blocks are performed on a background thread.
///
/// @param annotationType      Bitmask for the type of annotations to look for in the document.
/// @param progressBlock       Called for every page in the document that's searched.
/// @param completionBlock     Called when the searching has finished.
- (void)lookForAnnotationsOfType:(PSPDFAnnotationType)annotationType withProgress:(void(^)(NSUInteger currentPageIndex, NSArray<PSPDFAnnotation *> *annotations, CGFloat progress, BOOL *stop))progressBlock completionBlock:(void(^)(NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *annotationsFound))completionBlock;

/// Override to perform additional actions during a save.
///
/// Invoked on the save queue after the annotation and data provider save has been performed,
/// but before any save notifications or callbacks are invoked. This call is also invoked inside
/// background task, to ensure it is executed even if the application is backgrounded.
///
/// @param savedAnnotations The list of changed annotations that have been saved (or synced to core). If any.
/// @param didSave Indicates whether data provider saves were successful (changes have been persisted).
/// @param error The current save error when passed in. Can be replaced with a new error, which is then passed on via notifications and callbacks, if appropriate.
/// @return The value of `didSave` or an updated value if the method implementation caused a change.
- (BOOL)queue_performAdditionalSaveActionsFor:(nullable NSArray<__kindof PSPDFAnnotation *> *)savedAnnotations didSave:(BOOL)didSave error:(NSError *__autoreleasing *)error;

/// Same as `fillCache` but allows using a block to return the document, for scenarios where the document is weak.
///
/// This is used when we fill the cache but want to cancel it if a different document is presented.
///
/// @param weakDocumentFetcher Block used to retrieve the weak document instance to work with.
/// @param jsLoadedBlock       Called when the JavaScript is loaded into the document so that it can be executed.
+ (void)fillCacheWithDocumentFetcher:(PSPDFDocument* (^_Nullable)(void))weakDocumentFetcher javaScriptLoadedBlock:(void (^_Nullable)(void))jsLoadedBlock;

/// Used to keep track of existing, created and deleted redactions in the document.
@property (nonatomic, readonly) PSPDFRedactionTracker *redactionTracker;

/// Checks if the all the document providers can be written to.
- (BOOL)canWriteToAllDocumentProviders;

/// Update the dirty state on the AppKit backed NSDocument.
- (void)updateAppKitDirtyState;

/// A set of known `DataProviding` classes.
@property (class, nonatomic, readonly) NSSet<Class> *knownDataProviderClasses;

/// Flag set during document editor updates. If data is loaded while this is set, bad things will happen.
/// There is no thread safety on this flag, which is possibly a bad thing.
/// See https://github.com/PSPDFKit/PSPDFKit/issues/24718 and https://github.com/PSPDFKit/PSPDFKit/issues/37325
@property (nonatomic) BOOL isPendingReloadFromDocumentEditor;

@end

@interface PSPDFDocument (BookmarksPrivate)

@property (nonatomic, readonly, getter=isCreatingBookmarkManager) BOOL creatingBookmarkManager;

@end

@interface PSPDFDocument (TextParserPrivate)

/// Checks if the text parser has already been loaded. Thread safe.
- (BOOL)hasLoadedTextParserForPageAtIndex:(PSPDFPageIndex)pageIndex;

@end

/// Since core is piling up stuff, we need to flush it from time to time when we are in tight loops.
/// This depends on the device and memory.
PSPDF_SDK_EXPORT NSUInteger PSPDFPageFlushThreshold(void) __attribute__((const, pure));

NS_ASSUME_NONNULL_END
