//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFRenderRequest.h>
#import <PSPDFKit/PSPDFRenderOptions+Private.h>

NS_ASSUME_NONNULL_BEGIN
@interface PSPDFRenderRequest ()

/// The actual size the resulting image will have (taking into account the aspect
/// ratio of the document or the pdfRect property).
@property (nonatomic, readonly) CGSize actualRenderSize;

/// The actual image scale. If the scale factor is set to 0.0 on iOS this returns the
/// main screen's scale factor, on macOS it returns 1.0.
@property (nonatomic, readonly) CGFloat actualImageScale;

/// Render options, taking into account the options from the document.
@property (nonatomic, readonly) PSPDFRenderOptions *actualRenderOptions;

/// `true` if a request can be cached / read from the cache, or `false` if it can't.
@property (nonatomic, readonly) BOOL eligibleForCaching;

/// A specialized hash of the `actualRenderOptions` dictionary, derived using `optionsHashForRequestParameters:`.
///
/// The value is cached, and calculated lazily. For mutable render requests, the cached value is reset whenever the has is.
@property (nonatomic, readonly) NSUInteger optionsHash;

/// Validates the requests values and logs a warning if the request is invalid.
///
/// @return YES if the request is valid, NO otherwise.
- (BOOL)validateAndLogError:(NSError **)error;

/// Hashes the `options` of a `PSPDFRenderRequest` to a single word.
///
/// This function is optimized for a limited set of keys, known ahead of time. In stark contrast to `NSDictionary.hash`,
/// equal outputs provide a reliable estimate for the equality of two inputs.
///
/// The hash is stable, and has the following properties:
///
/// - it is never 0 to simplify caching
/// - a single value makes the same contribution as a single object array containing that value
/// - the contribution of an array value depends on the order of its elements
/// - the contribution of a dictionary value combines all keys with their respective values
/// - the contribution of values of any other type is based on their `hash` property
+ (NSUInteger)optionsHashForRequestParameters:(NSDictionary<NSString *, id<NSObject>> *)parameters;

@end
NS_ASSUME_NONNULL_END
