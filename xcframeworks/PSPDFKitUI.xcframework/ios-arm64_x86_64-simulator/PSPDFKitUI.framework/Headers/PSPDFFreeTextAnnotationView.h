//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFHostingAnnotationView.h>

@class PSPDFResizableView;

NS_ASSUME_NONNULL_BEGIN

/// Free Text View. Allows inline text editing.
PSPDF_CLASS_SWIFT(FreeTextAnnotationView)
@interface PSPDFFreeTextAnnotationView : PSPDFHostingAnnotationView<UITextViewDelegate, PSPDFOverridable>

/// Starts editing; shows the keyboard.
///
/// @return YES if editing was able to be started, NO otherwise. This can happen in cases where the annotation is locked/has contents locked.
- (BOOL)beginEditing;

/// Ends editing; hides the keyboard.
- (void)endEditing;

/// Internally used textView. Only valid during begin and before `endEditing`.
@property (nonatomic, readonly, nullable) UITextView *textView;

/// The dragging view, if we are currently dragged.
@property (nonatomic, weak) PSPDFResizableView *resizableView;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFFreeTextAnnotationView (SubclassingHooks)

/// Creates a textView on the fly once we enter edit mode.
///
/// Subclass to create a different text view.
/// Every call to this method will create a new text view. Do not call directly. Only intended to subclass.
- (UITextView *)textViewForEditing;

@end

NS_ASSUME_NONNULL_END
