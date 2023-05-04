//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFPageCell.h>
#import <PSPDFKitUI/PSPDFRoundedLabel.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

/// The thumbnail cell classed used for the thumbnail grid and thumbnail scroll bar.
///
/// @note To modify the selection/highlight state, customize `selectedBackgroundView`.
PSPDF_CLASS_SWIFT(ThumbnailGridViewCell)
@interface PSPDFThumbnailGridViewCell : PSPDFPageCell<PSPDFOverridable>

/// Referenced document.
@property (nonatomic, nullable) PSPDFDocument *document;

/// Bookmark ribbon image color. Defaults to red.
@property (nonatomic, nullable) UIColor *bookmarkImageColor UI_APPEARANCE_SELECTOR;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFThumbnailGridViewCell (SubclassingHooks)

/// May be used to update the bookmark image.
@property (nonatomic, readonly, nullable) UIImageView *bookmarkImageView;

/// Update bookmark image frame and image visibility.
- (void)updateBookmarkImage;

@end

NS_ASSUME_NONNULL_END
