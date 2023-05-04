//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFToolbar.h>

@protocol PSPDFSystemBar;
@class PSPDFFlexibleToolbarDragView, PSPDFFlexibleToolbar, PSPDFToolbarCollapsedButton, PSPDFMenuItem;

typedef NS_OPTIONS(NSUInteger, PSPDFFlexibleToolbarPosition) {
    /// Undefined position. Upon display the toolbar can select an appropriate default
    /// position or restore position from previous runs.
    PSPDFFlexibleToolbarPositionNone = 0,
    /// The toolbar replaces the top (navigation)bar.
    PSPDFFlexibleToolbarPositionInTopBar = 1 << 0,
    /// The toolbar is positioned on the left side of the available screen real estate.
    PSPDFFlexibleToolbarPositionLeft = 1 << 1,
    /// The toolbar is positioned on the right side of the available screen real estate.
    PSPDFFlexibleToolbarPositionRight = 1 << 2,
    /// The toolbar is positioned at the top, below the navigation bar.
    PSPDFFlexibleToolbarPositionTop = 1 << 3,
    /// The toolbar is positioned on the left or right side of the available screen real estate.
    PSPDFFlexibleToolbarPositionHorizontal = PSPDFFlexibleToolbarPositionInTopBar | PSPDFFlexibleToolbarPositionTop,
    /// The toolbar is positioned in the top (navigation)bar or below it.
    PSPDFFlexibleToolbarPositionVertical = PSPDFFlexibleToolbarPositionLeft | PSPDFFlexibleToolbarPositionRight,
    /// The default toolbar positions in the top (navigation)bar and on the left and right side of the available screen real estate.
    PSPDFFlexibleToolbarPositionDefault = PSPDFFlexibleToolbarPositionInTopBar | PSPDFFlexibleToolbarPositionVertical,
    /// All valid toolbar positions. Excluding `PSPDFFlexibleToolbarPositionNone`.
    PSPDFFlexibleToolbarPositionAll = PSPDFFlexibleToolbarPositionHorizontal | PSPDFFlexibleToolbarPositionVertical,
} PSPDF_ENUM_SWIFT(FlexibleToolbar.Position);

typedef NS_CLOSED_ENUM(NSInteger, PSPDFToolbarGroupButtonIndicatorPosition) {
    /// The toolbar button groping indicator will not not be shown.
    PSPDFToolbarGroupButtonIndicatorPositionNone = 0,
    /// The toolbar button groping indicator will be positioned on the bottom left side of the button.
    PSPDFToolbarGroupButtonIndicatorPositionBottomLeft,
    /// The toolbar button groping indicator will be positioned on the bottom right side of the button.
    PSPDFToolbarGroupButtonIndicatorPositionBottomRight,
} PSPDF_ENUM_SWIFT(ToolbarGroupButton.IndicatorPosition);

#define PSPDFFlexibleToolbarGroupIndicatorPositionForToolbarPosition(position) ((position == PSPDFFlexibleToolbarPositionRight) ? PSPDFToolbarGroupButtonIndicatorPositionBottomLeft : PSPDFToolbarGroupButtonIndicatorPositionBottomRight)

#define PSPDFFlexibleToolbarPositionIsHorizontal(position) ((position) == PSPDFFlexibleToolbarPositionInTopBar || (position) == PSPDFFlexibleToolbarPositionTop)
#define PSPDFFlexibleToolbarPositionIsVertical(position) ((position) == PSPDFFlexibleToolbarPositionLeft || (position) == PSPDFFlexibleToolbarPositionRight)

NS_ASSUME_NONNULL_BEGIN

PSPDF_PROTOCOL_SWIFT(FlexibleToolbarDelegate)
@protocol PSPDFFlexibleToolbarDelegate<NSObject>

@optional

/// The toolbar container will be displayed (called before `showToolbarAnimated:completion:` is performed).
- (void)flexibleToolbarWillShow:(PSPDFFlexibleToolbar *)toolbar;

/// The toolbar container has been displayed (called after `showToolbarAnimated:completion:` is performed).
- (void)flexibleToolbarDidShow:(PSPDFFlexibleToolbar *)toolbar;

/// The toolbar container will be hidden (called before `hideToolbarAnimated:completion:` is performed).
- (void)flexibleToolbarWillHide:(PSPDFFlexibleToolbar *)toolbar;

/// The toolbar container has been hidden (called after `hideToolbarAnimated:completion:` is performed).
- (void)flexibleToolbarDidHide:(PSPDFFlexibleToolbar *)toolbar;

/// Called whenever the flexible toolbar changes position in response to a user drag & drop action
- (void)flexibleToolbar:(PSPDFFlexibleToolbar *)toolbar didChangePosition:(PSPDFFlexibleToolbarPosition)position;

@end

/// A custom toolbar, that can be dragged around the screen and anchored to different positions.
///
/// This class holds an array of `UIButton` objects. For best results use `PSPDFToolbarButton` or one of its subclasses.
/// PSPDFFlexibleToolbar should be used in combination with a `PSPDFFlexibleToolbarContainer` instance.
/// The bar's visual appearance can be customized using UIAppearance compliant properties.
///
/// @see `PSPDFFlexibleToolbarContainer`
PSPDF_CLASS_SWIFT(FlexibleToolbar)
@interface PSPDFFlexibleToolbar : PSPDFToolbar

/// A list of valid toolbar positions.
///
/// Defaults to `PSPDFFlexibleToolbarPositionDefault` on iOS and `PSPDFFlexibleToolbarPositionInTopBar` on Mac Catalyst.
///
/// @note: Change this before setting `toolbarPosition`, else any unsupported `toolbarPosition` is rejected.
@property (nonatomic) PSPDFFlexibleToolbarPosition supportedToolbarPositions;

/// Current toolbar position.
///
/// @see setToolbarPosition:animated:
///
/// @note Ensure that any new toolbar position is supported in `supportedToolbarPositions`, else the value is rejected.
@property (nonatomic) PSPDFFlexibleToolbarPosition toolbarPosition;

/// Sets the toolbar position and optionally animates the change
///
/// When `PSPDFFlexibleToolbarPositionNone` is used (the default value) the toolbar can select
/// an appropriate default position or restore position from previous runs.
///
/// @param toolbarPosition The new toolbar position to set.  Limited to `supportedToolbarPositions`.
/// @param animated Whether the toolbar should animate into the new position (move or fade, depending on whether the orientation changes).
- (void)setToolbarPosition:(PSPDFFlexibleToolbarPosition)toolbarPosition animated:(BOOL)animated;

/// Toolbar delegate. (Can be freely set to any receiver)
@property (nonatomic, weak) id<PSPDFFlexibleToolbarDelegate> toolbarDelegate;

/// Enables or disables toolbar dragging (hides the `dragView` when disabled).
/// `isDragEnabled` will return NO if `supportedToolbarPositions` has only one possible position.
///
/// Defaults to YES on iOS and NO on Mac Catalyst.
@property (nonatomic, getter=isDragEnabled) BOOL dragEnabled;

/// The currently selected button. The selected button is indicated by a selection bezel behind the button.
/// The selected button's tint color gets automatically adjusted to `selectedTintColor` as well.
@property (nonatomic, nullable) UIButton *selectedButton;

/// Sets the selection button and optionally fades the selection view.
- (void)setSelectedButton:(nullable UIButton *)button animated:(BOOL)animated;

// MARK: Presentation

/// Shows the toolbar (optionally by fading it in).
- (void)showToolbarAnimated:(BOOL)animated completion:(nullable void (^)(BOOL finished))completionBlock;

/// Hides the toolbar (optionally by fading it out).
- (void)hideToolbarAnimated:(BOOL)animated completion:(nullable void (^)(BOOL finished))completionBlock;

// MARK: Styling

/// Drag indicator view, positioned on the right or bottom of the toolbar (depending on the toolbar orientation).
/// Drag & drop gesture recognizers (UIPanGestureRecognizer) should be added to this view.
/// Visible only if `dragEnabled` is set to YES.
@property (nonatomic, readonly) PSPDFFlexibleToolbarDragView *dragView;

/// The tint color for selected buttons.
/// Defaults to `standardAppearance.backgroundColor` if available, or `barTintColor` if available, otherwise
/// an attempt is made to select an appropriate color based on the `backgroundView` appearance.
@property (nonatomic) UIColor *selectedTintColor UI_APPEARANCE_SELECTOR;

/// The selection bezel color.
/// Defaults to self.tintColor.
@property (nonatomic) UIColor *selectedBackgroundColor UI_APPEARANCE_SELECTOR;

/// Toolbar positions that draw a thin border around the toolbar.
/// Defaults to `PSPDFFlexibleToolbarPositionAll`.
@property (nonatomic) PSPDFFlexibleToolbarPosition borderedToolbarPositions UI_APPEARANCE_SELECTOR;

/// Toolbar positions that draw a faint shadow around the toolbar.
/// Defaults to `PSPDFFlexibleToolbarPositionVertical`.
@property (nonatomic) PSPDFFlexibleToolbarPosition shadowedToolbarPositions UI_APPEARANCE_SELECTOR;

/// Toolbar positions that slightly round the background view.
/// Defaults to `PSPDFFlexibleToolbarPositionVertical`.
@property (nonatomic) PSPDFFlexibleToolbarPosition roundedToolbarPositions UI_APPEARANCE_SELECTOR;

/// Matches the toolbar appearance to the provided UINavigationBar or UIToolbar.
/// Includes `barTintColor`, `tintColor`, `barStyle`, `translucency`, `standardAppearance` and `compactAppearance`.
/// The `barTintColor`, `tintColor`, `standardAppearance` and  `compactAppearance` are only matched if the haven't been already explicitly set (using properties or UIAppearance).
- (void)matchUIBarAppearance:(UIView<PSPDFSystemBar> *)navigationBarOrToolbar;

// MARK: Metrics

/// Returns the toolbars native size for the provided position, bound to the `availableSize`.
/// Internally used by the container view to correctly position the toolbar and anchor views during drag & drop.
/// The toolbar height will be increased when docked underneath the status bar by `PSPDFFlexibleToolbarContainer`.
///
/// @see -[PSPDFFlexibleToolbarContainer rectForToolbarPosition:]
- (CGSize)preferredSizeFitting:(CGSize)availableSize forToolbarPosition:(PSPDFFlexibleToolbarPosition)position;

// MARK: Menu

/// Shows a menu (UIMenuController) for a specific button.
///
/// @param menuItems An array of PSPDFMenuItem objects.
/// @param target The target view (most commonly on of the buttons) used to anchor the menu arrow.
/// @param animated Whether to animate the menu presentation or not.
- (void)showMenuWithItems:(NSArray<PSPDFMenuItem *> *)menuItems target:(UIView *)target animated:(BOOL)animated;

/// Called when the `collapsedButton` menu action is invoked.
/// The default implementation uses `menuItemForButton:` to convert buttons into menu items
/// and than calls through to `showMenuWithItems:target:animated:`.
- (void)showMenuForCollapsedButtons:(NSArray<__kindof UIButton *> *)buttons fromButton:(UIButton *)sourceButton animated:(BOOL)animated;

/// Converts buttons into similarly styled menu items
- (PSPDFMenuItem *)menuItemForButton:(UIButton *)button;

@end

NS_ASSUME_NONNULL_END
