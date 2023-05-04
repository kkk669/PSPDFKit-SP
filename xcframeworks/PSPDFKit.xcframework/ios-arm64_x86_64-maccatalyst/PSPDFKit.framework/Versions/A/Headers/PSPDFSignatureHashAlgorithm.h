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

/// A hash algorithm or hash function is a function that maps data of arbitrary size to data of a fixed size. In the context of PDF,
/// this arbitrary data may represent a part of a document. The output of a hash function is always identical if the
/// input data is the same. This fact can be used to check if a document has been altered intentionally or
/// accidentally.
///
/// PSPDFKit supports several hash functions. This list is not a complete list of every hash algorithm that is available.
/// Some hash algorithms are not supported yet by the PDF specification for their use in digital signatures.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSignatureHashAlgorithm) {
    /// MD5 is a widely used hash algorithm, but it's no longer considered secure. Use only for compatibility purposes.
    PSPDFSignatureHashAlgorithmMD5,
    /// Secure Hash Algorithm. SHA-160 is safer than MD5, but there are known security vulnerabilities since 2005.
    PSPDFSignatureHashAlgorithmSHA160,
    /// Recommended. Secure Hash Algorithm with an output length of 224 bits.
    PSPDFSignatureHashAlgorithmSHA224,
    /// Recommended. Secure Hash Algorithm with an output length of 256 bits.
    PSPDFSignatureHashAlgorithmSHA256,
    /// Recommended. Secure Hash Algorithm with an output length of 384 bits.
    PSPDFSignatureHashAlgorithmSHA384,
    /// Recommended. Secure Hash Algorithm with an output length of 512 bits.
    PSPDFSignatureHashAlgorithmSHA512,
    /// This is a hash algorithm we don't know about yet.
    PSPDFSignatureHashAlgorithmUnknown,
} PSPDF_ENUM_SWIFT(PDFSignatureHashAlgorithm);

NS_ASSUME_NONNULL_END
