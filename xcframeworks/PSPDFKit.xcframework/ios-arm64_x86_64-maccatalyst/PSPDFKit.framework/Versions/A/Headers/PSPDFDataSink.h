//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
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

/// Specifies the type of `PSPDFDataSink` you're requesting.
typedef NS_OPTIONS(NSUInteger, PSPDFDataSinkOptions) {
    /// No option specified, the returned `PSPDFDataSink` is completely empty and writing starts at the beginning.
    PSPDFDataSinkOptionNone = 0,

    /// Append mode. The data provider’s data will be used as a starting point and writing starts at the end.
    PSPDFDataSinkOptionAppend = 0x01
} NS_SWIFT_NAME(DataSinkOptions);

/// This protocol allows an implementation of `DataProviding` to return an object that can be used to re-write/append to a data source.
PSPDF_PROTOCOL_SWIFT(DataSink)
@protocol PSPDFDataSink<NSObject>

/// `isFinished` should return `true` if `finish` has been called. This is used for
/// consistency checks to make sure writing has actually finished.
@property (nonatomic, readonly) BOOL isFinished;

/// The options the receiver was initialized with, describing its behavior for writing.
@property (nonatomic, readonly) PSPDFDataSinkOptions options;

/// This method should append the given `data` to your data source. If your data source is full or encounters a error,
/// return `false` and the write operation will be marked as a failure.
- (BOOL)writeData:(NSData *)data;

/// This is called at the end of all the write operations. This gives you the opportunity to finish up any compression
/// or encryption operation. After this, `writeData:` will no longer be called and the `PSPDFDataSink` is finished.
/// If any error occurs, return `false` and the write operation will be marked as a failure.
- (BOOL)finish;

@end

NS_ASSUME_NONNULL_END
