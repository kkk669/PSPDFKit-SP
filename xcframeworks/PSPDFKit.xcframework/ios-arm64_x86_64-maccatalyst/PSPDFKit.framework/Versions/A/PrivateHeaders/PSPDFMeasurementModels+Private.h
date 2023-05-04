//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

/// All available options for the measurement precision.
PSPDF_SDK_EXPORT NSArray<NSNumber /* PSPDFMeasurementPrecision */ *> *const PSPDFMeasurementPrecisionOptions;
/// All available options for the from unit in the measurement scale.
PSPDF_SDK_EXPORT NSArray<NSNumber /* PSPDFUnitFrom */ *> *const PSPDFMeasurementUnitFromOptions;
/// All available options for the to unit in the measurement scale. This excludes `PSPDFUnitToPoint` because it is deprecated.
PSPDF_SDK_EXPORT NSArray<NSNumber /* PSPDFUnitTo */ *> *const PSPDFMeasurementUnitToOptions;

/// Returns a string describing the precision. This string may be displayed to the user.
PSPDF_SDK_EXPORT NSString *PSPDFMeasurementPrecisionLabel(PSPDFMeasurementPrecision precision);
/// Returns a string describing the unit. This string may be displayed to the user.
PSPDF_SDK_EXPORT NSString *PSPDFMeasurementUnitFromLabel(PSPDFUnitFrom from);
/// Returns a string describing the unit. This string may be displayed to the user.
PSPDF_SDK_EXPORT NSString *PSPDFMeasurementUnitToLabel(PSPDFUnitTo to);

/// Convenience that maps `PSPDFMeasurementPrecisionOptions` using `PSPDFMeasurementPrecisionLabel`.
PSPDF_SDK_EXPORT NSArray<NSString *> *PSPDFMeasurementPrecisionOptionNames(void);
/// Convenience that maps `PSPDFMeasurementUnitFromOptions` using `PSPDFMeasurementUnitFromLabel`.
PSPDF_SDK_EXPORT NSArray<NSString *> *PSPDFMeasurementUnitFromOptionNames(void);
/// Convenience that maps `PSPDFMeasurementUnitToOptions` using `PSPDFMeasurementUnitToLabel`.
PSPDF_SDK_EXPORT NSArray<NSString *> *PSPDFMeasurementUnitToOptionNames(void);

PSPDF_SDK_EXPORT NSString *PSPDFLocalizeMeasurementScale(PSPDFMeasurementScale *scale);
PSPDF_SDK_EXPORT NSString *PSPDFLocalizeMeasurementCalibration(PSPDFMeasurementCalibration *calibration);

PSPDF_SDK_EXPORT NSValueTransformerName const PSPDFMeasurementPrecisionTransformerName;

PSPDF_SDK_EXPORT BOOL PSPDFAnnotationVariantIsMeasurement(NSString * _Nullable variant);
PSPDF_SDK_EXPORT BOOL PSPDFAnnotationVariantIsAbstractLineMeasurement(NSString * _Nullable variant);
PSPDF_SDK_EXPORT PSPDFMeasurementMode PSPDFMeasurementModeForAnnotationVariant(NSString *variant);

// MARK: -

@class PDFCMeasurementCalibration, PDFCMeasurementInfo, PDFCMeasurementScale;

@interface PSPDFMeasurementCalibration ()

/// Designated initializer.
- (instancetype)initWithValue:(double)value unit:(PSPDFUnitTo)unitTo NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoreMeasurementCalibration:(PDFCMeasurementCalibration *)coreMeasurementCalibration;

- (PDFCMeasurementCalibration *)coreMeasurementCalibration;

@end

@interface PSPDFMeasurementScale ()

- (instancetype)initWithCoreMeasurementScale:(PDFCMeasurementScale *)coreMeasurementScale;

- (PDFCMeasurementScale *)coreMeasurementScale;

@end

@interface PSPDFMeasurementInfo ()

- (instancetype)initWithCoreMeasurementInfo:(PDFCMeasurementInfo *)coreMeasurementInfo;
- (instancetype)initWithMeasurementScale:(PSPDFMeasurementScale *)scale precision:(PSPDFMeasurementPrecision)precision mode:(PSPDFMeasurementMode)mode;

@end

NS_ASSUME_NONNULL_END
