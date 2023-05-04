//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAction.h>
#import <PSPDFKit/PSPDFBookmark.h>
#import <PSPDFKit/PSPDFBookmarkManager.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocumentProvider;

/// Defines the action of going to a specific location within the PDF document.
PSPDF_CLASS_SWIFT(GoToAction)
@interface PSPDFGoToAction : PSPDFAction

/// Initializer with the page index.
- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex;

/// Set to `NSNotFound` if not valid.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

@end

@interface PSPDFBookmark (GoToAction)

/// Initialize with page. Convenience initialization that will create a `PSPDFGoToAction`.
- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex;

/// Convenience shortcut for self.action.pageIndex (if action is of type `PSPDFGoToAction`)
/// Page is set to `NSNotFound` if action is nil or a different type.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

@end

@interface PSPDFBookmarkManager (GoToAction)

/// Adds a bookmark for page index.
///
/// @note Convenience method. Will return the added bookmark.
- (PSPDFBookmark *)addBookmarkForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Removes all bookmarks for a given page index.
- (void)removeBookmarksForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Returns a bookmark if page index has a bookmark.
///
/// @note If the page has multiple bookmarks, this returns any of them.
- (nullable PSPDFBookmark *)bookmarkForPageAtIndex:(PSPDFPageIndex)pageIndex;

@end

NS_ASSUME_NONNULL_END
