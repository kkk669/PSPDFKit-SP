//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFContainerViewController;

/// Delegate for events and customization of `PSPDFContainerViewController`.
PSPDF_PROTOCOL_SWIFT(ContainerViewControllerDelegate)
@protocol PSPDFContainerViewControllerDelegate<NSObject>

@optional

/// Called every time `visibleViewControllerIndex` changes.
- (void)containerViewController:(PSPDFContainerViewController *)controller didUpdateSelectedIndex:(NSUInteger)selectedIndex;

/// Returns a Boolean value that indicates whether prefer to use a View Controller title or an icon in a segmented control.
- (BOOL)containerViewController:(PSPDFContainerViewController *)controller shouldUseTitleForViewController:(UIViewController *)viewController;

@end

/// Similar to `UITabBarController` but using a segmented control at the top to switch between child view controllers.
PSPDF_CLASS_SWIFT(ContainerViewController)
@interface PSPDFContainerViewController : PSPDFBaseViewController<PSPDFStyleable, PSPDFOverridable>

/// Convenience initializer.
///
/// @note Controllers contained in the `PSPDFContainerViewController` must not change their `navigationItem`'s bar button items.
- (instancetype)initWithControllers:(nullable NSArray<__kindof UIViewController *> *)controllers titles:(nullable NSArray<NSString *> *)titles;

/// The container controller delegate, notifies when the index changes.
@property (nonatomic, weak) IBOutlet id<PSPDFContainerViewControllerDelegate> delegate;

// MARK: View Controller adding/removing

/// Add view controller to the list.
///
/// @note Uses the default controller title. Controller should not change it's navigationItem's bar button items.
- (void)addViewController:(UIViewController *)controller;

/// Remove view controller from the list.
- (void)removeViewController:(UIViewController *)controller;

/// All added view controllers.
@property (nonatomic, copy, readonly) NSArray<__kindof UIViewController *> *viewControllers;

// MARK: State

/// The currently visible view controller index.
@property (nonatomic) NSUInteger visibleViewControllerIndex;

/// Set the currently visible view controller index.
- (void)setVisibleViewControllerIndex:(NSUInteger)visibleViewControllerIndex animated:(BOOL)animated;

// MARK: Settings

/// Set to YES if you want to animate controller changes. Defaults to YES.
@property (nonatomic) BOOL shouldAnimateChanges;

/// Visible view controller title will be stored in NSUserDefaults under this key.
/// Container controller will automatically restore the last visible controller when presented.
/// Make sure this is set before view loads.
@property (nonatomic, nullable) NSString *lastVisibleViewControllerTitleKey;

/// Segmented control used to switch between the child view controllers. nonnull once view is loaded.
@property (nonatomic, readonly, nullable) UISegmentedControl *filterSegment;

@end

NS_ASSUME_NONNULL_END
