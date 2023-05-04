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

@interface NSSet <ObjectType> (PSPDFFoundation)

/// Variant that accepts nullable.
+ (instancetype)pspdf_setWithSet:(nullable NSSet<ObjectType> *)set;

/// Variant that accepts nullable.
+ (instancetype)pspdf_setWithArray:(nullable NSArray<ObjectType> *)array;

/// Only allow objects of type `theClass` in the resulting set.
- (NSSet<ObjectType> *)pspdf_filterAllowingClass:(Class)theClass;

/// Waits for the first object to pass the test and returns it.
- (nullable ObjectType)pspdf_objectPassingTest:(BOOL (^)(ObjectType obj))predicate;

/// Add `object` to the set, if it isn't already part of the set. Always returns a new object.
- (NSSet<ObjectType> *)pspdf_setByAddingObject:(ObjectType)object;

/// Remove `object` from the set, if it is contained in the set. Always returns a new object.
- (NSSet<ObjectType> *)pspdf_setByRemovingObject:(ObjectType)object;

/// Returns a new set formed by removing the objects in a given set from the receiving set.
- (NSSet<ObjectType> *)pspdf_setByRemovingObjectsFromSet:(NSSet<ObjectType> *)other;

@end

@interface NSMutableSet <ObjectType> (PSPDFAdditions)

/// Version of addObject: accepting nil.
- (void)pspdf_addObject:(nullable ObjectType)anObject;

@end

NS_ASSUME_NONNULL_END
