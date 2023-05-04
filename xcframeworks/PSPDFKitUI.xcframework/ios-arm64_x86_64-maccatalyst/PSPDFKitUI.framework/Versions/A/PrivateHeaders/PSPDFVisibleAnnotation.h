//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAnnotation;
@class PSPDFPageView;
@protocol PSPDFAnnotationPresenting;

NS_ASSUME_NONNULL_BEGIN

/// An annotation that's visible on a page view.
///
/// We can't bridge `PSPDFVisibleAnnotation` to Swift because it causes import
/// cycles in the generated Swift module header file (probably because it's a
/// generic type). Therefore, we need to type-erase it into a protocol first.
NS_SWIFT_NAME(VisibleAnnotation)
@protocol PSPDFAnyVisibleAnnotation <NSObject>

/// The annotation visible on `pageView`.
@property (nonatomic, readonly) PSPDFAnnotation *annotation;

/// The view of the annotation on `pageView`.
@property (nonatomic, nullable, readonly) UIView<PSPDFAnnotationPresenting> *annotationView;

/// The page view that contains `annotation`.
@property (nonatomic, readonly) PSPDFPageView *pageView;

@end

/*
 Safely cast the annotation inside `PSPDFVisibleAnnotation`, like:

 ```
 PSPDFVisibleAnnotation *anyAnnotation;
 PSPDFVisibleAnnotation<PSPDFFormElement *> *formElement = PSPDFVisibleAnnotationCast(anyAnnotation, PSPDFFormElement);
 ```

 @param annotation Annotation object to cast.
 @param type Annotation type.
 */
#define PSPDFVisibleAnnotationCast(object, type) (PSPDFVisibleAnnotation<type *> * _Nullable)(^{ let tmp = (object); return ([tmp.annotation isKindOfClass:type.class] ? tmp : nil); }())

/// An annotation that's visible on a page view.
PSPDF_SUBCLASSING_RESTRICTED
NS_SWIFT_UNAVAILABLE("Use `VisibleAnnotation` protocol instead.")
@interface PSPDFVisibleAnnotation<__covariant AnnotationType : PSPDFAnnotation *> : NSObject <PSPDFAnyVisibleAnnotation>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new instance with the given annotation and a page view.
///
/// @param annotation Annotation visible on `pageView`.
/// @param pageView Page view that contains `annotation`.
- (instancetype)initWithAnnotation:(AnnotationType)annotation onPageView:(PSPDFPageView *)pageView NS_DESIGNATED_INITIALIZER;

/// The annotation visible on `pageView`.
@property (nonatomic, readonly) AnnotationType annotation;

@end

NS_ASSUME_NONNULL_END
