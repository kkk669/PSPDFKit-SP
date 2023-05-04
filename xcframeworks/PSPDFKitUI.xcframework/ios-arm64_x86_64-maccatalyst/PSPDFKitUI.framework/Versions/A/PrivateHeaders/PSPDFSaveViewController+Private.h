//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSaveViewController.h>

@interface PSPDFSaveViewController()

/// Conforming callers can skip this view controller and instead show the system document picker directly.
///
/// This requires that saveDirectories contains an array with `[Directory.documentPickerDirectory]` and no other options.
/// Static property. Defaults to YES.
/// Private until customers ask for it.
@property (nonatomic, class) BOOL showSystemPickerDirectly;

/// This call is used to keep logic on the save controller but display the system document picker directly.
/// Lifetime is bound to the document picker and delegates are called as usual.
- (void)showDocumentPickerOnViewController:(UIViewController *)viewController;

/// Tests if we should use the direct document picker logic.
- (BOOL)shouldShowSystemPickerDirectly;

@end
