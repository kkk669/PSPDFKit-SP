//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//
//  Based on GitHub's Mantle project, MIT licensed.
//  Portions Copyright © 2011 Bitswift. BSD licensed.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Macro to cast filter result correct.
#define PSPDFArrayFilterClass(array, className) ((NSArray<className *> *)[array pspdf_filteredKindOfClass:className.class])

/// Higher-order functions for `NSArray`.
@interface NSArray <ObjectType> (PSPDFFoundation)

/// Version that accepts nullable.
+ (instancetype)pspdf_arrayWithArray:(nullable NSArray<ObjectType> *)array;

/// @return an array if `anObject` is not nil, else returns nil.
/// Shorthand version of the pattern `obj ? @[obj] : nil;`
+ (nullable instancetype)pspdf_arrayWithObject:(nullable ObjectType)anObject;

/// Shortcut variant to conditionally wrap an object into an array if the object is not nil.
#define PSPDFArrayIf(obj) ([NSArray pspdf_arrayWithObject:obj])

/// Checks if an enumerable object has elements and returns nil if it does not.
/// This is a macro to perfectly preserve type information.
#define PSPDFNilIfEmpty(obj) ((obj.count > 0) ? obj : nil)

/// Combines two arrays, using arrayByAddingObjectsFromArray:, while also handling nil cases for both.
#define PSPDFMergeArray(first, second) (first.count == 0 ? second : (second.count == 0 ? first : [first arrayByAddingObjectsFromArray:second]))

/// Returns the first element that matches class c.
/// Useful for tail returns to save on casts.
#define PSPDFCastFirst(array, c) ((c * _Nullable)[(array) pspdf_objectKindOfClass:c.class])

/// Variant that checks bounds and returns nil if out of bounds instead of throwing.
- (nullable ObjectType)pspdf_objectAtIndex:(NSUInteger)index;

/// Convert an `NSArray` of `NSNumber`s to an `NSIndexSet`.
@property (nonatomic, readonly) NSIndexSet *pspdf_indexSet;

/// Variant of `containsObject:` that accepts `nil` and returns `false` in that case.
- (BOOL)pspdf_containsObject:(nullable ObjectType)anObject;

/// Variant of `indexOfObjectPassingTest:` that returns `true` if any object in the
/// array passes a test in a given block.
///
/// @param predicate The test to apply to each element in the receiver. This block
/// should return whether the object passed the test.
- (BOOL)pspdf_containsObjectPassingTest:(NS_NOESCAPE BOOL (^)(id anObject, NSUInteger idx, BOOL *stop))predicate;

/// Returns a Boolean value that indicates whether every object in the receiving array
/// passes a test in a given block. Returns NO if the array is empty.
///
/// @param predicate The test to apply to each element in the receiver.
/// @return YES is all objects pass the test. NO if any object fails the test or the array is empty.
- (BOOL)pspdf_doAllObjectsPassTest:(NS_NOESCAPE BOOL (^)(id anObject, NSUInteger idx))predicate;

/// Returns an array of filtered objects for which `block` returns true.
///
/// @param block A predicate block that determines whether to include or exclude
/// a given object.
- (NSArray<ObjectType> *)pspdf_filtered:(NS_NOESCAPE BOOL (^)(ObjectType obj))block;

/// Only allow entries that are `targetClass` or a subclass thereof.
- (NSArray<__kindof ObjectType> *)pspdf_filteredKindOfClass:(Class)targetClass;

/// Returns an array of filtered objects for which `block` returns `true`, and
/// sets `failedObjects` to an array of the objects for which `block` returned
/// `false`.
///
/// @param failedObjects If not `NULL`, this will be a collection of all the
/// objects for which `block` returned `false`. If no objects failed, this will be
/// an empty array.
/// @param block A predicate with which to filter objects in the receiver. If
/// this block returns `true`, the object will be added to the returned
/// collection. If this block returns `false`, the object will be added to
/// `failedObjects`.
- (NSArray<ObjectType> *)pspdf_filteredArrayWithFailedObjects:(out NSArray * _Nullable __strong * _Nonnull)failedObjects usingBlock:(NS_NOESCAPE BOOL (^)(ObjectType obj))block;

/// Variant of `indexOfObject:` that accepts `nil`, and returns `NSNotFound` in that case.
- (NSUInteger)pspdf_indexOfObject:(nullable ObjectType)anObject;

/// Transforms each object in the receiver with the given block, returning
/// a new array built from the resulting objects.
///
/// @param block A block with which to transform each element. The element from
/// the receiver is passed in as the `obj` argument.
///
/// @warning **Important:** It is permissible to return `nil` from `block`, but
/// doing so will omit an entry from the resultant array, such that the number of
/// objects in the result is less than the number of objects in the receiver. If
/// you need the arrays to match in size, return `NSNull` instead of `nil`.
- (NSArray *)pspdf_mapped:(NS_NOESCAPE id _Nullable (^)(ObjectType obj))block;

/// Returns a new, one-dimensional array that is a recursive flattening of
/// the receiver.
///
/// id rv = @[@[@1, @[@2]], @3, @[@4]].flatten
/// // rv => @[@1, @2, @3, @4]
@property (nonatomic, readonly) NSArray *pspdf_flattened;

/**
 * Returns a new array with the concatenated results of running block once
 * for every element in the receiver.
 *
 * id rv = @[@1, @2, @3, @4].flatMap(^(id n){
 *   return @[n, n];
 * });
 * // rv => @[@1, @1, @2, @2, @3, @3, @4, @4]
 *
 * id rv = @[@1, @2, @3, @4].flatMap(^(id n){
 *    return @[n, @[n]];
 * });
 * // rv => @[@1, @[@1], @2, @[@2], @3, @[@3], @4, @[@4]]
 */
- (NSArray *)pspdf_flatMap:(NS_NOESCAPE NSArray *_Nullable (^)(ObjectType obj))block;

/// Performs a set of operations on a mutable copy, then returns a new immutable array.
- (NSArray<ObjectType> *)pspdf_mutatedArrayUsingBlock:(NS_NOESCAPE void (^)(NSMutableArray<ObjectType> *mutableArray))block;

/// Returns the first object in the receiver that passes the given test, or `nil`
/// if no such object exists.
///
/// @param predicate The test to apply to each element in the receiver. This block
/// should return whether the object passed the test.
- (nullable ObjectType)pspdf_objectPassingTest:(NS_NOESCAPE BOOL (^)(ObjectType obj))predicate;

/// Returns the first object that is of type `targetClass. Returns nil if no match was found.
- (nullable __kindof ObjectType)pspdf_objectKindOfClass:(Class)targetClass;

/// Returns the first object in the receiver that passes the given test, or `nil`
/// if no such object exists.
///
/// @param opts A mask of `NSEnumerationOptions` to apply when enumerating.
/// @param predicate The test to apply to each element in the receiver. This block
/// should return whether the object passed the test.
- (nullable ObjectType)pspdf_objectWithOptions:(NSEnumerationOptions)opts passingTest:(NS_NOESCAPE BOOL (^)(ObjectType obj, NSUInteger index, BOOL *stop))predicate;

/// Converts the current array into a weak array.
@property (nonatomic, readonly) NSPointerArray *pspdf_weakArray NS_SWIFT_UNAVAILABLE("Unlikely to be useful in Swift");

/// Removes any duplicates from the array.
@property (nonatomic, readonly) NSArray<ObjectType> *pspdf_uniqueArray NS_SWIFT_NAME(uniqued);

/// Returns an array where each object it contains is copied.
@property (nonatomic, readonly) NSArray<ObjectType> *pspdf_deepCopyArray NS_SWIFT_NAME(deepCopy);

/// Returns a random object from the receiver and optionally the index of the object.
///
/// @param index After this method returns, contains the index of the object.
/// @return A random object from the receiver or nil if the array is empty.
- (nullable ObjectType)pspdf_randomObject:(out NSInteger *_Nullable)index;

@end

@interface NSMutableArray <ObjectType> (PSPDFQueue)

- (nullable ObjectType)pspdf_dequeue;
- (void)pspdf_enqueue:(ObjectType)object;
- (void)pspdf_enqueueFromArray:(NSArray *)objects;

@end

@interface NSMutableArray <ObjectType> (PSPDFStack)

- (nullable ObjectType)pspdf_pop;
- (void)pspdf_push:(ObjectType)object;

@end

@interface NSMutableArray <ObjectType> (PSPDFHigherOrderAdditions)

/// Filters the current array to objects for which `block` returns true.
///
/// @param block A predicate block that determines whether to include or exclude
/// a given object.
- (void)pspdf_filter:(NS_NOESCAPE BOOL (^)(ObjectType obj))block;

/// Only allow entries that are `targetClass` or a subclass thereof.
- (void)pspdf_filterKindOfClass:(Class)targetClass;

@end

@interface NSMutableArray <ObjectType> (PSPDFNullable)

/// Version of addObject: accepting nil.
- (void)pspdf_addObject:(nullable ObjectType)anObject;

/// Version of addObjectsFromArray: accepting nil.
- (void)pspdf_addObjectsFromArray:(nullable NSArray<ObjectType> *)otherArray;

@end

#ifdef __cplusplus

namespace PSPDF {

    template <typename ObjectType, typename MappedType>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
    NSArray<MappedType> *_Nonnull mapped(NSArray<ObjectType> *_Nullable array, NS_NOESCAPE MappedType _Nullable (^block)(_Nonnull ObjectType)) {
    return (NSArray<MappedType> *)(array ? [array pspdf_mapped:block] : @[]);
}
#pragma clang diagnostic pop
}

#endif

NS_ASSUME_NONNULL_END
