//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKitUI/PSPDFSpreadScrollPosition.h>

@class PSPDFDocument, PSPDFConfiguration, PSPDFDocumentViewController, PSPDFDocumentViewLayout, PSPDFSpreadView, PSPDFPageView;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(PDFDocumentViewControllerDelegate)
@protocol PSPDFDocumentViewControllerDelegate <NSObject>
@optional

/// Called when the spread index changes.
///
/// @note This method is called even if the spread index was modified programmatically.
///
/// @param documentViewController The document view controller whose spread index changed.
/// @param oldSpreadIndex The old spread index, before it was changed.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController didChangeSpreadIndex:(NSInteger)oldSpreadIndex;

/// Called when the continuous spread index changes.
///
/// @note This method is called constantly when scrolling. If you implement this method,
/// it should be fast. It is called even if the continuous spread index was modified
/// programmatically.
///
/// @param documentViewController The document view controller whose continuous spread index changed.
/// @param oldContinuousSpreadIndex The old continuous spread index, before it was changed.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController didChangeContinuousSpreadIndex:(CGFloat)oldContinuousSpreadIndex;

/// Called whenever the zoom scale is updated.
///
/// @note This method will be called rapidly while the user is actively zooming in or out.
/// Make sure you do the minimum amount of work in this method.
///
/// @param documentViewController The document view controller the change occurred in.
/// @param zoomScale The new zoom scale.
/// @param spreadIndex The index of the spread that was zoomed or `NSNotFound` if the
/// zooming view is responsible for multiple spread views.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController didUpdateZoomScale:(CGFloat)zoomScale forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when a spread view enters the bounds of the document view.
///
/// A spread is considered visible if at least one pixel of it is inside the document
/// view's bounds.
///
/// @see `-documentViewController:didEndDisplayingSpreadView:forSpreadAtIndex:`
///
/// @param documentViewController The document view controller the spread view belongs to.
/// @param spreadView The spread view that is entering the visible bounds.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController willBeginDisplayingSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when a spread view leaves the bounds of the document view.
///
/// A spread is considered visible if at least one pixel of it is inside the document
/// view's bounds.
///
/// @see `-documentViewController:willBeginDisplayingSpreadView:forSpreadAtIndex:`
///
/// @param documentViewController The document view controller the spread view belongs to.
/// @param spreadView The spread view that left the visible bounds.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController didEndDisplayingSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when a spread view is configured and added to the view hierarchy.
///
/// @see `-documentViewController:didCleanupSpreadView:forSpreadAtIndex:`
///
/// @param documentViewController The document view controller the spread view belongs to.
/// @param spreadView The spread view that was configured.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController didConfigureSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when a spread view is cleaned up and removed from the view hierarchy.
///
/// @see `-documentViewController:didConfigureSpreadView:forSpreadAtIndex:`
///
/// @param documentViewController The document view controller the spread view belongs to.
/// @param spreadView The spread view that was cleaned up.
/// @param spreadIndex The spread index the spread view represents.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController didCleanupSpreadView:(PSPDFSpreadView *)spreadView forSpreadAtIndex:(NSInteger)spreadIndex;

/// Called when the document view controller is configuring the scroll view that is
/// responsible for scrolling the spreads.
///
/// It is safe to assign a delegate to the `UIScrollView` object received in this delegate.
///
/// @note This delegate method might be called multiple times throughout the lifetime
/// of the scroll view.
///
/// @warning Do not capture the existing scroll view delegate to relay calls - this is handled internally.
///
/// @param documentViewController The document view controller the scroll view belongs to.
/// @param scrollView The scroll view being configured.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController configureScrollView:(UIScrollView *)scrollView;

/// Called when the document view controller is configuring a scroll view that is responsible
/// for zooming one or multiple spreads.
///
/// It is safe to assign a delegate to the `UIScrollView` object received in this delegate.
///
/// @note This delegate method might be called multiple times throughout the lifetime
/// of the scroll view.
///
/// @note In some layouts the zoom view is equal to the scroll view responsible for
/// scrolling the spreads. Therefore configuring the zoom view can have an impact
/// on the scrolling behavior.
///
/// @warning Do not capture the existing scroll view delegate to relay calls - this is handled internally.
///
/// @param documentViewController The document view controller the zoom view belongs to.
/// @param zoomView The zoom view being configured.
/// @param spreadIndex The index of the spread the zoom view is displaying or `NSNotFound`
/// if the zoom view is responsible for multiple spreads.
- (void)documentViewController:(PSPDFDocumentViewController *)documentViewController configureZoomView:(UIScrollView *)zoomView forSpreadAtIndex:(NSInteger)spreadIndex;

@end

/// Posted when a spread view enters the bounds of the view.
///
/// A spread is considered visible if at least one pixel of it is inside the document
/// view's bounds.
///
/// Use `PSPDFDocumentViewControllerSpreadViewKey` to get the spread view in question
/// from the `userInfo` dictionary on the notification.
///
/// @see `PSPDFDocumentViewControllerDidEndDisplayingSpreadViewNotification`
PSPDF_EXPORT NSNotificationName const PSPDFDocumentViewControllerWillBeginDisplayingSpreadViewNotification;

/// Posted when a spread view leaves the bounds of the view.
///
/// A spread is considered visible if at least one pixel of it is inside the document
/// view's bounds.
///
/// Use `PSPDFDocumentViewControllerSpreadViewKey` to get the spread view in question
/// from the `userInfo` dictionary on the notification.
///
/// @see `PSPDFDocumentViewControllerWillBeginDisplayingSpreadViewNotification`
PSPDF_EXPORT NSNotificationName const PSPDFDocumentViewControllerDidEndDisplayingSpreadViewNotification;

/// Posted when a spread view is configured and added to the view hierarchy.
///
/// Use `PSPDFDocumentViewControllerSpreadViewKey` to get the spread view in question
/// from the `userInfo` dictionary on the notification.
///
/// @see `PSPDFDocumentViewControllerDidCleanupSpreadViewNotification`
PSPDF_EXPORT NSNotificationName const PSPDFDocumentViewControllerDidConfigureSpreadViewNotification;

/// Posted when a spread view is cleaned up and removed from the view hierarchy.
///
/// Use `PSPDFDocumentViewControllerSpreadViewKey` to get the spread view in question
/// from the `userInfo` dictionary on the notification.
///
/// @see `PSPDFDocumentViewControllerDidConfigureSpreadViewNotification`
PSPDF_EXPORT NSNotificationName const PSPDFDocumentViewControllerDidCleanupSpreadViewNotification;

/// The key on a notifications `userInfo` that holds the spread view that is relevant
/// for the posted notification.
PSPDF_EXPORT NSString *const PSPDFDocumentViewControllerSpreadViewKey;

/// Posted when the spread index changes.
PSPDF_EXPORT NSNotificationName const PSPDFDocumentViewControllerSpreadIndexDidChangeNotification;

/// The document view controller is the starting point for visualizing a document on
/// screen. It groups all the UI that deals with showing documents on screen and controls
/// the view hierarchy and the layout.
///
/// ## The Layout
///
/// The main way of controlling how a layout looks is through `PSPDFDocumentViewLayout`.
/// While PSPDFKit provides you with a set of default layouts such as a continuous
/// scrolling layout, a paginated scroll per spread layout and a curl based layout,
/// layouts are meant to be fully customizable so you can adopt PSPDFKit to your design
/// perfectly.
///
/// To customize a design you can start by changing properties on a design provided
/// by PSPDFKit. If this is not enough, `PSPDFDocumentViewLayout` and its subclasses
/// provide various levels of entry points to best fit what your desired outcome is.
///
/// You can either subclass `PSPDFContinuousScrollingLayout` or `PSPDFScrollPerSpreadLayout`
/// if you want a layout similar to these two but only need a couple of tweaks. If
/// you want to have more control but your layout still follows the general idea of
/// a layout that scrolls in a single direction, either vertically or horizontally,
/// `PSPDFStackViewLayout`, gives you a lot of control while covering the basics and
/// a couple of convenience methods that make your life easier. This should be enough
/// control for almost all designs. However if your design is very specific, we also
/// give you the same base class all of our own layouts use: `PSPDFDocumentViewLayout`.
/// With this layout you need to do everything on your own but there should be pretty
/// much no limitations on what to do with it.
///
/// To get you started with implementing your own layout, check out the documentation
/// for `PSPDFDocumentViewLayout`.
///
/// ## The Hierarchy
///
/// The document view hierarchy can be seen in the following diagram.
///
/// ```
/// ╔═══════════════════════════╗         ┌───────────────────────────┐
/// ║  DocumentViewController   ║         │  PSPDFDocumentViewLayout  │
/// ║                           ║────────▶│                           │
/// ╚═══════════════════════════╝         └───────────────────────────┘
/// ┌───────────────────────────┐
/// │       UIScrollView        │
/// │   (scrolling & zooming)   │◀───┐            Depending on
/// └───────────────────────────┘    │     spreadBasedZooming either
/// ┌───────────────────────────┐    ├──── one of these scroll views
/// │       UIScrollView        │    │     is responsible for zooming
/// │         (zooming)         │◀───┘            the content.
/// └───────────────────────────┘
/// ╔═══════════════════════════╗
/// ║        SpreadView         ║
/// ║                           ║
/// ╚═══════════════════════════╝
/// ╔═══════════════════════════╗
/// ║         PageView          ║
/// ║                           ║
/// ╚═══════════════════════════╝
///
/// ┌─────────────────────────────────────────────────────────────────┐
/// │                        ═══  Subclassable                        │
/// └─────────────────────────────────────────────────────────────────┘
/// ```
///
/// ## Continuous Spread Index
///
/// Usually you should prefer the integer based `spreadIndex` APIs. The `spreadIndex`
/// is less complex and does the necessary conversion to the continuous spread index
/// for you. However there are use cases where you need floating point precision for
/// the current scrolling position.
///
/// The `continuousSpreadIndex` maps the spreads of the document on to the viewport
/// in a size independent way. That means that no matter what size a spread is displayed
/// on and also no matter what other spread sizes are already known of a document,
/// the continuous spread index remains stable. E.g. a continuous spread index of 2.5
/// will always refer to the center of spread 2.
///
/// In the places where a continuous spread index is related to a certain position
/// in the view hierarchy, it is related to the center of the current viewport. So
/// if you call `continuousSpreadIndex` you will receive the continuous spread index
/// that is currently shown at the center of the document view controller's view.
///
/// If you implement your own custom layout and this layout does not build on top of
/// `PSPDFStackViewLayout`, you may need to deal with the continuous spread index though
/// and do calculations between the continuous spread index and the content offset
/// yourself. For that it is important how the function of the continuous spread index
/// looks. It is a monotonically increasing function over all spreads of a document.
/// Its valid range is `[0, spreadCount)`. Note that it is monotonically, but not strictly
/// monotonically increasing. The spaces between spread are not considered to be a
/// part of a spread, therefore in this area, the continuous spread index does not
/// change. E.g. spread 2 has a range of `[2, 3)`, then there is the inter-item spacing
/// between spread 2 and 3 where the continuous spread index is 3 and only when you
/// start scrolling into spread 3, the continuous spread index starts increasing again
/// in the range of `[3, 4)` for this spread.
///
/// ```
/// 3.0 ─│               ╱
///      │              ╱
///      │             ╱      This diagram shows how the continuous spread index
///      │            ╱       is calculated over the spreads. In the gap between
/// 2.0 ─│         ╱─╱        two spreads, the continuous spread index is not
///      │        ╱           changing.
///      │       ╱
///      │      ╱             Inside each spread, the continuous spread index is
/// 1.0 ─│   ╱─╱              linear in the range [i, i+1).
///      │  ╱
///      │ ╱
///      │╱
///      ╳────────────────
///      ┌───┐ ┌───┐ ┌───┐
///      │   │ │   │ │   │
///      │ 0 │ │ 1 │ │ 2 │
///      │   │ │   │ │   │
///      └───┘ └───┘ └───┘
/// ```
///
PSPDF_CLASS_SWIFT(PDFDocumentViewController)
@interface PSPDFDocumentViewController : UIViewController<PSPDFOverridable>

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// The delegate to be used to receive updates about spread views, spread changes and
/// other document view controller related events.
@property (nonatomic, weak) id<PSPDFDocumentViewControllerDelegate> delegate;

/// The layout being used to render the current document.
///
/// Changing the layout will cause the view to refresh with the new layout without
/// any animation.
@property (nonatomic) PSPDFDocumentViewLayout *layout;

// MARK: Scrolling and Zooming

/// The spread index that should be displayed by the view controller.
///
/// A spread describes a collection of continuous pages that are grouped in a logical
/// container from the layout. E.g. if you have a book, when the book is open you will
/// always see two pages next to each other. These two pages build one spread. If you
/// have a stack of loose paper on the other hand, you always only see one page, so
/// a spread only consists of one page in that example.
///
/// This property is key value observable.
///
/// Setting the spread index will be ignored if the document is not valid (e.g. locked).
///
/// @see `PSPDFSpreadView`
@property (nonatomic) NSInteger spreadIndex;

/// Sets the spread index of a document either in an animated way or without animating.
///
/// @see `-setSpreadIndex:`
///
/// @param spreadIndex The index of the spread you want to become visible.
/// @param animated Whether or not you want the scrolling to be animated.
- (void)setSpreadIndex:(NSInteger)spreadIndex animated:(BOOL)animated;

/// Scrolls so the specified spread is visible in the document view either in an animated way or without animating.
///
/// @note The `position` parameter is only applicable if the view controller view is already loaded and only for continuous (non paginated) scrolling.
///
/// @param spreadIndex The destination spread index.
/// @param position The position of the spread in the document view viewport.
/// @param animated Whether the scrolling should be animated or not.
- (void)scrollToSpreadAtIndex:(NSInteger)spreadIndex scrollPosition:(PSPDFSpreadScrollPosition)position animated:(BOOL)animated;

// MARK: Continuous Spread Index

/// The continuous spread index that should be displayed by the view controller.
///
/// A spread describes a collection of continuous pages that are grouped in a logical
/// container from the layout. E.g. if you have a book, when the book is open you will
/// always see two pages next to each other. These two pages build one spread. If you
/// have a stack of loose paper on the other hand, you always only see one page, so
/// a spread only consists of one page in that example.
///
/// The continuous spread index is relative to the center of the view's viewport, so
/// to center a spread in the scroll view, you need to set the continuous spread view
/// to the spreads center. E.g. when you want to have spread index 2 centered on screen
/// you need to set the continuous spread index to 2.5.
///
/// If you are not interested in the inter-spread offset, there are integer based methods
/// available as well to read and modify the spread index. If you do not need the
/// inter-spread granularity, the integer based methods should be preferred.
///
/// This property is key value observable.
///
/// Setting the continuous spread index will be ignored if the document is not valid (e.g. locked).
///
/// @see `PSPDFSpreadView`
/// @see `spreadIndex`
@property (nonatomic) CGFloat continuousSpreadIndex;

/// Sets the continuous spread index of a document either in an animated way or without
/// animating.
///
/// @see `-setSpreadIndex:`
///
/// @param continuousSpreadIndex The index of the spread you want to become visible.
/// @param animated Whether or not you want the scrolling to be animated.
- (void)setContinuousSpreadIndex:(CGFloat)continuousSpreadIndex animated:(BOOL)animated;

// MARK: Scrolling and Zooming

/// Scrolls to the next spread based on the current `spreadIndex` value.
///
/// @param animated `true` if the transition should be animated, `false` otherwise.
/// @return `true` if the transition was successful, `false` otherwise (e.g. if we are
/// already on the last spread).
- (BOOL)scrollToNextSpreadAnimated:(BOOL)animated;

/// Scrolls to the previous spread based on the current `spreadIndex` value.
///
/// @param animated `true` if the transition should be animated, `false` otherwise.
/// @return `true` if the transition was successful, `false` otherwise (e.g. if we are
/// already on the first spread).
- (BOOL)scrollToPreviousSpreadAnimated:(BOOL)animated;

/// Scrolls to the "next" viewport, preserving zoom scale.
///
/// @param animated Specifies whether the scroll should be animated.
/// @return `true` if the scroll occurred, else `false`.
- (BOOL)scrollToNextViewportAnimated:(BOOL)animated;

/// Scrolls to the "previous" viewport, preserving zoom scale.
///
/// @param animated Specifies whether the scroll should be animated.
/// @return `true` if the scroll occurred, else `false`.
- (BOOL)scrollToPreviousViewportAnimated:(BOOL)animated;

/// Switches to a particular spread index and then zooms to a given rect on that page.
///
/// If you want to show a particular part of a document initially (before the view hierarchy has been set up)
/// then use `applyViewState(_:animateIfPossible:)` on the `PDFViewController` instead of this method.
///
/// @param pdfRect The rect that should be zoomed on in PDF coordinates. If this is `CGRectNull`, the full page will be visible.
/// @param pageIndex The page index of the page on which the given `pdfRect` should be zoomed to.
/// @param animated `true` if the change and zoom should be animated, `false` otherwise.
- (void)zoomToPDFRect:(CGRect)pdfRect forPageAtIndex:(NSInteger)pageIndex animated:(BOOL)animated;

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

/// The boolean value that indicates whether the view responsible for scrolling
/// should show scroll indicators or not.
///
/// Default: `false` if the layout uses spread-based zooming, otherwise `true`.
@property (nonatomic) BOOL showsScrollIndicator;

// MARK: Spread Views

/// The spread views that are currently visible, ordered by their spread index.
@property (nonatomic, copy, readonly) NSArray<PSPDFSpreadView *> *visibleSpreadViews;

@end

@interface PSPDFDocumentViewController (PageViews)

/// Asks the document view controller for a currently visible page view at the
/// given location.
///
/// - Parameters:
///     - point: Location of a potential page view, in the coordinate space of
///       the document view controller's view.
///
/// - Returns: A page view that is currently visible at the given location, or
///   `nil` if there is none.
- (nullable PSPDFPageView *)visiblePageViewAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END
