//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFIndexPathDiff.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;
@class PSPDFBookmark;
@class PSPDFBookmarkListDataSource;

/// The delegate protocol for `PSPDFBookmarkListDataSource`, primarily used to update the UI.
@protocol PSPDFBookmarkListDataSourceDelegate <NSObject>

@optional

/// Tells the delegate that it is about to reload bookmarks. Use this for example
/// to display progress indicator.
- (void)bookmarkListDataSourceWillReloadBookmarks:(PSPDFBookmarkListDataSource *)bookmarkListDataSource;

/// Tells the delegate that reloading of bookmarks finished. Use this for example
/// to hide a progress indicator. It is guaranteed, that updates, if any, will be
/// performed between the `...WillReload...` and `...DidReload...` calls. You can
/// therefore safely assume that everything is up-to-date at this point.
- (void)bookmarkListDataSourceDidReloadBookmarks:(PSPDFBookmarkListDataSource *)bookmarkListDataSource aborted:(BOOL)aborted;

/// Asks the delegate whether it should suppress updates. Default is `false`. Returning
/// `true` will suppress `bookmarkListDataSourceWillBeginUpdates`,
/// `bookmarkListDataSourceDidEndUpdates`, and all of the
/// `bookmarkListDataSource:updateBy...` methods. See
/// `bookmarkListDataSourceDidSuppressUpdates` for more info and use cases.
- (BOOL)bookmarkListDataSourceShouldSuppressUpdates:(PSPDFBookmarkListDataSource *)bookmarkListDataSource;

/// Tells the delegate that it did suppress updates. This method is called instead
/// of `bookmarkListDataSourceDidEndUpdates`, at which point you can safely
/// assume that all data has been reloaded. You can use this for example to
/// trigger a full reload of a table or collection view instead of applying
/// incremental updates.
- (void)bookmarkListDataSourceDidSuppressUpdates:(PSPDFBookmarkListDataSource *)bookmarkListDataSource;

/// Tells the delegate that it is about to begin an update transaction. Use this to
/// set up your view for updates. Similar to `UITableView`, the update transactions
/// specify the final state, not a step-by-step progression.
- (void)bookmarkListDataSourceWillBeginUpdates:(PSPDFBookmarkListDataSource *)bookmarkListDataSource;

/// Tells the delegate that it ended an update transaction. Use this to tear down
/// updates for your view.
- (void)bookmarkListDataSourceDidEndUpdates:(PSPDFBookmarkListDataSource *)bookmarkListDataSource;

/// Notifies the delegate about changes by providing a diff object. Use this to
/// update your views.
- (void)bookmarkListDataSource:(PSPDFBookmarkListDataSource *)bookmarkListDataSource updateBookmarksWithIndexPathDiff:(PSPDFIndexPathDiff *)indexPathDiff;

@end

NS_ASSUME_NONNULL_END
