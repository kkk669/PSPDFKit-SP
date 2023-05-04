//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBaseViewController.h>

@class PSPDFRedactionViewController, PSPDFDocument, PSPDFDirectory;

NS_ASSUME_NONNULL_BEGIN

/// Delegate for the redaction view controller.
@protocol PSPDFRedactionViewControllerDelegate <NSObject>

/// Called when the redaction view controller applied redactions.
- (void)redactionViewController:(PSPDFRedactionViewController *)redactionViewController didApplyRedactionsToDocument:(PSPDFDocument *)document;

@end

/// Screen that informs the user about uncommitted redactions in the document.
/// Contains buttons, used to commit the redactions, either in the current file or in a new file,
/// and a preview switch to render the redactions in their redacted state.
///
/// Requires the Redaction license component.
PSPDF_APP_CLASS_SWIFT(RedactionViewController)
@interface PSPDFRedactionViewController : PSPDFBaseViewController<PSPDFOverridable>

/// Creates a new redaction view controller with a given document.
- (instancetype)initWithDocument:(PSPDFDocument *)document;

/// Document that is used as the source for previewing and applying redactions on.
@property (nonatomic, readonly) PSPDFDocument *document;

/// Delegate for callback when redactions have been applied.
@property (nonatomic, weak) id<PSPDFRedactionViewControllerDelegate> delegate;

/// Save directories to choose, if any. If none set, the "Apply As..." feature will be disabled.
///
/// Defaults to `[Directory.documentPickerDirectory]`.
///
/// @note: Must be set before the view is loaded to be effective.
@property (nonatomic, copy) NSArray<PSPDFDirectory *> *saveDirectories;

@end

NS_ASSUME_NONNULL_END
