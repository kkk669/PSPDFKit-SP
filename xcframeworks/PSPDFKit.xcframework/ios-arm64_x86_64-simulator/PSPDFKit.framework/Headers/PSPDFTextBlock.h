//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFWord.h>

@class PSPDFGlyph;

NS_ASSUME_NONNULL_BEGIN

/// Represents multiple words forming a text block. (e.g. a Column)
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(TextBlock)
@interface PSPDFTextBlock : NSObject<NSCopying, NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Convenience initializer to create a text block.
/// The initializer will fail if there are no glyphs in `glyphs`.
///
/// @param glyphs The glyphs that are a part of the text block that is being instantiated.
/// @param frame The frame of the text block, in normalized PDF coordinates. Pass in `CGRectNull` if you want the frame to be calculated from the values in `glyphs`.
- (nullable instancetype)initWithGlyphs:(NSArray<PSPDFGlyph *> *)glyphs frame:(CGRect)frame;

/// Designated initializer to create a text block. The initializer will fail if the range of text is invalid (`NSNotFound` for its location/length).
/// Note that the `glyphs` array will be empty when using this initializer.
///
/// @param textRange The range of text (in `PSPDFTextParser.text`) that the receiver is representing.
/// @param text The text that is contained by the receiver. It is the caller's responsibility to ensure that the `text` matches the passed in `range`.
/// @frame The frame of the text block, in normalized PDF coordinates.
- (nullable instancetype)initWithRange:(NSRange)textRange text:(NSString *)text frame:(CGRect)frame NS_DESIGNATED_INITIALIZER;

/// Frame of the text block, in normalized PDF coordinates.
@property (nonatomic, readonly) CGRect frame;

/// The range of glyphs (in `PSPDFTextParser.glyphs`) that the receiver is representing.
@property (nonatomic, readonly) NSRange range;

/// All words of the current text block. Evaluated lazily.
@property (nonatomic, copy, readonly) NSArray<PSPDFWord *> *words;

/// Returns the content of the text block (all words merged together)
/// Text lines end with CRLF (`\r\n`).
@property (nonatomic, copy, readonly) NSString *content;

/// Compare to another text block.
- (BOOL)isEqualToTextBlock:(PSPDFTextBlock *)otherBlock;

@end

NS_ASSUME_NONNULL_END
