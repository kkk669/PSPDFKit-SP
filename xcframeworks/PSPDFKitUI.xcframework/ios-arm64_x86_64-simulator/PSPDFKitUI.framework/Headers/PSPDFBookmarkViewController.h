//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBookmarkCell.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKitUI/PSPDFDocumentInfoController.h>
#import <PSPDFKitUI/PSPDFSegmentImageProviding.h>
#import <PSPDFKitUI/PSPDFStatefulTableViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

@class PSPDFDocument, PSPDFBookmark, PSPDFBookmarkViewController;

NS_ASSUME_NONNULL_BEGIN

/// Delegate for the bookmark controller.
PSPDF_PROTOCOL_SWIFT(BookmarkViewControllerDelegate)
@protocol PSPDFBookmarkViewControllerDelegate<NSObject>

/// Query the page that should be bookmarked when pressed the [+] button.
- (NSUInteger)currentPageForBookmarkViewController:(PSPDFBookmarkViewController *)bookmarkController;

/// Called when a cell is touched.
- (void)bookmarkViewController:(PSPDFBookmarkViewController *)bookmarkController didSelectBookmark:(PSPDFBookmark *)bookmark;

@end

/// Show list of bookmarks for the current document and allows editing/reordering of the bookmarks.
PSPDF_CLASS_SWIFT(BookmarkViewController)
@interface PSPDFBookmarkViewController : PSPDFStatefulTableViewController<PSPDFBookmarkTableViewCellDelegate, PSPDFDocumentInfoController, PSPDFSegmentImageProviding, PSPDFStyleable, PSPDFOverridable>

/// Whether the user can long press to copy the title. Defaults to `true`.
@property (nonatomic) BOOL allowCopy;

/// Whether the user can edit the list. Defaults to `true`.
@property (nonatomic) BOOL allowEditing;

/// Whether the bookmark name should automatically become editable after adding a new bookmark. Defaults to `true`.
@property (nonatomic) BOOL shouldStartEditingBookmarkNameWhenAdding;

/// Defines whether it is possible to add multiple bookmarks on the same page. Defaults to NO.
///
/// This property will automatically be set to the value of `PSPDFConfiguration.allowMultipleBookmarksPerPage`
/// if the bookmark controller is created and presented by `PDFViewController`.
@property (nonatomic) BOOL allowMultipleBookmarksPerPage;

/// Control the sort order. Reordering is only allowed for `PSPDFBookmarkManagerSortOrderCustom`.
@property (nonatomic) PSPDFBookmarkManagerSortOrder sortOrder;

/// An array of custom bar button items to display on the right (or trailing) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *rightActionButtonItems;

/// An array of custom bar button items to display on the left (or leading) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *leftActionButtonItems;

/// The bookmark view controller delegate to detect when a bookmark entry is tapped.
@property (nonatomic, weak) IBOutlet id<PSPDFBookmarkViewControllerDelegate> delegate;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFBookmarkViewController (SubclassingHooks)

- (void)configureCell:(PSPDFBookmarkCell *)bookmarkCell withBookmark:(PSPDFBookmark *)bookmark forRowAtIndexPath:(NSIndexPath *)indexPath inTableView:(UITableView *)tableView;
- (void)updateBookmarkViewAnimated:(BOOL)animated;
- (void)updateBarButtonItems;
- (void)addBookmarkAction:(nullable id)sender;
- (void)doneAction:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
