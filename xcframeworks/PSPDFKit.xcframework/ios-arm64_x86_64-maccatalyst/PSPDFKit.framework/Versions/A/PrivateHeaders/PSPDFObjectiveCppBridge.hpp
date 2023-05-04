//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//
//  This file helps with bridging ObjC and C++. Enjoy :)

#pragma once

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFastEnumeration.h>
#import <PSPDFKit/NSNumber+PSPDFFoundation.h>
#import <PSPDFKit/PSPDFHigherOrderFunctions.hpp>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFFastEnumeration.h"
#import "NSNumber+PSPDFFoundation.h"
#import "PSPDFHigherOrderFunctions.hpp"
#endif

#import <CoreGraphics/CoreGraphics.h>

#ifdef __cplusplus
#import <optional>
#import <list>
#import <map>
#import <set>
#import <vector>
#import <string>

NS_ASSUME_NONNULL_BEGIN

namespace PSPDF {

/**
 When using `thread_local`, we need a C++ wrapper class as using an ObjC object directly
 isn't supported as of Xcode 9.3. (non-trivial lifetime)
*/
template <typename T>
class ObjCContainer {
public:
    ObjCContainer() : object([T new]) {}
    ObjCContainer(T *_Nonnull type) : object(type) {}
    T *_Nonnull object;
};

template <typename T>
class ObjCNullableContainer {
public:
    ObjCNullableContainer() {}
    ObjCNullableContainer(T *_Nullable type) : object(type) {}
    T *_Nullable object;
};

/// Returns the object if it has at least on child.
template <typename T> inline T _Nullable nn_unless_empty(T _Nullable collection) noexcept { return collection.count > 0 ? PSPDFNN(collection) : nullptr; }

/// Returns the String if it is not empty.
template <> inline NSString *_Nullable nn_unless_empty(NSString *_Nullable string) noexcept { return string.length > 0 ? PSPDFNN(string) : nullptr; }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

/// as? Casts nullable object to type T. Return nil if wrong type.
template <class T> PSPDF_ALWAYS_INLINE T *_Nullable as(id _Nullable o) noexcept {
#ifndef __clang_analyzer__
    if ([o isKindOfClass:[T class]]) {
        return (T * _Nullable)o;
    }
#endif
    return nil;
}

/// as! Casts nullable object to type T. Asserts if wrong type.
template <class T> PSPDF_ALWAYS_INLINE T *_Nullable as_force(NSObject *_Nullable o) noexcept {
    PSPDFCAssertClassOptional(o, T);
    return PSPDF::as<T> (o);
}

template <class T, class E> PSPDF_ALWAYS_INLINE T *_Nullable as_force_enumerable(id<NSFastEnumeration> _Nullable o) noexcept {
    PSPDFCAssertClassOptional(((NSObject *)o), T);
    PSPDFAssertEnumerable(o, E);
    return PSPDF::as<T> (o);
}

/// Casts object to type T. Asserts if wrong type or nil.
template <class T> PSPDF_ALWAYS_INLINE T *as_force_nn(NSObject *_Nullable o) noexcept {
    PSPDFCAssertClass(o, T);
    return PSPDFNN(PSPDF::as<T> (o));
}
#pragma clang diagnostic pop

/// Returns true if object is of type T. false if object has a different type or is nil.
template <class T> PSPDF_ALWAYS_INLINE bool is(NSObject *_Nullable o) noexcept {
    return [o isKindOfClass:[T class]];
}

PSPDF_ALWAYS_INLINE NSString *to_NSString(const CGRect &rect) { return NSStringFromCGRect(rect); }

PSPDF_ALWAYS_INLINE NSString *to_NSString(const CGPoint &point) { return NSStringFromCGPoint(point); }

PSPDF_ALWAYS_INLINE NSString *_Nullable to_NSString(const std::string &text) { return [[NSString alloc] initWithBytes:text.c_str() length:text.size() encoding:NSUTF8StringEncoding]; }

PSPDF_ALWAYS_INLINE NSString *_Nullable to_NSStringView(const std::string &text) { return [[NSString alloc] initWithBytesNoCopy:const_cast<char *> (text.c_str()) length:text.size() encoding:NSUTF8StringEncoding freeWhenDone:NO]; }

PSPDF_ALWAYS_INLINE NSString *_Nullable to_NSString(const std::shared_ptr<std::string> &text) { return text ? to_NSString(*text) : nil; }

PSPDF_ALWAYS_INLINE NSString *_Nullable to_NSString(const std::optional<std::string> &text) { return text ? to_NSString(*text) : nil; }

PSPDF_ALWAYS_INLINE std::string to_string(NSData *data) {
    auto result = std::string();
    result.resize(data.length);
    [data getBytes:const_cast<char *> (result.c_str()) length:result.size()];
    return result;
}

/// Returns a CGPoint vector from an array of boxed points (NSValue).
inline std::vector<CGPoint> CGPointArrayToVector(NSArray<NSValue *> *_Nullable array) {
    return map(array, [](NSValue *boxedPoint) {
        PSPDFCAssertValue(boxedPoint, CGPoint);
#if TARGET_OS_OSX
        return NSPointToCGPoint(boxedPoint.pointValue);
#else
        return boxedPoint.CGPointValue;
#endif
    });
}

/// Returns a CGFloat array from an array of boxed floats (NSNumber).
inline std::vector<CGFloat> FloatArrayToVector(NSArray<NSNumber *> *_Nullable array) {
    return map(array, [](NSNumber *boxedFloat) { return boxedFloat.pspdf_CGFloatValue; });
}

/// Helper that converts a vector to an array.
/// Modifies the vector (cleans nullptr)
template <typename ContainedType> NSArray<ContainedType> *_Nonnull CreateArrayWithVector(std::vector<ContainedType> &vector) {
    // Ensure we don't have nullptr's in there.
    vector.erase(remove(begin(vector), end(vector), nullptr), end(vector));
    return [[NSArray alloc] initWithObjects:vector.data() count:vector.size()];
}

/// Converts the provided vector into an objective-c array, transforming each value from `ContainedType` to `MappedType` with the provided mapping.
template <typename ContainedType, typename MappedType, typename Allocator>
// Similar case to `PSPDFCompare`:
// ContainedType is not necessarily a pointer type, so specifying nullability would prevent template instantiation for e.g. int
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
NSArray<MappedType> *_Nonnull ArrayWithVector(std::vector<ContainedType, Allocator> const &vector, MappedType _Nullable (^_Nonnull mapping)(ContainedType)) {
#pragma clang diagnostic pop
    auto mapped = PSPDF::map(vector, mapping);
    return CreateArrayWithVector(mapped);
}

/// Convert a list to an array.
template <typename ContainedType> NSArray<ContainedType> *_Nonnull ArrayWithList(std::list<ContainedType> const &list) {
    auto vector = std::vector<ContainedType>{std::begin(list), std::end(list)};
    return CreateArrayWithVector(vector);
}

/// Converts a std::vector of Objective–C objects to an NSArray of the same objects.
// NOTE: this overload is **not** redundant to a default parameter to the 3 parameter version:
// Apparently, clang cannot deduce the types if you try that.😳
template <typename ContainedType, typename Allocator> NSArray<ContainedType> *_Nonnull ArrayWithVector(std::vector<ContainedType, Allocator> const &vector) {
    return PSPDF::ArrayWithVector(vector, ^(ContainedType value) {
        return value;
    });
}

/// Returns an `NSNumber` array from a vector. Type `T` needs to be supported by boxed expressions.
template <typename ContainedType, typename Allocator> NSArray<NSNumber *> *_Nonnull ArrayWithNumberVector(std::vector<ContainedType, Allocator> const &vector) {
    return PSPDF::ArrayWithVector(vector, ^(ContainedType value) {
        return @(value);
    });
}

/// Template specialization for vectors of C strings
template <typename Allocator> NSArray<NSString *> *_Nonnull ArrayWithNumberVector(std::vector<char *, Allocator> const &vector) {
    return PSPDF::ArrayWithVector(vector, ^(NSUInteger value) {
        return @(value);
    });
}

/// Template specialization for vectors of const C strings
template <typename Allocator> NSArray<NSString *> *_Nonnull ArrayWithNumberVector(std::vector<char *const, Allocator> const &vector) {
    return PSPDF::ArrayWithVector(vector, ^(NSUInteger value) {
        return @(value);
    });
}

/// Returns a NSValue array from a vector. Type `T` needs to be supported by `NSValue`.
template <typename ContainedType, typename Allocator> NSArray<NSValue *> *_Nonnull ArrayWithStructVector(std::vector<ContainedType, Allocator> const &vector) {
    return PSPDF::ArrayWithVector(vector, ^(ContainedType value) {
        return @(value);
    });
}

template <typename T> static inline NSSet *SetWithSet(const std::set<T> &set, id (^block)(const T _Nonnull &value)) {
    let result = [NSMutableSet setWithCapacity:set.size()];
    for (const T &value : set) {
        [result addObject:block(value)];
    }
    return [result copy];
}

template <typename T> static inline std::set<T> SetWithElements(id<NSFastEnumeration> array, T _Nonnull (^_Nonnull block)(id _Nonnull value)) {
    std::set<T> result;
    for (id value in array) {
        result.insert(block(value));
    }
    return result;
}

template <typename K, typename V> static inline NSDictionary *DictionaryWithMap(const std::map<K, V> &map, id (^keyBlock)(const K _Nonnull &key), id (^valueBlock)(const V _Nonnull &value)) {
    let result = [NSMutableDictionary dictionaryWithCapacity:map.size()];
    for (let &pair : map) {
        result[keyBlock(pair.first)] = valueBlock(pair.second);
    }
    return [result copy];
}

template <typename K, typename V> static inline std::map<K, V> MapWithDictionary(NSDictionary *dictionary, K _Nonnull (^_Nonnull keyBlock)(id<NSCopying> key), V _Nonnull (^_Nonnull valueBlock)(id value)) {
    __block std::map<K, V> result;
    [dictionary enumerateKeysAndObjectsUsingBlock:^(id<NSCopying> key, id obj, BOOL *_) {
        result[keyBlock(key)] = valueBlock(obj);
    }];

    return result;
}

/// Compares two value types, returns NSComparisonResult.
template <typename T>
// This is a template, and _could_ be instantiated for pointer types, so we’ll get a warning for missing nullability specifiers.
// If, however, we add nullability specifiers, the template can no longer be instantiated for the value types we want to use it…
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
inline NSComparisonResult Compare(const T value1, const T value2) {
#pragma clang diagnostic pop
    if (value1 < value2) {
        return (NSComparisonResult)NSOrderedAscending;
    } else if (value1 > value2) {
        return (NSComparisonResult)NSOrderedDescending;
    } else
        return (NSComparisonResult)NSOrderedSame;
}
}

NS_ASSUME_NONNULL_END
#endif
