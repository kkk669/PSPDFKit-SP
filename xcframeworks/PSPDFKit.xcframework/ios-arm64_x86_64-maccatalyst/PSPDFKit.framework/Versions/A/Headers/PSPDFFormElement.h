//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFResetFormAction.h>
#import <PSPDFKit/PSPDFWidgetAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFFormField;

/// The minimum acceptable font to be used when editing fields with autosizing fonts.
static const CGFloat PSPDFMinimumAcceptableFontSize = 5.0;

/// Represents a PDF form element.
PSPDF_CLASS_SWIFT(FormElement)
@interface PSPDFFormElement : PSPDFWidgetAnnotation

/// Returns the form field linked to this annotation.
@property (atomic, weak, readonly) PSPDFFormField *formField;

/// Returns true if we can reset this form element to default values.
@property (atomic, getter=isResettable, readonly) BOOL resettable;

/// (Optional; inheritable) The default value to which the field reverts when a reset-form action is executed (see 12.7.5.3, “Reset-Form Action”). The format of this value is the same as that of V.
@property (atomic, readonly, nullable) id defaultValue;

/// The value which the field is to export when submitted. Can return either a string or an array of strings in the case of multiple selection.
@property (atomic, readonly, nullable) id exportValue;

/// Color when the annotation is being highlighted.
///
/// @note PSPDFKit extension. Won't be saved into the PDF.
@property (atomic, nullable) UIColor *highlightColor;

/// The previous control in tab order.
@property (atomic, weak) PSPDFFormElement *next;

/// The next control in tab order.
@property (atomic, weak) PSPDFFormElement *previous;

/// Position of the receiver in the form calculation order list (used when a form with JavaScript scripts must be recalculated).
/// An index of 0 is the first position in that list, an index of 1 is the second position, and so on. For example, if the receiver is the first form field that is recalculated in a form document, then this property has a value of `0`.
@property (atomic, readonly) NSUInteger calculationOrderIndex;

/// If set, the user may not change the value of the field. Any associated widget annotations will not interact with the user; that is, they will not respond to mouse clicks or change their appearance in response to mouse motions. This flag is useful for fields whose values are computed or imported from a database.
/// This reflects the set value for this property on the linked `formField`.
@property (atomic, getter=isReadOnly, readonly) BOOL readOnly;

/// If set, the field shall have a value at the time it is exported by a submit- form action (see 12.7.5.2, “Submit-Form Action”).
/// This reflects the set value for this property on the linked `formField`.
///
/// Partially supported. A border will be shown around required elements according to `requiredFormBorderColor` in the
/// `RenderOptions`, but PSPDFKit will not ensure all required fields are filled before executing a submit form action.
@property (atomic, getter=isRequired, readonly) BOOL required;

/// If set, the field shall not be exported by a submit-form action (see 12.7.5.2, “Submit-Form Action”).
/// This reflects the set value for this property on the linked `formField`.
///
/// Not supported. PSPDFKit will read this flag from the PDF and write back changes to its state, but otherwise this flag has no effect on PSPDFKit.
@property (atomic, getter=isNoExport, readonly) BOOL noExport;

/// The partial field name.
@property (atomic, readonly, nullable) NSString *fieldName;

/// The T entry in the field dictionary (see Table 220) holds a text string defining the field’s partial field name. The fully qualified field name is not explicitly defined but shall be constructed from the partial field names of the field and all of its ancestors. For a field with no parent, the partial and fully qualified names are the same. For a field that is the child of another field, the fully qualified name shall be formed by appending the child field’s partial name to the parent’s
/// fully qualified name, separated by a PERIOD (2Eh) — PDF Spec
@property (atomic, readonly, nullable) NSString *fullyQualifiedFieldName;

/// Returns the Form Type Name. "Form Element", "Text Field" etc
@property (atomic, readonly) NSString *formTypeName;

// MARK: - Fonts

/// The maximum length of the field’s text, in characters. (Optional; inheritable)
@property (atomic) NSUInteger maxLength;

/// Whether the text field should scroll with it's content.
///
/// (PDF 1.4) If set, the field shall not scroll (horizontally for single-line fields, vertically for multiple-line fields) to accommodate more text than fits within its annotation rectangle. Once the field is full, no further text shall be accepted for interactive form filling; for non- interactive form filling, the filler should take care not to add more character than will visibly fit in the defined area.
@property (atomic) BOOL doNotScroll;

/// Properties for rendering
@property (atomic) BOOL isMultiline;

@end

// MARK: - Deprecated API

@interface PSPDFFormElement (Deprecated)

/// Draws the form highlight.
- (void)drawHighlightInContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)renderOptions multiply:(BOOL)shouldMultiply PSPDF_DEPRECATED(11.4, "This method is unused since at least PSPDFKit 10.2 for iOS and will be removed in a future release.");

@end

NS_ASSUME_NONNULL_END
