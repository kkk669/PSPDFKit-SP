//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFRotatable.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation;

/// Annotations that can be rotated should privately conform to this protocol (as well as publicly to `PSPDFRotatable`).
@protocol PSPDFRotatableInternal <PSPDFRotatable>

/// YES if the annotation supports rotation, or NO if it does not support rotation.
@property (nonatomic, readonly) BOOL supportsRotation;

/// The value stored in the PDF to save the aspect ratio of the unrotated content.
/// Only the aspect ratio of this rectangle is significant.
/// To read the actual content size that should be used, use `PSPDFRotatableGetContentSize`.
///
/// Because of the way the Core property map automatically applies page transforms based on
/// types, the width and height of this size will be incorrectly flipped on pages at 90º or 270º.
/// We can’t easily unflip this when setting up state from Core because we don’t know the page
/// rotation at that point. Therefore the PSPDFRotatable functions that act on this property
/// will perform the unflipping.
///
/// To change this property in situations where the aspect ratio of an annotation is supposed to
/// change (for instance when resizing a free-text annotation), use the
/// `PSPDFRotatableUpdateStoredContentSize` function. That will take care of correctly flipping
/// the height and width if the page is rotated.
@property (nonatomic) CGRect storedContentSizeRect;

@end

/// Tries to cast the annotation to a rotatable annotation. Returns nil for types that don’t conform to `PSPDFRotatableInternal`.
PSPDF_SDK_EXPORT PSPDFAnnotation<PSPDFRotatableInternal> *_Nullable PSPDFRotatableAnnotationCast(PSPDFAnnotation *_Nullable annotation);

/// The resolved content size, scaled for the current bounding box.
///
/// @param annotation A rotatable annotation.
/// @return The size of the annotation’s content when not rotated, in PDF points.
PSPDF_SDK_EXPORT CGSize PSPDFRotatableGetContentSize(PSPDFAnnotation<PSPDFRotatableInternal> *annotation);

/// Call this function when it is required to change the stored content size of an annotation, for instance when resizing a free text annotation.
/// Using this function to update the stored content size will take care of correctly flipping the height and width if the page is rotated.
///
/// @param annotation A rotatable annotation.
/// @param newContentSize The new stored content size of the annotation. Note that only the aspect ratio of this property will be significant.
PSPDF_SDK_EXPORT void PSPDFRotatableUpdateStoredContentSize(PSPDFAnnotation<PSPDFRotatableInternal> *annotation, CGSize newContentSize);

/// Rotatable annotation should call this after the rotation is changed so the bounding box can be updated to enclose the content while preserving the content size.
///
/// @param annotation A rotatable annotation.
/// @param contentSize The content size of the annotation before rotation. This must be the actual size, not the stored size where only the aspect ratio is significant.
PSPDF_SDK_EXPORT void PSPDFRotatableUpdateBoundingBox(PSPDFAnnotation<PSPDFRotatableInternal> *annotation, CGSize contentSize);

NS_ASSUME_NONNULL_END
