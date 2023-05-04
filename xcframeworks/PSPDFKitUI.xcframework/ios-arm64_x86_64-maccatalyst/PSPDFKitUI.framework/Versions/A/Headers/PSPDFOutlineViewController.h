//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFDocumentInfoController.h>
#import <PSPDFKitUI/PSPDFOutlineCell.h>
#import <PSPDFKitUI/PSPDFSearchableTableViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFOutlineViewController, PSPDFOutlineElement;

/// Delegate for the `OutlineViewController`.
PSPDF_PROTOCOL_SWIFT(OutlineViewControllerDelegate)
@protocol PSPDFOutlineViewControllerDelegate<NSObject>

/// Called when a outline element cell is tapped.
///
/// @param outlineController Corresponding `OutlineViewController`.
/// @param outlineElement Tapped outline element.
/// @return Return `false` if no action was executed, which will then call `outlineCellDidTapDisclosureButton:` if the element is expandable. Return `true` if an action was executed and no further methods should be called.
- (BOOL)outlineController:(PSPDFOutlineViewController *)outlineController didTapAtElement:(PSPDFOutlineElement *)outlineElement;

@end

/// Outline (Table of Contents) view controller.
PSPDF_CLASS_SWIFT(OutlineViewController)
@interface PSPDFOutlineViewController : PSPDFSearchableTableViewController<PSPDFDocumentInfoController, UISearchDisplayDelegate, PSPDFStyleable, PSPDFOverridable>

/// Delegate to react when taps are made on outline elements.
@property (nonatomic, weak) IBOutlet id<PSPDFOutlineViewControllerDelegate> delegate;

/// Whether the user can long press to copy the title. Defaults to `true`.
@property (nonatomic) BOOL allowCopy;

/// Enables displaying page labels. Defaults to `true`.
@property (nonatomic) BOOL showPageLabels;

/// How many lines of text should be displayed for each cell. Defaults to 4. Set to 0 for unlimited lines.
@property (nonatomic) NSUInteger maximumNumberOfLines;

/// Left intent width. Defaults to 5.0.
@property (nonatomic) CGFloat outlineIndentLeftOffset;

 /// Intent multiplier (will be added x times the intent level). Defaults to 10.0.
@property (nonatomic) CGFloat outlineIndentMultiplier;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFOutlineViewController (SubclassingHooks) <PSPDFOutlineCellDelegate>

/// Outline elements with child elements can also contain a PDF action.
/// Elements with an assigned action will trigger the action. Elements without an assigned action will
/// just expand/collapse the element. This duality can create a confusing user experience.
///
/// Ideally this is controlled at the PDF authoring stage, however you can also permanently disable invoking actions
/// on non-leave nodes by overriding this method and returning `true`.
///
/// The default implementation of this method returns `false` which is the standard compliant PDF spec behavior.
@property (nonatomic, readonly) BOOL shouldExpandCollapseOnRowSelection;

/// Cell delegate - expand/shrink content.
- (void)outlineCellDidTapDisclosureButton:(PSPDFOutlineCell *)cell;

/// The search controller used to search the outline.
@property (nonatomic, readonly) UISearchController *searchController;

@end

NS_ASSUME_NONNULL_END
