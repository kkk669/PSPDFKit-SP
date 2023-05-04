//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFSignatureEncryptionAlgorithm.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PSPDFPrivateKeyEncoding) {
    /// A PKCS#8 encoded private key.
    PSPDFPrivateKeyEncodingPKCS8,
    /// A PKCS#1 encoded private key. Both PEM and raw ASN.1 binary format supported.
    PSPDFPrivateKeyEncodingPKCS1,
} PSPDF_ENUM_SWIFT(PrivateKey.Encoding);

/// Represents a cryptographic private key.
///
/// Supported encodings are PKCS1 (https://tools.ietf.org/html/rfc8017) and PCKS8 (https://tools.ietf.org/html/rfc5208).
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PrivateKey)
@interface PSPDFPrivateKey : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates a private key from raw encoded data.
///
/// @param data     The raw data that represents the private key.
/// @param encoding The encoding that was used to encode `data`. Supported encodings are PCKS1 (https://tools.ietf.org/html/rfc8017) and PCKS8 (https://tools.ietf.org/html/rfc5208).
+ (nullable PSPDFPrivateKey *)createFromRawPrivateKey:(NSData *)data
                                             encoding:(PSPDFPrivateKeyEncoding)encoding;

/// The encryption algorithm used in this private key.
@property (nonatomic, readonly) PSPDFSignatureEncryptionAlgorithm signatureEncryptionAlgorithm;

@end

NS_ASSUME_NONNULL_END
