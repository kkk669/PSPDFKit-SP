//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// PDF Line annotation.
PSPDF_CLASS_SWIFT(LineAnnotation)
@interface PSPDFLineAnnotation : PSPDFAbstractLineAnnotation<PSPDFOverridable>

/// Designated initializer.
- (instancetype)initWithPoint1:(CGPoint)point1 point2:(CGPoint)point2;

/// Starting point.
///
/// @note After changing the point, call `recalculateBoundingBox` to update the bounds.
@property (atomic) CGPoint point1;

/// End point.
///
/// @note After changing the point, call `recalculateBoundingBox` to update the bounds.
@property (atomic) CGPoint point2;

@end

NS_ASSUME_NONNULL_END
