//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFGlyph.h>

NS_ASSUME_NONNULL_BEGIN

/// Base class for Highlight, Underline, StrikeOut and Squiggly annotations.
/// You should never create instances of this class directly. Use one of its subclasses instead.
PSPDF_CLASS_SWIFT(TextMarkupAnnotation)
@interface PSPDFTextMarkupAnnotation : PSPDFAnnotation

/// Convenience initializer that creates a markup annotation from glyphs.
///
/// @param glyphs The glyphs from which the markup annotation is to be created. It should have at least one object, otherwise `nil` is returned.
///
/// @note This method should be called on a subclass, and not on this class directly.
///
/// @note The passed-in `PSPDFGlyph` instances do not carry information about the page index they are to be inserted at. Use `PSPDFAnnotation.pageIndex` on the `PSPDFTextMarkupAnnotation` instance returned from this method to set the appropriate page index.
+ (nullable instancetype)textOverlayAnnotationWithGlyphs:(nullable NSArray<PSPDFGlyph *> *)glyphs;

/// Convenience initializer that creates a text markup annotation from an array of rects to be marked up.
///
/// @param rects The rects, in PDF coordinates, that are to be marked up. Must have at least 1 rect, failing which `nil` is returned.
/// @param boundingBox The bounding box for the annotation.
/// @param pageIndex The page index the new annotation is on.
/// @return An instance of the markup annotation.
///
/// @note This method should be called on a subclass, and not on this class directly.
+ (nullable instancetype)textOverlayAnnotationWithRects:(NSArray<NSValue *> *)rects boundingBox:(CGRect)boundingBox pageIndex:(NSUInteger)pageIndex NS_REFINED_FOR_SWIFT;

/// Helper that will query the associated `Document` to get the marked up content.
/// (Because we actually just write rects, it's not easy to get the underlying text)
@property (atomic, readonly) NSString *markedUpString;

/// The default color for a freshly created text markup annotation.
@property (nonatomic, class, readonly) UIColor *defaultColor;

@end

/// Mask for all text markups. `PSPDFAnnotationTypeHighlight|PSPDFAnnotationTypeStrikeOut|PSPDFAnnotationTypeUnderline|PSPDFAnnotationTypeSquiggly`
PSPDF_EXPORT const PSPDFAnnotationType PSPDFAnnotationTypeTextMarkup;

NS_ASSUME_NONNULL_END
