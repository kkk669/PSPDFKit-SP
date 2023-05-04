//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFCacheStore.h>
#import <PSPDFKit/PSPDFMemoryCache.h>

@interface PSPDFMemoryCache () <PSPDFCacheStore>

/// The designated initializer.
/// Initializes the memory cache with the given settings.
///
/// This is the designated initializer.
///
/// @param settings The settings to use for the cache store.
- (instancetype)initWithSettings:(PSPDFKitGlobal *)settings NS_DESIGNATED_INITIALIZER;

@end
