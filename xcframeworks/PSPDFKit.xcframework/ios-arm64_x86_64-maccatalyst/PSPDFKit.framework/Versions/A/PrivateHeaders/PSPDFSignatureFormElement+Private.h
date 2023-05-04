//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFSignatureFormElement.h>

@class PSPDFCoreAnnotation;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFSignatureFormElement ()

/// Initializes the PSPDFSignatureFormElement.
- (instancetype)initWithCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation formField:(PSPDFFormField *)formField documentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Signature information. Read-write.
@property (atomic, nullable) PSPDFSignatureInfo *signatureInfo;

@end

NS_ASSUME_NONNULL_END
