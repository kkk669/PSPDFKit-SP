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

/// Cell that shows a switch.
PSPDF_APP_CLASS_SWIFT(SwitchCell)
@interface PSPDFSwitchCell : PSPDFTableViewCell

/// The switch.
@property (nonatomic, readonly) UISwitch *switchView;

/// A block that is called when the switch value changes.
@property (nonatomic, copy, nullable) void (^actionBlock)(UISwitch *theSwitch);

@end

NS_ASSUME_NONNULL_END
