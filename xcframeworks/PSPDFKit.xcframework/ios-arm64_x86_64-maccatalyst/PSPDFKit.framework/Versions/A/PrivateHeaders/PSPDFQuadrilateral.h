//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

/// Could be any quadrilateral but is usually used only for rotated rectangles. Used for the quadrilaterals property of `PSPDFAnnotation`.
typedef struct __attribute__((objc_boxable)) { CGPoint topLeft, topRight, bottomLeft, bottomRight; } PSPDFQuadrilateral;

PSPDF_EXPORT const PSPDFQuadrilateral PSPDFQuadrilateralZero;

PSPDF_EXPORT PSPDFQuadrilateral PSPDFQuadrilateralFromRect(CGRect rect);

PSPDF_EXPORT CGRect PSPDFQuadrilateralGetEnclosingRect(PSPDFQuadrilateral quadrilateral);

PSPDF_EXPORT PSPDFQuadrilateral PSPDFQuadrilateralApplyTransform(PSPDFQuadrilateral quadrilateral, CGAffineTransform transform);

/// Not recommended for new code. This function was kept around without modification because it was used in one place.
PSPDF_EXPORT PSPDFQuadrilateral PSPDFQuadrilateralApplyTransformToRect(CGAffineTransform transform, CGRect rect);

PSPDF_EXPORT BOOL PSPDFQuadrilateralEqualToQuadrilateral(PSPDFQuadrilateral quad1, PSPDFQuadrilateral quad2);

@interface NSValue (PSPDFQuadrilateral)

@property (nonatomic, readonly) PSPDFQuadrilateral pspdf_quadrilateralValue;

@end
