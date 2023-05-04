//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFJSPlatformDelegateAdapter, PSPDFFormElement;

@interface PSPDFDocumentProvider (JavascriptAdditions)

- (void)configureDocumentScriptExecutor:(nullable NSString *)initPath;

/// Configures a platform delegate for JavaScript. A platform delegate is an interface that implements part of the
/// Adobe JavaScript API for things like sending an email, printing a document, or showing an alert message.
- (void)configureJavaScriptPlatformDelegate:(PSPDFJSPlatformDelegateAdapter *)platformDelegate;

/// Executes all calculate actions in the document that depend on the `sourceForm` value.
/// For performance reasons, this method isn't automatically executed on creation time. If you need up-to-date form values
/// be sure to call this method at least once (passing `nil` as the `sourceForm`) before accessing the form values.
/// `PDFViewController` will do this for you automatically, if you are displaying the document.
///
/// @note Executes synchronously. Use with caution for complex actions, as it blocks the main thread. (Must be run on main thread).
/// @return YES if successful.
- (BOOL)updateCalculatedFieldsDependingOnForm:(nullable PSPDFFormElement *)sourceForm error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
