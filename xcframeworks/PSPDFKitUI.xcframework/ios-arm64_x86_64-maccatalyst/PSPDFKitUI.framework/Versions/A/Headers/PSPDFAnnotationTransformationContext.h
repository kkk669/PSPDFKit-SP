//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAnnotation, PSPDFPageView;

NS_ASSUME_NONNULL_BEGIN

/// An enum representing a mode in which an annotation is transformed.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationTransformationMode) {
    /// An annotation is being moved.
    PSPDFAnnotationTransformationModeMove,
    /// An annotation is being rotated.
    PSPDFAnnotationTransformationModeRotate,
    /// An annotation is being resized.
    PSPDFAnnotationTransformationModeResize,
    /// An annotation (e.g. polyline shape) is being adjusted.
    PSPDFAnnotationTransformationModeAdjust,
} PSPDF_ENUM_SWIFT(AnnotationTransformationMode);

// MARK: -

/// An object used as an activation context in `PSPDFAnnotationInteraction` that
/// provides information about an annotation being transformed, a page view that
/// contains it and a transformation mode.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AnnotationTransformationContext)
@interface PSPDFAnnotationTransformationContext<__covariant AnnotationType : PSPDFAnnotation *> : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Annotation being transformed.
@property (nonatomic, readonly) AnnotationType annotation;

/// Page view that contains `annotation`.
@property (nonatomic, readonly) PSPDFPageView *pageView;

/// Mode in which `annotation` is being transformed.
@property (nonatomic, readonly) PSPDFAnnotationTransformationMode mode;

@end

NS_ASSUME_NONNULL_END
