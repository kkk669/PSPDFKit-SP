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

/// Represents a text form field in a PDF form. Allows the user to enter custom text.
PSPDF_CLASS_SWIFT(TextFormField)
@interface PSPDFTextFormField : PSPDFFormField

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Inserts a new `TextFormField` into the document.
///
/// @note This new form field will automatically be added to the document.
///
/// @param fullyQualifiedName Each form field is identifiable using its fully qualified name. You can specify any dot separated name.
/// @param documentProvider The document the form field gets inserted in.
/// @param formElement One `PSPDFChoiceFormElement` that will be linked to this form field. The form elements are the visual representation of the form on the page. If the form elements aren't yet added to the document provider, they will be added.
/// @param error The error, if any happens.
/// @return Either an instance of `PSPDFTextFormField` or nil if an error occurs.
+ (nullable instancetype)insertedTextFieldWithFullyQualifiedName:(NSString *)fullyQualifiedName documentProvider:(PSPDFDocumentProvider *)documentProvider formElement:(PSPDFFormElement *)formElement error:(NSError *__autoreleasing *)error;

/// If set, the field may contain multiple lines of text; if clear, the field’s text shall be restricted to a single line.
@property (nonatomic) BOOL isMultiLine;

/// If set, the field is intended for entering a secure password that should not be echoed visibly to the screen.
@property (nonatomic) BOOL isPassword;

/// Allows enabling the combing behavior where the field is automatically divided into as many equally spaced positions, or combs, as the value of `maxLength`, and the text is laid out into those combs.
/// Setting this property to `true` enables the `Comb` flag of the field flags. However, combing behavior is only enabled if `isMultiline`, `isPassword`, `fileSelect` are set to `false` and `maxLength` is greater than 0 i.e the `MultiLine`, `Password`, and `FileSelect` flags are disabled and the maximum length of text characters for the field is greater than 0 but not unlimited.
///
/// Comb spacing is not applied while editing, but will be visible when editing ends.
///
/// @return Returns `true` only when the combing behavior can be enabled. Meaning the `Comb` flag is enabled by setting this property to `true` with `isMultiline` property set to `false` and `maxLength` is greater than 0.
@property (nonatomic) BOOL isComb;

/// (PDF 1.4) If set, the field shall not scroll (horizontally for single-line fields, vertically for multiple-line fields) to accommodate more text than fits within its annotation rectangle. Once the field is full, no further text shall be accepted for interactive form filling; for non- interactive form filling, the filler should take care not to add more character than will visibly fit in the defined area.
@property (nonatomic) BOOL doNotScroll;

/// (PDF 1.5) If set, the value of this field shall be a rich text string (see 12.7.3.4, “Rich Text Strings”). If the field has a value, the RV entry of the field dictionary (Table 222) shall specify the rich text string.
///
/// Not supported. PSPDFKit will read this flag from the PDF and write back changes to its state, but otherwise this flag has no effect on PSPDFKit.
@property (nonatomic) BOOL isRichText;

/// (PDF 1.4) If set, text entered in the field shall not be spell-checked.
///
/// Not supported. PSPDFKit will read this flag from the PDF and write back changes to its state, but otherwise this flag has no effect on PSPDFKit.
@property (nonatomic) BOOL doNotSpellCheck;

/// (PDF 1.4) If set, the text entered in the field represents the pathname of a file whose contents shall be submitted as the value of the field.
///
/// Not supported. PSPDFKit will read this flag from the PDF and write back changes to its state, but otherwise this flag has no effect on PSPDFKit.
@property (nonatomic) BOOL fileSelect;

/// The text value of the text form field.
@property (nonatomic, copy, nullable) NSString *text;

/// The rich text value of the text form field.
@property (nonatomic, copy, nullable) NSString *richText;

/// The maximum length of the field’s text, in characters. Returns 0 if length is unlimited.
@property (nonatomic) NSUInteger maxLength;

@end

NS_ASSUME_NONNULL_END
