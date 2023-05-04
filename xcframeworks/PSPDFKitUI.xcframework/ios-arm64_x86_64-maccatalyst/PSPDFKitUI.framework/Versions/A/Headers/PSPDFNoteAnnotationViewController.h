//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

@class PSPDFAnnotation, PSPDFNoteAnnotationViewController;

NS_ASSUME_NONNULL_BEGIN

PSPDF_PROTOCOL_SWIFT(NoteAnnotationViewControllerDelegate)
@protocol PSPDFNoteAnnotationViewControllerDelegate<NSObject>

@optional

/// Called when the `noteController` has deleted the parent annotation.
/// Not called when any of the comments has been deleted.
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController didDeleteAnnotation:(PSPDFAnnotation *)annotation;

/// Called when the `noteController` has cleared the contents of the annotation.
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController didClearContentsForAnnotation:(PSPDFAnnotation *)annotation;

/// Called when the `noteController` changes the annotation’s contents, color, or iconName.
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController didChangeAnnotation:(PSPDFAnnotation *)annotation;

/// Called before the `noteController` is closed.
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController willDismissWithAnnotation:(nullable PSPDFAnnotation *)annotation;

@end

/// A view controller to view and edit the comments attached to an annotation.
///
/// Comments means the `contents` of the annotation and, if enabled, the `contents` of all replies to that
/// annotation. Whether replies and reviews are enabled is determined by the `canShowAnnotationReplies`
/// and `canShowAnnotationReviews` features from `PSPDFDocumentFeatures` respectively.
///
/// This can be used for any type of annotation.
/// For `PSPDFNoteAnnotation`, additional options are displayed for setting the note’s color and icon.
PSPDF_CLASS_SWIFT(NoteAnnotationViewController)
@interface PSPDFNoteAnnotationViewController : PSPDFBaseViewController<UITextViewDelegate, PSPDFStyleable, PSPDFOverridable>

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

/// Creates a new note annotation view controller with an annotation.
///
/// @param annotation The annotation whose `contents` should be shown.
- (instancetype)initWithAnnotation:(nullable PSPDFAnnotation *)annotation NS_DESIGNATED_INITIALIZER;

/// Creates a new note annotation view controller from Interface Builder.
- (nullable instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

/// Attached annotation. All types are allowed.
@property (nonatomic, nullable) PSPDFAnnotation *annotation;

/// The comment view's background color.
@property (nonatomic, nullable) UIColor *commentBackgroundColor;

/// Whether the date label should be shown.
@property (nonatomic) BOOL showsTimestamps;

/// Whether the author name label should be shown.
@property (nonatomic) BOOL showsAuthorName;

/// If YES, the Style button will be displayed for changing note annotation color and icon. Defaults to YES.
/// Will be ignored if `allowEditing` is NO or annotation type is not `PSPDFAnnotationTypeNote`.
@property (nonatomic) BOOL showColorAndIconOptions;

/// Attached delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFNoteAnnotationViewControllerDelegate> delegate;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFNoteAnnotationViewController (SubclassingHooks)

/// Called as we update the text view.
/// This can be used to update various text view properties like font.
///
/// @note An even better way is to use UIAppearance:
/// `[[UITextView appearanceWhenContainedIn:PSPDFNoteAnnotationViewController.class, nil] setFont:[UIFont fontWithName:@"Helvetica" size:20.0]];`
- (void)updateTextView:(UITextView *)textView;

/// The view used for showing the background color.
@property (nonatomic, readonly) UIView *backgroundView;

/// Called initially and every time a property changes to re-build the toolbar’s items.
- (void)setupToolbar;

/// Called whenever text is changed and after toolbar creation.
/// Used to control the delete button enabled state.
- (void)updateToolbar;

@end

NS_ASSUME_NONNULL_END
