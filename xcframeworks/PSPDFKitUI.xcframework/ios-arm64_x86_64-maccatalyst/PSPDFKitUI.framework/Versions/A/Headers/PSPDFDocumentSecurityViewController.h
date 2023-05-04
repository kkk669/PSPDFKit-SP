//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFStaticTableViewController.h>
#import <PSPDFKitUI/PSPDFDocumentInfoController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// Document Security and Permissions View Controller.
///
/// Present and allows to edit the PDF Document permissions and passwords.
///
/// @see `PSPDFDocumentSecurityOptions`
PSPDF_CLASS_SWIFT(PDFDocumentSecurityViewController)
@interface PSPDFDocumentSecurityViewController : PSPDFStaticTableViewController <PSPDFDocumentInfoController, PSPDFStyleable, PSPDFOverridable>

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

- (instancetype)initWithStyle:(UITableViewStyle)style PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

/// Whether the user can edit the list. Defaults to `true`.
/// Determines if the controller should allow editing and if the Edit button should be shown.
@property (nonatomic) BOOL allowEditing;

/// An array of custom bar button items to display on the right (or trailing) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *rightActionButtonItems;

/// An array of custom bar button items to display on the left (or leading) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *leftActionButtonItems;

/// Creates a new document security view controller with a document.
///
/// @param document The document whose document provider’s security should be shown.
- (instancetype)initWithDocument:(nullable PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// Creates a new document security view controller from Interface Builder.
- (nullable instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
