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

PSPDF_PROTOCOL_SWIFT(Hook)
@protocol PSPDFHook <NSObject, NSCopying>

/// Deregisters a hook.
///
/// @return YES if deregistration is successful, otherwise NO.
- (BOOL)remove;

/// Exposes the block registered with the hook.
@property (nonatomic, readonly) id block;

@end

@interface NSObject (PSPDFHooks)

/* May be used to hook an object method.

 @note The `forwarder` should swizzle the selector and also run the hooks.
 To not introduce even more magic (and NSInvocation drama) we need to call the block explicitely.

 id aspectToken = [testClass pspdf_hookSelector:selector usingBlock:^{
   testCallCalled = YES;
 } forwarder:^(Class clazz) {
   __block IMP originalIMP = pspdf_swizzleSelectorWithBlock(clazz, selector, ^(id _self) {
     ((void (*)(id, SEL))originalIMP)(_self, selector);

     // Call saved block(s).
     for (id <PSPDFHook> hook in [_self pspdf_hooksForSelector:selector]) {
       ((void (^)(id))hook.block)(_self);
     }
   });
 }];
 */
- (id<PSPDFHook>)pspdf_hookSelector:(SEL)selector usingBlock:(nullable id)block forwarder:(void (^)(Class clazz))forwarderBlock NS_SWIFT_NAME(hook(selector:usingBlock:forwarder:));

// Returns all saved hooks for `selector`.
- (NSArray<PSPDFHook> *)pspdf_hooksForSelector:(SEL)selector NS_SWIFT_NAME(hooks(selector:));

@end

NS_ASSUME_NONNULL_END
