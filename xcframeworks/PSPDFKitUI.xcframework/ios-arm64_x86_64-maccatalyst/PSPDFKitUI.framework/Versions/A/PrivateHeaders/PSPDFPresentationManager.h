//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>
#import <PSPDFKitUI/PSPDFViewController.h>
#import <PSPDFKitUI/PSPDFViewControllerDelegate.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFPresentationManager;

@protocol PSPDFPresentationManagerDelegate

@optional

/// Called before the controller will be displayed. Return NO to cancel presentation.
- (BOOL)presentationManager:(PSPDFPresentationManager *)presentationManager shouldShowController:(UIViewController *)viewController options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

/// Called after the controller has been fully displayed.
- (void)presentationManager:(PSPDFPresentationManager *)presentationManager didShowController:(UIViewController *)viewController options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

/// May be used to customize properties before the view is initialized.
- (void)presentationManager:(PSPDFPresentationManager *)presentationManager applyStyleToViewController:(UIViewController *)viewController targetPresentationStyle:(UIModalPresentationStyle)style;

@end

/// Manages the presentation of modal controllers, popovers and half modal controllers.
PSPDF_APP_CLASS_SWIFT(PresentationManager)
@interface PSPDFPresentationManager : NSObject<PSPDFPresentationActions, UIPopoverPresentationControllerDelegate>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
- (instancetype)initWithTargetController:(UIViewController *)targetController NS_DESIGNATED_INITIALIZER;

/// Dismisses a view controller matching the specified class alongside the transition coordinator if possible.
/// The transition coordinator can only be used for half modal presentations.
///
/// If `transitionCoordinator` is provided and can be used, then `animated` is ignored, and returning YES does not
/// necessarily mean the view controller was dismissed because the user might cancel an interactive transition.
/// In this case a `UIView` animation to ‘dismiss’ the view of a half modal presentation alongside `transitionCoordinator`.
/// This allows the half modal to be interactively moved down in sync with a back swipe gesture.
/// The presented view controller will actually be dismissed if the transition completes without being cancelled.
///
/// @param controllerClass Only view controllers matching this class will be dismissed. Pass nil to dismiss any class of view controller.
/// @param animated Whether to animate the dismissal. Ignored if there is a `transitionCoordinator`.
/// @param transitionCoordinator The coordinator to dismiss alongside.
/// @param completion Block to run after dismissal (if there is a dismissal).
/// Is not called of there's no dismiss and NO is returned.
/// @return YES if a dismissal starts (although does not necessarily finish), NO if there is no suitable view controller to dismiss.
- (BOOL)dismissViewControllerOfClass:(nullable Class)controllerClass animated:(BOOL)animated alongsideTransitionCoordinator:(nullable id<UIViewControllerTransitionCoordinator>)transitionCoordinator completion:(nullable void (^)(void))completion;

/// The target view controller.
@property (nonatomic, weak, readonly) UIViewController *targetController;

/// The presenter delegate.
@property (nonatomic, weak) id<PSPDFPresentationManagerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
