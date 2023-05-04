//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentEditorConfiguration.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>

@class PSPDFNewPageViewController, PSPDFNewPageConfiguration;

NS_ASSUME_NONNULL_BEGIN

/// Delegate that allows connecting a `PSPDFNewPageViewController` to
/// receive the event when a selection has been chosen.
PSPDF_PROTOCOL_SWIFT(PDFNewPageViewControllerDelegate)
@protocol PSPDFNewPageViewControllerDelegate<NSObject>

/// Called when the selection process completes (i.e., the commit button is pressed).
/// The delegate should dismiss the view controller at this point.
/// New page action should be ignored if `configuration` is `nil`.
///
/// @param controller      The `PSPDFNewPageViewController` instance.
/// @param configuration   The configuration with which the new page(s) should be created.
/// @param pageCount       The number of pages that should be created with the configuration.
- (void)newPageController:(PSPDFNewPageViewController *)controller didFinishSelectingConfiguration:(nullable PSPDFNewPageConfiguration *)configuration pageCount:(PSPDFPageCount)pageCount;

@end

PSPDF_PROTOCOL_SWIFT(PDFNewPageViewControllerDataSource)
@protocol PSPDFNewPageViewControllerDataSource<NSObject>

@optional
/// Optional method. Called when the new page view controller is being configured.
///
/// The return value of this method's implementation is used to determine the correct
/// title for the "Add page" button on the `PSPDFNewPageViewController` instance.
///
/// @param controller  The controller that's calling this method.
///
/// @return Integer with the index of the first item that's selected and will serve as insertion point reference. If no index is selected, return `NSNotFound`. If this method is not implemented, `NSNotFound` is used.
- (PSPDFPageIndex)selectedIndexForNewPageViewController:(PSPDFNewPageViewController *)controller;

@end

/// Manages new selection of various configuration options for new PDF pages. Builds the user interface
/// based on the passed in `configuration` object.
///
/// @note This class requires the Document Editor component to be enabled for your license.
PSPDF_CLASS_SWIFT(PDFNewPageViewController)
@interface PSPDFNewPageViewController : PSPDFStaticTableViewController<PSPDFDocumentEditorConfigurationConfigurable, PSPDFOverridable>

PSPDF_DEFAULT_TABLEVIEWCONTROLLER_INIT_UNAVAILABLE

/// Initializes the controller with a configuration library.
- (instancetype)initWithDocumentEditorConfiguration:(PSPDFDocumentEditorConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

/// Receives notifications about the new page view controller state.
@property (nonatomic, weak) id<PSPDFNewPageViewControllerDelegate> delegate;

/// Provides the new page view controller with information for UI customization.
@property (nonatomic, weak) id<PSPDFNewPageViewControllerDataSource> dataSource;

/// Makes the view controller ask it's data source for information again.
- (void)reloadData;

@end

NS_ASSUME_NONNULL_END
