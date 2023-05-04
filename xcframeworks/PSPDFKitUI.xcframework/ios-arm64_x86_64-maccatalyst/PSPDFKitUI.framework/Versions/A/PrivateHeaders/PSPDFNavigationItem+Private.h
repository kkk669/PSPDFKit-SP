//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFNavigationItem.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFNavigationItemDelegate <NSObject>

/// The current view mode that should be used to update navigation items.
- (PSPDFViewMode)viewModeForNavigationItem:(PSPDFNavigationItem *)navigationItem;

@optional

/// Called when the navigation items have been updated in the navigation bar.
///
/// @note This method is not called when the items of a non-current view mode have changed.
- (void)navigationItemDidUpdate:(PSPDFNavigationItem *)navigationItem;

/// Called before the active left bar button items are changed.
///
/// The receiver can return a different array with other bar button items to customize the items that will be set.
/// If you do not implement this method, the passed in `barButtonItems` will instead be used.
///
/// @param barButtonItems The items the navigation item wants to set as active items.
///
/// @return The items that the delegate wants to set as active items.
- (NSArray<UIBarButtonItem *> *)navigationItem:(PSPDFNavigationItem *)navigationItem shouldSetLeftBarButtonItems:(NSArray<UIBarButtonItem *> *)barButtonItems;

/// Called before the active right bar button items are changed.
///
/// The receiver can return a different array with other bar button items to customize the items that will be set.
/// If you do not implement this method, the passed in `barButtonItems` will instead be used.
///
/// @param barButtonItems The items the navigation item wants to set as active items.
///
/// @return The items that the delegate wants to set as active items.
- (NSArray<UIBarButtonItem *> *)navigationItem:(PSPDFNavigationItem *)navigationItem shouldSetRightBarButtonItems:(NSArray<UIBarButtonItem *> *)barButtonItems;

@end

// MARK: -

@interface PSPDFNavigationItem ()

/// Initializer that hooks up our navigation item with an original one to work
/// around a couple of issues with Storyboards.
///
/// All calls you make to this item will be mirrored to the original item.
///
/// @param originalItem The item to forward calls to.
- (instancetype)initWithOriginalItem:(nullable UINavigationItem *)originalItem;

/// The delegate to control the view mode and customize the navigation bar items.
@property (nonatomic, weak) id<PSPDFNavigationItemDelegate> pspdfDelegate;

/// Update the bar button items.
///
/// Call this method if e.g. the view mode has changed and the navigation bar needs to adopt to that.
///
/// @param animated `true` if you want to animate the changes.
- (void)updateBarButtonItems:(BOOL)animated;

/// Set the custom value of the `showsCloseButton` property to use for the given
/// view mode. The `showsCloseButton` property controls whether to show the
/// close button or not.
///
/// If this property is `true`, the close button is included among the left bar
/// button items for the given view mode.
///
/// - Parameters:
///     - leftItemsSupplementBackButton: The value of the property to use.
///     - viewMode: The view mode to use the value for.
- (void)setShowsCloseButton:(BOOL)showsCloseButton forViewMode:(PSPDFViewMode)viewMode animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
