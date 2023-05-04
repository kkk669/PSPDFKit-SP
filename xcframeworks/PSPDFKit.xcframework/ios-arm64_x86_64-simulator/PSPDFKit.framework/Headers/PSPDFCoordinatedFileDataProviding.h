//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFFileDataProviding.h>
#import <PSPDFKit/PSPDFFileConflictResolution.h>
#else
#import "PSPDFFileDataProviding.h"
#import "PSPDFFileConflictResolution.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFFileCoordinationDelegate;

/// File-based data providers that support file coordination (`NSFileCoordinator`).
PSPDF_PROTOCOL_SWIFT(CoordinatedFileDataProviding)
@protocol PSPDFCoordinatedFileDataProviding <PSPDFFileDataProviding>

// MARK: File Presentation

/// The data provider’s file presenter.
/// If the data provider implements `NSFilePresenter` itself, then return `self`.
/// The data provider’s `fileURL` is expected to be the same as the file presenter’s `presentedItemURL`.
@property (nonatomic, readonly) id<NSFilePresenter> filePresenter;

/// A data provider implementation may notify this delegate of `NSFilePresenter`-like notifications when the
/// underlying file is updated. This property is set internally by PSPDFKit and should not be set otherwise.
@property (nonatomic, weak) id<PSPDFFileCoordinationDelegate> coordinationDelegate;

@optional

// MARK: Conflict Resolution

/// Specifies whether conflict resolution is currently possible.
///
/// Should be checked before invoking any conflict resolution calls on the data provider.
///
/// The implementation of this property should reflect any internal limitations (like the
/// file system type for the `PSPDFCoordinatedFileDataProvider`).
@property (atomic, readonly) BOOL isConflictResolutionAvailable;

/// Resolves a file conflict (externally removed or modified file) using a selected conflict resolution option.
///
/// This method should be invoked in response to a `presentedItemDidChangeForDataProvider:` or
/// `accommodatePresentedItemDeletionForDataProvider:completionHandler:` file presenter update.
///
/// If the data provider is used in context of `Document`, invoking
/// `-[PSPDFDocument resolveFileConflictForDataProvider:withResolution:error:]` should be preferred.
/// It will call through to this implementation and also perform all necessary document updates.
///
/// @note Passing `PSPDFFileConflictResolutionSave` does nothing if a file copy is not currently
/// available (`isConflictResolutionAvailable == NO`).
///
/// @param resolution The conflict resolution option that should be performed.
/// @param error Error details if the conflict resolution operation failed.
/// @return `true`, if the conflict resolution was successful and `false` otherwise.
- (BOOL)resolveFileConflictWithResolution:(PSPDFFileConflictResolution)resolution error:(NSError **)error;

@end

/// Methods that need to be implemented by the `coordinationDelegate` of a coordinated file data
/// provider. As such, all methods in this protocol are required.
PSPDF_PROTOCOL_SWIFT(FileCoordinationDelegate)
@protocol PSPDFFileCoordinationDelegate<NSObject>

/// Called after the underlying file was modified.
///
/// Roughly corresponds to a `presentedItemDidChange` `NSFilePresenter` notification.
/// This call is only invoked if the file content changes since the last successful read.
/// File metadata updates are ignored. Will be called on a private queue.
///
/// @param dataProvider The requesting coordinated file data provider.
- (void)presentedItemDidChangeForDataProvider:(id<PSPDFCoordinatedFileDataProviding>)dataProvider;

/// Called when the underlying file is about to be deleted.
///
/// Corresponds to a `accommodatePresentedItemDeletionWithCompletionHandler:` `NSFilePresenter`
/// notification. Will be called on a private queue.
///
/// @note It is crucial that completionHandler is invoked after this method is handled.
/// Best to do it on the same queue and not dispatching. Dispatchign to the main thread
/// and invoking the callback can lead to deadlocks if the file is deleted from the main
/// thread in the host app.
///
/// @param dataProvider The requesting coordinated file data provider.
/// @param completionHandler Should be invoked to allow the deletion to continue.
- (void)accommodatePresentedItemDeletionForDataProvider:(id<PSPDFCoordinatedFileDataProviding>)dataProvider completionHandler:(void (^)(NSError *_Nullable))completionHandler;

@end

/// A helper to quickly determine if a coordinated data provider provides conflict resolution at a given moment.
///
/// @param dataProvider The data provider to check.
/// @return `true` if conflict resolution APIs are implemented and conflict resolution is currently possible.
/// `false` in all other cases.
PSPDF_EXPORT BOOL PSPDFConflictResolutionAvailableForDataProvider(id<PSPDFCoordinatedFileDataProviding> dataProvider) NS_SWIFT_NAME(ConflictResolutionAvailable(forDataProvider:));

NS_ASSUME_NONNULL_END
