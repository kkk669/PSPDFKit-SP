//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFFormElementView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFTextFieldFormElement, PSPDFResizableView;

/// Free Text View. Allows inline text editing.
PSPDF_CLASS_SWIFT(TextFieldFormElementView)
@interface PSPDFTextFieldFormElementView : PSPDFFormElementView<UITextViewDelegate, UITextFieldDelegate, PSPDFOverridable>

/// Start editing, shows the keyboard.
- (void)beginEditing;

/// Ends editing, hides the keyboard.
- (void)endEditing;

/// Internally used textView. Only valid during begin and before endEditing.
@property (nonatomic, readonly, nullable) UITextView *textView;

/// Internally used textField. Only valid during begin and before endEditing.
@property (nonatomic, readonly, nullable) UITextField *textField;

/// Is this a multiline text view?
@property (nonatomic, readonly) BOOL isMultiline;

/// Is this a secure text view for displaying passwords?
@property (nonatomic, readonly) BOOL isPassword;

/// Whether view is in edit mode.
@property (nonatomic) BOOL editMode;

/// The dragging view, if we are currently dragged.
@property (nonatomic, weak) PSPDFResizableView *resizableView;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFTextFieldFormElementView (SubclassingHooks)

/// Creates a textView on the fly once we enter edit mode.
@property (nonatomic, readonly) UITextView *setTextViewForEditing;

@end

NS_ASSUME_NONNULL_END
