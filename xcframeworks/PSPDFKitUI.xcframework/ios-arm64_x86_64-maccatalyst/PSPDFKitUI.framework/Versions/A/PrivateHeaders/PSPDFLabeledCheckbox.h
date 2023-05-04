//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFCheckbox.h>

NS_ASSUME_NONNULL_BEGIN

/// A labeled checkbox, that consists of a checkbox and a (button) label.
/// Displayed in a view horizontally next to each other.
/// Handles highlighting and touch area insets.
@interface PSPDFLabeledCheckbox : UIView

/// Create a labeled checkbox with the `title` as the label and the `checkboxSize` used for the checkbox's width and height.
- (instancetype)initWithTitle:(NSString *)title checkboxSize:(CGFloat)checkboxSize;

/// Defines and sets if the checkbox is on or off. Defaults to `false`.
@property (nonatomic, getter=isOn) BOOL on;

/// The underlying checkbox.
@property (nonatomic, readonly) PSPDFCheckbox *checkbox;

// MARK: Colors

/// Background color of the labeled checkbox, when it's not selected.
@property (nonatomic) UIColor *unselectedBackgroundColor;

/// Background color of the labeled checkbox, when it's selected. If `nil`, `backgroundUnselectedColor` will be used.
@property (nonatomic, nullable) UIColor *selectedBackgroundColor;

/// Border color of the labeled checkbox, when it's not selected.
@property (nonatomic) UIColor *unselectedBorderColor;

/// Border color of the labeled checkbox, when it's not selected. If `nil`, `borderUnselectedColor` will be used.
@property (nonatomic, nullable) UIColor *selectedBorderColor;

/// Tells the labeled checkbox to resolve and update colors that are either dynamic
/// or derived from the underlying checkbox. Call this if you changed any
/// color-related property of `checkbox`.
- (void)setNeedsUpdateColors;

@end

NS_ASSUME_NONNULL_END

