//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFAnnotationStyleManager.h>

NS_ASSUME_NONNULL_BEGIN

/// Model class used to define custom border style presets.
///
/// @see `PSPDFStyleManager`
PSPDF_TEST_CLASS_SUBCLASSING_RESTRICTED_SWIFT(BorderStylePreset)
@interface PSPDFBorderStylePreset : PSPDFModel <PSPDFStylePreset>

/// Creates a `PSPDFAnnotationBorderStyleSolid` preset with no `dashArray`.
+ (PSPDFBorderStylePreset *)solidLinePresetWithName:(NSString *)name;

/// Creates a `PSPDFAnnotationBorderStyleDashed` preset.
+ (PSPDFBorderStylePreset *)presetWithDashArray:(nullable NSArray<NSNumber *> *)dashArray name:(NSString *)name;

/// Creates a `PSPDFAnnotationBorderEffectCloudy` preset.
///
/// @note The PDF Specification and the documentation for `PSPDFAnnotation.borderEffectIntensity`
/// recommend a value between 0 and 2 for the intensity.
+ (PSPDFBorderStylePreset *)cloudyEffectWithIntensity:(CGFloat)intensity name:(NSString *)name;

/// The preset name.
@property (nonatomic, readonly) NSString *name;

/// Annotation border style.
@property (nonatomic, readonly) PSPDFAnnotationBorderStyle borderStyle;

/// Array of boxed integer-values defining the dash style.
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *dashArray;

/// The border effect style.
@property (nonatomic, readonly) PSPDFAnnotationBorderEffect borderEffect;

/// The border effect intensity (if set to cloudy)
@property (nonatomic, readonly) CGFloat borderEffectIntensity;

/// Checks if the preset matches the annotation's border style.
- (BOOL)matchesAnnotation:(PSPDFAnnotation *)annotation;

/// Applies style to annotation. Does not emit a change notification.
- (void)applyToAnnotation:(PSPDFAnnotation *)annotation;

/// Returns a black and white template image that can be used as a button image for the preset.
- (UIImage *)symbolImageWithSize:(CGSize)size scale:(CGFloat)screenScale;

@end

NS_ASSUME_NONNULL_END
