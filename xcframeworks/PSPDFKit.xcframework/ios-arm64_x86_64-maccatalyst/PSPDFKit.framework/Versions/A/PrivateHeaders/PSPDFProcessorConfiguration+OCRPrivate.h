//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFProcessorConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFProcessorConfiguration ()

/// Performs OCR on the set pages in the language (using as the raw value of PDFCOcrLanguage) provided.
///
/// @note This method is only exposed privately,
/// and should only be used from the PSPDFKitOCR framework, since we don't want this
/// to be called without linking the OCR framework.
- (void)performOcr:(NSIndexSet *)pageIndexes language:(NSInteger)language;

@end

NS_ASSUME_NONNULL_END
