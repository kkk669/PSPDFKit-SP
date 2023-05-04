//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
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

/// Stores a collection of tasks for later execution.
///
/// All calls are thread safe. Tasks are always executed synchronously in the order they were added on the calling thread.
PSPDF_SUBCLASSING_RESTRICTED
PSPDF_APP_EXPORT @interface PSPDFTaskCollection<BlockType> : NSObject

/// Enqueues a block as task.
///
/// @param block The block to be added to the queue.
- (void)enqueueBlock:(BlockType)block;

/// Runs all enqueued tasks synchronously and removes them.
///
/// @param executorBlock A block that gets passed each enqueued `block` for execution. Used to allow passing of any block argument values to `block`.
- (void)performTasksWithExecutor:(void (^)(BlockType block))executorBlock;

/// Removes all tasks without executing them.
- (void)clear;

/// Returns the number of tasks currently stored.
@property (nonatomic, readonly) NSUInteger count;

@end

NS_ASSUME_NONNULL_END
