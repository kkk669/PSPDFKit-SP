//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFFileDataProvider.h>
#import <PSPDFKit/PSPDFSecurityScopedURL.h>
#else
#import "PSPDFFileDataProvider.h"
#import "PSPDFSecurityScopedURL.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFFileDataProvider ()

/// This is used by Instant to initialize without a file URL because it will be provided later when the document is loaded.
///
/// The correctly handle not having a file URL, the Instant subclass overrides the fileURL getter.
/// The Instant subclass also overrides a few methods that could read from fileURL before the document is loaded (when the progress is incomplete).
/// Methods that read from fileURL after the document is loaded assert that it is not nil at that point. Situations causing this to occur should be fixed.
///
/// Therefore the implementation of this class should be sure to not read the _fileURL instance variable anywhere except in the property getter.
///
/// @param progress A progress that completes when the document is loaded.
- (instancetype)initWithProgress:(NSProgress *)progress NS_DESIGNATED_INITIALIZER;

/// Updates the file URL and invalidates the file handle when set.
@property (nonatomic, readwrite) NSURL *fileURL;

/// Re-declaration so the coordinated file data provider can store errors.
@property (nonatomic, nullable, readwrite) NSError *error;

// MARK: Error Generators

typedef NS_ENUM(NSInteger, PSPDFFileDataProviderOperation) {
    PSPDFFileDataProviderOperationReading,
    PSPDFFileDataProviderOperationWriting,
    PSPDFFileDataProviderOperationDeleting,
};

- (NSError *)fileURLNotSetErrorForOperation:(PSPDFFileDataProviderOperation)operation;
- (NSError *)dataProviderInFlightErrorForFileURL:(nullable NSURL *)fileURL operation:(PSPDFFileDataProviderOperation)operation;

// MARK: File URL change tolerant data provider methods

/// An alternative to the `DataProviding` method `size`, that allows us to specify the `destinationURL`.
///
/// @param fileURL The URL of the file for which the size needs to be retrieved.
/// @param error A pointer to populate with an error when accessing the file fails.
/// @return Returns `nil` when the file could not be accessed, otherwise an `NSNumber` of the size of the file in bytes.
- (nullable NSNumber *)sizeForFileAtURL:(NSURL *)fileURL error:(NSError **)error;

/// An alternative to the `DataProviding` method `readWithSize:atOffset:`, that allows us to specify the `destinationURL`.
- (nullable NSData *)readDataFromFileAtURL:(NSURL *)fileURL withSize:(uint64_t)size atOffset:(uint64_t)offset error:(NSError **)error;

/// An alternative to the `DataProviding` method `data`, that allows us to specify the `destinationURL`.
- (nullable NSData *)dataFromFileAtURL:(NSURL *)fileURL error:(NSError **)error;

/// An alternative to the `DataProviding` method `replaceWithDataSink:`, that allows us to specify the `fileURL`.
- (BOOL)replaceFileAtURL:(NSURL *)fileURL withDataSink:(id<PSPDFDataSink>)replacementDataSink error:(NSError *__autoreleasing *)error;

/// An alternative to the `DataProviding` method `deleteDataWithError:`, that allows us to specify the `fileURL`.
- (BOOL)deleteFileAtURL:(NSURL *)fileURL withError:(NSError *__autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
