//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>
#import <PSPDFKit/PSPDFDataProviding.h>

NS_ASSUME_NONNULL_BEGIN

/// Configures the style of a digital signature.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSignatureAppearanceMode) {
    /// Show the signature and signature description side-by-side.
    PSPDFSignatureAppearanceModeSignatureAndDescription,
    /// Show the signature description only.
    PSPDFSignatureAppearanceModeDescriptionOnly,
    /// Show the signature appearance stream set in `signatureWatermark` only.
    PSPDFSignatureAppearanceModeSignatureOnly
} PSPDF_ENUM_SWIFT(PDFSignatureAppearance.Mode);

@class PSPDFAnnotationAppearanceStream;

/// This configuration builder offers all properties of `PSPDFSignatureAppearance`
/// in a writable version.
///
/// @see `PSPDFSignatureAppearance`
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFSignatureAppearanceBuilder)
@interface PSPDFSignatureAppearanceBuilder : PSPDFBaseConfigurationBuilder

/// @see PSPDFSignatureAppearance.appearanceMode.
@property (nonatomic) PSPDFSignatureAppearanceMode appearanceMode;
/// @see PSPDFSignatureAppearance.showSignerName.
@property (nonatomic) BOOL showSignerName;
/// @see PSPDFSignatureAppearance.showSigningDate.
@property (nonatomic) BOOL showSigningDate;
/// @see PSPDFSignatureAppearance.showSignatureReason.
@property (nonatomic) BOOL showSignatureReason;
/// @see PSPDFSignatureAppearance.showSignatureLocation.
@property (nonatomic) BOOL showSignatureLocation;
/// @see PSPDFSignatureAppearance.signatureGraphic.
@property (nonatomic, nullable) PSPDFAnnotationAppearanceStream *signatureGraphic;
/// @see PSPDFSignatureAppearance.signatureWatermark.
@property (nonatomic, nullable) PSPDFAnnotationAppearanceStream *signatureWatermark;
/// @see PSPDFSignatureAppearance.reuseExistingAppearance.
@property (nonatomic) BOOL reuseExistingAppearance;
/// @see PSPDFSignatureAppearance.showWatermark.
@property (nonatomic) BOOL showWatermark;

@end

/// This class configures the appearance that a `PSPDFSignatureElement` will have in a document when signed.
///
/// By default, a digital signature form element will show information from the signing certificate, like the signer's name, the date when the document was signed, and so on.
/// Use a `PSPDFSignatureAppearance` instance when you want to configure further how this information is presented to the user.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFSignatureAppearance)
@interface PSPDFSignatureAppearance : PSPDFBaseConfiguration<PSPDFSignatureAppearanceBuilder *>

/// The appearance style that is configured (signature and description, description only, signature only).
/// Defaults to PSPDFSignatureAppearanceModeSignatureAndDescription.
@property (nonatomic, readonly) PSPDFSignatureAppearanceMode appearanceMode;

/// Whether to show or not the person who signed the `PSPDFSignatureElement`. Defaults to YES.
@property (nonatomic, readonly) BOOL showSignerName;

/// Whether to show or not the date when the document was signed. Defaults to YES.
@property (nonatomic, readonly) BOOL showSigningDate;

/// Whether to show or not the reason why the document was signed (ie. "Contract agreement"). Defaults to NO.
@property (nonatomic, readonly) BOOL showSignatureReason;

/// Whether to show or not the place where the document was signed. Defaults to NO.
@property (nonatomic, readonly) BOOL showSignatureLocation;

/// The signature graphic to show on the left part of a signature when mode is `PSPDFSignatureAppearanceModeSignatureAndDescription`.
/// Defaults to `nil`.
@property (nonatomic, readonly, nullable) PSPDFAnnotationAppearanceStream *signatureGraphic;

/// The signature watermark to show in the centre of the signature when mode is `PSPDFSignatureAppearanceModeSignatureAndDescription`.
/// If `PSPDFSignatureAppearanceModeSignatureOnly` is set, this is the entire appearance stream.
/// Apperance is centered by default but can fill the entire signature if width/height are the same as the signature form element.
/// Defaults to `nil` which renders the pspdfkit logo.
@property (nonatomic, readonly, nullable) PSPDFAnnotationAppearanceStream *signatureWatermark;

/// Configures whether the existing signature appearance is kept after the document is signed. Defaults to YES.
@property (nonatomic, readonly) BOOL reuseExistingAppearance;

/// Whether to show or not the signature watermark. Defaults to YES.
@property (nonatomic) BOOL showWatermark;

@end

NS_ASSUME_NONNULL_END
