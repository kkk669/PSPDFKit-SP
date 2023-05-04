//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFInkAnnotation, PSPDFSigner, PSPDFSignatureBiometricProperties;

/// Container object for storing a signature containing an ink annotation and an optional signer.
PSPDF_CLASS_SWIFT(SignatureContainer)
@interface PSPDFSignatureContainer : NSObject<NSSecureCoding, PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer to create a signature container.
///
/// @param signatureAnnotation The annotation used to sign a document. Supported annotation types are ink annotations and image stamp annotations.
/// @param signer A signer, if needed, used for digitally signing a document.
/// @param biometricProperties Biometric properties of the signature. Only honored if a `signer` is also provided.
- (instancetype)initWithSignatureAnnotation:(PSPDFAnnotation *)signatureAnnotation signer:(nullable PSPDFSigner *)signer biometricProperties:(nullable PSPDFSignatureBiometricProperties *)biometricProperties NS_DESIGNATED_INITIALIZER;

/// Signature annotation that is used for signing a document.
@property (nonatomic, readonly) PSPDFAnnotation *signatureAnnotation;

/// Signer, used for digitally signing a document.
@property (nonatomic, nullable, readonly) PSPDFSigner *signer;

/// Biometric properties of the signature. This is only honored when a `signer` is set, and stored encrypted in a created digital signature.
@property (nonatomic, nullable, readonly) PSPDFSignatureBiometricProperties *biometricProperties;

@end

NS_ASSUME_NONNULL_END
