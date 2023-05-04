//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreText/CoreText.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Label placement options.
typedef NS_ENUM(NSInteger, PSPDFTextPlacement)
{
    /// The label is placed above the given line or point.
    PSPDFTextPlacementAbove,
    /// The label is placed with it's center on the given line or point.
    PSPDFTextPlacementCenter,
    /// The label is placed below the given line or point.
    PSPDFTextPlacementBelow,
} NS_SWIFT_NAME(TextPlacement);

/// Draws text along the line of two points with the given font, color and distance from the center point of the line segment.
///
/// @note: When using `PSPDFTextPlacementCenter` for placement, `distance` will be ignored.
/// @return: Returns 'YES' if the label was drawn, otherwise `NO` if the text could not be drawn, ex. the text could not fit in the given `sizeLimit`.
PSPDF_EXTERN BOOL PSPDFDrawTextNextToLine(NSString *text, CGPoint point1, CGPoint point2, CGFloat distance, PSPDFTextPlacement placement, UIFont *font, UIColor *color, CGSize sizeLimit, CGContextRef context);

/// Draws text above the given point with the given an angle, font, color and distance from the point.
///
/// @note: When using `PSPDFTextPlacementCenter` for placement, `distance` will be ignored.
/// @return: Returns 'YES' if the label was drawn, otherwise `NO` if the text could not be drawn, ex. the text could not fit in the given `sizeLimit`.
PSPDF_EXTERN BOOL PSPDFDrawTextNextToPoint(NSString *text, CGPoint point, CGFloat angle, CGFloat distance, PSPDFTextPlacement placement, UIFont *font, UIColor *color, CGSize sizeLimit, CGContextRef context);

/// Calculates the bounding box of the text placed with above the given point using the given angle, font and distance from the point.
///
/// @note: When using `PSPDFTextPlacementCenter` for placement, `distance` will be ignored.
/// @return: Bounding rectangle for the text. The returned value might be `CGRectNull` if the text could not fit in the given `sizeLimit`.
PSPDF_EXTERN CGRect PSPDFTextBoundingBoxNextToPoint(NSString *text, CGPoint point, CGFloat angle, CGFloat distance, PSPDFTextPlacement placement, UIFont *font, CGSize sizeLimit);

/// Calculates the bounding box of the text placed with the given font and distance from the center point of the line segment.
///
/// @note: When using `PSPDFTextPlacementCenter` for placement, `distance` will be ignored.
/// @return: Bounding rectangle for the text. The returned value might be `CGRectNull` if the text could not fit in the given `sizeLimit`.
PSPDF_EXTERN CGRect PSPDFTextBoundingBoxNextToLine(NSString *text, CGPoint point1, CGPoint point2, CGFloat distance, PSPDFTextPlacement placement, UIFont * font, CGSize sizeLimit);

/// Creates a frame setter for the given string/font and returns it if the suggested size is positive definite, `nil` otherwise.
///
/// @note: If `sizeLimit` is not `CGSizeZero` this function might return `nil` if the text cannot be fit in the given `sizeLimit`.
PSPDF_EXTERN CTFramesetterRef _Nullable PSPDFCreateNonemptyFramesetterForTextWithFont(NSString *text, UIFont *font, UIColor *_Nullable color, CGSize sizeLimit, CGSize *suggestedSize);

NS_ASSUME_NONNULL_END
