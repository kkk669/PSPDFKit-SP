//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
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

/*
 * rdar://21290730
 *
 * [NSArray arrayWithArray:] now requires a nonnull argument. This was traditionally used a lot in situations where you either have nil or an array, to make sure there’s always an array. Granted, I don’t see that explicitly documented, but it’s something I see a lot in code. (Same behaviour with NSDictionary and NSSet)
 */

@interface NSArray <ObjectType> (PSPDFArrayCreation)

+ (instancetype)arrayWithArray:(nullable NSArray<ObjectType> *)array;

@end

@interface NSMutableArray <ObjectType> (PSPDFArrayCreation)

+ (instancetype)arrayWithArray:(nullable NSArray<ObjectType> *)array;

@end

@interface NSDictionary <KeyType, ObjectType> (PSPDFDictionaryCreation)

+ (instancetype)dictionaryWithDictionary:(nullable NSDictionary<KeyType, ObjectType> *)dict;

@end

@interface NSMutableDictionary <KeyType, ObjectType> (PSPDFDictionaryCreation)

+ (instancetype)dictionaryWithDictionary:(nullable NSDictionary<KeyType, ObjectType> *)dict;

@end

@interface NSSet <ObjectType> (PSPDFSetCreation)

- (instancetype)initWithSet:(nullable NSSet<ObjectType> *)set;
+ (instancetype)setWithSet:(nullable NSSet<ObjectType> *)set;
+ (instancetype)setWithArray:(nullable NSArray<ObjectType> *)array;

@end

@interface NSMutableSet <ObjectType> (PSPDFSetCreation)

- (instancetype)initWithSet:(nullable NSSet<ObjectType> *)set;
+ (instancetype)setWithSet:(nullable NSSet<ObjectType> *)set;
+ (instancetype)setWithArray:(nullable NSArray<ObjectType> *)array;

@end

@interface NSString (PSPDFStringCreation)

+ (instancetype)stringWithString:(nullable NSString *)string;

@end

@interface NSMutableString (PSPDFStringCreation)

+ (instancetype)stringWithString:(nullable NSString *)string;

@end

@interface NSOrderedSet <ObjectType> (PSPDFOrderedSetCreation)

+ (instancetype)orderedSetWithOrderedSet:(nullable NSOrderedSet<ObjectType> *)set;

@end

@interface NSMutableOrderedSet <ObjectType> (PSPDFOrderedSetCreation)

+ (instancetype)orderedSetWithOrderedSet:(nullable NSOrderedSet<ObjectType> *)set;

@end

NS_ASSUME_NONNULL_END
