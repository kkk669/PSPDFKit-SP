//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFTextMarkupAnnotation.h>

/// Text StrikeOut Annotation
///
/// @warning If you programmatically create a strikeout annotation, you need to both set the `boundingBox` AND the `rects` array. The rects array contains boxed variants of `CGRect` (`NSValue`).
PSPDF_CLASS_SWIFT(StrikeOutAnnotation)
@interface PSPDFStrikeOutAnnotation : PSPDFTextMarkupAnnotation<PSPDFOverridable>

@end
