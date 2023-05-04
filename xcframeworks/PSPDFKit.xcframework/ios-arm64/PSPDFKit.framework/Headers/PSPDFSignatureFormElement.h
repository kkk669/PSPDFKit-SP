//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormElement.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFInkAnnotation, PSPDFSignatureInfo, PSPDFSignatureBiometricProperties, PSPDFPrivateKey;

/// Represents a Signature Form Element
/// A digital signature (PDF 1.3) may be used to verify the integrity of the document’s contents using verification information related to a signer.
///
/// @see https://pspdfkit.com/guides/ios/features/digital-signatures/
PSPDF_CLASS_SWIFT(SignatureFormElement)
@interface PSPDFSignatureFormElement : PSPDFFormElement

/// Returns YES if the signature field is digitally signed.
///
/// @note This does not mean that the signature is valid.
@property (atomic, readonly) BOOL isSigned;

/// The signature dictionary contains signature information.
@property (atomic, readonly, nullable) PSPDFSignatureInfo *signatureInfo;

/// Searches the document for a signature annotation that overlaps the form element.
///
/// This can only be an ink signature, or a stamp signature.
/// Stamp annotations need to have `isSignature` set to be considered.
@property (atomic, readonly, nullable) PSPDFAnnotation *overlappingSignatureAnnotation;

/// Returns the biometric properties of this signature with parameters like pressure, time information,
/// or input device or `nil` if there's no such information.
///
/// @note As the information is encrypted inside the document, it requires the corresponding private key
/// to access it.
- (nullable PSPDFSignatureBiometricProperties *)signatureBiometricProperties:(PSPDFPrivateKey *)privateKey;

/// This will remove the digital signature of the signature form element.
///
/// Only works if
/// - the form element is digitally signed (`isSigned` needs to be set.)
/// - the document of the signature form element is set
/// - the document can save and embed annotations
///
/// @param error Will be set if this method returns `false` and removing the signature failed.
///
/// @note This will save the document.
///
/// @returns Whether removing the digital signature was successful.
- (BOOL)removeSignatureWithError:(NSError *__autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
