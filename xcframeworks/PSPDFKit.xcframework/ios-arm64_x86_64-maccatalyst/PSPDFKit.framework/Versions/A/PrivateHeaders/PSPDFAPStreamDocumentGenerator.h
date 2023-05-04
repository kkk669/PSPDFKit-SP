//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

@class PSPDFDocumentProvider, PDFCAnnotation;

NS_ASSUME_NONNULL_BEGIN

/// This class is responsible for generating an AP stream for the core when it can't generate one itself.
PSPDF_TEST_EXPORT @interface PSPDFAPStreamDocumentGenerator : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the generator with the given document provider.
///
/// @param documentProvider The document provider we need to generate AP streams for.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// The document provider.
@property (nonatomic, weak) PSPDFDocumentProvider *documentProvider;

@end

NS_ASSUME_NONNULL_END
