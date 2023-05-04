//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFDataSink.h>

NS_ASSUME_NONNULL_BEGIN

/// Writes an XML in XFDF standard from PSPDFKit annotations.
/// http://partners.adobe.com/public/developer/en/xml/XFDF_Spec_3.0.pdf
PSPDF_CLASS_SWIFT(XFDFWriter)
@interface PSPDFXFDFWriter : NSObject

/// Writes the given annotations to the given `dataSink` and blocks until done.
///
/// @param annotations The annotations that should be written.
/// @param dataSink The data sink the XML will be written to. See `-[PSPDFDataProviding createDataSinkWithOptions:]`.
/// @param documentProvider The document provider.
/// @param error Pass an error for better error description.
/// @return YES if the data was written, NO otherwise.
- (BOOL)writeAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations toDataSink:(id<PSPDFDataSink>)dataSink documentProvider:(PSPDFDocumentProvider *)documentProvider error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
