//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// UITextField subclass with some additional helpers.
PSPDF_APP_CLASS_SWIFT(PDFTextField)
@interface PSPDFTextField : UITextField 

/// Preselects the current text using the marked appearance. The selection is automatically replaced
/// if the user starts typing. The marked region is cleared if the user instead long presses.
- (void)markCurrentTextAsPlaceholder;

/// Clear the marked text selection and cleanup all of the setup triggers for unmarking.
- (void)unmarkPlaceholderText;

@end

NS_ASSUME_NONNULL_END
