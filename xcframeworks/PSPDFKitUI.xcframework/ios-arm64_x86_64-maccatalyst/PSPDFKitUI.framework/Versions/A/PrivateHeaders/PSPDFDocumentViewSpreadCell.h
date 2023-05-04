//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFReusableObjectCache.h>
#import <PSPDFKitUI/PSPDFObservableScrollView.h>

@class PSPDFDocumentViewLayout, PSPDFSpreadView, PSPDFPageView, PSPDFDocumentViewSpreadCell;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDocumentViewSpreadCellScrollView : PSPDFObservableScrollView

PSPDF_INIT_WITH_CODER_UNAVAILABLE

/// The additional content insets that the document view layout requires to be
/// set around the spread. This directly corresponds to `spreadCellContentInsets`
/// property of the layout. Setting this property also sets the scroll idicator
/// insets.
@property (nonatomic) UIEdgeInsets spreadCellContentInsets;

@end

@protocol PSPDFDocumentViewSpreadCellDelegate <NSObject>

/// Informs the delegate that the cell has been prepared for reuse.
///
/// @param cell A reference to the cell that has been put into the reuse queue.
- (void)cellDidPrepareForReuse:(PSPDFDocumentViewSpreadCell *)cell;

@end

/// The spread cell is responsible for showing spread views that contain the actual
/// pages of the current document.
@interface PSPDFDocumentViewSpreadCell : UICollectionViewCell

/// The layout that is used by the collection view and the whole document view hierarchy
/// that this cell participates in.
@property (nonatomic, readonly, nullable) PSPDFDocumentViewLayout *layout;

/// The spread index that this cell will display.
@property (nonatomic, readonly) NSInteger spreadIndex;

/// Attached scroll view. Contains the spread view. Manages zoom in certain page transition modes.
@property (nonatomic, readonly) PSPDFDocumentViewSpreadCellScrollView *scrollView;

/// Attached spread view. Manages display of page views.
@property (nonatomic, readonly, nullable) PSPDFSpreadView *spreadView;

/// Configures the receiver with the given layout and spread index.
///
/// @param layout The layout to configure this spread cell with.
/// @param spreadIndex The index this spread cell represents.
- (void)configureWithLayout:(PSPDFDocumentViewLayout *)layout spreadIndex:(NSInteger)spreadIndex pageViewCache:(PSPDFReusableObjectCache<PSPDFPageView *> *)pageViewCache;

/// Resets view states like the zoom scale and content offset of the scroll view to
/// the defaults.
- (void)resetViewState;

/// Delegate receiving certain cell lifecycle callbacks.
@property (nonatomic, weak) id<PSPDFDocumentViewSpreadCellDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
