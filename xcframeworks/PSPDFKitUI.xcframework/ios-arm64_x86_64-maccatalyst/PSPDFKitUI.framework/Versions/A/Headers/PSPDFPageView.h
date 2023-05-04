//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFDocument+DataDetection.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFRenderTask.h>
#import <PSPDFKitUI/PSPDFRelayTouchesView.h>
#import <PSPDFKitUI/PSPDFResizableView.h>

@class PSPDFAnnotation;
@class PSPDFFormElement;
@class PSPDFPageInfo;
@class PSPDFRenderStatusView;
@class PSPDFTextSelectionView;
@protocol PSPDFAnnotationPresenting;
@protocol PSPDFPresentationContext;

NS_ASSUME_NONNULL_BEGIN

PSPDF_CLASS_SWIFT(AnnotationContainerView)
@interface PSPDFAnnotationContainerView : PSPDFRelayTouchesView<PSPDFOverridable>
@end

/// Notification is fired when the `selectedAnnotations` value changed.
/// `object` is the pageView.
PSPDF_EXPORT NSNotificationName const PSPDFPageViewSelectedAnnotationsDidChangeNotification;

/// The name of the notification that is fired when a newly created annotation is inserted.
///
/// @note This notification does not have a sender (`object == nil`).
PSPDF_EXPORT NSNotificationName const PSPDFAnnotationCreateActionDidInsertNotification;

/// The key, in `PSPDFAnnotationCreateActionDidInsertNotification`'s userInfo, that is used to store the
/// array of inserted annotations.
PSPDF_EXPORT NSString * const PSPDFAnnotationCreateActionInsertedAnnotationsKey;

/// Display a single PDF page. View is reused.
/// You can add your own views on top of the `annotationContainerView` (e.g. custom annotations)
/// Events from a attached `UIScrollView` will be relayed to all visible `PDFPageView` classes.
PSPDF_CLASS_SWIFT(PDFPageView)
@interface PSPDFPageView : UIView<PSPDFRenderTaskDelegate, PSPDFResizableViewDelegate, PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

// MARK: Show / Destroy a document

/// The attached presentation context.
@property (nonatomic, weak, readonly) id<PSPDFPresentationContext> presentationContext;

/// Prepares the `PDFPageView` for reuse. Removes all unknown internal `UIViews`.
- (void)prepareForReuse NS_REQUIRES_SUPER;

// MARK: Internal views and rendering

/// Redraw the `renderView` (dynamically rendered PDF for maximum sharpness, updated on every zoom level.)
- (void)updateRenderView NS_REQUIRES_SUPER;

/// Redraw `renderView` and `contentView`.
- (void)updateView NS_REQUIRES_SUPER;

/// Call whenever you change which annotations should be rendered.
/// Updates overlay annotations and will remove any annotation selection.
/// In most cases this should be called in combination with `updateView`.
- (void)updateAnnotationViewsAnimated:(BOOL)animated;

/// Returns the existing subview used to display the given annotation — if any.
///
/// This method will neither trigger loading annotations, nor create and insert a view for the given
/// annotation. In addition, it will not return views that are scheduled to be removed.
///
/// @note Unless they are currently selected, most annotations are rendered into the page. Whether or
/// not a separate view will be used to display an annotation is controlled through its `isOverlay`
/// property.
/// In other words: This method always returns nil for annotations that return `false` from `isOverlay`
/// and are not selected.
- (nullable UIView<PSPDFAnnotationPresenting> *)annotationViewForAnnotation:(PSPDFAnnotation *)annotation;

/// UIImageView displaying the whole document.
@property (nonatomic, readonly) UIImageView *contentView;

/// UIImageView for the zoomed in state.
@property (nonatomic, readonly) UIImageView *renderView;

/// Container view for all overlay annotations.
///
/// This is just a named subclass of `UIView` that will always track the frame of the `PDFPageView`.
/// It's useful to coordinate this with your own subviews to get the zIndex right.
///
/// @warning Most annotations will not be rendered as overlays or only when they are currently being selected.
/// Rendering annotations within the pageView has several advantages including performance or view color multiplication (in case of highlight annotations)
/// The contents of this view are managed. Additional subviews can be added, but they will be removed during page reuse. Subviews should respond to the `PSPDFAnnotationPresenting`, especially the annotation method.
@property (nonatomic, readonly) PSPDFAnnotationContainerView *annotationContainerView;

/// Access the selectionView. (handles text selection)
@property (nonatomic, readonly) PSPDFTextSelectionView *selectionView;

/// Access the render status view that is displayed on top of a page while we are rendering.
@property (nonatomic) PSPDFRenderStatusView *renderStatusView;

/// Top right offset. Defaults to 30.
@property (nonatomic) CGFloat renderStatusViewOffset;

/// The PDF scale the current page is rendered with.
@property (nonatomic, readonly) CGFloat PDFScale;

/// Current CGRect of the part of the page that's visible. Screen coordinate space.
///
/// @note If the scroll view is currently decelerating, this will show the TARGET rect, not the one that's currently animating.
@property (nonatomic, readonly) CGRect visibleRect;

/// Color used to indicate link or form objects.
@property (nonatomic) UIColor *highlightColor UI_APPEARANCE_SELECTOR;

/// The color displayed on the page view before the PDF page is rendered.
///
/// By default (assigned `nil` value), this value will be the best guess for the
/// page background color, given the current render options (such as `backgroundFill`
/// or `invertRenderColor`).
///
/// This property is intended to be customized via `-[PSPDFViewControllerDelegate pdfViewController:didConfigurePageView:forPageAtIndex:]`,
/// `UIAppearance` or by subclassing this class.
@property (nonatomic, null_resettable) UIColor *placeholderColor UI_APPEARANCE_SELECTOR;

// MARK: Coordinate calculations and object fetching

/// The normalized PDF coordinate space of this view’s page. The origin of the space is the bottom-left corner of the displayed content.
///
/// Use this property together with the methods in the `UICoordinateSpace` protocol to convert between PDF page and view coordinate spaces.
/// For example to find the location of a `UITouch` in a page’s PDF coordinate space:
///
/// ```
/// let viewPoint = touch.location(in: pageView)
/// let pdfPoint = pageView.convert(viewPoint, to: pageView.pdfCoordinateSpace)
/// ```
///
/// @note **Important:** Rectangles converted with this coordinate space must be well–formed!
/// Do not, for example, try to convert something with a less–than–zero width…
///
/// Read more in our Coordinate Space Conversions guide at https://pspdfkit.com/guides/ios/faq/coordinate-spaces/
@property (nonatomic, readonly) id<UICoordinateSpace> pdfCoordinateSpace;

/// Get the glyphs/words on a specific page.
- (NSDictionary<PSPDFObjectFinderType, id> *)objectsAtPoint:(CGPoint)viewPoint options:(nullable NSDictionary<PSPDFObjectFinderOption, NSValue *> *)options;

/// Get the glyphs/words on a specific rect.
/// Usage e.g. `NSDictionary *objects = [pageView objectsAtRect:rect options:@{PSPDFObjectFinderOptionExtractWords: @ YES}]`;
- (NSDictionary<PSPDFObjectFinderType, id> *)objectsAtRect:(CGRect)viewRect options:(nullable NSDictionary<PSPDFObjectFinderOption, NSValue *> *)options;

// MARK: Accessors

/// Access the `UIScrollView` that is responsible for zooming this page view if available.
@property (nonatomic, readonly, nullable) UIScrollView *zoomView;

/// Returns an array of `UIView` `PSPDFAnnotationPresenting` objects currently in the view hierarchy.
@property (nonatomic, readonly) NSArray<UIView<PSPDFAnnotationPresenting> *> *visibleAnnotationViews;

/// Page that is displayed. Readonly.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

/// Shortcut to access the current page info of the set page.
@property (nonatomic, readonly, nullable) PSPDFPageInfo *pageInfo;

// MARK: Selecting Annotations

/// View for the selected annotation. Created and destroyed on the fly.
@property (nonatomic, readonly, nullable) PSPDFResizableView *annotationSelectionView;

/// The array of currently selected annotations and focused form elements on the
/// page view.
///
/// Setting this property is equivalent to calling the ``selectAnnotations:presentMenu:animated:``
/// method with `false` for both `presentMenu` and `animated` parameters.
///
/// > Note: Selecting annotations requires the _Annotation Editing_ feature
/// > to be enabled for your license (or the _Electronic Signatures_ feature
/// > when selecting just signature annotations). Otherwise, only annotations
/// > with underlying content (such as sounds, files, notes and annotations with
/// > comments) can be selected.
@property (nonatomic, copy, null_resettable) NSArray<PSPDFAnnotation *> *selectedAnnotations;

/// Select the given annotations as a result of user interaction and optionally
/// present the menu for them.
///
/// > Note: Selecting annotations requires the _Annotation Editing_ feature
/// > to be enabled for your license (or the _Electronic Signatures_ feature
/// > when selecting just signature annotations). Otherwise, only annotations
/// > with underlying content (such as sounds, files, notes and annotations with
/// > comments) can be selected.
///
/// > Important: Calling this method will discard any previous annotation or
/// > content selection on this page view.
///
/// - Parameters:
///     - annotations: The annotations to select.
///     - presentMenu: A boolean value that indicates whether the annotation
///       menu should be presented along with selection. This value will be
///       ignored if presenting menu for the given selected annotations is not
///       possible.
///     - animated: Whether to animate view controller transitions.
- (void)selectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations presentMenu:(BOOL)presentMenu animated:(BOOL)animated NS_SWIFT_NAME(select(annotations:presentMenu:animated:));

/// Focus the given form element. This will discard any previous selection on
/// this page view.
///
/// > Note: Focusing form elements requires the _Forms_ feature to be enabled
/// > for your license. Otherwise, calling this method will have no effect.
///
/// > Important: Calling this method will discard any previous annotation or
/// > content selection on this page view.
///
/// - Parameters:
///     - formElement: The form element to focus.
///     - toggleValue: Whether the value of the form element should be toggled
///       if possible.
///     - animated: Whether to animate view controller transitions.
- (void)focusFormElement:(PSPDFFormElement *)formElement toggleValue:(BOOL)toggleValue animated:(BOOL)animated NS_SWIFT_NAME(focus(formElement:toggleValue:animated:));

// MARK: Deprecated

/// Select the given annotation or focus the given form element.
///
/// > Warning: This method is deprecated. To select annotations, use the
/// > ``selectAnnotations:presentMenu:animated:`` method instead. To focus form
/// > elements, use the ``focusFormElement:toggleValue:animated:`` method
/// > instead.
///
/// - Parameters:
///     - annotation: The annotation to select or form element to focus.
///     - animated: Whether to animate view controller transitions.
- (void)selectAnnotation:(PSPDFAnnotation *)annotation animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'select(annotations:presentMenu:animated:)' or 'focus(formElement:toggleValue:animated:)' instead.");

@end

/// Extensions to handle annotations.
@interface PSPDFPageView (AnnotationViews)

/// Associate an annotation with an annotation view
- (void)setAnnotation:(PSPDFAnnotation *)annotation forAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

/// Recall the annotation associated with an annotation view
- (nullable PSPDFAnnotation *)annotationForAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

/// Add an `annotation` to the current pageView.
/// This will either queue a re-render of the PDF, or add an `UIView` subclass for the matching annotation,
/// depending on the annotation type and the value of `isOverlay`.
///
/// @note In PSPDFKit, annotations are managed in two ways:
///
/// 1) Annotations that are fixed and rendered with the page image.
/// Those annotations are `PSPDFHighlightAnnotation`, `PSPDFSquareAnnotation`, `PSPDFInkAnnotation` and more.
/// Pretty much all more or less "static" annotations are handled this way.
///
/// 2) Then, there are the more dynamic annotations like `PSPDFLinkAnnotation` and `PSPDFNoteAnnotation`.
/// Those annotations are not part of the rendered image but are actual subviews in `PDFPageView`.
/// Those annotations return YES on the isOverlay property.
///
/// This method is called recursively with all annotation types except if they return isOverlay = NO. In case of isOverlay = NO, it will call updateView to re-render the page.
///
/// @warning This will not change anything on the data model below. Also add an annotation to the document object.
- (void)addAnnotation:(PSPDFAnnotation *)annotation options:(nullable NSDictionary<NSString *, NSNumber *> *)options animated:(BOOL)animated;

/// Removes an `annotation` from the view, either by re-rendering the page image or removing a matching UIView-subclass of the annotation was added as an overlay.
///
/// @note This will not change the data model of the document.
- (BOOL)removeAnnotation:(PSPDFAnnotation *)annotation options:(nullable NSDictionary<NSString *, NSNumber *> *)options animated:(BOOL)animated;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFPageView (SubclassingHooks)

// MARK: Shadow settings

/// Subclass to change shadow behavior.
- (void)updateShadowAnimated:(BOOL)animated;

/// Used to expand the tap point to make tapping objects easier. By default the
/// rect has a size of 30 pixels.
- (CGRect)hitTestRectForPoint:(CGPoint)viewPoint;

/// Called with the set of annotations that are now selected.
/// Can be used to post-process annotations or enforce user changes.
- (void)didSelectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations NS_REQUIRES_SUPER;

/// Called with the set of annotations that were selected, but are no longer.
/// Can be used to post-process annotations or enforce user changes.
- (void)didDeselectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations NS_REQUIRES_SUPER;

/// Get annotation rect (PDF coordinate space)
- (CGRect)rectForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Render options that are used for the live-page rendering. (not for the cache)
/// One way to use this would be to customize what annotations types will be rendered with the pdf.
/// See `PSPDFRenderOptions` for a list of options.
- (PSPDFRenderOptions *)renderOptionsWithZoomScale:(CGFloat)zoomScale animated:(BOOL)animated;

/// Helper to properly place an annotation.
- (void)centerAnnotation:(PSPDFAnnotation *)annotation aroundPDFPoint:(CGPoint)pdfPoint;

/// Load page annotations from the PDF.
- (void)loadPageAnnotationsAnimated:(BOOL)animated blockWhileParsing:(BOOL)blockWhileParsing;

/// Computes a scale value suitable for computation of the line width to use during drawing and selection.
@property (nonatomic, readonly) CGFloat scaleForPageView;

/// Change notification processing.
- (void)annotationsAddedNotification:(NSNotification *)notification NS_REQUIRES_SUPER;
- (void)annotationsRemovedNotification:(NSNotification *)notification NS_REQUIRES_SUPER;
- (void)annotationChangedNotification:(NSNotification *)notification NS_REQUIRES_SUPER;

/// Customize if the `annotation` object should also transform the properties.
- (BOOL)shouldScaleAnnotationWhenResizing:(PSPDFAnnotation *)annotation usesResizeKnob:(BOOL)usesResizeKnob;

/// Customize annotation selection view.
- (void)updateAnnotationSelectionView;

@end

NS_ASSUME_NONNULL_END
