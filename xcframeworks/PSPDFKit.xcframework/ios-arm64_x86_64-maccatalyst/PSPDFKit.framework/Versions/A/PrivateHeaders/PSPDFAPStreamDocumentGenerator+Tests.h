//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAPStreamDocumentGenerator.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAPStreamDocumentGenerator (Tests)

/// Copied fromPDFCAPStreamDocumentGenerator for tests:
///
/// Asks the `APStreamDocumentGenerator` if it should be used to generate the AP stream for be passed in annotation.
- (BOOL)shouldUseApstreamDocumentGenerator:(nonnull PDFCAnnotation *)annotation;

@end

NS_ASSUME_NONNULL_END
