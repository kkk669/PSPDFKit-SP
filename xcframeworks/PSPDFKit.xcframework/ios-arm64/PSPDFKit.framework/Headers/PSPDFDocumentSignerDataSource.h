//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFSignatureEncryptionAlgorithm.h>
#import <PSPDFKit/PSPDFSignatureHashAlgorithm.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSignatureAppearance, PSPDFSignatureBiometricProperties, PSPDFSigner, PSPDFFormField;

/// A data source that, when configured on a `PSPDFSigner` instance or one of its subclasses, gives implementors a chance
/// to configure some details of a digital signature.
PSPDF_PROTOCOL_SWIFT(PDFDocumentSignerDataSource)
@protocol PSPDFDocumentSignerDataSource<NSObject>
@optional

/// Gives the implementor a chance to configure the signature appearance for a form field.
///
/// @note If not implemented, `PSPDFSignatureAppearance.defaultConfiguration` will be used.
- (PSPDFSignatureAppearance *)documentSigner:(PSPDFSigner *)signer signatureAppearance:(NSString *)formFieldFqn;
/// Gives the implementor a chance to configure the signature estimated size (in bytes) for a form field.
/// This is the size that you expect your signature container will need in the PDF. The estimated size will be reserved
/// in the PDF document before digitally signing it, but PSPDFKit may reserve around the double of that space to fit some implementation details.
/// A big estimated size will possibly make the signed document bigger than necessary, but a too small one will cause the
/// signing process to fail. For complex certificates, we recommend this method returns around 16 KB, but this number may need to be
/// even larger depending on the size of the signing certificate.
///
/// @note If not implemented, 8 KB will be used, which will occupy more or less double that size (16 KB) in the PDF. The returned value will be clamped between 0 and 256 KB
/// (262144 bytes).
- (int32_t)documentSigner:(PSPDFSigner *)signer signatureEstimatedSize:(NSString *)formFieldFqn;
/// Gives the implementor a chance to configure biometric properties for this signature. Biometric properties are optional metadata
/// that will be stored encrypted inside the signature dictionary.
///
/// @note If not implemented, no biometric properties will be embedded.
- (PSPDFSignatureBiometricProperties *)documentSigner:(PSPDFSigner *)signer signatureBiometricProperties:(NSString *)formFieldFqn;
/// Gives the implementor a chance to select a digest algorithm for the signature.
///
/// @note If not implemented, SHA256 will be used.
- (PSPDFSignatureHashAlgorithm)documentSigner:(PSPDFSigner *)signer signatureHashAlgorithm:(NSString *)formFieldFqn;
/// Gives the implementor a chance to select an encryption algorithm for the signature.
///
/// @note If not implemented, RSA will be used.
- (PSPDFSignatureEncryptionAlgorithm)documentSigner:(PSPDFSigner *)signer signatureEncryptionAlgorithm:(NSString *)formFieldFqn;

@end

NS_ASSUME_NONNULL_END
