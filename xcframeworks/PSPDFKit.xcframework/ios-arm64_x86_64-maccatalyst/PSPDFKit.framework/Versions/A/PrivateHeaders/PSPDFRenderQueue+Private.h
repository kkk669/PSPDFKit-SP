//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFRenderQueue.h>

NS_ASSUME_NONNULL_BEGIN

// uncomment to enable detailed logging
//#define PSPDFRenderQueueLog(...) do { NSLog(__VA_ARGS__); } while(0)

#ifndef PSPDFRenderQueueLog
#define PSPDFRenderQueueLog(...)
#endif

@interface PSPDFRenderQueue ()

/// This marks all running render jobs with the given document and pages as outdated
/// which results in these jobs not updating the cache.
///
/// When a call to this method returns it is guaranteed that no render jobs that were
/// running at that time and match the document and one of the pages will update the
/// cache.
///
/// @param document The document that changed.
/// @param pages The pages that changed in that document or `nil` if the whole document changed.
- (void)markRunningJobsOutdatedWithDocument:(PSPDFDocument *)document pages:(nullable NSIndexSet *)pages;

@end

@interface PSPDFRenderQueue (Testing)

/// Returns the number of running jobs.
///
/// @important Don't call this from any kind of completion handler of the render engine!
@property (nonatomic, readonly) NSUInteger numberOfRunningJobs;

/// Return how many jobs are currently queued.
///
/// @important Don't call this from any kind of completion handler of the render engine!
@property (nonatomic, readonly) NSUInteger numberOfQueuedJobs;

@end

PSPDF_EXTERN NSString *PSPDFRenderQueuePriorityToString(PSPDFRenderQueuePriority priority) NS_SWIFT_NAME(RenderQueuePriorityToString(_:));

NS_ASSUME_NONNULL_END
