//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFModelObject.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFRenderOptions;

/// An annotation set may be used to add and position multiple annotations.
PSPDF_CLASS_SWIFT(AnnotationSet)
@interface PSPDFAnnotationSet : PSPDFModel<NSFastEnumeration>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
///
/// @param annotations The annotations the set holds.
/// @param shouldCopyAnnotations If true, a deep copy of the annotations will be made and the annotation bounding boxes will be normalized so the bottom-left one will have its origin at (0,0).
- (instancetype)initWithAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations copyAnnotations:(BOOL)shouldCopyAnnotations NS_DESIGNATED_INITIALIZER;

/// The saved annotations.
@property (nonatomic, copy, readonly) NSArray<__kindof PSPDFAnnotation *> *annotations;

/// Draw all annotations.
- (void)drawInContext:(CGContextRef)context options:(nullable PSPDFRenderOptions *)options;

// MARK: Frames

/// Bounding box of all annotations. If set, will correctly resize all annotations.
@property (nonatomic) CGRect boundingBox;

// MARK: Clipboard

/// Copies the current set to the clipboard.
- (void)copyToClipboard;

/// Loads a PSPDFAnnotationSet from the clipboard.
///
/// @note Also supports legacy format and will automatically pack it into a `PSPDFAnnotationSet`.
+ (nullable instancetype)unarchiveFromClipboard;

@end

NS_ASSUME_NONNULL_END
