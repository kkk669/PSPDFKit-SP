//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFResetFormAction.h>

@class PSPDFFormElement, PSPDFDocumentProvider, PSPDFFormField, PSPDFJavaScriptFormField;

NS_ASSUME_NONNULL_BEGIN

/// Parses PDF Forms ("AcroForms").
/// This will not create objects based on the (soon deprecated) XFA standard.
///
/// @see https://pspdfkit.com/guides/ios/rendering-issues/pspdfkit-doesnt-show-the-pdf-form/
PSPDF_CLASS_SWIFT(PDFFormParser)
@interface PSPDFFormParser : NSObject<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Attached document provider.
@property (nonatomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

/// A collection of all forms in AcroForm. Lazily evaluated.
@property (nonatomic, copy, readonly) NSArray<__kindof PSPDFFormElement *> *forms;

/// A collection of all form fields in the AcroForm. Lazily evaluated.
@property (nonatomic, copy, readonly, nullable) NSArray<__kindof PSPDFFormField *> *formFields;

/// Return all "dirty" = unsaved form elements
@property (nonatomic, readonly, nullable) NSArray<__kindof PSPDFFormElement *> *dirtyForms;

/// Finds a form element with its field name. Returns nil if not found.
- (nullable __kindof PSPDFFormElement *)findAnnotationWithFieldName:(NSString *)fieldName;

/// Finds a form field with the given fully qualified field name.
///
/// @param fullFieldName The fully qualified field name.
/// @return The form field, if found. nil otherwise.
- (nullable __kindof PSPDFFormField *)findFieldWithFullFieldName:(NSString *)fullFieldName;

/// Removes the form elements from the `AcroForms` structure inside the PDF and also removes
/// the visual representation (`widget annotation`) from the pages.
///
/// @note The `PSPDFFormField` will also be removed if it doesn't contain any `PSPDFFormElement` any more.
/// @note Depending on the size of your document, this operation will be slow and should not be run on the main thread.
/// @param formElements The `PSPDFFormElement`s to be removed.
/// @return YES if the form elements were removed, NO otherwise.
- (BOOL)removeFormElements:(NSArray<__kindof PSPDFFormElement *> *)formElements error:(NSError **)error;

/// Removes the form fields from the `AcroForms` structure inside the PDF, removes all linked `PSPDFFormElements` and
/// their visual representation (`widget annotation`) from the pages.
///
/// @note Depending on the size of your document, this operation will be slow and should not be run on the main thread.
/// @param formFields The `PSPDFFormField`s to be removed.
/// @return YES if the form elements were removed, NO otherwise.
- (BOOL)removeFormFields:(NSArray<__kindof PSPDFFormField *> *)formFields error:(NSError **)error;

/// Given a list of `formFields`, resets the form fields from the `AcroForms` structure inside the PDF.
///
/// If the `includeExclude` flag is set to YES, resets all form fields except those in the `formFields` list.
/// If the `includeExclude` flag is set to NO, resets all form fields in the `formFields` list.
///
/// @note If the `formFields` list is empty, resets all form fields in the PDF document.
/// @param formFields The `PSPDFFormField`s to be reset.
/// @param resetFormActionFlags Decides if the form fields that will be reset are those in the `formFields` list or every form field that is not in the `formFields` list. See `PSPDFResetFormActionFlag` documentation.
/// @return YES if the form fields were reset, NO otherwise.
- (BOOL)resetForm:(NSArray<PSPDFFormField *> *)formFields withFlags:(PSPDFResetFormActionFlag)resetFormActionFlags error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
