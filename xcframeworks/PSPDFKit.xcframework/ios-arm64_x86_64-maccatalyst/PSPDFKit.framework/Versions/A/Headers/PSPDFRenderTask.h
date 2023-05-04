//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFRenderQueue.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFRenderRequest;
@class PSPDFRenderTask;

/// Implement this delegate to get rendered pages. (Most of the times, you want to use `PDFCache` instead)
PSPDF_PROTOCOL_SWIFT(RenderTaskDelegate)
@protocol PSPDFRenderTaskDelegate<NSObject>
@optional

/// Called when a render task finishes successfully. Guaranteed to be called from the main thread.
- (void)renderTaskDidFinish:(PSPDFRenderTask *)task;

/// Called when a render task fails. Guaranteed to be called from the main thread.
- (void)renderTask:(PSPDFRenderTask *)task didFailWithError:(NSError *)error;

@end

/// A render task is used to create an image from the page (or part of it) of a document.
///
/// Depending on the `PSPDFRenderRequest` cache policy, a render task checks the cache
/// before actually triggering a new rendering.
///
/// You create a render task by passing it an instance of `PSPDFRenderRequest`. Once
/// you have created a render request make sure to fully set it up before scheduling
/// it in a render queue.
///
/// A simple example of requesting an image from a page:
///
/// ```
/// let request = MutableRenderRequest(document: document)
/// request.pageIndex = 0
/// request.imageSize = CGSize(width: 320.0, height: 480.0)
///
/// let task = try RenderTask(request: request)
/// task.priority = .utility
/// task.delegate = self
///
/// SDK.shared.renderManager.renderQueue.schedule(task)
/// ```
PSPDF_CLASS_SWIFT(RenderTask)
@interface PSPDFRenderTask : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a task with a given render request.
///
/// The render request is copied so you can no longer make changes to it after creating
/// a render task out of it.
///
/// @note The initializer verifies the request and returns nil if the request is not valid.
///
/// @param request The render request the task should fulfill.
/// @param error Error that is set if creating the render task failed, because the render request is invalid.
- (nullable instancetype)initWithRequest:(PSPDFRenderRequest *)request error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/// The render request this task is initialized with.
@property (nonatomic, readonly) PSPDFRenderRequest *request;

/// The delegate that is used for reporting progress on this render task.
@property (nonatomic, weak) id<PSPDFRenderTaskDelegate> delegate;

/// The completion handler to be called after the rendering has completed.
@property (atomic, copy, nullable) void (^completionHandler)(UIImage *_Nullable image, NSError *_Nullable error);

// MARK: Prioritizing Render Tasks

/// The priority of the render task.
///
/// Defaults to PSPDFRenderQueuePriorityUnspecified.
@property (atomic) PSPDFRenderQueuePriority priority;

// MARK: Output of a Render Task

/// The rendered image after the task has completed.
@property (atomic, readonly, nullable) UIImage *image;

// MARK: Managing the Status of a Render Task

/// `true` if the task has been cancelled, `false` otherwise.
@property (atomic, readonly, getter=isCancelled) BOOL cancelled;

/// `true` if the task has been completed, `false` otherwise.
@property (atomic, readonly, getter=isCompleted) BOOL completed;


/// Cancels a task.
///
/// You will no longer receive any callbacks from this task after cancelling it.
- (void)cancel;

/// Groups a number of tasks together and executes a completion handler once all grouped
/// tasks complete.
///
/// @param tasks The tasks you want to group.
/// @param completionHandler The completion handler that is executed once all render
/// tasks in the `tasks` array completed.
+ (void)groupTasks:(NSArray<PSPDFRenderTask *> *)tasks completionHandler:(void (^)(void))completionHandler;

@end

NS_ASSUME_NONNULL_END
