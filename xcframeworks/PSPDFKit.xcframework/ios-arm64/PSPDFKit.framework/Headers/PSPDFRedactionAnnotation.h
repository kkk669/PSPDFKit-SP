//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// Redaction Annotation
///
/// Used to remove content from a document.
///
/// `color` can be used to change the color of the overlay text. It has no effect if there is no overlay text specified. Defaults to a red color.
/// `fillColor` specifies the background color of the redaction area after is has been applied. The color is drawn on all the specified `rects`. Defaults to black.
/// `lineWidth` can be set to change the border width of the redaction in its marked state. Defaults to 5.
///
/// @note Supports redacting text, images, paths, annotations, and forms.
///
/// @note Redaction annotations need to be applied, after they were created and added to a document, to remove the content beneath them. See `PSPDFProcessorConfiguration` or `PSPDFDocumentSaveOptionApplyRedactions` for further information.
///
/// @warning When programmatically creating a redaction annotation, both `boundingBox` and `rects` need to be set. The `rects` array contains boxed variants of `CGRect` (`NSValue`).
PSPDF_CLASS_SWIFT(RedactionAnnotation)
@interface PSPDFRedactionAnnotation : PSPDFAnnotation<PSPDFOverridable>

/// Specifies the color used for the redaction's border in its marked state.
/// Defaults to a red color.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, nullable) UIColor *outlineColor;

/// Can be used to set the text that should be displayed at the specified `rects` when a redaction has been applied.
/// Defaults to nil.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, copy, nullable) NSString *overlayText;

/// Defines if the overlay text should be drawn only once, or repeated to fill the whole bounding box.
/// Defaults to disabled, which means the overlay text is only drawn once.
///
/// @note This property has no effect if there is no overlay text set.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic) BOOL repeatOverlayText;

@end

NS_ASSUME_NONNULL_END
