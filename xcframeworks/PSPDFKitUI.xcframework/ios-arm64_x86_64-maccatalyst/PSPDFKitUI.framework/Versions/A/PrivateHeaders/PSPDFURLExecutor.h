//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFApplicationPolicy.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFileManager.h>
#import <PSPDFKitUI/PSPDFApplication.h>
#import <PSPDFKitUI/PSPDFControlDelegate.h>
#import <PSPDFKitUI/PSPDFExternalURLHandler.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFURLAction, PSPDFURLExecutor;

@protocol PSPDFURLExecutorDelegate <NSObject, PSPDFExternalURLHandler>
/*
 We have some delegate methods here that are also present in other protocols. `handleError` is
 declared in `PSPDFErrorHandler.h` and `presentPreviewControllerForURL` is declared in `PSPDFViewController.h`
 and `PSPDFControlDelegate.h`. Tried untangling by moving the `PSPDFURLExecutorDelegate` into
 `PSPDFControlDelegate.h` (and removing the duplicated methods in the 2 files) and removing the
 `PSPDFErrorHandler.h` in favor of this one, but since they are all public this would lead to a lot of public
 API changes which currently isn't worth it.
*/

/// If the executor finds an URL, you can decide the behavior. Default is `PSPDFLinkActionInlineBrowser` if not implemented.
- (PSPDFLinkAction)urlExecutor:(PSPDFURLExecutor *)urlExecutor linkActionForAction:(PSPDFURLAction *)URLAction;

@optional

/// Allows file preview using QuickLook. Will call `presentPDFViewControllerWithDocument:` if the pdf filetype is detected.
///
/// @see PSPDFPresentationActions.h for compatible keys for `options`.
- (void)presentPreviewControllerForURL:(NSURL *)fileURL title:(nullable NSString *)title options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated completion:(nullable void (^)(void))completion;

- (void)handleError:(nullable NSError *)error title:(nullable NSString *)title message:(nullable NSString *)message;

@end

PSPDF_TEST_CLASS_SWIFT(URLExecutor)
@interface PSPDFURLExecutor : NSObject

@property (nonatomic, weak) UIViewController<PSPDFPresentationActions> *sourceViewController;

@property (nonatomic) id<PSPDFApplication> application;
@property (nonatomic) id<PSPDFFileManager> fileManager;
@property (nonatomic) id<PSPDFApplicationPolicy> policy;

@property (nonatomic, weak) id<PSPDFURLExecutorDelegate> delegate;

- (BOOL)executeURLAction:(PSPDFURLAction *)URLAction targetRect:(CGRect)targetRect actionContainer:(nullable id)actionContainer animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
