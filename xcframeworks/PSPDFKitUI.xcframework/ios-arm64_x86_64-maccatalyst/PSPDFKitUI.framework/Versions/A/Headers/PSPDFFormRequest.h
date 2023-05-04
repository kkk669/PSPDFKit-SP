//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// The possible formats a form submission can be encoded in.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSubmitFormActionFormat) {
    /// The form will be submitted in Forms Data Format.
    PSPDFSubmitFormActionFormatFDF,
    /// The form will be submitted in XML Forms Data Format.
    PSPDFSubmitFormActionFormatXFDF,
    /// The form will be submitted in Hypertext Markup Language.
    PSPDFSubmitFormActionFormatHTML,
    /// The form will be submitted in Portable Document Format.
    PSPDFSubmitFormActionFormatPDF,
} PSPDF_ENUM_SWIFT(SubmitFormActionFormat);

NS_ASSUME_NONNULL_BEGIN

/// Models a request to submit a form in a PDF document to a remove server.
PSPDF_CLASS_SWIFT(PDFFormRequest)
@interface PSPDFFormRequest : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates and returns a new form request.
- (instancetype)initWithFormat:(PSPDFSubmitFormActionFormat)format values:(NSDictionary<NSString *, id> *)values request:(NSURLRequest *)request NS_DESIGNATED_INITIALIZER;

/// How the form data is to be encoded in the submission.
@property (nonatomic, readonly) PSPDFSubmitFormActionFormat submissionFormat;

/// Keys and values of the data to be submitted.
@property (nonatomic, readonly) NSDictionary<NSString *, id> *formValues;

/// The URL request that will be used to fulfill the submission.
@property (nonatomic, readonly) NSURLRequest *request;

@end

NS_ASSUME_NONNULL_END
