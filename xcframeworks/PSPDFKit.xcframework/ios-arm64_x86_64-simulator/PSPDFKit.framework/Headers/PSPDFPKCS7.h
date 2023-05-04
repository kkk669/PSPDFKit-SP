//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFSignatureEncryptionAlgorithm.h>
#import <PSPDFKit/PSPDFSignatureHashAlgorithm.h>
#import <PSPDFKit/PSPDFSigner.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFPrivateKey, PSPDFX509;

/// An instance of this class represents a PKCS7 (https://tools.ietf.org/html/rfc2315) cryptographic container. This container format is the most common format used
/// for signing PDFs digitally. For example, you can use an instance of this class when you want to sign a document that was
/// already prepared for deferred digital signing. One example scenario may be the following:
///
/// - Prepare a PDF document with a digital signature form field by calling `-[PSPDFSigner prepareFormElement:toBeSignedWithAppearance:contents:writingToDataSink:completion:]`.
/// - Embed the data contents of this container by calling `-[PSPDFSigner embedSignatureInFormElement:withContents:writingToDataSink:completion:]`. In your custom implementation of the `PSPDFSignatureContents` interface that you pass to this method, you can return `[PSPDFPKCS7 data]` from inside the `-[PSPDFSignatureContents signData:]` method.
PSPDF_CLASS_SWIFT(PKCS7)
@interface PSPDFPKCS7 : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates an instance of a PKCS7 container.
///
/// Deprecated. Use `PKCS7.init(digest:type:privateKey:certificate:hashAlgorithm:encryptionAlgorithm:)` instead, with CMS as the type.
///
/// @param digest              The digest data that will be cryptographically protected by this PKCS7. For digital signatures this is typically all the PDF document except the signature contents.
/// @param privateKey          The private key that will be used to encrypt the digest.
/// @param certificate         An instance of an X509 certificate that will be used to validate the authenticity of the signer.
/// @param hashAlgorithm       The hash algorithm that was used to hash the `digest` argument.
/// @param encryptionAlgorithm The encryption algorithm that will be used to encrypt the data using the cryptographic resources also passed to this function as arguments.
+ (PSPDFPKCS7 *)create:(NSData *)digest
            privateKey:(PSPDFPrivateKey *)privateKey
           certificate:(PSPDFX509 *)certificate
         hashAlgorithm:(PSPDFSignatureHashAlgorithm)hashAlgorithm
   encryptionAlgorithm:(PSPDFSignatureEncryptionAlgorithm)encryptionAlgorithm PSPDF_DEPRECATED(12.1, "Use PKCS7.init(digest:type:privateKey:certificate:hashAlgorithm:encryptionAlgorithm:) instead, with CMS as the type.");

/// Initializes a PKCS7 container of a given type (CMS or PAdES).
///
/// @param digest              The digest data that will be cryptographically protected by this PKCS7. For digital signatures this is typically all the PDF document except the signature contents.
/// @param signatureType       The kind of PKCS7 to create. See `PDFSignatureType`.
/// @param privateKey          The private key that will be used to encrypt the digest.
/// @param certificate         An instance of an X509 certificate that will be used to validate the authenticity of the signer.
/// @param hashAlgorithm       The hash algorithm that was used to hash the `digest` argument.
/// @param encryptionAlgorithm The encryption algorithm that will be used to encrypt the data using the cryptographic resources also passed to this function as arguments.
- (instancetype)initWithDigest:(NSData *)digest
                          type:(PSPDFSignatureType)signatureType
                    privateKey:(PSPDFPrivateKey *)privateKey
                   certificate:(PSPDFX509 *)certificate
                 hashAlgorithm:(PSPDFSignatureHashAlgorithm)hashAlgorithm
           encryptionAlgorithm:(PSPDFSignatureEncryptionAlgorithm)encryptionAlgorithm;

/// Returns this PKCS7 structure as data.
- (NSData *)data;

@end

NS_ASSUME_NONNULL_END
