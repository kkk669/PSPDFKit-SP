//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBookmarkListDataSourceDelegate.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFBookmark.h>
#import <PSPDFKit/PSPDFBookmarkManager.h>
#import <PSPDFKit/PSPDFDocument.h>

NS_ASSUME_NONNULL_BEGIN

/// Manages a list of bookmarks.
///
/// @warning this class is intended to be used from the main thread, calling any
/// method or accessing a property from a non-main thread results in undefined
/// behavior.
PSPDF_SDK_CLASS_SWIFT(BookmarkListDataSource)
@interface PSPDFBookmarkListDataSource : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Allocates and initializes a new bookmark list data source for a given
/// document.
+ (instancetype)bookmarkListDataSourceWithDocument:(PSPDFDocument *)document;

/// Allocates and initializes a new bookmark list data source with a parent
/// bookmark list data source.
+ (instancetype)bookmarkListDataSourceWithParentBookmarkListDataSource:(PSPDFBookmarkListDataSource *)parentBookmarkListDataSource;

/// Initializes a new bookmark list data source for a given document.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// Initializes a new bookmark list data source with a parent bookmark list data
/// source. Bookmarks are loaded from the parent instead of a document, which in
/// general is much faster. Useful for example for implementing dedicated search
/// results, which need to access the same bookmarks.
- (instancetype)initWithParentBookmarkListDataSource:(PSPDFBookmarkListDataSource *)parentBookmarkListDataSource NS_DESIGNATED_INITIALIZER;

/// Useful to identify a specific data source and for debugging purposes. Setting
/// this property to a human readable identifier is recommended.
@property (nonatomic, nullable, copy) NSString *identifier;

/// Returns the document for which the bookmarks are managed by the receiver.
@property (nonatomic, readonly) PSPDFDocument *document;

/// Returns the parent bookmark list data source.
@property (nonatomic, nullable, readonly) PSPDFBookmarkListDataSource *parentBookmarkListDataSource;

/// The common init method.
- (void)commonInit NS_REQUIRES_SUPER;

/// The `delegate` is informed of any changes to the bookmark list, useful
/// primarily as a hook to update the UI.
@property (nonatomic, weak) id<PSPDFBookmarkListDataSourceDelegate> delegate;

/// The search string by which the pages are filtered. Set to `nil` by default,
/// which means no filtering.
@property (nonatomic, nullable, copy) NSString *searchString;

/// Returns the total number of all bookmarks.
@property (nonatomic, readonly) NSUInteger numberOfBookmarks;

/// Returns `true` if the bookmarks have been loaded at least once (i.e. method
/// `reloadBookmarks` called) otherwise returns `false`. Useful for showing a
/// loading indicator before first reload or block animations for the first reload.
@property (nonatomic, readonly) BOOL hasLoadedBookmarks;

/// Controls the sort order. Reordering is only allowed for
/// `PSPDFBookmarkManagerSortOrderCustom`.
@property (nonatomic) PSPDFBookmarkManagerSortOrder sortOrder;

/// Defines whether it is possible to add multiple bookmarks on the same page.
@property (nonatomic) BOOL allowMultipleBookmarksPerPage;

/// Returns the index for the given bookmark. Returns `NSNotFound` if the
/// bookmark isn't currently managed by this data source.
- (NSUInteger)indexForBookmark:(PSPDFBookmark *)bookmark;

/// Returns the indexes for the given bookmarks. If one of the bookmarks isn't
/// currently managed by this data source, it will be ignored.
- (NSIndexSet *)indexesForBookmarks:(NSArray<PSPDFBookmark *> *)bookmarks;

/// Returns the indexes for all bookmarks.
@property (nonatomic, readonly) NSIndexSet *indexesForAllBookmarks;

/// Returns a single bookmark at the given index. Throws `NSRangeException` if
/// `index` is not valid.
- (PSPDFBookmark *)bookmarkAtIndex:(NSUInteger)index;

/// Returns multiple bookmarks at the given `indexes`. Throws
/// `NSRangeException` if one of the `indexes` is not valid.
- (NSArray<PSPDFBookmark *> *)bookmarksAtIndexes:(NSIndexSet *)indexes;

/// Returns `true` if bookmark can be added for the page at `pageIndex`, otherwise
/// return `false`. Throws `NSRangeException` if `pageIndex` is not valid. Returns
/// `false` if bookmark already exists for that `pageIndex`. You can use this method
/// for example to enable/disable a "Bookmark this Page" button.
- (BOOL)canAddBookmarkForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Adds a bookmark for `pageIndex`. Throws `NSRangeException` if `pageIndex` is
/// not valid. Throws `NSGenericException` if bookmark for `pageIndex` already
/// exists.
- (PSPDFBookmark *)addBookmarkForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Returns `true` if bookmark at index can be deleted, otherwise returns
/// `false`. Convenience method for `canDeleteBookmarksAtIndexes:`.
- (BOOL)canDeleteBookmarkAtIndex:(NSUInteger)index;

/// Deletes a single bookmark at the given index. Convenience method for
/// `deleteBookmarksAtIndexes:`.
- (void)deleteBookmarkAtIndex:(NSUInteger)index;

/// Returns indexes for all bookmarks that can be deleted. Throws
/// `NSRangeException` if one of the indexes is not valid.
- (NSIndexSet *)canDeleteBookmarksAtIndexes:(NSIndexSet *)indexes;

/// Deletes all bookmarks at the given indexes. Please note that forms can't
/// be deleted and must be cleared instead. Throws `NSGenericException` if an
/// bookmark at one of the indexes can't be deleted (use
/// `canDeleteBookmarksAtIndexes:` if you don't know for sure). Throws
/// `NSRangeException` if one of the indexes is not valid.
- (void)deleteBookmarksAtIndexes:(NSIndexSet *)indexes;

/// Returns `true` if the bookmark can be moved at all, otherwise returns `false`.
/// This is a convenience method for `canMoveBookmarksAtIndexes:`.
- (BOOL)canMoveBookmarkAtIndex:(NSUInteger)index;

/// Returns indexes for all bookmarks at `indexes` which can be moved. Returns an
/// empty index set if no item can be moved. Throws `NSRangeException` if any one
/// of the `indexes` is not valid. Use this method to decide whether to allow
/// dragging of an item (on `macOS`) or to show a dragging handle (on `iOS`).
- (NSIndexSet *)canMoveBookmarksAtIndexes:(NSIndexSet *)indexes;

/// Returns `true` if the bookmark can be moved to the specified index, otherwise
/// returns `false`. This is a convenience method for
/// `canMoveBookmarksAtIndexes:toIndex:`.
- (BOOL)canMoveBookmarkAtIndex:(NSUInteger)fromIndex toIndex:(NSUInteger)toIndex;

/// Moves the bookmark `fromIndex` to `toIndex`. Convenience method for
/// `moveBookmarksAtIndexes:toIndex:`.
- (void)moveBookmarkAtIndex:(NSUInteger)fromIndex toIndex:(NSUInteger)toIndex;

/// Returns indexes for all bookmarks at `fromIndexes` which can be moved to the
/// `toIndex`. Returns an empty index set if no item can be moved. Throws
/// `NSRangeException` if any one of the `fromIndexes` or the `toIndex` is not
/// valid. Use this method to signal the user whether he can drop the dragged
/// bookmarks to the specified index.
- (NSIndexSet *)canMoveBookmarksAtIndexes:(NSIndexSet *)fromIndexes toIndex:(NSUInteger)toIndex;

/// Moves the bookmarks at `fromIndexes` to `toIndex`. Throws `NSRangeException`
/// if any one of the `fromIndexes` or the `toIndex` is not valid. Throws
/// `NSGenericException` if any one of the `fromIndexes` can't be moved to the
/// `toIndex`.
- (void)moveBookmarksAtIndexes:(NSIndexSet *)fromIndexes toIndex:(NSUInteger)toIndex;

/// Reloads bookmarks from the document synchronously. The delegate is notified
/// when reloading completes.
- (void)reloadBookmarks;

/// Returns the page text preview for the bookmark at a given index.
///
/// Only works for bookmarks with an associated page index (which is only given for PSPDFGoToAction).
/// Returns nil for bookmarks with any other action.
///
/// Can block the calling thread. Call this on a background thread,
/// if `canProvideTextPreviewWithoutParsingForBookmarkAtIndex:` returns NO.
- (nullable NSString *)textPreviewForBookmarkAtIndex:(NSUInteger)index;

/// Returns if the page text preview can be provided without parsing.
/// Checks if the text parser of the bookmark's page is loaded.
- (BOOL)canProvideTextPreviewWithoutParsingForBookmarkAtIndex:(NSUInteger)index;

/// The methods in this section provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: - Subclassing Hooks

/// The receiver is signed up for `PSPDFBookmarksChangedNotification` for all
/// objects. Make sure to call `super` when overriding.
- (void)bookmarksChangedNotification:(NSNotification *)notification NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
