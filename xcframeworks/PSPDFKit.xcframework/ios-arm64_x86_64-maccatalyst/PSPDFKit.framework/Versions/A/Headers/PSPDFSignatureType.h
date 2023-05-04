//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// The signature type defines the digital signature format that will be used to sign the document.
///
/// @see https://pspdfkit.com/guides/ios/features/digital-signatures/
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSignatureType) {
    /// CMS is the default signature type and will work for most common situations.
    /// This translates to PDF `SubFilter` value of `adbe.pkcs7.detached`.
    PSPDFSignatureTypeCMS,

    /// PAdES is an advanced digital signature type with long term validation (LTV).
    /// PAdES is not yet fully supported in PSPDFKit so this option should be used with caution.
    /// This translates to PDF `SubFilter` value of `ETSI.CAdES.detached`.
    PSPDFSignatureTypePades,

    /// Deprecated. SHA1 is an older signature type which has been deprecated in PDF 2.0.
    /// We are not able to sign documents using this type, but it can be checked on validation.
    /// This translates to PDF `SubFilter` value of `adbe.pkcs7.sha1`.
    PSPDFSignatureTypeSHA1
} PSPDF_ENUM_SWIFT(PDFSignatureType);

NS_ASSUME_NONNULL_END
