//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationStyleManager.h>

@class PSPDFColorPreset, PSPDFBorderStylePreset;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDefaultAnnotationStyleManager (Defaults)

/// Sets the styles to default values.
- (void)setupDefaultStyles;

/// The default color presets for the given key.
- (NSArray<PSPDFColorPreset *> *)defaultColorPresetsForKey:(PSPDFAnnotationStateVariantID)key;

/// The default border presets for the given key.
- (NSArray<PSPDFBorderStylePreset *> *)defaultBorderPresetsForKey:(PSPDFAnnotationStateVariantID)key;

/// Default yellow color used for the highlighter tool.
+ (UIColor *)highlightYellow;

/// Default blue drawing color.
+ (UIColor *)drawingBlue;

@end

NS_ASSUME_NONNULL_END
