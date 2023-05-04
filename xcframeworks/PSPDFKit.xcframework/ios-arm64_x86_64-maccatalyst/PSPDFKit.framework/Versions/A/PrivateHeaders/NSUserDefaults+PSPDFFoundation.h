//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
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

@interface NSUserDefaults (PSPDFFoundation)

/// Allows storage of arbitrary `NSCoding` compliant objects in `NSUserDefaults` as data objects.
///
/// @note With great power comes great responsibility. Limit this to small model objects.
/// Don't store complex object graphs in NSUserDefaults.
- (BOOL)pspdf_setCustomObject:(nullable id<NSSecureCoding>)object key:(NSString *)key error:(NSError *__autoreleasing *)error;

/// Retrieves an object previously stored using `pspdf_setCustomObject:key:`.
- (nullable id<NSSecureCoding>)pspdf_customObjectForKey:(NSString *)key ofClass:(Class)klass error:(NSError *__autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
