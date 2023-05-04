//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFReusableObjectCache.h>
#import <PSPDFKitUI/PSPDFDocumentView+Private.h>

@class PSPDFPageCurlViewController, PSPDFDocumentViewLayout, PSPDFPageCurlLayout, PSPDFSpreadView, PSPDFPageView, PSPDFDocumentViewPageViewController;

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFPageCurlViewControllerDelegate <NSObject>

/// Called when the page curl view controller is going to begin transitioning to the specified spread view.
///
/// @param viewController The calling page curl view controller.
/// @param spreadView The spread view to which the view controller is transitioning.
/// @param triggeredByPageCurl Specifies whether the transition was triggered by the view controller itself (via input from the user), or externally.
- (void)pageCurlViewController:(PSPDFPageCurlViewController *)viewController willBeginTransitionToSpreadView:(PSPDFSpreadView *)spreadView triggeredByPageCurl:(BOOL)triggeredByPageCurl;

/// Called when the transition to the given spread has been completed.
///
/// @param viewController The calling page curl view controller.
/// @param spreadView The spread view to which the transition was performed.
/// @param triggeredByPageCurl Specifies whether the transition was triggered by the view controller itself (via input from the user), or externally.
- (void)pageCurlViewController:(PSPDFPageCurlViewController *)viewController didFinishTransitionToSpreadView:(PSPDFSpreadView *)spreadView triggeredByPageCurl:(BOOL)triggeredByPageCurl;

/// Called when the page curl view controller cleans up a spread view that is hidden.
///
/// @param viewController The calling page curl view controller.
/// @param spreadView The spread view that is no longer needed.
/// @param triggeredByPageCurl Specifies whether the transition was triggered by the view controller itself (via input from the user), or externally.
- (void)pageCurlViewController:(PSPDFPageCurlViewController *)viewController didCleanupSpreadView:(PSPDFSpreadView *)spreadView triggeredByPageCurl:(BOOL)triggeredByPageCurl;

@end

/// The page curl view controller is responsible for displaying a document in the page
/// curl mode.
///
/// @note The frame of the page curl controller is automatically modified as content changes.
/// This is required to improve the curl effect. See `updateFrameToRequiredSize`.
NS_SWIFT_NAME(PageCurlViewController)
@interface PSPDFPageCurlViewController : UIPageViewController

/// Initializes the page curl view controller with a given layout.
///
/// @param layout The layout to use with this page curl view controller.
/// @param delegate The delegate to use. Setting the delegate only after initializing
/// the receiver may result in some missed delegate calls.
- (instancetype)initWithLayout:(PSPDFPageCurlLayout *)layout pageViewCache:(PSPDFReusableObjectCache<PSPDFPageView *> *)pageViewCache pspdfDelegate:(nullable id<PSPDFPageCurlViewControllerDelegate>)delegate NS_DESIGNATED_INITIALIZER;

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE
- (instancetype)initWithTransitionStyle:(UIPageViewControllerTransitionStyle)style navigationOrientation:(UIPageViewControllerNavigationOrientation)navigationOrientation options:(nullable NSDictionary<NSString *,id> *)options NS_UNAVAILABLE;

/// The layout that is used with this page curl view controller.
@property (nonatomic, readonly) PSPDFPageCurlLayout *layout;

/// The spread index currently displayed by this page curl view controller.
@property (nonatomic) NSInteger spreadIndex;

/// Sets the spread index and the visible spread either with or without animation.
///
/// @param spreadIndex The spread index to display.
/// @param animated `true` if the transition should be animated, `false` otherwise.
- (void)setSpreadIndex:(NSInteger)spreadIndex animated:(BOOL)animated;

// Implemented by the receiver itself:
@property (nullable, nonatomic, weak) id <UIPageViewControllerDelegate> delegate NS_UNAVAILABLE;
@property (nullable, nonatomic, weak) id <UIPageViewControllerDataSource> dataSource NS_UNAVAILABLE;

/// The pspdf delegate contains callbacks that are used in the context of the document view.
@property (nonatomic, weak) id<PSPDFPageCurlViewControllerDelegate> pspdfDelegate;

/// Updates the controller view size to match the displayed page views.
///
/// To correctly apply the page curl effect on non full screen pages,
/// we match the controller view size to the page size.
///
/// When the bounds change (e.g., during rotation) we need to trigger this externally.
- (void)updateFrameToRequiredSize;

/// The array of visible page view controllers managed by the page curl view
/// controller.
@property (nonatomic, readonly) NSArray<PSPDFDocumentViewPageViewController *> *visiblePageViewControllers;

@end

NS_ASSUME_NONNULL_END
