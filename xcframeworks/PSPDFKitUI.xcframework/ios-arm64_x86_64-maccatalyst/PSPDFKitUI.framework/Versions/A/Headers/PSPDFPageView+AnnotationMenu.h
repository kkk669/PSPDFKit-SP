//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFPageView.h>

#import <PSPDFKitUI/PSPDFAnnotationStyleViewController.h>
#import <PSPDFKitUI/PSPDFControlDelegate.h>
#import <PSPDFKitUI/PSPDFFontPickerViewController.h>
#import <PSPDFKitUI/PSPDFLinkAnnotationEditingContainerViewController.h>
#import <PSPDFKitUI/PSPDFNoteAnnotationViewController.h>
#import <PSPDFKitUI/PSPDFSignedFormElementViewController.h>
#import <PSPDFKitUI/PSPDFTextSelectionView.h>

@class PSPDFFreeTextAnnotation;
@class PSPDFLinkAnnotation;
@class PSPDFMenuItem;
@class PSPDFSignatureFormElement;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFPageView (AnnotationMenu) <
    PSPDFAnnotationStyleViewControllerDelegate,
    PSPDFFontPickerViewControllerDelegate,
    PSPDFLinkAnnotationEditingContainerViewControllerDelegate,
    PSPDFNoteAnnotationViewControllerDelegate,
    PSPDFSignedFormElementViewControllerDelegate,
    PSPDFSignedFormElementViewControllerDelegate,
    PSPDFTextSelectionViewDelegate
>

/// Returns a menu item, that is used for creating a new annotation from the current text selection.
///
/// @note Only supports highlight, underline, squiggly, strike out, redaction, and link annotation types.
/// @note Requires the Redaction license feature when passing `PSPDFAnnotationStringRedaction`, returns `nil` otherwise.
- (nullable PSPDFMenuItem *)textSelectionMenuItemForCreatingAnnotationWithType:(PSPDFAnnotationString)annotationString;

/// Show the signature controller.
- (void)showSignatureControllerAtRect:(CGRect)viewRect withTitle:(nullable NSString *)title signatureFormElement:(nullable PSPDFSignatureFormElement *)signatureFormElement options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options animated:(BOOL)animated;

/// Show signature menu.
- (void)showNewSignatureMenuAtRect:(CGRect)viewRect signatureFormElement:(nullable PSPDFSignatureFormElement *)signatureFormElement options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options animated:(BOOL)animated;

/// Show digital signature menu.
/// Only shown when `signatureField` is signed already.
- (BOOL)showDigitalSignatureMenuForSignatureField:(PSPDFSignatureFormElement *)signatureField animated:(BOOL)animated;

/// Show menu if annotation/text is selected.
- (void)showMenuIfSelectedAnimated:(BOOL)animated;
- (void)showMenuIfSelectedWithOption:(PSPDFContextMenuOption)contextMenuOption animated:(BOOL)animated;

/// Shows a menu as appropriate for a context menu invocation at the given location.
- (void)showMenuForPoint:(CGPoint)location animated:(BOOL)animated;

/// The method that checks if the receiver can create annotations, optionally showing a message with the `PSPDFStatusHUD`.
///
/// @param showMessage Specifies whether a message should be displayed if annotations cannot be created.
/// @return `true` if annotations can be created, else `false`.
- (BOOL)canCreateAnnotationsShowMessage:(BOOL)showMessage;

// MARK: Deprecated

/// Attempt to present the legacy menu for creating an annotation at the given
/// location.
///
/// > Warning: This method is deprecated. To present the annotation creation
/// > menu programmatically, use the ``PSPDFDocumentViewInteractions/tryToShowAnnotationMenuAtPoint:inCoordinateSpace:``
/// > method.
///
/// - Parameters:
///     - viewPoint: The point in page view's coordinate space.
///     - animated: Whether the presentation should be animated. Starting from
///       PSPDFKit 12 for iOS, this parameter is ignored as the presentation is
///       always animated.
///
/// - Returns: A boolean value indicating whether the presentation succeeded.
- (BOOL)showAnnotationMenuAtPoint:(CGPoint)viewPoint animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'PDFViewController.interactions.tryToShowAnnotationMenu(at:in:)' instead.");

/// Attempt to present a legacy menu for the given annotations.
///
/// When calling this method on iPad for a single note annotation, this method
/// will present the comments view controller instead.
///
/// > Warning: This method is deprecated. To programmatically present the menu
/// > for selected annotations, use the ``selectAnnotations:presentMenu:animated:``
/// > method.
///
/// - Parameters:
///     - annotations: The array of annotations to show the menu for.
///     - targetRect: The rect from which the menu should be shown in the
///       coordinate space of the page view. Starting from PSPDFKit 12 for iOS,
///       this parameter is ignored and the rect is calculated automatically.
///     - animated: Whether to animate view controller transitions.
- (void)showMenuForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations targetRect:(CGRect)targetRect option:(PSPDFContextMenuOption)contextMenuOption animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'select(annotations:presentMenu:animated:)' instead.");

/// Attempt to present a legacy menu for choosing a color for an annotation.
///
/// > Warning: This method is deprecated. The color menu is now a child of the
/// > annotation menu. To present a color choice menu that's detached from the
/// > annotation menu, use your own `UIEditMenuInteraction` or `UIMenuController`.
///
/// - Parameters:
///     - annotation: The annotation for which to present a legacy menu.
///     - isFillColor: Whether the `fillColor` property should be set instead of
///       the `color` property.
- (void)selectColorForAnnotation:(PSPDFAnnotation *)annotation isFillColor:(BOOL)isFillColor PSPDF_DEPRECATED(12, "Use 'presentColorPicker(for:property:options:animated:completion:)' instead.");

/// Check if the annotation inspector should be used for the given annotations.
///
/// > Warning: This method is deprecated. To check if the annotation inspector
/// > can be presented for a given array of annotations, use the
/// > ``canPresentInspectorForAnnotations:`` method.
- (BOOL)useAnnotationInspectorForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations PSPDF_DEPRECATED(12, "Use 'canPresentInspector(for:)' instead.");

/// Present the annotation inspector for the given annotations.
///
/// > Warning: This method is deprecated. To present the annotation inspector,
/// > use the ``presentInspectorForAnnotations:options:animated:completion:``
/// > method.
///
/// - Parameters:
///     - annotations: The array of annotations to inspect.
///     - options: The presentation options.
///     - animated: Whether to animate the presentation.
///
/// - Returns: An instance of the annotation inspector view controller or `nil`
///   if the annotation inspector couldn't be presented for the given
///   annotations.
- (nullable PSPDFAnnotationStyleViewController *)showInspectorForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'presentInspector(for:options:animated:completion:)' instead.");

/// Present comments for the given annotation.
///
/// > Warning: This method is deprecated. To present comments for an annotation,
/// > use the ``presentCommentsForAnnotation:options:animated:completion:``
/// > method.
///
/// - Parameters:
///     - annotation: The annotation to present comments for.
///     - animated: Whether to animate the presentation.
- (void)showNoteControllerForAnnotation:(PSPDFAnnotation *)annotation animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'presentComments(for:options:animated:completion:)' instead.");

/// Present the color picker for the given annotation.
///
/// > Warning: This method is deprecated. To present a color picker for an
/// > annotation, use the ``presentColorPickerForAnnotation:property:options:animated:completion:``
/// > method.
///
/// - Parameters:
///     - annotation: The annotation to modify.
///     - animated: Whether to animate the presentation.
- (void)showColorPickerForAnnotation:(PSPDFAnnotation *)annotation animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'presentColorPicker(for:property:options:animated:completion:)' instead.");

/// Present the font picker for the given free text annotation.
///
/// > Warning: This method is deprecated. To present the font picker for a
/// > free text annotation, use the ``presentFontPickerForAnnotation:options:animated:completion``
/// > method.
///
/// - Parameters:
///     - annotation: The free text annotation to modify.
///     - animated: Whether to animate the presentation.
- (void)showFontPickerForAnnotation:(PSPDFFreeTextAnnotation *)annotation animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'presentFontPicker(for:options:animated:completion:)' instead.");

/// Present the link menu for the given link annotation.
///
/// > Warning: This method is deprecated. To present the action sheet for a link
/// > annotation, use ``presentLinkActionSheetForAnnotation:options:animated:completion:``
/// > method.
///
/// - Parameters:
///     - annotation: The link annotation to present the menu for.
///     - viewRect: The rect from which the action sheet should be presented in
///       the coordinate space of the page view.
///     - animated: Whether to animate the presentation.
///
/// - Returns: A boolean value that indicates whether the link menu was
///   successfully presented.
- (BOOL)showLinkPreviewActionSheetForAnnotation:(PSPDFLinkAnnotation *)annotation fromRect:(CGRect)viewRect animated:(BOOL)animated PSPDF_DEPRECATED(12, "Use 'presentLinkActionSheet(for:options:animated:completion:)' instead.");

/// Returns an array of menu items used for the legacy annotation creation
/// menu.
///
/// > Warning: This method is deprecated. To customize the annotation creation
/// > menu directly, use the ``PSPDFViewControllerDelegate/pdfViewController:menuForCreatingAnnotationAtPoint:onPageView:appearance:suggestedMenu:``
/// > delegate method. See the documentation of that method to learn more about
/// > backwards compatibility considerations.
///
/// - Parameters:
///     - point: The point in page view's coordinate space.
///
/// - Returns: An array of menu items used for the legacy annotation creation
///   menu.
- (NSArray<PSPDFMenuItem *> *)menuItemsForNewAnnotationAtPoint:(CGPoint)point PSPDF_DEPRECATED(12, "Use 'PDFConfiguration.createAnnotationMenuGroups' or 'PDFViewControllerDelegate.pdfViewController(_:menuForCreatingAnnotationAt:onPageView:appearance:suggestedMenu:)' instead.");

/// Returns an array of menu items used in the legacy annotation menu.
///
/// > Warning: This method is deprecated. To customize the annotation menu
/// > directly, use ``PSPDFViewControllerDelegate/pdfViewController:menuForAnnotations:onPageView:appearance:suggestedMenu:``
/// > delegate method. See the documentation of this method to learn more about
/// > backwards compatibility considerations.
///
/// - Parameters:
///     - annotations: The annotations for which to return menu items.
///
/// - Returns: An array of menu items used in the legacy annotation menu.
- (NSArray<PSPDFMenuItem *> *)menuItemsForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations PSPDF_DEPRECATED(12, "Use 'PDFViewControllerDelegate.pdfViewController(_:menuForAnnotations:onPageView:appearance:suggestedMenu:)' instead.");

/// Returns an array of menu items used in the legacy annotation menu to change
/// the color of an annotation.
///
/// > Warning: This method is deprecated. To customize the color choices
/// > available in the annotation menu, use the ``PSPDFConfiguration/annotationMenuConfiguration``
/// > configuration property. To customize the annotation menu directly, use the
/// > ``PSPDFViewControllerDelegate/pdfViewController:menuForAnnotations:onPageView:appearance:suggestedMenu:``
/// > delegate method.
///
/// - Parameters:
///     - annotation: The annotation for which to return menu items.
///
/// - Returns: An array of menu items used in the legacy annotation menu.
- (NSArray<PSPDFMenuItem *> *)colorMenuItemsForAnnotation:(PSPDFAnnotation *)annotation PSPDF_DEPRECATED(12, "Use 'PDFConfiguration.annotationMenuConfiguration.colorChoices' or 'PDFViewControllerDelegate.pdfViewController(_:menuForAnnotations:onPageView:appearance:suggestedMenu:)' instead.");

/// Returns an array of menu items used in the legacy annotation menu to change
/// the fill color of an annotation.
///
/// > Warning: This method is deprecated. To customize the fill color choices
/// > available in the annotation menu, use the ``PSPDFConfiguration/annotationMenuConfiguration``
/// > configuration property. To customize the annotation menu directly, use the
/// > ``PSPDFViewControllerDelegate/pdfViewController:menuForAnnotations:onPageView:appearance:suggestedMenu:``
/// > delegate method.
///
/// - Parameters:
///     - annotation: The annotation for which to return menu items.
///
/// - Returns: An array of menu items used in the legacy annotation menu.
- (NSArray<PSPDFMenuItem *> *)fillColorMenuItemsForAnnotation:(PSPDFAnnotation *)annotation PSPDF_DEPRECATED(12, "Use 'PDFConfiguration.annotationMenuConfiguration.colorChoices' or 'PDFViewControllerDelegate.pdfViewController(_:menuForAnnotations:onPageView:appearance:suggestedMenu:)' instead.");

/// Returns a menu item used in the legacy annotation menu to change the opacity
/// of an annotation.
///
/// > Warning: This method is deprecated. To customize the opacity choices
/// > available in the annotation menu, use the ``PSPDFConfiguration/annotationMenuConfiguration``
/// > configuration property. To customize the annotation menu directly, use the
/// > ``PSPDFViewControllerDelegate/pdfViewController:menuForAnnotations:onPageView:appearance:suggestedMenu:``
/// > delegate method.
///
/// - Parameters:
///     - annotation: The annotation for which to return a menu item.
///     - color: The color of the annotation.
///
/// - Returns: A menu item used in the legacy annotation menu.
- (PSPDFMenuItem *)opacityMenuItemForAnnotation:(PSPDFAnnotation *)annotation withColor:(nullable UIColor *)color PSPDF_DEPRECATED(12, "Use 'PDFConfiguration.annotationMenuConfiguration.alphaChoices' or 'PDFViewControllerDelegate.pdfViewController(_:menuForAnnotations:onPageView:appearance:suggestedMenu:)' instead.");

/// Returns an array of colors to display in the annotation menu for the given
/// annotation.
///
/// > Warning: This subclassing hook is deprecated. To customize color choices
/// > available in the annotation menu, use the ``PSPDFConfiguration/annotationMenuConfiguration``
/// > configuration property instead.
- (NSArray<UIColor *> *)defaultColorOptionsForAnnotationType:(PSPDFAnnotationType)annotationType PSPDF_DEPRECATED(12, "Use 'PDFConfiguration.annotationMenuConfiguration.colorChoices' instead.");

/// An array of font sizes to display in the annotation menu for compatible
/// annotations.
///
/// > Warning: This subclassing hook is deprecated. To customize font size
/// > choices available in the annotation menu, use the ``PSPDFConfiguration/annotationMenuConfiguration``
/// > configuration property instead.
@property (nonatomic, readonly) NSArray<NSNumber /* CGFloat */ *> *availableFontSizes PSPDF_DEPRECATED(12, "Use 'PDFConfiguration.annotationMenuConfiguration.fontSizeChoices' instead.");

/// An array of line widths to display in the annotation menu for compatible
/// annotations.
///
/// > Warning: This subclassing hook is deprecated. To customize line width
/// > choices available in the annotation menu, use the ``PSPDFConfiguration/annotationMenuConfiguration``
/// > configuration property instead.
@property (nonatomic, readonly) NSArray<NSNumber /* CGFloat */ *> *availableLineWidths PSPDF_DEPRECATED(12, "Use 'PDFConfiguration.annotationMenuConfiguration.lineWidthChoices' instead.");

/// A boolean value that indicates whether annotation style menu elements should
/// be displayed as a sub-menu or an inline menu.
///
/// > Warning: This subclassing hook is deprecated. To customize the annotation
/// > menu directly, use the ``PSPDFViewControllerDelegate/pdfViewController:menuForAnnotations:onPageView:appearance:suggestedMenu:``
/// > delegate method and customize the `.displayInline` option for the menu
/// > with `.pspdfkit.style` identifier.
@property (nonatomic, readonly) BOOL shouldMoveStyleMenuEntriesIntoSubmenu PSPDF_DEPRECATED(12, "Use 'PDFViewControllerDelegate.pdfViewController(_:menuForAnnotations:onPageView:appearance:suggestedMenu:)' instead.");

/// An array of pass-through views for popover controller, e.g. the color picker
/// or the annotation inspector. By default, this is fairly aggressive and
/// returns the entire parent view controller's view.
///
/// > Warning: This subclassing hook is deprecated and no longer called since
/// > PSPDFKit 12 for iOS. To customize the pass-through views for view
/// > controllers presented in popovers, use one of the view controller
/// > presentation methods with a custom array of views for the
/// > ``PSPDFPresentationOptionPopoverPassthroughViews`` presentation option.
/// > Alternatively, override one of these methods in your subclass of
/// > ``PSPDFPageView` and call `super` with modified presentation options.
@property (nonatomic, readonly) NSArray<UIView *> *passthroughViewsForPopoverController PSPDF_DEPRECATED(12, "Use 'PresentationOption.popoverPassthroughViews' when presenting view controllers instead.");

@end

// MARK: -

typedef NSString * PSPDFTextMenu NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(TextMenu);

PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuCopy;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuCreateLink;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuDefine;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuPause;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuSaveAs;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuSearch;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuShare;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuSpeak;
PSPDF_EXPORT const PSPDFTextMenu PSPDFTextMenuWikipedia;

PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuHighlight;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuRedaction;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuSquiggle;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuStrikeout;
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuUnderline;

PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignment PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignmentCenter PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignmentLeft PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuAlignmentRight PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuBlendMode PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuCancel PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuColor PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuContinueRecording PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuCopy PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.copy' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuCustomColor PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuEdit PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.editFreeText' or 'UIAction.Identifier.PSPDFKit.editSound' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFillColor PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFinishRecording PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFitToText PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.sizeToFit' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuFont PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuGroup PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.group' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuHighlightType PSPDF_DEPRECATED(12, "Use 'UIMenu.Identifier.PSPDFKit.type' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuInspector PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.inspector' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineEnd PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineStart PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeButt PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeCircle PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeClosedArrow PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeDiamond PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeNone PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeOpenArrow PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeReverseClosedArrow PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeReverseOpenArrow PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeSlash PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuLineTypeSquare PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuMerge PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.merge' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuNote PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.comments' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuOpacity PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPaste PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.paste' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPause PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPauseRecording PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPlay PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.play' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuPreviewFile PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.previewFile' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuRemove PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.delete' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuSave PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.store' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuSize PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuStyle PSPDF_DEPRECATED(12, "Use 'UIMenu.Identifier.PSPDFKit.style' in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuThickness PSPDF_DEPRECATED(12, "This value is unused in the modern menu system.");
PSPDF_EXPORT const PSPDFTextMenu PSPDFAnnotationMenuUngroup PSPDF_DEPRECATED(12, "Use 'UIAction.Identifier.PSPDFKit.ungroup' in the modern menu system.");

NS_ASSUME_NONNULL_END
