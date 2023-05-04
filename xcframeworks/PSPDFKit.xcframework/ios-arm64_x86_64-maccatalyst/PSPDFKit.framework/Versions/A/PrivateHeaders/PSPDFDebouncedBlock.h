//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
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

NS_ASSUME_NONNULL_BEGIN

/// This object debounces a block so that only the last block that was submitted to
/// this object is executed.
///
/// The debounce interval is bound to `dispatch_async` semantics. On a high level view
/// this means that there will be a maximum of one block be executed per run loop cycle;
/// while in detail this might not always be correct, it should be safe to treat it
/// as such for most usecases.
PSPDF_SDK_CLASS_SWIFT(DebouncedBlock)
@interface PSPDFDebouncedBlock : NSObject

/// Initializes the receiver with a queue that scheduled blocks will be called on.
///
/// If passing `nil` for the queue, the main queue will be used.
///
/// @param queue The queue to execute scheduled blocks on.
- (instancetype)initWithQueue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

/// Performs the passed in block asynchronously on the receivers queue if no other
/// block was scheduled on the receiver in the meantime.
///
/// @param block The block to be executed.
- (void)performBlock:(void(^)(void))block;

/// This method executes a previously scheduled perform block synchronously on the
/// queue you are calling it from, blocking until the call finished.
- (void)executePendingBlock;

@end

NS_ASSUME_NONNULL_END
