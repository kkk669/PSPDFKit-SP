//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//
//  Based on GitHub's Mantle project, MIT licensed.
//  Portions Copyright © 2011 Bitswift. BSD licensed.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Higher-order functions for `NSDictionary`.
@interface NSDictionary <KeyType, ObjectType> (PSPDFFoundation)

/// Converts the current dictionary into a case insensitive one.
///
/// @note When the dictionary is converted to Swift, it will no longer use be case insensitive. Keep this casted as NSDictionary if necessary.
@property (nonatomic, readonly) NSDictionary<NSString *, ObjectType> *pspdf_caseInsensitiveDictionary NS_SWIFT_NAME(caseInsensitive);

/// Inverts a dictionary. Duplicate values will result in a random value winning as key.
@property (nonatomic, readonly) NSDictionary<ObjectType, KeyType> *pspdf_invertedDictionary NS_SWIFT_NAME(inverted);

/// Filters the keys and values of the receiver with the given predicate,
/// returning a new dictionary built from those entries.
///
/// @param block A predicate block that determines whether to include or exclude
/// a given key-value pair.
- (NSDictionary<KeyType, ObjectType> *)pspdf_filteredEntries:(NS_NOESCAPE BOOL (^)(KeyType key, ObjectType value))block;

/// Reduces the receiver to a single value, using the given block.
///
/// If the receiver is empty, `startingValue` is returned. Otherwise, the
/// algorithm proceeds as follows:
///
///  1. `startingValue` is passed into the block as the `left` value, and the
///  first key and value of the receiver are passed into the block as `rightKey`
///  and `rightValue`, respectively.
///  2. The result of the previous invocation is passed into the block as the
///  `left` value, and the next key and value of the receiver are passed into the
///  block as `rightKey` and `rightValue`, respectively.
///  3. Step 2 is repeated until all elements have been processed.
///  4. The result of the last call to `block` is returned.
///
/// @param startingValue The value to be combined with the first entry of the
/// receiver. If the receiver is empty, this is the value returned.
/// @param block A block that describes how to combine elements of the receiver.
/// If the receiver is empty, this block will never be invoked.
///
/// @warning **Important:** Although this method is structured as a left fold,
/// the algorithm used for `block` must work irrespective of the order that the
/// dictionary's elements are processed, as dictionaries are unordered.
- (id)pspdf_foldEntriesWithValue:(id)startingValue usingBlock:(NS_NOESCAPE id (^)(id left, KeyType rightKey, ObjectType rightValue))block;

/// Transforms each value in the receiver with the given predicate, returning
/// a new dictionary built from the original keys and the transformed values.
///
/// @param block A block with which to transform each value. The key and original
/// value from the receiver are passed in as the arguments.
///
/// @warning **Important:** It is permissible to return `nil` from `block`, but
/// doing so will omit an entry from the resultant dictionary, such that the
/// number of objects in the result is less than the number of objects in the
/// receiver. If you need the dictionaries to match in size, return `NSNull`
/// instead of `nil`.
- (NSDictionary<KeyType, id> *)pspdf_mappedValues:(NS_NOESCAPE id _Nullable (^)(KeyType key, ObjectType value))block;

/// Lenient typed accessors

/// Looks for `NSString` then tries `stringValue`.
- (nullable NSString *)pspdf_stringForKey:(NSString *)key;

/// Looks for `NSNumber` then tries `NSString` with a number formatter.
- (nullable NSNumber *)pspdf_numberForKey:(NSString *)key;

/// Looks for `URL` then `NSString`.
- (nullable NSURL *)pspdf_URLForKey:(NSString *)key;

/// Looks for `NSArray`.
- (nullable NSArray *)pspdf_arrayForKey:(NSString *)key;

/// Looks for `NSDictionary`.
- (nullable NSDictionary *)pspdf_dictionaryForKey:(NSString *)key;

/// Looks for `NSNumber` then tries `NSString.boolValue`.
- (BOOL)pspdf_boolForKey:(NSString *)key;

/// Creates a dictionary from an URL query string.
+ (NSDictionary<NSString *, NSString *> *)pspdf_dictionaryWithQuery:(nullable NSString *)queryString;

@end

@interface NSMutableDictionary <KeyType, ObjectType> (PSPDFAdditions)

/// Checks if `otherDictionary` is non-null before forwarding.
///
/// Apple's method does this as well, but it's not declared that way.
- (void)pspdf_addEntriesFromDictionary:(nullable NSDictionary<KeyType, ObjectType> *)otherDictionary;

/// Remove all keys matching in `block`.
- (void)removeKeysMatching:(NS_NOESCAPE BOOL (^)(KeyType key))block;

@end

/// Merges two dictionaries. Always guarantees to at least return an empty dictionary, even if `first` and `second` are both nil. `second` might override entries in `first`.
///
/// @note Method is optimized to not create unnecessary objects if first or second is empty and might return a mutable subclass.
/// If both dictionaries contain the same key, the first dictionary’s previous value object for that key is sent a release message, and the new value of second takes its place.
PSPDF_TEST_EXPORT NSDictionary *PSPDFMergeDictionaries(NSDictionary *_Nullable first, NSDictionary *_Nullable second) NS_SWIFT_NAME(MergeDictionaries(_:_:));

/// Update dictionary with mutable block; returns immutable variant.
PSPDF_APP_EXPORT NSDictionary *PSPDFUpdateDictionary(NSDictionary *_Nullable dictionary, NS_NOESCAPE void (^updateBlock)(NSMutableDictionary *mutableDictionary)) NS_SWIFT_NAME(UpdateDictionary(_:_:));

/// Looks for `NSNumber` then tries `NSString.boolValue`.
/// Applies default if key does not exist.
PSPDF_APP_EXPORT BOOL PSPDFBOOLForKey(NSDictionary *_Nullable dictionary, NSString *_Nonnull key, BOOL defaultValue);

NS_ASSUME_NONNULL_END
