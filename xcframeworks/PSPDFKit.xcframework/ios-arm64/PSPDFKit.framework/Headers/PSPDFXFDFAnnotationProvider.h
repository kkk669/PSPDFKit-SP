//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFContainerAnnotationProvider.h>
#import <PSPDFKit/PSPDFDataProviding.h>

NS_ASSUME_NONNULL_BEGIN

/// Concrete implementation of the `PSPDFAnnotationProvider` protocol that uses a XFDF file as a source.
///
/// The XFDF file needs to be local and in a writable location, not on a web server.
/// This annotation provider handles data form fields according to the XFDF spec: "An XFDF file with form data contains form field names and values. When importing XFDF into Acrobat, the target PDF file must already contain the form fields. Importing XFDF updates the form field values in the PDF file. Exporting to XFDF puts the current value of the field in the value element. Using XFDF, it is not possible to create a new form field in a PDF document, or change anything other than the value of
/// an existing form field."
/// It complements an existing data form fields from PDF with values from the XFDF file. If data form field value is not found in the XFDF file it will be served by this provider with the default value.
///
/// If you use XFDF to fill out form elements, you will want to keep both the file annotation provider and the xfdf provider around,
/// using following order: annotationProviders = [xfdfProvider, fileProvider]. Without the fileProvider, form elements will not be found.
/// (In versions of PSPDFKit earlier than 7.5, we did that somewhat magically. This requirement has now been made explicit.)
///
/// @note Requires the `Features.annotationEditing` feature flag.
///
/// @note If an error occurs when attaching a parsed annotation a document, the error is logged and the annotation is skipped.
///
/// @warning If the XFDF contains annotations with page indices beyond the length
/// of the document, then warnings will be logged and those annotations will be skipped.
PSPDF_CLASS_SWIFT(XFDFAnnotationProvider)
@interface PSPDFXFDFAnnotationProvider : PSPDFContainerAnnotationProvider

/// Designated initializers.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider fileURL:(NSURL *)XFDFFileURL NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider dataProvider:(id<PSPDFDataProviding>)dataProvider NS_DESIGNATED_INITIALIZER;

/// The XFDF file URL.
@property (nonatomic, copy, readonly, nullable) NSURL *fileURL;

/// The data provider. If initialized with a `XFDFFileURL`, will be auto generated.
@property (nonatomic, readonly, nullable) id<PSPDFDataProviding> dataProvider;

/// Will force-load annotations. Usually invoked lazily.
/// Use `hasLoadedAnnotationsForPageAtIndex:` with any page (usually page 0) to detect if the annotations have been loaded yet.
///
/// @note If an error occurs when attaching a parsed annotation a document, the error is logged and the annotation is skipped.
- (void)loadAllAnnotations;

@end

NS_ASSUME_NONNULL_END
