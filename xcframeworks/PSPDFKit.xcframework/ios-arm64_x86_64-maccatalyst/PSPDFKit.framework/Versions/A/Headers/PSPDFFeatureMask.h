//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Declares all possible feature flags in a license.
typedef NS_OPTIONS(NSUInteger, PSPDFFeatureMask) {
    PSPDFFeatureMaskNone = 0,

    /// View PDFs without watermark. Automatically enabled by every valid license key.
    PSPDFFeatureMaskPDFViewer = 1 << 0,

    /// Text Selection. Was included in PSPDFKit Basic.
    PSPDFFeatureMaskTextSelection = 1 << 1,

    /// Enables `PSPDFAESCryptoDataProvider` and the various other crypto related classes.
    /// (`PSPDFCryptoInputStream`, `PSPDFCryptoOutputStream`, `PSPDFAESDecryptor`, `PSPDFAESEncryptor`)
    PSPDFFeatureMaskStrongEncryption = 1 << 2,

    /// Use an instance of `Processor`. Does not include the `Processor` class methods for conversion.
    PSPDFFeatureMaskPDFCreation = 1 << 3,

    /// Edit/Create annotations.
    PSPDFFeatureMaskAnnotationEditing = 1 << 4,

    /// PDF Forms display/editing.
    PSPDFFeatureMaskAcroForms = 1 << 5,

    /// Use the indexed full-text-search. (`PSPDFLibrary`)
    PSPDFFeatureMaskIndexedFTS = 1 << 6,

    /// Digitally Sign PDF Forms.
    PSPDFFeatureMaskDigitalSignatures = 1 << 7,

    /// Requires PDF files to be signed.
    PSPDFFeatureMaskRequireSignedSource = 1 << 8,

    /// Enables advanced document editing.
    PSPDFFeatureMaskDocumentEditing = 1 << 9,

    /// Enables the UI.
    PSPDFFeatureMaskUI = 1 << 10,

    /// Shows annotation replies in a comment thread.
    PSPDFFeatureMaskAnnotationReplies = 1 << 11,

    /// Enables the non-destructive editing of images.
    /// See `PSPDFImageDocument` for more information.
    PSPDFFeatureMaskImageDocument = 1 << 12,

    /// Enables redacting page content.
    PSPDFFeatureMaskRedaction = 1 << 13,

    /// Enables comparing, merging and recoloring document pages.
    /// See `PSPDFProcessorConfiguration`.
    PSPDFFeatureMaskComparison = 1 << 14,

    /// Enables HTML to PDF conversion and attributed string to PDF conversion using the `Processor` class methods.
    PSPDFFeatureMaskWebKitHtmlConversion = 1 << 16,

    /// Enables Reader View.
    PSPDFFeatureMaskReaderView = 1 << 17,

    /// Enables performing OCR on documents.
    PSPDFFeatureMaskOCR = 1 << 18,

    /// Electronic signing of documents.
    PSPDFFeatureMaskElectronicSignatures = 1 << 19,
    
    /// PDF/A validation and conversion.
    PSPDFFeatureMaskPDFA = 1 << 20,

    /// Measurement tools.
    PSPDFFeatureMaskMeasurementTools = 1 << 21,

    /// Content editing.
    PSPDFFeatureMaskContentEditing = 1 << 22,

    PSPDFFeatureMaskAll = UINT_MAX
} PSPDF_ENUM_SWIFT(Features);
