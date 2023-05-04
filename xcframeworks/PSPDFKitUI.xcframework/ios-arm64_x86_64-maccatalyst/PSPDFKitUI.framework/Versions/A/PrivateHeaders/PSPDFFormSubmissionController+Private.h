//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFFormSubmissionController.h>
#import <PSPDFKit/PSPDFDocument.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocumentProvider, PSPDFSubmitFormAction;

@interface PSPDFFormSubmissionController ()

/// Creates a new PSPDFFormSubmissionController using the provided document provider, the submit form
/// action, and whether the document should be saved with the given document saving options.
///
/// @param documentProvider Document Provider of the document containing the submit form action.
/// @param action Submit form action to be executed.
/// @param autosaveDocument Whether the document should be saved before executing the submit action.
/// @param saveOptions Document save options to be used to save the document if enabled.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider action:(PSPDFSubmitFormAction *)action autosaveDocument:(BOOL) autosaveDocument saveOptions:(NSDictionary<PSPDFDocumentSaveOption, id> *_Nonnull)saveOptions;

@end

NS_ASSUME_NONNULL_END
