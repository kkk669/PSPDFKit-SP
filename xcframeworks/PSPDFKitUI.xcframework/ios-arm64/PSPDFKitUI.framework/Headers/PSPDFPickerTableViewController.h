//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// The list controller can check models to build a selectable list.
PSPDF_CLASS_SWIFT(PickerTableViewController)
@interface PSPDFPickerTableViewController : PSPDFStaticTableViewController<PSPDFOverridable>

@end

NS_ASSUME_NONNULL_END
