//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

/// `UITableViewCell` subclass representing a document.
/// Used in `PSPDFDocumentPickerController`.
PSPDF_CLASS_SWIFT(PDFDocumentPickerCell)
@interface PSPDFDocumentPickerCell : PSPDFTableViewCell

/// Configure a new cell.
- (void)configureWithDocument:(PSPDFDocument *)document useDocumentTitle:(BOOL)useDocumentTitle detailText:(nullable NSAttributedString *)detailText pageIndex:(PSPDFPageIndex)pageIndex previewImage:(UIImage *)previewImage;

/// Associated document with the cell. Used to get the document title.
@property (nonatomic, weak) PSPDFDocument *document;

/// Associated `pageIndex` of the document.
/// Usually `0`.
@property (nonatomic) PSPDFPageIndex pageIndex;

/// Page preview image.
@property (nonatomic, nullable) UIImage *pagePreviewImage;

/// Set a new page preview image.
- (void)setPagePreviewImage:(nullable UIImage *)pagePreviewImage animated:(BOOL)animated;

/// Image view used for displaying the page preview image.
@property (nonatomic) UIImageView *pageImageView;

/// Label used for displaying the document title.
@property (nonatomic) UILabel *titleLabel;

/// Label used for displaying an optional detail text.
@property (nonatomic) UILabel *detailLabel;

/// :nodoc:
@property (nonatomic, readonly, nullable) UIImageView *imageView NS_UNAVAILABLE;
/// :nodoc:
@property (nonatomic, readonly, nullable) UILabel *textLabel NS_UNAVAILABLE;
/// :nodoc:
@property (nonatomic, readonly, nullable) UILabel *detailTextLabel NS_UNAVAILABLE;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFDocumentPickerCell (SubclassingHooks)

/// Font used for the title label. Defaults to `UIFontTextStyleSubheadline`.
+ (UIFont *)titleLabelFont;

/// Font used for the detail label. Default to `UIFontTextStyleFootnote`.
+ (UIFont *)detailLabelFont;

@end

NS_ASSUME_NONNULL_END
