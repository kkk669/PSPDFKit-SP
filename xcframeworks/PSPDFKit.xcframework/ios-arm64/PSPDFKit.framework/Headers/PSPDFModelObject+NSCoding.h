//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//  Based on GitHub's Mantle project, MIT licensed.
//

#import <PSPDFKit/PSPDFModelObject.h>

NS_ASSUME_NONNULL_BEGIN

/// Use this macro to retrieve a value stored at self.preservedValues[key] if
/// maybeBackingStore does not exist.
///
/// @param key The key where the value is located.
/// @param maybeBackingStore Nullable object that can return the value for key.
/// @param type The expected type for the value on key.
/// @param valueFromBackingStore If maybeBackingStore exists, this will be returned and -preservedValues won't be queried.
#define PSPDF_UNWRAP_PRESERVED_VALUE(key, maybeBackingStore, type, valueFromBackingStore)   \
if (maybeBackingStore) {                                                                    \
    return valueFromBackingStore;                                                           \
}                                                                                           \
return PSPDFCast(self.preservedValues[key], type);                                          \

/// Use this macro to retrieve an NSInteger value stored at self.preservedValues[key] if
/// maybeBackingStore does not exist.
///
/// @param key The key where the value is located.
/// @param maybeBackingStore Nullable object that can return the value for key.
/// @param valueFromBackingStore If maybeBackingStore exists, this will be returned and -preservedValues won't be queried.
#define PSPDF_UNWRAP_PRESERVED_INT_VALUE(key, maybeBackingStore, valueFromBackingStore) \
if (maybeBackingStore) {                                                                \
    return valueFromBackingStore;                                                       \
}                                                                                       \
return PSPDFCast(self.preservedValues[key], NSNumber).integerValue;                     \

/// Use this macro to retrieve a BOOL value stored at self.preservedValues[key] if
/// maybeBackingStore does not exist.
///
/// @param key The key where the value is located.
/// @param maybeBackingStore Nullable object that can return the value for key.
/// @param valueFromBackingStore If maybeBackingStore exists, this will be returned and -preservedValues won't be queried.
#define PSPDF_UNWRAP_PRESERVED_BOOL_VALUE(key, maybeBackingStore, valueFromBackingStore)    \
if (maybeBackingStore) {                                                                    \
    return (valueFromBackingStore) != 0;                                                    \
}                                                                                           \
return PSPDFCast(self.preservedValues[key], NSNumber).boolValue;                            \

/// Defines how a PSPDFModel property key should be encoded into an archive.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFModelEncodingBehavior) {
    /// The property should never be encoded. Will also not be read when decoding because it wouldn’t
    /// be there except for old archives, and those migrations should be handled separately.
    PSPDFModelEncodingBehaviorExcluded = 0,

    /// The property should always be encoded.
    PSPDFModelEncodingBehaviorUnconditional,

    /// The object should be encoded only if unconditionally encoded elsewhere.
    PSPDFModelEncodingBehaviorConditional,

    /// The object should be encoded as pointer value and is post-processed manually.
    PSPDFModelEncodingBehaviorPointerValue
} PSPDF_ENUM_SWIFT(ModelObject.EncodingBehavior);

/// Implements default archiving and unarchiving behaviors for `PSPDFModel`.
@interface PSPDFModel (NSSecureCodingPrivate)

/// A dictionary mapping the underlying values to the keys specified in `+propertyKeysToPreserveWhenDecoding`.
@property (nonatomic, nullable) NSDictionary<NSString *, id> *preservedValues;

/// Initializes the receiver from an archive.
///
/// This will decode the original +modelVersion of the archived object, then
/// invoke `-decodeValueForKey:withCoder:modelVersion:` for each of the receiver's
/// `+propertyKeys`.
///
/// Returns an initialized model object, or nil if a decoding error occurred.
- (nullable instancetype)initWithCoder:(NSCoder *)coder;

/// Archives the receiver using the given coder.
///
/// This will encode the receiver's +modelVersion, then the receiver's properties
/// according to the behaviors specified in +encodingBehaviorsByPropertyKey.
- (void)encodeWithCoder:(NSCoder *)coder;

/// Defines the keys in `propertyKeys` that should be preserved internally in the `-preservedValues`.
///
/// This is useful when decoding models that have properties that are mappings to properties on other
/// objects, or that are computed dynamically. These properties might produce a valid value when encoding
/// them, but when decoding them, often there would be no underlying model to store them (in the case of
/// form fields, for instance, where the actual values are mapped to Core objects).
///
/// Getters for the properties contained in this Set should be handled in a special way to see whether the
/// underlying model exists to retrieve the value, or the `preservedValues` dictionary should be used.
///
/// You can use the PSPDF_UNWRAP_PRESERVED_VALUE() macro to help with this.
@property (nonatomic, class, readonly) NSSet<NSString *> *propertyKeysToPreserveWhenDecoding;

/// Determines how the `+propertyKeys` of the class are encoded into an archive.
/// The values of this dictionary should be boxed `PSPDFModelEncodingBehavior`
/// values.
///
/// Any keys not present in the dictionary will be excluded from the archive.
///
/// Subclasses overriding this method should combine their values with those of
/// `super`.
///
/// Returns a dictionary mapping the receiver's +propertyKeys to default encoding
/// behaviors. If a property is an object with `weak` semantics, the default
/// behavior is `PSPDFModelEncodingBehaviorConditional`; otherwise, the default is
/// `PSPDFModelEncodingBehaviorUnconditional`.
@property (nonatomic, class, readonly) NSDictionary<NSString *, NSNumber *> *encodingBehaviorsByPropertyKey;

/// Determines the classes that are allowed to be decoded for each of the
/// receiver's properties when using <NSSecureCoding>. The values of this
/// dictionary should be NSSets of Class objects.
///
/// If any encodable keys (as determined by `+encodingBehaviorsByPropertyKey`) are
/// not present in the dictionary, an exception will be thrown during secure
/// encoding or decoding.
///
/// Subclasses overriding this method should combine their values with those of
/// `super`.
///
/// Returns a dictionary mapping the receiver's encodable keys (as determined by
/// `+encodingBehaviorsByPropertyKey`) to default allowed classes, based on the
/// type that each property is declared as. If type of an encodable property
/// cannot be determined (e.g., it is declared as `id`), it will be omitted from
/// the dictionary, and subclasses must provide a valid value to prevent an
/// exception being thrown during encoding/decoding.
@property (nonatomic, class, readonly) NSDictionary<NSString *, NSSet<Class> *> *allowedSecureCodingClassesByPropertyKey;

/// Decodes the value of the given property key from an archive.
///
/// By default, this method looks for a `-decode<Key>WithCoder:modelVersion:`
/// method on the receiver, and invokes it if found.
///
/// If the custom method is not implemented and `coder` does not require secure
/// coding, `-[NSCoder decodeObjectForKey:]` will be invoked with the given
/// `key`.
///
/// If the custom method is not implemented and `coder` requires secure coding,
/// `-[NSCoder decodeObjectOfClasses:forKey:]` will be invoked with the
/// information from +allowedSecureCodingClassesByPropertyKey and the given `key`. The
/// receiver must conform to <NSSecureCoding> for this to work correctly.
///
/// key          - The property key to decode the value for. This argument cannot
/// be nil.
/// coder        - The NSCoder representing the archive being decoded. This
/// argument cannot be nil.
// modelVersion - The version of the original model object that was encoded.
/// Returns the decoded and boxed value, or nil if the key was not present.
- (nullable id)decodeValueForKey:(NSString *)key withCoder:(NSCoder *)coder modelVersion:(NSUInteger)modelVersion;

/// Override this to decode and return additional values (maybe to migrate from older model versions).
/// These will be merged and also used to initialize the object.
/// The default implementation will return nil.
/// Subclasses of subclasses of `PSPDFModel` should make they combine their additional values with those from the superclass.
- (nullable NSDictionary<NSString *, id> *)decodeAdditionalValues:(NSCoder *)coder model:(NSUInteger)model;

/// The version of this PSPDFModel subclass.
///
/// This version number is saved in archives so that later model changes can be
/// made backwards-compatible with old versions.
///
/// Subclasses should override this method to return a higher version number
/// whenever a breaking change is made to the model.
///
/// Returns 0.
@property (nonatomic, class, readonly) NSUInteger modelVersion;

@end

NS_ASSUME_NONNULL_END
