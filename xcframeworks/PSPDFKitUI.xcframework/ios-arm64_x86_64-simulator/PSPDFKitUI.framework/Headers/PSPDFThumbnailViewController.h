//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>
#import <PSPDFKitUI/PSPDFThumbnailFlowLayout.h>
#import <PSPDFKitUI/PSPDFViewModePresenter.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFThumbnailViewController, PSPDFThumbnailGridViewCell;

/// Subclass to enable `UIAppearance` rules on the filter.
PSPDF_CLASS_SWIFT(ThumbnailFilterSegmentedControl)
@interface PSPDFThumbnailFilterSegmentedControl : UISegmentedControl<PSPDFOverridable>
@end

/// Possible filter types for `PSPDFThumbnailViewController`.
typedef NSString *PSPDFThumbnailViewFilter NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(ThumbnailViewFilter);

/// Show all thumbnails.
PSPDF_EXPORT const PSPDFThumbnailViewFilter PSPDFThumbnailViewFilterShowAll;

/// Show bookmarked thumbnails.
PSPDF_EXPORT const PSPDFThumbnailViewFilter PSPDFThumbnailViewFilterBookmarks;

/// All annotation types except links. Requires the `Features.annotationEditing` feature flag.
PSPDF_EXPORT const PSPDFThumbnailViewFilter PSPDFThumbnailViewFilterAnnotations;

/// Delegate for thumbnail actions.
PSPDF_PROTOCOL_SWIFT(ThumbnailViewControllerDelegate)
@protocol PSPDFThumbnailViewControllerDelegate<NSObject>

@optional

/// A thumbnail has been selected.
- (void)thumbnailViewController:(PSPDFThumbnailViewController *)thumbnailViewController didSelectPageAtIndex:(PSPDFPageIndex)pageIndex inDocument:(PSPDFDocument *)document;

@end

/// The thumbnail view controller.
PSPDF_CLASS_SWIFT(ThumbnailViewController)
@interface PSPDFThumbnailViewController : UICollectionViewController<UICollectionViewDataSource, UICollectionViewDelegate, PSPDFViewModePresenter, PSPDFCollectionViewDelegateThumbnailFlowLayout, PSPDFOverridable>

/// Data source to get double page mode.
@property (nonatomic, weak) IBOutlet id<PSPDFPresentationContext> dataSource;

/// Delegate for the thumbnail controller.
///
/// @note If this instance has been created by `PDFViewController` the delegate is already linked and should not be changed.
@property (nonatomic, weak) IBOutlet id<PSPDFThumbnailViewControllerDelegate> delegate;

/// Get the cell for certain page. Compensates against open filters.
///
/// @note `document` is ignored in the default implementation.
- (nullable UICollectionViewCell *)cellForPageAtIndex:(PSPDFPageIndex)pageIndex document:(nullable PSPDFDocument *)document;

/// Stops an ongoing scroll animation.
- (void)stopScrolling;

/// Call to refresh the results on the view controller for the filter that's currently applied.
- (void)refreshResultsForCurrentFilter;

/// Defines the filter options. Set to nil or empty to hide the filter bar.
/// Defaults to `PSPDFThumbnailViewFilterShowAll, PSPDFThumbnailViewFilterAnnotations, PSPDFThumbnailViewFilterBookmarks`.
@property (nonatomic, copy, null_resettable) NSArray<PSPDFThumbnailViewFilter> *filterOptions;

/// Currently active filter. Make sure that one is also set in `filterOptions`.
@property (nonatomic, copy) PSPDFThumbnailViewFilter activeFilter;
- (void)setActiveFilter:(PSPDFThumbnailViewFilter)activeFilter animated:(BOOL)animated;

/// Class used for thumbnails. Defaults to `PSPDFThumbnailGridViewCell` and customizations should be a subclass of thereof.
///
/// @see `-[PSPDFViewModePresenter cellClass]`
@property (nonatomic) Class cellClass;

/// Returns a suitable size for a thumbnail of a page in a given container size.
+ (CGSize)automaticThumbnailSizeForPageWithSize:(CGSize)pageSize referencePageSize:(CGSize)referencePageSize containerSize:(CGSize)containerSize interitemSpacing:(CGFloat)interitemSpacing;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFThumbnailViewController (SubclassingHooks)

/// Override to customize thumbnail cell configuration. By default, this method sets an `imageLoader` for the current cell.
/// To use a custom `imageLoader`, update the property after or instead of calling through to `super`.
- (void)configureCell:(PSPDFThumbnailGridViewCell *)cell forIndexPath:(NSIndexPath *)indexPath;

/// Returns the page for the `indexPath`. Override if you structure the cells differently.
- (PSPDFPageIndex)pageForIndexPath:(NSIndexPath *)indexPath;

/// Retrieves the index path for the passed in page index.
///
/// @param pageIndex The page index for which the index path is required.
/// @return The index path for the passed in page.
- (nullable NSIndexPath *)indexPathForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// The segmented control shown at the top, which can be used to filter to only show bookmarked or annotated pages.
@property (nonatomic, readonly, nullable) PSPDFThumbnailFilterSegmentedControl *filterSegment;

/// The filter segmented control is recreated on changes; to customize subclass this class and override `updateFilterSegment`.
- (void)updateFilterSegment;

/// Starts an asynchronous search for the pages on the document available through the filter provided.
///
/// @param filter          The filter to be used
/// @param groupSize       The searching takes batchSize as a cue as to how often to execute the resultHandler callback.
/// @param resultHandler   Called when results become available.
/// @param completion      Called when the search has completed.
///
/// @return `NSProgress` instance that can be used to track the progress of the
- (nullable NSProgress *)pagesForFilter:(PSPDFThumbnailViewFilter)filter groupingResultsBy:(NSUInteger)groupSize result:(void (^)(NSIndexSet *pageIndexes))resultHandler completion:(void (^)(BOOL finished))completion;

/// Return label when there's no content for the filter.
- (nullable NSString *)emptyContentLabelForFilter:(PSPDFThumbnailViewFilter)filter;

/// Updates the view used to display filtering progress to a "loading" state.
///
/// Pass `false` to enter a "finished loading" state (i.e., when no filter is selected).
///
/// Pass `true` to transition to a "loading state", which shows a title for the currently applied filter.
///
/// @param loading     Whether the view should display a loading indicator.
- (void)refreshLoadingViewWithLoadingState:(BOOL)loading;

/// Returns an instance of PSPDFCollectionReusableFilterView for the header of section 0, nil otherwise.
///
/// Override this method if you need to customize the header in ways that `UIAppearance` does not support or on an instance by instance basis.
/// If, for example, your app has instances of this class that use the sticky header and instances that don’t, you could do the following:
/// <code>
/// - (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath {
/// PSPDFCollectionReusableFilterView *header = (id)[super collectionView:collectionView viewForSupplementaryElementOfKind:kind atIndexPath:indexPath];
/// if ([header isKindOfClass:PSPDFCollectionReusableFilterView.class]) {
/// // Sticky header should have a background, regular header should not.
/// // If you use a solid, accented background color for the sticky header, but want a seamless look for the non–sticky header this makes even more sense.
/// header.backgroundStyle = ((PSPDFThumbnailFlowLayout *)self.collectionViewLayout).stickyHeaderEnabled ? PSPDFCollectionReusableFilterViewStyleDarkBlur : PSPDFCollectionReusableFilterViewStyleNone;
/// // Assuming we want the filter element to sit very close to the items:
/// header.filterElementOffset = CGPointMake(0, 10);
/// }
/// return header;
/// }
/// </code>
///
/// @see stickyHeaderEnabled (PSPDFThumbnailFlowLayout)
/// @see backgroundStyle (PSPDFCollectionReusableFilterView)
- (UICollectionReusableView *_Nullable)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

@end

NS_ASSUME_NONNULL_END
