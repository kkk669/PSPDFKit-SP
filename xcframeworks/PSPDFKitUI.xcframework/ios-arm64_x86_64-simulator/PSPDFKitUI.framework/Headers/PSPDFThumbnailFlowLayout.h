//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFPresentationContext.h>
#import <PSPDFKitUI/PSPDFDocumentViewSpreadMode.h>

NS_ASSUME_NONNULL_BEGIN

/// Define the alignment of the thumbnail collection view.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFThumbnailFlowLayoutLineAlignment) {
    /// Layouts a line so that its items are left aligned inside the collection view.
    PSPDFThumbnailFlowLayoutLineAlignmentLeft,
    /// Layouts a line so that its items are centered inside the collection view.
    PSPDFThumbnailFlowLayoutLineAlignmentCenter,
    /// Layouts a line so that its items are right aligned inside the collection view.
    PSPDFThumbnailFlowLayoutLineAlignmentRight,
    /// Layouts a line so that its items are aligned alongside the contents page binding. (Default value)
    PSPDFThumbnailFlowLayoutLineAlignmentPageBinding,
} PSPDF_ENUM_SWIFT(ThumbnailFlowLayout.LineAlignment);

/// Layout attributes for the thubmnail collection view.
PSPDF_CLASS_SWIFT(ThumbnailFlowLayoutAttributes)
@interface PSPDFThumbnailFlowLayoutAttributes : UICollectionViewLayoutAttributes

/// The page mode this cell is displayed in. This tells the layout if this cell needs
/// to be selected together with neighboring cells and if this cell should be positioned
/// right next to neighboring cells without a gap.
@property (nonatomic) PSPDFDocumentViewLayoutPageMode pageMode;

@end

/// A layout similar to UICollectionViewFlowLayout with support for sticky headers
/// and double-page spreads, as you’d use it for the thumbnails of a magazine.
///
/// @note This layout only supports a single section. Using multiple sections is
/// unsupported and may result in undefined behavior.
///
/// @note This layout only supports a very limited horizontal scrolling mode which
/// you can enable by setting the `singleLineMode` property to `true`.
PSPDF_CLASS_SWIFT(ThumbnailFlowLayout)
@interface PSPDFThumbnailFlowLayout : UICollectionViewLayout

/// The insets used to lay out content in a section
///
/// The section insets effects the positioning of the items inisde a section. It
/// does not effect the positioning of the section header in any direction. Instead
/// the top section inset controls the spacing between the section header and the
/// first line of items in that section.
@property (nonatomic) UIEdgeInsets sectionInset;

/// The inter item spacing controls the spacing between items in horizontal direction.
///
/// Defaults to 10.0
@property (nonatomic) CGFloat interitemSpacing;

/// The line spacing controllers the spacing between items in vertical direction.
///
/// Defaults to 10.0
@property (nonatomic) CGFloat lineSpacing;

/// If the layout should horizontally position its items in one line, set this
/// value to `true`.
///
/// Defaults to `false`.
///
/// @note In single line mode headers are not supported and will result in an exception.
@property (nonatomic) BOOL singleLineMode;

/// Specifies how an incomplete lines (i.e. the last line when it has less items
/// than the previous lines) in the layout are aligned.
///
/// Defaults to PSPDFThumbnailFlowLayoutLineAlignmentLeft
@property (nonatomic) PSPDFThumbnailFlowLayoutLineAlignment incompleteLineAlignment;

/// Controls whether a section header should always stick to the top of the screen or not.
///
/// When setting this property to `true`, you should also take care of customizing the section header such that it has a visible background.
/// You can do so either by setting the `backgroundColor` or `backgroundStyle` of the appearance of `PSPDFCollectionReusableFilterView` or—if you need finer grained control—by overriding `-collectionView:viewForSupplementaryElementOfKind:atIndexPath:`.
///
/// This makes sense because the scrollable content area no longer includes the header, but it will look weird if you don’t give the header a background.
///
/// @see collectionView:viewForSupplementaryElementOfKind:atIndexPath:
/// @see backgroundStyle (PSPDFCollectionReusableFilterView)
@property (nonatomic) BOOL stickyHeaderEnabled;

// MARK: Supporting Right to Left Documents

/// Controls whether the layout is in a left to right orientation or if the layout
/// should flip its horizontal axis and calculate its items' position in a right to
/// left manner.
@property (nonatomic) BOOL flipsLayoutDirection;

// MARK: Invalidating the Layout

/// Call this method when the layout delegate page mode property changes and the layout should take the new page mode value into account.
/// 
/// @note While `invalidateLayout` handles the general invalidation of the layout and might decide to still use cached results,
/// this method handles page mode changes specifically and forces the layout to reload all item positions and sizes.
- (void)invalidateLayoutWithPageModeChange;

@end


/// Delegate for the collection view thumbnail flow layout.
PSPDF_PROTOCOL_SWIFT(CollectionViewDelegateThumbnailFlowLayout)
@protocol PSPDFCollectionViewDelegateThumbnailFlowLayout<NSObject>

@optional

/// Asks the delegate for an item size for a given index path.
///
/// @warning In multi line mode layouts (i.e. singleLineMode returns `false`),
/// `collectionView:layout:itemSizeAtIndexPath:completionHandler:` takes
/// precedence over this method.
///
/// @param collectionView The collection view object displaying the item.
/// @param layout         The collection view layout used for positioning the item.
/// @param indexPath      The index path of the item.
///
/// @return The size that the item should be laid out with.
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)layout itemSizeAtIndexPath:(NSIndexPath *)indexPath;

/// Asks the delegate for an item size for a given index path and gives the option
/// to update this size later on once expensive size calculations are finished.
///
/// If you are doing expensive size calculation you can implement this method to
/// immediately return an estimate size and then do your size calculation on a background
/// thread. Once done with the calculation, you can pass the correct height to the
/// layout by calling the completion handler. Continuous calls to the completion handler
/// will be ignored and only the first call will be used to update the size of the
/// item.
///
/// @note In case the layout is in single line mode, this method will not be called.
/// Instead, only the method without a completion handler will be called as
/// estimated sizing is not available for this mode.
///
/// @warning In multi line mode layouts (i.e. singleLineMode returns `false`), this method
/// takes precedence over `collectionView:layout:itemSizeAtIndexPath:`.
///
/// @param collectionView    The collection view object displaying the item.
/// @param layout            The collection view layout used for positioning the item.
/// @param indexPath         The index path of the item.
/// @param completionHandler A completion handler than can optionally be called if you
/// need to do expensive height calculation asynchronously.
/// Can be called from an arbitrary queue.
///
/// @return The size that the item currently should be laid out with. This can be
/// an estimate in case you use the completion handler.
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)layout itemSizeAtIndexPath:(NSIndexPath *)indexPath completionHandler:(void (^)(CGSize itemSize))completionHandler;

/// Asks the delegate for the size of the header view in the specified section.
///
/// @param collectionView The collection view object displaying the header view.
/// @param layout         The collection view layout used for positioning the header view.
/// @param section        The section of the header.
///
/// @return The size the header should have in the layout.
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)layout referenceSizeForHeaderInSection:(NSInteger)section;

/// Asks the delegate for the page mode of a specific item.
///
/// @warning `PSPDFThumbnailFlowLayout` currently only supports single, leading and
/// trailing page modes. Returning `PSPDFDocumentViewLayoutPageModeCenter`
/// will trigger an exception.
///
/// @param collectionView The collection view object displaying the item.
/// @param layout The collection view layout used for positioning the item.
/// @param indexPath The index path of the item.
/// @return The page mode that should be used by the layout.
- (PSPDFDocumentViewLayoutPageMode)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)layout pageModeForItemAtIndexPath:(NSIndexPath *)indexPath;

@end

NS_ASSUME_NONNULL_END
