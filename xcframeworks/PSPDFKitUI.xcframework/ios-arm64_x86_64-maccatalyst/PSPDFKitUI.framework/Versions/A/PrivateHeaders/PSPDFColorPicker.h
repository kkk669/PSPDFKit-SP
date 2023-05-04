//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFColorPicker;

/// A color set describes a set of different color pickers that provide colors for
/// a certain use case.
///
/// @note The list of color sets may grow, keep this in mind when designing custom
/// color pickers and provide a suitable default (or fall back to PSPDFKit's
/// built-in color picker in this case).
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFColorSet) {
    /// The default color set, used for most foreground colors in PSPDFKit.
    PSPDFColorSetDefault,
    /// The default color set but including transparent / empty color. Mostly used for background colors through out PSPDFKit.
    PSPDFColorSetDefaultWithTransparency,
    /// The color set used when selecting page background colors. Its colors are suitable for full page background colors.
    PSPDFColorSetPageBackgrounds,
} PSPDF_ENUM_SWIFT(ColorPatch.ColorSet);

/// A color patch represents a single patch of colors in the UI. It contains of
/// one or multiple colors that should be grouped together.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ColorPatch)
@interface PSPDFColorPatch : NSObject

/// Create a color patch representing a single color.
///
/// @param color The color that this patch should represent.
///
/// @return A newly created instance of `PSPDFColorPatch` representing the passed in color.
+ (PSPDFColorPatch *)colorPatchWithColor:(UIColor *)color;

/// Create a color patch representing multiple colors.
///
/// @param colors The colors that this patch should represent.
///
/// @return A newly created instance of `PSPDFColorPatch` representing the passed in colors.
+ (PSPDFColorPatch *)colorPatchWithColors:(NSArray<UIColor *> *)colors;

/// The colors that this color patch represents.
@property (nonatomic, copy, readonly) NSArray<UIColor *> *colors;

@end

/// A color palette is a set of color patches that are grouped together based on a specific
/// look or theme.
///
/// @note Starting with iOS 14 PSPDFKit's default UI will display the system color picker
/// (`UIColorPickerViewController`) where possible. On macOS Big Sur and later the system
/// color picker will also be used for select options (e.g. the highlight annotation menu).
/// Customizing this API will have no effect on the system color picker.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ColorPalette)
@interface PSPDFColorPalette : NSObject

/// Creates a color palette with a given title and the patches it should group.
///
/// @param title   The title of the palette.
/// @param patches The color patches that should be grouped by this palette.
///
/// @return A new color palette.
+ (PSPDFColorPalette *)colorPaletteWithTitle:(NSString *)title colorPatches:(NSArray<PSPDFColorPatch *> *)patches;

/// Creates a color palette representing all colors of the hsv color space.
///
/// @param title The title of the palette.
///
/// @return A new color palette.
+ (PSPDFColorPalette *)hsvColorPaletteWithTitle:(NSString *)title;

/// The title of the color palette as shown in the UI.
@property (nonatomic, copy, readonly) NSString *title;

/// The color patches this color space represents.
@property (nonatomic, copy, readonly) NSArray<PSPDFColorPatch *> *colorPatches;

/// If a color palette has no dedicated colors but instead represents the whole
/// hsv color space, this property is `true`, `false` otherwise.
@property (nonatomic, readonly, getter=isHSVPalette) BOOL hsvPalette;

@end

@interface PSPDFColorPalette (PSPDFColorPalettes)

/// @return A unified color palette with 13 rainbow colors and 5 gray scale colors.
+ (PSPDFColorPalette *)unifiedColorPalette;

/// @return A unified color palette with 12 rainbow colors, 5 gray scale colors and a clear color.
+ (PSPDFColorPalette *)unifiedTransparentColorPalette;

/// @return A monochrome color palette containing 6 gray scale colors.
+ (PSPDFColorPalette *)monochromeColorPalette;

/// @return A monochrome color palette containing 5 gray scale colors and a clear color.
+ (PSPDFColorPalette *)monochromeTransparentPalette;

/// @return A modern color palette with 6 colors.
+ (PSPDFColorPalette *)modernColorPalette;

/// @return A vintage color palette with 6 colors.
+ (PSPDFColorPalette *)vintageColorPalette;

/// @return A color palette with 6 colors similar to those in a rainbow.
+ (PSPDFColorPalette *)rainbowColorPalette;

/// @return A color palette with colors suitable for page backgrounds.
+ (PSPDFColorPalette *)paperColorPalette;

/// @return A color palette representing the hsv color space.
+ (PSPDFColorPalette *)hsvColorPalette;

@end

/// The factory used to create color pickers. Subclass this to customize your color
/// pickers.
///
/// @note Starting with iOS 14 PSPDFKit's default UI will display the system color picker
/// (`UIColorPickerViewController`) where possible. On macOS Big Sur and later the system
/// color picker will also be used for select options (e.g. the highlight annotation menu).
/// Customizing this API will have no effect on the system color picker.
PSPDF_CLASS_SWIFT(ColorPickerFactory)
@interface PSPDFColorPickerFactory : NSObject

/// The color palettes for a certain color set.
///
/// @param colorSet The color set whose color palettes are requested.
///
/// @return An array of `PSPDFColorPalette`s representing the passed in color set.
+ (NSArray<PSPDFColorPalette *> *)colorPalettesInColorSet:(PSPDFColorSet)colorSet;

/// The class of view controller returned by `colorPickerViewControllerWithColorSet:`.
@property (nonatomic, readonly, class) Class colorPickerViewControllerClass;

/// Creates a single color picker view controller ready for presentation, containing
/// all color palettes of the given color set.
///
/// @param colorSet The color set to be presented.
///
/// @return A view controller conforming to the `PSPDFColorPicker` protocol.
+ (UIViewController<PSPDFColorPicker> *)colorPickerViewControllerWithColorSet:(PSPDFColorSet)colorSet;

/// Creates custom color pickers for certain color sets.
///
/// @param colorSet The color set whose color pickers are requested.
///
/// @return An array of `UIViewController`s that support the `PSPDFColorPicker` protocol
///         and provide colors that are suitable for the passed in set. Return the
///         value from calling `super` to indicate that you want to use the default
///         color pickers.
+ (NSArray<UIViewController<PSPDFColorPicker> *> *)colorPickersWithColorSet:(PSPDFColorSet)colorSet;

/// Creates a custom color picker for the given color palette.
///
/// @param colorPalette The color palette to be represented by the color picker.
///
/// @return A view controller that conforms to `PSPDFColorPicker`, representing the passed
///         in color palette or `nil` if you want to use the default color picker for this
///         color palette.
+ (nullable UIViewController<PSPDFColorPicker> *)colorPickerForColorPalette:(PSPDFColorPalette *)colorPalette;


@end

/// The color picker delegate is used to report when the user selected a color in
/// a color picker.
///
/// When providing your own color pickers you need to support the delegate as well.
@protocol PSPDFColorPickerDelegate <NSObject>

/// This method needs to be called whenever the user changes the color through
/// the interface.
///
/// @param colorPicker The color picker whose color was changed.
/// @param color       The color the user chose.
/// @param finished    If the color picker is interactive (e.g. a pan gesture is currently
///                    active), this should be `false` to inform the delegate that there are
///                    more color change events coming until the color is finally chosen.
///                    The last event in an interactive process and all events in a non
///                    interactive process should report `true`.
- (void)colorPicker:(id<PSPDFColorPicker>)colorPicker didSelectColor:(UIColor *)color finishedSelection:(BOOL)finished;

@end

/// A PSPDFColorPicker is used to provide custom color pickers to the framework
/// that will be shown instead of the build in color pickers.
@protocol PSPDFColorPicker <NSObject>

/// The delegate that should receive color updates when the user changes the color.
///
/// @note When calling `setSelectedColor:`, this should not trigger a delegate call.
///       Only color updates triggered by user interaction or through internal logic
///       should cause the delegate to be informed.
@property (nonatomic, weak) id<PSPDFColorPickerDelegate> colorPickerDelegate;

/// The currently selected color. When set, the UI should update accordingly.
/// If this property is `nil` that means that currently no color is selected in
/// the receiver.
@property (nonatomic, nullable) UIColor *selectedColor;

@end

NS_ASSUME_NONNULL_END
