//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>

#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// This cell enforces the value1 table view cell style by overriding the designated initializer.
///
/// @note you are no longer able to set a custom table view cell style when instantiating this cell yourself!
PSPDF_APP_CLASS_SWIFT(Value1TableViewCell)
@interface PSPDFValue1TableViewCell : PSPDFTableViewCell

@end

NS_ASSUME_NONNULL_END
