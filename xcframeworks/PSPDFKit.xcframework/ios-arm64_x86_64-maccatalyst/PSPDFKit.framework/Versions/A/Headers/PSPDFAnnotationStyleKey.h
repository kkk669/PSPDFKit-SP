//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation;

/// Property keys for annotation inspector customization.
///
/// @see PSPDFAnnotationStyleViewController
/// @see PSPDFConfiguration
/// @see https://pspdfkit.com/guides/ios/annotations/annotation-inspector/
typedef NSString *PSPDFAnnotationStyleKey NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(AnnotationStyle.Key);

/// A list of annotation style keys (inner array) grouped into serval groups (outer array).
typedef NSArray<NSArray<PSPDFAnnotationStyleKey> *> * PSPDFAnnotationStyleKeyGroupedList;

/// A block type that takes an annotation and returns the grouped list of style keys for that particular annotation.
typedef PSPDFAnnotationStyleKeyGroupedList _Nonnull (^PSPDFAnnotationStyleBlock)(PSPDFAnnotation *annotation);

// MARK: Property-Backed Keys

/// Style key representing the annotation `color` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyColor;

/// Style key representing the annotation `fillColor` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyFillColor;

/// Style key representing the annotation `alpha` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyAlpha;

/// Style key representing the annotation `lineWidth` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineWidth;

/// Style key representing the annotation `dashArray` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyDashArray;

/// Style key representing the free text annotation `lineEnd` property.
///
/// @note Applicable only to `FreeTextAnnotation` in callout mode.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineEnd;

/// Style key representing the abstract line annotation `lineEnd1` property.
///
/// @note Applicable only to `PSPDFAbstractLineAnnotation` subclasses.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineEnd1;

/// Style key representing the abstract line annotation `lineEnd2` property.
///
/// @note Applicable only to `PSPDFAbstractLineAnnotation` subclasses.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyLineEnd2;

/// Style key representing the annotation `fontName` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyFontName;

/// Style key representing the annotation `fontSize` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyFontSize;

/// Style key representing the annotation `textAlignment` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyTextAlignment;

/// Style key representing the annotation `blendMode` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyBlendMode;

/// Style key representing the redaction annotation `outlineColor` property.
///
/// @note Applicable only to `PSPDFRedactionAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyOutlineColor;

/// Style key representing the redaction annotation `overlayText` property.
///
/// @note Applicable only to `PSPDFRedactionAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyOverlayText;

/// Style key representing the redaction annotation `repeatOverlayText` property.
///
/// @note Applicable only to `PSPDFRedactionAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyRepeatOverlayText;

/// Style key representing the measurement annotation `measurementScale` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyMeasurementScale;

/// Style key representing the measurement annotation `measurementCalibration` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyMeasurementCalibration;

/// Style key representing the measurement annotation `measurementPrecision` property.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyMeasurementPrecision;

/// Style key representing the global `measurementSnapping` property, to toggle measurement annotation point snapping.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyMeasurementSnapping;

/// Style key representing the annotations `contents` property.
///
/// This will be displayed in `AnnotationStyleViewController` as a single line of static text. This is only intended to be used for measurement annotations. In other cases, use `NoteAnnotationViewController` to view and edit annotation `contents`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyContents;

// MARK: Special Keys

/// Converting a regular free text annotation into a callout (and vice versa)
/// modifies multiple properties, so we use a special key for the change.
///
/// @note Applicable only to `FreeTextAnnotation`.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyCalloutAction;

/// Applying a color preset modifies multiple properties, so we use a special
/// key for the change.
PSPDF_EXPORT PSPDFAnnotationStyleKey const PSPDFAnnotationStyleKeyColorPreset;

NS_ASSUME_NONNULL_END
