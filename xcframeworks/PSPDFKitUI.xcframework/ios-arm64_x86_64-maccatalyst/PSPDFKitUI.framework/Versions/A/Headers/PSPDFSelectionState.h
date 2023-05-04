//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFGlyphRange.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFTextSelectionView, PSPDFGlyph, PSPDFImageInfo;

/// Contains information about the currently selected state on a page.
PSPDF_CLASS_SWIFT(SelectionState)
@interface PSPDFSelectionState : NSObject<NSSecureCoding>

/// Returns an instance of the receiver configured to match the selectionView argument's state, if a selection exists.
+ (nullable instancetype)stateForSelectionView:(PSPDFTextSelectionView *)selectionView;

/// The uid of the document which the receiver corresponds to.
@property (nonatomic, readonly) NSString *UID;

/// The page index on which the selection exists.
@property (nonatomic, readonly) PSPDFPageIndex selectionPageIndex;

/// The range of glyphs (in `PSPDFTextParser.glyphs`) that are selected.
/// If no glyphs are selected, this method returns `PSPDFInvalidGlyphRange`.
@property (nonatomic, readonly) NSRange selectedGlyphRange;

/// The info for the selected image, if any.
@property (nonatomic, readonly, nullable) PSPDFImageInfo *selectedImage;

/// Returns a Boolean value that indicates whether a selection state is equal to the receiver.
///
/// @param selectionState The selection with which to compare the receiver
/// @return YES is `selectionState` is equivalent to the receiver, otherwise NO.
- (BOOL)isEqualToSelectionState:(nullable PSPDFSelectionState *)selectionState;

@end

NS_ASSUME_NONNULL_END
