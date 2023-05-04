//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>
#import <PSPDFKitUI/PSPDFCustomTitleCell.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

@class PSPDFTextField;

NS_ASSUME_NONNULL_BEGIN

/// Cell that shows a label and a text field. If you only need a text field, use `PSPDFFullSizeTextFieldCell`.
PSPDF_APP_CLASS_SWIFT(TextFieldCell)
@interface PSPDFTextFieldCell : PSPDFTableViewCell <PSPDFCustomTitleCell>

/// The text field.
@property (nonatomic, readonly) PSPDFTextField *textField;

/// If YES then the textField will have the opposite of natural text alignment
/// and the clear button will always be shown.
/// If NO then the textField will have natural text alignment
/// and the clear button will show only while editing.
/// Defaults to NO.
///
/// Currently the implementation of this property does not handle setting this back to NO.
/// It should just be set to YES after the cell is created.
@property (nonatomic) BOOL prefersOppositeAlignedTextField;

/// If YES, titleLabel will use the theme’s secondaryTextColor or gray if theming is not used.
/// If NO, titleLabel will use the theme’s primaryTextColor or black if theming is not used.
/// This must be set before the theme is applied.
/// Defaults to NO.
@property (nonatomic) BOOL labelUsesSecondaryTextColor;

/// Custom label used instead of textLabel.
@property (nonatomic, readonly) UILabel *titleLabel;

@property (nonatomic, readonly, nullable) UILabel *textLabel PSPDF_UNAVAILABLE("Use titleLabel");
@property (nonatomic, readonly, nullable) UILabel *detailTextLabel PSPDF_UNAVAILABLE("Not available");

@end

/// Cell that shows only a text field. If you need a label, use PSPDFTextFieldCell.
PSPDF_APP_CLASS_SWIFT(FullSizeTextFieldCell)
@interface PSPDFFullSizeTextFieldCell : PSPDFTableViewCell

/// The text field.
@property (nonatomic, readonly) PSPDFTextField *textField;

@property (nonatomic, readonly, nullable) UILabel *textLabel PSPDF_UNAVAILABLE("Use titleLabel");
@property (nonatomic, readonly, nullable) UILabel *detailTextLabel PSPDF_UNAVAILABLE("Not available");

@end

NS_ASSUME_NONNULL_END
