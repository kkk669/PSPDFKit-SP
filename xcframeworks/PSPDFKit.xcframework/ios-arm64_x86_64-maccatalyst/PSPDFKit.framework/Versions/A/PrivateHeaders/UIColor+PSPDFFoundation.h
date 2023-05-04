//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (PSPDFFoundation)

// MARK: - Integer representation

/// Constructor that creates a color from an ARGB integer.
+ (UIColor *)pspdf_colorWithARGB32:(int32_t)argb32Value;

// MARK: - Component values

/// Gets the red, green, blue and alpha components of the color.
- (BOOL)pspdf_getRed:(CGFloat *)red green:(CGFloat *)green blue:(CGFloat *)blue alpha:(nullable CGFloat *)alpha NS_SWIFT_UNAVAILABLE("Use rgbaComponents(clamped:) instead");

/// Gets the red, green, blue and alpha components of the color, optionally clamping them to [0.0, 1.0].
- (BOOL)pspdf_getRed:(CGFloat *)red green:(CGFloat *)green blue:(CGFloat *)blue alpha:(nullable CGFloat *)alpha clamped:(BOOL)clamped NS_REFINED_FOR_SWIFT;

/// Component access.
///
/// @note Please resolve the color using appropriate traits
/// before using this API in case it is a dynamic color.
@property (nonatomic, readonly) CGFloat pspdf_alphaComponent NS_SWIFT_NAME(alphaComponent);

// MARK: - Standard colors

/// Default alpha for various selection views.
@property (class, nonatomic, readonly) CGFloat pspdf_selectionAlpha NS_SWIFT_NAME(selectionAlpha);

/// Color for guide helpers.
@property (class, nonatomic, readonly) UIColor *pspdf_guideColor NS_SWIFT_NAME(guideColor);

#if TARGET_OS_MACCATALYST

/// `+[NSColor selectedContentBackgroundColor]`.
@property (class, nonatomic, readonly) UIColor *pspdf_selectedContentBackgroundColor;

/// `+[NSColor unemphasizedSelectedContentBackgroundColor]`.
@property (class, nonatomic, readonly) UIColor *pspdf_unemphasizedSelectedContentBackgroundColor;
#endif

/// Creates a checkered pattern of color
///
/// @param backgroundColor Color to be used as the background color for the checker pattern.
/// @param checkerColor Color to be used to draw the checkers on the background.
/// @param checkerSize Size of the checker squares.
/// @param screenScale Screen scale of the view the this color is intended to be used.
+ (UIColor *)pspdf_checkerColorWithBackgroundColor:(UIColor *)backgroundColor checkerColor:(UIColor *)checkerColor checkerSize:(CGFloat)checkerSize screenScale:(CGFloat)screenScale;

/// A neutral checker pattern used for semi-translucent color rendering.
+ (UIColor *)pspdf_checkerColorWithSize:(CGFloat)patternSize screenScale:(CGFloat)screenScale;

// MARK: - String representation

/// Property list support.
///
/// @return nil if the colorObject is neither a parsable string nor an `UIColor` object.
+ (nullable UIColor *)pspdf_colorFromPropertyRepresentation:(id)colorObject;

/// Returns color in string format. ({%f, %f, %f, %f} or {%f, %f} if there's no color)
@property (nonatomic, readonly, nullable) NSString *pspdf_colorString;

/// Hex support (#FFFFFF or #FFF). White space is ignored.
+ (nullable UIColor *)pspdf_colorWithHexString:(NSString *)colorString NS_SWIFT_NAME(init(hexString:));
@property (nonatomic, readonly) NSString *pspdf_hexString;

/// Parses CSS format rgb(100, 100, 100). White space is ignored.
/// Falls back to hex parsing if `rgb` token wasn't found.
+ (nullable UIColor *)pspdf_colorWithCSSString:(NSString *)colorString;

/// RG Representation, as seen in XFDF default appearance.
@property (nonatomic, readonly) NSString *pspdf_RGString;

// MARK: - HSL

/// Creates and returns a color object specified by HSLA values.
+ (UIColor *)pspdf_colorWithHue:(CGFloat)hue saturation:(CGFloat)saturation lightness:(CGFloat)lightness alpha:(CGFloat)alpha;

/// Returns by reference the components that make up the color in HSLA.
- (BOOL)pspdf_getHue:(nullable CGFloat *)hue saturation:(nullable CGFloat *)saturation lightness:(nullable CGFloat *)lightness alpha:(nullable CGFloat *)alpha NS_SWIFT_UNAVAILABLE("Use hslComponents(clamped:) instead");

/// Returns by reference the components that make up the color in HSLA, optionally clamping the values to [0.0, 1.0].
- (BOOL)pspdf_getHue:(nullable CGFloat *)hue saturation:(nullable CGFloat *)saturation lightness:(nullable CGFloat *)lightness alpha:(nullable CGFloat *)alpha clamped:(BOOL)clamped  NS_REFINED_FOR_SWIFT;

// MARK: - Derived colors

/// Performs alpha compositing of two colors.
///
/// This matches what the system would do if we draw elements with those colors on top of
/// each other with the default bend mode.
///
/// @param topColor The color that is drawn on top of the receiver.
/// @return The composited color or nil if compositing failed (for non-grayscale or non-RGBA colors).
- (nullable UIColor *)pspdf_colorByAlphaCompositing:(UIColor *)topColor;

/// Returns color multiplied by the parameters given.
///
/// @return Color or nil of we do not know how to deal with the underlying color object (component mismatch)
- (nullable UIColor *)pspdf_colorByMultiplyingByRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;
- (nullable UIColor *)pspdf_colorByMultiplyingBy:(CGFloat)value;

/// Derived colors. Default delta is 0.1.
@property (nonatomic, readonly) UIColor *pspdf_lightenedColor NS_SWIFT_NAME(lightened);
- (UIColor *)pspdf_lightenedColorWithDelta:(CGFloat)delta NS_SWIFT_NAME(lightened(withDelta:));

@property (nonatomic, readonly) UIColor *pspdf_darkenedColor NS_SWIFT_NAME(darkened);
- (UIColor *)pspdf_darkenedColorWithDelta:(CGFloat)delta NS_SWIFT_NAME(darkened(withDelta:));

/// Returns the color with an alpha channel of 1.f and `nil` for UIColor.clearColor.
@property (nonatomic, readonly, nullable) UIColor *pspdf_opaqueColor NS_SWIFT_NAME(opaque);

- (UIColor *)pspdf_colorWithMultipliedAlpha:(CGFloat)alpha NS_SWIFT_NAME(color(withMultipliedAlpha:));

/// Returns a color with inverted components (except alpha).
@property (nonatomic, readonly) UIColor *pspdf_invertedColor NS_SWIFT_NAME(inverted);

/// Applies a filter to an image of the color and returns the captured color.
- (UIColor *)pspdf_colorWithApplyingFilter:(CIFilter *)filter NS_SWIFT_NAME(color(withApplyingFilter:));

/// Returns a color correct inversion of the current color value.
@property (nonatomic, readonly) UIColor *pspdf_colorCorrectInvertedColor NS_SWIFT_NAME(colorCorrectInverted);

// MARK: - Image representation

/// Returns a resizable image filled with the receiver’s color.
/// This is useful to add state-dependant background colors to `UIButton`.
/// Supports dynamic colors.
@property (readonly) UIImage *pspdf_constantColorImage NS_SWIFT_NAME(constantColorImage);

@end

// MARK: -

/// Convert from RGB to HSB colorspace
PSPDF_SDK_EXPORT void PSPDFRGBtoHSB(CGFloat r, CGFloat g, CGFloat b, CGFloat *h, CGFloat *s, CGFloat *v);

/// Convert from HSB to RGB colorspace
PSPDF_EXTERN void PSPDFHSBtoRGB(CGFloat *r, CGFloat *g, CGFloat *b, CGFloat h, CGFloat s, CGFloat v);

/// Convert PDF color AP string to a color
PSPDF_EXTERN UIColor *_Nullable PSPDFParseRGColorString(NSString *appearanceString);

/// Converts an float array of 1, 3 or 4 elements to a color.
PSPDF_EXTERN UIColor *_Nullable PSPDFParseVariableLengthColorArray(NSArray<NSString *> *colors);

/// Save memory by de-duplicating color instances.
PSPDF_EXTERN UIColor *PSPDFDeduplicatedColorInstance(UIColor *color);
PSPDF_EXTERN UIColor *PSPDFTransparentColorInstance(void);

NS_ASSUME_NONNULL_END
