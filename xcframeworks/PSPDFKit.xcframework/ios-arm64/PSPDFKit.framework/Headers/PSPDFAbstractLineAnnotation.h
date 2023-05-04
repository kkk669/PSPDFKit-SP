//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractShapeAnnotation.h>
#import <PSPDFKit/PSPDFMeasurementAnnotation.h>

/// The possible types of start- and end-point for line annotations.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFLineEndType) {
    /// No special end point. The line just stops here.
    PSPDFLineEndTypeNone,
    /// A small square is drawn centered at this end point of the line, such that the line is parallel to two sides.
    PSPDFLineEndTypeSquare,
    /// A small circle is drawn centered at this end point of the line.
    PSPDFLineEndTypeCircle,
    /// A small square is drawn centered at this end point of the line, such that no side is parallel to the line.
    PSPDFLineEndTypeDiamond,
    /// The line ends in an arrow-head like this one: →
    PSPDFLineEndTypeOpenArrow,
    /// The line ends in an arrow-head like this one: ➞
    PSPDFLineEndTypeClosedArrow,
    PSPDFLineEndTypeButt,
    /// Same as open arrow, but facing towards the other end of the line
    PSPDFLineEndTypeReverseOpenArrow,
    /// Same as closed arrow, but facing towards the other end of the line
    PSPDFLineEndTypeReverseClosedArrow,
    PSPDFLineEndTypeSlash,
} PSPDF_ENUM_SWIFT(AbstractLineAnnotation.EndType);

NS_ASSUME_NONNULL_BEGIN

/// Base class for Line, Polygon and PolyLine annotations.
PSPDF_CLASS_SWIFT(AbstractLineAnnotation)
@interface PSPDFAbstractLineAnnotation : PSPDFAbstractShapeAnnotation <PSPDFMeasurementAnnotation>

/// Designated initializer. Requires an array with at least two points.
- (instancetype)initWithPoints:(NSArray<__kindof NSValue *> *)points NS_REFINED_FOR_SWIFT;

/// Starting line end type.
@property (atomic) PSPDFLineEndType lineEnd1;

/// Ending line end type.
@property (atomic) PSPDFLineEndType lineEnd2;

/// The path of the line.
///
/// Might return nil if there are not sufficient points defined in the annotation.
/// If you override this property, take care to create the path with the annotation's lineDashStyle
@property (atomic, copy, readonly, nullable) UIBezierPath *bezierPath;

/// By default, setting the `boundingBox` will transform the annotation.
/// Use this setter to manually change the boundingBox without changing the points.
- (void)setBoundingBox:(CGRect)boundingBox transformPoints:(BOOL)transformPoints;

/// Call after points have been changed to update the bounding box.
- (void)recalculateBoundingBox;

@end

NS_ASSUME_NONNULL_END
