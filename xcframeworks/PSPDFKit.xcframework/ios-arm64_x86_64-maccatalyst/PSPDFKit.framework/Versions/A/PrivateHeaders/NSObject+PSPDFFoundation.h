//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
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

@interface NSObject (PSPDFFoundation)

/// Register block to be called when the receiver is deallocated.
///
/// @param block The block to be called up on deallocation of the receiver.
/// @param owner An optional owner. If the owner is deallocated before the receiver,
/// the block is removed from the receiver. In this case the block is
/// not called.
/// @return A token that can be used to remove the block by calling `pspdf_removeDeallocBlock:`
- (NSString *)pspdf_addDeallocBlock:(void (^)(void))block owner:(nullable id)owner;

/// Remove block registered for `uid`. Returns YES if a block was found.
- (BOOL)pspdf_removeDeallocBlock:(NSString *)uid;

/// This enqueues the block to be dispatched during the next run loop cycle on the main queue. Can
/// be useful for working around various UIKit bugs.
- (void)pspdf_performBlockAfterRunLoopCycle:(void (^)(void))block;

/// Binds `object` to the lifetime of `self`.
- (void)pspdf_bindObjectToLifeTime:(id)object NS_SWIFT_NAME(bind(to:));

/// Exception-safe KVC getter. Useful for accessing private API.
/// Since exceptions cannot be captured in Swift, this always has to be in ObjC.
- (nullable id)pspdf_safeValueForKey:(NSString *)key NS_SWIFT_NAME(safeValue(forKey:));

/// Exception-safe KVC getter. Useful for accessing private API.
/// Since exceptions cannot be captured in Swift, this always has to be in ObjC.
- (nullable id)pspdf_safeValueForKeyPath:(NSString *)key NS_SWIFT_NAME(safeValue(forKeyPath:));

/// Exception-safe KVC setter. Useful for accessing private API.
/// Since exceptions cannot be captured in Swift, this always has to be in ObjC.
- (void)pspdf_safeSetValue:(nullable id)value forKey:(NSString *)key NS_SWIFT_NAME(safeSetValue(_:forKey:));

@end

@interface NSObject (PSPDFWeakAssociation)

/// Uses associated objects to bind `object` to `self`.
/// Unlike `objc_setAssociatedObject` this will be truly weak and safe.
- (void)pspdf_setWeakAssociatedObject:(nullable id)object forKey:(const void *)key;
- (nullable id)pspdf_weakAssociatedObjectForKey:(const void *)key;

@end

/// Calls the property setter explicitly on the main thread with a `nil` argument
/// when the weak instance variable backing the property is nilled out.
///
/// @note Needs to be placed inside an overridden setter for a weak property.
/// @warning The setter's selector must *not* be used as the key for any associated
/// object storage outside of this macro.
///
/// @param property The property that should be called.
/// @param previousObject The previous value (stored object) of the property.
/// @param newObject The newly set object.
///
/// @discussion Only re-sets the adornment source to `nil` if it already is `nil`.
/// This is the case when the property as been zeroed by the weak reference.
/// If the property has already been set to something else, we have called the
/// setter anyways, so no need to call it again.
#define PSPDFInvokeSetterOnWeakDeallocation(property, previousObject, newObject) \
    do {                                                                         \
        NSString *uuid = objc_getAssociatedObject(self, _cmd);                   \
        if (uuid) {                                                              \
            [(NSObject *)previousObject pspdf_removeDeallocBlock:uuid];          \
        }                                                                        \
        weakify(self);                                                           \
        uuid = [(NSObject *)newObject pspdf_addDeallocBlock:^{                   \
            strongify(self);                                                     \
            [PSPDFDispatchQueue.mainQueue asyncIfNotOnQueue:^{                                         \
                if (!self.property) {                                            \
                    self.property = nil;                                         \
                }                                                                \
            }];                                                                  \
        } owner:self];                                                           \
        objc_setAssociatedObject(self, _cmd, uuid, OBJC_ASSOCIATION_COPY);       \
    } while (0)

NS_ASSUME_NONNULL_END
