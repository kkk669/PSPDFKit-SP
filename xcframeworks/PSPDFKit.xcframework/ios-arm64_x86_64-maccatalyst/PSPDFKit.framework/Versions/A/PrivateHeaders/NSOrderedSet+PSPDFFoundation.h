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

@interface NSOrderedSet <ObjectType> (PSPDFAdditions)

/// Returns an ordered set from an array.
///
/// If `array` is nil, returns nil.
+ (nullable instancetype)pspdf_orderedSetWithArray:(nullable NSArray<ObjectType> *)array;

/// Returns a new set formed by removing the objects in a given set.
- (NSOrderedSet<ObjectType> *)pspdf_orderedSetByRemovingObjectsFromOrderedSet:(NSOrderedSet<ObjectType> *)other;

@end

@interface NSMutableOrderedSet <ObjectType> (PSPDFAdditions)

/// Version of addObject: accepting nil.
- (void)pspdf_addObject:(nullable ObjectType)anObject;

@end

NS_ASSUME_NONNULL_END
