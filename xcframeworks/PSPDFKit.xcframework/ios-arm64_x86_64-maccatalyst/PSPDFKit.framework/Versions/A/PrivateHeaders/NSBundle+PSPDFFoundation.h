//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
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

@interface NSBundle (PSPDFFoundation)

/// The bundle containing our model level code, and the PSPDFKit resource bundle.
///
/// In general, this will be the `PSPDFKit.framework` bundle. For the customers that link us as a
/// static library into their own SDK,  this will be _their_ framework bundle.
@property (class, readonly) NSBundle *pspdf_modelBundle NS_SWIFT_NAME(modelBundle);

/// Bundle containing the PSPDFKitUI asset catalog.
@property (class, readonly, nullable) NSBundle *pspdf_UIBundle NS_SWIFT_NAME(uiBundle);

/// Calls through to `localizedStringForKey:value:table:` but returns `nil` if the key is not found.
- (nullable NSString *)pspdf_localizedStringForKey:(NSString *)key table:(nullable NSString *)tableName NS_FORMAT_ARGUMENT(1) NS_SWIFT_NAME(localizedString(forKey:table:));

@end

NS_ASSUME_NONNULL_END
