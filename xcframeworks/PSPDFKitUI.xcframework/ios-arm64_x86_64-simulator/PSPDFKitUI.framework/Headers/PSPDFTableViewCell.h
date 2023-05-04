//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

/// Base class for table views in PSPDFKit with various helpers.
/// Enabled unlimited lines for textLabel and detailTextLabel.
PSPDF_CLASS_SWIFT(PDFTableViewCell)
@interface PSPDFTableViewCell : UITableViewCell

/// The current context that is associated with this cell. Can be used to uniquely identify a cell.
///
/// @note This property is cleared in `prepareForReuse`.
@property (nonatomic, nullable) id context;

@end

/// Simple subclass that disables animations during `layoutSubviews` if the popover is being resized.
/// This fixes an unexpected animation when the tableView is updated while a popover resizes.
PSPDF_CLASS_SWIFT(NonAnimatingTableViewCell)
@interface PSPDFNonAnimatingTableViewCell : PSPDFTableViewCell
@end

/// Never allows animations during `layoutSubviews`.
PSPDF_CLASS_SWIFT(NeverAnimatingTableViewCell)
@interface PSPDFNeverAnimatingTableViewCell : PSPDFTableViewCell<PSPDFOverridable>
@end
