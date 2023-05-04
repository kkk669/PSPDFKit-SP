//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//  Based on GitHub's Mantle project, MIT licensed.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// A value transformer supporting block-based transformation.
PSPDF_SDK_CLASS_SWIFT(ValueTransformer)
@interface PSPDFValueTransformer : NSValueTransformer

/// Returns a transformer which transforms values using the given block. Reverse
/// transformations will not be allowed.
+ (instancetype)transformerWithBlock:(nullable id (^)(id))transformationBlock;

/// Returns a transformer which transforms values using the given block, for
/// forward or reverse transformations.
+ (instancetype)reversibleTransformerWithBlock:(nullable id (^)(id))transformationBlock;

/// Returns a transformer which transforms values using the given blocks.
+ (instancetype)reversibleTransformerWithForwardBlock:(nullable id (^)(id))forwardBlock reverseBlock:(nullable id (^)(id))reverseBlock;

/// Returns a transformer that translates with `dictionary` and optionally returns `defaultValue`.
/// Both keys and values in `dictionary` must correspond to NSCopying.
+ (instancetype)transformerWithDictionary:(NSDictionary *)dictionary defaultValue:(nullable id<NSCopying>)defaultValue unknownValue:(nullable id<NSCopying>)unknownValue;

/// Returns a value transformer and executes the block to create the transformer if not found.
+ (NSValueTransformer *)valueTransformerForName:(NSValueTransformerName)name createBlock:(NSValueTransformer * (^)(void))createBlock;

@end

NS_ASSUME_NONNULL_END
