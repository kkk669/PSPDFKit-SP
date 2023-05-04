//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// The type of a template identifier. See `PSPDFShapeTemplateTransformer.h` for PSPDFKit's preset templates.
typedef NSString *PSPDFShapeTemplateIdentifier NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(ShapeTemplateIdentifier);

/// Identifies a template for a rectangle.
PSPDF_APP_EXPORT PSPDFShapeTemplateIdentifier const PSPDFShapeTemplateIdentifierRectangle;

/// Identifies a template for a circle (or ellipse).
PSPDF_APP_EXPORT PSPDFShapeTemplateIdentifier const PSPDFShapeTemplateIdentifierCircle;

/// Identifies a template for a simple line.
PSPDF_APP_EXPORT PSPDFShapeTemplateIdentifier const PSPDFShapeTemplateIdentifierLine;

/// Identifies a template for a line that starts with an arrow.
PSPDF_APP_EXPORT PSPDFShapeTemplateIdentifier const PSPDFShapeTemplateIdentifierLineArrowStart;

/// Identifies a template for a line that ends with an arrow.
PSPDF_APP_EXPORT PSPDFShapeTemplateIdentifier const PSPDFShapeTemplateIdentifierLineArrowEnd;

/// Identifies a template for a curve. This is currently used to ensure drawn curves aren't converted to shapes.
PSPDF_APP_EXPORT PSPDFShapeTemplateIdentifier const PSPDFShapeTemplateIdentifierCurve;

NS_ASSUME_NONNULL_END
