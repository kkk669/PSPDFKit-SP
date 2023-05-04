//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>

#import <MessageUI/MessageUI.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFBackForwardActionList.h>
#import <PSPDFKit/PSPDFTextSearch.h>
#import <PSPDFKit/PSPDFFileConflictResolution.h>
#import <PSPDFKitUI/PSPDFAnnotationTableViewController.h>
#import <PSPDFKitUI/PSPDFBookmarkViewController.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKitUI/PSPDFConflictResolutionManager.h>
#import <PSPDFKitUI/PSPDFControllerState.h>
#import <PSPDFKitUI/PSPDFExternalURLHandler.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarContainer.h>
#import <PSPDFKitUI/PSPDFInlineSearchManager.h>
#import <PSPDFKitUI/PSPDFNavigationItem.h>
#import <PSPDFKitUI/PSPDFOutlineViewController.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>
#import <PSPDFKitUI/PSPDFSearchViewController.h>
#import <PSPDFKitUI/PSPDFThumbnailBar.h>
#import <PSPDFKitUI/PSPDFUserInterfaceView.h>
#import <PSPDFKitUI/PSPDFWebViewController.h>
#import <PSPDFKitUI/PSPDFFormSubmissionDelegate.h>
#import <PSPDFKitUI/PSPDFDocumentViewInteractions.h>

@protocol PSPDFAnnotationSetStore, PSPDFViewControllerDelegate;
@class PSPDFAction;
@class PSPDFAnnotationStateManager;
@class PSPDFAnnotationToolbar;
@class PSPDFAnnotationToolbarController;
@class PSPDFAnnotationViewCache;
@class PSPDFAppearanceModeManager;
@class PSPDFBrightnessManager;
@class PSPDFDocument;
@class PSPDFDocumentEditorViewController;
@class PSPDFDocumentInfoCoordinator;
@class PSPDFDocumentLabelView;
@class PSPDFDocumentViewController;
@class PSPDFPageLabelView;
@class PSPDFPageView;
@class PSPDFPageViewController;
@class PSPDFRelayTouchesView;
@class PSPDFScrollView;
@class PSPDFSearchHighlightViewManager;
@class PSPDFSearchResult;
@class PSPDFThumbnailViewController;
@class PSPDFViewState;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PSPDFAutosaveReason) {
    /// Called when the view controller was visible but is being dismissed/is disappearing because of another presentation. (`viewDidDisappear`)
    PSPDFAutosaveReasonDisappearing,
    /// The application is moved to background (see `UIApplicationDidEnterBackgroundNotification`)
    PSPDFAutosaveReasonMovingToBackground,
    /// The application is terminating. (see `UIApplicationWillTerminateNotification`)
    PSPDFAutosaveReasonTerminating,
    /// A File conflict has been detected and is being resolved. (see `PSPDFFileConflictResolution`)
    PSPDFAutosaveReasonResolvingFileConflict
};

/// This is the main view controller to display PDF documents.
///
/// This view controller can be used modally or embedded in another view controller.
///
/// @note When adding as a child view controller, ensure view controller containment is set up correctly.
/// If you override this class, ensure all `UIViewController` methods you're using do call super.
/// https://pspdfkit.com/guides/ios/customizing-the-interface/embedding-the-pspdfviewcontroller-inside-a-custom-container-view-controller/
///
/// For subclassing, use `overrideClass:withClass:` to register your custom subclasses.
/// https://pspdfkit.com/guides/ios/getting-started/overriding-classes/
///
/// The best time for setting properties is during initialization in `commonInitWithDocument:configuration:`. Some properties require a call to `reloadData` if they are changed after the controller has been displayed. Do not set properties during a rotation phase or view appearance (e.g. use `viewDidAppear:` instead of `viewWillAppear:`) since that could corrupt internal state, instead use `updateSettingsForBoundsChangeBlock`.
///
/// To provide a more immersive viewing experience, `PDFViewController` shows content underneath the navigation bar
/// and allows the user to tap to hide this bar. Therefore, using bars with transparent backgrounds is not supported.
/// `PDFViewController` will automatically handle disabling transparent bar backgrounds when its a direct child of a
/// `UINavigationController` or a `UITabBarController`. For other view controller hierarchies, you should disable
/// transparent bar backgrounds by setting the `scrollEdgeAppearance` to be the same as the `standardAppearance` on
/// the navigation bar, toolbar, or tab bar.
PSPDF_CLASS_SWIFT(PDFViewController)
@interface PSPDFViewController : PSPDFBaseViewController<
MFMailComposeViewControllerDelegate,
MFMessageComposeViewControllerDelegate,
PSPDFAnnotationTableViewControllerDelegate,
PSPDFBackForwardActionListDelegate,
PSPDFBookmarkViewControllerDelegate,
PSPDFConflictResolutionManagerDelegate,
PSPDFControlDelegate,
PSPDFDocumentSharingViewControllerDelegate,
PSPDFErrorHandler,
PSPDFExternalURLHandler,
PSPDFFlexibleToolbarContainerDelegate,
PSPDFInlineSearchManagerDelegate,
PSPDFOutlineViewControllerDelegate,
PSPDFOverridable,
PSPDFPresentationContext,
PSPDFSearchViewControllerDelegate,
PSPDFTextSearchDelegate,
PSPDFWebViewControllerDelegate
>

// MARK: Initialization and essential properties.

/// Initialize with a document.
///
/// @note Document can be nil. In this case, just the background is displayed and the User Interface stays visible.
/// Also supports creation via `initWithCoder:` to allow usage in Storyboards.
- (instancetype)initWithDocument:(nullable PSPDFDocument *)document configuration:(nullable PSPDFConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

/// Convenience init for `initWithDocument:configuration:` that uses a default configuration set.
- (instancetype)initWithDocument:(nullable PSPDFDocument *)document;

/// Property for the currently displayed document.
///
/// @note To allow easier setup via Storyboards, this property also accepts `NSString`s. (The default bundle path will be used.)
@property (nonatomic, nullable) PSPDFDocument *document;

/// Set or get selected annotations.
///
/// @note: All set selected annotations must be on the same page view.
@property (nonatomic, copy) NSArray<PSPDFAnnotation *> *selectedAnnotations;

/// The document view controller displaying the current document.
///
/// The `documentViewController` is a child view controller of `PDFViewController`.
/// It is responsible for the main document content view, shown when the view controller
/// is in `PSPDFViewModeDocument`.
///
/// @note This returns `nil` if `document` is `nil` or invalid.
@property (nonatomic, readonly, nullable) PSPDFDocumentViewController *documentViewController;

/// Register delegate to capture events, change properties.
@property (nonatomic, weak) IBOutlet id<PSPDFViewControllerDelegate> delegate;

/// Register to be informed of and direct form submissions.
@property (nonatomic, weak) IBOutlet id<PSPDFFormSubmissionDelegate> formSubmissionDelegate;

/// Reloads the view hierarchy and triggers a re-render of the document.
/// This method is required to be called after most changed settings.
/// Certain setters like changing a document will trigger this implicitly.
///
/// If possible (= the document has not changed significantly) this will preserve:
/// - The current view state (page and scrolling position)
/// - Selected annotations
///
/// @note This is called implicitly with `updateConfigurationWithBuilder:`.
///
/// To reset the view port, call `applyViewState:animateIfPossible:` with a view state
/// that only offers a page and not a specific view port:
/// `[[PSPDFViewState alloc] initWithPageIndex:pageIndex]`
- (IBAction)reloadData;

/// Reloads the view hierarchy and triggers a re-render of specific pages.
///
/// Annotation selection will be cleared.
///
/// @param indexes The index set of the pages in the document to be reloaded.
/// @param animated Whether to animate the view updates.
- (void)reloadPagesAtIndexes:(NSIndexSet *)indexes animated:(BOOL)animated NS_SWIFT_NAME(reloadPages(indexes:animated:));

// MARK: Page Scrolling

/// The index of the current page.
///
/// If there is more than one page displayed, the getter returns the index of the first page in the spread that is in the center of the viewport.
/// With `PageTransition.scrollPerSpread` (displaying a single spread), this will be the lowest visible page index.
/// With `PageTransition.scrollContinuous` this will be the index of the page in the center of the viewport.
///
/// More advanced APIs to handle spread transitions and other document view mode related
/// APIs are available through `PSPDFDocumentViewController`. In particular, these may be useful:
/// `documentViewController.visibleSpreadViews`, `PSPDFSpreadView`’s `spreadIndex` property, and
/// `documentViewController.layout.pageRangeForSpread(at spreadIndex)`.
///
/// Setting the page index will be ignored if the document is not valid (e.g. locked).
///
/// @see `-documentViewController`
@property (nonatomic) PSPDFPageIndex pageIndex;

/// Sets the current page while optionally animating the change.
///
/// More advanced APIs to handle spread transitions and other document view mode related
/// APIs are available through `PSPDFDocumentViewController`.
///
/// Setting the page index will be ignored if the document is not valid (e.g. locked).
///
/// @see `-documentViewController`
///
/// @param pageIndex The page to transition to.
/// @param animated `true` if the transition should be animated, `false` otherwise.
- (void)setPageIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animated;

// MARK: View State Restoration

/// Captures the current view–state of the receiver as a serializable object.
///
/// @note There may not always be a view–state to capture.
/// Reasons for this include the view not being loaded yet, no document being set, etc.
/// As a rule of thumb, you should only expect to obtain a nonnull value after `viewDidAppear:` and before `viewWillDisappear:` has been called.
@property (nonatomic, readonly, nullable) PSPDFViewState *viewState;

/// Applies a previously captured view state, optionally animated.
///
/// @param viewState The state to restore.
/// @param animateIfPossible A hint whether applying the state should be animated.
/// It is not always possible to animate application of a new view state:
/// Animation only ever happens if the view controller is currently on screen.
/// Therefore, a `true` value _may_ be silently ignored.
///
/// A word on timing:
/// The most common use–case for this method is to seamlessly restore the reading position in a document when displaying the receiver.
/// However, since restoring a viewport requires a fairly complete view hierarchy, you should not try to call this method directly after init.
/// If you subclass PSPDFViewController, `viewWillAppear:` and `viewDidLayoutSubviews` (after calling `super`) are good times to do so.
///
/// @note For `PageTransition.curl`, only the _page_ is restored.
- (void)applyViewState:(PSPDFViewState *)viewState animateIfPossible:(BOOL)animateIfPossible;

// MARK: Searching

/// Search current page, but don't show any search UI.
/// Dictionary key, expects a boxed boolean as value.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionSearchHeadless;

/// Searches for `searchText` within the current document.
/// Opens the `PSPDFSearchViewController`, or presents inline search UI based `searchMode` in `PDFConfiguration`.
/// If `searchText` is nil, the UI is shown but no search is performed.
/// The only valid option is `PSPDFPresentationOptionSearchHeadless` to disable the search UI.
///
/// @param options Forwarded to the `presentViewController:options:animated:sender:completion:` method.
/// @param sender Used to anchor the search popover, if one should be displayed (see `searchMode` in `PDFConfiguration`).
///
/// @note If search is already active (as determined by  `isSearchActive`) then calling this method again will ignore `options`
/// and won't present the controller again. If you need to do that, first cancel the previous search using `cancelSearchAnimated:`.
- (void)searchForString:(nullable NSString *)searchText options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated;

/// Cancels search and hides search UI.
- (void)cancelSearchAnimated:(BOOL)animated;

/// Returns YES if a search UI is currently being presented.
@property (nonatomic, getter=isSearchActive, readonly) BOOL searchActive;

/// The search view manager
@property (nonatomic, readonly) PSPDFSearchHighlightViewManager *searchHighlightViewManager;

/// The inline search manager used when `PSPDFSearchModeInline` is set.
@property (nonatomic, readonly) PSPDFInlineSearchManager *inlineSearchManager;

/// The appearance manager, responsible for the rendering style and app theme.
@property (nonatomic, readonly) PSPDFAppearanceModeManager *appearanceModeManager;

/// Text extraction class for current document.
/// The delegate is set to this controller. Don't change but create your own text search class instead if you need a different delegate.
///
/// @note Will be recreated as the document changes. Returns nil if the document is nil. Thread safe.
@property (nonatomic, readonly) PSPDFTextSearch *textSearch;

// MARK: Actions

/// Executes a passed in PDF action.
///
/// @param action The action to execute.
/// @param targetRect The rect that triggered this action in the receiver's view coordinate space.
/// @param pageIndex The current page index. This is used for relative actions like `NamedActionType.nextPage` and to register a back action in the back-forward action list.
/// @param animated Whether the transition the action is describing should be animated.
/// @param actionContainer The sender that triggered the execution of this action, such as an annotation or a button.
/// @return Whether the action or at least one of its sub-actions was added to `backForwardList`.
- (BOOL)executePDFAction:(nullable PSPDFAction *)action targetRect:(CGRect)targetRect pageIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animated actionContainer:(nullable id)actionContainer;

/// Represents previously invoked PDF actions and allows navigation through the action history.
///
/// You need to manually update this list if you're executing actions outside of this view controller.
@property (nonatomic, readonly) PSPDFBackForwardActionList *backForwardList;

// MARK: User Interface Controls

/// View that is displayed as User Interface.
@property (nonatomic, readonly) PSPDFUserInterfaceView *userInterfaceView;

/// Show or hide User Interface controls, titlebar, status bar (depending on the appearance properties).
@property (nonatomic, getter=isUserInterfaceVisible) BOOL userInterfaceVisible;

/// Show or hide User Interface controls. optionally animated.
- (BOOL)setUserInterfaceVisible:(BOOL)show animated:(BOOL)animated;

/// Show the User Interface. Respects `UserInterfaceViewMode`.
- (BOOL)showControlsAnimated:(BOOL)animated;

/// Hide the User Interface. Respects `UserInterfaceViewMode`.
- (BOOL)hideControlsAnimated:(BOOL)animated;

/// Hide the User Interface (respects `UserInterfaceViewMode`) and additional elements like page selection.
- (BOOL)hideControlsAndPageElementsAnimated:(BOOL)animated;

/// Toggles the User Interface. Respects `UserInterfaceViewMode`.
- (BOOL)toggleControlsAnimated:(BOOL)animated;

/// Content view. Use this if you want to add any always-visible UI elements.
/// ContentView does NOT overlay the `navigationBar`/`statusBar`, even if that one is transparent.
@property (nonatomic, readonly) PSPDFRelayTouchesView *contentView;

/// Check this to determine the navigation bar visibility when it is managed by PSPDFKit.
/// Will return the same value as `navigationController.navigationBarHidden` if
/// `shouldHideNavigationBarWithUserInterface` is not set or `userInterfaceViewMode` is set to `UserInterfaceViewMode.always`.
///
/// @note PSPDFKit always sets `navigationController.navigationBarHidden` to `false` when managing
/// navigation bar visibility.
@property (nonatomic, getter=isNavigationBarHidden, readonly) BOOL navigationBarHidden;

// MARK: Controller State

/// The controller state that this view controller is currently in.
@property (nonatomic, readonly) PSPDFControllerState controllerState;

/// If `controllerState` equals `PSPDFControllerStateError` or `PSPDFControllerStateLocked`, contains the underlying error.
@property (nonatomic, nullable, readonly) NSError *controllerStateError;

/// The view controller that is used to present the current controller state overlay of the `PDFViewController`.
///
/// Setting the overlay view controller makes it a child view controller of the receiver.
///
/// @note The default value for this property is an internal view controller that is used to visualize the state.
/// Only set this property if you want to take care of state handling yourself.
@property (nonatomic, nullable) UIViewController<PSPDFControllerStateHandling> *overlayViewController;

// MARK: Class Accessors

/// Return the pageView for a given page. Returns nil if page is not Initialized (e.g. page is not visible.)
/// Usually, using the delegates is a better idea to get the current page.
- (nullable PSPDFPageView *)pageViewForPageAtIndex:(PSPDFPageIndex)pageIndex;

// MARK: View Mode

/// Get or set the current view mode. (`PSPDFViewModeDocument` or `ViewMode.thumbnails`)
@property (nonatomic) PSPDFViewMode viewMode;

/// Set the view mode, optionally animated.
- (void)setViewMode:(PSPDFViewMode)viewMode animated:(BOOL)animated;

/// The controller shown in the `ViewMode.thumbnails` view mode. Contains a (grid) collectionView. Lazily created.
@property (nonatomic, readonly) PSPDFThumbnailViewController *thumbnailController;

/// The controller shown in the `ViewMode.documentEditor` view mode. Lazily created.
///
/// @note Requires the Document Editor component to be enabled for your license.
@property (nonatomic, readonly) PSPDFDocumentEditorViewController *documentEditorController;

// MARK: Helpers

/// Return array of all currently visible `PDFPageView` objects.
///
/// @note: The underlying view is `UICollectionView`, thus this might return views that are not visible.
/// Some reasons why the collection view might keep views around:
/// - Prefetching (for smoother scrolling)
/// - The view contains a first responder (It is kept around until the responder moves somewhere else)
@property (nonatomic, readonly) NSArray<PSPDFPageView *> *visiblePageViews;

/// Called when `viewWillLayoutSubviews` is triggered.
///
/// @note You can use this to adapt to view frame changes (i.e., add or remove toolbar items). Check `pdfController.traitCollection` and act accordingly.
- (void)setUpdateSettingsForBoundsChangeBlock:(void (^)(PSPDFViewController *pdfController))block;

/// Resets the apperance mode when view disappears. Defaults to `true`.
/// Setting this property to `false` can be useful when presenting multiple `PDFViewController` instances and you want to persist the appearance mode.
///
/// @note You set this property to `false`, you need to manually handle the appearance mode reset after dismissing the last controller.
@property (nonatomic) BOOL shouldResetAppearanceModeWhenViewDisappears;

// MARK: Configuration

/// The configuration. Defaults to `+PSPDFConfiguration.defaultConfiguration`.
///
/// @warning You cannot set this property to `nil` since the pdf controller must always have a configuration.
@property (nonatomic, copy, readonly) PSPDFConfiguration *configuration;

/// Changes any value within `PDFConfiguration` and correctly updates the state in the controller.
///
/// @note This will invoke `reloadData` to apply the changes, which will reset the zoom level back to 1.0.
- (void)updateConfigurationWithBuilder:(NS_NOESCAPE void (^)(PSPDFConfigurationBuilder *builder))builderBlock;

/// Updates the configuration without triggering a view reload.
///
/// @see updateConfigurationWithBuilder: for a better alternative.
///
/// @warning You should know what you're doing with using this updater.
///
/// The `PDFViewController` will not be reloaded, which can bring it into an invalid state.
/// Use this for properties that don't require reloading such as `textSelectionEnabled` or `scrollOnEdgeTapEnabled`. The benefit is that this method does not trigger a reload and thus is faster.
/// As a general rule, any property that changes the view hierarchy will require an explicit update.
///
/// Changes in PSPDFKit might result in differences around explicit/implicit updating.
/// A property which was picked up before might no longer be updated automatically with an update.
/// Makes sure to test calls to this option whenever you attempt a version update.
- (void)updateConfigurationWithoutReloadingWithBuilder:(NS_NOESCAPE void (^)(PSPDFConfigurationBuilder *builder))builderBlock;

// MARK: Presentation

/// Show a modal view controller or a popover with automatically added close button on the left side.
/// Use sender (`UIBarButtonItem` or `UIView`) OR rect in `options` (both only needed for the popover)
///
/// @see PSPDFPresentationActions.h for compatible keys for `options`.
///
/// @note If this returns NO, the completion block won't be called and presentation was blocked.
- (BOOL)presentViewController:(UIViewController *)controller options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options animated:(BOOL)animated sender:(nullable id)sender completion:(nullable void (^)(void))completion;

/// Dismisses a view controller or popover controller, if class matches.
- (BOOL)dismissViewControllerOfClass:(nullable Class)controllerClass animated:(BOOL)animated completion:(nullable void (^)(void))completion;

// MARK: Presenting embedded files

/// Invoked when a document action wants to present a new document modally. Can be subclassed to change behavior.
///
/// @see PSPDFPresentationActions.h for compatible keys for `options`.
- (void)presentPDFViewControllerWithDocument:(PSPDFDocument *)document options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated configurationBlock:(nullable void (^)(PSPDFViewController *pdfController))configurationBlock completion:(nullable void (^)(void))completion;

/// Allows file preview using QuickLook. Will call `presentPDFViewControllerWithDocument:` if the pdf filetype is detected.
///
/// @see PSPDFPresentationActions.h for compatible keys for `options`.
- (void)presentPreviewControllerForURL:(NSURL *)fileURL title:(nullable NSString *)title options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated completion:(nullable void (^)(void))completion;

// MARK: Annotations

/// A convenience accessor for a pre-configured, persistent, annotation state manager for the controller.
@property (nonatomic, readonly) PSPDFAnnotationStateManager *annotationStateManager;

// MARK: Toolbar button items

/// Use this if you want to customize the navigation bar appearance of a `PDFViewController`.
///
/// @note This creates a `navigationItem` on demand, only call this method if you need it.
@property (nonatomic, readonly) PSPDFNavigationItem *navigationItem;

/// Closes the active modal view controller.
/// Default button in `leftBarButtonItems` if view is presented modally.
@property (nonatomic, readonly) UIBarButtonItem *closeButtonItem;

/// Presents the view controller of the `documentInfoCoordinator`, which show information like the document outline and bookmarks.
@property (nonatomic, readonly) UIBarButtonItem *outlineButtonItem;

/// Presents the `SearchViewController` or the `InlineSearchManager` for searching text in the current `document`.
///
/// @see `SearchMode` in `PDFConfiguration` to configure this.
@property (nonatomic, readonly) UIBarButtonItem *searchButtonItem;

/// A bar button item that shows Reader View, which reformats document text into
/// an easy-to-read, single-column view that’s optimized for mobile devices.
///
/// This bar button item is not included by default. It must be programatically
/// added to the left or right bar button items.
///
/// Reader View can also be presented programatically using the `ReaderViewController` class.
///
/// @note Requires the Reader View component to be enabled for your license.
///
/// @see https://pspdfkit.com/guides/ios/features/reader-view/ for further documentation.
@property (nonatomic, readonly) UIBarButtonItem *readerViewButtonItem;

/// Toggles between the document and the thumbnails view state (`ViewMode.thumbnails`).
///
/// @see `PSPDFViewMode`
/// @see `setViewMode:animated:`
@property (nonatomic, readonly) UIBarButtonItem *thumbnailsButtonItem;

/// Toggles between the document and the document editor view state (`ViewMode.documentEditor`).
///
///
/// @note Requires the Document Editor component to be enabled for your license.
///
/// @see `PSPDFViewMode`
/// @see `setViewMode:animated:`
@property (nonatomic, readonly) UIBarButtonItem *documentEditorButtonItem;

/// Presents custom printing options and then invokes `UIPrintInteractionController` for document printing.
///
/// This is a preset for invoking `PDFDocumentSharingViewController` using `DocumentSharingConfiguration.Destination.print`.
///
/// @note Only displayed if document is allowed to be printed (see `allowsPrinting` in `Document`).
@property (nonatomic, readonly) UIBarButtonItem *printButtonItem;

/// Presents export options and then invokes `UIDocumentInteractionController` to open the document in other apps.
///
/// This is a preset for invoking `PDFDocumentSharingViewController` using `DocumentSharingConfiguration.Destination.otherApplication`.
@property (nonatomic, readonly) UIBarButtonItem *openInButtonItem;

/// Presents export options and then invokes `MFMailComposeViewController` to send the document via email.
///
/// This is a preset for invoking `PDFDocumentSharingViewController` using `DocumentSharingConfiguration.Destination.email`.
///
/// @note Will only work when sending emails is configured on the device.
@property (nonatomic, readonly) UIBarButtonItem *emailButtonItem;

/// Presents export options and then invokes `MFMessageComposeViewController` to send the document via iMessage/SMS.
///
/// This is a preset for invoking `PDFDocumentSharingViewController` using `DocumentSharingConfiguration.Destination.messages`.
///
/// @note Will only work if iMessage or SMS is configured on the device. Doesn’t work on Mac Catalyst as of macOS 12.
@property (nonatomic, readonly) UIBarButtonItem *messageButtonItem;

/// Shows and hides the `AnnotationToolbar` toolbar for creating annotations.
///
/// @note Requires the `Features.annotationEditing` feature flag.
@property (nonatomic, readonly) UIBarButtonItem *annotationButtonItem;

/// Shows a user interface for adding a signature to the document.
///
/// @note Requires the Electronic Signatures feature to be enabled in your license.
@property (nonatomic, readonly) UIBarButtonItem *signatureButtonItem;

/// Presents the `BookmarkViewController` for creating/editing/viewing bookmarks.
@property (nonatomic, readonly) UIBarButtonItem *bookmarkButtonItem;

/// Presents the `BrightnessViewController` to control screen brightness and to change the appearance mode.
///
/// @note iOS has a similar feature in the control center, but PSPDFKit brightness includes an additional software brightener. Not available on Mac Catalyst.
@property (nonatomic, readonly) UIBarButtonItem *brightnessButtonItem;

/// Presents the `UIActivityViewController` for various actions, including many of the above button items.
@property (nonatomic, readonly) UIBarButtonItem *activityButtonItem;

/// Presents the `PDFSettingsViewController` to control some aspects of PSPDFViewController UX.
@property (nonatomic, readonly) UIBarButtonItem *settingsButtonItem;

/// Transitions to the `.contentEditing` view mode.
///
/// > Important: Using this bar button item requires _Content Editing_ feature
/// > to be included in your license.
@property (nonatomic, readonly) UIBarButtonItem *contentEditingButtonItem;

/// Add your custom `UIBarButtonItems` so that they won't be automatically enabled/disabled.
/// Contains the `closeButtonItem` by default.
///
/// @warning This needs to be set before setting `left/rightBarButtonItems`.
@property (nonatomic, copy) NSArray<UIBarButtonItem *> *barButtonItemsAlwaysEnabled;

/// Handles the controllers for metadata infos (outline, annotations, bookmarks, embedded files)
@property (nonatomic, readonly) PSPDFDocumentInfoCoordinator *documentInfoCoordinator;

/// Accesses and manages the annotation toolbar.
/// To check if the toolbar is visible, check if a window is set on the toolbar.
@property (nonatomic, readonly, nullable) PSPDFAnnotationToolbarController *annotationToolbarController;

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: Subclassing Hooks

/// Override this initializer to allow all use cases (storyboard loading, etc)
///
/// @warning Do not call this method directly, except for calling super when overriding it.
- (void)commonInitWithDocument:(nullable PSPDFDocument *)document configuration:(PSPDFConfiguration *)configuration NS_REQUIRES_SUPER;

/// Called when a document view controller has been created.
///
/// A document view controller may be created and destroyed multiple times through
/// out the lifetime of a `PDFViewController`, depending on the document being set
/// and its state.
///
/// You can implement this method to customize a document view controller's appearance.
- (void)documentViewControllerDidLoad;

/// Override if you're changing the toolbar to your own.
/// The toolbar is only displayed, if `PDFViewController` is inside a `UINavigationController`.
- (void)updateToolbarAnimated:(BOOL)animated;

/// Return rect of the content view area excluding translucent toolbar/status bar.
///
/// @note This method does not compensate for the navigation bar alone. Returns the view bounds when the view controller is not visible.
@property (nonatomic, readonly) CGRect contentRect;

/// Bar Button Actions
- (void)annotationButtonPressed:(nullable id)sender;

/// Will save the document. Don't call this method directly.
///
/// Called with one of the reasons outlined in `PSPDFAutosaveReason`.
/// Can be overridden to customize or disable autosaving.
///
/// @note `document` might differ from the current set document, if it is changed while a file notification is received async.
- (void)handleAutosaveRequestForDocument:(PSPDFDocument *)document reason:(PSPDFAutosaveReason)reason;

// MARK: Customizing the User Interactions

/// A collection of customizable interaction components.
@property (nonatomic, readonly) id<PSPDFDocumentViewInteractions> interactions;

@end

NS_ASSUME_NONNULL_END
