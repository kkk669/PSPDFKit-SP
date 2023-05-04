//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFButton.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbar.h>

// Uses the UIControlEventApplicationReserved range.
typedef NS_OPTIONS(NSUInteger, PSPDFToolbarButtonControlEvents) {
    /// Custom event for periodic button actions.
    PSPDFControlEventTick = 1 << 24,

    /// Similar to `UIControlEventTouchUpInside` but only sent if the button was
    /// not sending `PSPDFControlEventTick` events before the touch up.
    PSPDFControlEventTouchUpInsideIfNotTicking = 1 << 25
} PSPDF_ENUM_SWIFT(ToolbarButton.ControlEvents);

NS_ASSUME_NONNULL_BEGIN

/// A UIButton subclass that mimic the appearance of plain style UIBarButtonItems.
PSPDF_CLASS_SWIFT(ToolbarButton)
@interface PSPDFToolbarButton : PSPDFButton<PSPDFOverridable>

/// Sets the main button image. Sets it as the button image for several button states.
@property (nonatomic, nullable) UIImage *image;

/// When set the button will automatically switch to the small image if its height is less or equal to 32pt.
@property (nonatomic, nullable) UIImage *smallSizeImage;

/// Toggles the appearance between the highlighted and normal state.
- (void)styleForHighlightedState:(BOOL)highlighted;

/// General purpose user data storage.
@property (nonatomic, nullable) id userInfo;

/// Allows animated transitions between the enabled and disabled appearance.
- (void)setEnabled:(BOOL)enabled animated:(BOOL)animated;

// MARK: Metrics

/// Designates the button to be collapsible into one item, if toolbar space is limited.
/// Defaults to YES.
@property (nonatomic, getter=isCollapsible) BOOL collapsible;

/// The fixed length value. Will become the button width or height depending on the toolbar orientation.
/// Set to -1. to use the default toolbar length (the default).
@property (nonatomic) CGFloat length;

/// Automatically sets the length to the intrinsic size width.
- (void)setLengthToFit;

/// If YES, the actual button space will be computed dynamically by counting all button instances
/// and dividing the remaining available toolbar space with that number. Otherwise the length will be
/// taken from the `length` property. Defaults to NO.
@property (nonatomic, getter=isFlexible) BOOL flexible;

// MARK: Appearance

/// Called whenever the tint color changes. Use to update tint color dependent
/// content (like a tint color based custom drawn image or attributed text).
@property (nonatomic, copy, nullable) void (^tintColorDidChangeBlock)(UIColor *tintColor);

@end

/// Buttons that can be used as spacers for the  toolbar
/// (similar to UIBarButtonSystemItemFlexibleSpace and UIBarButtonSystemItemFixedSpace).
/// Does not allow user interaction and is not visible, but takes up space on the toolbar.
/// Use the properties described under "Metrics" form `PSPDFToolbarButton` for sizing.
PSPDF_CLASS_SWIFT(ToolbarSpacerButton)
@interface PSPDFToolbarSpacerButton : PSPDFToolbarButton

/// Convenience factory method for creating flexible spacer button.
+ (instancetype)flexibleSpacerButton;

@end

/// Sends out `PSPDFControlEventTick` events while the button is pressed.
PSPDF_CLASS_SWIFT(ToolbarTickerButton)
@interface PSPDFToolbarTickerButton : PSPDFToolbarButton

/// The time interval between subsequent tick events.
@property (nonatomic) NSTimeInterval timeInterval;

/// If set, gradually decreases the time interval between subsequent ticks. Defaults to YES.
@property (nonatomic) BOOL accelerate;

@end

/// A custom spacer button that visually separates button groups.
PSPDF_CLASS_SWIFT(ToolbarSeparatorButton)
@interface PSPDFToolbarSeparatorButton : PSPDFToolbarSpacerButton

/// The tinted separator view.
@property (nonatomic, readonly) UIView *hairlineView;

@end

PSPDF_CLASS_SWIFT(ToolbarSelectableButton)
@interface PSPDFToolbarSelectableButton : PSPDFToolbarButton

/// Shows the selected state, optionally animating the change.
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

// MARK: Styling

/// Selected tint color.
/// Inferred from the parent toolbar by default.
@property (nonatomic) UIColor *selectedTintColor UI_APPEARANCE_SELECTOR;

/// Selection indicator bezel color.
/// Defaults to `tintColor` (matches `tintColor` when set to nil).
@property (nonatomic) UIColor *selectedBackgroundColor UI_APPEARANCE_SELECTOR;

/// The selection view padding from the button edge.
/// Automatically set to an appropriate value for `PSPDFToolbar` when negative (default).
@property (nonatomic) CGFloat selectionPadding UI_APPEARANCE_SELECTOR;

/// If yes, a the selection indicator will be faded in when the button is highlighted.
/// Defaults to NO.
@property (nonatomic) BOOL highlightsSelection;

@end

/// Toolbar button that shows a light gray rounded border.
PSPDF_CLASS_SWIFT(ToolbarBorderButton)
@interface PSPDFToolbarBorderButton : PSPDFToolbarButton

@end

/// PSPDFToolbarButton with a grouping disclosure indicator.
PSPDF_CLASS_SWIFT(ToolbarGroupButton)
@interface PSPDFToolbarGroupButton : PSPDFToolbarButton<PSPDFOverridable>

/// The location of the disclosure indicator on the button.
@property (nonatomic) PSPDFToolbarGroupButtonIndicatorPosition groupIndicatorPosition;

@end

/// PSPDFToolbarButton that combines two buttons into one.
PSPDF_CLASS_SWIFT(ToolbarDualButton)
@interface PSPDFToolbarDualButton : PSPDFToolbarButton

/// The primary button image.
@property (nonatomic, nullable) UIImage *primaryImage;

/// The secondary button image. Gets composited together with `primaryImage`.
@property (nonatomic, nullable) UIImage *secondaryImage;

/// Draws `primaryImage` faded-out when set to `false`. Prevents action dispatch when enabled.
@property (nonatomic) BOOL primaryEnabled;

/// Draws `secondaryImage` faded-out when set to `false`.
@property (nonatomic) BOOL secondaryEnabled;

@end

/// Special `PSPDFToolbarGroupButton` used for the collapsed button item.
PSPDF_CLASS_SWIFT(ToolbarCollapsedButton)
@interface PSPDFToolbarCollapsedButton : PSPDFToolbarGroupButton

/// A button whose appearance is mimicked.
@property (nonatomic, nullable) UIButton *mimickedButton;

@end

NS_ASSUME_NONNULL_END
