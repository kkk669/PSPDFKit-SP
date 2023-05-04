//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFPKCS12.h>
#import <PSPDFKit/PSPDFSigner.h>

NS_ASSUME_NONNULL_BEGIN

/// Concrete implementation of a `PSPDFSigner`.
///
/// This class augments the functionality of its superclass by supporting password-protected PKCS12 files (.p12 extension).
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PKCS12Signer)
@interface PSPDFPKCS12Signer : PSPDFSigner

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates a new PKCS12 signer with the specified display name.
/// The certificate and private key should be contained in the `PSPDFPKCS12` instance.
- (instancetype)initWithDisplayName:(NSString *)displayName PKCS12:(PSPDFPKCS12 *)p12 NS_DESIGNATED_INITIALIZER;

/// The PKCS12 container holding the private key and certificate.
@property (nonatomic, readonly) PSPDFPKCS12 *p12;

/// Signs the passed form element |elem| using provided password to open the p12 container (to get the certificate and the private key)
/// and writes the signed document to |path|.  Returns YES for |success|, NO otherwise and error |err| is set.
///
/// @param element                 The signature form element to sign.
/// @param password                The password to unlock the p12 container.
/// @param path                    The destination path for the signed document.
- (void)signFormElement:(PSPDFSignatureFormElement *)element usingPassword:(NSString *)password writeTo:(NSString *)path completion:(nullable void (^)(BOOL success, PSPDFDocument *document, NSError *_Nullable error))completionBlock;

/// Signs the passed form element |elem| using provided password to open the p12 container (to get the certificate and the private key)
/// and writes the signed document to |path|.  Returns YES for |success|, NO otherwise and error |err| is set.
///
/// @param element                 The signature form element to sign.
/// @param password                The password to unlock the p12 container.
/// @param path                    The destination path for the signed document.
/// @param signatureAppearance     The `PSPDFSignatureAppearance` instance that customizes how the signature will appear in the signed document. If `nil`, the default signature appearance will be used.
/// @param biometricProperties     The `PSPDFSignatureBiometricProperties` instance that adds enhanced security properties to the signature,
/// like input pressure, type, etc.
- (void)signFormElement:(PSPDFSignatureFormElement *)element usingPassword:(NSString *)password writeTo:(NSString *)path appearance:(nullable PSPDFSignatureAppearance *)signatureAppearance biometricProperties:(nullable PSPDFSignatureBiometricProperties *)biometricProperties completion:(nullable void (^)(BOOL success, PSPDFDocument *document, NSError *_Nullable error))completionBlock;

/// Signs the passed form element |element| and writes the signed document
/// to |dataSink|. The completion block will signal if the result was successful, return the signed document, if it was signed correctly,
/// and the signing error, if there's any.
///
/// @param element                 The signature form element to sign.
/// @param password                The password to unlock the p12 container.
/// @param dataSink                The destination data sink for the signed document. @see `PSPDFDataSink`.
- (void)signFormElement:(PSPDFSignatureFormElement *)element usingPassword:(NSString *)password writeToDataSink:(id<PSPDFDataSink>)dataSink completionBlock:(nullable void (^)(BOOL success, id<PSPDFDataSink> _Nullable document, NSError *_Nullable error))completionBlock;

/// Signs the passed form element |element| and writes the signed document
/// to |path|. The completion block will signal if the result was successful, return the signed document, if it was signed correctly,
/// and the signing error, if there's any.
///
/// @param element                 The signature form element to sign.
/// @param password                The password to unlock the p12 container.
/// @param path                    The destination path for the signed document.
- (void)signFormElement:(PSPDFSignatureFormElement *)element usingPassword:(NSString *)password writeTo:(NSString *)path completionBlock:(nullable void (^)(BOOL success, PSPDFDocument *_Nullable document, NSError *_Nullable error))completionBlock;

@end

NS_ASSUME_NONNULL_END
