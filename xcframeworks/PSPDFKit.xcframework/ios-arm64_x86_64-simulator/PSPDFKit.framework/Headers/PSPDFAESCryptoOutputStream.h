//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFCryptoOutputStream.h>

NS_ASSUME_NONNULL_BEGIN

/// AES decryption, RNCryptor data format  (see https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md )
PSPDF_CLASS_SWIFT(AESCryptoOutputStream)
@interface PSPDFAESCryptoOutputStream : PSPDFCryptoOutputStream

/// Designated initializer with the passphrase. The encryption key salt and HMAC key salt will be saved in the file header.
/// Returns nil if the underlying crypto context can't be initialized
/// or if the encryption feature is not enabled.
- (nullable instancetype)initWithOutputStream:(NSOutputStream *)stream passphrase:(NSString *)passphrase;

/// Check the streamStatus after calling this method. Due to AES CBC encryption is working finalized data
/// is written during this call. If it fails the streamStatus is set to NSStreamStatusError and streamError
/// holds the detailed info.
- (void)close;

@end

/// The PSPDFAESCryptoOutputStream Error Domain.
///
/// @note Used in the PSPDFAESCryptoOutputStream -(NSError *)streamError method.
PSPDF_EXPORT NSString *const PSPDFAESCryptoOutputStreamErrorDomain;

/// List of documented errors within the PSPDFAESCryptoOutputStream.
///
/// @note Used in the PSPDFAESCryptoOutputStream -(NSError *)streamError method.
typedef NS_ERROR_ENUM(PSPDFAESCryptoOutputStreamErrorDomain, PSPDFAESCryptoOutputStreamErrorCode) {
    PSPDFAESCryptoOutputStreamErrorEncryptionFailed = 100,
    PSPDFAESCryptoOutputStreamErrorCryptorFinalFailed = 170,
    PSPDFAESCryptoOutputStreamErrorWritingToParentStreamFailed = 120,
    PSPDFAESCryptoOutputStreamErrorMemoryAllocationFailed = 200,
    PSPDFAESCryptoOutputStreamErrorUnknown = NSIntegerMax,
} PSPDF_ENUM_SWIFT(AESCryptoOutputStreamError);

NS_ASSUME_NONNULL_END
