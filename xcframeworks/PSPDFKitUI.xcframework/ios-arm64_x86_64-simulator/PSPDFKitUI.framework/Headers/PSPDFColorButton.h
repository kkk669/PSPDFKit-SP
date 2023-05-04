//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFButton.h>

NS_ASSUME_NONNULL_BEGIN

/// The shape of color button.
typedef NS_ENUM(NSInteger, PSPDFColorButtonShape) {
    /// The color button will be a rounded rectangle.
    PSPDFColorButtonShapeRoundedRect = 0,
    /// The color button will be an ellipse drawn within the frame.
    PSPDFColorButtonShapeEllipse,
} PSPDF_ENUM_SWIFT(ColorButton.Shape);

/// Button that shows a selected color. Highlightable.
PSPDF_CLASS_SWIFT(ColorButton)
@interface PSPDFColorButton : PSPDFButton<PSPDFOverridable>

/// The shape of the button. Defaults to rounded rectangle.
@property (nonatomic) PSPDFColorButtonShape shape;

/// The inset of button content in relation to its bounds.
@property (nonatomic) UIEdgeInsets contentInset;

/// Current color.
@property (nonatomic, nullable) UIColor *color;

/// Inner border color. Defaults to semi-transparent black.
@property (nonatomic, nullable) UIColor *innerBorderColor;

/// Inner border width. Defaults to 1.
@property (nonatomic) CGFloat innerBorderWidth;

/// Outer border color. Defaults to the tint color.
@property (nonatomic, nullable) UIColor *outerBorderColor;

/// Outer border width. Defaults to 2.
@property (nonatomic) CGFloat outerBorderWidth;

/// Padding between outer border and inner border. Defaults to 2.
@property (nonatomic) CGFloat outerBorderPadding;

@end

NS_ASSUME_NONNULL_END
