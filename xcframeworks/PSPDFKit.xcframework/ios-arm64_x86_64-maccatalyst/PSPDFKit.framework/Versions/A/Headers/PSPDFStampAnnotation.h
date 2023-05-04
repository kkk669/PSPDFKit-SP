//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFRotatable.h>

NS_ASSUME_NONNULL_BEGIN

/// Predefined standard values for a stamp annotation’s `stampType`, which will be written as `Name` in the PDF.
typedef NSString *PSPDFStampType NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(StampAnnotation.Kind);

/// A green checkmark stamp. Does not display text. From Adobe Acrobat’s Sign Here stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeAccepted;

/// A green stamp that displays the text ‘APPROVED’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeApproved;

/// A stamp that displays the text ‘AS IS’ in English. From the PDF specification.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeAsIs;

/// A green stamp that displays the text ‘COMPLETED’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeCompleted;

/// A stamp that displays the text ‘CONFIDENTIAL’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeConfidential;

/// A stamp that displays the text ‘DEPARTMENTAL’ in English. From the PDF specification.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeDepartmental;

/// A stamp that displays the text ‘DRAFT’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeDraft;

/// A stamp that displays the text ‘EXPERIMENTAL’ in English. From the PDF specification.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeExperimental;

/// A stamp that displays the text ‘EXPIRED’ in English. From the PDF specification.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeExpired;

/// A green stamp that displays the text ‘FINAL’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeFinal;

/// A stamp that displays the text ‘FOR COMMENT’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeForComment;

/// A stamp that displays the text ‘FOR PUBLIC RELEASE’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeForPublicRelease;

/// A stamp that displays the text ‘INFORMATION ONLY’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeInformationOnly;

/// A stamp with a left-pointing arrow that displays the text ‘INITIAL HERE’ in English. From Adobe Acrobat’s Sign Here stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeInitialHere;

/// A red stamp that displays the text ‘NOT APPROVED’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeNotApproved;

/// A stamp that displays the text ‘NOT FOR PUBLIC RELEASE’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeNotForPublicRelease;

/// A stamp that displays the text ‘PRELIMINARY RESULTS’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypePreliminaryResults;

/// A red cross stamp. Does not display text. From Adobe Acrobat’s Sign Here stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeRejected;

/// A stamp that displays the text ‘REVISED’ in English. From Adobe Acrobat’s Dynamic stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeRevised;

/// A red stamp with a left-pointing arrow that displays the text ‘SIGN HERE’ in English. From Adobe Acrobat’s Sign Here stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeSignHere;

/// A stamp that displays the text ‘SOLD’ in English. From the PDF specification.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeSold;

/// A stamp that displays the text ‘TOP SECRET’ in English. From the PDF specification.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeTopSecret;

/// A red stamp that displays the text ‘VOID’ in English. From Adobe Acrobat’s Standard Business stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeVoid;

/// A yellow stamp with a left-pointing arrow that displays the text ‘WITNESS’ in English. From Adobe Acrobat’s Sign Here stamps.
PSPDF_EXPORT PSPDFStampType const PSPDFStampTypeWitness;

/// PDF stamp annotation.
///
/// Stamp annotations that have no `image` and no known `stampType` will render their `title`.
/// `title` is a PSPDFKit addition that is not part of the PDF specification.
///
/// Stamps may be rotated using the `rotation` property from `PSPDFRotatable`.
///
/// @note Make sure you configured Image Permissions in your app.
/// See https://pspdfkit.com/guides/ios/getting-started/permissions/#toc_image-permissions for further documentation.
PSPDF_CLASS_SWIFT(StampAnnotation)
@interface PSPDFStampAnnotation : PSPDFAnnotation <PSPDFRotatable, PSPDFOverridable>

/// Returns predefined colors for known names, like red for "void" or green for "completed".
/// Returns a default color (blue) for any other name, including `nil` and empty ones.
+ (UIColor *)colorForStampType:(nullable PSPDFStampType)stampType NS_SWIFT_NAME(color(for:));

/// Creates a new stamp annotation with a known identifier.
/// Standard names are defined in the PDF specification.
/// Most names that Adobe Acrobat creates are also supported.
/// The stamp color will be set using using `colorForStampType:`.
- (instancetype)initWithStampType:(nullable PSPDFStampType)stampType;

/// Creates a new stamp annotation that displays custom text.
/// The stamp color will be blue.
- (instancetype)initWithTitle:(nullable NSString *)title;

/// Create a new stamp annotation with an image.
- (instancetype)initWithImage:(nullable UIImage *)image;

/// A standard, known stamp identifier.
///
/// This is not text displayed to the user. It’s an identifier used to look up the image or localized text to display.
///
/// The "Name" key in the PDF.
/// Be careful not to confuse this with the `name` property on `PSPDFAnnotation`, which is the "NM" key in the PDF.
///
/// Setting this to a standard type will change the title and subtitle to the predefined values for that type.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, copy, nullable) PSPDFStampType stampType;

/// The main text shown by the stamp.
/// This is a PSPDFKit addition that is not part of the PDF specification.
/// This is set automatically to the correct localized text when a standard stamp type is set.
/// Usually this property should only be changed for stamps with no stamp type.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, copy, nullable) NSString *title;

/// The text shown in the second line of a custom text stamp.
/// This is a PSPDFKit addition that is not part of the PDF specification.
/// This property does nothing for stamps with an `image`.
/// Usually this property should not be set for stamps with a known stamp type.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, copy, nullable) NSString *subtitle;

/// The counterclockwise angle of the annotation relative to the page, in degrees.
/// The angle should be between 0 and 359. Defaults to 0.
///
/// To set the rotation, use `setRotation(_:updateBoundingBox:)`.
///
/// NOTE: Only the default (Acrobat stamps) and vector stamps support rotation but in limited document
/// saving configurations. See `Rotatable` for more details.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, readonly) NSUInteger rotation;

/// Stamp image. Defaults to nil. Set to render an image.
///
/// @note An image set will take priority over the internal appearance stream.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic, nullable) UIImage *image;

/// Parses the AP stream, searches for an image and loads it.
/// This can return nil if the `image` has been set manually.
///
/// @note This will not update `image` or `imageTransform` - do that manually if required.
- (nullable UIImage *)loadImageWithTransform:(nullable out CGAffineTransform *)transform error:(NSError **)error;

/// Stamp image transform. Defaults to `CGAffineTransformIdentity`.
@property (atomic) CGAffineTransform imageTransform;

/// Whether this stamp annotation is a PSPDFKit signature.
///
/// This is a proprietary extension - other viewer will not be able to detect this.
///
/// Signatures are created using the tool `Annotation.Tool.signature`.
@property (atomic) BOOL isSignature;

// MARK: Sizing

/// Return 'best' size to fit given size. does not actually resize the `boundingBox`.
/// Will only work for simple stamp annotations with a subtitle.
- (CGSize)sizeThatFits:(CGSize)size;

/// Calls `sizeThatFits:` with the current `boundingBox` and changes the `boundingBox`.
- (void)sizeToFit;

@end

NS_ASSUME_NONNULL_END
