//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSelectableCollectionViewCell.h>
#import <PSPDFKit/PSPDFOverridable.h>

@class PSPDFAnnotationSet;

NS_ASSUME_NONNULL_BEGIN

/// Annotation Set cell, displays an annotation set.
PSPDF_CLASS_SWIFT(AnnotationSetCell)
@interface PSPDFAnnotationSetCell : PSPDFSelectableCollectionViewCell<PSPDFOverridable>

/// The annotation set.
@property (nonatomic, nullable) PSPDFAnnotationSet *annotationSet;

/// Edge insets for the set image.
@property (nonatomic) UIEdgeInsets edgeInsets UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END
