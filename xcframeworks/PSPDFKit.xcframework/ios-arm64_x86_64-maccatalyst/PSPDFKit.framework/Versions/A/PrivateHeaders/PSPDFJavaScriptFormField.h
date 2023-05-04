//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

@class PSPDFDocumentProvider, PSPDFFormParser, PSPDFFormField, PSPDFFormElement;

NS_ASSUME_NONNULL_BEGIN

/// The PDF JavaScript API expects a PDF AcroForm environment that differs from the one we work with. The core form API
/// is a little simplified but still offers all the features we need. The biggest example of difference is that we do
/// not have a hierarchy but have a flat namespace.
///
/// The official API, http://help.adobe.com/livedocs/acrobat_sdk/10/Acrobat10_HTMLHelp/wwhelp/wwhimpl/js/html/wwhelp.htm?href=JS_API_AcroJS.88.1.html#1515776&accessible=true,
/// does expect a hierarchy and we have to supply one. We do this by initializing a `PSPDFJavaScriptFormField` with the
/// form that is wanted and split it up into a hierarchy of `PSPDFJavaScriptFormField` items.
PSPDF_SDK_CLASS_SWIFT(JavaScriptFormField)
@interface PSPDFJavaScriptFormField : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Finds the correct `PSPDFJavaScriptFormField` for the given fully qualified name.
///
/// @param fullyQualifiedName The name where to start building the form hierarchy.
/// @param formParser The form parser.
/// @return An instance of this type.
+ (nullable instancetype)findJavaScriptFormFieldFromFullyQualifiedName:(NSString *)fullyQualifiedName formParser:(PSPDFFormParser *)formParser;

/// Creates a root JavaScript form field node from the given list of form fields.
///
/// @param formFields The form fields intended to be used from JavaScript.
/// @param documentProvider The document provider associated with the given form fields.
/// @return The root node of the JavaScript form hierarchy.
+ (nullable instancetype)createRootJavaScriptFormFieldWithFormFields:(NSArray<PSPDFFormField *> *)formFields documentProvider:(PSPDFDocumentProvider *)documentProvider;

/// The document provider.
@property (nonatomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

/// The kids of this form field.
@property (nonatomic, readonly) NSArray<PSPDFJavaScriptFormField *> *kids;

/// Returns all kid annotations.
@property (nonatomic, readonly) NSArray<PSPDFFormElement *> *annotationKids;

/// The form field name of this form field.
@property (nonatomic, readonly) NSString *name;

/// The fully qualified form field name (FQN) of this form field.
@property (nonatomic, readonly) NSString *fullyQualifiedName;

/// The actual form field. Can be null in faked hierarchy.
@property (nonatomic, nullable, readonly) PSPDFFormField *formField;

/// In terminal fields that also have a widget, this is set to the actual widget annotation.
@property (nonatomic, nullable, readonly) PSPDFFormElement *formElement;

/// Returns the kid with the given name or nil if there is none.
- (nullable PSPDFJavaScriptFormField *)kidWithName:(NSString *)name;

@end

NS_ASSUME_NONNULL_END
