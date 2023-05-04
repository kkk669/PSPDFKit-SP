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
#import <PSPDFKit/PSPDFMacros.h>
#import <PSPDFKitUI/PSPDFAnnotationPresenting.h>
#import <PSPDFKitUI/PSPDFEditMenuAppearance.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFGlyph, PSPDFImageInfo, PSPDFMenuItem, PSPDFPageInfo, PSPDFPageView, PSPDFScrollView;

/// Helper method that will dig into popovers, navigation controllers, container view controllers or other controller view hierarchies and dig out the requested class if found.
PSPDF_EXPORT id _Nullable PSPDFChildViewControllerForClass(UIViewController *_Nullable controller, Class controllerClass);

/// Implement this delegate in your `UIViewController` to get notified of `PDFViewController` events.
PSPDF_PROTOCOL_SWIFT(PDFViewControllerDelegate)
@protocol PSPDFViewControllerDelegate<NSObject>

@optional

// MARK: Document Handling

/// Asks the delegate if the specified document should be saved with the provided options.
///
/// This delegate method is not called if the `Document` being shared has its `annotationSaveMode` set to `disabled`.
///
/// @param pdfController   The PSPDFViewController instance.
/// @param document        The document to save.
/// @param options         The current options that the document is going to be saved with. This is an inout parameter.
///
/// @return BOOL indicating whether the passed document should be saved with the passed parameters.
///
/// @note This method will only be called if the view controller's PSPDFConfiguration autosave option is set to YES, and its annotation save mode is set to a value other than PSPDFAnnotationSaveModeDisabled.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldSaveDocument:(PSPDFDocument *)document withOptions:(NSDictionary<PSPDFDocumentSaveOption, id> * _Nonnull * _Nonnull)options;

/// Notifies the delegate that the specified document's saving operation was completed.
///
/// @param pdfController   The PSPDFViewController instance.
/// @param document        The document that was saved.
/// @param error           The error that occurred during document saving, if any. Can be nil.
///
/// @note This method will only be called if the view controller's PSPDFConfiguration autosave option is set to YES, and its annotation save mode is set to a value other than PSPDFAnnotationSaveModeDisabled.
- (void)pdfViewController:(PSPDFViewController *)pdfController didSaveDocument:(PSPDFDocument *)document error:(nullable NSError *)error;

/// Will be called when an action tries to change the document (For example, a PDF link annotation pointing to another document).
/// Will also be called when the document is changed via using the `document` property.
/// Return NO to block changing the document.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldChangeDocument:(nullable PSPDFDocument *)document;

/// Will be called after the document has been changed.
///
/// @note This will also be called for nil and broken documents. use `document.isValid` to check.
- (void)pdfViewController:(PSPDFViewController *)pdfController didChangeDocument:(nullable PSPDFDocument *)document;

// MARK: Scroll and Page Events

// If you need more scroll events, subclass `PSPDFScrollView` and relay your custom scroll events. Don't forget calling super though.

/// Called when a page view schedules a render task to update its content view.
///
/// Once the render tasks completes, `pdfViewController:didFinishRenderTaskForPageView:`
/// will be called.
///
/// @see pdfViewController:didFinishRenderTaskForPageView:
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that scheduled the render task.
- (void)pdfViewController:(PSPDFViewController *)pdfController willScheduleRenderTaskForPageView:(PSPDFPageView *)pageView;

/// Called when a render task finishes that was scheduled by a page view to update
/// its content view.
///
/// @see pdfViewController:willScheduleRenderTaskForPageView:
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that scheduled the render task.
- (void)pdfViewController:(PSPDFViewController *)pdfController didFinishRenderTaskForPageView:(PSPDFPageView *)pageView;

/// Called when a page view sets an image on its content view. This image can either
/// be a full sized image, a smaller image that is used while waiting for a full
/// sized image, or `nil`. The image might be acquired from the cache or from a render task.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that updated its content view's image.
/// @param placeholder YES if the image set in the content view is just a placeholder
/// while waiting for a full resolution image from the render engine.
/// The placeholder image might also be `nil`.
- (void)pdfViewController:(PSPDFViewController *)pdfController didUpdateContentImageForPageView:(PSPDFPageView *)pageView isPlaceholder:(BOOL)placeholder;

/// Called before a page view enters the visible screen area.
///
/// You can use this method to customize the page view before it is displayed. Say, for example, you’ve built a custom user
/// interface for searching, you can use this method to add the search highlights to the page before it comes on screen.
///
/// This call is bound to the page view’s spread view and will be triggered before the spread view enters the visible
/// screen area. As such, you should _generally avoid_ to begin view animations on the page in this callback:
/// CoreAnimation may skip the animation of off-screen elements.
/// If you want to animate changes to the page’s view hierarchy, have a look at
/// `PSPDFDocumentViewControllerSpreadIndexDidChangeNotification` instead.
///
/// This call will not be invoked for page views belonging to spreads that have
/// an active first responder. This matches the behavior of similar
/// `UICollectionViewDelegate` callbacks.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that is about to enter the visible screen.
/// @param pageIndex The page index of the page that this page view will display.
- (void)pdfViewController:(PSPDFViewController *)pdfController willBeginDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

/// Called when a page view exits the visible screen area.
///
/// This call is bound to the page view's spread view and will be triggered when
/// the spread view leaves the visible screen area.
///
/// This call will not be invoked for page views belonging to spreads that have
/// an active first responder. This matches the behavior of similar
/// `UICollectionViewDelegate` callbacks.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that exits the visible screen.
/// @param pageIndex The page index of the page that this page view has displayed.
- (void)pdfViewController:(PSPDFViewController *)pdfController didEndDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;


/// Called when a page view is configured for the view hierarchy.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that is configured for the view hierarchy.
/// @param pageIndex The page index of the page that this page view will display.
- (void)pdfViewController:(PSPDFViewController *)pdfController didConfigurePageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

/// Called when a page view is cleaned up from the view hierarchy.
///
/// @param pdfController The pdf view controller the page view belongs to.
/// @param pageView The page view that is removed from the view hierarchy.
/// @param pageIndex The page index of the page that this page view has displayed.
- (void)pdfViewController:(PSPDFViewController *)pdfController didCleanupPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

/// Return a PSPDFDocument for a relative path.
/// If this returns nil, we try to find the PDF ourselves with using the current document's `basePath`.
- (nullable PSPDFDocument *)pdfViewController:(PSPDFViewController *)pdfController documentForRelativePath:(NSString *)relativePath;

// MARK: Text Selection

/// Called when text is about to be selected. Return NO to disable text selection.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

/// Called after text has been selected.
/// Will also be called when text has been deselected. Deselection sometimes cannot be stopped, so the `shouldSelectText:` will be skipped.
- (void)pdfViewController:(PSPDFViewController *)pdfController didSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

// MARK: Menu Handling

/// Called before the menu for text selection is displayed.
/// All coordinates are in view coordinate space.
///
/// Using `PSPDFMenuItem` will help with adding custom menu's w/o hacking the responder chain.
/// Default returns menuItems if not implemented. Return nil or an empty array to not show the menu.
///
/// Use `PSPDFMenuItem`’s `identifier` property to check and modify the menu items. This string will not be translated. (vs the title property)
///
/// `rect` is in the coordinate space of the `pageView`.
/// `annotationRect` or `textRect` is in the PDF coordinate space of the current page.
- (NSArray<PSPDFMenuItem *> *)pdfViewController:(PSPDFViewController *)pdfController shouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedText:(NSString *)selectedText inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

/// Called before the menu for a selected image is displayed.
- (NSArray<PSPDFMenuItem *> *)pdfViewController:(PSPDFViewController *)pdfController shouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedImage:(PSPDFImageInfo *)selectedImage inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

// MARK: Annotations

/// Called before an annotation view is created and added to a page. Defaults to YES if not implemented.
///
/// @warning This will only be called for annotations that render as an overlay (that return YES for isOverlay)
/// If NO is returned, viewForAnnotation will not be called.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldDisplayAnnotation:(PSPDFAnnotation *)annotation onPageView:(PSPDFPageView *)pageView;

/// Called when a user taps on an annotation but before PSPDFKit continues
/// handling the touch. This allows the delegate to implement custom behavior
/// that happens just before the annotation becomes selected or form element
/// becomes focused.
///
/// > Note: This method isn't called if a user interacts with annotation views
/// > like the ``PSPDFGalleryView``. See these subclasses for more details, e.g.
/// > ``PSPDFMediaPlayerControllerPlaybackDidStartNotification``.
///
/// - Parameters:
///     - pdfController: The calling view controller.
///     - annotation: The annotation that was tapped.
///     - annotationPoint: The point of touch relative to the annotation, in the
///       PDF coordinate space.
///     - annotationView: The overlay view of the annotation, if any.
///     - pageView: The page view that contains the annotation.
///     - viewPoint: The point of touch in the coordinate space of `pageView`.
///
/// - Returns: A boolean value that, if `true`, cancels PSPDFKit's further
///   touch handling (like selecting an annotation, presenting menus, opening
///   links).
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController didTapOnAnnotation:(PSPDFAnnotation *)annotation annotationPoint:(CGPoint)annotationPoint annotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView pageView:(PSPDFPageView *)pageView viewPoint:(CGPoint)viewPoint NS_SWIFT_NAME(pdfViewController(_:didTapOn:annotationPoint:annotationView:pageView:viewPoint:));

/// Called when annotations are about to become selected.
///
/// This method is called after the `didTapOnAnnotation` method but before the
/// `didSelectAnnotations` and `didDeselectAnnotations` methods. This method
/// isn't called when selecting annotations programmatically.
///
/// - Parameters:
///     - pdfController: The calling view controller.
///     - annotations: The annotations about to become selected.
///     - pageView: The page view that contains the annotations.
///
/// - Returns: An array containing a subset or none of the given annotations.
- (NSArray<PSPDFAnnotation *> *)pdfViewController:(PSPDFViewController *)pdfController shouldSelectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

/// Called after annotations have been selected as a result of direct user
/// interaction on a page view.
///
/// This method is called after the `shouldSelectAnnotations` method but before
/// the `didDeselectAnnotations` method.
///
/// This method isn't called for indirect selections, for example when a
/// newly created annotation is selected, a set of annotations are selected
/// using the selection tool, or an annotation is selected via the list of
/// annotations. It's also not called when selecting the  annotations
/// programmatically. For exact diff tracking, consider implementing the
/// ``PSPDFPageView/didSelectAnnotations:`` and ``PSPDFPageView/didDeselectAnnotations:``
/// subclassing hooks instead.
///
/// - Parameters:
///     - pdfController: The calling view controller.
///     - annotations: The newly selected annotations.
///     - pageView: The page view that contains the annotations.
- (void)pdfViewController:(PSPDFViewController *)pdfController didSelectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

/// Called after an annotation has been deselected by a touch directly on the
/// page view.
///
/// This method is called after the `didSelectAnnotations` method.
///
/// This method isn't called for indirect selections, for example when a
/// newly created annotation is selected, a set of annotations are selected
/// using the selection tool, or an annotation is selected via the list of
/// annotations. It's also not called when selecting the  annotations
/// programmatically. For exact diff tracking, consider implementing the
/// ``PSPDFPageView/didSelectAnnotations:`` and ``PSPDFPageView/didDeselectAnnotations:``
/// subclassing hooks instead.
///
/// - Parameters:
///     - pdfController: The calling view controller.
///     - annotations: The newly selected annotations.
///     - pageView: The page view that contains the annotations.
- (void)pdfViewController:(PSPDFViewController *)pdfController didDeselectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

/// Customization point to modify or replace the view for showing an annotation.
///
/// The default view PSPDFKit would use is passed into this method as `annotationView`. This view
/// can be modified and then returned, or you can return an entirely different view. For custom
/// annotations types, the passed in `annotationView` will be nil. You probably don’t want to return
/// nil from this method because that will result in the annotation disappearing when PSPDFKit tries
/// to put it in the annotation view. If you don’t need any customizations for a particular
/// annotation, return `annotationView` without modifying it.
///
/// To get the targeted rect use `annotation.boundingBox(forPageRect: pageView.bounds)`.
///
/// @param pdfController The PDF view controller displaying the document.
/// @param annotationView The proposed view for displaying the annotation.
/// @param annotation The annotation to be displayed.
/// @param pageView The view for the page the annotation is on.
///
/// @return The view for displaying the annotation.
- (nullable UIView<PSPDFAnnotationPresenting> *)pdfViewController:(PSPDFViewController *)pdfController annotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView forAnnotation:(PSPDFAnnotation *)annotation onPageView:(PSPDFPageView *)pageView;

/// Invoked prior to the presentation of the annotation view: use this to configure actions etc
///
/// @warning This will only be called for annotations that render as an overlay (that return YES for `isOverlay`)
/// `PSPDFLinkAnnotations` are handled differently (they don't have a selected state) - delegate will not be called for those.
- (void)pdfViewController:(PSPDFViewController *)pdfController willShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView onPageView:(PSPDFPageView *)pageView;

/// Invoked after animation used to present the annotation view
///
/// @warning This will only be called for annotations that render as an overlay (that return YES for `isOverlay`)
/// `PSPDFLinkAnnotations` are handled differently (they don't have a selected state) - delegate will not be called for those.
- (void)pdfViewController:(PSPDFViewController *)pdfController didShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView onPageView:(PSPDFPageView *)pageView;

// MARK: View Controller Management

/// Called before we show an internal view controller (color picker, note editor, ...) modally or in a popover. Allows last minute modifications.
///
/// Return NO to process the displaying manually.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldShowController:(UIViewController *)controller options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

/// Called after the controller has been fully displayed.
- (void)pdfViewController:(PSPDFViewController *)pdfController didShowController:(UIViewController *)controller options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

// MARK: General View State

/// Will be called when `viewMode` changes.
- (void)pdfViewController:(PSPDFViewController *)pdfController didChangeViewMode:(PSPDFViewMode)viewMode;

/// Called before the view controller will be dismissed (either by modal dismissal, or popping from the navigation stack).
/// Called before PSPDFKit tries to save any dirty annotation.
///
/// @note If you use child view containment then the dismissal might not be properly detected.
- (void)pdfViewControllerWillDismiss:(PSPDFViewController *)pdfController;

/// Called after the view controller has been dismissed (either by modal dismissal, or popping from the navigation stack).
///
/// @note If you use child view containment then the dismissal might not be properly detected.
- (void)pdfViewControllerDidDismiss:(PSPDFViewController *)pdfController;

// MARK: Display State

/// Called after the view controller changed its controller state or its controller state error.
///
/// @param pdfController   The controller that changed its state.
/// @param controllerState The new state that the controller was changed to.
/// @param error           The underlying error if the controllerState provided is either .error or .locked.
- (void)pdfViewController:(PSPDFViewController *)pdfController didChangeControllerState:(PSPDFControllerState)controllerState error:(nullable NSError *)error;

// MARK: user interface

/// Return NO to stop the user interface change event.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldShowUserInterface:(BOOL)animated;

/// User interface was displayed (called after the animation finishes)
- (void)pdfViewController:(PSPDFViewController *)pdfController didShowUserInterface:(BOOL)animated;

/// Return NO to stop the user interface change event.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldHideUserInterface:(BOOL)animated;

/// User interface was hidden (called after the animation finishes)
- (void)pdfViewController:(PSPDFViewController *)pdfController didHideUserInterface:(BOOL)animated;

// MARK: Actions

/// Called every time before an action will be executed.
/// Actions can come from many sources: Links, Forms, or any other annotation type (via additionalActions)
/// Actions can be invoked on trigger events like PSPDFAnnotationTriggerEventMouseDown.
/// Using the back/forward list will also trigger actions.
///
/// Return NO to prevent the PDF action from being executed.
///
/// @note This is also called for every sub-action the action has.
- (BOOL)pdfViewController:(PSPDFViewController *)pdfController shouldExecuteAction:(PSPDFAction *)action;

/// Called every time after an action has been executed.
///
/// @note This is also called for every sub-action the action has.
- (void)pdfViewController:(PSPDFViewController *)pdfController didExecuteAction:(PSPDFAction *)action;

// MARK: Customizing Menus

/// Allow the delegate to customize the annotation creation menu.
///
/// The view controller will call this method just before the annotation
/// creation menu is presented. This method will not be called before any of the
/// sub-menus are presented.
///
/// If you just want to exclude certain annotation types from appearing in the
/// menu, consider customizing ``PSPDFConfiguration/createAnnotationMenuGroups``
/// configuration property instead.
///
/// ### Backwards Compatibility Considerations
///
/// Historically, there have been multiple ways to customize the annotation
/// creation menu:
///
/// - ``pdfViewController:menuForCreatingAnnotationAtPoint:onPageView:appearance:suggestedMenu:``
///   — this delegate method that allows you to customize the menu directly,
///
/// - ``pdfViewController:shouldShowMenuItems:atSuggestedTargetRect:forAnnotations:inRect:onPageView:``
///   (deprecated) — the legacy equivalent of this method that allowed you to
///   customize the legacy menu items directly,
///
/// - ``PSPDFPageView/menuItemsForNewAnnotationAtPoint:`` (deprecated) – the
///   legacy subclassing hook for ``PSPDFPageView`` subclasses that also allowed
///   you to customize the legacy menu items directly.
///
/// Since the modern menu system based on `UIMenuElement` and `UIMenu` is
/// incompatible with the legacy menu system based on `UIMenuItem` and
/// `UIMenuController`, one of the two will be used, depending on the following
/// circumstances.
///
/// - If this method is implemented, it's treated as an explicit opt into the
///   modern menu system, even if one or more legacy methods are still
///   implemented.
///
/// - If this method is unimplemented but one or more legacy method listed above
///   is, the legacy menu system will be used to preserve backwards
///   compatibility during the deprecation period. Note that the legacy menu
///   system is no longer supported and may exhibit problems on all iOS
///   versions.
///
/// - If none of the methods listed above is implemented, the modern menu system
///   will be used by default.
///
/// To learn more about migrating from the legacy menu system to the modern menu
/// system, check out our PSPDFKit 12 for iOS Migration Guide.
///
/// - Parameters:
///     - sender: The calling view controller.
///     - point: The point at which the menu is about to be presented. This
///       point is in the coordinate space of the `pageView`.
///     - pageView: The page view on which the menu is about to be presented.
///     - appearance: The appearance of the menu that's about to be presented.
///     - suggestedMenu: The suggested menu. Ignoring its children is not
///       recommended, as it might break important functionality, such as
///       copy & paste.
///
/// - Returns: An annotation creation menu. Returning a menu with no children
///   will cancel the annotation creation menu presentation.
- (UIMenu *)pdfViewController:(PSPDFViewController *)sender menuForCreatingAnnotationAtPoint:(CGPoint)point onPageView:(PSPDFPageView *)pageView appearance:(PSPDFEditMenuAppearance)appearance suggestedMenu:(UIMenu *)suggestedMenu NS_SWIFT_NAME(pdfViewController(_:menuForCreatingAnnotationAt:onPageView:appearance:suggestedMenu:));

/// Allow the delegate to customize the annotation menu.
///
/// The view controller will call this method just before the annotation
/// menu is presented. This method will not be called before any of the
/// sub-menus are presented.
///
/// If you want to customize the choices for different style properties,
/// consider customizing ``PSPDFConfiguration/annotationMenuConfiguration``
/// configuration property instead.
///
/// > Important: Customizing the annotation menu requires _Annotation Editing_
/// > feature to be enabled for your license (or the _Electronic Signatures_
/// > feature when customizing the menu for signature annotations). Even though
/// > the menu might be presented for certain types of annotations without
/// > either of these features enabled, customizing it isn't possible in this
/// > situation.
///
/// ### Backwards Compatibility Considerations
///
/// Historically, there have been multiple ways to customize the annotation
/// menu:
///
/// - ``pdfViewController:menuForAnnotations:onPageView:appearance:suggestedMenu:``
///   — this delegate method that allows you to customize the menu directly,
///
/// - ``pdfViewController:shouldShowMenuItems:atSuggestedTargetRect:forAnnotations:inRect:onPageView:``
///   (deprecated) — the legacy equivalent of this method that allowed you to
///   customize the legacy menu items directly,
///
/// - ``PSPDFPageView/menuItemsForAnnotations:`` (deprecated) — the legacy
///   subclassing hook for ``PSPDFPageView`` subclasses that also allowed
///   you to customize the legacy menu items directly,
///
/// - ``PSPDFPageView/colorMenuItemsForAnnotation:`` (deprecated) — the legacy
///   subclassing hook for ``PSPDFPageView`` subclasses that allowed you to
///   customize the legacy menu items for choosing color,
///
/// - ``PSPDFPageView/fillColorMenuItemsForAnnotation:`` (deprecated) — the
///   legacy subclassing hook for ``PSPDFPageView`` subclasses that allowed you
///   to customize the legacy menu items for choosing fill color,
///
/// - ``PSPDFPageView/opacityMenuItemForAnnotation:withColor:`` (deprecated)
///   — the legacy subclassing hook for ``PSPDFPageView`` subclasses that
///   allowed you to customize the legacy menu item for choosing opacity,
///
/// - ``PSPDFPageView/defaultColorOptionsForAnnotationType:`` (deprecated) — the
///   legacy subclassing hook for ``PSPDFPageView`` subclasses that allowed you
///   to customize the color choices,
///
/// - ``PSPDFPageView/availableFontSizes`` (deprecated) — the legacy subclassing
///   hook for ``PSPDFPageView`` subclasses that allowed you to customize the
///   font size choices,
///
/// - ``PSPDFPageView/availableLineWidths`` (deprecated) — the legacy
///   subclassing hook for ``PSPDFPageView`` subclasses that allowed you to
///   customize the line width choices,
///
/// - ``PSPDFPageView/shouldMoveStyleMenuEntriesIntoSubmenu`` (deprecated) — the
///   legacy subclassing hook for ``PSPDFPageView`` subclasses that allowed you
///   to customize the appearance of the _Style_ menu.
///
/// Since the modern menu system based on `UIMenuElement` and `UIMenu` is
/// incompatible with the legacy menu system based on `UIMenuItem` and
/// `UIMenuController`, one of the two will be used, depending on the following
/// circumstances.
///
/// - If this method is implemented, it's treated as an explicit opt into the
///   modern menu system, even if one or more legacy methods are still
///   implemented.
///
/// - If this method is unimplemented but one or more legacy method listed above
///   is, the legacy menu system will be used to preserve backwards
///   compatibility during the deprecation period. Note that the legacy menu
///   system is no longer supported and may exhibit problems on all iOS
///   versions.
///
/// - If none of the methods listed above is implemented, the modern menu system
///   will be used by default.
///
/// To learn more about migrating from the legacy menu system to the modern menu
/// system, check out our PSPDFKit 12 for iOS Migration Guide.
///
/// - Parameters:
///     - sender: The calling view controller.
///     - annotations: The array of annotations for which the menu is about to
///       be presented. This array will always contain at least one element.
///     - pageView: The page view on which the menu is about to be presented.
///     - appearance: The appearance of the menu that's about to be presented.
///     - suggestedMenu: The suggested menu. Ignoring its children is not
///       recommended, as it might break important functionality.
///
/// - Returns: An annotation menu. Returning a menu with no children will
///   cancel the annotation menu presentation.
- (UIMenu *)pdfViewController:(PSPDFViewController *)sender menuForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView appearance:(PSPDFEditMenuAppearance)appearance suggestedMenu:(UIMenu *)suggestedMenu NS_SWIFT_NAME(pdfViewController(_:menuForAnnotations:onPageView:appearance:suggestedMenu:));

// MARK: Deprecated

/// Allow the delegate to customize the legacy annotation creation or edit menu.
///
/// The view controller will call this method just before the legacy annotation
/// creation or edit menu is about to be presented. This method will also be
/// called as you dig into the sub-menus like color options.
///
/// - Warning: This delegate method is deprecated in favor of the more modern
///   ``pdfViewController:menuForCreatingAnnotationAtPoint:onPageView:appearance:suggestedMenu:``
///   and ``pdfViewController:menuForAnnotations:onPageView:appearance:suggestedMenu:``
///   equivalents. See the documentation of these method to learn more about
///   backwards compatibility considerations.
///
/// - Parameters:
///     - pdfController: The calling view controller.
///     - menuItems: The array of suggested menu items.
///     - rect: The rect in which the menu is about to be presented. This rect
///       is in the coordinate space of `pageView`.
///     - annotations: The array of annotations for which the edit menu is about
///       to be presented, or `nil` if this method is being called for the
///       annotation creation menu.
///     - annotationRect: The rect containing all `annotations` or `.null` if
///       this method is being called for the annotation creation menu. This
///       rect is in the PDF coordinate space.
///     - pageView: The page view on which the menu is about to be presented.
///
/// - Returns: An array of menu items for the legacy annotation creation or edit
///   menu. Returning an empty array will cancel the menu presentation.
- (NSArray<PSPDFMenuItem *> *)pdfViewController:(PSPDFViewController *)pdfController shouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forAnnotations:(nullable NSArray<PSPDFAnnotation *> *)annotations inRect:(CGRect)annotationRect onPageView:(PSPDFPageView *)pageView PSPDF_DEPRECATED(12, "Use 'pdfViewController(_:menuForAnnotations:onPageView:appearance:suggestedMenu:)' or 'pdfViewController(_:menuForCreatingAnnotationAt:onPageView:appearance:suggestedMenu:)' instead.");

@end

NS_ASSUME_NONNULL_END
