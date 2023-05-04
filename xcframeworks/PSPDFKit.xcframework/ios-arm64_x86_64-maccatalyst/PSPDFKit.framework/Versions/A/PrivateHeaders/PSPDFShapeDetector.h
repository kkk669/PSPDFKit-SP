//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFShapeTemplate.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFShapeTemplateStore;

/// Use this class to find the shape that best matches a set of inputs.
PSPDF_SDK_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ShapeDetector)
@interface PSPDFShapeDetector : NSObject

/// Initializes a shape detector with an array of `PSPDFShapeTemplateStore`s.
///
/// @param stores An array of stores containing the templates that the detector should search to find a match.
- (instancetype)initWithTemplateStores:(NSArray<PSPDFShapeTemplateStore *> *)stores NS_DESIGNATED_INITIALIZER;

/// The stores used by the detector to find matches.
@property (nonatomic, readonly) NSArray<PSPDFShapeTemplateStore *> *templateStores;

/// Performs a shape detection.
///
/// @param points The points in the gesture for which the shape is to be detected.
/// @param confidence A pointer to an integer that will be set with the confidence score for the returned match. The confidence will always be in [0, 100],
/// with 100 being a perfect match.
/// @return The identifier for the matching shape template, if one was found.
- (nullable PSPDFShapeTemplateIdentifier)detectShapeMatchingPoints:(PSPDFCGPointArray *)points confidence:(nullable out NSUInteger *)confidence;

@end

NS_ASSUME_NONNULL_END
