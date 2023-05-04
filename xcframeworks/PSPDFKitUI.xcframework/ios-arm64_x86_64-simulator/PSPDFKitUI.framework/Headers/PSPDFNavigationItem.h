//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// A navigation item that supports different values for certain properties for
/// different view modes.
///
/// ``PSPDFNavigationItem`` enables you to assign left and right bar button
/// items based on the view mode, so that every view mode can have different bar
/// button items displayed in the navigation bar. This navigation item and the
/// corresponding view controller ensure that displayed bar button items are are
/// updated correctly when the view mode changes.
PSPDF_CLASS_SWIFT(NavigationItem)
@interface PSPDFNavigationItem : UINavigationItem

// MARK: Customizing the Bar Button Items

/// The value of the `leftBarButtonItems` property for the given view mode.
///
/// - Parameters:
///     - viewMode: The view mode to get the value for.
- (nullable NSArray<UIBarButtonItem *> *)leftBarButtonItemsForViewMode:(PSPDFViewMode)viewMode;

/// Set the custom value of the `leftBarButtonItems` property to use for the
/// given vien mode, optionally animating the change.
///
/// > Note: Using `leftBarButtonItem`, `setLeftBarButtonItem(_:animated:)`,
/// > `leftBarButtonItems` or `setLeftBarButtonItems(_:animated:)` will set the
/// > value of the `leftBarButtonItems` property for all view modes, resetting
/// > any custom values that were previously set for each view mode.
///
/// - Parameters:
///     - items: The value of the property to use.
///     - viewMode: The view mode to use the value for.
///     - animated: Whether to animate the change, if the given view mode is
///       the current view mode.
- (void)setLeftBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items forViewMode:(PSPDFViewMode)viewMode animated:(BOOL)animated;

/// The value of the `rightBarButtonItems` property for the given view mode.
///
/// - Parameters:
///     - viewMode: The view mode to get the value for.
- (nullable NSArray<UIBarButtonItem *> *)rightBarButtonItemsForViewMode:(PSPDFViewMode)viewMode;

/// Set the custom value of the `rightBarButtonItems` property to use for the
/// given view mode, optionally animating the change.
///
/// > Note: Using `rightBarButtonItem`, `setRightBarButtonItem(_:animated:)`,
/// > `rightBarButtonItems` or `setRightBarButtonItems(_:animated:)` will set
/// > the value of the `rightBarButtonItems` property for all view modes,
/// > resetting any custom values that were previously set for each view mode.
///
/// - Parameters:
///     - items: The value of the property to use.
///     - viewMode: The view mode to use the value for.
///     - animated: Whether to animate the change, if the given view mode is
///       the current view mode.
- (void)setRightBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items forViewMode:(PSPDFViewMode)viewMode animated:(BOOL)animated;

/// The button that is used as the close button in presentation contexts.
///
/// This property should always be set. The managing view controller takes care
/// of showing or hiding this button as necessary.
///
/// If you set this property to `nil`, you need to take care of the cases where
/// the related view controller may be presented modally yourself.
///
/// > Note: The ``closeBarButtonItem`` may be included in the `leftBarButtonItems`
/// > array, depending on whether the close button is currently visible or not.
/// > You should not use this property and instead use ``leftBarButtonItemsForViewMode:``,
/// > which will never include the ``closeBarButtonItem``.
@property (nonatomic, nullable) UIBarButtonItem *closeBarButtonItem;

// MARK: Customizing the Title

/// The value of the ``title`` property for the given view mode.
///
/// - Parameters:
///     - viewMode: The view mode to get the value for.
///
/// - Returns: The value of the `title` property for the given view mode.
- (nullable NSString *)titleForViewMode:(PSPDFViewMode)viewMode;

/// Set the custom value of the ``title`` property to use for the given view
/// mode.
///
/// > Note: Setting the `title` property directly will set the default value
/// > which will be used if no custom value is set for a particular view mode.
///
/// - Parameters:
///     - title: The value of the property to use.
///     - viewMode: The view mode to use the value for.
- (void)setTitle:(nullable NSString *)title forViewMode:(PSPDFViewMode)viewMode;

// MARK: Customizing Other Properties

/// The value of the ``leftItemsSupplementBackButton`` property to use for the
/// given view mode.
///
/// - Parameters:
///     - viewMode: The view mode to get the value for.
- (BOOL)leftItemsSupplementBackButtonForViewMode:(PSPDFViewMode)viewMode;

/// Set the custom value of the `leftItemsSupplementBackButton` property to
/// use for the given view mode.
///
/// > Note: Setting the `leftItemsSupplementBackButton` property directly will
/// > set the default value which will be used if no custom value is set for a
/// > particular view mode.
///
/// - Parameters:
///     - leftItemsSupplementBackButton: The value of the property to use.
///     - viewMode: The view mode to use the value for.
- (void)setLeftItemsSupplementBackButton:(BOOL)leftItemsSupplementBackButton forViewMode:(PSPDFViewMode)viewMode;

@end

NS_ASSUME_NONNULL_END
