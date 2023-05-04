//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

/// A wrapper around `PDFCDocumentValidator`  document validator.
/// Ensures all annotations stream and resource references resolve to the right kind of object.
/// Added for use in Swift.
PSPDF_TEST_CLASS_SWIFT(DocumentValidator)
@interface PSPDFDocumentValidator : NSObject

- (instancetype)initWithDocument:(PSPDFDocument *)document;

/// Performs the actual validation iterating through all the annotations.
- (BOOL)validate;

@end

NS_ASSUME_NONNULL_END
