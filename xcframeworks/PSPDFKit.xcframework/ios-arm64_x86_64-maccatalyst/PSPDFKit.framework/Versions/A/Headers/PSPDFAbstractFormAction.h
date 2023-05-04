//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAction.h>

@protocol PSPDFFormFieldIdentifier;

PSPDF_CLASS_SWIFT(AbstractFormAction)
@interface PSPDFAbstractFormAction : PSPDFAction

/// An optional array, specifying the form fields to include or exclude (based on the `flags` property)
/// when executing this action.
///
/// Fields can be identified by their `objectNumber` (boxed as `NSNumber`) or their `fullyQualifiedName`.
/// The array can hold a mix of both types!
///
/// From the PDF Reference, version 1.7:
///
/// (Optional) An array identifying which fields to reset or which to exclude from resetting, depending on the setting of the Include/Exclude flag in the Flags entry (see Table 239). Each element of the array shall be either an indirect reference to a field dictionary or (PDF 1.3) a text string representing the fully qualified name of a field. Elements of both kinds may be mixed in the same array.
/// If this entry is omitted, the Include/Exclude flag shall be ignored; all fields in the document’s interactive form are reset.
@property (nonatomic, copy, nullable) NSArray<id<PSPDFFormFieldIdentifier>> *fields NS_REFINED_FOR_SWIFT;

@end

// MARK: - Possible Types of Form Field Identifier:

/// Trait for the types that can be found in the `fields` property of form actions.
@protocol PSPDFFormFieldIdentifier <NSObject> @end

/// The `objectNumber` of the form field.
@interface NSNumber (PSPDFFormFieldIdentifier) <PSPDFFormFieldIdentifier> @end

/// The `fullyQualifiedName` or the form field.
@interface NSString (PSPDFFormFieldIdentifier) <PSPDFFormFieldIdentifier> @end
