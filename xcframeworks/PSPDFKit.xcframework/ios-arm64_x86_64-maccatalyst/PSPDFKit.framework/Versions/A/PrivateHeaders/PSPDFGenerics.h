//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

/// This file overrides the NSObject declaration of copy with specialized ones that retain the generic type.
/// This is pure compiler sugar and will create additional warnings for type mismatches.
///
/// @note id-casted objects will create a warning when copy is called on them as there are multiple
/// declarations available. Either cast to specific type or to NSObject to work around this.
@interface NSArray <ElementType> (PSPDFSafeCopy)

/// Same as `copy` but retains the generic type.
- (NSArray <ElementType> *)copy;

/// Same as `mutableCopy` but retains the generic type.
- (NSMutableArray <ElementType> *)mutableCopy;

@end

@interface NSSet <ElementType> (PSPDFSafeCopy)

/// Same as `copy` but retains the generic type.
- (NSSet <ElementType> *)copy;

/// Same as `mutableCopy` but retains the generic type.
- (NSMutableSet <ElementType> *)mutableCopy;

@end

@interface NSDictionary <KeyType, ValueType> (PSPDFSafeCopy)

/// Same as `copy` but retains the generic type.
- (NSDictionary <KeyType, ValueType> *)copy;

/// Same as `mutableCopy` but retains the generic type.
- (NSMutableDictionary <KeyType, ValueType> *)mutableCopy;

@end

@interface NSOrderedSet <ElementType> (PSPDFSafeCopy)

/// Same as `copy` but retains the generic type.
- (NSOrderedSet <ElementType> *)copy;

/// Same as `mutableCopy` but retains the generic type.
- (NSMutableOrderedSet <ElementType> *)mutableCopy;

@end

@interface NSHashTable <ElementType> (PSPDFSafeCopy)

/// Same as `copy` but retains the generic type.
- (NSHashTable <ElementType> *)copy;

@end

@interface NSMapTable <KeyType, ValueType> (PSPDFSafeCopy)

/// Same as `copy` but retains the generic type.
- (NSMapTable <KeyType, ValueType> *)copy;

@end

