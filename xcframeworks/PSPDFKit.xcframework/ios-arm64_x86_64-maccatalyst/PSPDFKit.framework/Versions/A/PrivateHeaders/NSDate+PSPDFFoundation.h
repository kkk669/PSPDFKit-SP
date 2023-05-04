//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSDate (PSPDFFoundation)

/// Checks if the date contains any sub-second components.
/// If it does it returns a new date rounded down to the nearest second,
/// otherwise `self` is returned.
@property (nonatomic, readonly) NSDate *pspdf_dateLimitedToSecondPrecision;

// MARK: ISO 8601

/// Returns a new date represented by an ISO8601 string.
///
/// @param iso8601String An ISO8601 string
+ (nullable NSDate *)pspdf_dateFromISO8601String:(nullable NSString *)iso8601String;

/// Returns a string representation of the receiver in ISO8601 format.
@property (nonatomic, readonly) NSString *pspdf_ISO8601String NS_SWIFT_NAME(iso8601);

// MARK: ISO 1123

/// Returns a new date represented by an RFC1123 string.
///
/// @param rfc1123String An ISO8601 string
+ (nullable NSDate *)pspdf_dateFromRFC1123:(nullable NSString *)rfc1123String;

/// Returns a string representation of the receiver in RFC1123 format.
@property (nonatomic, readonly) NSString *pspdf_rfc1123String NS_SWIFT_NAME(rfc1123);

/// Same as `[[NSDate date] timeIntervalSince1970]`, just a lot faster.
PSPDF_EXTERN NSTimeInterval PSPDFGetTimeIntervalSince1970(void);

@end

NS_ASSUME_NONNULL_END
