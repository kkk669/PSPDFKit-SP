//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFInkAnnotation.h>

@class PSPDFPointArray;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFInkAnnotation ()

// Optimized line container that uses `PSPDFPointArray` instead.
@property (nonatomic, copy, readonly, nullable) NSArray<PSPDFPointArray *> *lineArray;

/// Adds the line to the end of `lines`.
/// Use instead of setter to avoid converting all existing lines to `PSPDFPointArray`.
- (void)appendLine:(NSArray<NSValue *> *)line;

@end

/// Helper to convert `UIBezierPath` into an array of points (of `CGPoints` inside `NSValues`).
PSPDF_EXTERN NSArray<NSValue *> *PSPDFBezierPathGetPoints(UIBezierPath *path);

/// Calculates the natural drawing bounding box from lines.
///
/// @param lines Either an `NSArray<PSPDFPointArray *>` or `NSArray>NSArray<NSValue *> *>`.
PSPDF_EXTERN CGRect PSPDFNaturalDrawingBoundingBoxFromLines(NSArray *lines, CGFloat lineWidth);

/// Returns a new set of lines, with transform applied.
///
/// @param lines Either an `NSArray<PSPDFPointArray *>` or an `NSArray<NSArray<NSValue *> *>`.
/// @return Same type as `lines`
PSPDF_SDK_EXPORT NSArray *PSPDFCopyLinesByApplyingTransform(NSArray *lines, CGAffineTransform transform);

/// Create a spline path or regular path from an array of boxed points.
PSPDF_SDK_EXPORT UIBezierPath *PSPDFBezierPathFromPoints(NSArray<NSValue *> *pointArray, BOOL spline, CGAffineTransform transform);

/// Create a spline path or regular path from an array of point sequences or point arrays.
PSPDF_SDK_EXPORT UIBezierPath *PSPDFBezierPathFromLines(NSArray *_Nullable lines, BOOL spline, CGAffineTransform transform);

/// Create a spline path or regular path from an array of point sequences and appends it to the given bezier path.
/// This uses the same underlying conversion from points to path as PSPDFBezierPathFromLines but can be used for incremental updates to improve performance.
///
/// @param path The bezier path to append the calculated path to
/// @param line The point sequences (array of PSPDFDrawingPoint wrapped in NSValue)
/// @param spline Pass YES to use a spline path, which looks better but takes longer to calculate.
/// @param transform The transform to apply to the appended path.
PSPDF_SDK_EXPORT void PSPDFAddPathFromLineToBezierPath(UIBezierPath *path, NSArray<NSValue *> *line, BOOL spline, CGAffineTransform transform);

/// Compares the two point sequences and determines if thy are equal.
PSPDF_SDK_EXPORT BOOL PSPDFEqualPointSequences(NSArray<NSArray<NSValue *> *> *_Nullable sequences, NSArray<NSArray<NSValue *> *> *_Nullable otherSequences);

NS_ASSUME_NONNULL_END
