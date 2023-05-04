//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDrawingPoint.hpp>
#import <PSPDFKit/PSPDFPointArray.h>

#ifdef __cplusplus
#include <vector>
NS_ASSUME_NONNULL_BEGIN

@interface PSPDFPointArray ()

/// Initialize with a pre-filled point vector
- (instancetype)initWithVector:(std::vector<PSPDF::DrawingPoint> const &)points NS_DESIGNATED_INITIALIZER;

/// Directly expose the vector array. Fast but careful to ensure lifetime.
@property (nonatomic, readonly) const std::vector<PSPDF::DrawingPoint> &vectorPointsReference;

/// Returns a copy of the internal vector array.
@property (nonatomic, readonly) std::vector<PSPDF::DrawingPoint> vectorPoints;

@end

/// Converts an array of points into a vector of points.
/// @note Ensures all points are valid and will filter out invalid points.
std::vector<PSPDF::DrawingPoint> PSPDFVectorFromBoxedPoints(NSArray<NSValue *> *points);

NS_ASSUME_NONNULL_END
#endif
