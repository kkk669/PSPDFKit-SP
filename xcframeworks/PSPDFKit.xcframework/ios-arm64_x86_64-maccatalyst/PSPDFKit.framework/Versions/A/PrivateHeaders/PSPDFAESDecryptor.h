//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

// CCPseudoRandomAlgorithm, see CommonCrypto/CommonKeyDerivation.h
// Not imported as this breaks modular header rules.
typedef uint32_t PSPDFPseudoRandomAlgorithm;

/// Returns the binary key for AES encryption
///
/// The default PRF is `kCCPRFHmacAlgSHA1`.
/// The default number of iterations is `PSPDFAESDefaultPBKDFNumberOfRounds` (10000).
/// The legacy file format used `kCCPRFHmacAlgSHA256` and 50000 iterations.
PSPDF_EXTERN NSData *PSPDFAESConstructKey(NSData *passphraseData, NSData *saltData, PSPDFPseudoRandomAlgorithm prf, NSUInteger rounds);

/// This class allows a decryption of AES256 encrypted files using RNCryptor file format
/// or using legacy file format (CBC and an initial 16 byte IV vector written in the first 16 bytes of the file to read)
///
/// https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md
///
/// Requires the `Features.strongEncryption` feature flag.
NS_SWIFT_NAME(AESDecryptor)
@interface PSPDFAESDecryptor : NSObject

/// Designated initializer with the passphrase.
///
/// URL must be a file-based URL.
/// Salt will be loaded from the header of the
/// current file format https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md
/// The default PRF is `kCCPRFHmacAlgSHA1`.
/// The default number of iterations is `PSPDFAESDefaultPBKDFNumberOfRounds` (10000).
- (instancetype)initWithURL:(NSURL *)sourceURL passphrase:(NSString *)passphrase error:(NSError **)error;

/// Designated initializer with the passphrase, customized PRF and iterations number.
/// Salt will be loaded from the header of the
/// file format (see https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md )
/// The default PRF is kCCPRFHmacAlgSHA1.
/// The default number of iterations is `PSPDFAESDefaultPBKDFNumberOfRounds` (10000).
/// URL must be a file-based URL.
- (instancetype)initWithURL:(NSURL *)sourceURL passphrase:(NSString *)passphrase PRF:(PSPDFPseudoRandomAlgorithm)prf rounds:(NSUInteger)rounds error:(NSError **)error;

/// Designated initializer with a prepared, stretched, binary key.
///
/// @warning: only use this if the key is cryptographically random and of length `kCCKeySizeAES256`.
/// URL must be a file-based URL.
- (instancetype)initWithURL:(NSURL *)sourceURL key:(NSData *)key error:(NSError **)error;

/// Initializer with passphrase, salt, and rounds.
///
/// Supports the old legacy format and the new format. (see https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md )
- (instancetype)initWithURL:(NSURL *)sourceURL passphrase:(NSString *)passphrase salt:(NSString *)salt rounds:(NSUInteger)rounds error:(NSError **)error;

/// Fills the responseBuffer with decrypted data of the requestedLength starting from the requestedOffset.
/// and returns the number of bytes that was filled in the responseBuffer.
- (size_t)bytesAtOffset:(off_t)requestedOffset length:(size_t)requestedLength buffer:(void *)responseBuffer bufferSize:(size_t)responseBufferLength;

/// The size of the decrypted file in bytes.
@property (nonatomic, readonly) long decryptedFileSize;

/// Calculates the HMAC of the encrypted data and compares it to the stored HMAC (at the end of the file)
///
/// Warning: the whole encrypted data has to be read in order to calculate the HMAC (due to the random data access pattern of this class we cannot calculate HMAC while reading decrypting data)
@property (nonatomic, readonly) BOOL isCorrectHMAС;

@end
