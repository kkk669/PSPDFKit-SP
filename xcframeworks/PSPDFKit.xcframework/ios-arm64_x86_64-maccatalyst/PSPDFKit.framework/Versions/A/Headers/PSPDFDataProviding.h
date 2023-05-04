//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFDataSink.h>
#else
#import "PSPDFDataSink.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Specifies which types of operations the data provider supports.
/// Every data provider must support reading.
typedef NS_OPTIONS(NSUInteger, PSPDFDataProvidingAdditionalOperations) {
    /// No additional operations are supported.
    PSPDFDataProvidingAdditionalOperationNone = 0x00,

    /// Specifies that this data provider supports writing.
    PSPDFDataProvidingAdditionalOperationWrite = 0x01
} NS_SWIFT_NAME(DataProvidingAdditionalOperations);

/// This protocol is to be used by all possible data providers for PDF access.
/// E.g. a `FileDataProvider` or `AESCryptoDataProvider`.
///
/// @note Ensure that your implementation is thread safe.
/// Data might be fetched from multiple threads, in random chunks.
PSPDF_PROTOCOL_SWIFT(DataProviding)
@protocol PSPDFDataProviding<NSObject, NSSecureCoding>

/// Creates a `Data` object with all the data of the provider. Use with caution - this can take a while if the data provider is
/// a remote source and it can quickly exhaust all your memory if it is a big data provider.
- (nullable NSData *)data:(NSError **)error;

/// Returns the size of the data.
@property (nonatomic, readonly) uint64_t size;

/// Returns a UID that enables you to uniquely identify this data provider, even after restarting the application.
@property (nonatomic, readonly) NSString *UID;

/// Specifies which additional operations are supported, if any.
@property (nonatomic, readonly) PSPDFDataProvidingAdditionalOperations additionalOperationsSupported;

/// Reads and returns data read from offset with size. You have to make sure not to read past the end of your data.
- (nullable NSData *)readDataWithSize:(uint64_t)size atOffset:(uint64_t)offset error:(NSError **)error;

/// The public key to identify the data source. This should be set before the data provider is used in a `Document`.
/// Used for special types of licenses only.
@property (nonatomic, nullable) NSData *signature;

@optional

/// An optional progress object that indicates that the data backing the data provider is still being generated.
/// Be sure to transition into the fully completed progress state only after the data is completely ready for reading.
@property (nonatomic, readonly, nullable) NSProgress *progress;

/// Providing the data might fail. This sets the last error trying to read data.
/// 
/// @note This is not used for creating data sinks.
@property (nonatomic, readonly, nullable) NSError *error;

/// This method should create a data sink for your data provider with the given options.
/// PSPDFKit will write all the appropriate data into it and pass it to `replaceContents(with:)` when appropriate.
- (nullable id<PSPDFDataSink>)createDataSinkWithOptions:(PSPDFDataSinkOptions)options error:(NSError **)error;

/// This method should replace your current data with the one written into `replacementDataSink`.
///
/// When called by PSPDFKit, `replacementDataSink` is the object instantiated in `createDataSinkWithOptions:`.
/// Depending on `replacementDataSink.options`, you either have to append or replace the data.
- (BOOL)replaceContentsWithDataSink:(id<PSPDFDataSink>)replacementDataSink error:(NSError * __autoreleasing *)error;

/// Whether it is acceptable to call `replaceContents(with:)` when `additionalOperationsSupported` contains `.write`.
///
/// If this method is not implemented the behavior defaults to `true`.
@property (nonatomic, readonly) BOOL canWrite;

/// This method should delete any data that is referenced by this data provider.
/// PSPDFKit uses this method to delete temporary data, if necessary.
/// Returns YES on successful deletion, NO otherwise.
- (BOOL)deleteDataWithError:(NSError **)error;

/// Should reset any cached data and restore the data provider to its original state.
/// For file based data providers, this should recreate the file handle in case the underlying file was replaced.
- (void)clearCache;

/// Toggle if a document using this data provider should use the disk cache.
/// If not implemented, enabled is assumed.
@property (nonatomic, readonly) BOOL useDiskCache;

@end

NS_ASSUME_NONNULL_END
