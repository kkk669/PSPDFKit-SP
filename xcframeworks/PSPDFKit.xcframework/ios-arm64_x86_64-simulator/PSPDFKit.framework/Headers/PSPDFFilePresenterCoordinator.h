//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Coordinates file presenters and notifications.
/// Observed presenters are automatically unregistered in response to `UIApplicationDidEnterBackgroundNotification` notification.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(FilePresenterCoordinator)
@interface PSPDFFilePresenterCoordinator : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Shared instance of the coordinator.
@property(class, nonatomic, readonly) PSPDFFilePresenterCoordinator *sharedCoordinator;

/// Registers the specified file presenter object so that it can receive notifications.
- (void)observeFilePresenter:(id<NSFilePresenter>)filePresenter;

/// Unregisters the specified file presenter object.
- (void)unobserveFilePresenter:(id<NSFilePresenter>)filePresenter;

/// Re-registers the file presenter for file presentation changes.
///
/// This is needed if the file the file presenter is tracking was previously
/// deleted and then re-created.
///
/// @param filePresenter The file presenter to reload. Should be already registered
/// with the coordinator, otherwise this method is a NOOP.
- (void)reloadFilePresenter:(id<NSFilePresenter>)filePresenter;

// MARK: Collection helpers

/// Observers multiple objects at the same time.
- (void)observeFilePresenters:(nullable NSArray<id<NSFilePresenter>> *)filePresenters;

/// Unobserve multiple objects at the same time.
- (void)unobserveFilePresenters:(nullable NSArray<id<NSFilePresenter>> *)filePresenters;

@end

NS_ASSUME_NONNULL_END
