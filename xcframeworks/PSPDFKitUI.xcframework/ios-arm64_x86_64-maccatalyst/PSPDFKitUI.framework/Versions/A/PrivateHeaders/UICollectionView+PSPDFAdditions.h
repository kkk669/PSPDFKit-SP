//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface UICollectionView (PSPDFAdditions)

/// Reloads the collection view but keeps the selection in place.
- (void)pspdf_reloadDataKeepingSelection;

/// Similar to `indexPathsForSelectedItems`, but returns an `NSIndexSet` limited to one section.
/// Filters out any invalid underflowing or overflowing indexes.
- (NSIndexSet *)pspdf_selectedIndexesInSection:(NSInteger)section;

/// The offset that needs to be added to the item position in order to get the current `contentOffset`.
///
/// @param indexPath The collection view item for which we want to determine the offset.
/// @return The offset that needs to be applied to get the current position of the item at `indexPath`.
- (CGFloat)pspdf_topScrollOffsetForItemAtIndexPath:(NSIndexPath *)indexPath;

/// Scrolls so the specified item is visible, then applies the offset.
///
/// @param indexPath The collection view item we want to scroll to.
/// @param topOffset The scroll offset to be applied to the item position.
- (void)pspdf_scrollToItemAtIndexPath:(NSIndexPath *)indexPath topOffset:(CGFloat)topOffset;

/// Calculates the bounding rectangle of the selected items and scrolls to it by horizontally centering it.
///
/// @param animated Specifies whether the scroll should be animated.
- (void)pspdf_scrollToSelectedItemsHorizontallyCenteredAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
