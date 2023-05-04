//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocument, PSPDFDocumentProvider, PSPDFPageInfo, PSPDFFreeTextAnnotation, PSPDFStampAnnotation;

NS_ASSUME_NONNULL_BEGIN

/// The PDF Page represents a page of a document. The document is strongly retained.
///
/// Responsibilities:
///
/// - Make working with annotations simpler.
PSPDF_CLASS_SWIFT(PDFPage)
@interface PSPDFPage : NSObject

/// The associated document. Strongly held.
@property (nonatomic, readonly) PSPDFDocument *document;

/// The associated document provider. Fetched via `document`.
@property (nonatomic, readonly) PSPDFDocumentProvider *documentProvider;

// Page metrics and metadata.
@property (nonatomic, readonly) PSPDFPageInfo *pageInfo;

/// Page index, absolute based on the document.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

@end

/// Annotations are not actually added to the page but are positioned based on page metrics.
/// It is your responsibility to add them to the page.
@interface PSPDFPage (AnnotationFactory)

/// Creates a stamp annotation from image.
- (PSPDFStampAnnotation *)createStampAnnotationWithImage:(UIImage *)image;

/// Creates a free text annotation from content.
- (PSPDFFreeTextAnnotation *)createFreeTextAnnotationWithContents:(NSString *)contents;

@end

NS_ASSUME_NONNULL_END
