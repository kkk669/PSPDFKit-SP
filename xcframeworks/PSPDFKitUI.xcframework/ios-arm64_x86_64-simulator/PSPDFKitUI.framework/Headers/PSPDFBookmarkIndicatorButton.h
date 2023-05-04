//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

/// Indicates the type of image the bookmark indicator button should use.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFBookmarkIndicatorImageType) {
    /// Specifies the large (22pt x 36pt) bookmark image.
    /// Images used are: `bookmark-large-color`, `bookmark-large-shadow`
    PSPDFBookmarkIndicatorImageTypeLarge,

    /// Specifies the medium (11pt x 18pt) bookmark image.
    /// Images used are: `bookmark-medium-color`, `bookmark-medium-shadow`
    PSPDFBookmarkIndicatorImageTypeMedium,

    /// Specifies the small (7pt x 12pt) bookmark image.
    /// Images used are: `bookmark-small-color`, `bookmark-small-shadow`
    PSPDFBookmarkIndicatorImageTypeSmall,
} PSPDF_ENUM_SWIFT(BookmarkIndicatorButton.ImageType);

NS_ASSUME_NONNULL_BEGIN

/// Custom `UIButton` that sets the appropriate bookmark image based on `imageType`, and applies a shadow as well.
/// The image will always have a tint applied to it, based on the `normalTintColor` and `selectedTintColor` properties
/// These colors can be customized using regular `UIAppearance` APIs. To customize the appearance even further, your can use the
/// custom image loading API to change the images.
///
/// @see `PSPDFBookmarkIndicatorImageType`
PSPDF_CLASS_SWIFT(BookmarkIndicatorButton)
@interface PSPDFBookmarkIndicatorButton : UIButton<PSPDFOverridable>

/// Specifies the image type the button should use.
/// Defaults to `PSPDFBookmarkIndicatorImageTypeMedium`.
@property (nonatomic) PSPDFBookmarkIndicatorImageType imageType;

/// Specifies the image's tint color when not selected (bookmarked).
/// Defaults to the system gray.
///
/// @see selectedTintColor
@property (nonatomic, null_resettable) UIColor *normalTintColor UI_APPEARANCE_SELECTOR;

/// Specifies the image's tint color when selected (bookmarked).
/// Defaults to the system red.
///
/// @see normalTintColor
@property (nonatomic, null_resettable) UIColor *selectedTintColor UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END
