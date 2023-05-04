//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// The supported encryption algorithms that can be used when signing a document.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSignatureEncryptionAlgorithm) {
    /// RSA, one of the most popular public-key encryption systems.
    PSPDFSignatureEncryptionAlgorithmRSA,
    /// DSA (Digital Signature Algorithm). Faster than RSA for signing a document, but the verification is slower.
    PSPDFSignatureEncryptionAlgorithmDSA,
    /// ECDSA (Elliptic Curve Digital Signature Algorithm). Introduced for signing PDF documents in PDF 2.0.
    PSPDFSignatureEncryptionAlgorithmECDSA,
    /// This is an algorithm we don't currently know about.
    PSPDFSignatureEncryptionAlgorithmUnknown,
} PSPDF_ENUM_SWIFT(PDFSignatureEncryptionAlgorithm);

NS_ASSUME_NONNULL_END
