//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractFormAction.h>

NS_ASSUME_NONNULL_BEGIN

/// Flags for submit-form actions. The names and behaviors of these flags are taken from the PDF reference.
///
/// If none of the format flags `.exportFormat`, `.xfdf`, and `.submitPDF` are specified then the format will be FDF.
/// For FDF, the `Content-Type` header field will incorrectly be `application/vnd.adobe.xfdf`. Please contact us if you require the correct type to be used (`application/vnd.fdf`).
typedef NS_OPTIONS(NSUInteger, PSPDFSubmitFormActionFlag) {
    PSPDFSubmitFormActionFlagIncludeExclude = 1 << (1 - 1),
    PSPDFSubmitFormActionFlagIncludeNoValueFields = 1 << (2 - 1),
    /// Whether to submit the form like a URL query string (as an HTML form would be submitted). This is ignored if `.xfdf` or `.submitPDF` is set.
    PSPDFSubmitFormActionFlagExportFormat = 1 << (3 - 1),
    /// Whether to use the HTTP GET method instead of the HTTP POST method.
    ///
    /// Not supported.
    PSPDFSubmitFormActionFlagGetMethod = 1 << (4 - 1),
    PSPDFSubmitFormActionFlagSubmitCoordinates = 1 << (5 - 1),
    /// Whether to submit the form as XFDF. This takes precedence over `.exportFormat`, but it is ignored if `.submitPDF` is set.
    ///
    /// The `Content-Type` header field will incorrectly be `application/vnd.fdf`. Please contact us if you require the correct type to be used (`application/vnd.adobe.xfdf`).
    PSPDFSubmitFormActionFlagXFDF = 1 << (6 - 1),
    PSPDFSubmitFormActionFlagIncludeAppendSaves = 1 << (7 - 1),
    PSPDFSubmitFormActionFlagIncludeAnnotations = 1 << (8 - 1),
    /// Whether to submit the whole PDF rather than extracting form field values. This takes precedence over `.exportFormat` and `.xfdf`.
    PSPDFSubmitFormActionFlagSubmitPDF = 1 << (9 - 1),
    PSPDFSubmitFormActionFlagCanonicalFormat = 1 << (10 - 1),
    PSPDFSubmitFormActionFlagExclNonUserAnnots = 1 << (11 - 1),
    PSPDFSubmitFormActionFlagExclFKey = 1 << (12 - 1),
    PSPDFSubmitFormActionFlagEmbedForm = 1 << (14 - 1),
} PSPDF_ENUM_SWIFT(SubmitFormAction.Flag);

/// Submit-Form-Action: Send data to a uniform resource locator. PDF 1.2.
///
/// These actions are executed by `PDFFormSubmissionController`.
PSPDF_CLASS_SWIFT(SubmitFormAction)
@interface PSPDFSubmitFormAction : PSPDFAbstractFormAction

/// Designated initializer.
- (instancetype)initWithURL:(nullable NSURL *)url flags:(PSPDFSubmitFormActionFlag)flags;

/// The target URL.
@property (nonatomic, copy, readonly, nullable) NSURL *URL;

/// The submit form action flags.
@property (nonatomic, readonly) PSPDFSubmitFormActionFlag flags;

@end

NS_ASSUME_NONNULL_END
