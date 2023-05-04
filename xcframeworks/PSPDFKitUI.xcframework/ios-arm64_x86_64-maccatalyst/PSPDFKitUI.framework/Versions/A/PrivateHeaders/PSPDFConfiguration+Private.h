//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFConfiguration.h>

#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFAnnotationStyleKey.h>

NS_ASSUME_NONNULL_BEGIN

/// An enum that describes how safe area insets are used during layout.
typedef NS_ENUM(NSInteger, PSPDFSafeAreaInsetsAdjustmentBehavior) {
    // Document layout will use the true `safeAreaInsets` of `PDFDocumentView`
    // directly without any modification.
    PSPDFSafeAreaInsetsAdjustmentBehaviorDirect,
    // Document layout will use the `customSafeAreaInsets` of `PDFDocumentView`.
    // This allows full control over the effective safe area insets from the
    // outside of `PDFViewController`.
    PSPDFSafeAreaInsetsAdjustmentBehaviorCustom,
    // Safe area insets will be managed entirely by `PDFViewController` to
    // include certain UI elements and exclude others.
    PSPDFSafeAreaInsetsAdjustmentBehaviorLegacy,
} NS_SWIFT_NAME(PDFConfiguration.SafeAreaInsetsAdjustmentBehavior);

@interface PSPDFConfiguration () <PSPDFOverrideProvider>

@property (nonatomic, copy, readonly) NSDictionary<Class, Class> *overrideClassNames;

/// Allows editing annotation replies. Defaults to YES.
@property (nonatomic, getter=isAnnotationRepliesEditingEnabled, readonly) BOOL annotationRepliesEditingEnabled;

/// Returns YES if we should be able to edit the provided annotations with our inspectors.
/// Based on the values in `self.propertiesForAnnotations`.
- (BOOL)hasPropertiesForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Resolves properties for the specified annotations from the provided `propertiesForAnnotations` dictionary.
+ (NSArray<NSArray<PSPDFAnnotationStyleKey> *> *)propertiesForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations dictionary:(NSDictionary<PSPDFAnnotationString, id> *)dictionary;

/// A boolean value that indicates whether accessibility elements are created
/// for text visible on PDF pages. PSPDFKit intelligently separates text into
/// paragraphs. Default: `true`.
@property (nonatomic, readonly, getter=isAccessibilityEnabledForText) BOOL accessibilityEnabledForText;

/// A boolean value that indicates whether accessibility elements are created
/// for annotations visible on PDF pages. Default: `true`.
@property (nonatomic, readonly, getter=isAccessibilityEnabledForAnnotations) BOOL accessibilityEnabledForAnnotations;

/// A value that describes how safe area insets are used during layout.
@property (nonatomic, readonly) PSPDFSafeAreaInsetsAdjustmentBehavior safeAreaInsetsAdjustmentBehavior;

@end

@interface PSPDFConfigurationBuilder ()

/// @see PSPDFConfiguration.annotationRepliesEditingEnabled.
@property (nonatomic, getter=isAnnotationRepliesEditingEnabled) BOOL annotationRepliesEditingEnabled;
/// @see PSPDFConfiguration.allValidEditableAnnotationTypes.
@property (nonatomic, class, readonly) NSSet<PSPDFAnnotationString> *allValidEditableAnnotationTypes;
/// @see PSPDFConfiguration.accessibilityEnabledForText.
@property (nonatomic, getter=isAccessibilityEnabledForText) BOOL accessibilityEnabledForText;
/// @see PSPDFConfiguration.accessibilityEnabledForAnnotations.
@property (nonatomic, getter=isAccessibilityEnabledForAnnotations) BOOL accessibilityEnabledForAnnotations;
/// @see PSPDFConfiguration.safeAreaInsetsAdjustmentBehavior.
@property (nonatomic) PSPDFSafeAreaInsetsAdjustmentBehavior safeAreaInsetsAdjustmentBehavior;

@end

NS_ASSUME_NONNULL_END
