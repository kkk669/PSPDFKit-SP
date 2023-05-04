//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// This is a private dummy annotation class created for the eraser tool.
///
/// Default radius of the eraser (`lineWidth`) is 15 points.
/// As the lineWidth UI can be disabled using `PSPDFConfiguration.propertiesForAnnotations`,
/// we need to have an eraser of a sufficient size.
PSPDF_SDK_EXPORT @interface PSPDFEraserAnnotation : PSPDFAnnotation<PSPDFOverridable>

@end

NS_ASSUME_NONNULL_END
