//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// Advanced appearance characteristics for a widget annotation.
/// It contains additional information for constructing the annotation’s appearance stream
PSPDF_CLASS_SWIFT(AppearanceCharacteristics)
@interface PSPDFAppearanceCharacteristics : PSPDFModel <PSPDFOverridable>

/// (Optional) A form XObject defining the widget annotation’s normal icon, which shall be displayed
/// when it is not interacting with the user. Only applies to push buttons.
@property (nonatomic, nullable) UIImage *normalIcon;

@end

NS_ASSUME_NONNULL_END
