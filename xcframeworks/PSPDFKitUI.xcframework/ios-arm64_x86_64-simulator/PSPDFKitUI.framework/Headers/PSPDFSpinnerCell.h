//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>

/// Base class that shows centered labels and a spinner label.
PSPDF_CLASS_SWIFT(PDFSpinnerCell)
@interface PSPDFSpinnerCell : PSPDFTableViewCell
@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFSpinnerCell (SubclassingHooks)

/// Spinner that is displayed while search is in progress.
@property (nonatomic, readonly) UIActivityIndicatorView *spinner;

/// Re-align text.
- (void)alignTextLabel;

@end
