//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//
#import <PSPDFKitUI/PSPDFFlexibleToolbar.h>

#import <PSPDFKit/PSPDFMacros+Private.h>

@class PSPDFFlexibleToolbarContainer;

PSPDF_EXTERN const CGFloat PSPDFFlexibleToolbarContentEdgeInset;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFFlexibleToolbar () <UIContextMenuInteractionDelegate>

/// The superview (casted to `PSPDFFlexibleToolbarContainer`)
@property (nonatomic, readonly, nullable) PSPDFFlexibleToolbarContainer *toolbarContainer;

/// Measures the size needed to display the toolbar.
- (CGFloat)contentLengthForToolbarPosition:(PSPDFFlexibleToolbarPosition)position;

/// Length of the secondary background that is added at the bottom edge (for vertical positions), or
/// trailing edge (for horizontal positions) of the toolbar.
- (CGFloat)secondaryBackgroundLengthForToolbarPosition:(PSPDFFlexibleToolbarPosition)position;

/// Measures the size needed to display `buttons`.
- (CGFloat)contentLengthForButtons:(NSArray *)buttons buttonLength:(CGFloat)defaultLength;

/// The maximal content length for for the toolbar position given available container space.
///
/// @param position The toolbar position for which the calculations should be performed.
/// @return The maximum content length available for buttons (excluding spacing).
- (CGFloat)maximalContentLengthForToolbarPosition:(PSPDFFlexibleToolbarPosition)position;

/// Returns the fixed size or width for the giver toolbar position. This is also the default button size.
- (CGFloat)fixedDimensionForPosition:(PSPDFFlexibleToolbarPosition)position;

/// Creates menu elements (actions) that match the button's functionality.
///
/// Used as menu elements on the collapsed button shown when there is not enough space
/// to fit all toolbar buttons on screen.
///
/// Override the `menuElementsForButton:` if there's a need for more than one menu action per button
/// or a need to customize the button's actions.
///
/// @param button The button that should be represented in the menu.
/// @return One or more menu elements that represent the button's actions.
- (NSArray<UIMenuElement *> *)menuElementsForButton:(UIButton *)button;

/// Creates an action that match the button's functionality.
///
/// Used as menu elements on the collapsed button shown when there is not enough space
/// to fit all toolbar buttons on screen.
///
/// Override the `menuActionForButton:` if there's a need to customize the button's action.
///
/// @param button The button that should be represented in the menu.
/// @return An action that represents the button.
- (UIAction *)menuActionForButton:(UIButton *)button;

/// Reloads menu elements provided by `menuElementsForButton:` or `menuActionForButton:` methods
///
/// Used to keep up the menu elements state (such as disabled or enabled) with the current model state.
- (void)reloadMenuElements;

/// The radius the toolbar background uses.
/// Derived from the `fixedDimension`.
@property (nonatomic, readonly) CGFloat cornerRadius;

@end

# pragma mark - Testing

/// This notification is triggered whenever the `PSPDFFlexibleToolbar.collapsedButton` is pressed for its context menu.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFFlexibleToolbarCollapsedButtonContextMenuTriggeredNotification;

NS_ASSUME_NONNULL_END
