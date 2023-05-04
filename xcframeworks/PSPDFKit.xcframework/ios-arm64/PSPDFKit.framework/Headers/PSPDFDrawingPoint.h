//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

/// The default intensity used for legacy lines without explicit intensity data.
PSPDF_EXPORT const CGFloat PSPDFDefaultIntensity NS_SWIFT_NAME(DrawingPoint.defaultIntensity);

/// Models a point used for natural drawing.
/// Use `PSPDFDrawingPointFromCGPoint` to convert from a point with default intensity.
///
/// @note The type encoding of this struct needs to remain consistent, because drawing point
/// data can be serialized in NSValue objects.
typedef struct __attribute__((objc_boxable)) {
    /// The location as a regular CGPoint.
    CGPoint location;
    /// The relative thickness of the line at location. Range is 0-1.
    CGFloat intensity;
} PSPDFDrawingPoint NS_SWIFT_NAME(DrawingPoint);

/// Point at location `CGPointZero` with `intensity` `0.`.
PSPDF_EXPORT const PSPDFDrawingPoint PSPDFDrawingPointZero NS_SWIFT_NAME(DrawingPoint.zero);

/// An invalid point with all components set to `NaN`.
PSPDF_EXPORT const PSPDFDrawingPoint PSPDFDrawingPointNull NS_SWIFT_NAME(DrawingPoint.null);

/// Returns `true`, if all values are different from `NAN` and `+inf/-inf`.
PSPDF_EXPORT BOOL PSPDFDrawingPointIsFinite(PSPDFDrawingPoint point) PSPDF_SWIFT_NAME("getter:DrawingPoint.isFinite(self:)") PSPDF_PURE;

/// Yes when the `location` and `intensity` values match.
PSPDF_EXPORT BOOL PSPDFDrawingPointIsEqualToPoint(PSPDFDrawingPoint point, PSPDFDrawingPoint otherPoint) NS_SWIFT_NAME(DrawingPoint.isEqual(self:_:)) PSPDF_PURE;

/// Converts the point into a string representation.
PSPDF_EXPORT NSString *PSPDFDrawingPointToString(PSPDFDrawingPoint point) PSPDF_SWIFT_NAME("getter:DrawingPoint.debugDescription(self:)") PSPDF_PURE;

/// The reverse operation to `PSPDFDrawingPointToString`. Returns `PSPDFDrawingPointNull` is parsing fails.
PSPDF_EXPORT PSPDFDrawingPoint PSPDFDrawingPointFromString(NSString *string) NS_SWIFT_NAME(DrawingPoint.init(string:)) PSPDF_PURE;

/// Creates a new `PSPDFDrawingPoint`.
PSPDF_EXPORT PSPDFDrawingPoint PSPDFDrawingPointMake(CGPoint location, CGFloat intensity) NS_SWIFT_UNAVAILABLE("Use DrawingPoint initializer") PSPDF_PURE;

/// Creates a new `PSPDFDrawingPoint` from a `CGPoint`, using `PSPDFDefaultIntensity`.
PSPDF_EXPORT PSPDFDrawingPoint PSPDFDrawingPointFromCGPoint(CGPoint location) NS_SWIFT_NAME(DrawingPoint.init(cgPoint:)) PSPDF_PURE;

/// Extends `NSValue` to deal with `PSPDFDrawingPoint`.
@interface NSValue (PSPDFModel)

/// Creates a new value object containing the specified drawing point structure.
+ (NSValue *)pspdf_valueWithDrawingPoint:(PSPDFDrawingPoint)point NS_SWIFT_NAME(valueWithDrawingPoint(_:));

/// Returns the drawing point structure representation of the value.
@property (nonatomic, readonly) PSPDFDrawingPoint pspdf_drawingPointValue NS_SWIFT_NAME(drawingPointValue);

@end

NS_ASSUME_NONNULL_END
