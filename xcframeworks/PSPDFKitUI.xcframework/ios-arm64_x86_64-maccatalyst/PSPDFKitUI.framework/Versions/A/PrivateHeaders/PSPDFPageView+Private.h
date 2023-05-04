//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFPageView.h>
#import <PSPDFKitUI/PSPDFPageView+AnnotationMenu.h>
#import <PSPDFKitUI/PSPDFPageView+Scribble.h>

#import <PSPDFKit/PSPDFAnnotationStyleManager.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFReusableObjectCache.h>
#import <PSPDFKitUI/PSPDFDrawView+Private.h>
#import <PSPDFKitUI/PSPDFResizableView+Private.h>
#import <PSPDFKitUI/PSPDFTextSelectionView+Private.h>

@class PSPDFAnnotationMenuInteraction;
@class PSPDFBookmarkIndicatorButton;
@class PSPDFDocument;
@class PSPDFDocumentView;
@class PSPDFDocumentViewController;
@class PSPDFKeyboardHandlingView;
@class PSPDFMeasurementSnapper;
@class PSPDFPage;
@class PSPDFPageViewDragAndDropHandler;
@class PSPDFTextMarkupAnnotation;
@class PSPDFViewState;
@protocol PSPDFColorPicker;
@protocol PSPDFPendingUndoRecorder;

/// Enable this to see the presentation rect that the page view computes for
/// menus and popovers. The presentation rect will flash as a red border every
/// time `defaultPresentationRectForAnnotations:` is called.
#define DEBUG_PAGE_VIEW_PRESENTATION_RECT 0

NS_ASSUME_NONNULL_BEGIN

/// The options that can be used when selecting annotations.
typedef NSString * PSPDFPageViewAnnotationSelectionOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PDFPageView.AnnotationSelectionOption);

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will call the `didSelectAnnotations` and `didDeselectAnnotations` delegate
/// methods for newly selected and deselected annotations. Default: `false`.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionCallDelegateDidMethods;

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will call the `shouldSelectAnnotations` delegate method for newly selected
/// annotations. Default: `false`.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionCallDelegateShouldMethod;

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will select annotations but won't allow them to be moved or resized. This
/// option doesn't modify annotations themselves and it has no effect when
/// deselecting annotations. Default: `false`.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionLockSelection;

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will attempt to present comments for the newly selected annotations. This
/// option has no effect when deselecting annotations. Default: `false`.
///
/// > Note: This option is mutually exclusive with `.presentInspector` and
/// > `.presentMenu` options. If more than one of them is present, all of them
/// > will be ignored.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionPresentComments;

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will attempt to present the inspector for the newly selected annotations.
/// This option has no effect when deselecting annotations. Default: `false`.
///
/// > Note: This option is mutually exclusive with `.presentComments` and
/// > `.presentMenu` options. If more than one of them is present, all of them
/// > will be ignored.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionPresentInspector;

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will attempt to present the menu for newly selected annotations. This option
/// has no effect when deselecting annotations. Default: `false`.
///
/// > Note: This option is mutually exclusive with `.presentComments` and
/// > `.presentInspector` options. If more than one of them is present, all of
/// > them will be ignored.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionPresentMenu;

/// A key for a boolean `NSNumber` value. The value maps directly onto the
/// `PSPDFAnnotationOptionRenderImmediately` option. This option has no effect
/// when deselecting annotations. Default: `false`.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionRenderImmediately;

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will automatically include all annotations in the enclosing group for each
/// newly selected annotation. This option has no effect when deselecting
/// annotations. Default: `false`.
PSPDF_EXTERN PSPDFPageViewAnnotationSelectionOption const PSPDFPageViewAnnotationSelectionOptionResolveGroups;

/// The options that can be used when focusing form elements.
typedef NSString * PSPDFPageViewFormElementSelectionOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PDFPageView.FormElementSelectionOption);

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will call the `didSelectAnnotations` and `didDeselectAnnotations` delegate
/// methods for newly focused form element and any annotations that have been
/// deselected.
PSPDF_EXTERN PSPDFPageViewFormElementSelectionOption const PSPDFPageViewFormElementSelectionOptionCallDelegateDidMethods;

/// A key for a boolean `NSNumber` value. If the value is `true`, the page view
/// will toggle the newly focused form element's value, if it has one. Default:
/// `false`.
PSPDF_EXTERN PSPDFPageViewFormElementSelectionOption const PSPDFPageViewFormElementSelectionOptionToggleValue;

/// The key that identifies special auxiliary view controllers.
typedef NSString * PSPDFPageViewAuxiliaryViewControllerKey NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PDFPageView.AuxiliaryViewControllerKey);

/// A key that identifies the comments view controller.
PSPDF_EXTERN PSPDFPageViewAuxiliaryViewControllerKey const PSPDFPageViewAuxiliaryViewControllerKeyComments;

/// A key that identifies the inspector view controller.
PSPDF_EXTERN PSPDFPageViewAuxiliaryViewControllerKey const PSPDFPageViewAuxiliaryViewControllerKeyInspector;

// Options for `add/removeAnnotation:option:animated:`
// Also see `PSPDFAnnotationOptionAnimateView` in PSPDFAnnotationProvider.h
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionIgnoreOverlayState;
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionRenderImmediately; // add only
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionWaitForNextPageUpdate; // remove only

/// The minimum touch area in screen coordinates
PSPDF_TEST_EXPORT const CGFloat PSPDFScreenHitTestRectSize;

/// Sent out after the spread view changes the frame of one of its page views.
PSPDF_EXTERN NSNotificationName const PSPDFPageViewDidChangeSizeNotification;

/// A block type called after a page update has been completed.
typedef void (^PSPDFPageUpdateBlock)(BOOL);

@interface PSPDFPageView () <PSPDFReusable, PSPDFOverrideProvider, PSPDFTextSelectionViewDataSource, PSPDFDrawViewDataSource, PSPDFResizableViewDataSource>

/*
 readwrite upgrade from the PSPDFReusable protocol. This needs to be set by the
 initialization block in `PSPDFSpreadView`.
 */
@property (nonatomic, copy, nullable) NSString *reuseIdentifier;

/// The document the page view is rendering pages from. Derived from the presentation context if not set.
@property (nonatomic, nullable) PSPDFDocument *document;

/// The parent document view.
@property (nonatomic, readonly, nullable) PSPDFDocumentView *documentView;

/// The parent document view controller.
@property (nonatomic, readonly, nullable) PSPDFDocumentViewController *documentViewController;

/// Allows write access to the current page.
@property (nonatomic) PSPDFPageIndex pageIndex;

/// Returns the page object.
@property (nonatomic, readonly) PSPDFPage *page;

/// Temporarily suspend rendering updates to the renderView.
@property (nonatomic) BOOL suspendUpdate;

/// The bookmark indicator button, if the configuration requires it
@property (nonatomic, nullable) PSPDFBookmarkIndicatorButton *bookmarkIndicatorButton;

/// Timestamp of the last user interaction. Used to determine page focus after rotating device.
@property (nonatomic, readonly) CFTimeInterval lastInteractionTime;

/// Indicates if the page view has loaded annotations (they might be loaded on a background thread)
@property (nonatomic, readonly) BOOL hasLoadedAnnotations;

/// The internal drag and drop handler.
@property (nonatomic, readonly, nullable) PSPDFPageViewDragAndDropHandler *dragAndDropHandler;

/// Interaction object used to allow Scribbling on the entire page.
@property (nonatomic, readonly, nullable) UIIndirectScribbleInteraction *indirectScribbleInteraction;

/// Property used to determine the focused annotation during scribbling.
@property (nonatomic) CGRect lastRequestedScribbleRect;

/// Unique identifier for the current page view used during scribbling.
@property (nonatomic) NSUUID *annotationContainerViewUUID;

/// Updates lastInteractionTime to now.
- (void)markInteraction;

/// Update page view after a small delay. Optionally animated.
- (void)setNeedsUpdateAnimated:(BOOL)animated;

/// Update page view immediately, without enqueueing. Optionally animated.
- (void)updateAnimated:(BOOL)animated;

/// Hides all additional page elements — potentially animated.
- (void)hidePageElementsAnimated:(BOOL)animated;

/// Remove a page annotation/view as soon as the page has been refreshed. Will also refresh page.
- (void)removeViewOnNextPageUpdate:(UIView *)view;

/// Adds a view on the next page update.
- (void)addViewOnNextPageUpdate:(UIView *)view;

/// Executes the provided block on the next page update.
///
/// @param block The block to be executed. `finished` will be false
/// if the block is removed from the page view before the page update
/// completes (e.g., due to pageView resue).
- (void)performBlockOnNextPageUpdate:(PSPDFPageUpdateBlock)block;

/// Returns the first annotation view of the provided class.
/// Queries both annotationContainerView subviews and viewsToBeAdded.
- (nullable UIView *)firstAnnotationViewOfClass:(Class)queriedClass;

/// Will parse the text glyphs async to allow text selection. Override to disable.
- (void)preloadTextParser;

/// Get the shared, private keyboard handler.
@property (nonatomic, readonly, nullable) PSPDFKeyboardHandlingView *keyboardHandler;

/// Set block that is executed within `updateShadow` when `isShadowEnabled = YES`.
@property (nonatomic, copy, nullable) void (^updateShadowBlock)(PSPDFPageView *pageView);

/// Presentation helper to display an alert view while calling the delegates.
- (BOOL)presentAlertController:(PSPDFAlertController *)alertController options:(nullable NSDictionary<NSString *, id> *)options sender:(nullable id)sender animated:(BOOL)animated;

/// Applies the view state to the receiver.
///
/// @param viewState The view state to apply.
/// @note This method currently only applies `PSPDFViewState.selectionState`.
- (void)applyViewState:(PSPDFViewState *)viewState;

/// Views waiting to become visible.
@property (nonatomic, readonly) NSMutableSet<UIView *> *viewsToBeAdded;
@property (nonatomic, readonly) NSMutableSet<UIView *> *viewsToBeRemoved;

/// Shared queue. Exposed for testing teardown.
@property (nonatomic, class, readonly) NSOperationQueue *pageViewQueue;

/// Indicates whether menus should be invoked via the context menu gesture instead of being displayed automatically.
/// Default behaviour: `true` on Mac Catalyst and `false` otherwise.
@property (nonatomic, readonly) BOOL usesContextMenus;

/// Required so we can forward the delegate from the enclosing scroll view.
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset;

/// Required so we can forward the delegate from the enclosing scroll view.
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view;

/// Populates the `contentView` with a page image coming from the cache
/// or from a render request.
- (void)setBackgroundImage:(UIImage *)image animated:(BOOL)animated isPlaceholder:(BOOL)isPlaceholder;

/// The currently selected text rects — if any.
@property (nonatomic, nullable, readonly) NSArray<NSValue *> *selectedRectsInPDFCoordinates;

// MARK: Selecting Annotations

/// Returns annotations that can be tapped at the given location.
///
/// This method will add a variance of a few pixels to the point to make
/// selecting small annotations easier.
///
/// ### Determining Tappable Annotations
///
/// Annotations must be of a known type and must be drawable to be considered
/// tappable.
///
/// If all of the above conditions are met, the following annotations are always
/// tappable, regardless of license features:
///
/// - file, link, note and sound annotations,
/// - annotations with existing comments,
/// - annotations with with trigger event actions.
///
/// If none of the above conditions are met, annotations are only tappable if
/// they are interactive and the license allows interacting with them.
/// Depending on the type of an annotation, one or more of the following license
/// features might be required: Annotation Editing, Forms, Electronic Signatures
/// or Digital Signatures.
///
/// > Note: This method doesn't check the ``PSPDFConfiguration/editableAnnotationTypes``
/// > property. You must further filter the results if you want to take it into
/// > consideration.
///
/// - Parameters:
///     - point: The point in the coordinate space of the page view.
///
/// - Returns: An array of annotations at the given location that pass the
///   criteria of being tappable.
- (NSArray<PSPDFAnnotation *> *)tappableAnnotationsAtPoint:(CGPoint)point;

/// Select or deselect annotations.
///
/// - Parameters:
///     - selectedAnnotations: The new array of selected annotations.
///     - options: Options to consider when selecting or deselecting.
///     - animated: Whether to animate view controller transitions.
- (void)setSelectedAnnotations:(NSArray<PSPDFAnnotation *> *)selectedAnnotations options:(NSDictionary<PSPDFPageViewAnnotationSelectionOption, id> *)options animated:(BOOL)animated;

/// Focus the given form element.
///
/// - Parameters:
///     - formElement: The form element to focus.
///     - options: Options to consider when focusing the form element.
///     - animated: Whether to animate view controller transitions.
- (void)focusFormElement:(PSPDFFormElement *)formElement options:(NSDictionary<PSPDFPageViewFormElementSelectionOption, id> *)options animated:(BOOL)animated;

/// Execute the action of the given link annotation.
///
/// - Parameters:
///     - annotation: The link annotation to open.
- (void)openLinkAnnotation:(PSPDFLinkAnnotation *)annotation NS_SWIFT_NAME(open(linkAnnotation:));

/// Deselect any currently selected annotations, images or text.
///
/// - Parameters:
///     - animated: Whether to animate view controller transitions.
- (void)discardSelectionAnimated:(BOOL)animated;

// MARK: Auxiliary View Controllers

/// Register the given auxiliary view controller to be dismissed next time
/// annotations are deselected. View controllers bound to a selected annotation,
/// such as the annotation inspector or the font picker should be registered
/// this way.
///
/// - Parameters:
///     - viewController: The auxiliary view controller that will be dismissed
///       next time annotations are deselected.
///     - key: The key that identifies the view controller. Passing `nil` means
///       that the view controller isn't any special.
- (void)registerAuxiliaryViewController:(UIViewController *)viewController forKey:(nullable PSPDFPageViewAuxiliaryViewControllerKey)key NS_SWIFT_NAME(registerAuxiliaryViewController(_:for:));

/// A boolean value that indicates whether the page view has registered
/// auxiliary view controllers that are currently presented.
@property (nonatomic, readonly) BOOL hasAuxiliaryViewControllers;

// MARK: Undo and Redo

/// Pending undo recorder for changing annotations using Inspector.
@property (nonatomic, nullable) id<PSPDFPendingUndoRecorder> pendingUndoRecorderForInspector;

/// Pending undo recorder for moving, resizing, adjusting and rotating
/// annotations using `ResizableView`.
@property (nonatomic, nullable) id<PSPDFPendingUndoRecorder> pendingUndoRecorderForResizableView;

// MARK: Measurements

/// The current measurement snapper object used on the page for measurement annotation snapping.
@property (nonatomic, nullable) PSPDFMeasurementSnapper *measurementSnapper;

// MARK: Content Editing

/// The view that contains the actual content editing view. The latter is
/// managed by the view controller's content editing coordinator.
@property (nonatomic, readonly) UIView *contentEditingViewContainer;

/// Instant PDF coordinate space used in the Content Editing Core API.
@property (nonatomic, readonly) id<UICoordinateSpace> instantPdfCoordinateSpace;

@end

@interface PSPDFPageView (Shortcuts)

/// Shortcut to access the textParser corresponding to the current page.
@property (nonatomic, readonly, nullable) PSPDFTextParser *textParser;

/// The document provider in the document corresponding to the page view's page.
@property (nonatomic, readonly, nullable) PSPDFDocumentProvider *documentProvider;

/// The current configuration, queried via the configuration data source.
@property (nonatomic, copy, readonly, nullable) PSPDFConfiguration *configuration;

@end

@interface PSPDFPageView (AnnotationMenuPrivate)

/// The annotation menu interaction attached to this page view.
@property (nonatomic, readonly, nullable) PSPDFAnnotationMenuInteraction *annotationMenuInteraction;

/// The default rect that can be used to anchor the annotation menu and popover
/// presentations. The rect is in the coordinate space of the page view.
- (CGRect)defaultPresentationRectForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// The default presentation options that can be used when presenting view
/// controllers for selected annotations.
- (NSDictionary<PSPDFPresentationOption, id> *)defaultPresentationOptionsForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// A private subclassing hook that makes it possible to customize the menu for
/// link annotations.
///
/// - Parameters:
///     - annotation: The annotation for which the action sheet is presented.
///     - suggestedActions: The default suggested actions.
- (NSArray<UIAction *> *)linkActionSheetActionsForAnnotation:(PSPDFLinkAnnotation *)annotation suggestedActions:(NSArray<UIAction *> *)suggestedActions;

@end

NS_ASSUME_NONNULL_END
