//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFColorPicker.h>
#import <PSPDFKitUI/PSPDFSimplePageViewController.h>

/// @note Starting with iOS 14 PSPDFKit's default UI will display the system color picker
/// (`UIColorPickerViewController`) where possible. On macOS Big Sur and later the system
/// color picker will also be used for select options (e.g. the highlight annotation menu).
/// Customizing this API will have no effect on the system color picker.
@interface PSPDFColorPickerPageViewController : PSPDFSimplePageViewController <PSPDFColorPicker>

/// Initializes the page view controller with a list of color pickers and configures
/// the color pickers so that the receiver forwards color changes inside the pickers
/// to its own `colorPickerDelegate`.
///
/// @param viewControllers An array of color pickers.
- (instancetype)initWithColorPickerViewControllers:(NSArray<UIViewController<PSPDFColorPicker> *> *)viewControllers NS_DESIGNATED_INITIALIZER;

@end
