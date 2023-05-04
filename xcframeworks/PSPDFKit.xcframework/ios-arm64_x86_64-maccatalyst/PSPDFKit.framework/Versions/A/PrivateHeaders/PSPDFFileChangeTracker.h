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

@class PSPDFCoordinatedFileDataProvider;

/// Keeps track of file content changes during file coordination / file presenter operations.
///
/// Used to solve the following problem, mentioned in the `presentedItemDidChange` documentation:
///
/// > Because this method notifies you of both attribute and content changes,
/// you might want to check the modification date before needlessly rereading
/// the contents of a file. To do that, you must store the date when your object
/// last made changes to the file and compare that date with the item’s current
/// modification date. Use the coordinate(readingItemAt:options:error:byAccessor:)
/// method of a file coordinator to ensure exclusive access to the file when reading
/// the current modification date.
PSPDF_APP_CLASS_SWIFT(FileChangeTracker)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFFileChangeTracker : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Returns a new file change tracker initialized to track the passed presenter's file.
///
/// @param filePresenter A reference to the file presenter who's file we're monitoring.
/// Weakly held.
- (instancetype)initWithFilePresenter:(id<NSFilePresenter>)filePresenter NS_DESIGNATED_INITIALIZER;

/// A reference to the file presenter who's file we're monitoring.
@property (nonatomic, weak, readonly) id<NSFilePresenter> filePresenter;

/// Call this during a coordinated read to update the file modification checks.
///
/// @param fileURL an url obtained via a file coordination block.
/// Passing the URL avoids a nested coordinated read.
/// If `nil` a new coordinated read on `filePresenter.presentedItemURL` is performed instead.
///
/// @return Yes if the file has contents changed and no otherwise.
///
/// @note Needs to be called from a coordinated read block.
- (BOOL)markReadAndCheckContentChangesForCoordinatedFileURL:(nullable NSURL *)fileURL;

/// Call this during a coordinated write to update the file modification checks.
///
/// @param fileURL A url obtained via a file coordination block.
/// Passing the URL avoids a nested coordinated read.
/// If `nil` a new coordinated read on `filePresenter.presentedItemURL` is performed instead.
///
/// @note Needs to be called from a coordinated write block.
- (void)markWriteForCoordinatedFileURL:(nullable NSURL *)fileURL;

/// Checks if the file contents contents changed based on the tracked modification attribute.
/// This method can fail: be careful with the two BOOL return values.
///
/// This operation will perform a coordinated read of the file at `fileURL`
/// to obtain the latest required metadata.
/// This should be invoked from a `presentedItemDidChange` implementation
/// to check if the message can be suppressed.
///
/// @param didContentsChange Returns by reference whether the file contents have changed from the last known value. This value should only be read if the method returns YES.
/// @param update When `true`, the last modification attribute will be updated to reflect
/// the new state. Should be set to `true` when handling a `presentedItemDidChange` callback
/// and `false`, if just queriying the current state.
/// @param outError A pointer to an error to be set if the method returns NO.
/// @return Whether the check was able to run successfully. (This does not tell you whether the contents changed).
- (BOOL)getContentsChanged:(out BOOL *)didContentsChange updateModificationDate:(BOOL)update error:(NSError *__autoreleasing _Nullable *)outError;

@end

NS_ASSUME_NONNULL_END
