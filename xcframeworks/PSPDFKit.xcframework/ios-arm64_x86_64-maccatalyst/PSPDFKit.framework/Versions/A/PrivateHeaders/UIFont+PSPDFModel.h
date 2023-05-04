//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Replaces PDF font names into usable names for iOS (e.g. Hel to Helvetica; ComicSansMS to Noteworthy)
PSPDF_EXTERN NSString *PSPDFReplacementFontNameForFontName(NSString *fontName);

/// Finds the closest iOS font name for a PDF font entry like `Arial,Italic`.
/// E.g., would return `Arial-ItalicMT` for `Arial,Italic`.
PSPDF_EXTERN NSString *_Nullable PSPDFFuzzyMatchedFontNameForPDFFontName(NSString *pdfFontName);

@interface UIFont (PSPDFModel)

/// Converts the font into a bold variant.
@property (nonatomic, readonly) UIFont *pspdf_boldFont;

/// Returns a variant of the current font with `UIFontFeatureSelectorIdentifierKey: @(kMonospacedNumbersSelector)`
@property (nonatomic, readonly) UIFont *pspdf_monospacedNumbersFont;

@end

NS_ASSUME_NONNULL_END
