//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// An interface for producing content that will be inside the Contents key of a signature dictionary.
///
/// This interface abstracts the digital signature that can be in a signature form field so that you can create
/// your own and place it inside the document. You can call
/// `-[PSPDFSigner prepareFormElement:toBeSignedWithAppearance:contents:writingToDataSink:completion:]`
/// and pass an instance of this interface to prepare a document for digital signing.
PSPDF_PROTOCOL_SWIFT(PDFSignatureContents)
@protocol PSPDFSignatureContents <NSObject>

/// Given some `dataToSign`, return the digital signature contents that will be placed in the PDF document.
/// `dataToSign` is the raw range of the PDF document that should be covered by the signature. In a specific
/// implementation, you may hash the data, encrypt it, and then return it serialized in PKCS#7 format (https://tools.ietf.org/html/rfc2315).
- (NSData *)signData:(NSData *)dataToSign;

@end

NS_ASSUME_NONNULL_END
