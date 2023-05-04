//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormField.h>

@class PSPDFWidgetAnnotation, PSPDFFormOption;

NS_ASSUME_NONNULL_BEGIN

/// Represents one button form field in a PDF form.
/// They come in three variants:
/// - A push button that can have a action attached to it.
/// - A check box that can be independently checked or unchecked.
/// - A radio button that are mutually exclusive.
///
/// A `PSPDFButtonFormField` can be the parent of multiple buttons, like a RadioButton group.
PSPDF_CLASS_SWIFT(ButtonFormField)
@interface PSPDFButtonFormField : PSPDFFormField

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Inserts a new `PSPDFButtonFormField` into the document.
///
/// @note This new form field will automatically be added to the document.
/// @note `PSPDFFormFieldTypePushButton` only supports one form element.
///
/// @param type The type of the `PSPDFButtonFormField`. Can be `PSPDFFormFieldTypePushButton`, `PSPDFFormFieldTypeRadioButton` or `PSPDFFormFieldTypeCheckBox`.
/// @param fullyQualifiedName Each form field is identifiable using its fully qualified name. You can specify any dot separated name.
/// @param documentProvider The document the form field gets inserted in.
/// @param formElements One or more `PSPDFButtonFormElement` that will be linked to this form field. The form elements are the visual representation of the form on the page. If the form elements aren't yet added to the document provider, they will be added.
/// @param buttonValues When creating radio buttons or checkboxes, you have to supply their on-state value. For each form element passed in, you have to supply one string value in the array. The value cannot be `Off`.
/// @param error The error, if any happens.
/// @return Either an instance of `PSPDFButtonFormField` or nil if an error occurs.
+ (nullable instancetype)insertedButtonFieldWithType:(PSPDFFormFieldType)type fullyQualifiedName:(NSString *)fullyQualifiedName documentProvider:(PSPDFDocumentProvider *)documentProvider formElements:(NSArray<__kindof PSPDFFormElement *> *)formElements buttonValues:(NSArray<NSString *> *)buttonValues error:(NSError *__autoreleasing *)error;

/// A push button is a purely interactive control that responds immediately to user input without retaining a permanent value (see 12.7.4.2.2, “Pushbuttons”).
@property (nonatomic, readonly) BOOL isPushButton;

/// A check box toggles between two states, on and off (see 12.7.4.2.3, “Check Boxes”).
@property (nonatomic, readonly) BOOL isCheckBox;

/// Radio button fields contain a set of related buttons that can each be on or off. Typically, at most one radio button in a set may be on at any given time, and selecting any one of the buttons automatically deselects all the others. (There are exceptions to this rule, as noted in "Radio Buttons.")
@property (nonatomic, readonly) BOOL isRadioButton;

/// A set of selected annotation object numbers.
@property (nonatomic) NSArray<NSNumber *> *selectedAnnotationObjectNumbers;

/// (Optional) An array of options that shall be presented to the user.
@property (nonatomic, copy) NSArray<PSPDFFormOption *> *options;

/// The appearance state to be used in the 'on' position.
/// This will be a key in the dictionary of appearance streams for the different states. The off state is always "Off".
///
/// @note If the Key is in Non-ASCII format, this will convert it to be in UTF-8.
/// If a key has been converted from another format (e.g. ISO9959-1) then you cannot use this value to set the state.
- (nullable NSString *)onStateForButton:(PSPDFWidgetAnnotation *)annotation;

/// Toggles the button state.
///
/// @param annotation The annotation representing the button.
- (void)toggleButton:(PSPDFWidgetAnnotation *)annotation;

/// Checks if the given annotation is selected.
///
/// @param annotation The annotation representing the button.
/// @return YES if selected, NO otherwise.
- (BOOL)isSelected:(PSPDFWidgetAnnotation *)annotation;

/// Selects the button.
///
/// @param annotation The annotation representing the button.
- (void)selectButton:(PSPDFWidgetAnnotation *)annotation;

/// Deselects the button.
///
/// @param annotation The annotation representing the button.
- (void)deselectButton:(PSPDFWidgetAnnotation *)annotation;

/// Gets the value of the button.
///
/// @param annotation The annotation representing the button.
///
/// @note If the Key is in Non-ASCII format, this will convert it to be in UTF-8.
/// If a key has been converted from another format (e.g. ISO9959-1) then you cannot use this value to set the state.
- (nullable NSString *)valueForButton:(PSPDFWidgetAnnotation *)annotation;

@end

NS_ASSUME_NONNULL_END
