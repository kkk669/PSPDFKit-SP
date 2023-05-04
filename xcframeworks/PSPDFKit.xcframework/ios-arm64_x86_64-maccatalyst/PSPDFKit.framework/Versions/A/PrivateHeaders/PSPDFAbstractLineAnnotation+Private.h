//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFMeasurementAnnotationInternal.h>

@class PSPDFPointArray;

NS_ASSUME_NONNULL_BEGIN

/// Returns a string for the given line end type.
PSPDF_EXTERN NSString * PSPDFStringForLineEndType(PSPDFLineEndType value) NS_REFINED_FOR_SWIFT;

/// Returns a localized string for the given line end type.
PSPDF_EXTERN NSString * PSPDFLocalizedStringForLineEndType(PSPDFLineEndType value) NS_REFINED_FOR_SWIFT;

@interface PSPDFAbstractLineAnnotation () <PSPDFMeasurementAnnotationInternal>

@property (atomic, copy, nullable) UIBezierPath *bezierPathBackingStore;

@property (nonatomic, readonly) BOOL dashBezierPath;

@property (nonatomic, readonly) BOOL closesPath;

/// Invalidates the measurement label.
- (void)invalidateMeasurementLabel;

/// Update the stored measurement label using `calculateMeasurementLabel`.
- (void)updateMeasurementLabel;

/// Calculates the measurement label value. Subclasses can override this to provide their custom implementation. Default returns `nil`.
- (nullable NSString *)calculateMeasurementLabel;

@end

NS_ASSUME_NONNULL_END
