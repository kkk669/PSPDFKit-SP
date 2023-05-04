//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKitUI/PSPDFErrorHandler.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFContextMenuOption) {
    /// Displays a context menu. Suppresses situations where a popover would fit better.
    PSPDFContextMenuOptionMenuOnly,
    /// Displays a context menu. Allows a popover if situation fits.
    PSPDFContextMenuOptionAllowPopovers,
    /// Does not allow context menu, only presents popovers (if possible, otherwise does not present anything)
    PSPDFContextMenuOptionPopoversOnly,
} NS_SWIFT_NAME(ContextMenuOption);

@class PSPDFAction;

/// Protocol for handling page changes.
PSPDF_PROTOCOL_SWIFT(PageControls)
@protocol PSPDFPageControls<NSObject>

/// Set the page to a specific page index.
///
/// @param pageIndex Page index of the page that should be shown.
/// @param animated Defines if changing the page should be animated.
- (void)setPageIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animated;

/// Set the view mode.
///
/// @param viewMode View mode to change to.
/// @param animated Defines if changing the view mode should be animated.
- (void)setViewMode:(PSPDFViewMode)viewMode animated:(BOOL)animated;

/// Executes a passed in PDF action.
///
/// @param action The action to execute.
/// @param targetRect The rect that triggered this action in the receiver's view coordinate space.
/// @param pageIndex The current page index. This is used for relative actions like `NamedActionType.nextPage` and to register a back action in the back-forward action list.
/// @param animated Whether the transition the action is describing should be animated.
/// @param actionContainer The sender that triggered the execution of this action, such as an annotation or a button.
/// @return Whether the action or at least one of its sub-actions should be added to the back-forward action list.
- (BOOL)executePDFAction:(nullable PSPDFAction *)action targetRect:(CGRect)targetRect pageIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animated actionContainer:(nullable id)actionContainer;

/// Go forward in the navigation history if possible.
- (void)navigateForwardAnimated:(BOOL)animated;

/// Go back in the navigation history if possible.
- (void)navigateBackAnimated:(BOOL)animated;

/// Search for a specific string.
- (void)searchForString:(nullable NSString *)searchText options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated;

/// Presents the document info view controller.
- (nullable UIViewController *)presentDocumentInfoViewControllerWithOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated completion:(nullable void (^)(void))completion;

/// Allows file preview using QuickLook.
- (void)presentPreviewControllerForURL:(NSURL *)fileURL title:(nullable NSString *)title options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated completion:(nullable void (^)(void))completion;

/// Reloads the displayed controller and view.
- (void)reloadData;

/// Invokes the print share action.
- (void)printButtonPressed:(nullable id)sender;

@end

/// Protocol handling the user interface.
PSPDF_PROTOCOL_SWIFT(UserInterfaceControls)
@protocol PSPDFUserInterfaceControls<NSObject>

/// Defines if the user interface should be shown.
@property (nonatomic, readonly) BOOL shouldShowControls;

/// Hides the user interface.
- (BOOL)hideControlsAnimated:(BOOL)animated;

/// Hides the user interface and additional elements like page selection.
- (BOOL)hideControlsAndPageElementsAnimated:(BOOL)animated;

/// Toggles the visibility state of the user interface.
- (BOOL)toggleControlsAnimated:(BOOL)animated;

/// Shows the user interface.
- (BOOL)showControlsAnimated:(BOOL)animated;

/// Show menu if annotation/text is selected.
- (void)showMenuIfSelectedWithOption:(PSPDFContextMenuOption)contextMenuOption animated:(BOOL)animated;

@end

/// Protocol handling various controls.
PSPDF_PROTOCOL_SWIFT(ControlDelegate)
@protocol PSPDFControlDelegate<PSPDFPresentationActions, PSPDFPageControls, PSPDFUserInterfaceControls, PSPDFErrorHandler>
@end

NS_ASSUME_NONNULL_END
