//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

/// Computes bezier paths for provided `PSPDFDrawingPoint` sequences,
/// taking the point intensity into account.
PSPDF_SDK_CLASS_SWIFT(NaturalDrawingPaths)
@interface PSPDFNaturalDrawingPaths : NSObject

// MARK: Configuration

/// The line width at 50% intensity.
@property (nonatomic) CGFloat lineWidth;

/// Multiplied by `lineWidth` and the point intensity (if above 50%) to obtain the final line width.
@property (nonatomic, readonly) CGFloat increaseFactor;

/// Multiplied by `lineWidth` and the point intensity (if below 50%) to obtain the final line width.
@property (nonatomic, readonly) CGFloat decreaseFactor;

// MARK: Points

/// Boxed PSPDFDrawingPoint or PSPDFPointArray.
- (void)addLinesFromArray:(NSArray *)lines;

/// Removes all points.
- (void)eraseAllPaths;

// MARK: Path

/// Calls bezierPathForRect: with CGRectInfinite.
@property (nonatomic, readonly) UIBezierPath *bezierPath;

/// Returns the computed natural drawing paths that intersect the provided `rect` (or are contained in it).
- (UIBezierPath *)bezierPathForRect:(CGRect)rect;

/// Draws natural drawing paths contained in `rect` in the provided `context.
- (void)drawInContext:(CGContextRef)context rect:(CGRect)rect;

@end
