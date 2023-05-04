//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/NSString+PSPDFFoundation.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFGlyph.h>

#ifdef __cplusplus
#include <unordered_map>
#include <vector>
#endif

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFGlyph ()

/// Designated initializer.
- (instancetype)initWithFrame:(CGRect)frame content:(NSString *)content NS_DESIGNATED_INITIALIZER;

@property (nonatomic) BOOL lineBreaker;
@property (nonatomic, getter=isWordBreaker) BOOL wordBreaker;
@property (nonatomic, getter=isGenerated) BOOL generated;
@property (nonatomic) NSInteger indexOnPage;
@property (nonatomic, readonly) PSPDFTextDirection textDirection;

@end

/// Removes all glyphs that describe invisible characters.
PSPDF_SDK_EXPORT NSArray<PSPDFGlyph *> *PSPDFReduceInvisibleGlyphs(NSArray<PSPDFGlyph *> *glyphs);

/// Retrieves the bounding box and the first non-neutral text direction from the passed in glyphs.
///
/// @param glyphs The glyphs for which the information is required.
/// @param direction A pointer to a `PSPDFTextDirection`, which on return will be set to the first non-neutral text direction in the glyphs.
/// @return The smallest rectangle that can contain all the specified glyphs. In PDF coordinates.
PSPDF_SDK_EXPORT CGRect PSPDFBoundingBoxAndTextDirectionFromGlyphs(NSArray<PSPDFGlyph *> *_Nullable glyphs, PSPDFTextDirection *_Nullable direction);

#ifdef __cplusplus

// This enables the use of std::unordered_map with PSPDFGlyph objects as keys for caching.
namespace std {
template <> struct hash<PSPDFGlyph *> {
    size_t operator()(const PSPDFGlyph *glyph) const { return glyph.hash; }
};

template <> struct equal_to<PSPDFGlyph *> {
    size_t operator()(const PSPDFGlyph *glyph1, const PSPDFGlyph *glyph2) const { return [glyph1 isEqual:glyph2]; }
};
}

#endif

NS_ASSUME_NONNULL_END
