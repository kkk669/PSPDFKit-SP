//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFStaticTableViewController.h>

@class PSPDFApplePencilManager, PSPDFApplePencilController;

NS_ASSUME_NONNULL_BEGIN

/// Allows the user to enable and disable the Apple Pencil.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ApplePencilController)
@interface PSPDFApplePencilController : PSPDFStaticTableViewController

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates an instance of an `PSPDFApplePencilController` taking the passed in `PSPDFApplePencilManager` instance as source for its configuration.
- (instancetype)initWithApplePencilManager:(PSPDFApplePencilManager *)applePencilManager NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
