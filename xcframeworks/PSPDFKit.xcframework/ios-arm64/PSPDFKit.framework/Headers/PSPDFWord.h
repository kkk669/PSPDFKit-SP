//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFGlyphRange.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFGlyph;

/// Represents a word. Formed out of (usually) multiple glyphs.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(Word)
@interface PSPDFWord : NSObject<NSCopying, NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Convenience initializer to create a `PSPDFWord`.
/// The initializer will fail if there are no glyphs in `glyphs`.
///
/// @param wordGlyphs The glyphs that are a part of the text block that is being instantiated.
/// @param frame The frame of the word. Pass in `CGRectNull` if you want the frame to be calculated from the values in `glyphs`.
- (nullable instancetype)initWithGlyphs:(NSArray<PSPDFGlyph *> *)wordGlyphs frame:(CGRect)frame;

/// Designated initializer. The initializer will fail if the range of text is invalid (`NSNotFound` for its location/length).
/// Note that the `glyphs` array will be empty when using this initializer.
///
/// @param textRange The range of text (in `PSPDFTextParser.text`) that the receiver is representing.
/// @param text The text that is contained by the receiver. It is the caller's responsibility to ensure that the `text` matches the passed in `range`.
- (nullable instancetype)initWithRange:(NSRange)textRange text:(NSString *)text frame:(CGRect)frame NS_DESIGNATED_INITIALIZER;

/// Returns the content of the word (all glyphs merged together)
@property (nonatomic, readonly) NSString *stringValue;

/// All glyphs merged together in the smallest possible bounding box.
/// As an optimization, only the first and last glyph will be used for frame calculations.
@property (nonatomic) CGRect frame;

/// The range of glyphs (in `PSPDFTextParser.glyphs`) that the receiver is representing.
/// Returns `PSPDFInvalidGlyphRange` if the receiver does not have any glyphs.
@property (nonatomic, readonly) NSRange range;

/// Set to YES if this is the last word on a textBlock.
@property (nonatomic) BOOL lineBreaker;

@end

NS_ASSUME_NONNULL_END
