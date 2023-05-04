//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFSignatureEncryptionAlgorithm.h>
#import <PSPDFKit/PSPDFSignatureHashAlgorithm.h>

NS_ASSUME_NONNULL_BEGIN

/// The PSPDFExternalSignature protocol is adopted by an object that provides an external signature for a PDF document.
/// You set the externalSignatureDelegate property in a PSPDFSigner class or subclass when you want to control the digital
/// signing process with an external signature (for example, a signature that is implemented by a hardware device or by
/// an external webservice).
PSPDF_PROTOCOL_SWIFT(ExternalSignature)
@protocol PSPDFExternalSignature <NSObject>

/// This callback method is invoked when the digital signing process needs to cryptographically sign a hash of a PDF
/// document. Read the digital signature guides for more information about the digital signing process.
///
/// @param data The part of the document that needs to be hashed and signed before creating the digital signature.
/// @param hashAlgorithm The hash algorithm that must be used to digest the `data` parameter.
/// @return The signed data. Note that you must sign the data using the correspondent private key to the
/// certificate that was used when the signing process was started (see in `PSPDFSigner` the `signFormElement:` family of methods).
/// Otherwise, the digital signature will be invalid.
- (NSData *)signData:(NSData *)data hashAlgorithm:(PSPDFSignatureHashAlgorithm)hashAlgorithm;

/// The encryption algorithm to use in the digital signing process.
- (PSPDFSignatureEncryptionAlgorithm)encryptionAlgorithm;

@end

NS_ASSUME_NONNULL_END
