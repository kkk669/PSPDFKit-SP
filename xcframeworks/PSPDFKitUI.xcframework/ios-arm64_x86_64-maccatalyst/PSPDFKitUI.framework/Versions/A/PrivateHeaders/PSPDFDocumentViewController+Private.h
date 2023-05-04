//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentViewController.h>

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFScrollTouchMode.h>

@class PSPDFViewState, PSPDFDocumentView;

NS_ASSUME_NONNULL_BEGIN

/// Triggered whenever the continuous spread index changes.
///
/// Use `PSPDFDocumentViewControllerSpreadViewKey` to get the spread view in question
/// from the `userInfo` dictionary on the notification.
///
/// @warning This notification is triggered in rapid succession, use it carefully.
PSPDF_EXTERN NSNotificationName const PSPDFDocumentViewControllerContinuousSpreadIndexDidChangeNotification;

/// Triggered whenever the zoom scale of one of the zoom views changes.
///
/// @warning This notification is triggered in rapid succession, use it carefully.
PSPDF_EXTERN NSNotificationName const PSPDFDocumentViewControllerZoomScaleDidChangeNotification;

/// Triggered whenever the inner scroll view is scrolled or zoomed.
///
/// @warning This notification is triggered in rapid succession, use it carefully.
PSPDF_EXTERN NSNotificationName const PSPDFDocumentViewControllerInnerScrollViewDidScrollNotification;

/// Posted whenever the document view controller configures the scroll view responsible
/// for scrolling through the pages of a document.
///
/// The user info dictionary contains the key `PSPDFDocumentViewControllerScrollViewKey`,
/// referring to the scroll view that was just configured.
PSPDF_EXTERN NSNotificationName const PSPDFDocumentViewControllerDidConfigureScrollViewNotification;

/// The key on notifications `userInfo` that holds the spread index that is relevant
/// for the posted notification.
PSPDF_EXPORT NSString *const PSPDFDocumentViewControllerSpreadIndexKey;

/// The key on notifications `userInfo` that holds the old spread index that was relevant
/// before the notification was posted.
PSPDF_EXPORT NSString *const PSPDFDocumentViewControllerOldSpreadIndexKey;

/// The key on notifications `userInfo` represents a `bool`. `true` if the change originated
/// from a user action, `false` otherwise.
PSPDF_EXPORT NSString *const PSPDFDocumentViewControllerOriginatesFromUserInteractionKey;

/// A key referring to the scroll view the notification is about.
PSPDF_EXPORT NSString *const PSPDFDocumentViewControllerScrollViewKey;

@interface PSPDFDocumentViewController ()

/// Initializes a new instance of a document view controller.
///
/// @note You should never create such an instance yourself, instead access the instance
/// the `PDFViewController` created for you through its `documentViewController`
/// method.
///
/// @param document The document to render.
/// @param configuration The configuration to derive default values from.
/// @param layout The layout to use or `nil` if the layout should be derived from the configuration.
- (instancetype)initWithDocument:(PSPDFDocument *)document configuration:(PSPDFConfiguration *)configuration layout:(nullable PSPDFDocumentViewLayout *)layout NS_DESIGNATED_INITIALIZER;

/// The document used by the layout.
@property (nonatomic) PSPDFDocument *document;

/// The document view accessor.
@property (nonatomic, readonly) PSPDFDocumentView *documentView;

/// The configuration used by the layout.
@property (nonatomic) PSPDFConfiguration *configuration;

/// Invalidate the document view's view hierarchy without rebuilding it.
- (void)invalidateDocumentViewHierarchy;

/// Hides additional UI elements on all visible page views.
- (void)hidePageElementsAnimated:(BOOL)animated;

// MARK: Scrolling

/// Controls whether the scroll views can be scrolled with one or with two fin
@property (nonatomic) PSPDFScrollTouchMode scrollTouchMode;

// MARK: State Restoration

/// The current view state. This is a computed property, to always capture the current state.
@property (nonatomic, readonly, nullable) PSPDFViewState *viewState;

/// Applies the view state, with an optional animation.
///
/// @param viewState The view state to be applied.
/// @param animated Specifies whether the state should be applied with an animation.
///
/// @warning This forces the view to be loaded.
- (void)applyViewState:(PSPDFViewState *)viewState animated:(BOOL)animated;

// MARK: Scrolling and Zooming

/// Custom safe area insets to apply to the content. These insets are used if
/// `safeAreaInsetsAdjustmentBehavior` is `.custom`. Otherwise, either the
/// `legacySafeAreaInsets` or true `safeAreaInsets` are used instead.
@property (nonatomic) UIEdgeInsets customSafeAreaInsets;

/// Legacy safe area insets to apply to the content. These insets are used if
/// `safeAreaInsetsAdjustmentBehavior` is `.legacy`. Otherwise, either the
/// `customSafeAreaInsets` or true `safeAreaInsets` are used instead.
@property (nonatomic) UIEdgeInsets legacySafeAreaInsets;

/*
 Simply check if the scroll view(s) are currently scrolling or animating.
 */
@property (nonatomic, readonly) BOOL isScrollingOrDecelerating;

/// Switches to a particular spread index and then zooms to a given rect on that page.
///
/// @param pdfRect The rect that should be zoomed on in PDF coordinates. If this is `CGRectNull`, the full page will be visible.
/// @param zoomScale The zoom scale to apply to the scroll view. If this is `PSPDFAutomaticSearchResultZoomScale`, the scroll view zooms until the rect is at a vertical or horizontal edge of the scroll view.
/// In all other cases, `pdfRect` is centered and the zoomScale is applied, provided that `pdfRect` fits at the specified scale. If it does not, this value is adjusted as required.
/// @param pageIndex The page index of the page on which the given `pdfRect` should be zoomed to.
/// @param animated `true` if the change and zoom should be animated, `false` otherwise.
/// @param completionHandler The block to be call after the zoom is attempted. If the argument is `true`, then the zoom completed.
- (void)zoomToPDFRect:(CGRect)pdfRect zoomScale:(CGFloat)zoomScale forPageAtIndex:(NSInteger)pageIndex animated:(BOOL)animated completionHandler:(void (^ _Nullable)(BOOL))completionHandler;

@end

NS_ASSUME_NONNULL_END
