//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFDocumentProvider.h>
#import <PSPDFKit/PSPDFDocument.h>

NS_ASSUME_NONNULL_BEGIN

/// The algorithm to use to encrypt a document.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFDocumentEncryptionAlgorithm) {
    /// AES (Advanced Encryption Standard) is a secure, symmetric block cipher.
    PSPDFDocumentEncryptionAlgorithmAES,
    /// RC4 algorithm (Rivest Cipher 4 also known as ARC4 or ARCFOUR). This algorithm is deprecated in PDF 2.0.
    PSPDFDocumentEncryptionAlgorithmRC4,
} NS_SWIFT_NAME(DocumentEncryptionAlgorithm);

/// The constant to be used to indicate that the key length should be determined automatically.
PSPDF_EXPORT const NSUInteger PSPDFDocumentSecurityOptionsKeyLengthAutomatic NS_SWIFT_NAME(Document.SecurityOptionsKeyLengthAutomatic);


/// This class describes the security options you want to use when saving a PDF
/// file. Using a security options object overrides the default options of a file.
///
/// A PDF file can have multiple security-related options set. The owner password
/// generally controls the editing of a document and is required as soon as you
/// want to encrypt a document of any kind. The user password prevents users from
/// viewing the PDF. It is optional but if you specify it you also need to specify
/// an owner password.
///
/// You can also specify the key length of the encryption. This controls how large
/// the key is that is used for actually encrypting the document. The key is
/// derived from the passwords you specify. As soon as you specify at least an
/// owner password you also need to decide on a key length to be used. You can also
/// specify `PSPDFDocumentSecurityOptionsKeyLengthAutomatic` in all cases and let
/// PSPDFKit decide on if and what key length to use.
///
/// To specify what operations are allowed when opening the document with user
/// privileges you can also set `PSPDFDocumentPermissions`. With user privileges
/// you can always view the file in question and by specifying
/// `PSPDFDocumentPermissions` you can grant further rights that otherwise would
/// only be available when the user has owner privileges.
///
/// PSPDFKit supports two encryption algorithms: RC4 and AES. RC4 is a proprietary
/// encryption algorithm of RSA Security Inc. It is a symmetric stream cipher,
/// ie. the same algorithm is used for both encryption and decryption, and the
/// algorithm does not change the length of the data. AES support was introduced with
/// PDF 1.6. It is a symmetric block cipher, ie. the same algorithm is used for both
/// encryption and decryption, and the length of the data when encrypted is rounded up
/// to a multiple of the block size, which is fixed in this implementation to always be
/// 16 bytes.
///
/// @note In order to use this class, you need a license that enables you to use
/// the Document Editor. If you want to process a file while keeping the options of
/// the original file, simply pass `nil` for security options.
PSPDF_CLASS_SWIFT(Document.SecurityOptions)
@interface PSPDFDocumentSecurityOptions : NSObject

/// Initializes a newly allocated document security options object with no
/// passwords. Use this instance to save a document without any security. This
/// is a convenience initializer and is equivalent to sending
/// `initWithOwnerPassword:userPassword:` with both passwords set to `nil`.
- (instancetype)init;

/// Allows you to set different passwords on the resulting document. This is a
/// convenience initializer and is equivalent to sending
/// `initWithOwnerPassword:userPassword:keyLength:` with `keyLength` set to
/// `PSPDFDocumentSecurityOptionsKeyLengthAutomatic`.
///
/// If an error occurs, this returns `nil` and throws the error (Swift) or sets the out `error` parameter to the encountered error (Objective-C).
///
/// @param ownerPassword  The password to be used as the document owner password.
/// @param userPassword   The password to be used as the password of a regular user.
/// @param error          Upon return contains an error if the creation was not possible.
- (nullable instancetype)initWithOwnerPassword:(nullable NSString *)ownerPassword userPassword:(nullable NSString *)userPassword error:(NSError *__autoreleasing  *)error;

/// Allows you to set different passwords on the resulting document.
///
/// If an error occurs, this returns `nil` and throws the error (Swift) or sets the out `error` parameter to the encountered error (Objective-C).
///
/// @param ownerPassword  The password to be used as the document owner password.
/// @param userPassword   The password to be used as the password of a regular user.
/// @param keyLength      The length of the crypto key. This key must be a multiple
/// of 8 and between 40 and 128. You can also set the length
/// to `PSPDFDocumentSecurityOptionsKeyLengthAutomatic` to let
/// PSPDFKit maintain the key length for you. If you do not have
/// special needs, this might be the best choice for both,
/// encrypted and unencrypted documents.
/// @param error          Upon return contains an error if the creation was not possible.
- (nullable instancetype)initWithOwnerPassword:(nullable NSString *)ownerPassword userPassword:(nullable NSString *)userPassword keyLength:(NSUInteger)keyLength error:(NSError *__autoreleasing  *)error;

/// Allows you to set different passwords on the resulting document.
///
/// If an error occurs, this returns `nil` and throws the error (Swift) or sets the out `error` parameter to the encountered error (Objective-C).
///
/// @param ownerPassword        The password to be used as the document owner password.
/// @param userPassword         The password to be used as the password of a regular user.
/// @param keyLength            The length of the crypto key. This key must be a multiple
/// of 8 and between 40 and 128. You can also set the length
/// to `PSPDFDocumentSecurityOptionsKeyLengthAutomatic` to let
/// PSPDFKit maintain the key length for you. If you do not have
/// special needs, this might be the best choice for both,
/// encrypted and unencrypted documents.
/// @param documentPermissions  The permissions that should be set on the document.
/// @param error                Upon return contains an error if the creation was not possible.
- (nullable instancetype)initWithOwnerPassword:(nullable NSString *)ownerPassword userPassword:(nullable NSString *)userPassword keyLength:(NSUInteger)keyLength permissions:(PSPDFDocumentPermissions)documentPermissions error:(NSError *__autoreleasing  *)error;

/// Allows you to set different passwords on the resulting document.
///
/// If an error occurs, this returns `nil` and throws the error (Swift) or sets the out `error` parameter to the encountered error (Objective-C).
///
/// @param ownerPassword        The password to be used as the document owner password.
/// @param userPassword         The password to be used as the password of a regular user.
/// @param keyLength            The length of the crypto key. This key must be a multiple
/// of 8 and between 40 and 128. You can also set the length
/// to `PSPDFDocumentSecurityOptionsKeyLengthAutomatic` to let
/// PSPDFKit maintain the key length for you. If you do not have
/// special needs, this might be the best choice for both,
/// encrypted and unencrypted documents.
/// @param documentPermissions  The permissions that should be set on the document.
/// @param encryptionAlgorithm  The encryption algorithm to use. Can be RC4 or AES (recommended).
/// @param error Upon return contains an error if the creation was not possible.
- (nullable instancetype)initWithOwnerPassword:(nullable NSString *)ownerPassword userPassword:(nullable NSString *)userPassword keyLength:(NSUInteger)keyLength permissions:(PSPDFDocumentPermissions)documentPermissions encryptionAlgorithm:(PSPDFDocumentEncryptionAlgorithm)encryptionAlgorithm error:(NSError *__autoreleasing  *)error NS_DESIGNATED_INITIALIZER;

/// The owner password that will be set in the processed document or `nil` if the password should be removed.
@property (nonatomic, nullable, copy, readonly) NSString *ownerPassword;

/// The user password that will be set in the processed document or `nil` if the password should be removed.
@property (nonatomic, nullable, copy, readonly) NSString *userPassword;

/// The key-length of the encryption.
@property (nonatomic, readonly) NSUInteger keyLength;

/// The `PSPDFDocumentPermissions` that will be set.
@property (nonatomic, readonly) PSPDFDocumentPermissions permissions;

/// The algorithm used to encrypt the document.
@property (nonatomic, readonly) PSPDFDocumentEncryptionAlgorithm encryptionAlgorithm;

@end

NS_ASSUME_NONNULL_END
