//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#include <TargetConditionals.h>

// Wraps C function to prevent the C++ compiler to mangle C function names.
// https://stackoverflow.com/questions/1041866/in-c-source-what-is-the-effect-of-extern-c

/// Callable from 3rd party.
#if defined(__cplusplus)
#define PSPDF_EXPORT extern "C" __attribute__((visibility("default")))
#else
#define PSPDF_EXPORT extern __attribute__((visibility("default")))
#endif

#define PSPDF_CLASS_AVAILABLE __attribute__((visibility("default")))
#define PSPDF_ENUM_AVAILABLE
#define PSPDF_PROTOCOL_AVAILABLE

// Direct method and property calls increases performance and reduces binary size.
// https://pspdfkit.com/blog/2020/improving-performance-via-objc-direct/
// https://nshipster.com/direct/
//
// In PSPDFKit, we use PSPDF_OBJC_DIRECT_MEMBERS for *ANY NEW* ObjC classes.
// If the class is used outside of the framework, those methods can not be marked direct.
// Accessing direct selectors only works in the framework the class is compiled in.
// If you need to access a class outside of the framework it is defined, remove the macro.
// (e.g. if you want to access a model object in UI that is compiled in model, remove the direct macro there)
//
// Direct selectors do not work with KVO, KVC or anything dynamic.
// They are more like C calls, however messaging to nil is supported.
//
// Things to look out for: target/action, gesture recognizers, notifications.
// For notifications, consider using block-based variants.
// Selectors that are declared somewhere else do not trigger a warning when made direct
// and result in runtime crashes. For example, didReceiveMemoryWarning,
// since it's declared on UIViewController already.
//
// TODO: There's a future warning in the works about strict direct selector checking
// that might be useful to prevent future errors: -Wstrict-direct-dispatch
// https://reviews.llvm.org/D82611
// Last tested in Xcode 12b6, not yet available.
//
#define PSPDF_OBJC_DIRECT_MEMBERS __attribute__((objc_direct_members))
#define PSPDF_OBJC_DIRECT __attribute__((objc_direct))
#define PSPDF_DIRECT(propertyAttributes, ...) (direct, propertyAttributes, ## __VA_ARGS_)

// Escape hatch for tests that need to go swizzle direct helpers.
// Use only when absolutely necessary - this increases risk of tests missing direct bugs.
// This is required when you want to use methods in tests.
// Especially accessing PDFC* classes will require these.
#define PSPDF_OBJC_DIRECT_MEMBERS_EXCEPT_TESTS PSPDF_OBJC_DIRECT_MEMBERS
#if defined(DISABLE_SOME_OBJC_DIRECT_FOR_TESTS)
#undef PSPDF_OBJC_DIRECT_MEMBERS_EXCEPT_TESTS
#define PSPDF_OBJC_DIRECT_MEMBERS_EXCEPT_TESTS
#endif

// Pure allows compiler optimizations: https://lwn.net/Articles/285332/
#define PSPDF_PURE __attribute__((pure))

// Subclassing control
#define PSPDF_SUBCLASSING_RESTRICTED __attribute__((objc_subclassing_restricted))

// Swift rename shortcuts
#define PSPDF_CLASS_SWIFT(_name)     PSPDF_CLASS_AVAILABLE    NS_SWIFT_NAME(_name)
#define PSPDF_ENUM_SWIFT(_name)      PSPDF_ENUM_AVAILABLE     NS_SWIFT_NAME(_name)
#define PSPDF_PROTOCOL_SWIFT(_name)  PSPDF_PROTOCOL_AVAILABLE NS_SWIFT_NAME(_name)
#define PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(_name) PSPDF_CLASS_SWIFT(_name) PSPDF_SUBCLASSING_RESTRICTED

// Similar to NS_SWIFT_NAME but for declaring getters.
#define PSPDF_SWIFT_NAME(_name) __attribute__((swift_name(_name)))

// A macro that marks a declaration as deprecated in the given PSPDFKit version.
// Using this declaration will always produce a deprecation warning.
#define PSPDF_DEPRECATED(version, msg) \
    __attribute__((deprecated("Deprecated in PSPDFKit " #version " for iOS. " msg)))

// A macro that marks a declaration as soft-deprecated. It means that the
// declaration will be formally deprecated in a future version of PSPDFKit.
// Using this declatation will not produce a deprecation warning but it will
// show up as deprecated in code completion and documentation.
#define PSPDF_TO_BE_DEPRECATED(msg) \
    API_DEPRECATED("Will be deprecated in a future version of PSPDFKit. " msg, ios(1, API_TO_BE_DEPRECATED))

// A macro that marks a declaration as unavailable. Using this declaration will
// always produce a build error.
#define PSPDF_UNAVAILABLE(message) \
    __attribute__((unavailable(message)))

// API Unavailability
// Declares the parameterless `-init` and `+new` as unavailable.
#ifndef PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE
#define PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE PSPDF_UNAVAILABLE("Not the designated initializer")
#endif // PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE

#define PSPDF_EMPTY_INIT_UNAVAILABLE                                \
    - (instancetype)init PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE; \
    + (instancetype)new PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

#define PSPDF_INIT_WITH_CODER_UNAVAILABLE -(nullable instancetype)initWithCoder : (nonnull NSCoder *)aDecoder PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

#define PSPDF_DEFAULT_VIEW_INIT_UNAVAILABLE \
    PSPDF_EMPTY_INIT_UNAVAILABLE            \
    PSPDF_INIT_WITH_CODER_UNAVAILABLE       \
    - (instancetype)initWithFrame : (CGRect)frame PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

#define PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE \
    PSPDF_EMPTY_INIT_UNAVAILABLE                      \
    PSPDF_INIT_WITH_CODER_UNAVAILABLE                 \
    - (instancetype)initWithNibName : (nullable NSString *)nibNameOrNil bundle : (nullable NSBundle *)nibBundleOrNil PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

#define PSPDF_DEFAULT_TABLEVIEWCONTROLLER_INIT_UNAVAILABLE \
    PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE          \
    - (instancetype)initWithStyle : (UITableViewStyle)style PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;
