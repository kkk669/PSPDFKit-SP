//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFAESDecryptor.h>

extern const uint PSPDFAESDefaultPBKDFNumberOfRounds;
extern const uint8_t RNCryptorCurrentFileVersion;

PSPDF_EXTERN NSString *const PSPDFAESEncryptorErrorDomain;

typedef NS_ERROR_ENUM(PSPDFAESEncryptorErrorDomain, PSPDFAESEncryptorErrorCode) {
    PSPDFAESEncryptorErrorWritingToFile = 100,
    PSPDFAESEncryptorErrorEncryptingData = 110,
} NS_SWIFT_NAME(AESEncryptorError);

/// This class allows an streamed AES256 encryption of data into file using RNCryptor file format https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md
///
/// Requires the `Features.strongEncryption` feature flag.
NS_SWIFT_NAME(AESEncryptor)
@interface PSPDFAESEncryptor : NSObject

/// Designated initializer with the passphrase.
///
/// Encryption salt(random bytes) and HMAC salt(random bytes) WILL BE saved in the file header https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md
/// URL for the target encrypted file must be a file-based URL.
/// The default PRF is `kCCPRFHmacAlgSHA1`.
/// The default number of iterations is `PSPDFAESDefaultPBKDFNumberOfRounds` (10000).
- (instancetype)initWithURL:(NSURL *)targetURL passphrase:(NSString *)passphrase;

/// Designated initializer with the passphrase, customized PRF and iterations number.
///
/// Encryption salt(random bytes) and HMAC salt(random bytes) WILL BE saved in the file header https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md
/// URL for the target encrypted file must be a file-based URL.
/// The default PRF is `kCCPRFHmacAlgSHA1`.
/// The default number of iterations is `PSPDFAESDefaultPBKDFNumberOfRounds` (10000).
- (instancetype)initWithURL:(NSURL *)targetURL passphrase:(NSString *)passphrase PRF:(PSPDFPseudoRandomAlgorithm)prf rounds:(NSUInteger)rounds;

/// Designated initializer with stretched, binary key.
///
/// Encryption salt and HMAC salt WILL NOT BE saved in the file header https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md
/// Warning: only use this if the key is cryptographically random and of length `kCCKeySizeAES256`.
/// URL for the target encrypted file must be a file-based URL.
/// The default PRF is `kCCPRFHmacAlgSHA1`.
/// The default number of iterations is `PSPDFAESDefaultPBKDFNumberOfRounds` (10000).
- (instancetype)initWithURL:(NSURL *)targetURL key:(NSData *)key;

/// Contains error if the operation was unsuccessful.
@property (nonatomic, readonly) NSError *error;

/// Encrypts and writes the buffer of the length. Return YES if operation was successful, and NO if not (see error property).
- (BOOL)write:(const void *)buffer length:(size_t)length;

/// Finalizes necessary hash codes for RNCryptor format and closes the encrypted output file. Return YES if operation was successful, and NO if not (see error property).
- (BOOL)finish;

@end
