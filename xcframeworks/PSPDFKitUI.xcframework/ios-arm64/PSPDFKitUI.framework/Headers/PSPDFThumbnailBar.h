//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFThumbnailBar;

/// Delegate for thumbnail actions.
PSPDF_PROTOCOL_SWIFT(ThumbnailBarDelegate)
@protocol PSPDFThumbnailBarDelegate<NSObject>

@optional

/// A thumbnail has been selected.
- (void)thumbnailBar:(PSPDFThumbnailBar *)thumbnailBar didSelectPageAtIndex:(PSPDFPageIndex)pageIndex;

@end

/// Bottom bar that shows a scrollable list of thumbnails.
PSPDF_CLASS_SWIFT(ThumbnailBar)
@interface PSPDFThumbnailBar : UICollectionView<UICollectionViewDataSource, UICollectionViewDelegate, PSPDFOverridable>

/// Delegate for the thumbnail controller.
@property (nonatomic, weak) id<PSPDFThumbnailBarDelegate> thumbnailBarDelegate;

/// The data source.
@property (nonatomic, weak) id<PSPDFPresentationContext> thumbnailBarDataSource;

/// Scrolls to specified page in the grid and centers the selected page.
- (void)scrollToPageAtIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animated;

/// Stops an ongoing scroll animation.
- (void)stopScrolling;

/// Reload and keep the selection
- (void)reloadDataAndKeepSelection;

/// Reload specific pages. Animated property is currently being ignored, changes via this API always animate.
///
/// @param indexes The page indexes that should be reloaded.
/// @param animated Optionally animates the changes. Currently this is unsupported and changes will always be animated for single page reloads.
- (void)reloadPagesAtIndexes:(NSIndexSet *)indexes animated:(BOOL)animated;

/// Thumbnail size. Defaults to 88x125 on iPad and 53x75 on iPhone.
///
/// @note In most cases changing the `thumbnailSize` should also imply changing the `thumbnailBarHeight`.
/// To propagate the update, call `updateThumbnailBarFrameAnimated:` on the parent `PSPDFUserInterfaceView`.
@property (nonatomic) CGSize thumbnailSize;

/// Set the default height of the thumbnail bar. Defaults to 135 on iPad and 85 on iPhone.
///
/// @note To propagate the update, call `updateThumbnailBarFrameAnimated:` on the parent `PSPDFUserInterfaceView`.
@property (nonatomic) CGFloat thumbnailBarHeight;

/// Show page labels. Defaults to NO.
@property (nonatomic) BOOL showPageLabels;

@end

NS_ASSUME_NONNULL_END
