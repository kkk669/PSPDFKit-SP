//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>

NS_ASSUME_NONNULL_BEGIN

/// Table view cell that shows a thumbnail image along with a few text elements.
PSPDF_CLASS_SWIFT(ThumbnailTextCell)
@interface PSPDFThumbnailTextCell : PSPDFNonAnimatingTableViewCell

/// Text field that is shown on top of the cell. Can be used for displaying a title.
/// Non-editable by default.
@property (nonatomic, readonly) UITextField *textField;

/// Label that is shown below the text field. Uses a secondary text color.
@property (nonatomic, readonly) UILabel *detailLabel;

/// Label that is shown next to the text field, on the trailing side of the cell.
@property (nonatomic, readonly) UILabel *adornmentLabel;

/// Image view that will be shown next to the text field and the detail label on the leading edge of the cell.
///
/// @note The cell observes the image value of this property, and applies stylistic changes based upon its value.
/// If the image is set, the image view shows a border around the image and adds shadow behind it.
/// If no image is not set the border and the shadow are removed.
@property (nonatomic, readonly) UIImageView *pageImageView;

/// :nodoc:
@property (nonatomic, readonly, nullable) UIImageView *imageView NS_UNAVAILABLE;

/// :nodoc:
@property (nonatomic, readonly, nullable) UILabel *textLabel NS_UNAVAILABLE;

/// :nodoc:
@property (nonatomic, readonly, nullable) UILabel *detailTextLabel NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
