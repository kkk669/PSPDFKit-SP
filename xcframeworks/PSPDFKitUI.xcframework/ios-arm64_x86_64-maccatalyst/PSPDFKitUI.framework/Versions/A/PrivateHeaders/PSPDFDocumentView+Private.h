//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentView.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPageChangeReason) {
    PSPDFPageChangeReasonProgrammatic,
    PSPDFPageChangeReasonUser,
} NS_SWIFT_NAME(PageChangeReason);

@class PSPDFViewState, PSPDFDocumentViewScrollView, PSPDFPageView;

@interface PSPDFDocumentView ()

/// The view responsible for scrolling and zooming (when not in spread based zooming mode).
@property (nonatomic, readonly) PSPDFDocumentViewScrollView *scrollView;

/// Applies the view state to the document view, optionally with animation.
///
/// @param viewState The view state to be applied.
/// @param animated `true` if the state application should be animated, else `false`.
- (void)applyViewState:(PSPDFViewState *)viewState animated:(BOOL)animated;

// MARK: Testing

/// Useful for UI tests, to ensure content comes to rest sooner after scrolling.
@property (nonatomic) BOOL throttleDeceleration;

// MARK: Scrolling and Zooming

/// Set the continuous spread index and pass on animations that are preserved for the time of the animation.
- (void)setContinuousSpreadIndex:(CGFloat)continuousSpreadIndex reason:(PSPDFPageChangeReason)reason animated:(BOOL)animated;

/// Holds last `reason` passed via setContinuousSpreadIndex:reason:animated:`.
- (PSPDFPageChangeReason)lastSpreadIndexChangeReason;

/// Custom safe area insets to apply to the content. These insets are used if
/// `safeAreaInsetsAdjustmentBehavior` is `.custom`. Otherwise, either the
/// `legacySafeAreaInsets` or true `safeAreaInsets` are used instead.
@property (nonatomic) UIEdgeInsets customSafeAreaInsets;

/// Legacy safe area insets to apply to the content. These insets are used if
/// `safeAreaInsetsAdjustmentBehavior` is `.legacy`. Otherwise, either the
/// `customSafeAreaInsets` or true `safeAreaInsets` are used instead.
@property (nonatomic) UIEdgeInsets legacySafeAreaInsets;

/// Calculate the current viewport that can be used for state restoration in the
/// given page view.
///
/// @return A rectangle in the PDF coordinate space or `.null` if no viewport
/// is available for state restoration, including when the page view is zoomed
/// out completely.
- (CGRect)viewportForStateRestorationInPageView:(PSPDFPageView *)pageView;

// MARK: Page Views

/// Array of all currently visible page views in the document view.
@property (nonatomic, readonly) NSArray<PSPDFPageView *> *visiblePageViews;

/// Ask for a visible page view at the given location.
///
/// @param point Point in document view's coordiante space.
///
/// @return Visible page view at the given location, if any.
- (nullable PSPDFPageView *)visiblePageViewAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END

