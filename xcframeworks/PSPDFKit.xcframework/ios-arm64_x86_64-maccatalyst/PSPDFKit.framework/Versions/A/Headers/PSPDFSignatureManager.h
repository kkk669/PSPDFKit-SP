//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSigner, PSPDFX509;

/// Manages signature handlers for digital signature creation. Thread safe.
///
/// A `SignatureViewController` allows the user to select from certificates (signers) registered with the signature
/// manager. However, `SignatureViewController` is only used by PSPDFKit if the Annotations component is enabled in
/// your license from before the introduction of the Electronic Signatures component.
/// Registered signers are not used by the UI of the Electronic Signatures component (`SignatureCreationViewController`).
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFSignatureManager)
@interface PSPDFSignatureManager : NSObject

/// Returns all registered signers.
@property (nonatomic, readonly) NSArray<PSPDFSigner *> *registeredSigners;

/// Registers a signer.
/// Registering the same signing object more than once will be ignored.
- (void)registerSigner:(PSPDFSigner *)signer;

/// Removes all registered signers.
- (void)clearRegisteredSigners;

/// Returns the trusted certificate stack. By default, Adobe CA is included in this list.
@property (nonatomic, readonly) NSArray<PSPDFX509 *> *trustedCertificates;

/// Adds a trusted certificate to the stack.
- (void)addTrustedCertificate:(PSPDFX509 *)x509;

/// Removes all trusted certificates from the stack.
- (void)clearTrustedCertificates;

@end

NS_ASSUME_NONNULL_END
