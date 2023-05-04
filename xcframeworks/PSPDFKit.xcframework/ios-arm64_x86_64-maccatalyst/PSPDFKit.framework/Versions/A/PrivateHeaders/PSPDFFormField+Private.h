//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormField.h>
#import <PSPDFKit/PSPDFUndoDiffable.h>

@class PSPDFDocumentProvider, PSPDFResetFormAction;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFFormField ()

/// Initializes the `PSPDFFormField` by adding it to the document and creating a core form field.
///
/// @param type The type of `PSPDFFormField` to create.
/// @param fullyQualifiedName The fully qualified name of the form field to be inserted.
/// @param documentProvider The document provider the form field should be attached to.
/// @param formElements One or more form elements that will be the visual representation of the form field.
/// @param buttonValues Only relevant for radio and checkboxes. Specifies what values represents the `on` state.
/// @param error Error.
/// @return Either an instance of the `PSPDFFormField` or nil if an error occurs.
/// @note Only `PSPDFFormFieldTypeCheckBox` and `PSPDFFormFieldTypeRadioButton` support more than one annotations. All other types require exactly one.
- (nullable instancetype)initWithType:(PSPDFFormFieldType)type fullyQualifiedName:(NSString *)fullyQualifiedName documentProvider:(PSPDFDocumentProvider *)documentProvider formElements:(NSArray<__kindof PSPDFFormElement *> *)formElements buttonValues:(nullable NSArray<NSString *> *)buttonValues error:(NSError **)error;

/// Overwritten property for private read-write support.
@property (nonatomic, readwrite) BOOL dirty;

/// Overwritten property for private read-write support.
@property (nonatomic, readwrite, weak) PSPDFDocumentProvider *documentProvider;

/// Resets the values of the form field.
- (void)resetWithAction:(nullable PSPDFResetFormAction *)action;

/// When a form field is set-up from a external file, `isInitializing` will be true.
/// This is used for setting the formatted contents core value. We don't need to do that when we're initializing.
@property (nonatomic, getter=isInitializing, readonly) BOOL initializing;
- (void)startInitializing;
- (void)finishInitializing;

/// Called when a form element that is managed by this form field did change.
- (void)managedFormElementDidChange:(PSPDFFormElement *)formElement;

/// Resets the annotation cache.
- (void)resetAnnotationsCache;

/// Faster access to annotations for objectNumber-search.
- (NSDictionary<NSNumber *, PSPDFFormElement *> *)annotationsMap;

@end

// MARK: - Undo

@interface PSPDFFormField () <PSPDFUndoDiffable>

/// A set of properties to be taken into account when diffing the form field
/// when diffing its owning annotation.
@property (class, nonatomic, readonly) NSSet<NSString *> *propertyKeysForUndo;

@end

NS_ASSUME_NONNULL_END
