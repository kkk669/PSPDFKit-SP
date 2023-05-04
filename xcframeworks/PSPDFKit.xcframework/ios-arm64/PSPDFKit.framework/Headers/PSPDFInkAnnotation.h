//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractShapeAnnotation.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFPageInfo;

/// An ink annotation for freehand drawing or writing.
///
/// This annotation type is referred to as Drawing in the PSPDFKit UI.
/// It allows the user to add one or more strokes on top of PDF content.
///
/// The `lines` are automatically scaled when the `boundingBox` is changed,
/// and the `boundingBox` is updated when the `lines` are changed to enclose the new points.
///
/// @see The annotation tool is activated in the UI by `PSPDFAnnotationStateManager` and `AnnotationToolbar`.
/// The drawing interaction is handled by `PSPDFDrawView`. Some drawing-related behaviors
/// can be set in the `PDFConfiguration`, such as with its `drawCreateMode` property,
/// which controls whether a new ink annotation is created after each stroke).
PSPDF_CLASS_SWIFT(InkAnnotation)
@interface PSPDFInkAnnotation : PSPDFAbstractShapeAnnotation<PSPDFOverridable>

/// Designated initializer.
///
/// @param lines Array of arrays of boxed `PSPDFDrawingPoint`.
- (instancetype)initWithLines:(NSArray<NSArray<NSValue *> *> *)lines NS_REFINED_FOR_SWIFT;

/// The lines (or strokes) of the ink annotation.
///
/// This is an array of arrays of boxed `PSPDFDrawingPoint`. Each array represents a single line/stroke.
///
/// Example:
///
/// ```
/// annotation.lines = @[@[
///     @(PSPDFDrawingPointMake(CGPointMake(100,100), 0.5)),
///     @(PSPDFDrawingPointMake(CGPointMake(100,200), 0.5)),
///     @(PSPDFDrawingPointMake(CGPointMake(150,300), 0.5)),
/// ]];
/// ```
///
/// The intensity values determine the line thickness for natural drawing.
///
/// This property is equivalent to the `pointSequences` property inherited from `PSPDFAbstractShapeAnnotation`.
/// Setting either property also sets the other.
///
/// @warning: After setting lines, `boundingBox` will be automatically recalculated.
/// Additionally, the lines will be scaled when the `boundingBox` changed.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (null_resettable, atomic, copy) NSArray<NSArray<NSValue *> *> *lines NS_REFINED_FOR_SWIFT;

/// The `UIBezierPath` will be dynamically created from the lines array.
@property (atomic, readonly) UIBezierPath *bezierPath;

/// Returns `true` if `lines` doesn’t contain any points.
@property (atomic, getter=isEmpty, readonly) BOOL empty;

/// Whether this ink annotation uses the natural drawing style.
///
/// This is a proprietary extension — other viewers will not be able to detect this.
///
/// @see Whether natural drawing is enabled for new annotations can be set using the `PDFConfiguration`
/// properties `naturalDrawingAnnotationEnabled` and `naturalSignatureDrawingEnabled`.
@property (atomic) BOOL naturalDrawingEnabled;

/// Whether this ink annotation is a PSPDFKit signature.
///
/// This is a proprietary extension - other viewer will not be able to detect this.
///
/// Signatures are created using the tool `Annotation.Tool.signature`.
@property (atomic) BOOL isSignature;

/// By default, setting the `boundingBox` will transform all points in the lines array.
/// Use this setter to manually change the `boundingBox` without changing lines.
- (void)setBoundingBox:(CGRect)boundingBox transformLines:(BOOL)transformLines;

/// Generate new line array by applying transform.
/// This is used internally when `boundingBox` is changed.
///
/// @return Either an `NSArray<PSPDFPointArray *>` or an `NSArray<NSArray<NSValue *> *>`.
- (NSArray *)copyLinesByApplyingTransform:(CGAffineTransform)transform;

@end

/// Calculates the bounding box from lines.
///
/// @param lines Either an `NSArray<PSPDFPointArray *>` or `NSArray<NSArray<NSValue *> *>`.
PSPDF_EXPORT CGRect PSPDFBoundingBoxFromLines(NSArray *lines, CGFloat lineWidth) NS_SWIFT_NAME(BoundingBoxFromLines(_:lineWidth:));

/// Will convert view lines to PDF lines (operates on every point)
PSPDF_EXPORT NSArray<NSArray<NSValue *> *> *PSPDFConvertViewLinesToPDFLines(NSArray<NSArray<NSValue *> *> *lines, PSPDFPageInfo *pageInfo, CGRect viewBounds) NS_SWIFT_NAME(ConvertViewLines(pdfLines:pageInfo:viewBounds:));

/// Converts a single line of boxed `PSPDFDrawingPoints`.
PSPDF_EXPORT NSArray<NSValue *> *PSPDFConvertViewLineToPDFLines(NSArray<NSValue *> *line, PSPDFPageInfo *pageInfo, CGRect viewBounds) NS_SWIFT_NAME(ConvertViewLine(pdfLine:pageInfo:viewBounds:));

/// Will convert PDF lines to view lines (arrays of `PSPDFDrawingPoints`) (operates on every point)
PSPDF_EXPORT NSArray<NSArray<NSValue *> *> *PSPDFConvertPDFLinesToViewLines(NSArray<NSArray<NSValue *> *> *lines, PSPDFPageInfo *pageInfo, CGRect viewBounds) NS_SWIFT_NAME(ConvertPDFLines(viewLines:pageInfo:viewBounds:));

NS_ASSUME_NONNULL_END
