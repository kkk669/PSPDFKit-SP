//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// The name for a value transformer that converts strings into URLs and back.
PSPDF_EXTERN NSValueTransformerName const PSPDFURLValueTransformerName;

/// The name for a value transformer that converts `NSDate` to an ISO8601 date string and back.
PSPDF_EXTERN NSValueTransformerName const PSPDFISO8601DateValueTransformerName;

/// Converts a `CGRect` into `NSString`, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFRectValueTransformerName;

/// Converts an array of `CGRect`s into an array of `NSString`s, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFBoxedRectArrayValueTransformerName;

/// Converts an array of `CGPoint` objects into an `NSString`, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFBoxedPointArrayValueTransformerName;

/// Converts arrays of arrays of `CGPoint` objects into an array of array of `NSString`s, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFLinesValueTransformerName;

/// Converts a `CGAffineTransform` into `NSString` and back.
PSPDF_EXTERN NSValueTransformerName const PSPDFAffineTransformValueTransformerName;

/// Converts `Data` to `UIImage` and back.
PSPDF_EXTERN NSValueTransformerName const PSPDFPNGImageTransformerName;

/// Converts base64-encoded `NSString` to 'NSData` and back.
PSPDF_EXTERN NSValueTransformerName const PSPDFBase64TransformerName;

/// Converts base64-encoded `NSString` to `UIImage` and back.
/// This basically combines `PSPDFPNGImageTransformerName` and `PSPDFBase64TransformerName`.
PSPDF_EXTERN NSValueTransformerName const PSPDFBase64PNGImageTransformerName;

/// Converts a `CGPoint` object into an `NSString`, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFPointValueTransformerName;

/// Converts a `UIEdgeInsets` object into an `NSString`, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFEdgeInsetValueTransformerName;

/// Converts `UIColor`/`NSColor` into a string representation
/// (string with 2 or 4 components, depending if color is monochrome or not)
PSPDF_EXTERN NSValueTransformerName const PSPDFColorValueTransformerName;

/// Converts `NSIndexSet` into `NSArray`, reversible.
PSPDF_EXTERN NSValueTransformerName const PSPDFIndexSetTransformerName;

/// Ensure an NSNumber is backed by `__NSCFBoolean`/`CFBooleanRef`
///
/// `NSJSONSerialization`, and likely other serialization libraries, ordinarily
/// serialize NSNumbers as numbers, and thus booleans would be serialized as
/// 0/1. The exception is when the NSNumber is backed by __NSCFBoolean, which,
/// though very much an implementation detail, is detected and serialized as a
/// proper boolean.
PSPDF_EXTERN NSValueTransformerName const PSPDFBooleanValueTransformerName;

@interface NSValueTransformer (PSPDFModel)

/// Composes a value transformer for a dictionary with a key transformer and a value transformer.
/// If a transformer is nil, values are simply passed through.
+ (NSValueTransformer *)pspdf_dictionaryTransformerWithKeyTransformer:(nullable NSValueTransformer *)keyTransformer valueTransformer:(nullable NSValueTransformer *)valueTransformer;

/// Runs `valueTransformer` on the output before the currnet transformer for `transformValue`,
/// and reverse for the reverse operation.
/// self: A <-> B
/// valueTransformer argument: B <-> C
/// returned transformer: A <-(via B)-> C
- (NSValueTransformer *)valueTransformerByCombiningWithValueTransformer:(NSValueTransformer *)valueTransformer;

@end

NS_ASSUME_NONNULL_END
