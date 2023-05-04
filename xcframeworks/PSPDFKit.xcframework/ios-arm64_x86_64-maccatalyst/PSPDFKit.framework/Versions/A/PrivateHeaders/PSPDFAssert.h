//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFRuntime.h>
#import <PSPDFKit/PSPDFMacros.h>
#else
#import "PSPDFRuntime.h"
#import "PSPDFMacros.h"
#endif
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(NS_BLOCK_ASSERTIONS)
#define PSPDF_ASSERT_USE_ONLY __unused
#else
#define PSPDF_ASSERT_USE_ONLY
#endif

#if !defined(NS_BLOCK_ASSERTIONS)

// Copy of standard NSAssert/NSCAssert but using __FILE_NAME__ for shorter binary size
#undef NSAssert
#define NSAssert(condition, desc, ...)    \
    do {                \
    __PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    if (__builtin_expect(!(condition), 0)) {        \
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE_NAME__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
        [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd \
        object:self file:__assert_file__ \
            lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
    }                \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)

#undef NSCAssert
#define NSCAssert(condition, desc, ...) \
    do {                \
    __PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    if (__builtin_expect(!(condition), 0)) {        \
            NSString *__assert_fn__ = [NSString stringWithUTF8String:__PRETTY_FUNCTION__]; \
            __assert_fn__ = __assert_fn__ ? __assert_fn__ : @"<Unknown Function>"; \
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE_NAME__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
        [[NSAssertionHandler currentHandler] handleFailureInFunction:__assert_fn__ \
        file:__assert_file__ \
            lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
    }                \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)

#endif

#define PSPDFAssert(condition, description, ...) NSAssert(condition, description, ##__VA_ARGS__)
#define PSPDFCAssert(condition, description, ...) NSCAssert(condition, description, ##__VA_ARGS__)

#define PSPDFConditionalAssert(shouldTestCondition, condition, description, ...) PSPDFAssert((!(shouldTestCondition) || (condition)), nil, (description), ##__VA_ARGS__)
#define PSPDFCConditionalAssert(shouldTestCondition, condition, description, ...) PSPDFCAssert((!(shouldTestCondition) || (condition)), nil, (description), ##__VA_ARGS__)

#define PSPDFAssertNil(condition, description, ...) PSPDFAssert(!(condition), (description), ##__VA_ARGS__)
#define PSPDFCAssertNil(condition, description, ...) PSPDFCAssert(!(condition), (description), ##__VA_ARGS__)

#define PSPDFAssertNotNil(condition, description, ...) PSPDFAssert((condition), (description), ##__VA_ARGS__)
#define PSPDFCAssertNotNil(condition, description, ...) PSPDFCAssert((condition), (description), ##__VA_ARGS__)

#define PSPDFAssertTrue(condition) PSPDFAssert((condition), @"Condition %s is expected to be true", #condition)
#define PSPDFCAssertTrue(condition) PSPDFCAssert((condition), @"Condition %s is expected to be true", #condition)

#define PSPDFAssertFalse(condition) PSPDFAssert(!(condition), @"Condition %s is expected to be false", #condition)
#define PSPDFCAssertFalse(condition) PSPDFCAssert(!(condition), @"Condition %s is expected to be false", #condition)

#define PSPDFAssertEqual(_a, _b) PSPDFAssert(((_a) == (_b)), nil, nil) 
#define PSPDFCAssertEqual(_a, _b) PSPDFCAssert(((_a) == (_b)), nil, nil)

#define PSPDFAssertMainThread() PSPDFAssert(PSPDFIsMainThread(), @"This method must be called on the main thread.")
#define PSPDFCAssertMainThread() PSPDFCAssert(PSPDFIsMainThread(), @"This method must be called on the main thread.")

#define PSPDFFailAssert(description, ...) PSPDFAssert(NO, description, ##__VA_ARGS__)
#define PSPDFCFailAssert(description, ...) PSPDFCAssert(NO, description, ##__VA_ARGS__)

/// In case a resumable assert is thrown, a notification is emitted. DEBUG only.
PSPDF_EXPORT NSNotificationName const PSPDFAssertionNotification;

/// The key in the `PSPDFAssertionNotification.userInfo` for the assertion message.
PSPDF_EXPORT NSString* const PSPDFAssertionMessageUserInfoKey;

/// The key in the `PSPDFAssertionNotification.userInfo` for the assertion backtrace as `NSArray<NSString *>`
PSPDF_EXPORT NSString* const PSPDFAssertionBacktraceUserInfoKey;

/// Checks the enumerable if all objects are of type `allowedClass`.
///
/// @note This is a NOP if NS_BLOCK_ASSERTIONS is defined.
PSPDF_APP_EXPORT void PSPDFCheckAllowedClassThrows(id<NSFastEnumeration> _Nullable enumerable, Class allowedClass);

/// Checks the enumerable if all objects are one of the allowedClasses.
///
/// @note This is a NOP if NS_BLOCK_ASSERTIONS is defined.
PSPDF_APP_EXPORT void PSPDFCheckAllowedClassesThrows(id<NSFastEnumeration> _Nullable enumerable, id<NSFastEnumeration> allowedClasses);

/// Checks the enumerable if all objects confirm to `allowedProtocol`.
///
/// @note This is a NOP if NS_BLOCK_ASSERTIONS is defined.
PSPDF_APP_EXPORT void PSPDFCheckProtocolThrows(id<NSFastEnumeration> _Nullable enumerable, Protocol *allowedProtocol);

/// Works on anything that conforms to NSEnumeration/NSFastEnumeration.
/// Calling class on a class object will return the same.
#define PSPDFAssertEnumerable(enumerable, allowedClass) PSPDFCheckAllowedClassThrows((enumerable), [allowedClass self])

#define PSPDFAssertEnumerableProtocol(enumerable, allowedProtocol) PSPDFCheckProtocolThrows((enumerable), @protocol(allowedProtocol))

#define PSPDFAssertNotEmpty(enumerable)                                                                             \
    do {                                                                                                            \
        NSAssert(enumerable.count > 0, @"Object not satisfying: '%@' must contain at least one item.", enumerable); \
    } while (0)

#define PSPDFAssertClass(object, allowedClass)                                                                                                                                                  \
    do {                                                                                                                                                                                        \
        NSAssert(object_isClass([allowedClass self]), @"Trying to assert a class but parameter is an instance");                                                                                \
        NSAssert([object isKindOfClass:[allowedClass self]], @"Object type not satisfying: '%@' must be of type '%s' but is '%@'.", object, #allowedClass, PSPDFClassStringFromObject(object)); \
    } while (0)

/// Returns the class name from an object.
///
/// Basically: object ? NSStringFromClass((Class)[object class]) : @"(null)")
PSPDF_APP_EXPORT NSString *PSPDFClassStringFromObject(_Nullable id object);

/// Checks if `obj` is one of the allowed classes in `allowedClasses`.
PSPDF_APP_EXPORT void PSPDFAssertClasses(id obj, id<NSFastEnumeration> allowedClasses);

#define PSPDFAssertClassOptional(object, allowedClass)                                                                                                                                                                                           \
    do {                                                                                                                                                                                                                                         \
        NSAssert(object_isClass([allowedClass self]), @"Trying to assert a class but parameter is an instance");                                                                                                                                 \
        NSAssert(object == nil || [object isKindOfClass:[allowedClass self]], @"Object type not satisfying: '%@' must be of type '%@' or nil but is '%@'.", object, NSStringFromClass([allowedClass self]), PSPDFClassStringFromObject(object)); \
    } while (0)

#define PSPDFAssertProtocol(object, allowedProtocol)                                                                                                                     \
    do {                                                                                                                                                                 \
        NSAssert([(id)(object) conformsToProtocol:@protocol(allowedProtocol)], @"Object not satisfying: '%@' must conform to protocol '%s'.", object, #allowedProtocol); \
    } while (0)

#define PSPDFAssertSubclassOfClass(aClass, superClasName)                                                                                                                                   \
    do {                                                                                                                                                                                    \
        NSAssert([(Class)(aClass) isSubclassOfClass:[superClasName class]], @"Class not satisfying: '%@' must be a subclass of '%s'.", NSStringFromClass((Class)(aClass)), #superClasName); \
    } while (0)

/// Asserts that all of the passed in features are enabled.
#define PSPDFAssertFeatureEnabled(feature)                                                                                                                           \
    do {                                                                                                                                                             \
        NSAssert(PSPDFIsFeatureEnabled(feature, NO), @"Your license does not include %@.", PSPDFFeatureMaskToString(feature)); \
    } while (0)

/// Asserts that at least one of the passed in features are enabled.
#define PSPDFAssertAnyFeatureEnabled(feature)                                                                                                                           \
    do {                                                                                                                                                             \
        NSAssert(PSPDFIsAnyFeatureEnabled(feature, NO), @"Your license does not include %@.", PSPDFFeatureMaskToString(feature)); \
    } while (0)

#define PSPDFCAssertProtocol(object, allowedProtocol)                                                                                                                     \
    do {                                                                                                                                                                  \
        NSCAssert([(id)(object) conformsToProtocol:@protocol(allowedProtocol)], @"Object not satisfying: '%@' must conform to protocol '%s'.", object, #allowedProtocol); \
    } while (0)

#define PSPDFAssertProtocolOptional(object, allowedProtocol)                                                                                                                                    \
    do {                                                                                                                                                                                        \
        NSAssert(!(object) || [(id)(object) conformsToProtocol:@protocol(allowedProtocol)], @"Object not satisfying: '%@' must conform to protocol '%s' or be nil.", object, #allowedProtocol); \
    } while (0)

#define PSPDFCAssertNotEmpty(enumerable)                                                                             \
    do {                                                                                                             \
        NSCAssert(enumerable.count > 0, @"Object not satisfying: '%@' must contain at least one item.", enumerable); \
    } while (0)

#define PSPDFCAssertClass(object, allowedClass)                                                                                                                                                                           \
    do {                                                                                                                                                                                                                  \
        NSCAssert(object_isClass([allowedClass self]), @"Trying to assert a class but parameter is an instance");                                                                                                          \
        NSCAssert([object isKindOfClass:[allowedClass self]], @"Object type not satisfying: '%@' must be of type '%@' but is '%@'.", object, NSStringFromClass([allowedClass self]), PSPDFClassStringFromObject(object)); \
    } while (0)

#define PSPDFCAssertClassOptional(object, allowedClass)                                                                                                                                                                                     \
    do {                                                                                                                                                                                                                                    \
        NSCAssert(object_isClass([allowedClass self]), @"Trying to assert a class but parameter is an instance");                                                                                                                            \
        NSCAssert(!object || [object isKindOfClass:[allowedClass self]], @"Object type not satisfying: '%@' must be of type '%@' or nil but is '%@'.", object, NSStringFromClass([allowedClass self]), PSPDFClassStringFromObject(object)); \
    } while (0)

#define PSPDFCAssertSubclassOfClass(aClass, superClasName)                                                                                                                                   \
    do {                                                                                                                                                                                     \
        NSCAssert([(Class)(aClass) isSubclassOfClass:[superClasName class]], @"Class not satisfying: '%@' must be a subclass of '%s'.", NSStringFromClass((Class)(aClass)), #superClasName); \
    } while (0)

#define PSPDFCAssertFeatureEnabled(feature)                                                                                                                           \
    do {                                                                                                                                                              \
        NSCAssert(PSPDFIsFeatureEnabled(feature, NO), @"Your license does not include %@.", PSPDFFeatureMaskToString(feature)); \
    } while (0)

/// Common types
#define PSPDFAssertString(object) PSPDFAssertClass(object, NSString)
#define PSPDFAssertStringOptional(object) PSPDFAssertClassOptional(object, NSString)
/// Checks the object is a URL and is a file URL. If you need to allow non-file URLs, use PSPDFAssertClass.
#define PSPDFAssertFileURL(object)                                                                      \
    do {                                                                                                \
        PSPDFAssertClass(object, NSURL);                                                                \
        PSPDFAssert(object.isFileURL, @"%@ is not a file URL. Remote URLs are not supported.", object); \
    } while (0)

#define PSPDFAssertData(object) PSPDFAssertClass(object, NSData)
#define PSPDFAssertDictionary(object) PSPDFAssertClass(object, NSDictionary)

#define PSPDFCAssertString(object) PSPDFCAssertClass(object, NSString)
#define PSPDFCAssertStringOptional(object) PSPDFCAssertClassOptional(object, NSString)
#define PSPDFCAssertURL(object) PSPDFCAssertClass(object, NSURL)
#define PSPDFCAssertData(object) PSPDFCAssertClass(object, NSData)

#define PSPDFAssertValue(object, allowedType) \
do {                                                                                                                                                                                                                      \
NSAssert([object isKindOfClass:NSValue.class] && strcmp(((NSValue *)object).objCType, @encode(allowedType)) == 0, @"NSValue type not satisfying: '%@' must be a value and contain '%s' but is '%s'.", object, #allowedType, [object isKindOfClass:NSValue.class] ? ((NSValue *)object).objCType : ""); \
} while (0)

#define PSPDFCAssertValue(object, allowedType) \
do {                                                                                                                                                                                                                      \
NSCAssert([object isKindOfClass:NSValue.class] && strcmp(((NSValue *)object).objCType, @encode(allowedType)) == 0, @"NSValue type not satisfying: '%@' must be a value and contain '%s' but is '%s'.", object, #allowedType, [object isKindOfClass:NSValue.class] ? ((NSValue *)object).objCType : ""); \
} while (0)

#define PSPDFAssertValueOptional(object, allowedType) \
do {                                                                                                                                                                                                                      \
NSAssert(!object || ([object isKindOfClass:NSValue.class] && strcmp(((NSValue *)object).objCType, @encode(allowedType)) == 0), @"NSValue type not satisfying: '%@' must be nil or a value and contain '%s' but is '%s'.", object, #allowedType, [object isKindOfClass:NSValue.class] ? ((NSValue *)object).objCType : ""); \
} while (0)

#define PSPDFCAssertBlock(object)                                                                                                                            \
    do {                                                                                                                                                     \
        NSCAssert(PSPDFIsBlock(object), @"Object type not satisfying: '%@' must be a block but is '%@'.", object, NSStringFromClass((Class)[object class])); \
    } while (0)

#define PSPDFCAssertBlockOptional(object)                                                                                                                                        \
    do {                                                                                                                                                                         \
        NSCAssert(!object || PSPDFIsBlock(object), @"Object type not satisfying: '%@' must be a nil or a block but is '%@'.", object, NSStringFromClass((Class)[object class])); \
    } while (0)

#define PSPDFAssertBlock(object)                                                                                                                            \
    do {                                                                                                                                                    \
        NSAssert(PSPDFIsBlock(object), @"Object type not satisfying: '%@' must be a block but is '%@'.", object, NSStringFromClass((Class)[object class])); \
    } while (0)

#define PSPDFAssertBlockOptional(object)                                                                                                                                        \
    do {                                                                                                                                                                        \
        NSAssert(!object || PSPDFIsBlock(object), @"Object type not satisfying: '%@' must be a nil or a block but is '%@'.", object, NSStringFromClass((Class)[object class])); \
    } while (0)

PSPDF_APP_EXPORT NSString *const PSPDFAssertCalledOnceException;
#define PSPDFAssertCalledOnce(...) ({                                                                                                           \
    if (objc_getAssociatedObject(self, _cmd)) {                                                                                                 \
        @throw [NSException exceptionWithName:PSPDFAssertCalledOnceException reason:[NSString stringWithFormat:@"" __VA_ARGS__] userInfo:nil];  \
    } else {                                                                                                                                    \
        objc_setAssociatedObject(self, _cmd, @YES, OBJC_ASSOCIATION_RETAIN_NONATOMIC);                                                          \
    }                                                                                                                                           \
})

/// Use this to assert if code is executed on a given queue. To use this, do the following:
/// - Define a tag in the appropriate scope, like so: `static char PSPDFSomeQueue;`. This will usually
/// go at the top of your .m file.
/// - Tag the queue with `PSPDFAssertQueueSetup(someQueue, PSPDFSomeQueue);` where PSPDFSomeQueue is
/// the tag that you defined in step 1.
/// - Assert that code runs on the expected queue with PSPDFAssertQueue(PSPDFSomeQueue);`.
#define PSPDFAssertQueue(identifier) NSAssert(dispatch_get_specific(&identifier), @"Queue must match identifier")
#define PSPDFAssertQueueSetup(queue, identifier) dispatch_queue_set_specific(queue, &identifier, &identifier, NULL)

/// Prints a log warning if the controller is not used inside a navigation bar, as functionality won't work.
#define PSPDFWarnIfNotInsideNavigationController() \
do { if (!self.navigationController) { \
    PSPDFLogWarningOnce(@"%@ is intended to be used inside an UINavigationController. Functionality will be limited if presented without. This warning will only be logged once.", self); \
}} while (0)

/// Checks if a method has been overridden.
///
/// This method checks if any class in a given subclass hierarchy overrides a given
/// selector.
///
/// @param theClass The class that implements the selector.
/// @param subclass The class you want to know from if it or any superclass in between
/// it and `theClass` implements this method.
/// @param selector The selector to check for.
/// @return `true` if `subclass` or any class from the hierarchy before reaching `theClass`
/// implements `selector`, `false` otherwise.
PSPDF_APP_EXPORT BOOL PSPDFSubclassOverridesSelector(Class theClass, Class subclass, SEL selector);

/// Checks if `block` is a block (`NSBlock`)
PSPDF_APP_EXPORT BOOL PSPDFIsBlock(id _Nullable block);

#if !defined(NS_BLOCK_ASSERTIONS)

/// Checks if `selector` on `theClass` has been overridden in the app.
/// Only works for classes that are implemented in system frameworks  (UIKit, Foundation...)
/// Returns the category name, if found, otherwise nil.
PSPDF_APP_EXPORT BOOL PSPDFSystemFunctionOverriddenInCategory(Class theClass, SEL selector, NSString *__autoreleasing _Nullable *_Nullable categoryName);

/// Checks if a method has been overridden. Runtime equivalent for @final.
#define PSPDFAssertOnSubclassOverridesSelector(theClass, selector) \
    ({ NSAssert(!PSPDFSubclassOverridesSelector(theClass, self, selector), @"Subclass %@ must not override %@ method. See https://pspdfkit.com/guides/ios/getting-started/overriding-classes/ for details.", NSStringFromClass(self), NSStringFromSelector(selector)); })

#define PSPDFAssertOnSubclassOverridesSelectors(theClass, selectors)    \
    ({                                                                  \
        for (const SEL selector : selectors) {                          \
            PSPDFAssertOnSubclassOverridesSelector(theClass, selector); \
        }                                                               \
    })

#endif // !defined(NS_BLOCK_ASSERTIONS)

NS_ASSUME_NONNULL_END
