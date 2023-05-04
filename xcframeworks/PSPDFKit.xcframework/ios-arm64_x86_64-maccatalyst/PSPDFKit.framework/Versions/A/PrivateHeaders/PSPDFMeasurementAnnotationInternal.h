//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractShapeAnnotation.h>
#import <PSPDFKit/PSPDFMeasurementAnnotation.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Annotations that have a measurement variant should privately conform to this protocol (as well as publicly to `PSPDFMeasurementAnnotation`).
@protocol PSPDFMeasurementAnnotationInternal<PSPDFMeasurementAnnotation>

/// Measurement label bounding box. If the annotation is a measurement annotation this will return the label bounding rectangle, otherwise `CGRectNull`.
///
/// @Note: conforming classes should use this to provide their custom bounding boxes for the measurement label.
@property (nonatomic, readonly) CGRect measurementLabelBoundingBox;

/// Measurement label size limit. If the annotation is a measurement annotation this will return the maximum size for the measurement label. Return `CGSizeZero` to allow any size.
///
/// @Note: conforming classes should use this to provide their custom size limits for measurement labels.
@property (nonatomic, readonly) CGSize measurementLabelSizeLimit;

/// Measurement label. If the annotation is a measurement annotation this will return the label displayed on the line.
/// @TODO: We might be able to remove this and rely on `contents` instead.
@property (nonatomic, nullable, readonly) NSString *measurementLabel;

/// Invalidates the measurement label.
- (void)invalidateMeasurementLabel;

/// Updates the measurement label based on the measurement info settings.
- (void)updateMeasurementLabel;

@end

/// Tries to cast the annotation to a measurement annotation. Returns nil for types that don’t conform to `PSPDFMeasurementAnnotationInternal`.
PSPDF_SDK_EXPORT PSPDFAbstractShapeAnnotation<PSPDFMeasurementAnnotationInternal> *_Nullable PSPDFMeasurementAnnotationCast(PSPDFAnnotation *_Nullable annotation);

NS_ASSUME_NONNULL_END
