//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFSignaturePropBuild, PSPDFDigitalSignatureReference;

NS_ASSUME_NONNULL_BEGIN

/// Signature info for signature form fields.
///
/// @see `PSPDFSignatureFormElement`, `PSPDFSigner`
/// @see ISO 32000-2:2017(E) Table 255 — Entries in a signature dictionary
PSPDF_CLASS_SWIFT(PDFSignatureInfo)
@interface PSPDFSignatureInfo : NSObject

/// Specifies how many placeholder bytes will be reserved for the signature.
@property (nonatomic, readonly) NSUInteger placeholderBytes;

/// The signature value as data.
@property (nonatomic, copy, readonly, nullable) NSData *contents;

/// The ranges of the bytes of data being signed.
///
/// This property is deprecated in favor of `byteRanges`.
///
/// An array of pairs of integers (wrapped as `NSNumber`, starting byte offset, length in bytes) that shall describe the exact byte range for the digest calculation.
/// Multiple discontiguous byte ranges shall be used to describe a digest that does not include the signature value (the Contents entry) itself.
/// If SubFilter is ETSI.CAdES.detached, the ByteRange shall cover the entire file, including the signature dictionary but excluding the Contents value.
@property (nonatomic, copy, readonly, nullable) NSArray<NSNumber *> *byteRange NS_REFINED_FOR_SWIFT PSPDF_DEPRECATED(12.1, "Use byteRanges instead.");

/// The ranges of the bytes of data being signed.
///
/// The exact byte ranges for the digest calculation.
/// Multiple discontiguous byte ranges shall be used to describe a digest that does not include the signature value (the Contents entry) itself.
/// If SubFilter is ETSI.CAdES.detached, the ByteRange shall cover the entire file, including the signature dictionary but excluding the Contents value.
@property (nonatomic, copy, readonly, nullable) NSIndexSet *byteRanges;

/// The PDF filter name to use for this signer. Typical values are
/// `Adobe.PPKLite`, `Entrust.PPKEF`, `CICI.SignIt`, and `VeriSign.PPKVS`.
/// Returns `Adobe.PPKLite` as default value, as it's the only value supported for now.
@property (nonatomic, copy, readonly, nullable) NSString *filter;

/// The PDF SubFilter entry value. Tied to `signatureType`.
/// Typical values are `ETSI.CAdES.detached`, `adbe.pkcs7.detached`, and `adbe.pkcs7.sha1`.
@property (nonatomic, copy, readonly, nullable) NSString *subFilter;

/// The name.
@property (nonatomic, copy, readonly, nullable) NSString *name;

/// The creation date of the signature.
@property (nonatomic, copy, readonly, nullable) NSDate *creationDate;

/// The place where this signature was created. For example, 'Vienna'.
@property (nonatomic, copy, readonly, nullable) NSString *location;

/// The reason that will be embedded in every digital signature created by this instance of `PSPDFSigner`.
/// For example, if you are signing a PDF contract you can set this property to `I agree with the terms of this contract`.
@property (nonatomic, copy, readonly, nullable) NSString *reason;

/// The build properties of the signature.
@property (nonatomic, copy, readonly, nullable) PSPDFSignaturePropBuild *propBuild;

/// (Optional; PDF 1.5) An array of signature reference dictionaries.
@property (nonatomic, copy, readonly, nullable) NSArray<PSPDFDigitalSignatureReference *> *references;

@end

NS_ASSUME_NONNULL_END
