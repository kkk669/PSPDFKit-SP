//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFTextParser.h>

#ifdef __cplusplus
#import <vector>
#endif

NS_ASSUME_NONNULL_BEGIN

@class PSPDFParagraph;

@interface PSPDFTextParser ()

/// Designated initializer.
///
/// @note **Important:** This will actually parse the page to extract its text if the core object has not been created yet!
///
/// @param pageIndex The index of the page, relative to the `documentProvider`.
- (nullable instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex documentProvider:(PSPDFDocumentProvider *)documentProvider;

/// The paragraphs from the Core text parser.
@property (nonatomic, copy, readonly) NSArray<PSPDFParagraph *> *paragraphs;

- (void)parseTextBlocksIfRequired;

/// Finds the glyph closest to the passed in point.
///
/// @param point The point, in PDF coordinates, near which the search is to be performed.
/// @return The text index of the glyph near `point` if one could be found, else `NSNotFound`.
///
/// @note `PSPDFTextParser.glyphs` is sorted by their `textIndex`, so the returned index can be used for directly accessing the glyph, instead of searching for it.
- (NSUInteger)textIndexOfGlyphClosestToPDFPoint:(CGPoint)point;

/// Finds glyphs in the given rectangle.
///
/// @param rect Rectangle in PDF coordinates in which the search is to be performed.
/// @return An array of glyphs found in `rect`.
- (NSArray<PSPDFGlyph *> *)glyphsInRect:(CGRect)rect;

#ifdef __cplusplus

/// Finds the text blocks within a given range of glyphs. The range is based on the glyphs' `textIndex`.
///
/// @param range The range of glyphs within which the text blocks are to be retrieved.
/// @return A `std::vector<NSRange>`, where each `NSRange` is a block of text.
- (std::vector<NSRange>)textBlocksWithGlyphsInRange:(NSRange)range;

#endif // __cplusplus

@end

NS_ASSUME_NONNULL_END
