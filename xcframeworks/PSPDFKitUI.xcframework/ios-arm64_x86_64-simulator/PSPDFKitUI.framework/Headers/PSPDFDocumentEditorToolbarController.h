//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentEditor.h>
#import <PSPDFKit/PSPDFMacros.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarContainer.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarController.h>
#import <PSPDFKitUI/PSPDFNewPageViewController.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>
#import <PSPDFKitUI/PSPDFSaveViewController.h>

@class PSPDFDocumentEditorToolbar, PSPDFDocumentEditorToolbarController;
@protocol PSPDFPresentationContext;

NS_ASSUME_NONNULL_BEGIN

/// Fired whenever the toolbar visibility changes.
PSPDF_EXPORT NSNotificationName const PSPDFDocumentEditorToolbarControllerVisibilityDidChangeNotification;

/// Key inside the notification's userInfo.
PSPDF_EXPORT NSString *const PSPDFDocumentEditorToolbarControllerVisibilityAnimatedKey;

/// The delegate of `PDFDocumentEditorToolbarController`.
PSPDF_PROTOCOL_SWIFT(PDFDocumentEditorToolbarControllerDelegate)
@protocol PSPDFDocumentEditorToolbarControllerDelegate<PSPDFFlexibleToolbarContainerDelegate>

/// Tells the delegate that the set of selected pages changes as a result of
/// using one of the toolbar buttons.
///
/// The delegate should implement this method to update its state and UI for the
/// new selection.
///
/// @note This method is not called when the set of selected pages changes
/// programmatically or as a result of selecting individual pages one-by-one.
///
/// @param controller The calling toolbar controller.
/// @param pages The new set of selected pages.
- (void)documentEditorToolbarController:(PSPDFDocumentEditorToolbarController *)controller didSelectPages:(NSIndexSet *)pages;

@optional

/// Asks the delegate for the page index at which a new page should be inserted.
///
/// If the delegate does not implement this method, `0` is assumed.
///
/// @param controller The calling toolbar controller.
/// @param configuration The configuration of the new page being inserted.
///
/// @returns The page index at which the new page should be inserted.
- (PSPDFPageIndex)documentEditorToolbarController:(PSPDFDocumentEditorToolbarController *)controller indexForNewPageWithConfiguration:(PSPDFNewPageConfiguration *)configuration;

@end

/// Manages the document editor toolbar state and presents various document editing controllers.
///
/// @note This class requires the Document Editor component to be enabled for your license.
PSPDF_CLASS_SWIFT(PDFDocumentEditorToolbarController)
@interface PSPDFDocumentEditorToolbarController : PSPDFFlexibleToolbarController<PSPDFDocumentEditorDelegate, PSPDFNewPageViewControllerDelegate, PSPDFNewPageViewControllerDataSource, PSPDFSaveViewControllerDelegate, PSPDFOverridable>

/// Initialize with a document editor toolbar.
- (instancetype)initWithDocumentEditorToolbar:(PSPDFDocumentEditorToolbar *)documentEditorToolbar;

/// Displayed document editor toolbar.
@property (nonatomic, readonly) PSPDFDocumentEditorToolbar *documentEditorToolbar;

/// The document editor on which the toolbar actions are performed.
@property (nonatomic, nullable) PSPDFDocumentEditor *documentEditor;

/// The page indexes of the pages that should be affected by actions that require page selection.
/// Should be set to an empty set when there are no selected items.
@property (nonatomic, copy) NSIndexSet *selectedPages;

/// Forwards actions from internal handlers.
@property (nonatomic, weak) id<PSPDFDocumentEditorToolbarControllerDelegate> delegate;

/// Used for modal presentation, class overrides, etc.
@property (nonatomic, weak) id<PSPDFPresentationContext> presentationContext;

/// Configuration object with various controller options.
@property (nonatomic, readonly) PSPDFDocumentEditorConfiguration *documentEditorConfiguration;

// MARK: Copy & Paste

/// Copies the selected pages into a private named UIPasteBoard on the document editor.
/// Uses `-[PSPDFDocumentEditor exportPages:toPath:withCompletionBlock:]` internally.
- (void)copySelectedPagesToPasteboard;

/// If pages are available on the internal pasteboard, this pastes them into the document.
/// The new pages are inserted after the last selected page or at the end of the document,
/// if no pages are currently selected.
/// Uses `-[PSPDFDocumentEditor importPagesTo:fromDocument:withCompletionBlock:queue:]` internally.
- (void)pastePagesFromPasteboard;

// MARK: Controllers

/// Shows or hides the new page view controller, depending on whether it is already visible.
///
/// @param sender      A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller (iPad only).
/// @param options     A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
- (nullable PSPDFNewPageViewController *)toggleNewPageController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

/// Shows or hides a confirmation view controller to let the user decide how the changes should be handled.
///
/// By default, this method presents the view controller returned from `-[PSPDFDocumentEditorToolbarController savingConfirmationControllerForSender:completionHandler:]`.
///
/// To avoid showing any confirmation UI to the user, override this method and implement your custom saving logic without calling `super`.
///
/// @see `PSPDFDocumentEditor`.
///
/// @param sender              A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller (iPad only).
/// @param options             A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
/// @param completionHandler   A completion callback, called when saving completes. Might be called after the save controller completes if "Save As..." is selected. If `cancelled` is yes, the save flow was interrupted.
- (nullable UIViewController *)toggleSavingConfirmationViewController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options completionHandler:(nullable void (^)(BOOL cancelled))completionHandler;

/// Shows or hides a view controller with saving options.
///
/// @param sender              A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller (iPad only).
/// @param options             A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
/// @param completionHandler   A completion callback, called when saving completes. If `cancelled` is YES, the save flow was interrupted.
- (nullable PSPDFSaveViewController *)toggleSaveController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options completionHandler:(nullable void (^)(BOOL cancelled))completionHandler;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFDocumentEditorToolbarController (SubclassingHooks)

/// Returns a view controller that allows the user to choose how they want the changes on the underlying document to be handled.
///
/// By default, this method returns a preconfigured `UIAlertController` instance with 4 available options:
///
/// - Save (only available if the document is writable)
/// - Save As
/// - Discard Changes
/// - Cancel
///
/// You can override this method to return a custom view controller that presents the available options in a custom manner.
///
/// When overriding this method to provide your custom alert logic, you need to perform the appropriate checks to make sure the actions of the returned alert controller are valid for the current context, and that they perform the appropriate actions on the underlying document. See `PSPDFDocumentEditor`.
///
/// To avoid any confirmation UI from being shown, override `- toggleSavingConfirmationViewController:presentationOptions:completionHandler:` and implement your custom saving logic there without calling `super`.
///
/// @param sender              A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller (iPad only).
/// @param completionHandler   A completion callback, called when saving completes. Might be called after the save controller completes if "Save As..." is selected. If `cancelled` is yes, the save flow was interrupted.
- (UIViewController *)savingConfirmationControllerForSender:(nullable id)sender completionHandler:(nullable void (^)(BOOL cancelled))completionHandler;

@end

NS_ASSUME_NONNULL_END
