//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#pragma once

/// Callable from inside the framework.
#define PSPDF_EXTERN FOUNDATION_EXTERN

// For our PDF Viewer and for Instant we use some symbols that are not public in PSPDFKit.
// We do not use different framework builds for our apps, so these symbols are not hidden, just specially marked.
// This has to be defined before importing `PSPDFAssert.h` because of some header dependencies.
#define PSPDF_APP_EXPORT PSPDF_EXPORT

// Symbols that are used in PSPDFKitUI.framework from PSPDFKit.framework
// also need to be visible (even though these headers are private)
#define PSPDF_SDK_EXPORT PSPDF_EXPORT
#define PSPDF_SDK_VISIBLE __attribute__((visibility("default")))
#define PSPDF_SDK_CLASS_AVAILABLE PSPDF_CLASS_AVAILABLE

// Tests use special flags as well and we're currently lazy and just re-use the app system for it.
#define PSPDF_TEST_EXPORT PSPDF_APP_EXPORT

// Swift rename and visibility shortcuts. Ordered from most restrictive to the least.
// Use the most restrictive version you can for the given API.

/// Private API that is exposed just for tests.
///
/// @warning The macro will be modified during a PSPDFKit release build and made unavailable.
#define PSPDF_TEST_CLASS_SWIFT(_name) PSPDF_CLASS_SWIFT(_name)

/// Private API that is exposed for PSPDFKit apps (PDF Viewer).
///
/// @warning The macro will be modified during a PSPDFKit release build and made unavailable.
#define PSPDF_APP_CLASS_SWIFT(_name)  NS_SWIFT_NAME(_name)

/// The API is exposed to other PSPDFKit frameworks (i.e., PSPDFKit API exposed for PSPDFKitUI).
#define PSPDF_SDK_CLASS_SWIFT(_name)  PSPDF_CLASS_SWIFT(_name)

#define PSPDF_TEST_CLASS_SUBCLASSING_RESTRICTED_SWIFT(_name) PSPDF_SUBCLASSING_RESTRICTED PSPDF_TEST_CLASS_SWIFT(_name)
#define PSPDF_APP_CLASS_SUBCLASSING_RESTRICTED_SWIFT(_name) PSPDF_SUBCLASSING_RESTRICTED PSPDF_APP_CLASS_SWIFT(_name)
#define PSPDF_SDK_CLASS_SUBCLASSING_RESTRICTED_SWIFT(_name) PSPDF_SUBCLASSING_RESTRICTED PSPDF_SDK_CLASS_SWIFT(_name)

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFFastEnumeration.h>
#import <PSPDFKit/PSPDFAssert.h>
#import <PSPDFKit/PSPDFAvailability.h>
#import <PSPDFKit/PSPDFCollectionNullability.h>
#import <PSPDFKit/PSPDFGenerics.h>
#import <PSPDFKit/PSPDFScope.h>
#import <PSPDFKit/PSPDFWarnings.h>
#else
#import "PSPDFEnvironment.h"
#import "PSPDFFastEnumeration.h"
#import "PSPDFAssert.h"
#import "PSPDFAvailability.h"
#import "PSPDFCollectionNullability.h"
#import "PSPDFGenerics.h"
#import "PSPDFScope.h"
#import "PSPDFWarnings.h"
#endif

/// OS X in AppKit mode (not Catalyst)
/// According to the diagram in TargetConditionals.h this would just be same as TARGET_OS_OSX so we can probably clean this up.
#define TARGET_OS_OSX_APPKIT (TARGET_OS_OSX && !TARGET_OS_MACCATALYST)

/// Allow auto-boxing of common structs used in Foundation, CoreGraphics and UIKit.
typedef struct __attribute__((objc_boxable)) _NSRange NSRange;
typedef struct __attribute__((objc_boxable)) CGAffineTransform CGAffineTransform;
typedef struct __attribute__((objc_boxable)) UIEdgeInsets UIEdgeInsets;

// Attribute for Undefined Behavior Analyzer.
// Some form is ok, e.g. unsigned integer overflow is acceptable.
// https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
#define PSPDF_NO_SANITIZE_INTEGER_OVERFLOW __attribute__((no_sanitize("integer")))
#define PSPDF_NO_SANITIZE_NULLABILITY __attribute__((no_sanitize("nullability")))

// TODO: Have not found a way to detect this at compile time yet
// Some tests fail and UBSan is not flexible enough.
// These tests are disabled with this flag.
#define PSPDF_UBSAN_ENABLED 1

// We use this in some places to silence warnings generated when using distcc
#define PSPDF_SILENCE_DEAD_CODE_WARNING(...) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wunreachable-code\"") __VA_ARGS__ _Pragma("clang diagnostic pop")

// We use CLANG_WARN_QUOTED_INCLUDE_IN_FRAMEWORK_HEADER but some files need exceptions.
#define PSPDF_IMPORT_QUOTED_HEADERS_BEGIN _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wquoted-include-in-framework-header\"")
#define PSPDF_IMPORT_QUOTED_HEADERS_END _Pragma("clang diagnostic pop")

// Compiler-checked selectors and performance optimized at runtime.
// Avoid using PROPERTY and prefer PSPDF_KEYPATH or PSPDF_KEYPATH_SELF since they have stricter checks.
// When using distcc this generates a warning about unreachable code, and so we silence it.
#if DEBUG
#define PSPDF_KEYPATH(object, property) PSPDF_SILENCE_DEAD_CODE_WARNING(((void)(NO && ((void)object.property, NO)), @ #property))
#define PROPERTY(property) NSStringFromSelector(@selector(property))
#else
#define PROPERTY(property) @ #property
#define PSPDF_KEYPATH(object, property) @ #property
#endif

#define PSPDF_KEYPATH_SELF(property) PSPDF_KEYPATH(self, property)
// Compiler-checked instance key path with just a class.
#define PSPDF_KEYPATH_CLASS(c, property) PSPDF_KEYPATH(((c *)nil), property)

#if !defined(PSPDF_INLINE)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define PSPDF_INLINE static inline
#elif defined(__cplusplus)
#define PSPDF_INLINE static inline
#elif defined(__GNUC__)
#define PSPDF_INLINE static __inline__
#else
#define PSPDF_INLINE static
#endif
#endif

#define PSPDF_ALWAYS_INLINE inline __attribute__((always_inline))

NS_ASSUME_NONNULL_BEGIN

/// Returns whether both objects are identical or equal via `isEqual:`.
PSPDF_ALWAYS_INLINE BOOL PSPDFEqualObjects(id _Nullable obj1, id _Nullable obj2) {
    return obj1 == obj2 || [obj1 isEqual:obj2];
}

/// Helper to lazily initialize `ivar` with the value returned by `initializerBlock` if ivar is nil.
#define PSPDFInitializeLazy(ivar, initializerBlock) ivar ?: (ivar = initializerBlock())

/// Dynamic cast (either return object of type c or nil)
/// __unsafe_unretained is a pure performance optimization.
#define PSPDFCast(obj, c) ((c * _Nullable) _PSPDFCast(obj, [c class]))
PSPDF_APP_EXPORT id _Nullable _PSPDFCast(__unsafe_unretained id _Nullable obj, __unsafe_unretained Class objClass) NS_SWIFT_UNAVAILABLE("Casting is a Swift language feature");

/// Dynamic asserting cast. Returns an object of class c or asserts if the object has the wrong type.
#define PSPDFForceCast(obj, c) ((c * _Nonnull) _PSPDFForceCast(obj, [c class]))
PSPDF_APP_EXPORT id _Nonnull _PSPDFForceCast(__unsafe_unretained id _Nullable obj, __unsafe_unretained Class objClass) NS_SWIFT_UNAVAILABLE("Casting is a Swift language feature");

/// Dynamic cast to protocol. Returns either the object cast to the protocol type or nil if the object does not conform.
#define PSPDFProtocolCast(obj, p) ((id<p> _Nullable)_PSPDFProtocolCast(obj, @protocol(p)))
PSPDF_APP_EXPORT id _Nullable _PSPDFProtocolCast(__unsafe_unretained id _Nullable object, __unsafe_unretained Protocol *targetProtocol) NS_SWIFT_UNAVAILABLE("Casting is a Swift language feature");

/// Dynamic cast to protocol. Returns either the object cast to the protocol type or asserts if the object has the wrong type.
#define PSPDFForceProtocolCast(obj, p) ((id<p> _Nonnull)_PSPDFForceProtocolCast(obj, @protocol(p)))
PSPDF_APP_EXPORT id _Nonnull _PSPDFForceProtocolCast(__unsafe_unretained id _Nullable object, __unsafe_unretained Protocol *targetProtocol) NS_SWIFT_UNAVAILABLE("Casting is a Swift language feature");

/// Helper for secure decoding with NSCoder. Pass the decoder, the key as a string, and the class to expect.
#define PSPDF_DECODE_S(decoder, key, c) (PSPDFCast([decoder decodeObjectOfClass:c.class forKey:key], c))
/// Helper for secure decoding with NSCoder. Pass the decoder, the property key on self, and the class to expect.
#define PSPDF_DECODE(decoder, key, c) PSPDF_DECODE_S(decoder, PSPDF_KEYPATH_SELF(key), c)

/// Helper for secure decoding file URLs with NSCoder. Pass the decoder and the property key on self. Nil if not a file URL.
#define PSPDF_DECODE_FILE_URL(decoder, key) ^{                                 \
    __auto_type _Null_unspecified anyURL = PSPDF_DECODE(decoder, key, NSURL);  \
    return anyURL.isFileURL ? anyURL : nil;                                    \
}()

/// Encodes a property of self using the property name as the key. Must be used from an instance method.
///
/// @param coder    The NSCoder to encode into.
/// @param property The object property of self to be encoded and also used as the key.
/// @return void
#define PSPDF_ENCODE_OBJECT_PROPERTY(coder, property) ([coder encodeObject:self.property forKey:PSPDF_KEYPATH_SELF(property)])

/// Secure version of memcpy
PSPDF_APP_EXPORT void* _Nonnull  pspdf_memcpy_s(void* destination, size_t destinationSize, const void* source, size_t sourceSize) NS_SWIFT_UNAVAILABLE("Not needed in Swift");

// Similar to defer in Swift
#define pspdf_defer_block_name_with_prefix(prefix, suffix) prefix ## suffix
#define pspdf_defer_block_name(suffix) pspdf_defer_block_name_with_prefix(pspdf_defer_, suffix)
#define pspdf_defer __strong void(^pspdf_defer_block_name(__LINE__))(void) __attribute__((cleanup(pspdf_defer_cleanup_block), unused)) = ^
PSPDF_SDK_EXPORT void pspdf_defer_cleanup_block(__strong void(^_Nonnull* _Nonnull block)(void)) NS_SWIFT_UNAVAILABLE("Use native Swift defer");

NS_ASSUME_NONNULL_END

// micro optimizations
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

// swap helper
#define ps_fswap(a, b) do { let c = (a); (a) = (b); (b) = c; } while (0)

// Swift-like shortcut for auto const
#if defined(__cplusplus)
#define let auto const
#define var auto
#else
#define let const __auto_type
#define var __auto_type
#endif
#define bet bool const

/// Evaluate a condition and proceed if it's true or else return the specified
/// value. Equivalent of Swift's `guard condition else { return return_value }`.
///
/// ```
/// guard_else_return(CGRectIsValid(rect), nil);
/// // The `rect` is valid.
/// ```
///
/// @param condition Condition to evaluate.
/// @param return_value Value to return if `condition` is `false`.
#define guard_else_return(condition, return_value) \
    if (!(condition)) { return (return_value); } \
    do {} while(0)

/// Evaluate a condition and proceed if it's true or else return. Equivalent of
/// Swift's `guard condition else { return }`.
///
/// ```
/// guard_else_return_void(newValue != _oldValue);
/// // The `newValue` is not the same as `oldValue`.
/// ```
///
/// @param condition Condition to evaluate.
#define guard_else_return_void(condition) \
    if (!(condition)) { return; } \
    do {} while(0)

/// Try to unwrap the given nullable value or else return the specified value.
/// Equivalent of Swift's `guard let name = value else { return return_value }`.
///
/// ```
/// guard_nn_else_return(delegate, self.delegate, NO);
/// // `self.delegate` is not nil and is stored in local `delegate` variable.
/// ```
///
/// @param name Name of the local variable that will contain nonnull value.
/// @param value Nullable value to unwrap.
/// @param return_value Value to return in case `value` is nil.
#define guard_nn_else_return(name, value, return_value) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wnullable-to-nonnull-conversion\"") \
    _Pragma("clang diagnostic ignored \"-Wshadow\"") \
    let _Nonnull name = (^{ let _Null_unspecified name = (value); return name; })(); \
    _Pragma("clang diagnostic pop") \
    if (name == nil) { return (return_value); } \
    do {} while(0)

/// Try to unwrap the given nullable value or else return. Equivalent of Swift's
/// `guard let name = value else { return }`.
///
/// ```
/// guard_nn_else_return_void(delegate, self.delegate);
/// // `self.delegate` is not nil and is stored in local `delegate` variable.
/// ```
///
/// @param name Name of the local variable that will contain nonnull value.
/// @param value Nullable value to unwrap.
#define guard_nn_else_return_void(name, value) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wnullable-to-nonnull-conversion\"") \
    _Pragma("clang diagnostic ignored \"-Wshadow\"") \
    let _Nonnull name = (^{ let _Null_unspecified name = (value); return name; })(); \
    _Pragma("clang diagnostic pop") \
    if (name == nil) { return; } \
    do {} while(0)

/// Try to strongify the given weakiefied value or else return the specified value.
/// Equivalent of Swift's `guard let name else { return return_value }`.
///
/// ```
/// weakify(self);
/// strongify_else_return(self, NO);
/// // `self` is strong and not nil at this point.
/// ```
///
/// @param name Name of previously weakified variable.
/// @param return_value Value to return in case `name` is nil.
#define strongify_else_return(name, return_value) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wnullable-to-nonnull-conversion\"") \
    _Pragma("clang diagnostic ignored \"-Wshadow\"") \
    __strong let _Nonnull name = pspdfWeak_##name; \
    _Pragma("clang diagnostic pop") \
    if (name == nil) { return (return_value); } \
    do {} while(0)

/// Try to strongify the given weakiefied value or else return. Equivalent of
/// Swift's `guard let name else { return }`.
///
/// ```
/// weakify(self);
/// strongify_else_return_void(self);
/// // `self` is strong and not nil at this point.
/// ```
///
/// @param name Name of previously weakified variable.
#define strongify_else_return_void(name) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wnullable-to-nonnull-conversion\"") \
    _Pragma("clang diagnostic ignored \"-Wshadow\"") \
    __strong let _Nonnull name = pspdfWeak_##name; \
    _Pragma("clang diagnostic pop") \
    if (name == nil) { return; } \
    do {} while(0)

// Macros for collections. Source: https://gist.github.com/Tricertops/97e6c0dd9cc2c0f2f0e2ca791802eb9c
// Advantages:
//  1. Type of NSArray is inferred, in this case it’s NSArray<NSString *> *
//  2. List of objects is type-checked, so mixing types like NSArray(@42, @"Hi") will report compilation error.
//  3. Ability to allocate any class, not just NSArray. For example NSSet and NSMutableArray.
//  4. Avoids stupid clang bracket matching bug, if you know what I mean.

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvariadic-macros"

#define Array(first, other...) \
( (NSArray<typeof(first)> *) ({ \
typeof(first) _objects[] = {first, other}; \
const NSUInteger _count = sizeof(_objects) / sizeof(id); \
[NSArray arrayWithObjects:_objects count:_count]; \
}))

#define Set(first, other...) \
( (NSSet<typeof(first)> *) ({ \
typeof(first) _objects[] = {first, other}; \
const NSUInteger _count = sizeof(_objects) / sizeof(id); \
[NSSet setWithObjects:_objects count:_count]; \
}))

#define MutableArray(first, other...) \
( (NSMutableArray<typeof(first)> *) ({ \
typeof(first) _objects[] = {first, other}; \
const NSUInteger _count = sizeof(_objects) / sizeof(id); \
[NSMutableArray arrayWithObjects:_objects count:_count]; \
}))

#define MutableSet(first, other...) \
( (NSMutableSet<typeof(first)> *) ({ \
typeof(first) _objects[] = {first, other}; \
const NSUInteger _count = sizeof(_objects) / sizeof(id); \
[NSMutableSet setWithObjects:_objects count:_count]; \
}))

#pragma clang diagnostic pop

// In all of these bitwise macros, the first argument is the variable being set or checked.
// The second argument is often a constant where a single bit is set, such as `NSEnumerationReverse`.

// Modifies `bitField` by setting all bits included in `maskToSet` to true.
#define ENABLE_BITS(bitField, maskToSet) bitField |= (maskToSet)
// Modifies `bitField` by setting all bits included in `maskToClear` to false.
#define CLEAR_BITS(bitField, maskToClear) bitField &= ~(maskToClear)
// Modifies `bitField` by setting all bits included in `maskToSet` to the Boolean value of `newValue`.
#define SET_BITS_TO(bitField, maskToSet, newValue) { if (newValue) { ENABLE_BITS(bitField, maskToSet); } else { CLEAR_BITS(bitField, maskToSet); } }

// True if any of the bits in `maskToCheck` are true in `bitField`. If `maskToCheck` contains a single bit then this is identical to `CHECK_ALL_BITS`.
#define CHECK_ANY_BITS(bitField, maskToCheck) (((bitField) & (maskToCheck)) > 0)
// True if all of the bits in `maskToCheck` are true in `bitField`. If `maskToCheck` contains a single bit then this is identical to `CHECK_ANY_BITS`.
#define CHECK_ALL_BITS(bitField, maskToCheck) (((bitField) & (maskToCheck)) == (maskToCheck))
// True if all of the bits in `maskToCheck` are false in `bitField`.
#define CHECK_BITS_ARE_NOT_SET(bitField, maskToCheck) (((bitField) & (maskToCheck)) == 0)

// Forward properties
#define PSPDFForwardProperty(type, getter, setter, destination) \
- (type)getter {                                                \
    return destination;                                         \
}                                                               \
- (void)setter:(type)newValue {                                 \
    destination = newValue;                                     \
}

// Use this macro to mark abstract methods. If they are not overridden, this will thrown an exception.
#define PSPDFAbstractMethod() [NSException raise:NSInternalInconsistencyException format:@"%@ is an abstract method and must be overridden", NSStringFromSelector(_cmd)]

/// Force cast the given nullable value into a non-nil value or raise an
/// assertion if the value is nil. Equivalent to using `!` in Swift.
#define PSPDFNN(thing) \
    (^{ \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wshadow\"") \
        let _Null_unspecified thang = (thing); \
        NSCAssert(thang != nil, @"'" #thing "' must exist"); \
        _Pragma("clang diagnostic pop") \
        return thang; \
    })()

/// Force cast the given nullable id value into a non-nil id value or raise an
/// assertion if the id value is nil. Equivalent to using `!` in Swift. This
/// is split from from `PSPDFNN` because `__auto_type` doesn't work with id.
#define PSPDFNNID(thing) \
    (^{ \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wshadow\"") \
        id _Nonnull thang = (id _Nonnull)(thing); \
        NSCAssert(thang != nil, @"'" #thing "' must exist"); \
        _Pragma("clang diagnostic pop") \
        return thang; \
    })()

#define PSPDF_NOT_DESIGNATED_INITIALIZER() PSPDF_NOT_DESIGNATED_INITIALIZER_CUSTOM(init)
#define PSPDF_NOT_DESIGNATED_INITIALIZER_WITH_STYLE() PSPDF_NOT_DESIGNATED_INITIALIZER_CUSTOM(initWithStyle : (UITableViewStyle)style)
#define PSPDF_NOT_DESIGNATED_INITIALIZER_WITH_CODER() PSPDF_NOT_DESIGNATED_FAILABLE_INITIALIZER_CUSTOM(initWithCoder : (nonnull NSCoder *)aDecoder)

#define PSPDF_NOT_DESIGNATED_VIEW_INITIALIZERS()  \
    PSPDF_NOT_DESIGNATED_INITIALIZER()            \
    PSPDF_NOT_DESIGNATED_INITIALIZER_WITH_CODER() \
    PSPDF_NOT_DESIGNATED_INITIALIZER_CUSTOM(initWithFrame : (CGRect)frame)

#define PSPDF_NOT_DESIGNATED_VIEWCONTROLLER_INITIALIZERS() \
    PSPDF_NOT_DESIGNATED_INITIALIZER()                     \
    PSPDF_NOT_DESIGNATED_INITIALIZER_WITH_CODER()          \
    PSPDF_NOT_DESIGNATED_INITIALIZER_CUSTOM(initWithNibName : (nullable NSString *)nibNameOrNil bundle : (nullable NSBundle *)nibBundleOrNil)

#define PSPDF_NOT_DESIGNATED_TABLEVIEWCONTROLLER_INITIALIZERS() \
    PSPDF_NOT_DESIGNATED_INITIALIZER()                          \
    PSPDF_NOT_DESIGNATED_INITIALIZER_WITH_CODER()               \
    PSPDF_NOT_DESIGNATED_INITIALIZER_WITH_STYLE()               \
    PSPDF_NOT_DESIGNATED_INITIALIZER_CUSTOM(initWithNibName : (nullable NSString *)nibNameOrNil bundle : (nullable NSBundle *)nibBundleOrNil)

#define PSPDF_NOT_DESIGNATED_INITIALIZER_CUSTOM(initName)                                                                                           PSPDF_DEPRECATED_IMPLEMENTATIONS_BEGIN \
    _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wobjc-designated-initializers\"") - (instancetype)initName {              \
        do {                                                                                                                                        \
            NSAssert2(NO, @"%@ is not the designated initializer for instances of %@.", NSStringFromSelector(_cmd), NSStringFromClass(self.class)); \
            return nil;                                                                                                                             \
        } while (0);                                                                                                                                \
    }                                                                                                                                               PSPDF_DEPRECATED_IMPLEMENTATIONS_END \
    _Pragma("clang diagnostic pop")

#define PSPDF_NOT_DESIGNATED_FAILABLE_INITIALIZER_CUSTOM(initName)                                                                                           PSPDF_DEPRECATED_IMPLEMENTATIONS_BEGIN \
    _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wobjc-designated-initializers\"") - (nullable instancetype)initName {              \
        do {                                                                                                                                        \
            NSAssert2(NO, @"%@ is not the designated initializer for instances of %@.", NSStringFromSelector(_cmd), NSStringFromClass(self.class)); \
            return nil;                                                                                                                             \
        } while (0);                                                                                                                                \
    }                                                                                                                                               PSPDF_DEPRECATED_IMPLEMENTATIONS_END \
    _Pragma("clang diagnostic pop")

// Final class declaration.
#ifndef PSPDF_FINAL_CLASS_INITIALIZE_IMP
#define PSPDF_FINAL_CLASS_INITIALIZE_IMP(__finalClass)                                                                                                                      \
    do {                                                                                                                                                                    \
        if (![NSStringFromClass(self) hasPrefix:@"NSKVONotifying"] && self != (__finalClass)) {                                                                             \
            NSString *reason = [NSString stringWithFormat:@"%@ is a final class and cannot be subclassed. %@", NSStringFromClass((__finalClass)), NSStringFromClass(self)]; \
            @throw [NSException exceptionWithName:@"PSPDFFinalClassViolationException" reason:reason userInfo:nil];                                                         \
        }                                                                                                                                                                   \
    } while (0)
#endif // PSPDF_FINAL_CLASS_INITIALIZE_IMP

#ifndef PSPDF_FINAL_CLASS
#define PSPDF_FINAL_CLASS(__finalClass)                   \
    +(void)initialize {                                   \
        PSPDF_FINAL_CLASS_INITIALIZE_IMP((__finalClass)); \
    }
#endif // PSPDF_FINAL_CLASS

// Use for methods that come from base classes but cannot be called in a subclass.
#ifndef PSPDF_UNSUPPORTED_CALL_USE_INSTEAD
#define PSPDF_UNSUPPORTED_CALL_USE_INSTEAD(sel) \
    let reason = [NSString stringWithFormat:@"Calling %s is not supported. Use -[%@ %@] instead.", __PRETTY_FUNCTION__, NSStringFromClass(self.class), NSStringFromSelector(@selector(sel))]; \
    @throw [NSException exceptionWithName:NSInvalidArgumentException reason:reason userInfo:nil];
#endif // PSPDF_UNSUPPORTED_CALL_USE_INSTEAD

// Benchmark
#define PSPDFBenchStartTimer() CFAbsoluteTime _pspdf_benchtime_a = CFAbsoluteTimeGetCurrent();
#define PSPDFBenchEndTimer(x)                                       \
    CFAbsoluteTime _pspdf_benchtime_b = CFAbsoluteTimeGetCurrent(); \
    NSLog(@"benchmark %@: %2.5 seconds", x, _pspdf_benchtime_b - _pspdf_benchtime_a);

#define PSPDF_EMPTY_CLASS(className, parentClassName) \
@interface className : parentClassName @end @implementation className @end

// Ensure CI macro is always defined
#ifndef CI
#define CI 0
#endif

#ifndef TESTING
#define TESTING 0
#endif
