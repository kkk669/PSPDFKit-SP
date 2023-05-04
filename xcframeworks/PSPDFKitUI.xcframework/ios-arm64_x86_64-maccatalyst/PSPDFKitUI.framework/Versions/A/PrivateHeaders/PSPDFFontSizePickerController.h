//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseTableViewController.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFFontSizePickerController;

/// Delegate for `PSPDFFontSizePickerController`, calls back when a font size is selected.
NS_SWIFT_NAME(FontSizePickerControllerDelegate)
@protocol PSPDFFontSizePickerControllerDelegate<NSObject>

/// Called whenever a font size selection is made.
- (void)fontSizePickerController:(PSPDFFontSizePickerController *)controller didSelectFontSize:(CGFloat)fontSize;

@end

/// Font size picker. Allows quick font size changes.
NS_SWIFT_NAME(FontSizePickerController)
@interface PSPDFFontSizePickerController : PSPDFBaseTableViewController

/// An array of integer values for the desired font sizes.
/// Provides a list of common font sizes by default.
@property (nonatomic, copy) NSArray<NSNumber *> *fontSizes;

/// The font size picker delegate - notifies when a font size is selected.
@property (nonatomic, weak) IBOutlet id<PSPDFFontSizePickerControllerDelegate, PSPDFOverrideProvider> delegate;

/// Creates displayable attributed strings with a small "pt" suffix for the specified font size.
/// - Parameters:
///   - fontSize: Font size value that should be in the attributed string.
///   - color: Base color the attributed string should have as text color. "pt" will use this value with 0.6 alpha.
///   - traitCollection: Used to make the returned string use a fixed size based on the content size category. `nil` if the string should support Dynamic Type.
+ (NSAttributedString *)fontSizeStringForFontSize:(CGFloat)fontSize color:(UIColor *)color traitCollection:(nullable UITraitCollection *)traitCollection;

/// Creates displayable attributed strings with a small "pt" suffix for the specified font size.
/// - Parameters:
///   - sizeString: String that should represent the font size in the attributed string.
///   - color: Base color the attributed string should have as text color. "pt" will use this value with 0.6 alpha.
///   - traitCollection: Used to make the returned string use a fixed size based on the content size category. `nil` if the string should support Dynamic Type.
+ (NSAttributedString *)fontSizeStringForSizeString:(NSString *)sizeString color:(UIColor *)color traitCollection:(nullable UITraitCollection *)traitCollection;

@end

NS_ASSUME_NONNULL_END
