//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSignatureFormElement;

/// Severity of a signature validation problem
typedef NS_CLOSED_ENUM(NSInteger, PSPDFSignatureStatusSeverity) {
    /// The validation status does not contain any problem.
    PSPDFSignatureStatusSeverityNone = 0,
    /// The validation status has some important but not blocker problems (ie. signed with a self-signed certificate).
    PSPDFSignatureStatusSeverityWarning,
    /// The validation status has some blocker problems. The signature should not be trusted.
    PSPDFSignatureStatusSeverityError,
} PSPDF_ENUM_SWIFT(PDFSignatureStatus.Severity);

/// Integrity status of a signature field.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFSignatureIntegrityStatus) {
    /// The document has not been modified since the last time it was signed.
    PSPDFSignatureIntegrityStatusOk = 0,
    /// The document has been tampered with since the last time it was signed.
    PSPDFSignatureIntegrityStatusTamperedDocument,
} PSPDF_ENUM_SWIFT(PDFSignatureStatus.Integrity);

/// Represents the status of a digital signature after it has been validated.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFSignatureStatus)
@interface PSPDFSignatureStatus : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer. Initializes a signature status from a given signer name, a signing date, and whether the signature covers the entire document,
/// that is, if there are no further changes possibly added by an incremental save to the document.
- (instancetype)initWithSigner:(nullable NSString *)signer signingDate:(nullable NSDate *)date coversEntireDocument:(BOOL)coversEntireDocument NS_DESIGNATED_INITIALIZER;

/// The signer name
@property (nonatomic, copy, nullable, readonly) NSString *signer;

/// The signing date
@property (nonatomic, copy, nullable, readonly) NSDate *signingDate;

/// Returns YES if the signature covers the entire document, that is, if there are no further changes
/// possibly added by an incremental save to the document. NO otherwise.
@property (nonatomic, readonly) BOOL coversEntireDocument;

/// Returns an array of problems as text strings
@property (nonatomic, readonly) NSArray<NSString *> *problems;

/// The status severity (None, if no problems; warning, or error).
@property (nonatomic, readonly) PSPDFSignatureStatusSeverity severity;

/// The integrity status of this signature field, that is, if the document that is protected by this signature has been
/// modified and the modification has broken this digital signature.
@property (nonatomic, readonly) PSPDFSignatureIntegrityStatus signatureIntegrityStatus;

/// Returns a status summary with the specified signer name and signing date
@property (nonatomic, readonly) NSString *summary;

@end

NS_ASSUME_NONNULL_END
