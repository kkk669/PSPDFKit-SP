//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//
//  Based on GitHub's Mantle project, MIT licensed.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSError (PSPDFFoundation)

/// Creates a new error for an exception that occurred during updating an `PSPDFModel`.
///
/// exception - The exception that was thrown while updating the model.
/// This argument must not be nil.
///
/// Returns an error that takes its localized description and failure reason from the exception.
+ (instancetype)pspdf_modelErrorWithException:(NSException *)exception;

/// Helper to encapsulate an OS error.
+ (instancetype)pspdf_OSErrorWithStatus:(OSStatus)status description:(nullable NSString *)description;

/// Helper to convert errno to an NSError.
+ (instancetype)pspdf_errorWithPOSIXCode:(int)code;

/// Returns true if
///
/// NSCocoaErrorDomain & NSFileNoSuchFileError.
/// NSCocoaErrorDomain & NSFileReadNoSuchFileError
/// NSPOSIXErrorDomain & ENOENT
///
/// @note This function will also search the userInfo chain for NSUnderlyingErrorKey recursively.
@property (nonatomic, readonly) BOOL pspdf_fileNotFoundError NS_SWIFT_NAME(fileNotFoundError);

/// Returns true if
///
/// NSCocoaErrorDomain & NSFileWriteFileExistsError.
///
/// @note This function will also search the userInfo chain for NSUnderlyingErrorKey recursively.
@property (nonatomic, readonly) BOOL pspdf_fileExistsError NS_SWIFT_NAME(fileExistsError);

/// Checks if an error is based on the fact that there is no internet connection available.
///
/// NSURLErrorDomain &  NSURLErrorTimedOut
/// NSPOSIXErrorDomain & ECONNABORTED
///
/// @note This function will also search the userInfo chain for NSUnderlyingErrorKey recursively.
@property (nonatomic, readonly) BOOL pspdf_internetConnectionNotAvailable NS_SWIFT_NAME(internetConnectionNotAvailable);

/// Returns true if
///
/// NSOSStatusErrorDomain & errSecItemNotFound
///
/// @note This function will also search the userInfo chain for NSUnderlyingErrorKey recursively.
@property (nonatomic, readonly) BOOL pspdf_secItemNotFound NS_SWIFT_NAME(secItemNotFound);

@end


@interface NSException (PSPDFFoundation)

/// Returns a dictionary suitable for NSError userInfo.
- (NSDictionary *)pspdf_errorUserInfoWithKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
