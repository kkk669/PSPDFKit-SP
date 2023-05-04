//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
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

typedef NS_CLOSED_ENUM(NSInteger, PSPDFRectAlignment) {
    PSPDFRectAlignmentCenter = 0,
    PSPDFRectAlignmentTop,
    PSPDFRectAlignmentTopLeft,
    PSPDFRectAlignmentTopRight,
    PSPDFRectAlignmentLeft,
    PSPDFRectAlignmentBottom,
    PSPDFRectAlignmentBottomLeft,
    PSPDFRectAlignmentBottomRight,
    PSPDFRectAlignmentRight,
} PSPDF_ENUM_SWIFT(RectAlignment);
