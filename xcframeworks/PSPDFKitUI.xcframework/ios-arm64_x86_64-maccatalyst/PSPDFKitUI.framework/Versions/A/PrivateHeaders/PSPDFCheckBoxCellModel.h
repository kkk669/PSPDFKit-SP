//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFCellModel.h>
#import <PSPDFKitUI/PSPDFSectionModel.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFCheckBoxCellModel;

/// Handles changing the checkboxes on tap.
PSPDF_APP_CLASS_SWIFT(CheckboxSectionModel)
@interface PSPDFCheckboxSectionModel : PSPDFSectionModel

/// The currently active check box cell model.
@property (nonatomic, nullable) PSPDFCheckBoxCellModel *checkBoxModel;

/// All cell models in the section.
@property (nonatomic, nullable, readonly) NSArray<PSPDFCheckBoxCellModel *> *checkBoxCells;

@end

/// Automatically handles checkbox setting within a section.
PSPDF_APP_CLASS_SWIFT(CheckBoxCellModel)
@interface PSPDFCheckBoxCellModel : PSPDFCellModel

/// Determines if the checkbox cell is read only and therefore can't be selected, or if it should be selectable. Defaults to NO.
@property (nonatomic) BOOL readOnly;

@end

NS_ASSUME_NONNULL_END
