//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFHook;

@interface UIViewController (PSPDFAdditions)

/// Returns whether the controller or one of its ancestors is being dismissed
/// or popped from a navigation controller.
@property (nonatomic, readonly) BOOL pspdf_isBeingRemoved;

/// Returns all parent view controllers of the view controller.
///
/// @param includeSelf Weather the list should include `self` as the first object.
- (NSArray<UIViewController *> *)pspdf_ancestorViewControllersIncludingSelf:(BOOL)includeSelf;

/// Queries the view controller hierarchy upwards for objects of `controllerClass` and returns the
/// first match or `nil` until no more parents are available.
- (nullable __kindof UIViewController *)pspdf_closestAncestorViewControllerOfClass:(Class)controllerClass;

/// Queries the view controller hierarchy upwards for objects of `controllerClass` and returns the
/// last match or `nil` until no more parents are available.
- (nullable __kindof UIViewController *)pspdf_farthestAncestorViewControllerOfClass:(Class)controllerClass;

/// Queries the view controller hierarchy downwards into `childViewControllers`.
/// Returns the first match or `nil`. Also checks self.
/// See UIViewControllerLookupExtensions.swift
- (nullable __kindof UIViewController *)pspdf_closestChildViewControllerOfClass:(Class)controllerClass NS_REFINED_FOR_SWIFT;

/// Returns the frontmost (top) presented view controller in presentation hierarchy.
@property (nonatomic, readonly) UIViewController *pspdf_frontmostViewController NS_SWIFT_NAME(frontmost);

/// Returns the deepest child view controller in in the childViewControllerForStatusBarStyle /
/// presentedViewController chain.
@property (nonatomic, readonly) UIViewController *pspdf_leafChildViewControllerForStatusBarStyle;

/// Dismisses any presented view controllers before dismissing self.
/// Prefer this to dismissViewControllerAnimated:completion:, if the view controller
/// could currently be presenting another view controller (i.e., UISearchController).
- (void)pspdf_recursiveDismissViewControllerAnimated:(BOOL)animated completion:(void (^__nullable)(void))completion;

/// This method is called by `PSPDFPresentationManager` when the view controller will be presented or will adapt to a different presentation style.
/// Subclasses overriding this method should either call `super` to propagate the change to children or manually forward the change to children.
///
/// @param newPresentationStyle The style that the view controller will be used to present the receiver or its ancestor. This will not be `UIModalPresentationNone`.
- (void)pspdf_willTransitionToPresentationStyle:(UIModalPresentationStyle)newPresentationStyle withTransitionCoordinator:(nullable id<UIViewControllerTransitionCoordinator>)coordinator NS_REQUIRES_SUPER;

/// Excecutes the `block` if the controller's current trait collection has different color appearance
/// than the previous trait collection passed.
/// The changes in the `block` are themselves responsible for resolving the dynamic colors.
- (void)pspdf_performBlockIfAppearanceChangedFrom:(nullable UITraitCollection *)previousTraitCollection block:(NS_NOESCAPE void(^)(void))block;

@end

/// These are helpers to correctly deal with child view controller containment, since it's not always easy to get right.
@interface UIViewController (PSPDFContainer)

/// Adds `childViewController` and correctly calls delegates and adds the view.
///
/// @param childViewController The child view controller to add.
/// @param viewConfiguration   Called when it is time to configure the child view controller's view (i.e. set the frame). If you pass in NULL, the child view controller's view will be the same size as the receiver's view.
///
/// @note This helper uses autoresizing masks and will not work with SwiftUI - based views.
- (void)pspdf_containerAddChildViewController:(UIViewController *)childViewController viewConfiguration:(nullable NS_NOESCAPE void (^)(UIView *childView))viewConfiguration NS_SWIFT_NAME(add(childViewController:viewConfiguration:));

/// Removes the current view controller form the parent and removes the view.
///
/// @param viewTeardown Called just before removing the view controller's view from its superview. The block may do this itself if other state must be updated. This block will not be called if the view is not loaded.
- (void)pspdf_removeFromParentViewControllerWithViewTeardown:(nullable NS_NOESCAPE void (^)(UIView *childView))viewTeardown NS_SWIFT_NAME(removeFromParent(viewTeardown:));

@end

@interface UIViewController (PSPDFHooks)

/// Will add a dismiss action once the controller gets dismissed modally.
- (id<PSPDFHook>)pspdf_addWillDismissAction:(void (^)(void))action NS_SWIFT_NAME(addWillDismissAction(_:));
- (id<PSPDFHook>)pspdf_addDidDismissAction:(void (^)(void))action NS_SWIFT_NAME(addDidDismissAction(_:));
- (id<PSPDFHook>)pspdf_addViewWillDisappearAction:(void (^)(BOOL animated))action NS_SWIFT_NAME(addViewWillDisappearAction(_:));
- (id<PSPDFHook>)pspdf_addViewDidDisappearAction:(void (^)(BOOL animated))action NS_SWIFT_NAME(addViewDidDisappearAction(_:));
- (id<PSPDFHook>)pspdf_addViewWillAppearAction:(void (^)(BOOL animated))action NS_SWIFT_NAME(addViewWillAppearAction(_:));
- (id<PSPDFHook>)pspdf_addViewDidAppearAction:(void (^)(BOOL animated))action NS_SWIFT_NAME(addViewDidAppearAction(_:));

@end

@interface UIViewController (PSPDFWorkarounds)

/// Workaround for https://github.com/PSPDFKit/PSPDFKit/issues/10878, https://openradar.appspot.com/32980288
/// Make sure search bar doesn't go offscreen when the navigation bar has a background image set
- (void)pspdf_setNavigationBarHiddenIfBackgroundImageSet:(BOOL)hidden animated:(BOOL)animated;

@end

/// Helper to dig out the first scrollview of the controller's view or the first subview.
PSPDF_EXTERN UIScrollView *_Nullable PSPDFFirstScrollViewOfViewController(UIViewController *_Nullable controller);

NS_ASSUME_NONNULL_END
