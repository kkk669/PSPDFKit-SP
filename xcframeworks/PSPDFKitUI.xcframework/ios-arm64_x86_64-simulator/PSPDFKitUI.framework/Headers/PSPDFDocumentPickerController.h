//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSearchableTableViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocumentPickerController, PSPDFDocument, PSPDFLibrary, PSPDFDocumentPickerIndexStatusCell;

/// Document selector delegate.
PSPDF_PROTOCOL_SWIFT(PDFDocumentPickerControllerDelegate)
@protocol PSPDFDocumentPickerControllerDelegate<NSObject>

/// Called when a document cell has been selected in the document picker.
///
/// @param controller The document picker controller where the selection happened.
/// @param document The document that has been selected.
/// @param pageIndex Is usually 0, unless a search result from the FTS engine, that points to a specific page, was tapped.
/// @param searchString The search term that was entered while this document has been selected. Will be nil if search was not active.
- (void)documentPickerController:(PSPDFDocumentPickerController *)controller didSelectDocument:(PSPDFDocument *)document pageIndex:(PSPDFPageIndex)pageIndex searchString:(nullable NSString *)searchString;

@optional

/// Called right before search begins.
- (void)documentPickerControllerWillBeginSearch:(PSPDFDocumentPickerController *)controller;
/// Called when search did begin.
- (void)documentPickerControllerDidBeginSearch:(PSPDFDocumentPickerController *)controller;
/// Called right before search ends.
- (void)documentPickerControllerWillEndSearch:(PSPDFDocumentPickerController *)controller;
/// Called when search did end.
- (void)documentPickerControllerDidEndSearch:(PSPDFDocumentPickerController *)controller;

@end

/// Shows all documents available in the specified directory or the documents set directly.
/// By default this will enqueue all documents into the default `PSPDFLibrary` for FTS.
///
/// Uses a `UISearchController` internally. It displays results for both PDF text and annotations,
/// provided the library indexes both.
///
/// @note This controller should be presented embedded in a `UINavigationController`.
/// Failing to do so might lead to issues with the search UI.
PSPDF_CLASS_SWIFT(PDFDocumentPickerController)
@interface PSPDFDocumentPickerController : PSPDFSearchableTableViewController<UISearchDisplayDelegate, UISearchBarDelegate>

/// Returns an array of `Document`’s found in the `directoryName` directory.
+ (NSArray<PSPDFDocument *> *)documentsFromDirectory:(nullable NSString *)directoryName includeSubdirectories:(BOOL)includeSubdirectories;

/// Initializes a document picker controller for the specified directory.
///
/// @param directory The directory from which documents are to be retrieved for selection.
/// @param library The library in which the documents are to be indexed. This is optional but required if you want to use `fullTextSearchEnabled`.
/// @return An instance of `PSPDFDocumentPickerController`.
///
/// @warning Specifying a directory and a library with a `dataSource` set may result in the library's indexes being in an inconsistent state with the data source if the documents do not match those provided by the `dataSource`.
/// This is highly discouraged. IF you wish to use the picker controller for documents not already specified by the library's `dataSource`, create a new library at a separate path and pass that here.
- (instancetype)initWithDirectory:(nullable NSString *)directory includeSubdirectories:(BOOL)includeSubdirectories library:(nullable PSPDFLibrary *)library;

/// Initializes a document picker controller for the specified documents.
///
/// @param documents The documents available to be selected.
/// @param library The library in which the documents are to be indexed. This is optional but required if you want to use `fullTextSearchEnabled`.
/// @return An instance of `PSPDFDocumentPickerController`.
///
/// @warning Specifying documents and a library with a `dataSource` set may result in the library's indexes being in an inconsistent state with the data source if the documents do not match those provided by the `dataSource`.
/// This is highly discouraged. IF you wish to use the picker controller for documents not already specified by the library's `dataSource`, create a new library at a separate path and pass that here.
- (instancetype)initWithDocuments:(NSArray<PSPDFDocument *> *)documents library:(nullable PSPDFLibrary *)library NS_DESIGNATED_INITIALIZER;

/// Manually trigger library enqueueing. We automatically do that when the controller becomes visible.
- (void)enqueueDocumentsIfRequired;

/// Delegate for document selection and search callbacks.
@property (nonatomic, weak) IBOutlet id<PSPDFDocumentPickerControllerDelegate> delegate;

/// All `Document` objects.
@property (atomic, copy, readonly) NSArray<PSPDFDocument *> *documents;

/// Displayed path. Might be nil, if initialized with a number of documents.
@property (nonatomic, copy, readonly, nullable) NSString *directory;

/// Show document titles in the list. If set to NO, the file name is used instead. Defaults to NO, since getting the PDF document title can be slow.
@property (nonatomic) BOOL useDocumentTitles;

/// Enables section indexes. Defaults to YES.
@property (nonatomic) BOOL showSectionIndexes;

/// If disabled, documents will only be displayed once you start searching. Defaults to YES.
@property (nonatomic) BOOL alwaysShowDocuments;

/// Enable to perform full-text search on all documents. Defaults to YES.
///
/// @note To improve matching in large libraries, full text search is only performed after
/// at least 4 characters are entered in the search field.
@property (nonatomic) BOOL fullTextSearchEnabled;

/// If set to YES, will require an exact word match instead of an begin/end partial match. Defaults to NO.
///
/// @note This will forward the option via `PSPDFLibraryMatchExactWordsOnlyKey` to the `PSPDFLibrary`.
@property (nonatomic) BOOL fullTextSearchExactWordMatch;

/// Property is enabled if a FTS-Search is currently queued/running. KVO observable.
@property (nonatomic, readonly) BOOL isSearchingIndex;

/// Will show the actual pages and text preview instead of just the documents.
/// Only valid if `fullTextSearchEnabled` is enabled. Defaults to YES.
@property (nonatomic) BOOL showSearchPageResults;

/// Will show a preview text that presents the search term within its context.
/// Only valid if `fullTextSearchEnabled` is enabled. Defaults to YES.
@property (nonatomic) BOOL showSearchPreviewText;

/// Defaults to 600. A too high number will be slow.
/// Only valid if `fullTextSearchEnabled` is enabled.
@property (nonatomic) NSUInteger maximumNumberOfSearchResultsDisplayed;

/// Number of results found per document. Defaults to 10.
/// Only valid if `fullTextSearchEnabled` is enabled.
@property (nonatomic) NSUInteger maximumNumberOfSearchResultsPerDocument;

/// Maximum number of lines for search preview text. Defaults to 2.
/// The actual number of lines will be smaller if there's not enough preview text available.
/// Only valid if `fullTextSearchEnabled` is enabled.
@property (nonatomic) NSUInteger maximumNumberOfSearchPreviewLines;

/// The attached library, if any.
@property (nonatomic, readonly, nullable) PSPDFLibrary *library;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFDocumentPickerController (SubclassingHooks)

/// Called when the document picker status cell will be updated.
/// Override this method to customize the status cell.
- (void)updateStatusCell:(PSPDFDocumentPickerIndexStatusCell *)cell;

@end

NS_ASSUME_NONNULL_END
