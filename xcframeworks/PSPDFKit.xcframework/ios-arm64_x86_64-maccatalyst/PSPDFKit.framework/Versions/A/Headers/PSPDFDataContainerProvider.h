//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFDataProviding.h>
#else
#import "PSPDFDataProviding.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// An implementation of `DataProviding` that operates on a single `Data`.
///
/// This may be used to initialize `Document` with data.
///
/// @warning You might want to set a custom UID otherwise the `UID` will be calculated from a part of the PDF contents, which might be the same if the files are similar.
///
/// @note When using this data provider, PSPDFKit is unable to automatically save annotation changes back into the PDF.
/// Keep in mind that iOS is an environment without virtual memory. Loading a large PDF will simply get your app killed by the iOS watchdog while you try to allocate more memory than is available.
///
/// If you use `Data` because of encryption, look into `PSPDFAESCryptoDataProvider` or a custom implementation of `DataProviding` instead for a way to dynamically decrypt the needed portions of the PDF.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(DataContainerProvider)
@interface PSPDFDataContainerProvider : NSObject<PSPDFDataProviding>

// MARK: - Creating Instances

PSPDF_EMPTY_INIT_UNAVAILABLE
/// Initializes a `DataContainerProvider` with the given `data`.
///
/// @param data A blob containing the data to be held by the receiver.
- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

// MARK: - Implementations of optional protocol methods

/// An optional `Progress` object, indicating when the data backing the receiver is still being generated.
///
/// If this property is not nil, the receiver is considered “in-flight” until the `isFinished` property
/// of the progress object returns `true`: it acts as a promise for data that may become later.
///
/// All reading and writing operations on an in-flight data container provider are going to fail, reporting
/// `PSPDFError.dataProviderIsInFlight` where possible.
@property (nonatomic, readonly, nullable) NSProgress *progress;

/// Creates a new data container sink.
///
/// If the `options` contains the `append` flag, and `progress` is completed, the data sink will contain
/// all of `data`. Otherwise, the object returned will start with an empty buffer.
///
/// @note This call never fails.
- (nullable id<PSPDFDataSink>)createDataSinkWithOptions:(PSPDFDataSinkOptions)options error:(NSError **)error;

/// Replaces the receiver’s `data` with the data written to `replacementDataSink`.
///
/// This method fails if the receiver is in-flight, meaning it has a progress object whose `isFinished`
/// property returns `false`
///
/// @warning This method raises an exception if `replacementDataSink` is not an instance of `DataContainerSink`,
/// or if `replacementDataSink.isFinished` is `false`.
- (BOOL)replaceContentsWithDataSink:(id<PSPDFDataSink>)replacementDataSink error:(NSError * __autoreleasing *)error;

/// Clears the receiver’s `data`.
///
/// @note This method never fails.
- (BOOL)deleteDataWithError:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
