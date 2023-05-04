//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <AVFoundation/AVFoundation.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFGlyph, PSPDFTextSelectionView, PSPDFImageInfo;

/// Delegate for `PSPDFTextSelectionView`.
PSPDF_PROTOCOL_SWIFT(TextSelectionViewDelegate)
@protocol PSPDFTextSelectionViewDelegate<NSObject>

/// Called whenever there's a good moment to show/hide the menu based on the selection state of `selectedGlyphs` or `selectedImage`.
- (BOOL)textSelectionView:(PSPDFTextSelectionView *)textSelectionView updateMenuAnimated:(BOOL)animated;

@optional

/// Called when text is about to be selected. Return NO to disable text selection.
- (BOOL)textSelectionView:(PSPDFTextSelectionView *)textSelectionView shouldSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect;

/// Called after text has been selected.
/// Will also be called when text has been deselected. Deselection sometimes cannot be stopped, so the `shouldSelectText:` will be skipped.
- (void)textSelectionView:(PSPDFTextSelectionView *)textSelectionView didSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect;

@end

/// Handles text and image selection on a page.
///
/// @note Requires the `Features.textSelection` feature flag.
///
/// Don't manually create this class. The initializer here is not exposed.
///
/// The selection color is determined by the `tintColor` property inherited from `UIView`.
/// On Mac Catalyst, the `tintColor` is set to `[NSColor selectedContentBackgroundColor]`
/// & `unemphasizedSelectedContentBackgroundColor`, depending if the current window is the key window or not.
PSPDF_CLASS_SWIFT(TextSelectionView)
@interface PSPDFTextSelectionView : UIView<AVSpeechSynthesizerDelegate, PSPDFOverridable>

/// The text selection delegate.
@property (nonatomic, weak) id<PSPDFTextSelectionViewDelegate> delegate;

/// Currently selected glyphs.
///
/// @note Use `sortedGlyphs:` to pre-sort your glyphs if you manually set this.
/// @warning This method expects glyphs to be sorted in reading order.
@property (nonatomic, copy, null_resettable) NSArray<PSPDFGlyph *> *selectedGlyphs;

/// Currently selected text. Set via setting `selectedGlyphs`.
/// Use `discardSelection` to clear.
@property (nonatomic, copy, readonly, nullable) NSString *selectedText;

/// Currently selected image.
@property (nonatomic, nullable) PSPDFImageInfo *selectedImage;

/// The selection alpha value. Defaults to 0.2.
@property (nonatomic) CGFloat selectionAlpha UI_APPEARANCE_SELECTOR;

/// Currently selected text, optimized for searching
@property (nonatomic, copy, readonly, nullable) NSString *trimmedSelectedText;

/// To make it easier to select text, we slightly increase the frame margins. Defaults to 4 pixels.
@property (nonatomic) CGFloat selectionHitTestExtension UI_APPEARANCE_SELECTOR;

/// An `NSArray` of boxed `CGRect`s for every selected block, in view coordinates.
@property (nonatomic, readonly) NSArray<NSValue *> *selectionRects;

/// The rect (in view coordinates) for the first block that is currently selected, or `CGRectZero` if nothing is selected.
/// Note that this will return the rect for a selected image too.
/// Using this property is much quicker than doing `selectionRects.firstObject.CGRectValue`.
@property (nonatomic, readonly) CGRect rectForFirstBlock;

/// The rect (in view coordinates) for the last block that is currently selected, or `CGRectZero` if nothing is selected.
/// Note that this will return the rect for a selected image too.
/// Using this property is much quicker than doing `selectionRects.lastObject.CGRectValue`.
@property (nonatomic, readonly) CGRect rectForLastBlock;

/// Updates the `UIMenuController` if there is a selection.
/// Returns YES if a menu is displayed.
- (BOOL)updateMenuAnimated:(BOOL)animated;

/// Update the selection (text menu).
///
/// @note `animated` is currently ignored.
- (void)updateSelectionAnimated:(BOOL)animated;

/// Clears the current selection.
- (void)discardSelectionAnimated:(BOOL)animated;

/// Required if glyph frames change.
- (void)clearCache;

/// Currently has a text/image selection?
@property (nonatomic, readonly) BOOL hasSelection;

// MARK: Advanced Usage

/// This method sorts the passed in glyphs by reading order.
///
/// @param glyphs The glyphs that are to be sorted.
/// @return A new array of the passed in glyphs sorted according to their reading order.
- (NSArray<PSPDFGlyph *> *)sortedGlyphs:(NSArray<PSPDFGlyph *> *)glyphs;

@end

@interface PSPDFTextSelectionView (Debugging)

/// Debugging feature, visualizes the text blocks.
- (void)showTextFlowData:(BOOL)show animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
