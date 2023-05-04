//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFAnnotationStyleViewController.h>
#import <PSPDFKitUI/PSPDFFontPickerViewController.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>
#import <PSPDFKitUI/PSPDFToolbar.h>

@class PSPDFFreeTextAnnotation, PSPDFFreeTextAccessoryView, PSPDFToolbarButton;
@class PSPDFToolbarSelectableButton, PSPDFToolbarSeparatorButton, PSPDFPresentationContext;

NS_ASSUME_NONNULL_BEGIN

/// Notification when someone presses "Clear".
PSPDF_EXPORT NSNotificationName const PSPDFFreeTextAccessoryViewDidPressClearButtonNotification;

/// Delegate to receive actions from the free text accessory view.
PSPDF_PROTOCOL_SWIFT(FreeTextAccessoryViewDelegate)
@protocol PSPDFFreeTextAccessoryViewDelegate<NSObject>

@optional

/// Called when the done button is pressed.
/// You should resign first responder status at this point.
- (void)doneButtonPressedOnFreeTextAccessoryView:(PSPDFFreeTextAccessoryView *)inputView;

/// Called when the clear text button is pressed.
/// Use this to clear the text field and update the annotation.
- (void)clearButtonPressedOnFreeTextAccessoryView:(PSPDFFreeTextAccessoryView *)inputView;

/// Show the text inspector (relevant only if the inspector button is used - only on iPhone by default).
- (nullable PSPDFAnnotationStyleViewController *)freeTextAccessoryViewDidRequestInspector:(PSPDFFreeTextAccessoryView *)inputView;

/// Allow or reject a property change. Assumes always YES if left unimplemented.
- (BOOL)freeTextAccessoryView:(PSPDFFreeTextAccessoryView *)styleController shouldChangeProperty:(NSString *)propertyName;

/// Called whenever a style property of `FreeTextAccessoryView` changes.
/// Use this to also update the annotation bounding box and view frames as needed.
- (void)freeTextAccessoryView:(PSPDFFreeTextAccessoryView *)styleController didChangeProperty:(NSString *)propertyName;

@end

/// Free Text accessory toolbar for faster styling.
PSPDF_CLASS_SWIFT(FreeTextAccessoryView)
@interface PSPDFFreeTextAccessoryView : PSPDFToolbar<PSPDFFontPickerViewControllerDelegate, PSPDFAnnotationStyleViewControllerDelegate, PSPDFOverridable>

/// The input accessory delegate.
@property (nonatomic, weak) id<PSPDFFreeTextAccessoryViewDelegate> delegate;

/// Used to present popover pickers for certain button types.
@property (nonatomic, weak) id<PSPDFPresentationContext> presentationContext;

/// The annotation that is being edited.
@property (nonatomic) PSPDFFreeTextAnnotation *annotation;

// MARK: Customization

/// List of supported inspector properties.
///
/// The dictionary is keyed by annotation type (`PSPDFAnnotationString`).
/// The values are either:
/// - an array of arrays of property name strings (see `PSPDFAnnotationStyleKeyGroupedList`)
/// - a block taking an annotation and returning `PSPDFAnnotationStyleKeyGroupedList` for it (see `PSPDFAnnotationStyleBlock`)
///
/// See `AnnotationStyle.Key` for a list of supported keys.
///
/// Defaults to an empty dictionary. Normally set to the values from `PDFConfiguration` after initialization.
///
/// @note Only the `PSPDFAnnotationStringFreeText` key is relevant for this component.
@property (nonatomic, copy) NSDictionary<PSPDFAnnotationString, id> *propertiesForAnnotations;

// MARK: Styling

/// Whether a thing border should be added just above the accessory view. Defaults to YES.
@property (nonatomic, getter=isBorderVisible) BOOL borderVisible;

/// The color for the default separators and border.
@property (nonatomic) UIColor *separatorColor UI_APPEARANCE_SELECTOR;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFFreeTextAccessoryView (SubclassingHooks)

/// By default the accessory view buttons differ based on the available toolbar width.
/// Use this to customize the button order or fixate a certain set of buttons.
///
/// @note The default arrays include `PSPDFToolbarSeparatorButton` and `PSPDFToolbarSpacerButton` objects.
- (NSArray<__kindof PSPDFToolbarButton *> *)buttonsForWidth:(CGFloat)width;

/// This is called on size changes and when the free text accessory is deallocated.
/// If you present your own controller, add custom logic here to ensure it's dismissed.
- (void)dismissPresentedViewControllersAnimated:(BOOL)animated NS_REQUIRES_SUPER;

// MARK: Default toolbar buttons.

@property (nonatomic, readonly) PSPDFToolbarButton *fontNameButton;
@property (nonatomic, readonly) PSPDFToolbarButton *fontSizeButton;
@property (nonatomic, readonly) PSPDFToolbarButton *increaseFontSizeButton;
@property (nonatomic, readonly) PSPDFToolbarButton *decreaseFontSizeButton;
@property (nonatomic, readonly) PSPDFToolbarSelectableButton *leftAlignButton;
@property (nonatomic, readonly) PSPDFToolbarSelectableButton *centerAlignButton;
@property (nonatomic, readonly) PSPDFToolbarSelectableButton *rightAlignButton;
@property (nonatomic, readonly) PSPDFToolbarButton *colorButton;
@property (nonatomic, readonly) PSPDFToolbarButton *clearButton;
@property (nonatomic, readonly) PSPDFToolbarButton *doneButton;

@end

NS_ASSUME_NONNULL_END
