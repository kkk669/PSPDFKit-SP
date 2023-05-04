//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFExternalURLHandler.h>
#import <PSPDFKitUI/PSPDFStyleable.h>
#import <WebKit/WebKit.h>

@class PSPDFViewController, PSPDFWebViewController;

NS_ASSUME_NONNULL_BEGIN

/// Delegate for the `PSPDFWebViewController` to customize URL handling.
PSPDF_PROTOCOL_SWIFT(WebViewControllerDelegate)
@protocol PSPDFWebViewControllerDelegate<PSPDFExternalURLHandler>

@optional

/// Called when the web controller did start loading.
- (void)webViewControllerDidStartLoad:(PSPDFWebViewController *)controller;

/// Called when the web controller did finish loading.
- (void)webViewControllerDidFinishLoad:(PSPDFWebViewController *)controller;

/// Called when the web controller did fail to load.
- (void)webViewController:(PSPDFWebViewController *)controller didFailLoadWithError:(NSError *)error;

@end

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFWebViewControllerAvailableActions) {
    PSPDFWebViewControllerAvailableActionsNone = 0,
    PSPDFWebViewControllerAvailableActionsOpenInSafari = 1 << 0,
    PSPDFWebViewControllerAvailableActionsMailLink = 1 << 1,
    PSPDFWebViewControllerAvailableActionsCopyLink = 1 << 2,
    PSPDFWebViewControllerAvailableActionsPrint = 1 << 3,
    PSPDFWebViewControllerAvailableActionsStopReload = 1 << 4,
    PSPDFWebViewControllerAvailableActionsBack = 1 << 5,
    PSPDFWebViewControllerAvailableActionsForward = 1 << 6,
    PSPDFWebViewControllerAvailableActionsFacebook = 1 << 7,
    PSPDFWebViewControllerAvailableActionsTwitter = 1 << 8,
    PSPDFWebViewControllerAvailableActionsMessage = 1 << 9,

    /// Only offered if Google Chrome is actually installed.
    PSPDFWebViewControllerAvailableActionsOpenInChrome = 1 << 10,
    PSPDFWebViewControllerAvailableActionsAll = 0xFFFFFF,
} PSPDF_ENUM_SWIFT(WebViewControllerAvailableActions);

PSPDF_EXPORT NSNotificationName const PSPDFWebViewControllerDidStartLoadingNotification;
PSPDF_EXPORT NSNotificationName const PSPDFWebViewControllerDidFinishLoadingNotification;
PSPDF_EXPORT NSNotificationName const PSPDFWebViewControllerDidFailToLoadNotification;

/// Inline Web Browser.
PSPDF_CLASS_SWIFT(WebViewController)
@interface PSPDFWebViewController : PSPDFBaseViewController<PSPDFStyleable, PSPDFOverridable>

/// Use this to get a `UINavigationController` with a done-button.
+ (UINavigationController *)modalWebViewWithURL:(NSURL *)URL;

/// Creates a new `PSPDFWebViewController` with the specified custom URL request.
- (instancetype)initWithURLRequest:(NSURLRequest *)request;

/// Creates a new `PSPDFWebViewController` with the specified URL.
- (instancetype)initWithURL:(NSURL *)URL;

/// Controls the available actions under the more icon.
/// Defaults to `PSPDFWebViewControllerAvailableActionsAll&~PSPDFWebViewControllerAvailableActionsStopReload` on iPad and
/// `PSPDFWebViewControllerAvailableActionsAll` on iPhone (but with conditionally visible toolbars).
@property (nonatomic) PSPDFWebViewControllerAvailableActions availableActions;

/// Associated delegate, connects to the `PDFViewController`.
@property (nonatomic, weak) IBOutlet id<PSPDFWebViewControllerDelegate> delegate;

/// Accesses the  `WKWebView` directly.
@property (nonatomic, readonly) WKWebView *webView;

/// If enabled, shows a progress indicator much like Safari. Defaults to YES.
/// Set this before the view is loaded.
@property (nonatomic) BOOL showProgressIndicator;

/// If set to YES, a custom HTML is loaded when the `WKWebView` encounters an error (like 404).
/// Defaults to YES.
@property (nonatomic) BOOL useCustomErrorPage;

/// If set to yes, we will evaluate `document.title` from the web content and update the title.
/// Defaults to YES.
@property (nonatomic) BOOL shouldUpdateTitleFromWebContent;

/// The excluded activities.
/// Defaults to `@[UIActivityTypePostToWeibo, UIActivityTypePostToTencentWeibo, UIActivityTypeSaveToCameraRoll]`.
@property (nonatomic, copy) NSArray<NSString *> *excludedActivities;

/// A Boolean value indicating whether the web view suppresses content rendering until it is fully
/// loaded into memory. Defaults to `false`.
@property (nonatomic) BOOL suppressesIncrementalRendering;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFWebViewController (SubclassingHooks)

/// Called on error events if `useCustomErrorPage` is set.
///
/// Loads the contents of  `standard-error.html` from inside `PSPDFKit.bundle`.
- (void)showHTMLWithError:(NSError *)error;

/// This is your chance to modify the settings on the activity controller before it's displayed.
///
/// @return null if the URL is not set.
@property (nonatomic, readonly, nullable) UIActivityViewController *createDefaultActivityViewController;

/// Go back in history.
- (void)goBack:(nullable id)sender;

/// Go forward in history.
- (void)goForward:(nullable id)sender;

/// Reload page.
- (void)reload:(nullable id)sender;

/// Stop page loading.
- (void)stop:(nullable id)sender;

/// Show activity view controller.
- (void)action:(nullable UIBarButtonItem *)sender;

/// Dismiss PSPDFWebViewController.
- (void)done:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
