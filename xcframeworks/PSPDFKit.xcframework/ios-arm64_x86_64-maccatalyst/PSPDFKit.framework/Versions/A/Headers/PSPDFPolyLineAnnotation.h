//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

/// Polyline annotations (PDF 1.5) are similar to polygons (`PSPDFPolygonAnnotation),
/// except that the first and last vertex are not implicitly connected.
///
/// @note See `PSPDFAbstractLineAnnotation` for details how to use and initialize.
PSPDF_CLASS_SWIFT(PolyLineAnnotation)
@interface PSPDFPolyLineAnnotation : PSPDFAbstractLineAnnotation<PSPDFOverridable>

@end
