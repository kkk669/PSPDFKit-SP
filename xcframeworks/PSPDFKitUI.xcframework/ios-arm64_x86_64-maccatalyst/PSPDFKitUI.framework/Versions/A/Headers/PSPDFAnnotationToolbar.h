//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationStateManager.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbar.h>
#import <PSPDFKit/PSPDFOverridable.h>

@class PSPDFAnnotationToolbar, PSPDFAnnotationToolbarConfiguration, PSPDFColorButton, PSPDFToolbarDualButton;

NS_ASSUME_NONNULL_BEGIN

/// The annotation toolbar allows the creation of most annotation types supported by PSPDFKit.
///
/// To customize which annotation icons should be displayed, edit `editableAnnotationTypes` in `PDFConfiguration`.
/// Further appearance customization options are documented in the superclass header (`PSPDFFlexibleToolbar.h`).
///
/// `AnnotationToolbar` needs to be used together with a `PSPDFFlexibleToolbarContainerView` just like its superclass `PSPDFFlexibleToolbar`.
///
/// Since the annotation toolbar works with `UIButton` directly (rather than using `UIBarButtonItem`), the buttons in it
/// can’t be added directly to the main toolbar or navigation bar. This must be achieved by adding a custom
/// item to the `navigationItems` or `toolbarItems` that sets the state of the `PSPDFAnnotationStateManager`.
///
/// @note Directly updating `buttons` will not work. Use `additionalButtons` if you want to add custom buttons.
PSPDF_CLASS_SWIFT(AnnotationToolbar)
@interface PSPDFAnnotationToolbar : PSPDFFlexibleToolbar<PSPDFAnnotationStateManagerDelegate, PSPDFOverridable>

PSPDF_DEFAULT_VIEW_INIT_UNAVAILABLE

/// The designated initializer, which sets up the toolbar with an annotation state manager.
- (instancetype)initWithAnnotationStateManager:(PSPDFAnnotationStateManager *)annotationStateManager NS_DESIGNATED_INITIALIZER;

/// The attached annotation state manager, which holds the state of the currently selected tool.
@property (nonatomic) PSPDFAnnotationStateManager *annotationStateManager;

/// The annotation types that may be shown in the annotation toolbar.
/// In the default state, and if set to `nil`, this will return `pdfController.configuration.editableAnnotationTypes`.
@property (nonatomic, copy, null_resettable) NSSet<PSPDFAnnotationString> *editableAnnotationTypes;

// MARK: Configuration

/// Specifies a list of toolbar configurations amongst which the toolbar can pick when laying out items.
/// The toolbar automatically picks an appropriate configuration based on the available space.
/// Items are grouped by default. Set to `nil` to disable grouping. In that case the toolbar will be populated
/// by ungrouped items based based on `editableAnnotationTypes`.
///
/// @note Annotation types that are present in a toolbar configuration but missing in
/// `editableAnnotationTypes` will be not be shown.
@property (nonatomic, copy, nullable) NSArray<PSPDFAnnotationToolbarConfiguration *> *configurations;

/// Returns `annotationGroups` based on the selected configuration if set,
/// or implicitly created groups based on `editableAnnotationTypes`.
@property (nonatomic, readonly) NSArray<__kindof PSPDFAnnotationGroup *> *annotationGroups;

// MARK: Buttons

/// Access to buttons created based on the state of `annotationGroups`.
///
/// @param type The type of the annotation tool.
/// @param variant The variant of the annotation tool. Can be `nil` if the tool has no variants.
/// @param createFromGroup If this is set to `true`, the toolbar will automatically update and display the queried button,
/// in case it was previously not the chosen item in the corresponding annotation group and the annotation state manager
/// doesn't specify a different active state in the same group. Be sure to set this to `false` to avoid the method from
/// causing those side-effects.
- (nullable UIButton *)buttonWithType:(PSPDFAnnotationString)type variant:(nullable PSPDFAnnotationVariantString)variant createFromGroup:(BOOL)createFromGroup;

/// Allows custom `UIButton` objects to be added after the buttons in `annotationGroups`.
/// For best results use `PSPDFToolbarButton` objects. Defaults to nil.
///
/// @note The buttons should have unique accessibility labels so we can show them in a menu if needed.
@property (nonatomic, copy, nullable) NSArray<__kindof UIButton *> *additionalButtons;

/// Collapses the undo and redo buttons into one button for smaller toolbar sizes. Defaults to `true`.
///
/// @note This currently just hides the redo button.
@property (nonatomic) BOOL collapseUndoButtonsForCompactSizes;

/// Whether `showingStylusButton` should be set to `true` if an Apple Pencil is detected.
/// Set this to `false` if you don’t want the annotation toolbar to show this button, or want to decide when to show it yourself.
/// Defaults to `true`.
@property (nonatomic) BOOL showsApplePencilButtonAutomatically;

/// Whether `applePencilButton` is shown in the annotation toolbar.
///
/// The initial value of this property will be `true` if an Apple Pencil has been detected, or `false` if not.
///
/// This property will be changed by PSPDFKit when detecting an Apple Pencil if `showsApplePencilButtonAutomatically` is `true`.
///
/// Calling the setter of this property does not animate the change. To animate, use `setShowingStylusButton:animated:`.
@property (nonatomic, getter=isShowingApplePencilButton) BOOL showingApplePencilButton;

/// Animated setter for `showingApplePencilButton`.
- (void)setShowingApplePencilButton:(BOOL)showingApplePencilButton animated:(BOOL)animated;

// MARK: Behavior

/// This will issue a save event after the toolbar has been dismissed.
///
/// @note Since saving can take some time, this defaults to `false`.
@property (nonatomic) BOOL saveAfterToolbarHiding;

@end

/// Standard toolbar buttons (return nil if you don't want them).
/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFAnnotationToolbar (SubclassingHooks)

/// Dismisses the annotation toolbar.
///
/// @note Not `nil` by default, but can be overridden to return `nil` to remove it from the toolbar.
@property (nonatomic, readonly, nullable) UIButton *doneButton;

/// Shows whether Apple Pencil is being used to interact with annotations.
///
/// Tapping this button shows `PSPDFApplePencilController` which lets the user enable or disable Apple Pencil.
@property (nonatomic, readonly, nullable) PSPDFToolbarButton *applePencilButton;

/// Undoes the last action.
///
/// @note Not `nil` by default, but can be overridden to return `nil` to remove it from the toolbar.
@property (nonatomic, readonly, nullable) UIButton *undoButton;

/// Redoes the last action.
///
/// @note Not `nil` by default, but can be overridden to return `nil` to remove it from the toolbar.
@property (nonatomic, readonly, nullable) UIButton *redoButton;

/// Shows a menu with undo / redo options. Used in compact sizes instead of `undoButton` and `redoButton`.
///
/// @note Not `nil` by default, but can be overridden to return `nil` to remove it from the toolbar.
@property (nonatomic, readonly, nullable) PSPDFToolbarDualButton *undoRedoButton;

/// Shows the annotation inspector for the selected annotation type. Hidden (but not removed), if a relevant type
/// is currently not selected. Only added to the toolbar, if the toolbar contains buttons for supported annotation types.
///
/// @note Not `nil` by default, but can be override to return `nil` to remove it from the toolbar.
@property (nonatomic, readonly, nullable) PSPDFColorButton *strokeColorButton;

/// The done action.
- (void)done:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
