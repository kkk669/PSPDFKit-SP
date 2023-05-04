//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormField.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents a signature form field in a PDF form.
PSPDF_CLASS_SWIFT(SignatureFormField)
@interface PSPDFSignatureFormField : PSPDFFormField

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Inserts a new `PSPDFSignatureFormField` into the document.
///
/// @note This new form field will automatically be added to the document.
///
/// @param fullyQualifiedName Each form field is identifiable using its fully qualified name. You can specify any dot separated name.
/// @param documentProvider The document the form field gets inserted in.
/// @param formElement One `PSPDFChoiceFormElement` that will be linked to this form field. The form elements are the visual representation of the form on the page. If the form elements aren't yet added to the document provider, they will be added.
/// @param error The error, if any happens.
/// @return Either an instance of `PSPDFSignatureFormField` or nil if an error occurs.
+ (nullable instancetype)insertedSignatureFieldWithFullyQualifiedName:(NSString *)fullyQualifiedName documentProvider:(PSPDFDocumentProvider *)documentProvider formElement:(PSPDFFormElement *)formElement error:(NSError *__autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
