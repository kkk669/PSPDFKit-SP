//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFJavaScriptAction.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFJSPlatformDelegate;
@class PSPDFJavaScriptActionEvent, PSPDFDocumentProvider;

@interface PSPDFJavaScriptAction ()

/// Tries to execute the JavaScript in the context of a document provider.
/// Returns the action event, with possible modifications performed by the script.
- (nullable PSPDFJavaScriptActionEvent *)executeScriptAppliedToDocumentProvider:(PSPDFDocumentProvider *)documentProvider platformDelegate:(nullable id<PSPDFJSPlatformDelegate>)platformDelegate sender:(nullable id)sender error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
