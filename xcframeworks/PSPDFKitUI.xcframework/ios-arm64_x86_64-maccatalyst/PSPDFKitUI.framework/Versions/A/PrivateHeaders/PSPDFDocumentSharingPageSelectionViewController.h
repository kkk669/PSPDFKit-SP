//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFStaticTableViewController.h>

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFStyleable.h>
#import <PSPDFKitUI/PSPDFDocumentSharingPageSelectionDataSource.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocumentSharingPageSelectionViewController;

NS_SWIFT_NAME(PDFDocumentSharingPageSelectionViewControllerDelegate)
@protocol PSPDFDocumentSharingPageSelectionViewControllerDelegate <NSObject>

/// Called when the user updates the selection for which page range to share.
///
/// @note this may be called multiple times during the presentation of the view controller.
///
/// @param viewController  The view controller that is visible on screen.
/// @param pageOptions     The new options selected.
/// @param selectedRange   The explicit page range the user picked in the UI. If one of the dynamic options were selected, the passed value will be `(NSNotFound, 0).
- (void)documentSharingPageSelectionViewController:(PSPDFDocumentSharingPageSelectionViewController *)viewController didUpdateOptionSelection:(PSPDFDocumentSharingPagesOptions)pageOptions selectedPageRange:(NSRange)selectedRange;

@end

/// Displays a selection for available page ranges.
///
/// This view controller does not keep track of state.
PSPDF_TEST_CLASS_SWIFT(PDFDocumentSharingPageSelectionViewController)
@interface PSPDFDocumentSharingPageSelectionViewController : PSPDFStaticTableViewController<PSPDFStyleable>

PSPDF_DEFAULT_TABLEVIEWCONTROLLER_INIT_UNAVAILABLE

/// Initialize with a `pageRangeSelection` that this controller should operate on and the current sharing context.
- (instancetype)initWithPageSelectionDataSource:(PSPDFDocumentSharingPageSelectionDataSource *)dataSource delegate:(id<PSPDFDocumentSharingPageSelectionViewControllerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
