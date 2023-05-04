//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationGroupItem.h>
#import <PSPDFKit/PSPDFAnnotationStyle.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Protocol adopted by `PSPDFColorPreset` and `PSPDFBorderStylePreset`.
@protocol PSPDFStylePreset <NSObject, NSSecureCoding>
@end

typedef NSString *PSPDFAnnotationStyleType NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(AnnotationStyle.Kind);

/// This key will return the last used style.
PSPDF_EXPORT PSPDFAnnotationStyleType const PSPDFAnnotationStyleTypeLastUsed;

/// This key will mark styles as generic, thus they'll be returned
/// with all other style types except the last used trait.
PSPDF_EXPORT PSPDFAnnotationStyleType const PSPDFAnnotationStyleTypeGeneric;

/// Color preset type
PSPDF_EXPORT PSPDFAnnotationStyleType const PSPDFAnnotationStyleTypeColorPreset;

/// The annotation style manager will save UI-specific properties for annotations
/// and apply them after creation.
///
/// It also offers a selection of user-defined styles.
/// There are three categories: Last used, key-specific and generic styles.
PSPDF_PROTOCOL_SWIFT(AnnotationStyleManager)
@protocol PSPDFAnnotationStyleManager

// MARK: Styles

/// When annotations are changed and this is enabled, the defaults are updated accordingly.
/// This defaults to YES.
@property (nonatomic) BOOL shouldUpdateDefaultsForAnnotationChanges;

/// Set default annotation styles.
/// This is the perfect place to set your own default annotation styles.
- (void)setupDefaultStylesIfNeeded;

/// Keeps a list of style keys we want to listen to (like `color` or `lineWidth`).
///
/// @note If you want to disable automatic style saving, set this to nil.
@property (atomic, copy, nullable) NSSet<NSString *> *styleKeys;

/// Returns the annotation styles, for the given key.
/// Might return nil if there isn't anything saved yet.
- (nullable NSArray<PSPDFAnnotationStyle *> *)stylesForKey:(PSPDFAnnotationStateVariantID)key;

/// Adds a style on the key store.
- (void)addStyle:(PSPDFAnnotationStyle *)style forKey:(PSPDFAnnotationStateVariantID)key;

/// Removes a style from the key store.
- (void)removeStyle:(PSPDFAnnotationStyle *)style forKey:(PSPDFAnnotationStateVariantID)key;

// MARK: Last used style convenience helpers

/// Get the last used style for `key`. Uses `PSPDFAnnotationStyleTypeLastUsed` and calls `stylesForKey:`.
- (nullable PSPDFAnnotationStyle *)lastUsedStyleForKey:(PSPDFAnnotationStateVariantID)key;

/// Convenience method. Will fetch the last used style for `key` and fetches the `styleProperty` for it. Might return nil.
- (nullable id)lastUsedProperty:(NSString *)styleProperty forKey:(PSPDFAnnotationStateVariantID)key;

/// Convenience method. Will set the last used style for `key` and `styleProperty`.
/// `value` might be a boxed CGFloat, color or whatever matches the property.
/// `styleProperty` is the NSString-name for the property (e.g. `NSStringFromSelector(@ selector(fontSize))`
/// `key` is a annotation string, e.g. PSPDFAnnotationStringFreeText.
/// Uses `PSPDFAnnotationStyleTypeLastUsed` and calls `addStyle:forKey`.
- (void)setLastUsedValue:(nullable id)value forProperty:(NSString *)styleProperty forKey:(PSPDFAnnotationStateVariantID)key;

// MARK: Presets

/// Returns default presets for a given `key` and `type`. Either presets set via `setDefaultPresets:forKey:type:`,
/// or suitable internal defaults.
///
/// @see presetsForKey:type:
/// @note The implementation should be thread safe.
- (nullable NSArray<id<PSPDFStylePreset>> *)defaultPresetsForKey:(PSPDFAnnotationStateVariantID)key type:(PSPDFAnnotationStyleType)type;

/// Sets default presets for a given `key` and `type`. The set default presets should be stored in memory only
/// and set on every app restart.
///
/// @see setPresets:forKey:type:
/// @note The implementation should be thread safe.
- (void)setDefaultPresets:(nullable NSArray<id<PSPDFStylePreset>> *)presets forKey:(PSPDFAnnotationStateVariantID)key type:(PSPDFAnnotationStyleType)type;

/// Get the color presets for a specified key and preset type. Returns the set presets or appropriate default presets
/// if no custom presets were set.
/// Returns an array of objects corresponding to the preset type (e.g, `PSPDFColorPreset`).
///
/// @property key The annotation string, e.g. PSPDFAnnotationStringFreeText.
/// @property type The preset type, e.g. PSPDFAnnotationStyleTypeColorPreset (see PSPDFAnnotationStyleManager.h).
- (nullable NSArray<id<PSPDFStylePreset>> *)presetsForKey:(PSPDFAnnotationStateVariantID)key type:(PSPDFAnnotationStyleType)type;

/// Updates the presets for the specified key and preset type.
///
/// @property presets An array of presets to save. They object must conform to `NSSecureCoding`. Setting nil removes the presets from storage and reverts to the default presets (if set).
/// @property key The annotation string, e.g. PSPDFAnnotationStringFreeText.
/// @property type The preset type, e.g. PSPDFAnnotationStyleTypeColorPreset (see PSPDFAnnotationStyleManager.h).
- (void)setPresets:(nullable NSArray<id<PSPDFStylePreset>> *)presets forKey:(PSPDFAnnotationStateVariantID)key type:(PSPDFAnnotationStyleType)type;

/// Checks if the preset at the given index differs from its default value.
///
/// @property presets Index of preset in the preset array.
/// @property key The annotation string, e.g. PSPDFAnnotationStringFreeText.
/// @property type The preset type, e.g. PSPDFAnnotationStyleTypeColorPreset (see PSPDFAnnotationStyleManager.h).
- (BOOL)isPresetModifiedAtIndex:(NSUInteger)index forKey:(PSPDFAnnotationStateVariantID)key type:(PSPDFAnnotationStyleType)type;

/// Resets the preset at the given index to its default value.
///
/// @property presets Index of preset in the preset array.
/// @property key The annotation string, e.g. PSPDFAnnotationStringFreeText.
/// @property type The preset type, e.g. PSPDFAnnotationStyleTypeColorPreset (see PSPDFAnnotationStyleManager.h).
- (BOOL)resetPresetAtIndex:(NSUInteger)idx forKey:(PSPDFAnnotationStateVariantID)key type:(PSPDFAnnotationStyleType)type;

@end

/// The default implementation for the style manager.
PSPDF_CLASS_SWIFT(PDFDefaultAnnotationStyleManager)
@interface PSPDFDefaultAnnotationStyleManager : NSObject<PSPDFAnnotationStyleManager>
@end

NS_ASSUME_NONNULL_END
