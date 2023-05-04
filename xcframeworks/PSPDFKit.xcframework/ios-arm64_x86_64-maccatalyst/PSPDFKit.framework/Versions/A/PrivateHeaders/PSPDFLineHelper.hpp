//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#pragma once

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFLineHelper.h>
#import <PSPDFKit/PSPDFDrawingPoint.hpp>
#import <PSPDFKit/PSPDFHigherOrderFunctions.hpp>
#import <CoreGraphics/CoreGraphics.h>

#ifdef __cplusplus
#import <vector>

@class PSPDFAnnotation;

/**
 Calculates the perimeter for a given polygon.

 The perimeter is the sum of the length of all sections in the polygon, that is
 the sum of the distance between a point p_k and p_k+1.
 */
CGFloat PSPDFPolygonPerimeter(std::vector<CGPoint> const &points);

/// Return YES if points for the polygon is given in clockwise direction, otherwise returns NO.
BOOL PSPDFPolygonPathIsClockwise(std::vector<PSPDF::DrawingPoint> const &points);

/// Returns polygon path with a "cloudy" border effect applied.

CF_IMPLICIT_BRIDGING_ENABLED

PSPDF_APP_EXPORT CGPathRef PSPDFCreateCloudyPathForPolygon(std::vector<PSPDF::DrawingPoint> const &points, CGFloat intensity, BOOL closed);

/// Returns polygon path.
CGPathRef PSPDFCreatePathForPolygon(std::vector<PSPDF::DrawingPoint> const &points);

/// Returns the line end length.
/// The line end length is the length by which a line is shortened in order to accommodate a line end, so that the outer
/// edge of the line end is at or about at where the line end point would have been if the line had no line ends.
CGFloat PSPDFGetLineEndLength(std::vector<PSPDF::DrawingPoint> const &points, CGFloat lineWidth);

/// Constructs a polyline. Convenience method.
PSPDF_SDK_EXPORT void PSPDFConstructPolyLineBezierPathWithPoints(std::vector<PSPDF::DrawingPoint> const &points, PSPDFLineEndType lineEnd1, PSPDFLineEndType lineEnd2, CGFloat lineWidth, std::vector<CGFloat> lineDashVector, BOOL originUpperLeft, UIBezierPath **outStrokePath, UIBezierPath **outFillPath);

CF_IMPLICIT_BRIDGING_DISABLED

/// Draws a polyline between all given points. The two ends of this line can have a PSPDFLineEndType.
void PSPDFDrawPolyLine(CGContextRef context, std::vector<PSPDF::DrawingPoint> const &points, PSPDFLineEndType lineEnd1, PSPDFLineEndType lineEnd2, CGFloat lineWidth, std::vector<CGFloat> lineDashVector);

/// Converts an array of boxed `PSPDFDrawingPoint`s to a vector.
/// C++ linkage so we use a different exporter.
PSPDF_SDK_CLASS_AVAILABLE std::vector<PSPDF::DrawingPoint> PSPDFDrawingPointArrayToVector(NSArray<NSValue *> *array);

/// Converts the `dashArray` of an annotation into a vector that can be passed into CoreGraphics.
std::vector<CGFloat> PSPDFLineDashVectorForAnnotation(PSPDFAnnotation *annotation);

/// Converts the `dashArray` into a vector that can be passed into in CoreGraphics.
/// If `dashArray` is nil or empty and defaultDashWidth is zero, an empty vector is returned.
PSPDF_SDK_CLASS_AVAILABLE std::vector<CGFloat> PSPDFLineDashVector(NSArray<NSNumber *> *dashArray, CGFloat lineWidth, CGFloat defaultDashWidth = 30.0);

/// Returns the fill and stroke paths corresponding to a given line end type.
std::tuple<PSPDF::CFPointer<CGPathRef>, PSPDF::CFPointer<CGPathRef>> PSPDFFillAndStrokePathForLineEndType(PSPDFLineEndType endType, std::vector<PSPDF::DrawingPoint> const &points, CGFloat lineWidth);

#endif

