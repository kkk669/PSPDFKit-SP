//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Will always be drawn in a circle. Width and height are the same, using the smallest side of the frame's size.
@interface PSPDFCheckbox : UIControl

/// Determines the state of the checkbox. Can also be set and the checkbox updates. Defaults to `false`.
@property (nonatomic, getter=isOn) BOOL on;

/// Line width used for the checkbox border width and the checkmark line width. Defaults to 2.5.
@property (nonatomic) CGFloat lineWidth UI_APPEARANCE_SELECTOR;

/// Set the checkbox highlighted/unhighlighted.
- (void)setCheckboxHighlighted:(BOOL)isHighlighted;

// MARK: Checkbox

/// Background color of the checkbox in the off state. Defaults to clear.
@property (nonatomic) UIColor *checkboxUnselectedBackgroundColor UI_APPEARANCE_SELECTOR;

/// Background color of the checkbox in the on state.
/// Defaults to `systemGrayColor`.
///
@property (nonatomic) UIColor *checkboxSelectedBackgroundColor UI_APPEARANCE_SELECTOR;

/// Background color of the checkbox, used in the highlighted/touched state.
/// Defaults to `systemGray2Color`.
@property (nonatomic) UIColor *checkboxHighlightBackgroundColor UI_APPEARANCE_SELECTOR;

/// Border color of the checkbox. Defaults to clear.
@property (nonatomic) UIColor *checkboxBorderColor UI_APPEARANCE_SELECTOR;

// MARK: Checkmark

/// Color of the checkmark, in the off state.
/// Defaults to `systemGray2Color`.
@property (nonatomic) UIColor *checkmarkUnselectedColor UI_APPEARANCE_SELECTOR;

/// Color of the checkmark, used when the checkbox is on.
/// Defaults to `systemBackgroundColor`.
@property (nonatomic) UIColor *checkmarkSelectedColor UI_APPEARANCE_SELECTOR;

/// Color of the checkmark, used in the highlighted/touched state.
/// Defaults to `systemBackgroundColor`.
@property (nonatomic) UIColor *checkmarkHighlightedColor UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END
