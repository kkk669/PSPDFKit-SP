//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFMacros.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFRenderOptions, PSPDFAnnotation;

/// A block passed to PSPDFKit to render additional content or graphics on a page. Set it on `-[PSPDFRenderOptions drawBlock]`.
///
/// @param context The graphics context that should be drawn into.
/// @param pageIndex The index of the page being drawn.
/// @param pageRect A rectangle the size of the page being drawn, with zero origin.
/// @param options The `PSPDFRenderOptions` object that this block was attached to. For reference purposes only.
typedef void (^PSPDFRenderDrawBlock)(CGContextRef context, PSPDFPageIndex pageIndex, CGRect pageRect, PSPDFRenderOptions *options) NS_SWIFT_NAME(PDFRenderDrawBlock);

typedef NS_OPTIONS(NSUInteger, PSPDFRenderFilter) {
    /// If set, a grayscale filter will be applied.
    PSPDFRenderFilterGrayscale = 1 << 0,

    /// If set and `invertRenderColor` is `true`, the inverted mode (a.k.a. night mode) will be rendered color correct.
    PSPDFRenderFilterColorCorrectInverted = 1 << 1,

    /// If set, a sepia filter will be applied.
    PSPDFRenderFilterSepia = 1 << 2
} PSPDF_ENUM_SWIFT(RenderFilter);

// No support for macOS yet (CIFilter behaves differently there)
#define PSPDF_SUPPORTS_CIFILTER TARGET_OS_IOS

/// Defines the options to apply when rendering PDF pages, such as color inversion, filters,
/// colors and annotation behavior.
PSPDF_CLASS_SWIFT(RenderOptions)
@interface PSPDFRenderOptions : PSPDFModel

/// Changes the rendering to preserve the aspect ratio of the image. Defaults to `false`.
@property (nonatomic) BOOL preserveAspectRatio;

/// Controls whether the image is forced to render with a scale of 1.0. Defaults to `false`.
@property (nonatomic) BOOL ignoreDisplaySettings;

/// A color that is multiplied with the page content to color the pages. Defaults to `UIColor.clearColor`.
/// If the page content draws a white square, the resulting color of that square will be `pageColor`.
/// To set a background without tinting the page content, use `backgroundFill` instead.
@property (nonatomic) UIColor *pageColor;

/// Inverts the rendering output. Defaults to `false`.
@property (nonatomic) BOOL invertRenderColor;

/// Filters to be applied. Filters will increase rendering time. Defaults to no filters.
@property (nonatomic) PSPDFRenderFilter filters;

/// Set custom interpolation quality. Defaults to `kCGInterpolationHigh`.
@property (nonatomic) CGInterpolationQuality interpolationQuality;

/// Set to `true` to NOT draw page content. Defaults to NO. (Use to just draw an annotation).
@property (nonatomic) BOOL skipPageContent;

/// Set to `true` to render annotations that have `isOverlay = YES` set. Defaults to `false`.
@property (nonatomic) BOOL overlayAnnotations;

/// Skip rendering of any annotations that are in this array.
@property (nonatomic, nullable) NSArray<PSPDFAnnotation *> *skipAnnotationArray;

/// If `true`, will draw outside of page area. Defaults to `false`.
@property (nonatomic) BOOL ignorePageClip;

/// Enables/Disables antialiasing. Defaults to `true`.
@property (nonatomic) BOOL allowAntialiasing;

/// The page base color. Page content is drawn on top of this fill. Defaults to `UIColor.whiteColor`.
/// If the page content draws a white square, the resulting color of that square will be white regardless of the `backgroundFill`.
/// For a transparent background please set this property to `nil`. Setting this to `clear` instead will yield unexpected results.
/// To tint the page content too, use `pageColor` instead.
@property (nonatomic, nullable) UIColor *backgroundFill;

/// Whether native text rendering via Core Graphics should be used. Defaults to `true`.
///
/// @note Native text rendering usually yields better results but is slower.
@property (nonatomic) BOOL renderTextUsingCoreGraphics;

/// Sets the interactive fill color, which will override the fill color for all newly
/// rendered form elements that are editable.
///
/// The interactive fill color is used if a form element is editable by the user to
/// indicate that the user can interact with this form element.
///
/// @note This color is overlaid on top of the form contents. It is recommended to use
/// a color with low alpha to ensure the content is still legible with the overlay applied.
///
/// Defaults to a non-nil, translucent blue color.
/// Setting this property to nil will also result in this default color being used.
///
/// Set this property to clear to use the appearance specified in the PDF.
@property (nonatomic, nullable) UIColor *interactiveFormFillColor;

/// Sets the border color for required form fields. It is used when a form element is
/// marked as required to indicate a non-optional form element. Setting this property
/// to clear color will make the border invisible.
///
/// If this value is not set, the required form field border color defaults to red.
@property (nonatomic, nullable) UIColor *requiredFormBorderColor;

/// Allows custom content rendering after the PDF.
///
/// PSPDFKit’s render cache will not be used when this property is not nil.
@property (nonatomic, nullable) PSPDFRenderDrawBlock drawBlock;

/// Controls if the "Sign here" overlay should be shown on unsigned signature fields. Defaults to `true`.
@property (nonatomic) BOOL drawSignHereOverlay;

/// Controls if redaction annotations should be drawn in their redacted state, to preview the appearance of how
/// they would look if applied. By default redactions are rendered in their marked state.
///
/// Defaults to `false`.
@property (nonatomic) BOOL drawRedactionsAsRedacted;

#if PSPDF_SUPPORTS_CIFILTER
/// `CIFilter` objects that are applied to the rendered image before it is returned from the render pipeline.
///
/// @warning **Important:** When customizing this property, please make sure to not use the same kind of `CIFilter` with
/// different input parameters without customizing its `name`. `RenderOptions` are equality checked during cache lookup.
/// Using the standard implementation of `CIFilter` can cause overhead to the point of making PSPDFKit unusable and is
/// therefore substituted with a mere `name` check on the objects in this array.
@property (nonatomic, nullable) NSArray<CIFilter *> *additionalCIFilters;
#endif

// MARK: Annotation Drawing Options

/// Whether the annotations are drawn flattened when processing a document. Defaults to `false`.
@property (nonatomic) BOOL drawFlattened;

/// Set to `true` to specify that the annotation is being drawn for printing. Defaults to `false`.
@property (nonatomic) BOOL drawForPrinting;

/// If the annotation should be rendered centered within it's own context. Defaults to `false`.
@property (nonatomic) BOOL centered;

/// The margin that should be applied to the drawing annotation. Defaults to (0,0,0,0).
@property (nonatomic) UIEdgeInsets margin;

// MARK: Lifecycle

PSPDF_INIT_WITH_CODER_UNAVAILABLE

- (nullable instancetype)initWithDictionary:(nullable NSDictionary<NSString *, id> *)dictionaryValue error:(NSError * __autoreleasing _Nullable *)error PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
