//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFViewController.h>
#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFTabbedViewController.h>
#import <PSPDFKitUI/PSPDFNavigationItem+Private.h>

@class PSPDFAction;
@class PSPDFAnnotationViewCache;
@class PSPDFContentEditingCoordinator;
@class PSPDFDefaultApplication;
@class PSPDFDigitalSignatureCoordinator;
@class PSPDFDocument;
@class PSPDFJSPlatformDelegateAdapter;
@class PSPDFJSPrintParams;
@class PSPDFKeyboardHandlingView;
@class PSPDFLinkAnnotationView;
@class PSPDFPage;
@class PSPDFPageView;
@class PSPDFPresentationManager;
@class PSPDFScrollView;
@class PSPDFSoundAnnotationPlaybackCoordinator;
@class PSPDFViewControllerView;
@class PSPDFViewModeCoordinator;
@protocol PSPDFAnnotationPresenting;

NS_ASSUME_NONNULL_BEGIN

/// Called when the document is about to be changed / has been changed.
PSPDF_EXTERN NSNotificationName const PSPDFViewControllerWillChangeDocumentNotification;
PSPDF_EXTERN NSNotificationName const PSPDFViewControllerDidChangeDocumentNotification;

/// Rotation notifications.
PSPDF_EXTERN NSNotificationName const PSPDFViewControllerWillChangeSizeNotification;
PSPDF_EXTERN NSNotificationName const PSPDFViewControllerIsAnimatingSizeChangeNotification;
PSPDF_EXTERN NSNotificationName const PSPDFViewControllerDidChangeSizeNotification;

/// Editing notification. Will show/hide parts of the UI.
PSPDF_APP_EXPORT NSNotificationName const PSPDFViewControllerDidEnterEditingModeNotification;
PSPDF_APP_EXPORT NSNotificationName const PSPDFViewControllerDidExitEditingModeNotification;

PSPDF_EXTERN NSNotificationName const PSPDFViewControllerDidChangeControllerState;

PSPDF_EXTERN NSNotificationName const PSPDFViewControllerDidChangeViewModeNotification;

/// Called when the controller's configuration has been changed.
PSPDF_APP_EXPORT NSNotificationName const PSPDFViewControllerDidChangeConfigurationNotification;

/// # View Hierarchy
///
/// This only shows views that are relevant for presenting pages. There are other views involved, which are not shown here.
///
/// ```
///                             ┌───────────────────────────────┐
///                             │    PSPDFViewControllerView    │
///                             │     (PSPDFViewController)     │
///                             └───────────────────────────────┘
///                                             │
///                                     pagingScrollView
///                                             │
/// ╔═══Transition Style════════════════════════│══════════════════════════════════════════╗
/// ║               ┌───────────────────────────┼───────────────────────────┐              ║
/// ║               │                           │                           │              ║
/// ║               │                           │                           │              ║
/// ║               │                           │                           │              ║
/// ║               ▼                           ▼                           ▼              ║
/// ║ ┌─ ── ── ── ── ── ── ── ── ┐┌ ── ── ── ── ── ── ── ── ─┐┌─ ── ── ── ── ── ── ── ── ┐ ║
/// ║        ScrollPerPage       ││     ScrollContinuous                  Curl           │ ║
/// ║ │(actually ScrollPerSpread)                            ││                            ║
/// ║ └ ── ── ── ── ── ── ── ── ─┘└─ ── ── ── ── ── ── ── ── ┘└ ── ── ── ── ── ── ── ── ─┘ ║
/// ║               │                           │                           │              ║
/// ╚═══════════════│═══════════════════════════│═══════════════════════════│══════════════╝
///                 │                           │                           │
///                 ▼                           │                           │
///   ┌──────────────────────────┐              │                           │                 ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐
///   │  PSPDFPagingScrollView   │              │                           │                      Responsible for inter-page
///   │    (UIViewController)    │              │                           │                 │ scrolling (horizontal / vertical) │
///   └──────────────────────────┘              │                           │                  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
///                 *                           │                           │
///                 │                           │                           │
///                 ▼                           │                           ▼
///   ┌──────────────────────────┐              │             ┌──────────────────────────┐    ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐
///   │     PSPDFScrollView      │              │             │  PSPDFContentScrollView  │     Responsible for zooming and panning
///   │                          │              │             │(inherits PSPDFScrollView)│    │       inside a set of pages       │
///   └──────────────────────────┘              ▼             └──────────────────────────┘     ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
///                 │             ┌──────────────────────────┐              │                 ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐
///                 │             │  PSPDFContentScrollView  │              │                      Responsible for inter-page
///                 │             │(inherits PSPDFScrollView)│              │                 │   scrolling & zooming in pages    │
///                 │             └──────────────────────────┘              │                  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
///                 │                           │                           │
///                 │                           │                           │
///                 │                           ▼                           ▼
///                 │             ┌──────────────────────────┐+--------------------------+    ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐
///                 │             │          UIView          │| _UIPageViewCo...tentView |               Container View
///                 │             │    (UIViewController)    │|     (ViewController)     |    │                                   │
///                 │             └──────────────────────────┘+--------------------------+     ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
///                 │                           *                           2
///                 │                           │                           │
///                 ▼                           │                           ▼
///   ┌──────────────────────────┐              │             ┌──────────────────────────┐    ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐
///   │    PSPDFCompoundView     │              │             │   PSPDFSinglePageView    │               Container View
///   │                          │              │             │     (ViewController)     │    │                                   │
///   └──────────────────────────┘              │             └──────────────────────────┘     ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
///                 │                           │                           │
///          ┌──────┴──────┐                    │                           │
///          ▼             ▼                    ▼                           ▼
///   ┌────────────┐┌────────────┐┌──────────────────────────┐┌──────────────────────────┐    ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐
///   │PSPDFLeftPag││PSPDFRightPa││      PSPDFPageView       ││      PSPDFPageView       │     Contains actual page / image views
///   │   eView    ││   geView   ││                          ││                          │    │  Right/left page views don't add  │
///   └────────────┘└────────────┘└──────────────────────────┘└──────────────────────────┘                functionality
///                                                                                           └ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┘
/// ```
@interface PSPDFViewController () <PSPDFNavigationItemDelegate, PSPDFOverrideProvider>

/// Internal Swift Helper
+ (PSPDFViewController *)allocAndInitWithClass:(Class)klass document:(nullable PSPDFDocument *)document configuration:(nullable PSPDFConfiguration *)configuration;

/// The same object as `view`, but typed as our subclass.
@property (nonatomic, readonly) PSPDFViewControllerView *viewControllerView;

/// The main configuration object.
@property (nonatomic, copy) PSPDFConfiguration *configuration;

/// Returns the page object.
@property (nonatomic, readonly, nullable) PSPDFPage *page;

/// Returns all visible page objects.
@property (nonatomic, readonly) NSArray<PSPDFPage *> *visiblePages;

/// Returns the range of visible pages.
///
/// @note: Unlike `visiblePageViews` this ensure the range is really visible.
@property (nonatomic, readonly) NSRange visiblePageRange;

/// Saves the passed in document based on the receivers state of available features
/// and the auto saving option.
///
/// @note The document you pass in might be owned by another view controller but by
/// calling this method the receiver is the one that decides if a document should
/// be saved or not!
///
/// @param document The document to save.
- (void)saveDocument:(nullable PSPDFDocument *)document;

// MARK: user interface show/hide
- (BOOL)shouldShowControls;
- (void)hidePageElementsAnimated:(BOOL)animated;

/// Flag to set the tab bar's drag status. Used to disable user interface hiding while dragging.
- (void)setIsTabbedBarBeingDragged:(BOOL)isTabbedBarBeingDragged;

/// Thumbnails
@property (nonatomic, readonly) PSPDFViewModeCoordinator *viewModeCoordinator;

/// Access internal presentation manager
@property (nonatomic, readonly) PSPDFPresentationManager *presentationManager;

// MARK: Flags
@property (nonatomic, readonly) BOOL viewDidAppearCalled;
- (BOOL)isViewVisible;

/// Toggles the annotation mode (editing/not)
- (void)toggleAnnotationModeAnimated:(BOOL)animated completion:(nullable void (^)(BOOL finished))completionBlock;

/// actions
- (BOOL)isAnnotationEditingPossible;

@property (nonatomic, copy) NSArray<NSNumber *> *internalTapGesturesAllowedTouchTypes;

/// Locks the pan gesture of parent split view controllers so they don't interfere
/// with our gesture and drawing setup.
- (BOOL)lockPanGestureOfParentSplitViewEnabled:(BOOL)lockGesture;

/// Locks the interactive pop gesture of parent navigation view controllers so they
/// don't interfere with our gesture and drawing setup.
- (BOOL)lockInteractivePopGestureOfParentNavigationControllerEnabled:(BOOL)lockGesture;

/// Yes when statusbar hiding is requested.
@property (nonatomic, readonly, getter=isStatusBarHidden) BOOL statusBarHidden;

/// The store that is being used when annotations are saved by the user for later use. Defaults to nil.
/// Don't confuse this with regular annotation saving. The `annotationStore` is just for the PSPDFSavedAnnotationsViewController.
/// Saving annotations is enabled if the `editableAnnotations` set in the document contains `PSPDFAnnotationStringSavedAnnotations`.
@property (nonatomic) id<PSPDFAnnotationSetStore> annotationsStore;

/// Allows access to the annotation cache.
@property (nonatomic, readonly) PSPDFAnnotationViewCache *annotationViewCache;

/// The internal keyboard handler to forward key events.
@property (nonatomic, readonly) PSPDFKeyboardHandlingView *keyboardHandler;

// MARK: Bookmarks

/// Returns NSNotFound if none of the visible pages are bookmarked and the first visible
/// bookmarked page otherwise.
@property (nonatomic, readonly) NSUInteger bookmarkedPageForCurrentSpread;

/// Internal sound playback controller. Used to show and hide the appropriate sound player.
/// Change what player is shown via `soundAnnotationPlayerStyle`.
@property (nonatomic, readonly) PSPDFSoundAnnotationPlaybackCoordinator *soundAnnotationPlaybackCoordinator;

/// Digital signature coordinator used for digitally signing a document.
@property (nonatomic, readonly) PSPDFDigitalSignatureCoordinator *signatureCoordinator;

/// The tabbed view controller this instance is part of.
@property (nonatomic, readonly, nullable) PSPDFTabbedViewController *tabbedViewController;

/// Whether the view controller should be registering presented documents for file presentation
/// and handling file presentation callbacks.
@property (nonatomic, getter = isFilePresentationTrackingEnabled) BOOL filePresentationTrackingEnabled;

/// Undo action.
- (void)undo:(nullable id)sender;

/// Redo action.
- (void)redo:(nullable id)sender;

/// Invoke the go to page alert.
- (void)goToPage:(nullable id)sender;

/// Free function which is used to handle URLs from external apps for `PSPDFActionExecutor` and `PSPDFURLExecutor` so we don't duplicate the code.
PSPDF_EXPORT BOOL PSPDFHandleExternalURL(NSURL *URL, UIViewController *controller, PSPDFDefaultApplication *application,  void (^ _Nullable completionBlock) (BOOL switchedApplication));

/// Creates and configures a  `PSPDFDocumentSharingViewController`,
/// which then gives the caller the option to perform last minute customizations before presenting it.
- (void)presentSharingControllerForDocument:(PSPDFDocument *)document destination:(PSPDFDocumentSharingDestination)destination sender:(nullable id)sender customizations:(nullable void (^)(PSPDFDocumentSharingViewController *controllerToPresent))customizations;

// MARK: Content Editing

/// The content editing coordinator for this view controller. This will be `nil`
/// if _Content Editing_ feature is not included in the license.
@property (nonatomic, readonly, nullable) PSPDFContentEditingCoordinator *contentEditingCoordinator;

@end

@interface PSPDFViewController (PrivateLayoutGuides)

/// A layout guide marking the safe inset on the top you should use to position views
/// that should not be overlaid by the user interface view or similar views.
///
/// Elements using this guide will adjust as soon as the navigation bar starts the fadeout animation.
///
/// We used this for the (now removed) page grabber, and this could be used for similar elements.
@property (nonatomic, readonly) id<UILayoutSupport> safeTopLayoutGuide;

/// A layout guide similar to topLayoutGuide, but updated only on key layout events
/// and persisting the offset during navigation bar fadeout.
///
/// Elements using this guide will adjust only after the navigation bar fadeout animation is completed.
///
/// Use this instead of the other guides for elements that need to be attached to the
/// navigation bar even while it is fading out (tabbed bar, document label, etc.).
@property (nonatomic, readonly) id<UILayoutSupport> attachedSafeTopLayoutGuide;

/// A layout guide marking the safe inset on the bottom you should use to position
/// views that should not be overlaid by the user interface view or similar views.
@property (nonatomic, readonly) id<UILayoutSupport> safeBottomLayoutGuide;

/// A layout guide marking the inset on the bottom you should use to position
/// views that should not be overlaid by the user interface view.
@property (nonatomic, readonly) id<UILayoutSupport> userInterfaceBottomLayoutGuide;

/// A layout guide marking the inset on the leading side you should use to position
/// views that should not be overlaid by the user interface view.
@property (nonatomic, readonly) UILayoutGuide<UILayoutSupport> *userInterfaceLeadingLayoutGuide;

/// A layout guide marking the inset on the trailing side you should use to position
/// views that should not be overlaid by the user interface view.
@property (nonatomic, readonly) UILayoutGuide<UILayoutSupport> *userInterfaceTrailingLayoutGuide;

/// The controller shown in the `ViewMode.documentEditor` view mode.
///
/// @note Different to the public `documentEditorController` accessor, this doesn't lazy-create.
/// If the document editor isn't loaded or isn't licensed, it just returns nil.
@property (nonatomic, readonly, nullable) PSPDFDocumentEditorViewController *documentEditorControllerIfLoaded;

// MARK: - Private Subclassing Hooks

/// Checks whether item should be available for the current display mode.
- (BOOL)isBarButtonItemAvailable:(UIBarButtonItem *)barButtonItem;

/// The action of the built-in outline bar button item.
- (void)outlineButtonPressed:(nullable id)sender;

/// The action of the built-in email bar button item.
- (void)emailButtonPressed:(nullable id)sender;

/// The action of the built-in message bar button item.
- (void)messageButtonPressed:(nullable id)sender;

/// The action of the built-in activity bar button item.
- (void)activityButtonPressed:(id)sender;

/// Moves to the next page, else NOP.
- (void)previousPageAction:(nullable id)sender;

/// Moves to the previous page of possible, else NOP.
- (void)nextPageAction:(nullable id)sender;

/// Scrolls to the very first page in the document.
- (void)scrollToFirstPageAction:(nullable id)sender;

/// Scrolls to the very last page in the document.
- (void)scrollToLastPageAction:(nullable id)sender;

/// Open the sharing interface to print, export, show the activity controller or share via email or messages.
- (void)shareWithDestination:(PSPDFDocumentSharingDestination)destination sender:(nullable id)sender;

/// Presents the `RedactionViewController` to show information about uncommitted redactions on the document.
///
/// Requires the Redaction license component.
- (void)redactionInfoButtonPressed:(nullable id)sender;

/// Activates reader mode.
///
/// Requires the Reader View license component.
- (void)readerViewButtonPressed:(nullable id)sender;

/// Perform the default action for pressing `contentEditingButtonItem`.
///
/// > Important: The default action requires the _Content Editing_ feature to be
/// > included in the license.
- (void)contentEditingButtonItemPressed:(nullable id)sender;

@end

@interface PSPDFViewController (Testing)

/// Whether the view controller received its first `viewWillLayoutSubviews`.
@property (nonatomic, readonly) BOOL firstViewWillLayoutSubviewsCalled;

/// Whether the document in question should be saved with the given document saving options.
///
/// @param document Document to save.
/// @param options  The current options that the document is going to be saved with. This is an inout parameter.
///
/// @return BOOL indicating whether the passed document should be saved with the passed parameters.
///
/// @note This method will return `true` if the view controller's PSPDFConfiguration autosave option is enabled
/// along with the document's annotation save mode is set to option other than PSPDFAnnotationSaveModeDisabled
/// and `-[PDFViewControllerDelegate pdfViewController:shouldSaveDocument:withOptions:]` returns YES.
- (BOOL)shouldSaveDocument:(PSPDFDocument *)document withOptions:(NSDictionary<PSPDFDocumentSaveOption, id> *_Nonnull *_Nonnull)options;

@end

NS_ASSUME_NONNULL_END
