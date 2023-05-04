//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

// clang-format off
#if __has_include(<QuartzCore/QuartzCore.h>)
#import <QuartzCore/QuartzCore.h>
#endif
// clang-format on

#define PSPDFAllLineEndsAreInside 1 /// Define to 1 to keep all line endings extruding from the line/polyline coordinates to a minimum
/// (i.e. reverse arrow line ends are kept from jutting out past the line/polyline endpoints).
/// The PDF spec is conveniently unclear on this topic, do what is most appealing visually, but
/// since every other line ending is kept inside the endpoints, this is enabled here for consistency.
#define PSPDFPolyJoinStyle kCGLineJoinMiter /// Or kCGLineJoinBevel
#define PSPDFMiterLimit 10.0 /// Avoid miters turning to bevels by supplying a high miter limit

NS_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/// Transforms line end string <-> line end type (PDF reference).
PSPDF_SDK_EXPORT NSValueTransformerName const PSPDFLineEndTypeTransformerName;

/// Draws a line between two points with the specified line end types.
PSPDF_EXTERN void PSPDFDrawLine(CGContextRef context, CGPoint point1, CGPoint point2, PSPDFLineEndType lineEnd1, PSPDFLineEndType lineEnd2, CGFloat lineWidth, NSArray<NSNumber *> *_Nullable lineDashArray);

/// Returns whether the line end type requires a full line.
/// A full line is required if the line end type directly "connects" to the line, e.g. for an open arrow.
PSPDF_EXTERN BOOL PSPDFLineEndNeedsFullLine(PSPDFLineEndType lineEnd);

/// Returns the rectangle encompassing the line end at the first of two points.
PSPDF_EXTERN CGRect PSPDFGetLineEndRectangle(CGPoint point1, CGPoint point2, PSPDFLineEndType lineEnd, CGFloat lineWidth);

/// Returns path for a given rect with a "cloudy" border effect.
PSPDF_EXTERN CGPathRef PSPDFCreateCloudyPathForRect(CGRect rect, CGFloat intensity);

/// Returns path with a "cloudy" border effect bound by a given rect.
PSPDF_SDK_EXPORT CGPathRef PSPDFCreateCloudyPathBoundByRect(CGRect rect, CGFloat intensity);

/// This method creates a shape of an ellipse in a cloudy style. Because ellipses are
/// not very easy to calculate, and expensive as well, this method does three steps:
///
/// - First we sample the ellipse with ~360 points and get a vector of points out of it.
/// These points are all parts of the ellipse and are ordered in a counter clockwise
/// order.
/// - We iterate over the discrete points and calculate the center location of the arcs
/// for the cloudy style. These center locations are all on the path of the sampled
/// ellipse, but if they don't match exactly one point, we interpolate between two
/// points in the samples. This essentially creates a point that is not really on the
/// ellipse, but with ~360 sample points, they are so close to it, that this doesn't
/// matter.
/// - We then iterate over the calculated center points and determine the start and
/// end angles of every circle so that it starts and stops at the intersection points
/// with the previous / next circle.
///
/// @param rect The rectangle in which the cloudy ellipse should be drawn. The ellipse
/// is described by the rects width and the rects height subtracted by
/// the diameter of the cloudy circles which is calculated by the intensity.
/// @param intensity The intensity of the cloud effect. This essentially maps to the
/// radius of the cloud arcs.
///
/// @return A closed path that describes the cloudy annotation.
PSPDF_SDK_EXPORT CGPathRef PSPDFCreateCloudyPathForEllipse(CGRect rect, CGFloat intensity);

/// The length by which a line and the line end is shortened in order to accommodate the line end shape tip.
/// E.g., for PSPDFLineEndTypeOpenArrow, this compensates for the very edge of the arrow shape which would otherwise
/// slightly extend beyond the line end points.
PSPDF_EXTERN CGFloat PSPDFGetLineGetInsetForLineEndType(PSPDFLineEndType type, CGFloat lineWidth);

/// Insets `startPoint` by `byLength` in the direction of the `startPoint` -> `endPoint` vector.
PSPDF_EXTERN CGPoint PSPDFInsettedLineStartByLength(CGPoint startPoint, CGPoint endPoint, CGFloat byLength);

// clang-format off
#if __has_include(<QuartzCore/QuartzCore.h>)
// clang-format on

/// Will update `lineCap` and `lineJoin` depending on the `annotationType` set.
PSPDF_APP_EXPORT void PSPDFUpdateShapeLayerLineStyleForAnnotationType(CAShapeLayer *shapeLayer, PSPDFAnnotationType annotationType);

#endif

CF_IMPLICIT_BRIDGING_DISABLED
NS_ASSUME_NONNULL_END
