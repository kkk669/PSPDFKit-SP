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

/// This class maps template identifiers to transformer classes.
PSPDF_TEST_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ShapeTemplateTransformerRegistry)
@interface PSPDFShapeTemplateTransformerRegistry : NSObject

/// The shared registry. By default the registry has transformers defined for PSPDFKit's default set of templates.
@property (class, nonatomic, readonly) PSPDFShapeTemplateTransformerRegistry *sharedInstance NS_SWIFT_NAME(shared);

/// Retrieves the transformer class for a given identifier.
///
/// @param identifier The identifier to use to look up the transformer.
/// @return The class for `identifier`, if it was registered. Else `nil.`
- (nullable Class)transformerClassForIdentifier:(PSPDFShapeTemplateIdentifier)identifier;

@end

NS_ASSUME_NONNULL_END
