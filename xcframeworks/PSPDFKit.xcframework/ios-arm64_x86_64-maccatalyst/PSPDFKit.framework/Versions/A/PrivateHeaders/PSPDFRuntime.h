//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFMacros+Private.h>
#else
#import "PSPDFMacros+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

// Obfuscate method calls.
// Macros globally rename these helpers so they are harder to find.
#define pspdf_swizzleSelectorWithBlock pspdf_applyWithBlock
#define pspdf_swizzleSelectorOnce pspdf_applyWithBlockOnce
#define PSPDFXORString PSPDFGeneratePath2
#define PSPDFSelectorFromString PSPDFPathSelectorHelper

// We use the runtime directly so calls are harder to find.
#define PSPDFClassObfuscate(...) objc_lookUpClass((const char *)[NSString stringWithFormat:__VA_ARGS__].UTF8String)
#define PSPDFSELObfuscate(...) PSPDFSelectorFromString([NSString stringWithFormat:__VA_ARGS__])
#define PSPDFSELFromObfuscatedCString(cString, key) PSPDFSelectorFromString(PSPDFXORString(cString, key))

/// Returns the setter for a getter selector. (currently unused)
PSPDF_EXTERN SEL PSPDFSetterForGetter(SEL origSEL);

/**
 Swizzles selector with new IMP based on a block, returning current implementation.

 In most cases, you want to capture the current IMP and call it as part of the new implementation.
 If the IMP isn't captured, it'll be lost later on.

 Example use:

     pspdf_swizzleSelectorOnce(controller.class, @selector(topLayoutGuide), ^{
        __block IMP originalTopLayoutGuideIMP = pspdf_swizzleSelectorWithBlock(controller.class, @selector(topLayoutGuide), ^(UIViewController *_self) {
            if (PSPDFControllerIsInSimplePageViewController(_self)) {
                return _self.parentViewController.topLayoutGuide;
            } else {
                return ((id<UILayoutSupport> (*)(id, SEL))originalTopLayoutGuideIMP)(_self, @selector(topLayoutGuide));
            }
        });
    });
 */
PSPDF_TEST_EXPORT _Nullable IMP pspdf_swizzleSelectorWithBlock(Class clazz, SEL selector, id newImplementationBlock) NS_SWIFT_NAME(swizzle(clazz:selector:block:));

/// Use this method to ensure that any swizzling you perform is executed only once.
/// Swizzling using pspdf_swizzleSelectorWithBlock replaces the IMP, but doesn't touch the method signature.
/// An associated value is set with the selector as key to indicate that the IMP was successfully modified.
///
/// This function ensures that `block` is called only once for a given `Class` and `SEL` pair, thread-safe.
PSPDF_SDK_EXPORT bool pspdf_swizzleSelectorOnce(Class clazz, SEL selector, NS_NOESCAPE dispatch_block_t block) NS_SWIFT_NAME(swizzleOnce(clazz:selector:block:));

/// Checks if we're on the main thread or on the main queue.
/// This doesn't necessarily have to be the same. GCD, as an optimization, sometimes runs things on the current thread.
/// See https://gist.github.com/jspahrsummers/af6ddfbabf3894bde981 for details.
PSPDF_APP_EXPORT BOOL PSPDFIsMainThread(void);

/// XORs a C string with key to generate a useful string.
/// Used to hide strings and dynamically de-obfuscate them at runtime.
///
/// Generate ctring via po [NSString printHex:@"_parentScrollView" WithKey:@"ViewHierarchy"]
///
/// Defined in PSPDFStringObfuscation.m
PSPDF_SDK_EXPORT NSString *PSPDFXORString(const unsigned char *cstring, NSString *key);

/// Similar to NSSelectorFromString, just obfuscated so it's harder to decompile.
PSPDF_EXPORT __attribute__((always_inline)) SEL _Nonnull PSPDFSelectorFromString(NSString *string);

/// HACK for Catalyst specific UI when using Optimized For Mac.
PSPDF_SDK_EXPORT BOOL PSPDFAllowUnsupportedMacIdiom(Class klass);

NS_ASSUME_NONNULL_END
