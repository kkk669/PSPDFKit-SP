//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFSignatureHashAlgorithm.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^PSPDFDocumentSignDataCompletionBlock)(BOOL status, NSData * _Nullable signedData);

@class PSPDFSigner;

/// A `PSPDFDocumentSignerDelegate` gives flexibility to the process of adding a digital signature to a document.
///
/// Implement the `documentSigner:signData:hashAlgorithm:completion` method to sign the required data and invoke `completion`
/// when ready. The document signer will automatically embed the signed data inside the signature.
PSPDF_PROTOCOL_SWIFT(PDFDocumentSignerDelegate)
@protocol PSPDFDocumentSignerDelegate<NSObject>

/// Invoked when the document signer needs to sign the parts of the document that will be covered by the digital signature.
/// `data` is the data content that you will need to hash and sign. `hashAlgorithm` indicates which hash algorithm needs to be
/// used. You can customize it by setting a custom `PSPDFSignerDataSource` as the `dataSource` property of a `PSPDFSigner`.
/// If you are unable to sign the required data, call `completion(NO, nil);` to abort the signing process.
///
/// @note: See method - [PSPDFSigner signData:privateKey:hashAlgorithm:], which is a convenience method you can use to sign data.
- (void)documentSigner:(PSPDFSigner *)signer signData:(NSData *)data hashAlgorithm:(PSPDFSignatureHashAlgorithm)hashAlgorithm
      completion:(PSPDFDocumentSignDataCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
