//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFFileDataProviding.h>
#else
#import "PSPDFFileDataProviding.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// An implementation of `DataProviding` that acts upon a file.
PSPDF_CLASS_SWIFT(FileDataProvider)
@interface PSPDFFileDataProvider : NSObject<PSPDFFileDataProviding>

// MARK: - Creating Instances

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a `FileDataProvider` with the given `fileURL`.
///
/// When passing a `progress` object that returns `false` for its `isFinished` property, the newly
/// initialized object is considered in-flight. The main implications of this state are:
///
/// - the instance will assume that there is no file at `fileURL`, yet
/// - therefore, the `data` property will be `nil`
/// - as will the `UID` be
/// - calling `replace(with:)` will fail with `PSPDFKit.Error.dataProviderInFlight`
///
/// @note If you are expecting to encounter symlinks or alias files, you need to first resolve those
/// using the apropriate `URL` APIs before passing them here. For performance reasons, `FileDataProvider`
/// **will not** automatically resolve them for you.
///
/// @param fileURL A resolved file URL pointing to a file on the filesystem.
/// @param progress (Optional) A `Progress` instance that indicates progress until the file at `fileURL` can be accessed.
- (instancetype)initWithFileURL:(NSURL *)fileURL progress:(nullable NSProgress *)progress NS_DESIGNATED_INITIALIZER;

/// @see `initWithFileURL:progress:`
- (instancetype)initWithFileURL:(NSURL *)fileURL;

// MARK: - Implementations of optional protocol methods

/// The progress object passed during initialization — if any.
@property (nonatomic, nullable, readonly) NSProgress *progress;

/// The last error encountered accessing the underlying file.
///
/// The value is cleared whenever a successful read of the underlying data happens.
@property (nonatomic, nullable, readonly) NSError *error;

/// Creates a new `FileDataSink` with the given options, pointed at a unique temporary file with the
/// same path extension as the receiver’s `fileURL`.
///
/// This method fails if the temporary file for the new data sink could not be created.
- (nullable id<PSPDFDataSink>)createDataSinkWithOptions:(PSPDFDataSinkOptions)options error:(NSError **)error;

/// Replaces the file backing the receiver based on the data backing `replacementDataSink`.
///
/// This method fails if the receiver is in-flight or if writing `replacementDataSink`’s data to
/// `fileURL` fails.
///
/// @param replacementDataSink An instance of `FileDataSink`, typically created by calling `createDataSink(options:)`.
/// @param error A pointer to populate with an error IFF replacing the receiver’s content fails.
/// @warning This method raises an exception if `replacementDataSink` is not an instance of `FileDataSink`, or if `replacementDataSink.isFinished` is `false`.
- (BOOL)replaceContentsWithDataSink:(id<PSPDFDataSink>)replacementDataSink error:(NSError **)error;

/// Whether or not a writable file exists at `fileURL`.
@property (nonatomic, readonly) BOOL canWrite;

/// Removes the file backing the receiver.
///
/// This method fails if the receiver is in-flight, or when the item at `fileURL` cannot be deleted.
- (BOOL)deleteDataWithError:(NSError **)error;

/// Lets go of all resources held by the receiver.
///
/// Will block until any ongoing read or write access through the receiver has finished.
- (void)clearCache;

@end

NS_ASSUME_NONNULL_END
