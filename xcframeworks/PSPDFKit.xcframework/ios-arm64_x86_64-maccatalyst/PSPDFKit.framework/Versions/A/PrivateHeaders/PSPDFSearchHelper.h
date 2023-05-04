//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFSearchResult.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFSearchResult (PreviewHelper)

/// Creates an attributed version of the preview text with the given font.
- (NSAttributedString *)attributedPreviewTextWithFont:(UIFont *)font andColor:(UIColor *)color;

@end

// clang-format off

/// Creates an attributed version of the preview text with the given font.
PSPDF_EXPORT NSAttributedString *PSPDFSearchAttributedPreviewText(NSString *previewText, NSRange termRangeInPreviewText, UIFont *font, UIColor *color) NS_SWIFT_NAME(SearchAttributedStringFor(_:range:font:textColor:));
// clang-format on

NS_ASSUME_NONNULL_END
