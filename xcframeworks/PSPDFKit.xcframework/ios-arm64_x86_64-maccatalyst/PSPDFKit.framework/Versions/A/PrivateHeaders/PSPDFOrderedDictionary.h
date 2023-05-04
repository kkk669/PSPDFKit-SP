//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
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

/// Ordered dictionary, otherwise similar to NSMutableDictionary.
PSPDF_SDK_CLASS_SWIFT(OrderedDictionary)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFOrderedDictionary<KeyType, ObjectType> : NSMutableDictionary<KeyType, ObjectType>

/// Sorts the keys using the specified selector.
/// Naturally, instances of `KeyType` must respond to `comparator` and calling this method concurrently to doing basically anything else with the receiver causes nasal demons.
- (void)sortKeysUsingSelector:(SEL)comparator;

/// Insert key for object at index.
- (void)insertObject:(ObjectType)anObject forKey:(KeyType)aKey atIndex:(NSUInteger)index;

/// Stores anObject under the key `aKey`.
/// Iff the receiver did not have an entry for `aKey` before, a copy is appended to the list of existing keys.
/// This guarantees that for all entries in `allKeys`, `objectForKey:` returns nonnull.
- (void)setObject:(ObjectType)anObject forKey:(KeyType<NSCopying>)aKey;

/// Get key at index.
- (KeyType)keyAtIndex:(NSUInteger)index;

/// Get object at index.
- (ObjectType)objectAtIndex:(NSUInteger)index;

/// Removes the key and object at index. If the index is already known, this will be faster than `removeObjectForKey:`
- (void)removeKeyAndObjectAtIndex:(NSUInteger)index;

/// Reverse object enumerator.
@property (nonatomic, readonly) NSEnumerator<KeyType> *reverseKeyEnumerator;

@end

@interface PSPDFOrderedDictionary <KeyType, ObjectType> (ExtendedOrderedDictionary)
<NSFastEnumeration>

    /// Type clarification for the key in NSFastEnumeration.
    - (NSUInteger)countByEnumeratingWithState : (nonnull NSFastEnumerationState *)state objects : (__unsafe_unretained KeyType _Nonnull *_Nonnull)buffer count : (NSUInteger)len;

/// Support array-like subscripting, returning the object, not the key — use `keyAtIndex:` for that.
- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx;

@end

NS_ASSUME_NONNULL_END
