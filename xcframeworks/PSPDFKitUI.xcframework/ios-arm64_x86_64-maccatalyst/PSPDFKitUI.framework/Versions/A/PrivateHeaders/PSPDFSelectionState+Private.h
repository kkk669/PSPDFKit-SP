//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSelectionState.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFGlyph, PSPDFImageInfo;

@interface PSPDFSelectionState ()

/// Originally deprecated on iOS 7.5, macOS 2.5, but kept around for internal use.
///
/// We should eventually clean this up.
@property (nonatomic, readonly, nullable) NSArray<PSPDFGlyph *> *selectedGlyphs;

- (nonnull instancetype)initWithUID:(NSString *)uid selectionPageIndex:(NSUInteger)index selectedGlyphs:(nullable NSArray<PSPDFGlyph *> *)selectedGlyphs selectedImage:(nullable PSPDFImageInfo *)imageInfo;

@end

NS_ASSUME_NONNULL_END
