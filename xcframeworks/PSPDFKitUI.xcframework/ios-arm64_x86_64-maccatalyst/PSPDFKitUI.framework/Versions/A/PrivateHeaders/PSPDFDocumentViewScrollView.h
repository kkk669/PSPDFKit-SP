//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFObservableScrollView.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocumentViewScrollView;

NS_SWIFT_NAME(DocumentViewScrollViewDelegate)
@protocol PSPDFDocumentViewScrollViewDelegate <UIScrollViewDelegate>
@optional

/// Called whenever the bounds where changed on the document view scroll view.
///
/// @note This works on the model layer, not the presentation layer. So this is called
/// before the view represents the current value.
///
/// @param scrollView The scroll view whose bounds changed.
/// @param oldBounds The bounds before the update.
- (void)documentViewScrollView:(PSPDFDocumentViewScrollView *)scrollView didUpdateBounds:(CGRect)oldBounds;

@end

/// A document view scroll view is a regular scroll view but with some bounds change
/// callback methods. Its delegate notifies about bounds changes right away, before
/// the next layout path and the usual calls to `scrollViewDidScroll:`. It therefore
/// can be used to make model-layer adjustments to your view hierarchy before they
/// are transformed to the presentation layer during layout.
///
/// ## Contents
///
/// Internally the scroll view has a `contentView`, a simple `UIView` that can be
/// used as the container for the actual content. This enables a simple support for
/// zooming as the `contentView` can simply be returned from `viewForZoomingInScrollView:`.
PSPDF_TEST_CLASS_SWIFT(DocumentViewScrollView)
@interface PSPDFDocumentViewScrollView : PSPDFObservableScrollView

/// The delegate of the receiver. It also needs to conform to `UIScrollViewDelegate`.
@property (nonatomic, weak) id<PSPDFDocumentViewScrollViewDelegate> delegate;

/// The name shown when calling `description` or `debugDescription`.
///
/// @note For debugging purpose only.
@property (nonatomic, copy) NSString *name;

/// The content view of a scroll view contains all subviews of the view.
/// Its size is always equal to the scroll view's `contentSize`.
@property (nonatomic, readonly) UIView *contentView;

@end

NS_ASSUME_NONNULL_END
