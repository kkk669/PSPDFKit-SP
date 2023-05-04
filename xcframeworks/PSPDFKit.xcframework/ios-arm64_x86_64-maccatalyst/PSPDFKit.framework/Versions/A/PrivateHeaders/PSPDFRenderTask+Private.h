//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFRenderTask.h>

#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Sent every time the state on the render task is changed, after calling the delegates.
/// Object is the render task.
PSPDF_APP_EXPORT NSNotificationName const PSPDFRenderTaskDidChangeStateNotification;

@interface PSPDFRenderTask ()

@property (atomic, nullable) UIImage *image;
@property (atomic, nullable) NSError *error;

/// Notifies the delegate and the completion handler that this task finished.
///
/// @note The notification is done synchronously, so this method needs to be called
/// on the queue that should dispatch the event. (Usually the main queue.)
- (void)completeTask;

@end

NS_ASSUME_NONNULL_END
