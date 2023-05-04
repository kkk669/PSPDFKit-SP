//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFSigner.h>

#import <PSPDFKit/PSPDFSignatureAppearance.h>
#import <PSPDFKit/PSPDFSignatureBiometricProperties.h>

NS_ASSUME_NONNULL_BEGIN

/// A private category that stores two properties to be able to call the async signing API from the
/// sync signing API. This extension could be removed once we deprecate the old API.
@interface PSPDFSigner ()

@property(nonatomic) PSPDFSignatureAppearance *signatureAppearance;
@property(nonatomic) PSPDFSignatureBiometricProperties *signatureBiometricProperties;

/// (Optional) Signs the passed form element `element` and writes the signed document
/// to `path`. If successful, returns YES for `success`, NO otherwise and `error` is set.
///
/// This was previously public API and was deprecated in 8.0 and was removed.
///
/// @param element                 The signature form element to sign.
/// @param certificate             The `PSPDFX509` instance that represents the certificate for signing the signature form element.
/// @param path                    The destination path for the signed document.
/// @param signatureAppearance     The `PSPDFSignatureAppearance` instance that customizes how the signature will appear in the signed document. If `nil`, the default signature appearance will be used.
/// @param biometricProperties     The `PSPDFSignatureBiometricProperties` instance that adds enhanced security properties to the signature,
/// like input pressure, type, etc.
- (void)signFormElement:(PSPDFSignatureFormElement *)element withCertificate:(PSPDFX509 *)certificate writeTo:(NSString *)path appearance:(nullable PSPDFSignatureAppearance *)signatureAppearance biometricProperties:(nullable PSPDFSignatureBiometricProperties *)biometricProperties completionBlock:(nullable void (^)(BOOL success, PSPDFDocument *_Nullable document, NSError *_Nullable error))completionBlock NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
