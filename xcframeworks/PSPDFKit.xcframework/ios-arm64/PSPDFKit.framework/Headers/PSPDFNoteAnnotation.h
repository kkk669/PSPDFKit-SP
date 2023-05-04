//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationAuthorState.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// PDF Note (Text) Annotation.
///
/// @note Note annotations are rendered as fixed size; much like how Adobe Acrobat renders them.
/// PSPDFKit will always render note annotations at a fixed size of 32x32pt.
/// We recommend that you set the `boundingBox` to the same value.
PSPDF_CLASS_SWIFT(NoteAnnotation)
@interface PSPDFNoteAnnotation : PSPDFAnnotation<PSPDFOverridable>

/// Initialize with text contents.
- (instancetype)initWithContents:(NSString *)contents;

/// Note Icon name that changes the image representation.
///
/// PDF knows several standard icon names:
/// Comment, RightPointer, RightArrow, Check, Circle, Cross,
/// Insert, NewParagraph, Note, Paragraph, Help, Star, Key.
///
/// @note If set to nil, it will return to the default "Comment".
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, copy, null_resettable) NSString *iconName;

/// The category of the author-specific state associated with the parent annotation.
///
/// As in the PDF specification, the state is not specified on the annotation
/// itself but on a separate note annotation that refers to the original annotation
/// by means of the `inReplyToAnnotation`.
///
/// The default is `PSPDFAnnotationAuthorStateModelUnspecified`.
///
/// It is not possible to set this back to `PSPDFAnnotationAuthorStateModelUnspecified`.
@property (atomic) PSPDFAnnotationAuthorStateModel authorStateModel NS_REFINED_FOR_SWIFT;

/// The author-specific state associated with the parent annotation.
///
/// As in the PDF specification, the state is not specified on the annotation
/// itself but on a separate note annotation that refers to the original annotation
/// by means of the `inReplyToAnnotation`.
///
/// The default is `PSPDFAnnotationAuthorStateUnspecified`.
///
/// It is not possible to set this back to `PSPDFAnnotationAuthorStateUnspecified`.
@property (atomic) PSPDFAnnotationAuthorState authorState NS_REFINED_FOR_SWIFT;

/// The methods in this section provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: - Subclassing Hooks

/// Image that is rendered.
@property (nonatomic, readonly) UIImage *renderAnnotationIcon;

/// Whether the `renderAnnotationIcon` should be rendered as is — defaults to `false`.
///
/// When `true`, the icon is rendered without any changes. When `false`, the icon is used as a mask image for
/// a gradient tinted in the receiver’s color.
@property (nonatomic, readonly) BOOL shouldDrawIconAsIs;

/// Called to render the note image.
- (void)drawImageInContext:(CGContextRef)context boundingBox:(CGRect)boundingBox options:(nullable PSPDFRenderOptions *)options;

/// If the note annotation is rendered as text, this method returns the bounding box to contain the text.
/// This is used for flattening a note annotation.
@property (atomic, readonly) CGRect boundingBoxIfRenderedAsText;

@end

NS_ASSUME_NONNULL_END
