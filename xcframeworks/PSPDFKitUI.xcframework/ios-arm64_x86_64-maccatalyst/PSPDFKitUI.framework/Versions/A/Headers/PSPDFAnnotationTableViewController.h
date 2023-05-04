//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFDocumentInfoController.h>
#import <PSPDFKitUI/PSPDFSearchableTableViewController.h>
#import <PSPDFKitUI/PSPDFSegmentImageProviding.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFAnnotation, PSPDFAnnotationTableViewController;

/// Delegate for the `AnnotationTableViewController`.
PSPDF_PROTOCOL_SWIFT(AnnotationTableViewControllerDelegate)
@protocol PSPDFAnnotationTableViewControllerDelegate<NSObject>

/// Will be called when the user touches an annotation cell.
- (void)annotationTableViewController:(PSPDFAnnotationTableViewController *)annotationController didSelectAnnotation:(PSPDFAnnotation *)annotation;

@end

/// Shows an overview of all annotations in the current document.
///
/// @note The toolbar/navigation items are populated in `viewWillAppear:` and can be changed in your subclass.
PSPDF_CLASS_SWIFT(AnnotationTableViewController)
@interface PSPDFAnnotationTableViewController : PSPDFSearchableTableViewController<PSPDFDocumentInfoController, PSPDFSegmentImageProviding, PSPDFStyleable, PSPDFOverridable>

/// The annotation table view delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFAnnotationTableViewControllerDelegate> delegate;

/// Set to filter custom annotations.
/// By default this is nil, which means it uses the `editableAnnotationTypes' value of this class.
/// This set takes strings like `PSPDFAnnotationStringHighlight`, `PSPDFAnnotationStringInk`, ...
///
/// @note If neither is set, all annotations will be visible except link annotations.
@property (nonatomic, copy, nullable) NSSet<PSPDFAnnotationString> *visibleAnnotationTypes;

/// Usually this property should mirror what is set in `PDFConfiguration`.
/// When presented by PSPDFKit, this will be set to `PSPDFConfiguration.editableAnnotationTypes` excluding links.
@property (nonatomic, copy, nullable) NSSet<PSPDFAnnotationString> *editableAnnotationTypes;

/// Whether the user can long press to copy the title. Defaults to `true`.
@property (nonatomic) BOOL allowCopy;

/// Whether the user can edit the list. Defaults to `true`.
@property (nonatomic) BOOL allowEditing;

/// An array of custom bar button items to display on the right (or trailing) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *rightActionButtonItems;

/// An array of custom bar button items to display on the left (or leading) side.
@property (nonatomic, copy) NSArray <UIBarButtonItem *> *leftActionButtonItems;

/// Whether to show a button that lets the user delete all annotations. Defaults to `true`.
///
/// @note This button is hidden if there are no `editableAnnotationTypes` set in the document.
@property (nonatomic) BOOL showDeleteAllOption;

/// Defines if the annotation table view controller allows changing the annotation's z-index by showing a reorder control on the annotation cells in edit mode.
///
/// When presented from within PSPDFKit, this is usually set to `allowAnnotationZIndexMoves` of the used `PDFConfiguration`.
///
/// Defaults to YES.
@property (nonatomic) BOOL allowAnnotationZIndexMoves;

/// Reloads the displayed annotations and updates the internal cache.
- (void)reloadData;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFAnnotationTableViewController (SubclassingHooks)

/// Customize to make more fine-grained changes to the displayed annotation than what would be possible via setting `visibleAnnotationTypes`.
/// The result will be cached internally and only refreshed after `reloadData` is called. (the one on this controller, NOT on the table view).
///
/// @warning this method might be called from a background thread.
- (NSArray<__kindof PSPDFAnnotation *> *)annotationsForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Queries the cache to get the annotation for `indexPath`.
///
/// @param indexPath The index path of the annotation.
/// @param tableView The table view of the annotation. Is either equal to `self.tableView` or it is the table view of the search view controller.
/// @return The annotation that is shown in the passed in table view at the specified index path.
- (nullable PSPDFAnnotation *)annotationForIndexPath:(NSIndexPath *)indexPath inTableView:(UITableView *)tableView;

/// Invoked by the clear all button.
- (IBAction)deleteAllAction:(id)sender;

/// Invoked when the user confirms the deletion of all annotations.
- (void)clearOrDeleteAllAnnotations;

/// Returns a view that wraps the "%tu Annotations" counter.
/// Subclass to customize or return something custom/nil.
@property (nonatomic, readonly, nullable) UIView *viewForTableViewFooter;

/// Update action buttons
- (void)updateBarButtonItems;

@end

NS_ASSUME_NONNULL_END
