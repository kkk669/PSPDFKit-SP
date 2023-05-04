//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFAnnotationStyleKey.h>

NS_ASSUME_NONNULL_BEGIN

/// Returns a localized string for the given property of the given annotation
/// class, if such string is defined.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFLocalizeAnnotationProperty(Class /* PSPDFAnnotation */ annotationClass, NSString *property) NS_SWIFT_UNAVAILABLE("Use `localizedAnnotationProperty(_:)` instead.") PSPDF_PURE;

/// A safer version of `PSPDFLocalizeAnnotationProperty` that offers a compile
/// time check that class `c` has a property `p`.
#define PSPDFLocalizeAnnotationClassProperty(c, p) PSPDFLocalizeAnnotationProperty(c.class, PSPDF_KEYPATH_CLASS(c, p))

/// A safer version of `PSPDFLocalizeAnnotationProperty` that offers a compile
/// time check that an object `o` has a property `p`.
#define PSPDFLocalizeAnnotationObjectProperty(o, p) PSPDFLocalizeAnnotationProperty(o.class, PSPDF_KEYPATH(o, p))

/// Returns a localized string for the given annotation style key of the given
/// annotation class, if such string is defined.
PSPDF_SDK_EXPORT NSString * _Nullable PSPDFLocalizeAnnotationStyleKey(Class /* PSPDFAnnotation */ annotationClass, PSPDFAnnotationStyleKey styleKey) NS_SWIFT_UNAVAILABLE("Use `localizedAnnotationStyleKey(_:_:)` instead.") PSPDF_PURE;

NS_ASSUME_NONNULL_END
