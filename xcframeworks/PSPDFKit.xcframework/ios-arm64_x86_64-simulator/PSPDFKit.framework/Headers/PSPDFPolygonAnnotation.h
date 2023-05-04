//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFPolygonAnnotationIntent) {
    /// No intent.
    PSPDFPolygonAnnotationIntentNone = 0,

    /// The annotation is intended to function as a cloud object.
    PSPDFPolygonAnnotationIntentPolygonCloud,

    /// The polygon annotation is intended to function as a dimension. (not implemented)
    PSPDFPolygonAnnotationIntentPolygonDimension
} PSPDF_ENUM_SWIFT(PolygonAnnotation.Intent);

/// `NSValueTransformer` to convert between `PSPDFPolygonAnnotationIntent` enum and string value.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFPolygonAnnotation` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFPolygonAnnotationIntentTransformerName NS_SWIFT_NAME(polygonAnnotationIntent);

/// Polygon annotations (PDF 1.5) display closed polygons on the page. Such polygons may have any number of vertices connected by straight lines. Polyline annotations (PDF 1.5) are similar to polygons, except that the first and last vertex are not implicitly connected.
///
/// @note See `PSPDFAbstractLineAnnotation` for details how to use and initialize.
PSPDF_CLASS_SWIFT(PolygonAnnotation)
@interface PSPDFPolygonAnnotation : PSPDFAbstractLineAnnotation<PSPDFOverridable>

/// Designated initializer.
- (instancetype)initWithPoints:(NSArray<__kindof NSValue *> *)points intentType:(PSPDFPolygonAnnotationIntent)intentType NS_REFINED_FOR_SWIFT;

/// Defines the annotation intent. (Optional; PDF 1.6). Defaults to `PSPDFPolygonAnnotationIntentNone`.
@property (atomic) PSPDFPolygonAnnotationIntent intentType NS_SWIFT_NAME(intent);

@end

NS_ASSUME_NONNULL_END
