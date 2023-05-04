//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFKit.h>

@class PSPDFDocumentEditor, PSPDFDocument, PSPDFEditingChange, PSPDFNewPageConfiguration, PSPDFDocumentSecurityOptions;

NS_ASSUME_NONNULL_BEGIN

typedef void (^PSPDFDocumentEditorSuccessBlock)(BOOL success, NSError *_Nullable error);
typedef void (^PSPDFDocumentEditorSaveBlock)(PSPDFDocument *_Nullable document, NSError *_Nullable error);
typedef void (^PSPDFDocumentEditorImportBlock)(NSArray<PSPDFEditingChange *> * _Nullable changes, NSError *_Nullable error);

/// Delegate that can be implemented to be notified of changes that the document editor performs.
PSPDF_PROTOCOL_SWIFT(PDFDocumentEditorDelegate)
@protocol PSPDFDocumentEditorDelegate<NSObject>

/// This delegate call is is called in response to a `reset` call and when external document changes are detected.
/// After receiving this call, you should remove any cached data and do a full UI reload.
///
/// @param editor A reference to the document editor responsible for the changes.
- (void)documentEditorRequestsFullReload:(PSPDFDocumentEditor *)editor;

@optional

/// Called whenever a document operation performs incremental changes.
/// Use the provided `PSPDFEditingChange` objects to update any attached UI or do a full reload.
///
/// This call is not needed, if you instead use the changes retuned by the individual update methods.
///
/// @param editor A reference to the document editor responsible for the changes.
/// @param changes An array of changes that can be used for incremental UI updates.
- (void)documentEditor:(PSPDFDocumentEditor *)editor didPerformChanges:(NSArray<PSPDFEditingChange *> *)changes;

@end

/// Manages document editing. Supports operations such as remove, move, rotate and add page.
///
/// @note This class requires the Document Editor component to be enabled for your license.
PSPDF_CLASS_SWIFT(PDFDocumentEditor)
@interface PSPDFDocumentEditor : NSObject<PSPDFOverridable>

/// Starts an editing session on the document or a new blank editing session.
///
/// @param document The document used to initialize the document editor or `nil`.
/// If nil, the document editor is initialized with zero pages. If a document is used,
/// it must be a valid unlocked document. The changes won't be visible on the document
/// until the document editor is saved.
- (nullable instancetype)initWithDocument:(nullable PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// Creates a document editor without a document. Use this to create a new document from scratch.
///
/// @note You need to add at least one page before saving with `saveToPath:withCompletionBlock:`.
/// An empty document has 0 pages, which does not constitute a valid PDF document.
/// @see initWithDocument:
- (instancetype)init;

/// Reference to the backing document. Will never be nil if `initWithDocument:` with a document was used.
///
/// @see `initWithDocument:`
@property (nonatomic, readonly, nullable) PSPDFDocument *document;

/// Allows you to set security options for saving.
@property (nonatomic, readwrite, nullable) PSPDFDocumentSecurityOptions *securityOptions;

/// Adds a document editor delegate to the subscriber list.
///
/// @note Delegates are weakly retained, but be a good citizen and manually deregister.
- (void)addDelegate:(id<PSPDFDocumentEditorDelegate>)delegate;

/// Removes a document editor delegate from the subscriber list.
- (BOOL)removeDelegate:(id<PSPDFDocumentEditorDelegate>)delegate;

// MARK: Page info

/// Returns the page count of the edited Document.
/// If you remove or add pages, this will reflect that change.
@property (nonatomic, readonly) PSPDFPageCount pageCount;

/// Returns the page size, already rotated.
- (CGSize)pageSizeForPageAtIndex:(PSPDFPageIndex)pageIndex;

// MARK: Operations


/// Uses the given configuration to insert multiple pages in the specified range at once.
///
/// As this is an insertion, any pages in the document at or after the `range.location` are moved back
/// by `range.length` to make room for the new pages. As a side effect, this behavior disqualifies use
/// of this method for the purpose of duplicating and modifying a page of the receiver’s `document`. If
/// this is your goal, please use `duplicatePages:` and the appropriate modification calls instead, or
/// (if you absolutely must) make a copy of the `document` in order to create a suitable
/// `PSPDFNewPageConfiguration`.
///
/// @note If called inside an edition group (see -[PSPDFDocumentEditor groupUpdates:completion:]), the
/// delegates are not going to be called and the return value will be an empty array.
///
/// @param range           The range in which the new pages should be added. The provided range's
/// `location` must be within bounds of the document's page count.
/// @param configuration   The configuration used to create each one of the new pages.
///
/// @return Array of `PSPDFEditingChange` objects describing the changes performed by this method.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should call
/// this method on the main thread and apply the resulting changes (or perform a refresh) to your UI
/// immediately after the method returns. This will ensure that the UI state and the document editor
/// model representation are always in sync.
- (NSArray<PSPDFEditingChange *> *)addPagesInRange:(NSRange)range withConfiguration:(PSPDFNewPageConfiguration *)configuration;

/// Aggregates all the changes made by the actions inside the block, applies them as a single action, and notifies the delegates.
///
/// Call `updatesCompletedBlock` when you're done describing the updates to be performed.
///
/// @param updateBlock     Block that groups all the actions to be performed by the editor.
- (void)groupUpdates:(void (^)(void (^)(BOOL completed)))updateBlock;

/// Combines all editing actions inside `updateBlock` into one.
///
/// Call `updatesCompletedBlock` when you're done describing the updates to be performed.
///
/// @note If a `completionBlock` is provided the editor's delegates are not going to be called, and the aggregated updates will be delivered on the completion block.
/// @note If this method is called from within a group, the completion block is not going to be called.
///
/// @param updateBlock     Block that groups all the actions to be performed by the editor.
/// @param completionBlock Block to be executed when the editor finishes the changes. Parameter is a list of `PSPDFEditingChange`.
- (void)groupUpdates:(void (^)(void (^)(BOOL completed)))updateBlock completion:(nullable void (^)(NSArray<PSPDFEditingChange *> * changes))completionBlock;

/// Moves pages at the given page indexes to a new page index.
///
/// @note If called inside an edition group (see -[PSPDFDocumentEditor groupUpdates:completion:]), returns an empty array and the delegates are not called.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should call this method on the main thread and apply the resulting changes (or perform a refresh) to your UI immediately after the method returns. This will ensure that the UI state and the document editor model representation are always in sync.
- (NSArray<PSPDFEditingChange *> *)movePages:(NSIndexSet *)pageIndexes to:(PSPDFPageIndex)destination;

/// Removes pages at the given page indexes.
///
/// @note If called inside an edition group (see -[PSPDFDocumentEditor groupUpdates:completion:]), returns an empty array and the delegates are not called.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should call this method on the main thread and apply the resulting changes (or perform a refresh) to your UI immediately after the method returns. This will ensure that the UI state and the document editor model representation are always in sync.
- (NSArray<PSPDFEditingChange *> *)removePages:(NSIndexSet *)pageIndexes;

/// Duplicates pages at the given page indexes. The duplicated pages will be inserted exactly after the original page.
///
/// @note If called inside an edition group (see -[PSPDFDocumentEditor groupUpdates:completion:]), returns an empty array and the delegates are not called.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should call this method on the main thread and apply the resulting changes (or perform a refresh) to your UI immediately after the method returns. This will ensure that the UI state and the document editor model representation are always in sync.
- (NSArray<PSPDFEditingChange *> *)duplicatePages:(NSIndexSet *)pageIndexes;

/// Rotates the pages with the given page indexes.
/// Rotation can be 0, 90, 180 and 270. Clockwise and counter-clockwise (depending on the sign).
/// The rotation is added to the current page rotation value.
///
/// @note If called inside an edition group (see -[PSPDFDocumentEditor groupUpdates:completion:]), returns an empty array and the delegates are not called.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should call this method on the main thread and apply the resulting changes (or perform a refresh) to your UI immediately after the method returns. This will ensure that the UI state and the document editor model representation are always in sync.
- (NSArray<PSPDFEditingChange *> *)rotatePages:(NSIndexSet *)pageIndexes rotation:(NSInteger)rotation;

/// Returns the rotation value for the page at the given index.
///
/// Rotation can be 0, 90, 180 and 270. Clockwise (positive sign) and counter-clockwise (negative sign).
- (NSInteger)rotationForPageAtIndex:(PSPDFPageIndex)pageIndex;

// MARK: Undo / redo

/// Undoes the last action and returns the changes' descriptions.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should call this method on the main thread and apply the resulting changes (or perform a refresh) to your UI immediately after the method returns. This will ensure that the UI state and the document editor model representation are always in sync.
- (nullable NSArray<PSPDFEditingChange *> *)undo;

/// Redo the last undo and returns information about what changed.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should call this method on the main thread and apply the resulting changes (or perform a refresh) to your UI immediately after the method returns. This will ensure that the UI state and the document editor model representation are always in sync.
- (nullable NSArray<PSPDFEditingChange *> *)redo;

/// Checks if you can redo.
@property (nonatomic, readonly) BOOL canRedo;

/// Checks if you can undo.
@property (nonatomic, readonly) BOOL canUndo;

/// Discards all changes and clears the undo and redo stack.
/// Calls documentEditor:didPerformChanges: with a `nil` `changes array.
///
/// @note Any cached state on the caller side should be reset after calling this.
- (void)reset;

// MARK: Save

/// Specifies if it is possible to save document editor changes into the current document.
///
/// This is possible if the document is backed by a single data provider. If the document if backed by
/// a PDF file (file data provider), the file needs to be at a writable location and the document can't
/// use external annotation saving (see `Document.annotationSaveMode`). If a different data provider is used
/// it needs to support the optional data sink functionality (via `replaceContents(with:)`).
///
/// `save(completionBlock:)` can only be used if this property evaluates to `true`.
/// `save(to:, withCompletionBlock:)` and `save(toPath:, withCompletionBlock:)` can be used in any case.
@property (nonatomic, readonly) BOOL canSave;

/// Overwrites the document PDF file and clears the document caches.
///
/// @note If the `Document` referenced by `document` is currently displayed on a `PDFViewController`,
/// you should call `reloadData` on the `PDFViewController` after saving.
/// @warning Don't make any assumptions about the execution context of `block`. Can be called on a background queue.
/// @param block If successful, returns a reference to the current document with cleared caches. Otherwise an error will be available.
/// @see `canSave`
- (void)saveWithCompletionBlock:(nullable PSPDFDocumentEditorSaveBlock)block;

/// Saves the modified document to a new PDF file at `path`.
///
/// @note This does not affect the `Document` referenced by `document`.
/// @warning Don't make any assumptions about the execution context of `block`. Can be called on a background queue.
/// @param path The destination path for the new document. Should be a directory to which the application can write to.
/// @param block If successful, returns a new document that is configured for the given `path`. Otherwise an
/// error will be available.
- (void)saveToPath:(NSString *)path withCompletionBlock:(nullable PSPDFDocumentEditorSaveBlock)block;

/// Saves the modified document to a data sink.
///
/// @note This does not affect the `Document` referenced by `document`.
/// @warning Don't make any assumptions about the execution context of `block`. Can be called on a background queue.
/// @param dataSink The destination data sink for the new document.
/// @param block If successful, returns success of the write operation as boolean. Otherwise an error will be available.
- (void)saveToDataSink:(id<PSPDFDataSink>)dataSink withCompletionBlock:(nullable PSPDFDocumentEditorSuccessBlock)block;

// MARK: Import and Export

/// Saves the pages listed in `pageIndexes` to a new PDF at `path`.
///
/// @note This does not affect the `Document` referenced by `document`.
///
/// @warning Don't make any assumptions about the execution context of `block`. Can be called on a background queue.
/// @param pageIndexes A set of indexes corresponding to pages that should copied to the new document. All indexes need to be bounded by `pageCount`.
/// @param path The destination path for the new document. Should be a directory to which the application can write to.
/// @param block If successful, returns a new document that is configured for the given `path`. Otherwise an
/// error will be available.
- (void)exportPages:(NSIndexSet *)pageIndexes toPath:(NSString *)path withCompletionBlock:(nullable PSPDFDocumentEditorSaveBlock)block;

/// Saves the pages listed in `pageIndexes` to a data sink.
///
/// @note This does not affect the `Document` referenced by `document`.
///
/// @warning Don't make any assumptions about the execution context of `block`. Can be called on a background queue.
/// @param pageIndexes A set of indexes corresponding to pages that should copied to the new document. All indexes need to be bounded by `pageCount`.
/// @param dataSink The destination data sink for the new document.
/// @param block If successful, returns success of the write operation as boolean. Otherwise an error will be available.
- (void)exportPages:(NSIndexSet *)pageIndexes toDataSink:(id<PSPDFDataSink>)dataSink withCompletionBlock:(nullable PSPDFDocumentEditorSuccessBlock)block;

/// Imports pages from a given `document` into the currently edited document and returns a progress.
///
/// As with any other document editor changes, the added pages are not preserved until a document editor save is invoked.
/// The provided documents will be copied internally and preserved until a save is invoked or the document editor gets deallocated.
///
/// @note If called inside an edition group (see -[PSPDFDocumentEditor groupUpdates:completion:]), the delegates are not going to be called and the first parameter on the completion block will be an empty array.
///
/// @note If the document editor is used to drive a UI (e.g, a `UICollectionView`), you should use the main queue as the `queue` parameter of this method (or pass in `nil`). Use the completion block or delegate calls to apply the resulting changes (or perform a refresh). This will ensure that the UI state and the document editor model representation are always in sync.
///
/// @param index The insertion index for the new `sourceDocument` pages amongst the current pages.
/// @param sourceDocument The source document. Needs to be a `fileURL` backed `Document`.
/// @param block A optional block, called when the import completes. Invoked on the provided queue.
/// @param queue The queue that should be used to invoke the `block` and delegate calls on. If `nil`, the main queue will be used.
- (NSProgress *)importPagesTo:(PSPDFPageIndex)index fromDocument:(PSPDFDocument *)sourceDocument withCompletionBlock:(nullable PSPDFDocumentEditorImportBlock)block queue:(nullable dispatch_queue_t)queue;

// MARK: Rendering

/// Returns the rendered page as an `UIImage` with custom scale.
- (nullable UIImage *)imageForPageAtIndex:(PSPDFPageIndex)pageIndex size:(CGSize)size scale:(CGFloat)scale;

@end

NS_ASSUME_NONNULL_END
