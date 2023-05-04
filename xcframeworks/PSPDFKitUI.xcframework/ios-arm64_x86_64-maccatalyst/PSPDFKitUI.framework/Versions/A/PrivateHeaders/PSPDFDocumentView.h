//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKitUI/PSPDFScrollTouchMode.h>
#import <PSPDFKitUI/PSPDFSpreadScrollPosition.h>

@class PSPDFDocumentView, PSPDFDocumentViewLayout, PSPDFSpreadView;

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFDocumentViewDelegate <NSObject>

/// Called when the spread index changes.
///
/// @note This method is called even if the spread index was modified programmatically.
///
/// @param documentView The document view whose spread index changed.
/// @param oldSpreadIndex The old spread index, before it was changed.
- (void)documentView:(PSPDFDocumentView *)documentView didChangeSpreadIndex:(NSInteger)oldSpreadIndex;

/// Called when the continuous spread index changes.
///
/// @note This method is called constantly when scrolling. If you implement this method,
/// it should be fast. It is called even if the continuous spread index was modified
/// programmatically.
///
/// @param documentView The document view whose spread index changed.
/// @param oldContinuousSpreadIndex The old continuous spread index, before it was changed.
- (void)documentView:(PSPDFDocumentView *)documentView didChangeContinuousSpreadIndex:(CGFloat)oldContinuousSpreadIndex;

/// Called when a spread view enters the bounds of the document view.
///
/// A spread is considered visible if at least one pixel of it is inside the document
/// view's bounds.
///
/// @see `-documentView:didEndDisplayingSpreadView:forSpreadAtIndex:`
///
/// @param documentView The document view the spread view belongs to.
/// @param spreadView The spread view that is entering the visible bounds.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentView:(PSPDFDocumentView *)documentView willBeginDisplayingSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when a spread view leaves the bounds of the document view.
///
/// A spread is considered visible if at least one pixel of it is inside the document
/// view's bounds.
///
/// @see `-documentView:willBeginDisplayingSpreadView:forSpreadAtIndex:`
///
/// @param documentView The document view the spread view belongs to.
/// @param spreadView The spread view that left the visible bounds.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentView:(PSPDFDocumentView *)documentView didEndDisplayingSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when a spread view is configured and added to the view hierarchy.
///
/// @see `-documentView:didCleanupSpreadView:forSpreadAtIndex:`
///
/// @param documentView The document view the spread view belongs to.
/// @param spreadView The spread view that was configured.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentView:(PSPDFDocumentView *)documentView didConfigureSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when a spread view is cleaned up and removed from the view hierarchy.
///
/// @see `-documentView:didConfigureSpreadView:forSpreadAtIndex:`
///
/// @param documentView The document view the spread view belongs to.
/// @param spreadView The spread view that was cleaned up.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentView:(PSPDFDocumentView *)documentView didCleanupSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called whenever the zoom scale is updated.
///
/// @note This method will be called rapidly while the user is actively zooming in
/// or out. Make sure you do the minimum amount of work in this method.
///
/// @param documentView The document view the change occurred in.
/// @param zoomScale The new zoom scale.
/// @param spreadIndex The index of the spread that was zoomed or `NSNotFound` if the
/// zoom is responsible for multiple spread views.
- (void)documentView:(PSPDFDocumentView *)documentView didUpdateZoomScale:(CGFloat)zoomScale forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called whenever a inner scroll view is scrolled. Only relevant for spread based zooming.
/// This method is also called when we zoom.
///
/// @note This method will be called rapidly while the user actively scrolls.
/// Make sure you do the minimum amount of work in this method.
///
/// @param documentView The document view the change occurred in.
/// @param scrollView The scroll view who is being scrolled.
/// @param spreadIndex The index of the spread that was zoomed or `NSNotFound` if
/// the zoom is responsible for multiple spread views.
- (void)documentView:(PSPDFDocumentView *)documentView didScrollInnerScrollView:(UIScrollView *)scrollView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when the document view controller is configuring the scroll view that is
/// responsible for scrolling the spreads.
///
/// @param documentView The document view the scroll view belongs to.
/// @param scrollView The scroll view being configured.
- (void)documentView:(PSPDFDocumentView *)documentView configureScrollView:(UIScrollView *)scrollView;

/// Called when the document view controller is configuring a scroll view that is responsible
/// for zooming one or multiple spreads.
///
/// @note In some layouts the zoom view is equal to the scroll view responsible for
/// scrolling the spreads. Therefore configuring the zoom view can have an impact
/// on the scrolling behavior.
///
/// @param documentView The document view the zoom view belongs to.
/// @param zoomView The zoom view being configured.
/// @param spreadIndex The index of the spread the zoom view is displaying or `NSNotFound`
/// if the zoom view is responsible for multiple spreads.
- (void)documentView:(PSPDFDocumentView *)documentView configureZoomView:(UIScrollView *)zoomView forSpreadAtIndex:(NSInteger)spreadIndex;

@end

/// The document view is the view responsible for showing a document on screen. It
/// is the main starting point for anything that deals with how a document is laid
/// out on screen.
///
/// `PSPDFDocumentView` itself is mostly a container view that does not provide any
/// visible UI itself. Instead it groups all the UI on screen related to presenting
/// a document and the objects providing the layout.
PSPDF_TEST_CLASS_SWIFT(DocumentView)
@interface PSPDFDocumentView : UIView

PSPDF_DEFAULT_VIEW_INIT_UNAVAILABLE

/// Initializes a new document view with the given layout, document and configuration.
///
/// @param frame The frame of the document view.
/// @param layout The layout used by the document view.
- (instancetype)initWithFrame:(CGRect)frame layout:(PSPDFDocumentViewLayout *)layout delegate:(nullable id<PSPDFDocumentViewDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/// The layout currently used to layout the view hierarchy.
@property (nonatomic) __kindof PSPDFDocumentViewLayout *layout;

@property (nonatomic, weak) id<PSPDFDocumentViewDelegate> delegate;

/// @category Managing Spreads and Pages

/// The spread index currently displayed in the document view.
///
/// For spread-based zooming ang page curl layouts, this is an integer
/// representation of `continuousSpreadIndex`. For continuous scrolling layouts,
/// this points to the first fully visible spread along the scrolling direction.
///
/// This property is key value observable.
///
/// @see `-continuousSpreadIndex`
/// @see `-setContinuousSpreadIndex:`
@property (nonatomic) NSInteger spreadIndex;

/// Scrolls the document to a certain spread.
///
/// @param spreadIndex The index of the spread you want to become visible.
/// @param animated Whether or not you want the scrolling to be animated.
- (void)setSpreadIndex:(NSInteger)spreadIndex animated:(BOOL)animated;

/// Scrolls so the specified spread is visible in the document view either in an animated way or without animating.
///
/// @note For paginated scrolling and when using a page view controller, the `position` is ignored.
///
/// @param spreadIndex The destination spread index.
/// @param position The position of the spread in the document view viewport.
/// @param animated Whether the scrolling should be animated or not.
- (void)scrollToSpreadAtIndex:(NSInteger)spreadIndex scrollPosition:(PSPDFSpreadScrollPosition)position animated:(BOOL)animated;

/// The continuous spread index currently displayed in the document view.
///
/// The continuous spread index represents the main visible spread as well as the scroll
/// position of that spread. A continuous spread index of 2.5 means that the spread
/// index 2 is currently visible and already half way scrolled towards spread index 3.
///
/// The continuous spread index is relative to the center of the view's viewport, so
/// to center a spread in the scroll view, you need to set the continuous spread index
/// to the spreads center. E.g. when you want to have spread index 2 centered on screen
/// you need to set the continuous spread index to 2.5.
///
/// If you are not interested in the inter-spread offset, there are integer based methods
/// available as well to read and modify the spread index, setting a spread index with
/// the integer based methods will always center that spread. If you do not need the
/// inter-spread granularity, the integer based methods should be preferred.
///
/// This property is key value observable.
///
/// @see `-spreadIndex`
/// @see `-setSpreadIndex:`
@property (nonatomic) CGFloat continuousSpreadIndex;

/// Scrolls the document to a certain spread.
///
/// @param continuousSpreadIndex The index of the spread you want to become visible.
/// @param animated Whether or not you want the scrolling to be animated.
- (void)setContinuousSpreadIndex:(CGFloat)continuousSpreadIndex animated:(BOOL)animated;

// MARK: Scrolling & Zooming

@property (nonatomic) PSPDFScrollTouchMode scrollTouchMode;

/// Controls whether the user can scroll through a document or not
@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;

/// Controls whether the user can zoom inside a document or not
@property (nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;

/// Controls whether the view responsible for scrolling should always bounce. If the
/// layout is a directional layout (i.e. it inherits from `PSPDFStackViewLayout`),
/// bouncing only occurs in the direction of the layout.
///
/// Defaults to `false`.
@property (nonatomic) BOOL alwaysBounce;

/// Controls whether the view responsible for scrolling should show scroll
/// indicators or not.
///
/// Default: `.adaptive`, in which case the resolved value is `false` if the
/// layout uses spread-based zooming, otherwise `true`.
@property (nonatomic) PSPDFAdaptiveConditional showsScrollIndicators;

/// Switches to a particular spread index and then zooms to a given rect on that page.
///
/// @param pdfRect The rect that should be zoomed on in PDF coordinates. If this is `CGRectNull`, the full page will be visible.
/// @param zoomScale The zoom scale to apply to the scroll view. If this is `PSPDFAutomaticSearchResultZoomScale`, the scroll view zooms until the rect is at a vertical or horizontal edge of the scroll view.
/// In all other cases, `pdfRect` is centered and the zoomScale is applied, provided that `pdfRect` fits at the specified scale. If it does not, this value is adjusted as required.
/// @param pageIndex The page index of the page on which the given `pdfRect` should be zoomed to.
/// @param animated `true` if the change and zoom should be animated, `false` otherwise.
/// @param completionHandler The completion handler to call after the zoom is performed, animated or otherwise.
///
/// @note This method does not check the current `PDFConfiguration`'s maxZoomScale.
- (void)zoomToPDFRect:(CGRect)pdfRect zoomScale:(CGFloat)zoomScale forPageAtIndex:(NSInteger)pageIndex animated:(BOOL)animated completionHandler:(void(^_Nullable)(BOOL))completionHandler;

// MARK: Spread Views

/// The zoom views that are currently in the view hierarchy.
@property (nonatomic, copy, readonly) NSSet<UIScrollView *> *zoomViews;

/// The spread views that are currently in the view hierarchy.
@property (nonatomic, copy, readonly) NSSet<PSPDFSpreadView *> *spreadViews;

/// The spread views that are currently visible.
@property (nonatomic, copy, readonly) NSSet<PSPDFSpreadView *> *visibleSpreadViews;

@end

NS_ASSUME_NONNULL_END
