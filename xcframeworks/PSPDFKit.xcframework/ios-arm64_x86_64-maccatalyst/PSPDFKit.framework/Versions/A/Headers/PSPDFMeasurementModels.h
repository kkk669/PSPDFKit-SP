//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <PSPDFKit/PSPDFMacros.h>
#import <PSPDFKit/PSPDFModelObject.h>

NS_ASSUME_NONNULL_BEGIN

/// The number of decimal places displayed for a measurement.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFMeasurementPrecision) {
    /// Display no decimal places. For example: 3.
    PSPDFMeasurementPrecisionWhole,
    /// Display one decimal place. For example: 3.1.
    PSPDFMeasurementPrecisionOneDecimalPlace,
    /// Display two decimal places. For example: 3.14.
    PSPDFMeasurementPrecisionTwoDecimalPlaces,
    /// Display three decimal places. For example: 3.142.
    PSPDFMeasurementPrecisionThreeDecimalPlaces,
    /// Display four decimal places. For example: 3.1416.
    PSPDFMeasurementPrecisionFourDecimalPlaces,
} PSPDF_ENUM_SWIFT(MeasurementPrecision);

/// The type of measurement of a given `MeasurementInfo` type.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFMeasurementMode) {
    /// Distance measurement
    PSPDFMeasurementModeDistance,
    /// Perimeter measurement. This is the total length of a path through multiple connected points. In general, this path doesn’t form a closed shape.
    PSPDFMeasurementModePerimeter,
    /// Area measurement
    PSPDFMeasurementModeArea,
} PSPDF_ENUM_SWIFT(MeasurementMode);

/// Possible units for distances on a document page. These are used with the `from` value in a `MeasurementScale` object.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFUnitFrom) {
    /// Inches (default). 1 inch is 72 PDF points.
    PSPDFUnitFromInch,
    /// Millimeters
    PSPDFUnitFromMillimeter,
    /// Centimeters
    PSPDFUnitFromCentimeter,
    /// PDF points. A PDF point is 1/72 inch. All values in a PDF page coordinate space (e.g. an annotation’s bounding box) are specified in PDF points.
    PSPDFUnitFromPoint,
} PSPDF_ENUM_SWIFT(UnitFrom);

/// Possible units for real world distances. These are used with the `to` value in a `MeasurementScale` object.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFUnitTo) {
    /// Inches (default)
    PSPDFUnitToInch,
    /// Millimeters
    PSPDFUnitToMillimeter,
    /// Centimeters
    PSPDFUnitToCentimeter,
    /// PDF points. You probably don’t want to use this for real world distances.
    PSPDFUnitToPoint PSPDF_DEPRECATED(12, "Use a different unit for real world distances instead."),
    /// Feet
    PSPDFUnitToFoot,
    /// Meters
    PSPDFUnitToMeter,
    /// Yards
    PSPDFUnitToYard,
    /// Kilometers
    PSPDFUnitToKilometer,
    /// Miles
    PSPDFUnitToMile,
} PSPDF_ENUM_SWIFT(UnitTo);

/// A ratio of a distance on a document page to a corresponding real world distance.
PSPDF_CLASS_SWIFT(MeasurementScale)
@interface PSPDFMeasurementScale: PSPDFModel

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates a `MeasurementScale` object.
///
/// @param from A distance on a document page. The unit of this value is given by `unitFrom`.
/// @param unitFrom  The unit for the distance on a document page.
/// @param to A real world distance. The unit of this value is given by `unitTo`.
/// @param unitTo The unit for the real world distance.
- (instancetype)initWithFrom:(double)from unitFrom:(PSPDFUnitFrom)unitFrom to:(double)to unitTo:(PSPDFUnitTo)unitTo NS_DESIGNATED_INITIALIZER;

/// A distance on a document page. The unit of this value is given by `unitFrom`.
@property (nonatomic, readonly) double from;

/// The unit for the distance on a document page.
@property (nonatomic, readonly) PSPDFUnitFrom unitFrom;

/// A real world distance. The unit of this value is given by `unitTo`.
@property (nonatomic, readonly) double to;

/// The unit for the real world distance.
@property (nonatomic, readonly) PSPDFUnitTo unitTo;

@end

/// A known real world distance used for calibration to obtain a `MeasurementScale`.
PSPDF_CLASS_SWIFT(MeasurementCalibration)
@interface PSPDFMeasurementCalibration: NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// A known real world distance. The unit of this value is given by `unitTo`.
@property (nonatomic, readonly) double value;

/// The unit for the known real world distance.
@property (nonatomic, readonly) PSPDFUnitTo unitTo;

@end

/// Measurement info object used to store details of a measurement annotation.
PSPDF_CLASS_SWIFT(MeasurementInfo)
@interface PSPDFMeasurementInfo: PSPDFModel

/// The measurement scale used in the measurement annotation.
@property (nonatomic, readonly) PSPDFMeasurementScale *scale;

/// Returns the measurement mode (ie. distance, perimeter, area) of the measurement annotation.
@property (nonatomic, readonly) PSPDFMeasurementMode mode;

/// The number of decimal places of precision used to display the measurement in the annotation `contents`.
@property (nonatomic, readonly) PSPDFMeasurementPrecision precision;

@end

NS_ASSUME_NONNULL_END
