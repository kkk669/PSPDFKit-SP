//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocumentProvider, PSPDFGlyph, PSPDFImageInfo, PSPDFTextBlock, PSPDFWord;

/// Parses text and glyph data of a PDF page.
///
/// @note Do not instantiate this class directly. Instead, use `-[PSPDFDocument textParserForPageAtIndex:]`. Properties
/// are evaluated lazily and cached.
PSPDF_CLASS_SWIFT(TextParser)
@interface PSPDFTextParser : NSObject<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The complete page text, in reading order, including extrapolated spaces and newline characters.
@property (nonatomic, copy, readonly) NSString *text;

/// Complete list of all glyphs defined in the PDF page. Control characters are excluded.
/// These glyphs are guaranteed to be stored in order of their `indexOnPage`.
@property (nonatomic, copy, readonly) NSArray<PSPDFGlyph *> *glyphs;

/// A list of words on the PDF page. We apply heuristics to the glyphs to detect word boundaries in the text.
@property (nonatomic, copy, readonly) NSArray<PSPDFWord *> *words;

/// A list of text blocks on the PDF page. A text block is typically one line in the PDF. In a multi-column layout,
/// a text block will be one line of a single column.
@property (nonatomic, copy, readonly) NSArray<PSPDFTextBlock *> *textBlocks;

/// A list of `PSPDFImageInfo` objects representing all the images on the PDF page.
///
/// @see `PSPDFImageInfo`.
@property (nonatomic, copy, readonly) NSArray<PSPDFImageInfo *> *images;

/// The receiver's associated document provider.
@property (nonatomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

/// This is the page that the receiver represents. Relative to the `documentProvider` it was retrieved from.
///
/// @see `documentProvider`.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

/// Returns the page text for the glyphs passed in.
///
/// @param glyphs The glyphs from which the text is to be generated.
/// @return An `NSString` of the text from the passed in glyphs.
///
/// @note This method will find the glyphs with the lowest and highest `PSPDFGlyph.indexOnPage`, and return all the text between those two indexes.
/// If you want to get the text for discrete ranges of glyphs, use `PSPDFStringFromGlyphs` instead.
- (NSString *)textWithGlyphs:(NSArray<PSPDFGlyph *> *)glyphs;

/// Finds the glyphs in a passed in range.
///
/// @param range The range for which glyphs are to be fetched. This range must be based on `PSPDFGlyph.indexOnPage`.
/// @return The glyphs contained in the requested range.
///
/// @note If the range is invalid, and empty array is returned.
- (NSArray<PSPDFGlyph *> *)glyphsInRange:(NSRange)range;

@end

NS_ASSUME_NONNULL_END
