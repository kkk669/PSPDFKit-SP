//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFStaticTableViewController.h>
#import <PSPDFKitUI/PSPDFBaseTableViewController+Private.h>

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFCellModel.h>
#import <PSPDFKitUI/PSPDFSectionModel.h>

NS_ASSUME_NONNULL_BEGIN

/// Used as marker for auto sizing sections.
PSPDF_APP_CLASS_SWIFT(AutoSizingView)
@interface PSPDFAutoSizingView : UIView
@end

@class PSPDFSectionModel;

@interface PSPDFStaticTableViewController ()

/// Table view sections (`PSPDFSectionModel`)
@property (nonatomic, copy) NSArray<PSPDFSectionModel *> *sections;

/// Stop the editing of cells if another cell enters the edit state
@property (nonatomic) BOOL stopEditingOnCellSelectionChange;

/// Calls `updateBlock` on the `PSPDFCellModel` at the given index path, if any.
///
/// @param indexPath   The index path in which the cell model can be found.
- (void)callUpdateBlockForModelAtIndexPath:(NSIndexPath *)indexPath;

/// Calls the update block on all visible cells.
/// Does not update the heights of cells.
/// Returns YES if visible cells were successfully updated, NO otherwise.
///
/// @note Will not do anything if the view is not yet loaded.
- (BOOL)updateVisibleCells;

/// The default height for headers and footers is `UITableViewAutomaticDimension` for grouped style.
/// For plain style, extra padding is created.
///
/// Use this property to enforce zero sized empty headers and footers.
/// Defaults to `true` for `UITableViewStylePlain` and `false` for `UITableViewStyleGrouped`.
@property (nonatomic) BOOL useZeroHeightForEmptyHeadersAndFooters;

/// Helper to deselect a cell in the main table view.
- (void)deselectCell:(UITableViewCell *)cell animated:(BOOL)animated;

@end

@interface PSPDFStaticTableViewController (PSPDFDefaultTableViewCallbacks)

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView NS_REQUIRES_SUPER;
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section NS_REQUIRES_SUPER;
- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section NS_REQUIRES_SUPER;
- (nullable NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section NS_REQUIRES_SUPER;
- (nullable UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section NS_REQUIRES_SUPER;
- (nullable UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section NS_REQUIRES_SUPER;

/// If model has `headerView` then its height is returned. Otherwise the `tableView.sectionHeaderHeight` is returned.
/// When `useZeroHeightForEmptyHeadersAndFooters` is set to `true` this method returns 0 instead of `tableView.sectionHeaderHeight` for empty headers.
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section NS_REQUIRES_SUPER;

/// If model has `footerView` then its height is returned. Otherwise the `tableView.sectionFooterHeight` is returned.
/// When `useZeroHeightForEmptyHeadersAndFooters` is set to `true` this method returns 0 instead of `tableView.sectionFooterHeight` for empty footers.
- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section NS_REQUIRES_SUPER;

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath NS_REQUIRES_SUPER;
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath NS_REQUIRES_SUPER;
- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
