//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFShapeTemplateIdentifier.h>

/// Represents an array of boxed CGPoints.
typedef NSArray<NSValue /* CGPoint */ *> PSPDFCGPointArray;

NS_ASSUME_NONNULL_BEGIN

/// Identifies a template that is used for shape detection.
PSPDF_SDK_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ShapeTemplate)
@interface PSPDFShapeTemplate : PSPDFModel

/// Initializes a template with the specified identifier and an array of boxed `CGPoint`s.
///
/// @param identifier The identifier for the template.
/// @param points An array of boxed `CGPoint`s which, when put together, create the path for a shape.
/// These points should be in the default UIKit coordinate system. That is, the Y component should increase
/// from top to bottom, and the X component should increase from left to right.
- (instancetype)initWithIdentifier:(PSPDFShapeTemplateIdentifier)identifier points:(PSPDFCGPointArray *)points;

/// The identifier for the template.
@property (nonatomic, readonly) PSPDFShapeTemplateIdentifier identifier;

/// The points passed in when initializing the template are normalized to indicate the relative change between each other.
/// This is required by the shape detection algorithm. The original points are _not_ stored.
@property (nonatomic, readonly) PSPDFCGPointArray *normalizedPoints;

@end

NS_ASSUME_NONNULL_END
