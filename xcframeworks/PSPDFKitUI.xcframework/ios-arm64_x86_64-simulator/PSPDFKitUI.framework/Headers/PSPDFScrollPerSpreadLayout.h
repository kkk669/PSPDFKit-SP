//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFStackViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

/// The content scale describes how each spread lays out its content.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFScrollPerSpreadLayoutContentScale) {
    /// Aspect fit results in a spread view having all its pages always visible on
    /// screen. Pages are shown in a size so that everything fits the view.
    PSPDFScrollPerSpreadLayoutContentScaleAspectFit = 0,
    /// Aspect fill width means that the content uses the full width of the view even
    /// if that means that the height of the spread is larger than the view. The user
    /// then needs to scroll to view the full spread.
    PSPDFScrollPerSpreadLayoutContentScaleAspectFillWidth,
    /// Aspect fill height means that the content uses the full height of the view
    /// even if that means that the width of the spread is larger than the view. The
    /// user then needs to scroll to view the full spread.
    PSPDFScrollPerSpreadLayoutContentScaleAspectFillHeight,
} PSPDF_ENUM_SWIFT(ScrollPerSpreadLayout.ContentScale);

PSPDF_CLASS_SWIFT(ScrollPerSpreadLayout)
@interface PSPDFScrollPerSpreadLayout : PSPDFStackViewLayout

/// The content scale for spreads in the layout. Defaults to `PSPDFScrollPerSpreadLayoutContentScaleAspectFit`.
@property (nonatomic) PSPDFScrollPerSpreadLayoutContentScale contentScale;

@end

NS_ASSUME_NONNULL_END
