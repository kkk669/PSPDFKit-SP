//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationStyleKey.h>

NS_ASSUME_NONNULL_BEGIN

/// Compose a name for undoable command of adding the given annotations to a
/// document. Returns `nil` if no annotations are given or if localization is
/// not found.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFUndoCommandNameForAddingAnnotations(NSArray<PSPDFAnnotation *> *annotations) NS_REFINED_FOR_SWIFT;

/// Compose a name for undoable command of changing the given style key of the
/// given annotations. Returns `nil` if no annotations are given or if
/// localization is not found.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFUndoCommandNameForChangingAnnotations(NSArray<PSPDFAnnotation *> *annotations, PSPDFAnnotationStyleKey _Nullable styleKey) NS_REFINED_FOR_SWIFT;

/// Compose a name for undoable command of drawing the given annotations.
/// Returns `nil` if no annotations are given or if localization is not found.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFUndoCommandNameForDrawingAnnotations(NSArray<PSPDFAnnotation *> *annotations) NS_REFINED_FOR_SWIFT;

/// Compose a name for undoable command of moving the given annotations. Returns
/// `nil` if no annotations are given or if localization is not found.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFUndoCommandNameForMovingAnnotations(NSArray<PSPDFAnnotation *> *annotations) NS_REFINED_FOR_SWIFT;

/// Compose a name for undoable command of removing the given annotations from a
/// document. Returns `nil` if no annotations are given or if localization is
/// not found.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFUndoCommandNameForRemovingAnnotations(NSArray<PSPDFAnnotation *> *annotations) NS_REFINED_FOR_SWIFT;

/// Compose a name for undoable command of resizing the given annotations.
/// Returns `nil` if no annotations are given or if localization is not found.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFUndoCommandNameForResizingAnnotations(NSArray<PSPDFAnnotation *> *annotations) NS_REFINED_FOR_SWIFT;

/// Compose a name for undoable command of rotating the given annotations.
/// Returns `nil` if no annotations are given or if localization is not found.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFUndoCommandNameForRotatingAnnotations(NSArray<PSPDFAnnotation *> *annotations) NS_REFINED_FOR_SWIFT;

NS_ASSUME_NONNULL_END
