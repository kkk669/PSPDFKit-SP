//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

/// The annotation mapper matches annotation strings to their class implementation.
/// e.g. `PSPDFAnnotationStringHighlight` will be mapped to `PSPDFHighlightAnnotation.class`.
PSPDF_SDK_CLASS_SWIFT(AnnotationMapper)
@interface PSPDFAnnotationMapper : NSObject

/// The default instance.
@property (nonatomic, class, readonly) PSPDFAnnotationMapper *defaultMapper;

/// Returns the class where `annotationType` is implemented, or `Nil` if no class matches.
- (nullable Class)annotationClassForString:(nullable PSPDFAnnotationString)annotationString;

/// Returns the class where `annotationType` is implemented, or `Nil` if no class matches.
- (nullable Class)annotationClassForType:(PSPDFAnnotationType)annotationType;

/// Returns the annotation type for a given annotation. It will iterate over known annotation types and return a match.
- (nullable NSString *)annotationTypeStringFromIncompleteAnnotationInstance:(PSPDFAnnotation *)annotation;

/// Specifies corresponding `PSPDFAnnotation` subclass classes for various annotation types.
@property (nonatomic, copy, readonly) NSDictionary<PSPDFAnnotationString, Class> *typeToClassMap;

@end

NS_ASSUME_NONNULL_END
