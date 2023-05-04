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

/// An object used as an activation context in `PSPDFAnnotationInteraction` that
/// provides information about an annotation being selected or edited and a page
/// view that contains it.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AnnotationSelectionContext)
@interface PSPDFAnnotationSelectionContext<__covariant AnnotationType : PSPDFAnnotation *> : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Annotation being selected or edited.
@property (nonatomic, readonly) AnnotationType annotation;

/// Page view that contains `annotation`.
@property (nonatomic, readonly) PSPDFPageView *pageView;

@end

NS_ASSUME_NONNULL_END
