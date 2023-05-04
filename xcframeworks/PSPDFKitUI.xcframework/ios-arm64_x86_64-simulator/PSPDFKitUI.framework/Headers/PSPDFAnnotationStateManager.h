//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFDrawView.h>
#import <PSPDFKitUI/PSPDFViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotationStyleViewController;

/// Possible modes for `AnnotationStateManager`’s `stylusMode` property.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAnnotationStateManagerStylusMode) {
    /// Uses the stylus mode if the Apple Pencil is enabled via the global `PSPDFApplePencilManager`.
    PSPDFAnnotationStateManagerStylusModeFromStylusManager,
    /// Annotate with a single finger (direct touch) or with a trackpad or mouse (indirect pointer). Scroll with two fingers.
    PSPDFAnnotationStateManagerStylusModeDirect,
    /// Annotate only with Apple Pencil. Tap and scroll with fingers, trackpads and mice as normal.
    PSPDFAnnotationStateManagerStylusModeStylus,
} PSPDF_ENUM_SWIFT(AnnotationStateManagerStylusMode);

@class PSPDFAnnotationStateManager, PSPDFToolbarButton;

/// Special type that will add a selection tool to the toolbar.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringSelectionTool;

/// Special type that will show a view controller with saved/pre-created annotations.
PSPDF_EXPORT PSPDFAnnotationString const PSPDFAnnotationStringSavedAnnotations;

/// The annotation state manager delegate is informed of state changes.
///
/// @note The manager class supports registering multiple delegate implementations.
PSPDF_PROTOCOL_SWIFT(AnnotationStateManagerDelegate)
@protocol PSPDFAnnotationStateManagerDelegate<NSObject>

@optional

/// Called before the manager's `state` and or `variant` attribute changes.
/// As a convenience it also provides access the current `state` and `variant`.
/// If any of the delegates returns `false`, the state change won't be applied.
- (BOOL)annotationStateManager:(PSPDFAnnotationStateManager *)manager shouldChangeState:(nullable PSPDFAnnotationString)currentState to:(nullable PSPDFAnnotationString)proposedState variant:(nullable PSPDFAnnotationVariantString)currentVariant to:(nullable PSPDFAnnotationVariantString)proposedVariant;

/// Called after the manager's `state` and or `variant` attribute changes.
/// As a convenience it also provides access the previous `state` and `variant` for any state-related cleanup.
- (void)annotationStateManager:(PSPDFAnnotationStateManager *)manager didChangeState:(nullable PSPDFAnnotationString)oldState to:(nullable PSPDFAnnotationString)newState variant:(nullable PSPDFAnnotationVariantString)oldVariant to:(nullable PSPDFAnnotationVariantString)newVariant;

/// Called when the state of undo or redo changes.
- (void)annotationStateManager:(PSPDFAnnotationStateManager *)manager didChangeUndoState:(BOOL)undoEnabled redoState:(BOOL)redoEnabled;

/// Called when the annotation state manager would like to show the color palette.
/// This is called when the `UIPencilPreferredActionShowColorPalette` action is invoked from a `UIPencilInteraction`.
///
/// A single delegate should implement this and show UI. Multiple delegates trying to show UI are likely to interfere with each other.
/// `AnnotationToolbar` implements this method.
///
/// The implementation would typically call `toggleStylePicker:presentationOptions:` on the state manager, unless you want to show a custom color/style picker.
- (void)annotationStateManagerDidRequestShowingColorPalette:(PSPDFAnnotationStateManager *)manager;

@end

/// `AnnotationStateManager` holds the current annotation state and configures the associated `PDFViewController` to accept input related to the currently selected annotation state. The class also provides several convenience methods and user interface components required for annotation creation and configuration.
///
/// Interested parties can use KVO to observe the manager's properties.
///
/// You should never use more than one `AnnotationStateManager` for any given `PDFViewController`. It's recommended to use `-[PSPDFViewController annotationStateManager]` instead of creating your own one in order to make sure this requirement is always met.
///
/// `AnnotationStateManager` is internally used by `AnnotationToolbar` and can be re-used for any custom annotation related user interfaces.
///
/// Creating an annotation state manager requires either Annotations or Electronic Signatures to be enabled in your license.
/// If you have Electronic Signatures without Annotations then the only state the manager may be put into is `.signature`
///
/// @note Do not create this class yourself. Use the existing class that is exposed in the `PSPDFViewController.`
PSPDF_CLASS_SWIFT(AnnotationStateManager)
@interface PSPDFAnnotationStateManager : NSObject<PSPDFOverridable, UIPencilInteractionDelegate>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Attached pdf controller.
@property (nonatomic, weak, readonly) PSPDFViewController *pdfController;

/// Adds an annotation state delegate to the subscriber list.
///
/// @note Delegates are weakly retained, but be a good citizen and manually deregister.
- (void)addDelegate:(id<PSPDFAnnotationStateManagerDelegate>)delegate;

/// Removes an annotation state delegate from the subscriber list.
- (BOOL)removeDelegate:(id<PSPDFAnnotationStateManagerDelegate>)delegate;

/// Active annotation state.
///
/// @note Setting the state on it's own resets the variant to nil. Prefer using `setState(_, variant:)`, for tools that have associated variants (e.g., for `.ink`). Setting a state will temporarily disable the long press gesture recognizer on the `PSPDFScrollView` to disable the new annotation menu.
@property (nonatomic, copy, nullable) PSPDFAnnotationString state;

/// Sets the state to the specified annotation type, if it differs from the currently set `state`, otherwise sets the `state` to `nil`.
///
/// @note This will load the previous used color into `drawColor` and set all other options like `lineWidth`.
/// Set these value AFTER setting the state if you want to customize them, or set the default in `PSPDFStyleManager`
- (void)toggleState:(PSPDFAnnotationString)state;

/// Sets the annotation variant for the current state.
///
/// States with different variants uniquely preserve the annotation style settings.
/// This is handy for defining multiple tools of the same annotation type, each with different style settings.
///
/// @note When switching state prefer `setState(_, variant:)` to set the state and variant at the same time.
@property (nonatomic, copy, nullable) PSPDFAnnotationVariantString variant;

/// Sets the annotation type and variant at the same time.
///
/// @see state, variant
- (void)setState:(nullable PSPDFAnnotationString)state variant:(nullable PSPDFAnnotationVariantString)variant;

/// Toggles the annotation type and variant at the same time.
/// If the state and variant both match the currently set values, it sets both to `nil`.
/// Convenient for selectable toolbar buttons.
- (void)toggleState:(nullable PSPDFAnnotationString)state variant:(nullable PSPDFAnnotationVariantString)variant;

/// String identifier used as the persistence key for the current combination of state and variant.
@property (nonatomic, copy, readonly) PSPDFAnnotationStateVariantID stateVariantID;

/// Whether compatible annotations types may be created only with touches of type `pencil`. If set to
/// `stylus` and a compatible annotation tool is selected, users can annotate with Apple Pencil while taping and
/// scrolling as normal with finger touches. If set to `direct` then single finger touches will create annotations
/// and two fingers must be used to scroll.
/// The default is `fromStylusManager`, which effectively uses one of the other two modes depending on if `PSPDFApplePencilManager` enabled the Apple Pencil.
@property (nonatomic) PSPDFAnnotationStateManagerStylusMode stylusMode;

/// Default/current drawing color. KVO observable.
/// Defaults to `[UIColor colorWithRed:0.121 green:0.35 blue:1. alpha:1.0]`
///
/// @note PSPDFKit will save the last used drawing color in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic, nullable) UIColor *drawColor;

/// Default/current fill color. KVO observable.
/// Defaults to nil.
///
/// @note PSPDFKit will save the last used fill color in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic, nullable) UIColor *fillColor;

/// Current drawing line width. Defaults to 3.. KVO observable.
///
/// @note PSPDFKit will save the last used line width in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic) CGFloat lineWidth;

/// Starting line end type for lines and polylines. KVO observable.
///
/// @note PSPDFKit will save the last used line end in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic) PSPDFLineEndType lineEnd1;

/// Ending line end type for lines and polylines. KVO observable.
///
/// @note PSPDFKit will save the last used line end in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic) PSPDFLineEndType lineEnd2;

/// The stroke dash pattern. Draws a solid line when `nil` (default).
@property (nonatomic, copy, nullable) NSArray<NSNumber *> *dashArray;

/// The border effect style.
@property (nonatomic) PSPDFAnnotationBorderEffect borderEffect;

/// The border effect intensity (if set to cloudy)
@property (nonatomic) CGFloat borderEffectIntensity;

/// Defines a custom blend mode. Supported values include
/// `kCGBlendModeNormal` to `kCGBlendModeExclusion`.
@property (nonatomic) CGBlendMode blendMode;

/// Font name for free text annotations. KVO observable.
///
/// @note PSPDFKit will save the last used font name in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic, copy, nullable) NSString *fontName;

/// Font size for free text annotations. KVO observable.
///
/// @note PSPDFKit will save the last used font size in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic) CGFloat fontSize;

/// Text alignment for free text annotations. KVO observable.
///
/// @note PSPDFKit will save the last used text alignment in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic) NSTextAlignment textAlignment;

/// Outline color for redaction annotations. KVO observable.
///
/// @note PSPDFKit will save the last used outline color in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic, nullable) UIColor *outlineColor;

/// Overlay text for redaction annotations. KVO observable.
///
/// @note PSPDFKit will save the last used overlay text value in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic, copy, nullable) NSString *overlayText;

/// Repeat overlay text for redaction annotations. KVO observable.
///
/// @note PSPDFKit will save the last used repeat overlay text value in `NSUserDefaults`.
/// If you want to change the default value, use `-[PSPDFAnnotationStyleManager setLastUsedValue:forProperty:forKey:]`.
@property (nonatomic) BOOL repeatOverlayText;

/// The interaction used to handle actions from Apple Pencil.
///
/// The delegate is the annotation state manager.
/// The interaction is disabled initially.
/// `AnnotationToolbar` will enabled and disable the interaction when the toolbar appears and disappears respectively.
@property (nonatomic, readonly) UIPencilInteraction *pencilInteraction;

/// Shows the style picker for the current annotation class and configures it with annotation state manager style attributes.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
/// @note This will change style properties on this annotation state manager.
- (nullable PSPDFAnnotationStyleViewController *)toggleStylePicker:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

/// Displays a `PSPDFSignatureViewController` and toggles the state to `Annotation.Tool.signature`.
///
/// This requires Electronic Signatures to be enabled in your license.
/// (This method is also available for licenses with Annotations obtained in April 2021 or earlier.
/// In that case, it will show a more limited signing UI that only supports drawing.)
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
- (nullable UIViewController *)toggleSignatureController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

/// Displays a `PSPDFStampViewController` and toggles the state to `PSPDFAnnotationStringStamp`.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
- (nullable UIViewController *)toggleStampController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

/// Displays a `PSPDFSavedAnnotationsViewController` and toggles the state to `PSPDFAnnotationStringSavedAnnotations`.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
- (nullable UIViewController *)toggleSavedAnnotations:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

/// Displays a `PSPDFImagePickerController` and toggles the state to `PSPDFAnnotationStringImage`. This will display an alert if the user selects UIImagePickerControllerSourceTypeCamera but does not grant permission.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
- (nullable UIViewController *)toggleImagePickerController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

// MARK: State Helpers

/// Checks if `state` is a drawing state.
- (BOOL)isDrawingState:(nullable PSPDFAnnotationString)state;

/// Checks if `state` is a markup annotation state. (Highlight, underline, strikeout, and squiggly.).
- (BOOL)isMarkupAnnotationState:(nullable PSPDFAnnotationString)state;

/// Subclass to control if the state supports a style picker.
- (BOOL)stateShowsStylePicker:(nullable PSPDFAnnotationString)state;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFAnnotationStateManager (SubclassingHooks)

/// Color management.
- (void)setLastUsedColor:(nullable UIColor *)lastUsedDrawColor annotationString:(PSPDFAnnotationString)annotationString;
- (nullable UIColor *)lastUsedColorForAnnotationString:(PSPDFAnnotationString)annotationString;

/// If we're in drawing state, this dictionary contains the `PSPDFDrawView` classes that are overlaid on the `PDFPageView`.
/// The key is the current page.
@property (nonatomic, readonly) NSDictionary<NSNumber *, PSPDFDrawView *> *drawViews;

@end

NS_ASSUME_NONNULL_END
