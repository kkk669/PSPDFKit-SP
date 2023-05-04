//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

//
//  Based on GitHub's Mantle project, MIT licensed. See ACKNOWLEDGEMENTS for details.
//

#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFEnvironment.h>

/// Enable this flag to log a list of the keys that prevented two `PSPDFModel` instances
/// from returning `true` from `-isEqual:`.
#define PSPDF_ENABLE_MODEL_EQUALITY_DEBUG 0

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFModel ()

/// Cached variant. Do not subclass.
@property (nonatomic, class, readonly) NSArray<NSString *> *cachedPropertyKeys;

/// Returns an opaque object for `dictionaryWithSharedKeySet:`.
+ (id)cachedPropertyKeySet;

/// Returns the property keys that should be compared using pointers rather than
/// structurally. This is designed to be overwritten in subclasses, the default
/// implementation here returns an empty set.
@property (nonatomic, class, readonly) NSOrderedSet<NSString *> *propertyKeysWithReferentialEquality;

/// A set of keys from `propertyKeys` that are excluded from hash calculation.
/// This can be used to avoid accessing expensive computed properties during
/// potentially very frequent hash function calculations.
@property (nonatomic, nullable, class, readonly) NSSet<NSString *> *skipKeysForHashing;

/// A set of keys from `propertyKeys` that are excluded from equality calculation (-isEqual:).
///
/// This can be used for cases in which the objects is loaded from an archive and
/// some of its properties cannot be encoded or decoded.
@property (nonatomic, nullable, class, readonly) NSSet<NSString *> *skipKeysForEquality;

// Dynamically discovers all properties that the class has.
// @note This method is thread-safe.
@property (nonatomic, class, readonly) NSOrderedSet<NSString *> *discoveredPropertyKeys;

// Copies the values of all properties from the source to the target.
- (void)transferValuesFrom:(id)source to:(id)target;

/// Called before we restore a model from a dictionary.
- (void)willLoadModelFromDictionary NS_REQUIRES_SUPER;

/// Called after we restored a model from a dictionary.
- (void)didLoadModelFromDictionary NS_REQUIRES_SUPER;

/// Merges the value of the given key on the receiver with the value of the same
/// key from the given model object, giving precedence to the other model object.
///
/// By default, this method looks for a `-merge<Key>FromModel:` method on the
/// receiver, and invokes it if found. If not found, and `model` is not nil, the
/// value for the given key is taken from `model`.
- (void)mergeValueForKey:(NSString *)key fromModel:(PSPDFModel *)model;

/// Merges the values of the given model object into the receiver, using
/// -mergeValueForKey:fromModel: for each key in +propertyKeys.
///
/// `model` must be an instance of the receiver's class or a subclass thereof.
- (void)mergeValuesForKeysFromModel:(PSPDFModel *)model;

@end

/// Implements validation logic for PSPDFModel.
@interface PSPDFModel (Validation)

/// Validates the model.
///
/// The default implementation simply invokes -validateValue:forKey:error: with
/// all +propertyKeys and their current value. If -validateValue:forKey:error:
/// returns a new value, the property is set to that new value.
///
/// error - If not NULL, this may be set to any error that occurs during
/// validation
///
/// Returns YES if the model is valid, or NO if the validation failed.
- (BOOL)validate:(NSError * __autoreleasing _Nullable *)error;

@end

@interface PSPDFModel (PSPDFBehaviorCache)

/// Cached variants. Faster.
@property (nonatomic, class, readonly) NSDictionary<NSString *, NSNumber *> *cachedEncodingBehaviorsByPropertyKey;
@property (nonatomic, class, readonly) NSSet<NSString *> *cachedEncodablePropertyKeys;
@property (nonatomic, class, readonly) NSSet<NSString *> *cachedPropertyKeysToPreserveWhenDecoding;

@end

NS_ASSUME_NONNULL_END
