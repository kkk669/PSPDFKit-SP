//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

// TODO: We don't really know why this warning is triggered on some (CI) machines.
// PS: I also got this when using a newer Clang Toolchain; might be that we use a different Clang here?
// "non-portable path to file '<Dispatch/queue.h>'; specified path differs in case from file name on disk"
// This doesn't appear to be the case. The "dispatch" is lowercase, even on the affected machines.
// For the time being, we're disabling the warning here to prevent builds from failing due to -Werror.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnonportable-system-include-path"
#import <dispatch/queue.h>
#pragma clang diagnostic pop

NS_ASSUME_NONNULL_BEGIN

/// Calls out from an operation as long as the operation has not been cancelled.
PSPDF_APP_EXPORT void pspdf_dispatch_main_async_from_operation(dispatch_block_t block, NSOperation *operation);

/// Helper to create dispatch queues with a default name.
#define pspdf_dispatch_queue_create(name, type) dispatch_queue_create([NSString stringWithFormat:@PSPDF_URL_PREFIX ".%@", name].UTF8String, type)

#define pspdf_dispatch_queue_create_plain(type) pspdf_dispatch_queue_create(NSStringFromClass(self.class), type)

/// Execute a block that could release our object. Protects against [NSObject cancelPreviousPerformRequestsWithTarget:] woes which does a release instead of an autorelease.
PSPDF_SDK_EXPORT void pspdf_retainAndPerformBlock(id self, NS_NOESCAPE dispatch_block_t block);

/// Time tracking. Returns time in nanoseconds. Use result/1E9 to print seconds.
PSPDF_EXTERN uint64_t pspdf_performAndTrackTime(NS_NOESCAPE dispatch_block_t block, BOOL trackTime);

/// Helper to convert target/action pattern into a dispatchable block.
///
/// `target` will be tracked weakly.
/// `sender` is optional, only used if action accepts an argument.
/// If `target` is not nil, `action` is required.
PSPDF_SDK_EXPORT void (^pspdf_targetActionBlock(id _Nullable target, SEL action))(_Nullable id);

/// Performs `block` immediately and ignores subsequent calls during the same runloop.
#define pspdf_ensureCalledOnlyOncePerRunloop(block)                     \
    do {                                                                \
        static const char *__onceKey = "once";                          \
        _pspdf_ensureCalledOnlyOncePerRunloop(self, &__onceKey, block); \
    } while (0)
PSPDF_TEST_EXPORT void _pspdf_ensureCalledOnlyOncePerRunloop(id self, const void *key, NS_NOESCAPE dispatch_block_t block);

typedef BOOL (^PSPDFTestCondition)(void);

/// Test Helper for conditional waiting.
///
/// Not a fan of having this in the main SDK, but `cancelThreadOperationsAndWait` needs it and code duplication is bad.
PSPDF_TEST_EXPORT BOOL PSPDFWaitForConditionWithTimeout(NSTimeInterval timeout, PSPDFTestCondition condition) NS_SWIFT_NAME(WaitForConditionWithTimeout(_:condition:));

NS_ASSUME_NONNULL_END
