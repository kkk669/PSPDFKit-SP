//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFPresentationActions.h>

/// A block that can be used to customize the `popoverPresentationController` before the presentation
/// is happening, to customize some last minute presentation options.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionPopoverPresentationControllerCustomizationBlock;

/// A block of type `(UINavigationController) -> Void` that can be used to
/// customize the implicit navigation controller that was automatically created
/// if `.inNavigationController` or `.closeButton` option was set to `true`.
/// This block will not be called if the presented view controller itself was
/// already a `UINavigationController`.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionNavigationControllerCustomizationBlock;

/// Pass this option to not dismiss the currently presented controller from the
/// target controller, but present the new controller on the fronmost controller.
/// Note: This isn't honored when `PSPDFPresentationOptionReuseNavigationController` is set.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionOverFrontmostViewController;
