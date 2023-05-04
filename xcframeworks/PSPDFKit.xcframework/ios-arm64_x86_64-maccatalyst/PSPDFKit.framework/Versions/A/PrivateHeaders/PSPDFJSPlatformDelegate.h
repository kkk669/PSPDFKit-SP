//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFJSAlert.h>
#import <PSPDFKit/PSPDFJSButtonImportIcon.h>
#import <PSPDFKit/PSPDFJSMail.h>
#import <PSPDFKit/PSPDFJSPrintParams.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFJavaScriptAPI;

@protocol PSPDFJSPlatformDelegate <NSObject>

- (PSPDFJSAlertResult)showAlert:(PSPDFJavaScriptAPI *)virtualMachine
                     scriptUuid:(NSString *)scriptUuid
                          alert:(PSPDFJSAlert *)alert;

- (void)mailDoc:(PSPDFJavaScriptAPI *)virtualMachine
     scriptUuid:(NSString *)scriptUuid
         params:(PSPDFJSMail *)params;

- (int32_t)getPageNumber:(PSPDFJavaScriptAPI *)virtualMachine
              scriptUuid:(NSString *)scriptUuid;

- (void)setPageNumber:(PSPDFJavaScriptAPI *)virtualMachine
           scriptUuid:(NSString *)scriptUuid
           pageNumber:(int32_t)pageNumber;

- (void)launchUrl:(PSPDFJavaScriptAPI *)virtualMachine
       scriptUuid:(NSString *)scriptUuid
              url:(NSString *)url
         newFrame:(BOOL)newFrame;

- (PSPDFJSButtonImportIconResult)buttonImportIcon:(PSPDFJavaScriptAPI *)virtualMachine
                                       scriptUuid:(NSString *)scriptUuid
                                           params:(PSPDFJSButtonImportIconParams *)params
                                  formElementInfo:(PSPDFJSButtonImportIconFormElementInfo *)formElementInfo;

- (void)printWithParams:(PSPDFJSPrintParams *)params NS_SWIFT_NAME(printWithParams(_:));

@end

NS_ASSUME_NONNULL_END
