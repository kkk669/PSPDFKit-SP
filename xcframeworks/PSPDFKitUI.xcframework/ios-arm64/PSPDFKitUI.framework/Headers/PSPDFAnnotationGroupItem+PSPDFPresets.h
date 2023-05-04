//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationGroupItem.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAnnotationGroupItem (PSPDFPresets)

/// Produces the default Ink annotation icon, which includes the currently set ink color and thickness.
///
/// Only supported for Ink annotation types.
///
/// @note The ink annotation image is loaded using `-[PSPDFKitGlobal imageNamed:]`, which means that you either need
/// to supply your own ink icon for that method, use a custom configuration block, or link to `PSPDFKitUI.framework`,
/// to obtain default bundled annotation toolbar icons.
+ (PSPDFAnnotationGroupItemConfigurationBlock)inkConfigurationBlock;

/// Produces the default Line annotation icon with support for arrow.
+ (PSPDFAnnotationGroupItemConfigurationBlock)lineConfigurationBlock;

/// Block to configure the `PSPDFAnnotationVariantStringFreeTextCallout` option of `PSPDFAnnotationStringFreeText`.
+ (PSPDFAnnotationGroupItemConfigurationBlock)freeTextConfigurationBlock;

/// Block to configure the `PSPDFAnnotationVariantStringPolygonCloud` option of `PSPDFAnnotationStringPolygon`.
+ (PSPDFAnnotationGroupItemConfigurationBlock)polygonConfigurationBlock;

/// Block to configure the measurement variants of `PSPDFAnnotationStringLine`, `PSPDFAnnotationStringPolyLine`, `PSPDFAnnotationStringPolygon`, `PSPDFAnnotationStringCircle` and `PSPDFAnnotationStringSquare`.
+ (PSPDFAnnotationGroupItemConfigurationBlock)measurementConfigurationBlock;

@end

NS_ASSUME_NONNULL_END
