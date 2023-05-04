//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFFormElementView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFChoiceFormEditorViewController;

PSPDF_CLASS_SWIFT(ChoiceFormElementView)
@interface PSPDFChoiceFormElementView : PSPDFFormElementView<PSPDFOverridable>

/// Prepares the choice controller and adds an internal reference so keyboard events can be properly forwarded.
- (PSPDFChoiceFormEditorViewController *)prepareChoiceFormEditorController;

@end

NS_ASSUME_NONNULL_END
