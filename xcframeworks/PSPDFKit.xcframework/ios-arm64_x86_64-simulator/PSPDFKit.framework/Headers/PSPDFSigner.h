//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFDocumentSignerDelegate.h>
#import <PSPDFKit/PSPDFDocumentSignerDataSource.h>
#import <PSPDFKit/PSPDFExternalSignature.h>

#import <PSPDFKit/PSPDFDataSink.h>
#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFDocumentProvider.h>
#import <PSPDFKit/PSPDFSignatureBiometricProperties.h>
#import <PSPDFKit/PSPDFSignatureContents.h>
#import <PSPDFKit/PSPDFSignatureFormElement.h>
#import <PSPDFKit/PSPDFSignatureType.h>
#import <PSPDFKit/PSPDFX509.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_EXPORT NSString *const PSPDFSignerErrorDomain;

typedef NS_ERROR_ENUM(PSPDFSignerErrorDomain, PSPDFSignerErrorCode) {
    /// No error during the signing process.
    PSPDFSignerErrorNone = noErr,
    /// A signature form element was not found in the document.
    PSPDFSignerErrorNoFormElementSet = 0x1,
    /// An error occurred while generating the PKCS#7 structure.
    PSPDFSignerErrorCannotNotCreatePKCS7 = 0x100,
    /// A problem occurred while adding the signature to the PKCS#7.
    PSPDFSignerErrorCannotNotAddSignatureToPKCS7 = 0x101,
    /// A problem occurred while initializing the PKCS#7 structure.
    PSPDFSignerErrorCannotNotInitPKCS7 = 0x102,
    /// An error occurred while generating the PKCS#7 signature.
    PSPDFSignerErrorCannotGeneratePKCS7Signature = 0x103,
    /// A problem occurred while writing the PKCS#7 signature to the document.
    PSPDFSignerErrorCannotWritePKCS7Signature = 0x104,
    /// The document was signed correctly but couldn't be verified afterwards.
    PSPDFSignerErrorCannotVerifySignature = 0x105,
    /// The signed document could not be created. Check that you have the necessary permissions for the destination folder.
    PSPDFSignerErrorCannotSaveToDestination = 0x106,
    /// The sub-filter type specified to create the signature is not supported.
    PSPDFSignerErrorUnsupportedSubfilterType = 0x107,
    /// Cannot find the signature, either in a new or existing document.
    PSPDFSignerErrorCannotFindSignature = 0x108,
    /// The attributes could not be signed.
    PSPDFSignerErrorCannotSignAttributes = 0x109,
    /// The form element could not be signed.
    PSPDFSignerErrorCannotSignFormElement = 0x110,
    /// The form element is already digitally signed, so it does not make sense to digitally sign it again.
    PSPDFSignerErrorCannotSignAlreadySigned = 0x111,
    /// The byte range of the document could not be hashed.
    PSPDFSignerErrorCouldNotHashDocument = 0x112,
} PSPDF_ENUM_SWIFT(PDFSignerError);

/// Completion block for the production of documents by a `PSPDFSigner` instance.
///
/// @param success     Indicates whether the `PSPDFSigner` operation finished successfully or not.
/// @param document    Instance of a `PSPDFDataSink` that contains the document produced by the `PSPDFSigner` operation.
/// @param error       Indicates why the `PSPDFSigner` operation didn't finish successfully, in case `success` returned NO.
typedef void (^PSPDFSignatureCreationBlock) (BOOL success, id<PSPDFDataSink> _Nullable document, NSError *_Nullable error);

@class PSPDFSignatureAppearance;

/// `PSPDFSigner` is an abstract signer class. Override methods in subclasses as necessary.
PSPDF_CLASS_SWIFT(PDFSigner)
@interface PSPDFSigner : NSObject<PSPDFDocumentSignerDelegate, PSPDFDocumentSignerDataSource, PSPDFExternalSignature, NSSecureCoding>

/// The PDF filter name to use for this signer. Typical values are
/// `Adobe.PPKLite`, `Entrust.PPKEF`, `CICI.SignIt`, and `VeriSign.PPKVS`.
/// Returns `Adobe.PPKLite` as default value, as it's the only value supported for now.
@property (nonatomic, readonly) NSString *filter;

/// The PDF Digital Signature type. This translated directly to signature "SubFilter" type in the PDF.
///
/// Returns `.CMS` by default, as this is the only value fully supported for now.
/// Other values are `.SHA1` (deprecated), and `.Pades` for
/// advanced digital signatures which are only partially supported.
@property (nonatomic) PSPDFSignatureType signatureType;

/// The name that will be displayed in the signature UI to identify this signer.
///
/// @note This is not the signer's name that will appear in the signature itself. The signer's name always comes from the
/// certificate that was used to sign the document.
@property (nonatomic, nullable) NSString *displayName;

/// The person or entity who signed the document.  Important: For security reasons, if the API requires you to pass a
/// certificate for signing, the CN of the certificate will be used and this field will be ignored.
@property (nonatomic, nullable) NSString *signersName;

/// The reason that will be embedded in every digital signature created by this instance of `PSPDFSigner`.
/// For example, if you are signing a PDF contract you can set this property to `I agree with the terms of this contract`.
@property (nonatomic, nullable) NSString *reason;

/// The place where this signature was created. For example, 'Vienna'.
@property (nonatomic, nullable) NSString *location;

/// Private key from the certificate used to produce the signature by encrypting the message digest from the PDF file.
/// (see details https://pspdfkit.com/guides/ios/features/digital-signatures/).
///
/// @note If you don't set a custom `delegate` object that will perform the actual signing, you must set this property.
@property (nonatomic, nullable) PSPDFPrivateKey *privateKey;

/// The data source responsible for providing information about the digital signature, like the algorithms that will be used
/// to hash and encrypt, whether biometric properties should also be embedded or not, or the visual appearance that the signature
/// form element will have once the document is saved.
@property (nonatomic, weak) id<PSPDFDocumentSignerDataSource> dataSource;

/// The delegate that will be called when the actual signing process is taking place. It gives the opportunity
/// to customize the signature process in an asynchronous way. If this delegate is not set,
/// a default digital signature will be created by using the `privateKey` property of the receiver.
@property (nonatomic, weak) id<PSPDFDocumentSignerDelegate> delegate;

/// Builds a document where `element` is prepared with a custom appearance and filled with `contents` of `estimatedSize`.
///
/// @param element                 The signature form element to sign.
/// @param signatureAppearance     The `PSPDFSignatureAppearance` instance that customizes how the signature will appear in the signed document. If `nil`, the default signature appearance will be used.
/// @param contents                An implementation of the `PSPDFSignatureContents` protocol that will be used to fill the digital signature contents. Typically, you will want to pass an instance of a `PSPDFBlankSignatureContents` to simply fill the signature contents with zeros.
/// @param dataSink                The destination data sink for the prepared document. @see `PSPDFDataSink`.
/// @param completionBlock         A closure called after preparation succeeds or fails.
- (void)prepareFormElement:(PSPDFSignatureFormElement *)element toBeSignedWithAppearance:(PSPDFSignatureAppearance *)signatureAppearance contents:(id<PSPDFSignatureContents>)contents writingToDataSink:(id<PSPDFDataSink>)dataSink completion:(PSPDFSignatureCreationBlock)completionBlock;

/// Embeds signature contents in a form signature `element`. It assumes that the document that contains `element` has been prepared for digital signatures by calling `prepareFormElement:toBeSignedWithAppearance:contents:writingToDataSink:completion:` before.
///
/// @param element                 The signature form element to sign.
/// @param contents                An implementation of the `PSPDFSignatureContents` protocol that will be used to fill the digital signature contents.
/// @param dataSink                The destination data sink for the prepared document. @see `PSPDFDataSink`.
/// @param completionBlock         A closure called after embedding succeeds or fails.
- (void)embedSignatureInFormElement:(PSPDFSignatureFormElement *)element withContents:(id<PSPDFSignatureContents>)contents writingToDataSink:(id<PSPDFDataSink>)dataSink completion:(PSPDFSignatureCreationBlock)completionBlock;

/// This method signs a piece of data using a private key and uses `hashAlgorithm` for the signature padding.
- (NSData *)signData:(NSData *)data privateKey:(PSPDFPrivateKey *)privateKey hashAlgorithm:(PSPDFSignatureHashAlgorithm)hashAlgorithm;

/// Signs the passed form element `element` and writes the signed document
/// to `dataSink`. The completion block will signal if the result was successful, return the signed document, if it was signed correctly,
/// and the signing error, if there's any.
///
/// @param element                 The signature form element to sign.
/// @param certificate             The X509 certificate that will be used to create the digital signature.
/// @param dataSink                The destination data sink for the signed document. @see `PSPDFDataSink`.
/// @param completionBlock         A closure called after signing succeeds or fails.
- (void)signFormElement:(PSPDFSignatureFormElement *)element withCertificate:(PSPDFX509 *)certificate writeToDataSink:(id<PSPDFDataSink>)dataSink completionBlock:(nullable void (^)(BOOL success, id<PSPDFDataSink> _Nullable document, NSError *_Nullable error))completionBlock NS_REQUIRES_SUPER;

/// Signs the passed form element `element` and writes the signed document
/// to `path`. The completion block will signal if the result was successful, return the signed document, if it was signed correctly,
/// and the signing error, if there's any.
///
/// @param element                 The signature form element to sign.
/// @param certificate             The X509 certificate that will be used to create the digital signature.
/// @param path                    The destination path for the signed document.
/// @param completionBlock         A closure called after signing succeeds or fails.
- (void)signFormElement:(PSPDFSignatureFormElement *)element withCertificate:(PSPDFX509 *)certificate writeTo:(NSString *)path completionBlock:(nullable void (^)(BOOL success, PSPDFDocument *_Nullable document, NSError *_Nullable error))completionBlock NS_REQUIRES_SUPER;

@end

// MARK: -

/// Abstract API to be provided via category in UI level framework for specific subclasses of
/// `PSPDFSigner`.
@interface PSPDFSigner (PSPDFUI)

/// (Override) This method requests the signing certificate on demand. If the
/// certificate is for instance password protected or must be fetched over the
/// network, you can push a custom `UIViewController` on the passed navigation
/// controller to display a custom UI while unlocking/fetching the certificate.
/// If you are done, call the done handler with the fetched certificate and/or
/// and error value.
/// Subclasses of `PSPDFSigner` must override this method.
/// Overrides must not call super.
///
/// @param sourceController        A `UINavigationController` on which to push the UI for unlocking/fetching the certificate.
/// @param completionBlock         A closure to be called after the certificate has been fetched or the request failed.
#if !TARGET_OS_OSX
- (void)requestSigningCertificate:(id)sourceController completionBlock:(nullable void (^)(PSPDFX509 *_Nullable x509, NSError *_Nullable error))completionBlock;
#endif

@end

NS_ASSUME_NONNULL_END
