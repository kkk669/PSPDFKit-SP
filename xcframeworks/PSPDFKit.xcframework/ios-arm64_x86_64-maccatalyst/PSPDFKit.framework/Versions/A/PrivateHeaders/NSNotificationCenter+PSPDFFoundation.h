//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
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

@interface NSNotificationCenter (PSPDFFoundation)

/// Ensures a notification is posted on the main thread.
- (void)pspdf_postMainThreadNotification:(NSNotificationName)aName object:(nullable id)anObject;
- (void)pspdf_postMainThreadNotification:(NSNotificationName)aName object:(nullable id)anObject userInfo:(nullable NSDictionary *)aUserInfo;

/// Automatically deregisters notification when `observer` is deallocated.
/// `observer` is required.
- (id)pspdf_addObserver:(id)observer name:(NSNotificationName)notificationName usingBlock:(void (^)(id observer, NSNotification *notification))block;

/// Automatically deregisters notification when `observer` is deallocated.
/// `observer` is required.
///
/// Variant for multiple notification names, doesn't return.
- (void)pspdf_addObserver:(id)observer names:(NSArray<NSNotificationName> *)notificationNames usingBlock:(void (^)(id observer, NSNotification *notification))block;

/// Automatically deregisters notification when `observer` is deallocated.
/// `observer` is required.
- (id)pspdf_addObserver:(id)observer name:(nullable NSNotificationName)notificationName object:(nullable id)object queue:(nullable NSOperationQueue *)queue usingBlock:(void (^)(id observer, NSNotification *notification))block;

@end

NS_ASSUME_NONNULL_END
