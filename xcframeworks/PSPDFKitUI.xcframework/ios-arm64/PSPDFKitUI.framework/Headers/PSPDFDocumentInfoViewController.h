//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFDocumentInfoController.h>
#import <PSPDFKitUI/PSPDFSegmentImageProviding.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFDocumentInfoViewController;

NS_SWIFT_NAME(PSPDFDocumentInfoViewControllerDelegate)
@protocol PSPDFDocumentInfoViewControllerDelegate

@optional
/// Notifies the delegate that the pending updates have been discarded and the controller is no longer
/// in edit mode.
///
/// @param infoController The `PSPDFDocumentInfoViewController` that cancelled the changes.
- (void)documentInfoViewControllerDidCancelUpdates:(PSPDFDocumentInfoViewController *)infoController;

/// Notifies the delegate that the updates have been applied to the underlying document.
///
/// @param infoController  The `PSPDFDocumentInfoViewController` that applied the changes.
-(void)documentInfoViewControllerDidCommitUpdates:(PSPDFDocumentInfoViewController *)infoController;

@end

/// Document Info View Controller.
///
/// Present and allows to edit the most common PDF Document properties (metadata). Changes are applied to the document automatically.
PSPDF_CLASS_SWIFT(PDFDocumentInfoViewController)
@interface PSPDFDocumentInfoViewController : PSPDFStaticTableViewController <PSPDFDocumentInfoController, PSPDFSegmentImageProviding, PSPDFStyleable, PSPDFOverridable>

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

- (instancetype)initWithStyle:(UITableViewStyle)style PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

/// The delegate reacting to updates of the view controller
@property (nonatomic, weak) id<PSPDFDocumentInfoViewControllerDelegate> delegate;

/// Whether the user can edit the list. Defaults to `true`.
/// Determines if the controller should allow editing and if the Edit button should be shown.
@property (nonatomic) BOOL allowEditing;

/// An array of custom bar button items to display on the right (or trailing) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *rightActionButtonItems;

/// An array of custom bar button items to display on the left (or leading) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *leftActionButtonItems;

/// Creates a new document info view controller with a document.
///
/// @param document The document whose document provider’s metadata should be shown.
- (instancetype)initWithDocument:(nullable PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// Creates a new document info view controller from Interface Builder.
- (nullable instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
