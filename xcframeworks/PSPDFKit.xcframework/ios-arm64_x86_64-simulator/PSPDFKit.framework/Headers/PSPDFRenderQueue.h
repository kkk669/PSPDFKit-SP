//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFRenderJob, PSPDFRenderQueue, PSPDFRenderReceipt, PSPDFRenderTask, PSPDFRenderRequest;

/// Absolute limit for image rendering (memory constraint)
PSPDF_EXPORT const CGSize PSPDFRenderSizeLimit;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFRenderQueuePriority) {
    /// Used for unspecified renderings with the lowest priority.
    PSPDFRenderQueuePriorityUnspecified = 0,

    /// Used for renderings that the user is not aware of, such as building a cache in the background.
    PSPDFRenderQueuePriorityBackground = 100,

    /// Used for renderings that the user might see but that are not necessary to complete, such as generating thumbnails that are not necessary for the user to properly work with a document but.
    PSPDFRenderQueuePriorityUtility = 200,

    /// Used for renderings that the user requested but that are not required for the user to keep using a document.
    PSPDFRenderQueuePriorityUserInitiated = 300,

    /// Used for renderings that the user requested and that are currently blocking their workflow.
    PSPDFRenderQueuePriorityUserInteractive = 400,
} PSPDF_ENUM_SWIFT(RenderQueue.Priority);

/// The render queue is responsible for scheduling and completing tasks. Typically
/// you don't create your own render queue but instead use the render queue provided
/// by the render manager. Creating your own render queue is possible but due to internal
/// resource constraints will almost never speed up rendering but instead the queues
/// try to access the same resources and then need to wait until the resource becomes
/// available.
///
/// The goal of the render queue is to keep the average time it takes to complete a
/// render task at a minimum. To achieve this the render queue intelligently schedules
/// and bundles tasks. Therefore the order in which scheduled tasks are executed is
/// undefined and depends on many factors.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(RenderQueue)
@interface PSPDFRenderQueue : NSObject

// MARK: Requests

/// Schedules a render task in the receiving queue.
///
/// The order in which tasks are executed is not necessarily the order in which they
/// have been scheduled, nor the order of priority. The render queue makes an effort
/// to serve as many tasks as possible in a timely manner. You should treat the order
/// of execution of tasks as non-deterministic.
///
/// @param task The render task to schedule in the queue.
- (void)scheduleTask:(PSPDFRenderTask *)task NS_SWIFT_NAME(schedule(_:));

/// Schedules multiple render tasks in the receiving queue.
///
/// The order in which tasks are executed is not necessarily the order in which they
/// have been scheduled, nor the order of priority. The render queue makes an effort
/// to serve as many tasks as possible in a timely manner. You should treat the order
/// of execution of tasks as non-deterministic.
///
/// @param tasks The render tasks to schedule in the queue.
- (void)scheduleTasks:(NSArray<PSPDFRenderTask *> *)tasks NS_SWIFT_NAME(schedule(_:));

@end

@interface PSPDFRenderQueue (Debugging)

/// Cancel all queued and running tasks.
///
/// You should not call this method in production code. Instead to cancel tasks, call
/// `cancel` on the tasks you actually want to cancel. Tasks that are started by the
/// framework internally are cancelled by their respective owner if their result is
/// no longer needed.
///
/// @warning This method should only be used for debugging purpose and might result
/// in unexpected behavior when called while the framework is requesting images.
- (void)cancelAllTasks;

@end

NS_ASSUME_NONNULL_END
