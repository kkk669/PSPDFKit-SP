//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFRectAlignment.h>
#import <PSPDFKit/PSPDFRotation.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFRectAlignment.h"
#import "PSPDFRotation.h"
#endif

#import <CoreGraphics/CoreGraphics.h>

#ifdef __cplusplus
#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFHigherOrderFunctions.hpp>
#else
#import "PSPDFHigherOrderFunctions.hpp"
#endif
#import <vector>
#endif

NS_ASSUME_NONNULL_BEGIN

/// Converts from degrees to radians.
PSPDF_SDK_EXPORT CGFloat PSPDFRadiansFromDegrees(CGFloat degrees) NS_SWIFT_NAME(radiansFromDegrees(_:));

/// Converts from radians to degrees.
PSPDF_SDK_EXPORT CGFloat PSPDFDegreesFromRadians(CGFloat radian) NS_SWIFT_NAME(degreesFromRadians(_:));

/// Normalizes a radian value by checking that it's at least 2xπ.
PSPDF_SDK_EXPORT CGFloat PSPDFNormalizedRadian(CGFloat radian);

/// Checks if a > b, accounting for floating point rounding issues.
PSPDF_TEST_EXPORT BOOL PSPDFDefinitelyGreaterThan(CGFloat a, CGFloat b);

/// Checks if a < b, accounting for floating point rounding issues.
PSPDF_SDK_EXPORT BOOL PSPDFDefinitelyLessThan(CGFloat a, CGFloat b);

/// Checks if a == b, accounting for floating point rounding issues.
PSPDF_SDK_EXPORT BOOL PSPDFDefinitelyEqual(CGFloat a, CGFloat b);

/// Similar to CGPointZero, but this shows that the point is not initialized, while (0,0) is valid.
PSPDF_SDK_EXPORT const CGPoint PSPDFPointNil;

/// Returns the point between p1 and p2.
PSPDF_SDK_EXPORT CGPoint PSPDFMidPoint(CGPoint p1, CGPoint p2);

/// Calculates the centroid between multiple points. If you provide an array with
/// no points, `CGPointZero` will be returned.
PSPDF_SDK_EXPORT CGPoint PSPDFCentroidOfPoints(CGPoint *points, NSUInteger count);

/// Calculates the centroid between multiple points. If you provide an array with
/// no points, `CGPointZero` will be returned.
PSPDF_SDK_EXPORT CGPoint PSPDFCentroidOfBoxedPoints(NSArray<NSValue /* CGPoint */ *> *boxedPoints);

/// Calculates a point on the perpendicular bisector with the given distance from the line defined by the two endpoints.
PSPDF_SDK_EXPORT CGPoint PSPDFPointOnPerpendicularBisector(CGPoint point1, CGPoint point2, CGFloat distance);

/// Calculates a vector from `point1` to `point2`.
PSPDF_SDK_EXPORT CGVector PSPDFVectorWithPoints(CGPoint point1, CGPoint point2);

/// Calculates the minimum bounding rect.
///
/// The minimum bounding rect is the smallest possible rectangle that contains all points.
///
/// @note If you provide an array with 0 points, CGRectZero will be returned.
PSPDF_SDK_EXPORT CGRect PSPDFCalculateMinimumBoundingRect(CGPoint *points, NSUInteger count);

/// Calculates the minimum smallest rect that encompasses all the input points.
///
/// @param boxedPoints An array of `NSValue`s containing CGPoints.
/// @return The smallest bounding rect for the input.
PSPDF_SDK_EXPORT CGRect PSPDFCalculateMinimumBoundingRectFromBoxedPoints(NSArray<NSValue *> *boxedPoints);

/// Returns the smallest rectangle that encloses all the passed in rectangles.
/// Returns CGRectNull if the array is empty.
PSPDF_SDK_EXPORT CGRect PSPDFUnionOfRects(CGRect *rects, size_t count);

/// Inverts edge insets by multiplying top, bottom, left, and right with -1.0.
PSPDF_SDK_EXPORT UIEdgeInsets PSPDFInvertEdgeInsets(UIEdgeInsets edgeInsets);

/// Appends both edge insets to a bigger one.
PSPDF_SDK_EXPORT UIEdgeInsets PSPDFAppendEdgeInsets(UIEdgeInsets edgeInsets1, UIEdgeInsets edgeInsets2);

/// Returns a new inset with the maximum inset of a and b at every edge.
PSPDF_SDK_EXPORT UIEdgeInsets PSPDFInsetsMax(UIEdgeInsets a, UIEdgeInsets b);

/// Returns a new inset with the minimum inset of a and b at every edge.
PSPDF_SDK_EXPORT UIEdgeInsets PSPDFInsetsMin(UIEdgeInsets a, UIEdgeInsets b);

#if TARGET_OS_IOS

/// Checks on which edges innerRect touches (or overshoots) outerRect.
PSPDF_SDK_EXPORT UIRectEdge PSPDFInsetEdgesInRect(CGRect innerRect, CGRect outerRect);

/// Insets the rect horizontally by dx and vertically by dy on all passed in edges.
PSPDF_SDK_EXPORT CGRect PSPDFInsetRectOnEdges(CGRect rect, CGFloat dx, CGFloat dy, UIRectEdge edges);

/// Returns a mask of rect edges that are coined by the given corner(s).
PSPDF_SDK_EXPORT UIRectEdge PSPDFEdgesJoinedByCorners(UIRectCorner corners);

/// Returns a rect edge that is on the opposite side of the given edge.
PSPDF_SDK_EXPORT UIRectEdge PSPDFOppositeRectEdge(UIRectEdge edge);

#endif

/// Calculates the distance between two points. (hypotenuse)
PSPDF_SDK_EXPORT CGFloat PSPDFDistanceBetweenPoints(CGPoint p1, CGPoint p2);

/// Calculates the angle (in degrees) of the line between two points.
PSPDF_SDK_EXPORT CGFloat PSPDFAngleBetweenPoints(CGPoint p1, CGPoint p2);

/// Calculates the angle (in radians) of the line between two points.
PSPDF_SDK_EXPORT CGFloat PSPDFAngleBetweenPointsInRadians(CGPoint p1, CGPoint p2);

/// Calculates the angle (in radians) created by the intersection of the two lines.
/// Angle between the line at the point of intersection increases as the second line starts deviating (direction of the line towards the second point)
/// farther from the direction in which the first line is extending i.e. the second point (line1Point2).
/// See comment for pictorial representation: https://github.com/PSPDFKit/PSPDFKit/pull/32759#discussion_r811360356
PSPDF_SDK_EXPORT CGFloat PSPDFAngleBetweenLines(CGPoint line1Point1, CGPoint line1Point2, CGPoint line2Point1, CGPoint line2Point2);

/// Calculates the shortest distance between a point and line.
/// Returns the perpendicular distance of the point from the line.
PSPDF_SDK_EXPORT CGFloat PSPDFDistanceBetweenPointAndLine(CGPoint point, CGPoint linePoint1, CGPoint linePoint2);

/// Returns the shortest distance between the edge of a rectangle and a point outside that rectangle, or 0 if the point is inside the rectangle.
/// The returned value is always positive.
/// Should not be called with CGRectNull since it does not know if zero or infinity is a more logical fallback value; it will log and error and return zero in that case.
PSPDF_SDK_EXPORT CGFloat PSPDFDistanceBetweenPointAndRect(CGPoint point, CGRect rect);

/// Calculates a new rectangle expanded by a line width (requires a positive line width).
PSPDF_SDK_EXPORT CGRect PSPDFGrowRectByLineWidth(CGRect boundingBox, CGFloat lineWidth);

/// Calculates a new rectangle inset by a line width (requires a positive line width).
PSPDF_SDK_EXPORT CGRect PSPDFInsetRectByLineWidth(CGRect boundingBox, CGFloat lineWidth);

/// Insets a CGRect by a percentage of its current size
PSPDF_SDK_EXPORT CGRect PSPDFRectScale(CGRect rect, CGFloat scale);

/// Returns scale to fit a size within another size.
PSPDF_SDK_EXPORT CGFloat PSPDFScaleForSizeWithinSize(CGSize targetSize, CGSize boundsSize) NS_SWIFT_NAME(scaleForSize(targetSize:boundsSize:));

/// Returns scale to fit a size within another size, with optional zooming.
PSPDF_APP_EXPORT CGFloat PSPDFScaleForSizeWithinSizeWithOptions(CGSize targetSize, CGSize boundsSize, BOOL zoomMinimalSize, BOOL fitToWidthEnabled) NS_SWIFT_NAME(scaleForSize(targetSize:boundsSize:zoomMinimalSize:fitToWidthEnabled:));

/// Helper to calculate new size for specific scale and size.
PSPDF_APP_EXPORT CGSize PSPDFSizeForScale(CGSize size, CGFloat scale);

/// Returns a size that fits the given constraints.
PSPDF_APP_EXPORT CGSize PSPDFSizeThatFits(CGSize size, CGSize constraints);

/// Returns a rectangle with the specified size aligned to `rect` with the specified PSPDFRectAlignment. Usually used to center.
PSPDF_APP_EXPORT CGRect PSPDFAlignSizeInRect(CGSize size, CGRect rect, PSPDFRectAlignment alignment);

/// Returns a rectangle with the specified size aligned to `rect` with the specified PSPDFRectAlignment. Makes sure the results are rounded to integer valued rects.
PSPDF_APP_EXPORT CGRect PSPDFAlignSizeInRectIntegral(CGSize size, CGRect rect, PSPDFRectAlignment alignment);

/// Creates a rect with the given aspect ratio, aligned inside the given rect and offset
/// by the given offset in the coordinate space of the aspect ratio.
///
/// @param aspectRatio The aspect ratio the new rect should have.
/// @param bounds The bounds inside which the new rect should be.
/// @param widthOffset The width offset, in aspectRatio coordinate space (i.e. before the size transform).
/// @param heightOffset The height offset, in aspectRatio coordinate space (i.e. before the size transform).
/// @param alignment The alignment of the new rect inside the given bounds.
/// @return The newly created rect.
PSPDF_SDK_EXPORT CGRect PSPDFAlignSizeWithinRectWithOffset(CGSize aspectRatio, CGRect bounds, CGFloat widthOffset, CGFloat heightOffset, PSPDFRectAlignment alignment) NS_SWIFT_NAME(alignSize(size:bounds:widthOffset:heightOffset:alignment:));

/// Flips top / bottom.
PSPDF_SDK_EXPORT PSPDFRectAlignment PSPDFRectAlignmentFlip(PSPDFRectAlignment alignment);

/// Divides a source rectangle into two component rectangles, skipping the given amount of padding in between them.
PSPDF_APP_EXPORT void PSPDFRectDivideWithPadding(CGRect rect, CGRect *_Nullable slicePtr, CGRect *_Nullable remainderPtr, CGFloat sliceAmount, CGFloat padding, CGRectEdge edge);

/// Similar to `CGRectInset`, but will return a nil size instead of CGRectNull if size < margin.
PSPDF_APP_EXPORT CGRect PSPDFRectSafeInset(CGRect rect, CGFloat dx, CGFloat dy);

/// Ensures an angle in degrees is in the range 0 to 359. Use this for free-form rotation. For page rotation, use `PSPDFNormalizePageRotation` instead.
PSPDF_SDK_EXPORT NSUInteger PSPDFNormalizeDegrees(NSInteger degrees);

/// Normalizes page rotation values (returns 0, 90, 180, or 270). For free-form rotation, use `PSPDFNormalizeDegrees` instead.
PSPDF_SDK_EXPORT PSPDFRotation PSPDFNormalizePageRotation(NSInteger rotationInDegrees);

/// Encodes a rotation value more space efficiently.
PSPDF_EXTERN uint8_t PSPDFEncodePageRotation(PSPDFRotation rotationInDegrees);

/// Decodes a rotation value encoded with `PSPDFEncodePageRotation`.
PSPDF_EXTERN PSPDFRotation PSPDFDecodePageRotation(uint8_t pdfRotation);

/// Rotates rect.size.width with `rect.size.height` if rotation is 90 or 270 (normalized).
PSPDF_EXTERN BOOL PSPDFSwapRectSizeIfNeeded(NSUInteger rotation, CGRect *rect);

/// Apply rotation to specific rect
PSPDF_SDK_EXPORT CGRect PSPDFApplyRotationToRect(CGRect pageRect, PSPDFRotation rotation);

/// Get the transform to rotate `rect` around its center using `rotation`.
PSPDF_EXTERN CGAffineTransform PSPDFRotationAroundCenterTransform(CGRect rect, NSInteger rotation);

/// Rotate a rect around its center point
PSPDF_SDK_EXPORT CGRect PSPDFRotateRectAroundCenter(CGRect rect, NSInteger rotation);

/// Rotate a size around its center.
PSPDF_SDK_EXPORT CGSize PSPDFRotateSizeAroundCenter(CGSize size, NSInteger rotation);

/// Get the transform for a change between `oldRect` and `newRect`.
/// Optionally also returns if there's a size change at al via `sizeDidChange`.
/// If `meanScale` is backed, it calculates the sqrt of width and height differences.
PSPDF_EXTERN CGAffineTransform PSPDFTransformByComparingRects(CGRect oldRect, CGRect newRect, BOOL *_Nullable sizeDidChange, CGFloat *_Nullable meanScale);

/// Calculates a `CGAffineTransform` that is properly set up for the PDF coordinate system.
///
/// @param initialTransform The current transform.
/// @param size The size that represents the PDF drawable area.
/// @return The transform.
PSPDF_SDK_EXPORT CGAffineTransform PSPDFTransformForPDFContext(CGAffineTransform initialTransform, CGSize size);

/// Normalizes a rect. PDF rectangles might have negative width/height, so this turns them around.
PSPDF_EXTERN CGRect PSPDFNormalizeRect(CGRect rect);

/// Converts a null rect into a zero rect, otherwise passes through.
PSPDF_SDK_EXPORT CGRect PSPDFZeroForNullRect(CGRect rect);

/// Returns a cached version of the UIScreen.mainScreen.scale on iOS,
/// and always 1.0 on macOS.
///
/// This function ist exported as public API from PSPDFModel (`UIScreen+PSPDFAdditions`).
PSPDF_TEST_EXPORT CGFloat PSPDFDefaultScale(void);

/// Rounds to pixel boundaries taking into account the screen scale and the zoom scale.
PSPDF_SDK_EXPORT CGRect PSPDFRoundRectWithZoomScale(CGRect rect, CGFloat screenScale, CGFloat zoomScale);

/// Rounds to pixel boundaries taking screen scale into account.
PSPDF_APP_EXPORT CGRect PSPDFRoundRect(CGRect rect, CGFloat screenScale);

/// Rounds a rect to a given accuracy.
///
/// @param rect The rect to round.
/// @param accuracy The accuracy. The new value is calculated like this: round(value * accuracy) / accuracy.
/// @return The rounded rect.
PSPDF_APP_EXPORT CGRect PSPDFRoundRectWithAccuracy(CGRect rect, CGFloat accuracy);

#if DEBUG
/// Rounds to pixels taking into account the screen scale and the zoom scale.
PSPDF_SDK_EXPORT CGPoint PSPDFRoundPointWithZoomScale(CGPoint point, CGFloat zoomScale, CGFloat screenScale);
#endif

/// Rounds to pixels (0.5 step on retina)
PSPDF_TEST_EXPORT CGPoint PSPDFRoundPoint(CGPoint point, CGFloat screenScale);

/// Rounds to pixels (0.5 step on retina)
PSPDF_SDK_EXPORT CGSize PSPDFRoundSize(CGSize size, CGFloat screenScale);

/// Floors to pixels (0.5 step on retina)
PSPDF_SDK_EXPORT CGSize PSPDFFloorSize(CGSize size, CGFloat screenScale);

/// Rounds to pixels (0.5 step on retina)
PSPDF_TEST_EXPORT CGFloat PSPDFRoundFloat(CGFloat value, CGFloat screenScale);

/// Builds a rect out of two CGPoints.
PSPDF_SDK_EXPORT CGRect PSPDFRectFromPoints(CGPoint p1, CGPoint p2);

/// Whether or not the width or height of this size is not greater than zero.
///
/// Most of the time, you couldn’t care less about whether a size is exactly 0. Instead,
/// you want to know whether a size will “behave well” in further computation or likely
/// to cause trouble. This function answers the question, returning `true` when the
/// value is likely to cause trouble in further processing.
///
/// ### Examples
///
/// - `PSPDFSizeIsNotPositive(CGSizeMake(123, 456))` returns `false` — obviously
/// - `PSPDFSizeIsNotPositive(CGSizeZero)` returns `true`
/// - `PSPDFSizeIsNotPositive(CGRectNull.size)` returns `true` — because of the above
/// - `PSPDFSizeIsNotPositive(CGSizeMake(123, -456))` returns `true` — obviously
/// - `PSPDFSizeIsNotPositive(CGSizeMake(-123, 456))` returns `true` — same same, but different
/// - `PSPDFSizeIsNotPositive(CGSizeMake(-123, -456))` returns `true` — two wrongs don’t make one right
/// - `PSPDFSizeIsNotPositive(CGSizeMake(-0, 1))` returns `true` — negative zero is a thing
/// - `PSPDFSizeIsNotPositive(CGSizeMake(nan(""), 1))` returns `false` — NaN is a positive value in floating point math
/// - `PSPDFSizeIsNotPositive(CGSizeMake(-nan(""), 1))` returns `false` — as is `-NaN`!
PSPDF_SDK_EXPORT bool PSPDFSizeIsNotPositive(CGSize size);

/// Returns float if valid or 0.
PSPDF_SDK_EXPORT CGFloat PSPDFFloatEnsureValid(CGFloat aFloat);

/// Checks if none of the rect components are infinite or NaN.
PSPDF_SDK_EXPORT bool PSPDFRectIsFinite(CGRect rect);

/// Checks if none of the size components are infinite or NaN.
PSPDF_SDK_EXPORT bool PSPDFSizeIsFinite(CGSize size);

/// Returns `size` or CGSizeZero if invalid
PSPDF_SDK_EXPORT CGSize PSPDFSizeEnsureValid(CGSize size);

/// Checks if none of the point components are infinite or NaN.
PSPDF_SDK_EXPORT bool PSPDFPointIsFinite(CGPoint point);

/// Returns point if valid or CGPointZero.
PSPDF_SDK_EXPORT CGPoint PSPDFPointEnsureValid(CGPoint point);

/// Checks if none of the transform components are infinite or NaN.
PSPDF_SDK_EXPORT bool PSPDFTransformIsFinite(CGAffineTransform transform);

/// Checks if none of the transform 3D components are infinite or NaN.
PSPDF_EXTERN bool PSPDFTransform3DIsFinite(CATransform3D transform);

/// Combines fminf and fmaxf to limit a value between a range.
PSPDF_APP_EXPORT CGFloat psrange(CGFloat minRange, CGFloat value, CGFloat maxRange);

/// Default accuracy for comparison. Defaults to 0.001;
PSPDF_TEST_EXPORT const CGFloat PSPDFDefaultAccuracy;

/// Compares sizes and allows aspect ratio changes.
PSPDF_SDK_EXPORT BOOL PSPDFSizeAspectRatioEqualToSize(CGSize containerSize, CGSize size);

/// Ensures that frame is within outerFrame, embedded by margin.
PSPDF_APP_EXPORT CGRect PSPDFEnsureFrameIsInsideFrame(CGRect frame, CGRect outerFrame, CGFloat margin);

/// Returns true if two rects intersect such that the fraction of overlap is greater than or
/// equal to the given overlapFraction. Returns false if two rects do not intersect regardless
/// of the value of overlapFraction. Valid values of overlapFraction are 0 to 1.
///
/// @note: The overlap is calculated w.r.t the total area. So, if `a1` is the area
/// of rect1, `a2` is the area of rect2 and `ao` is the overlapping area, then fraction of
/// overlap would be ao / (a1 + a2 - ao).
PSPDF_EXTERN BOOL PSPDFRectIntersectsRectWithOverlapFraction(CGRect rect1, CGRect rect2, double overlapFraction);

/// Creates an affine transform from the comparison of `frame` to `targetFrame`.
PSPDF_SDK_EXPORT CGAffineTransform PSPDFAffineTransformFromRectDifferences(CGRect frame, CGRect targetFrame);

/// Create a fairly good hash for a rect.
PSPDF_EXTERN NSUInteger PSPDFHashFromCGRect(CGRect rect);

/// Unions all rects inside the array into one big rect.
PSPDF_SDK_EXPORT CGRect PSPDFUnionRects(NSArray<NSValue *> *rects);

/// Merges two arrays of rects. Tries to merge lines.
PSPDF_SDK_EXPORT NSArray<NSValue *> *PSPDFMergeRects(NSArray<NSValue *> *_Nullable rects, NSArray<NSValue *> *_Nullable otherRects);

/// Get the center point of the rect.
PSPDF_TEST_EXPORT CGPoint PSPDFRectGetCenter(CGRect rect);

/// Round rect to nearest size, if it's close.
PSPDF_SDK_EXPORT CGRect PSPDFRoundCompoundViewSize(CGRect compoundViewRect, CGRect superviewFrame, CGFloat screenScale);

/// Converts a point from `sourceFrame` to `targetFrame` and flips the Y-axis.
PSPDF_EXTERN CGPoint PSPDFConvertPointToPoint(CGPoint point, CGRect sourceFrame, CGRect targetFrame);

/// Convert rect from `sourceFrame` to `targetFrame` using `rotation`.
///
/// @note **Important:** All rects **must** be well formed!
/// That is, negative widths or heights will lead to results that are incorrect in very surprising ways.
PSPDF_EXTERN CGRect PSPDFConvertRectToRect(CGRect rect, CGRect sourceFrame, CGRect targetFrame);

/// Returns `UIEdgeInsets` for the inner rect to fit in the outer rect.
PSPDF_SDK_EXPORT UIEdgeInsets PSPDFEdgeInsetsFromRectToRect(CGRect inner, CGRect outer);

/// Returns `UIEdgeInsets` for the inner rect to fit in the outer rect. Interpreted with origin in the bottom-left.
PSPDF_SDK_EXPORT UIEdgeInsets PSPDFEdgeInsetsFromPDFRectToPDFRect(CGRect inner, CGRect outer);

/// Returns `UIEdgeInsets` with all negative values set to 0 and all positive values left untouched.
PSPDF_EXTERN UIEdgeInsets PSPDFEnsurePositiveEdgeInsets(UIEdgeInsets insets);

/// Converts a vector to a unit vector and optionally returns the length of the original vector.
///
/// @param vector The vector to convert to a unit vector.
/// @param length The length of the vector before it was converted to a unit vector.
/// @return A vector pointing in the same direction than the original vector but with a length of 1.
PSPDF_SDK_EXPORT CGVector PSPDFUnitVectorFromVector(CGVector vector, CGFloat *_Nullable length);

/// The width for a 1px thin line for the current device.
PSPDF_APP_EXPORT CGFloat PSPDFHairlineWidth(CGFloat screenScale);

/// Iterates over objects, calling `rectGenerator` and builds the union of all objects.
/// Returns CGRectNull if there are no objects set.
PSPDF_APP_EXPORT CGRect PSPDFUnionRectsWithBlock(id<NSFastEnumeration> _Nullable objects, CGRect (^rectGenerator)(id object));

/// Creates a rect from a given size and a center point.
PSPDF_SDK_EXPORT CGRect PSPDFRectForSizeWithCenter(CGSize size, CGPoint center);

#ifndef __cplusplus

/// `CGRect`/`CGSize`/`CGPoint` comparison methods that allow a comparison delta.
PSPDF_TEST_EXPORT BOOL PSPDFRectEqualToRectWithAccuracy(CGRect rect, CGRect rect2, CGFloat epsilon);

PSPDF_TEST_EXPORT BOOL PSPDFSizeEqualToSizeWithAccuracy(CGSize size, CGSize size2, CGFloat epsilon);

PSPDF_TEST_EXPORT BOOL PSPDFPointEqualToPointWithAccuracy(CGPoint p, CGPoint q, CGFloat epsilon);

PSPDF_TEST_EXPORT BOOL PSPDFEdgeInsetsEqualToEdgeInsetsWithAccuracy(UIEdgeInsets insets1, UIEdgeInsets insets2, CGFloat epsilon);

/// Tests if the affine transform `t1` is equal to `t2` while allowing `epsilon` as error margin.
PSPDF_EXTERN BOOL PSPDFAffineTransformEqualToTransformWithAccuracy(CGAffineTransform t1, CGAffineTransform t2, CGFloat epsilon);

#else

/// `CGRect`/`CGSize`/`CGPoint` comparison methods that allow a comparison delta.
PSPDF_TEST_EXPORT BOOL PSPDFRectEqualToRectWithAccuracy(CGRect rect, CGRect rect2, CGFloat epsilon = PSPDFDefaultAccuracy);

PSPDF_TEST_EXPORT BOOL PSPDFSizeEqualToSizeWithAccuracy(CGSize size, CGSize size2, CGFloat epsilon = PSPDFDefaultAccuracy);

PSPDF_TEST_EXPORT BOOL PSPDFPointEqualToPointWithAccuracy(CGPoint p, CGPoint q, CGFloat epsilon = PSPDFDefaultAccuracy);

PSPDF_TEST_EXPORT BOOL PSPDFEdgeInsetsEqualToEdgeInsetsWithAccuracy(UIEdgeInsets insets1, UIEdgeInsets insets2, CGFloat epsilon = PSPDFDefaultAccuracy);

/// Tests if the affine transform `t1` is equal to `t2` while allowing `epsilon` as error margin.
PSPDF_EXTERN BOOL PSPDFAffineTransformEqualToTransformWithAccuracy(CGAffineTransform t1, CGAffineTransform t2, CGFloat epsilon = PSPDFDefaultAccuracy);

/// C++ helper for convenient struct arithmetic.
PSPDF_SDK_VISIBLE CGPoint operator/(const CGPoint &, CGFloat);
PSPDF_SDK_VISIBLE CGPoint operator*(CGFloat, const CGPoint &);
PSPDF_SDK_VISIBLE CGPoint operator*(const CGPoint &, CGFloat);
PSPDF_SDK_VISIBLE CGPoint &operator+=(CGPoint &, const CGSize &);
PSPDF_SDK_VISIBLE CGRect &operator+=(CGRect &, const CGRect &);
PSPDF_SDK_VISIBLE CGRect operator*(const CGRect &lhs, CGFloat a);
PSPDF_SDK_VISIBLE const CGSize operator+(const CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE CGSize operator-(const CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE CGSize &operator+=(CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE CGSize &operator-=(CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE CGSize &operator/=(CGSize &, CGFloat);
PSPDF_SDK_VISIBLE CGSize operator*(CGFloat, const CGSize &);
PSPDF_SDK_VISIBLE CGSize operator*(const CGSize &, CGFloat);
PSPDF_SDK_VISIBLE CGSize &operator*=(CGSize &, CGFloat);
PSPDF_SDK_VISIBLE CGSize operator/(const CGSize &, CGFloat);

PSPDF_SDK_VISIBLE const CGPoint operator+(const CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE CGPoint operator-(const CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE CGPoint &operator+=(CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE CGPoint &operator-=(CGPoint &, const CGPoint &);

PSPDF_SDK_VISIBLE CGRect operator&(const CGPoint &, const CGSize &);

PSPDF_SDK_VISIBLE bool operator==(const CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE bool operator!=(const CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE bool operator>(const CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE bool operator>=(const CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE bool operator<(const CGPoint &, const CGPoint &);
PSPDF_SDK_VISIBLE bool operator<=(const CGPoint &, const CGPoint &);

PSPDF_SDK_VISIBLE bool operator==(const CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE bool operator!=(const CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE bool operator>(const CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE bool operator>=(const CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE bool operator<(const CGSize &, const CGSize &);
PSPDF_SDK_VISIBLE bool operator<=(const CGSize &, const CGSize &);

PSPDF_SDK_VISIBLE bool operator==(const CGRect &, const CGRect &);
PSPDF_SDK_VISIBLE bool operator!=(const CGRect &, const CGRect &);
PSPDF_SDK_VISIBLE bool operator>(const CGRect &, const CGRect &);
PSPDF_SDK_VISIBLE bool operator>=(const CGRect &, const CGRect &);
PSPDF_SDK_VISIBLE bool operator<(const CGRect &, const CGRect &);
PSPDF_SDK_VISIBLE bool operator<=(const CGRect &, const CGRect &);

namespace std {
template <> struct hash<CGSize> {
    size_t operator()(const CGSize &size) const { PSPDF_ALLOW_CAST_QUALIFIERS(return (*(NSUInteger *)&size.width << 10 ^ *(NSUInteger *)&size.height);) }
};

template <> struct hash<CGRect> {
    size_t operator()(const CGRect &rect) const { return PSPDFHashFromCGRect(rect); }
};
}

inline bool operator==(const UIEdgeInsets &lhs, const UIEdgeInsets &rhs) { return (lhs.top == rhs.top) && (lhs.bottom == rhs.bottom) && (lhs.left == rhs.left) && (lhs.right == rhs.right); }

inline bool operator!=(const UIEdgeInsets &lhs, const UIEdgeInsets &rhs) { return !(lhs == rhs); }

inline UIEdgeInsets operator+(const UIEdgeInsets &e1, const UIEdgeInsets &e2) { return {e1.top + e2.top, e1.left + e2.left, e1.bottom + e2.bottom, e1.right + e2.right}; }

inline UIEdgeInsets operator-(const UIEdgeInsets &e1, const UIEdgeInsets &e2) { return {e1.top - e2.top, e1.left - e2.left, e1.bottom - e2.bottom, e1.right - e2.right}; }

inline UIEdgeInsets operator*(const UIEdgeInsets &e1, const UIEdgeInsets &e2) { return {e1.top * e2.top, e1.left * e2.left, e1.bottom * e2.bottom, e1.right * e2.right}; }

inline UIEdgeInsets operator-(const UIEdgeInsets &e) { return {-e.top, -e.left, -e.bottom, -e.right}; }

inline UIEdgeInsets operator/(const UIEdgeInsets &e, const CGFloat divisor) { return {e.top / divisor, e.left / divisor, e.bottom / divisor, e.right / divisor}; }

inline UIEdgeInsets operator*(const UIEdgeInsets &e, const CGFloat factor) { return {e.top * factor, e.left * factor, e.bottom * factor, e.right * factor}; }

#endif

NS_ASSUME_NONNULL_END
