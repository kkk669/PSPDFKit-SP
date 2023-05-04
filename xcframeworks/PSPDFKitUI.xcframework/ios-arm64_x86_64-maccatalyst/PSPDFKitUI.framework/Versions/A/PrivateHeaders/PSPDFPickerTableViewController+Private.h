//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFPickerTableViewController.h>

@interface PSPDFPickerTableViewController ()

/// The index paths that should have a selected state
@property (nonatomic) NSSet<NSIndexPath *> *selectedIndexPaths;

/// The checkmark image for the active model.
@property (nonatomic, readonly) UIImage *checkmarkImage;

/// The placeholder image for not active models.
/// Usually a clear image, created in the same size as `checkmarkImage`.
@property (nonatomic, readonly) UIImage *placeholderImage;

/// Scrolls to the first selected index paths. Middle position.
- (void)scrollToFirstSelectedIndexPathAnimated:(BOOL)animated;

/// Updates the selection state for all visible cells.
/// Returns YES if visible cells were successfully updated, NO otherwise.
- (BOOL)updateVisibleCells;

// MARK: - Private Subclassing hooks

/// The default implementation checks against the `selectedIndexPaths` for the default table view.
/// Override this method to provide a dynamic lookup.
- (BOOL)isSelectedIndexPath:(NSIndexPath *)indexPath inTableView:(UITableView *)tableView;

@end
