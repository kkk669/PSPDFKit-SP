//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
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

// TODO: We don't really know why this warning is triggered on some (CI) machines.
// "non-portable path to file '<Dispatch/queue.h>'; specified path differs in case from file name on disk"
// This doesn't appear to be the case. The "dispatch" is lowercase, even on the affected machines.
// For the time being, we're disabling the warning here to prevent builds from failing due to -Werror.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnonportable-system-include-path"
#import <dispatch/queue.h>
#pragma clang diagnostic pop

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFConcurrentQueue;

/**
 Wraps the GCD dispatch_queue_t object in a modern wrapper.

 Example usage:
 ```
   [PSPDFDispatchQueue.mainQueueQueue async:^{}];
   let queue = [PSPDFDispatchQueue.utilityQueue namedQueue:@"search.cache-outline"];
   [queue conditional:slowOperation, async^{}];
   [queue syncIfNotOnQueue:^{}];
 ```

 In debug mode, you can use [PSPDFDispatchQueue _listAllQueues] to see all queues and parents.

 @note Do not create instances of this class yourself. Instead use `-namedQueue:` and `-namedConcurrentQueue:` to get
 appropriately configured queues with proper parent queue or QOS settings. You're encouraged to create many queues - they
 are generally cheap to create and maintain. In contrast from the global queues that are accessible through the class
 properties and `+queueFromQOSClass:`, named custom queues are not cached in any way, and subsequent calls to `-namedQueue:`
 and `-namedConcurrentQueue:` passing the same name will yield different objects. It is the caller’s responsibility to store
 custom queues as needed.

 @note: This is a helper class designed for Objective-C. Shouldn't be necessary in Swift.
 */
PSPDF_SDK_CLASS_AVAILABLE
@interface PSPDFDispatchQueue : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Explicit cast to dispatch queue object. Use this to interact with C dispatch API.
@property (nonatomic, readonly) dispatch_queue_t queue;

/// Tracks parent/child queue relationship.
/// Is automatically set when the dispatch queue is created.
@property (nonatomic, readonly, nullable) PSPDFDispatchQueue *parentQueue;

/// Checks if we're on the current queue.
///
/// @note Use with caution! This doesn't work if queues are chained.
@property (nonatomic, readonly) BOOL isCurrentQueue;

/// Call a block sync. @see dispatch_sync.
- (void)sync:(NS_NOESCAPE dispatch_block_t)block;

/// Call a block sync. @see dispatch_async.
- (void)async:(dispatch_block_t)block;

/// Call a block after certain time. @see dispatch_after.
- (void)after:(NSTimeInterval)when block:(dispatch_block_t)block;

// MARK: Conditional Enqueueing

/// Call a block sync if condition is true, else calls the block directly.
- (void)conditional:(BOOL)asyncCondition sync:(NS_NOESCAPE dispatch_block_t)block;

/// Call a block async if condition is true, else calls the block directly.
- (void)conditional:(BOOL)asyncCondition async:(dispatch_block_t)block;

/// Run code async if we're not already on that queue.
///
/// @warning Usually only useful for main thread checks!
- (void)asyncIfNotOnQueue:(dispatch_block_t)block;

/// Run code sync if we're not already on that queue.
///
/// @warning Usually only useful for main thread checks!
- (void)syncIfNotOnQueue:(NS_NOESCAPE dispatch_block_t)block;

// MARK: Naming Queues

/// Returns name of the queue.
@property (nonatomic, readonly) NSString *name;

/// Returns a named serial queue subclass.
- (PSPDFDispatchQueue *)namedQueue:(NSString *)name;

// MARK: Global Queue Accessors

/// Returns the main queue.
@property (nonatomic, class, readonly) PSPDFDispatchQueue *mainQueue;

/// Returns the wrapped global queue `QOS_CLASS_USER_INTERACTIVE`
@property (nonatomic, class, readonly) PSPDFDispatchQueue<PSPDFConcurrentQueue> *userInteractiveQueue;

/// Returns the wrapped global queue `QOS_CLASS_USER_INITIATED/DISPATCH_QUEUE_PRIORITY_HIGH`
@property (nonatomic, class, readonly) PSPDFDispatchQueue<PSPDFConcurrentQueue> *userInitiatedQueue;

/// Returns the wrapped global queue `QOS_CLASS_DEFAULT/DISPATCH_QUEUE_PRIORITY_DEFAULT`
@property (nonatomic, class, readonly) PSPDFDispatchQueue<PSPDFConcurrentQueue> *defaultQueue;

/// Returns the wrapped global queue `QOS_CLASS_UTILITY/DISPATCH_QUEUE_PRIORITY_LOW`
@property (nonatomic, class, readonly) PSPDFDispatchQueue<PSPDFConcurrentQueue> *utilityQueue;

/// Returns the wrapped global queue `QOS_CLASS_BACKGROUND/DISPATCH_QUEUE_PRIORITY_BACKGROUND`
@property (nonatomic, class, readonly) PSPDFDispatchQueue<PSPDFConcurrentQueue> *backgroundQueue;

/// Returns a global concurrent queue specific to a QOS class.
+ (PSPDFDispatchQueue<PSPDFConcurrentQueue> *)queueFromQOSClass:(qos_class_t)qosClass;

@end

// MARK: - Extended Queue Semantics

@protocol PSPDFCustomConcurrentQueue;

/// A dispatch queue that executes its work items concurrently.
///
/// All global queues except the main queue conform to this protocol, and work items submitted to any queue will eventually
/// run on one of these global queues. Because the global queues do not support exclusive execution of work items (aka.
/// barriers), there is a separate sub-protocol for custom concurrent queues.
@protocol PSPDFConcurrentQueue <NSObject>

/// Creates a new concurrent queue that uses the receiver as its parent queue.
///
/// Blocks submitted to this new queue will eventually be performed on the root ancestor queue.
///
/// @param name The name for the new queue.
- (PSPDFDispatchQueue<PSPDFCustomConcurrentQueue> *)concurrentNamedQueue:(NSString *)name;

@end

/// A concurrent queue that allows exclusive execution of work items, and eventually executes those items on one of the
/// global queues.
@protocol PSPDFCustomConcurrentQueue <PSPDFConcurrentQueue>

/// Returns whether or not you are executing exclusivle in the context of the current queue.
///
/// @note Handle with care! Whether or not we are running on a certain queue is rather complex to figure out, so there may
/// be dragons associated with this…
@property (nonatomic, readonly, getter=isRunningExclusively) BOOL runningExclusively;

/// Schedules the given block for asynchronous, exclusive execution on the receiver.
///
/// While the block is executing, no other blocks will run in the context of the receiver.
///
/// @param exclusiveWork The work to be executed exclusively.
- (void)barrierAsync:(dispatch_block_t)exclusiveWork;

/// Schedules the given block for exclusive execution on the receiver **and blocks** until execution finished.
///
/// While the block is executing, no other blocks will run in the context of the receiver.
///
/// @warning Calling this method while you are _already_ executing in the context of the receiver will inevitably deadlock!
/// @param exclusiveWork The work to be executed exclusively.
- (void)barrierSync:(NS_NOESCAPE dispatch_block_t)exclusiveWork;

// MARK: Conditional Enqueueing

/// Schedule the block for exclusive execution if not already executing on the queue.
///
/// When already executing exclusively in the context of the receiver, the block is executed synchronously.
///
/// @param block The work item in need of exclusive execution.
- (void)barrierAsyncIfNotOnQueue:(dispatch_block_t)block;

/// Execute the block exclusively on the queue.
- (void)barrierSyncIfNotOnQueue:(NS_NOESCAPE dispatch_block_t)block;

@end

NS_ASSUME_NONNULL_END
