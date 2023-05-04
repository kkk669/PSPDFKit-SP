//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
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

@interface NSString (PSPDFURLTypeDetection)

/// True if this is either a web url (http/s) or a mail link.
@property (readonly) BOOL pspdf_isURL NS_SWIFT_NAME(isURL);

@end

@interface NSURL (PSPDFURLTypeDetection)

/// Check for a prefix on the scheme, case-insensitive.
- (BOOL)pspdf_hasCaseInsensitivePrefix:(NSString *)prefix NS_SWIFT_NAME(hasCaseInsensitivePrefix(_:));

/// Strict check for http/s.
@property (readonly) BOOL pspdf_isHTTPFamilyURL NS_SWIFT_NAME(isHTTPFamily);

/// Strict check for mailto:
@property (readonly) BOOL pspdf_isMailURL NS_SWIFT_NAME(isMail);

@end

NS_ASSUME_NONNULL_END
