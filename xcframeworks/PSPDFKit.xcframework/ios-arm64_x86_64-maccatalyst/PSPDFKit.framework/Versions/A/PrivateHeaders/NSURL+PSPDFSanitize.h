//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
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

typedef NS_OPTIONS(NSUInteger, PSPDFURLSanitationOptions) {
    /// If no scheme is present, add the specified scheme.
    PSPDFURLSanitationAddScheme = 1 << 0,

    /// If the URL ends with a slash, remove it.
    PSPDFURLSanitationRemoveSlashSuffix = 1 << 1,

    /// If the URL contains any repeated forward slashes (//) after the protocol definition,
    /// they are replaced by a single one.
    PSPDFURLSanitationRemoveDoubleForwardSlash = 1 << 2,

    /// Invokes `URLByStandardizingPath` on the URL.
    PSPDFURLSanitationStandardizedURL = 1 << 3,

    /// All options.
    PSPDFURLSanitationOptionsAll = NSUIntegerMax
} NS_SWIFT_NAME(URLSanitationOptions);

@interface NSURL (PSPDFSanitize)

/// Sanitzes the URL with options. Default scheme is http.
- (NSURL *)pspdf_sanitizeWithOptions:(PSPDFURLSanitationOptions)options NS_SWIFT_NAME(sanitize(_:));
- (NSURL *)pspdf_sanitizeWithOptions:(PSPDFURLSanitationOptions)options defaultScheme:(NSString *)defaultScheme NS_SWIFT_NAME(sanitize(_:defaultScheme:));

/// Compares objects using pspdf_sanitizedIsEqualToURL: if they are both URLs.
- (BOOL)pspdf_sanitizedIsEqualTo:(id)other NS_SWIFT_NAME(sanitizedIsEqual(to:));

/// Sanitizes self and otherURL using PSPDFURLSanitationOptionRemoveSlashSuffix |
/// PSPDFURLSanitationOptionRemoveDoubleForwardSlash | PSPDFURLSanitationOptionStandardizedURL before comparing.
- (BOOL)pspdf_sanitizedIsEqualToURL:(NSURL *)otherURL NS_SWIFT_NAME(sanitizedIsEqual(toURL:));;

@end

NS_ASSUME_NONNULL_END
