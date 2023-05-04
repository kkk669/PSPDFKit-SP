//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDrawingPoint.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Immutable wrapper around a PSPDFDrawingPoint array with boxing/unboxing methods.
PSPDF_TEST_CLASS_SWIFT(PointArray)
@interface PSPDFPointArray : NSObject<NSCopying, NSSecureCoding, NSFastEnumeration>

/// Init with a boxed array, will unbox on load.
///
/// @note `points` will be validated, NaN or Inf values will be filtered out.
- (instancetype)initWithPoints:(NSArray<NSValue /* <PSPDFDrawingPoint> */ *> *)points;

/// Init with a C array of `PSPDFDrawingPoint`s. Will copy the content.
- (instancetype)initWithDrawingPoints:(const PSPDFDrawingPoint[_Nonnull])drawingPoints count:(NSUInteger)count;

/// Direct access to the internal C point structure.
/// Points can be changed (but not the number of them)
@property (nonatomic, readonly) const PSPDFDrawingPoint *drawingPoints;

/// The number of points.
@property (nonatomic, readonly) NSUInteger count;

/// Access internal points wrapped in `NSValue` objects. Thread safe accessor.
@property (atomic, copy, readonly) NSArray<NSValue /* <PSPDFDrawingPoint> */ *> *points;

/// Returns point at `index`. Will return `PSPDFDrawingPointZero` for invalid indexes.
- (PSPDFDrawingPoint)pointAtIndex:(NSUInteger)index;

/// Efficient check against internal points.
- (BOOL)isEqualToPointsArray:(NSArray<NSValue *> *)points NS_SWIFT_UNAVAILABLE("Use Equatable");

/// Enumerate of over all points.
- (void)enumerateDrawingPointsWithBlock:(NS_NOESCAPE void (^)(PSPDFDrawingPoint point, NSUInteger i, BOOL *stop))block;

/// Returns a new container with changed points.
- (PSPDFPointArray *)pointArrayByEnumeratingDrawingPointsWithBlock:(PSPDFDrawingPoint (^)(PSPDFDrawingPoint point, NSUInteger i, BOOL *stop))block;

/// Returns a new container with a mutable PSPDFDrawingPoint C array.
- (PSPDFPointArray *)pointArrayWithMutableDrawingPoints:(NS_NOESCAPE void (^)(PSPDFDrawingPoint *drawingPoints, size_t size))mutableUpdateBlock;

/// Returns a trimmed down version of the current array.
- (PSPDFPointArray *)subPointArrayWithRange:(NSRange)range;

/// Subscripting support.
- (NSValue *)objectAtIndexedSubscript:(NSUInteger)index;

@end

/// Converts arrays of `PSPDFPointArray` objects into an array of array of `NSString`s, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFPointArrayLinesValueTransformerName;

/// Converts a single `PSPDFPointArray` object into an array of `NSString`s, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFPointArrayValueTransformerName;

NS_ASSUME_NONNULL_END
