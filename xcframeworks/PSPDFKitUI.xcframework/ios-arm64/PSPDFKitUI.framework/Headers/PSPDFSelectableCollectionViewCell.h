//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSelectableCollectionViewCellStyle) {
    PSPDFSelectableCollectionViewCellStyleNone,
    PSPDFSelectableCollectionViewCellStyleCheckmark,
    PSPDFSelectableCollectionViewCellStyleBorder,
    PSPDFSelectableCollectionViewCellStyleDimmedBackgroundWithCheckmark,
} PSPDF_ENUM_SWIFT(SelectableCollectionViewCellStyle);

/// Cell that shows a selection status.
PSPDF_CLASS_SWIFT(SelectableCollectionViewCell)
@interface PSPDFSelectableCollectionViewCell : UICollectionViewCell

/// Shows overlay when selected. Defaults to `PSPDFSelectableCollectionViewCellStyleCheckmark`.
@property (nonatomic) PSPDFSelectableCollectionViewCellStyle selectableCellStyle;

/// Allows setting a custom selection tint color. Only relevant for `PSPDFSelectableCollectionViewCellStyleBorder`.
@property (nonatomic, nullable) UIColor *selectableCellColor UI_APPEARANCE_SELECTOR;

@end
