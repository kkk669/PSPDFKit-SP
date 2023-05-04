//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFileDataProviding.h>
#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAESDecryptor;

NS_ASSUME_NONNULL_BEGIN

/// In the old legacy file format the default number of PBKDF rounds is 50000.
/// The new default is `PSPDFAESDefaultPBKDFNumberOfRounds`. (10000)
PSPDF_EXPORT const NSUInteger PSPDFDefaultPBKDFNumberOfRounds NS_SWIFT_NAME(AESCryptoDataProvider.defaultNumberOfPBKDFRounds);

/// This class allows a transparent decryption of AES256 encrypted files using
/// the RNCryptor file format https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md
///
/// Legacy PSPDFKit old file format is also supported.
/// Use the provided encryption tool to prepare your documents.
///
/// Ensure your passphrase/salt are also protected within the binary, or at least obfuscated.
/// Encryption marginally slows down rendering, since everything is decrypted on the fly.
///
/// If saving annotations to a file managed by a `PSPDFAESCryptoDataProvider`, the whole file
/// will be re-written.
///
/// @note The initializers will return nil if the strong encryption feature is not enabled, or if you pass an invalid parameter configuration.
PSPDF_CLASS_SWIFT(AESCryptoDataProvider)
@interface PSPDFAESCryptoDataProvider : NSObject<PSPDFFileDataProviding>

/// Designated initializer with the passphrase and salt.
/// URL must be a file-based URL.
- (nullable instancetype)initWithURL:(NSURL *)url passphraseProvider:(NSString * (^)(void))passphraseProvider salt:(NSString *)salt rounds:(NSUInteger)rounds;

/// Initializer with the passphrase and salt as NSData rather than NSString.
/// URL must be a file-based URL.
- (nullable instancetype)initWithURL:(NSURL *)url passphraseDataProvider:(NSData * (^)(void))passphraseDataProvider salt:(NSData *)saltData rounds:(NSUInteger)rounds;

/// Designated initializer with the passphrase. Salt will be loaded from the header of the
/// file format (see https://github.com/RNCryptor/RNCryptor-Spec/blob/master/RNCryptor-Spec-v3.md )
///
/// The default PRF is kCCPRFHmacAlgSHA1.
/// The number of iterations will be the new default PSPDFAESDefaultPBKDFNumberOfRounds (10000)
/// URL must be a file-based URL.
- (nullable instancetype)initWithURL:(NSURL *)url passphraseProvider:(NSString * (^)(void))passphraseProvider;

/// Designated initializer with the passphrase and legacy file format PRF kCCPRFHmacAlgSHA256 and 50000 rounds.
///
/// Salt will be loaded from the header of the
/// URL must be a file-based URL.
- (nullable instancetype)initWithLegacyFileFormatURL:(NSURL *)url passphraseProvider:(NSString * (^)(void))passphraseProvider;

/// Designated initializer with a prepared, stretched, binary key.
///
/// Warning: only use this if the key is cryptographically random and of length `kCCKeySizeAES256`.
/// The default PRF is `kCCPRFHmacAlgSHA1`.
/// The default number of iterations is `PSPDFAESDefaultPBKDFNumberOfRounds` (10000).
/// For legacy file format use `kCCPRFHmacAlgSHA256` and 50000 rounds.
/// URL must be a file-based URL.
- (nullable instancetype)initWithURL:(NSURL *)url binaryKeyProvider:(NSData * (^)(void))binaryKeyProvider;

/// The local file URL the data provider was initialized with.
@property (nonatomic, readonly) NSURL *fileURL;

// MARK: - Implementations of optional protocol methods

/// Creates a new `AESCryptoDataSink` with the receiver’s `UID` and the given `options`.
///
/// This call never fails.
- (id<PSPDFDataSink>)createDataSinkWithOptions:(PSPDFDataSinkOptions)options error:(NSError **)error;

/// Replaces the file at `fileURL` with the contents of `replacementDataSink`.
///
/// @param replacementDataSink An instance of `AESCryptoDataSink`, typically created by calling `createDataSink(options:)`.
/// @param error A pointer to populate with an error IFF replacing the receiver’s content fails.
/// @warning This method raises an exception if `replacementDataSink` is not an instance of `AESCryptoDataSink`, or if `replacementDataSink.isFinished` is `false`.
/// or you forgot to call `finish` on it before passing it.
- (BOOL)replaceContentsWithDataSink:(id<PSPDFDataSink>)replacementDataSink error:(NSError **)error;

/// Removes the file at `fileURL`.
///
/// This method fails if the filesystem item at `fileURL` cannot be removed.
- (BOOL)deleteDataWithError:(NSError **)error;

/// Returns `false`
- (BOOL)useDiskCache;

@end

NS_ASSUME_NONNULL_END
