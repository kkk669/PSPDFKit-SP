//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFTextFieldFormElement.h>

@class PSPDFCoreAnnotation;
@class PSPDFJSResult;
@protocol PSPDFJSPlatformDelegate;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFTextFieldFormElement ()

// Designated initializer.
- (instancetype)initWithCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation formField:(PSPDFFormField *)formField documentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Handles Keystroke, Validate and Calculate actions that follow from user text input automatically.
/// `isFinal` defines if the user is typing (NO) or if the string should be committed (YES).
/// The change is the change in text.
/// Returns a result with the new text contents (possibly different from the passed change), or with an `NSError` is something went wrong.
- (PSPDFJSResult *)textFieldChangedWithContents:(NSString *)contents change:(NSString *)change range:(NSRange)range isFinal:(BOOL)isFinal platformDelegate:(nullable id<PSPDFJSPlatformDelegate>)platformDelegate;

/// Executes the formatting script of this text field form element, if JavaScript is enabled and configured.
- (void)runFormattingScript;

/// Returns the editing contents of this text field. The editing contents of a form field may be different from the form field contents because of a JavaScript script.
@property (atomic, readonly, nullable) NSString *editingContents;

@end

NS_ASSUME_NONNULL_END
