//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFMeasurementModels.h>

NS_ASSUME_NONNULL_BEGIN

/// Annotations that have a measurement variant (ex. `LineAnnotation`) implement this protocol. Use `isMeasurement` to determine if the annotation really is a measurement.
PSPDF_PROTOCOL_SWIFT(MeasurementAnnotation)
@protocol PSPDFMeasurementAnnotation

/// Returns `true` if the annotation is a measurement annotation.
///
/// Use of `isMeasurement` requires `Features.measurementTools`.
/// If your license key does not include this feature, reading `isMeasurement` always returns `false`.
@property (nonatomic, readonly) BOOL isMeasurement;

/// Returns the measurement info object containing the measurement scale and measurement precision if the annotation is a measurement annotation.
///
/// Use of `measurementInfo` requires `Features.measurementTools`.
/// If your license key does not include this feature, reading `measurementInfo` always returns `nil`.
///
/// Attempting to set a new value will do nothing except logging a warning.
@property (nonatomic, nullable, readonly) PSPDFMeasurementInfo *measurementInfo;

@end

NS_ASSUME_NONNULL_END
