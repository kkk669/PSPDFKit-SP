//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFMeasurementAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

/// The base class for Ink, Rectangle, Circle, Line, Polygon and PolyLine annotations.
///
/// These annotations are created in the UI using `PSPDFDrawView`.
PSPDF_CLASS_SWIFT(AbstractShapeAnnotation)
@interface PSPDFAbstractShapeAnnotation : PSPDFAnnotation<PSPDFMeasurementAnnotation>

/// The annotation data in a format suitable for display in `PSPDFDrawView`.
///
/// Modifies the annotation content when set. The values should be boxed `PSPDFDrawingPoint` structs.
@property (atomic, strong) NSArray<NSArray<NSValue *> *> *pointSequences NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
