//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormElement.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFButtonFormField, PSPDFFormOption;

/// Button Form Element (check boxes, radio buttons, regular form push buttons)
PSPDF_CLASS_SWIFT(ButtonFormElement)
@interface PSPDFButtonFormElement : PSPDFFormElement

/// Returns `true` if button is selected.
@property (atomic, getter=isSelected, readonly) BOOL selected;

/// (Optional; inheritable; PDF 1.4) An array containing one entry for each widget annotation in the Kids array of the radio button or check box field. Each entry shall be a text string representing the on state of the corresponding widget annotation. When this entry is present, the names used to represent the on state in the AP dictionary of each annotation (for example, /1, /2) numerical position (starting with 0) of the annotation in the Kids array, encoded as a name object. This allows
/// distinguishing between the annotations even if two or more of them have the same value in the Opt array.
@property (atomic, copy, nullable, readonly) NSArray<PSPDFFormOption *> *options;

/// The appearance state to be used in the 'on' position. This will be a key in the dictionary of appearance streams for the different states. The off state is always "Off".
@property (atomic, copy, readonly, nullable) NSString *onState;

/// Returns the parent property `formField` cast to the appropriate `PSPDFButtonFormField` type.
@property (atomic, readonly, nullable) PSPDFButtonFormField *buttonFormField;

/// Select the button.
- (void)select;

/// Deselect the button.
- (void)deselect;

/// Toggle button selection state.
///
/// @return YES if toggled, NO otherwise.
- (BOOL)toggleButtonSelectionState;

@end

NS_ASSUME_NONNULL_END
