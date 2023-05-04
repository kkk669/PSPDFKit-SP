//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseTableViewController.h>

#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

#define PSPDFMaxPopoverHeight 1400.

/// Indicates that we should allow animations, if the associated object is set to @YES.
PSPDF_EXTERN const char *PSPDFTableViewAllowAnimationsKey NS_SWIFT_NAME(TableViewAllowAnimationsKey);

/// Defines table view separator hiding modes.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSeparatorHidingMode) {
    /// Do not hide any cell separators.
    PSPDFSeparatorHidingModeNone,
    /// Hide extra cell separators below the table view.
    PSPDFSeparatorHidingModeAfterLastCell,
    /// Hide extra cell separators below the table view, including the last cell separator.
    PSPDFSeparatorHidingModeIncludingLastCell
} NS_SWIFT_NAME(SeparatorHidingMode);

@interface PSPDFBaseTableViewController ()

/// If enabled, popover size is changed as items are expanded/collapsed.
/// Defaults to NO, but will most likely be set to YES in the subclass.
@property (nonatomic) BOOL automaticallyResizesPopover;

/// If `automaticallyResizesPopover` is enabled, this defines the minimum height of the popover.
/// Defaults to 310.
@property (nonatomic) CGFloat minimumHeightForAutomaticallyResizingPopover;

/// By default, UIKit will show empty separator lines in plain style mode.
/// Use this to change the default behavior and hide entrain separators.
@property (nonatomic) PSPDFSeparatorHidingMode separatorHidingMode;

/// If hosted in a navigation controller, the bottom toolbar can be controlled via this property.
///
/// If number is a wrapped @(YES) or @(NO), view state will be customized.
/// The previous state will be retained and restored on a disappear event.
///
/// If set to nil (default), no action is taken.
@property (nonatomic, nullable) NSNumber *toolbarVisibilityState;

/// Recalculates the content size from UITableView.
- (void)recalculateContentSize;

/// Replace `UITableView` base with `UIView` as base with child `UITableView`.
- (void)replaceBaseTableViewWithRegularView;

/// Calls `reloadData` if the view is already loaded.
- (void)reloadDataIfViewLoaded;

// MARK: - Subclassing Hooks

/// Common initialization code. Requires calling super.
///
/// @note We make sure to invoke this during init, both for regular and NIB/Storyboards.
- (void)commonInit NS_REQUIRES_SUPER;

/// By default, popover size will be the tableView size.
/// Usually you want to override `requiredPopoverSize` instead.
- (void)updatePopoverSize;

/// Returns the required popover size. Override to customize.
@property (nonatomic, readonly) CGSize requiredPopoverSize;

/// Called when the font system base size is changed.
- (void)contentSizeDidChange NS_REQUIRES_SUPER;

/// Called in `viewDidAppear:` if the view has never previously appeared, or has fully disappeared since
/// the last time this was called. This is not called after a transition away from the view is cancelled.
- (void)viewDidAppearAfterNotBeingAppeared:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
