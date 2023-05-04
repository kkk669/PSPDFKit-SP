//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFRotation.h>

@class PSPDFAction, PSPDFDocumentProvider;

NS_ASSUME_NONNULL_BEGIN

/// Marks an unused or invalid page number.
static const PSPDFPageIndex PSPDFPageNull = NSUIntegerMax;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPageTriggerEvent) {
    /// O (0) Action to be performed when the page is opened.
    PSPDFPageTriggerEventOpen,
    /// C (1) Action to be performed when the page is closed.
    PSPDFPageTriggerEventClose
} PSPDF_ENUM_SWIFT(PDFPageInfo.TriggerEvent);

/// Represents PDF page data. Managed within `PSPDFDocumentProvider`.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFPageInfo)
@interface PSPDFPageInfo : NSObject<NSCopying, NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Referenced page, relative to the document provider.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;
 
/// Referenced document provider.
@property (nonatomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

/// The visible size of the page. This considers page rotation.
@property (nonatomic, readonly) CGSize size;

/// Saved clockwise rotation of page in degrees. The possible values are 0, 90, 180 and 270.
@property (nonatomic, readonly) PSPDFRotation savedRotation;

/// The manually set clockwise rotation of the page relative to its saved rotation.
///
/// The orientation of a page may be modified for display using `-[PSPDFDocumentProvider setRotationOffset:forPageAtIndex:]` without writing to the PDF.
/// The possible values are 0, 90, 180 and 270.
/// The final rotation a page appears is the sum of `rotation` and `rotationOffset`.
@property (nonatomic, readonly) PSPDFRotation rotationOffset;

/// Page transform matrix.
///
/// This uses the rotation and CropBox to map from the raw PDF coordinate space to the normalized PDF coordinate space.
/// Applying this transform to the CropBox will give a rectangle with zero origin and a size equal to the `size` property.
@property (nonatomic, readonly) CGAffineTransform transform;

/// Returns the media box that is set in the PDF. This is in PDF coordinates, straight from the PDF.
///
/// @note This might return CGRectNull if there's no MediaBox set.
@property (nonatomic, readonly) CGRect mediaBox;

/// Returns the crop box that is set in the PDF. This is in PDF coordinates, straight from the PDF.
///
/// @note This might return CGRectNull if there's no CropBox set.
@property (nonatomic, readonly) CGRect cropBox;

/// Returns the trim box that is set in the PDF. This is in PDF coordinates, straight from the PDF.
///
/// @note This might return CGRectNull if there's no TrimBox set.
@property (nonatomic, readonly) CGRect trimBox;

/// Returns the bleed box that is set in the PDF. This is in PDF coordinates, straight from the PDF.
///
/// @note This might return CGRectNull if there's no BleedBox set.
@property (nonatomic, readonly) CGRect bleedBox;

/// Defines additional page actions.
/// Key is `PSPDFPageTriggerEvent`, value a `PSPDFAction` instance.
@property (nonatomic, copy, nullable, readonly) NSDictionary<NSNumber *, PSPDFAction *> *additionalActions;

/// Can be used to selectively disable annotation creation on the page.
/// This feature is a proprietary PSPDFKit extension. To disable annotation creation
/// add a boolean key (`PSPDF:AllowAnnotationCreation`) to the PDF page dictionary and set it to `false`.
@property (nonatomic, readonly) BOOL allowAnnotationCreation;

@end

/// Convert a view point to the normalized PDF coordinate space. `bounds` is from the view. (usually `PSPDFPageView.bounds`)
PSPDF_EXPORT CGPoint PSPDFConvertViewPointToPDFPoint(CGPoint viewPoint, PSPDFPageInfo *pageInfo, CGRect viewBounds);

/// Converts a point in a normalized PDF coordinate space to the view coordinate space.
PSPDF_EXPORT CGPoint PSPDFConvertPDFPointToViewPoint(CGPoint pdfPoint, PSPDFPageInfo *pageInfo, CGRect viewBounds);

/// Converts a rectangle from a normalized PDF coordinate space to the view coordinate space.
///
/// @note **Important:** This is **not** a general purpose conversion function from PDF page to UIKit coordinates!
/// If the pdfRect has negative width or height, the results will be unexpected.
PSPDF_EXPORT CGRect PSPDFConvertPDFRectToViewRect(CGRect pdfRect, PSPDFPageInfo *pageInfo, CGRect viewBounds);

/// Converts a rectangle in a view coordinate space to the normalized PDF coordinate space.
///
/// @note **Important:** This is **not** a general purpose conversion function from UIKit to PDF page coordinates!
/// If the `viewRect` has negative width or height, the results will be unexpected.
PSPDF_EXPORT CGRect PSPDFConvertViewRectToPDFRect(CGRect viewRect, PSPDFPageInfo *pageInfo, CGRect viewBounds);

NS_ASSUME_NONNULL_END
