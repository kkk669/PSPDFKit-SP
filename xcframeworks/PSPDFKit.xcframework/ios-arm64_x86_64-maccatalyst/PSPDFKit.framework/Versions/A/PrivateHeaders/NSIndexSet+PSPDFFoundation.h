//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSIndexSet (PSPDFFoundation)

/// Maps each index in the receiver using a given block, returning
/// an array built from the resulting objects.
///
/// @param block A block with which to transform each index, which are
/// passed in the `idx` argument.
///
/// @warning **Important:** It is permissible to return `nil` from `block`, but
/// doing so will omit an entry from the resultant array, such that the number of
/// objects in the result is less than the number of indexes in the receiver. If
/// you need the array to match the index set in size, return `NSNull` instead of
/// `nil`.
- (NSArray *)pspdf_mapped:(NS_NOESCAPE id (^)(NSUInteger idx))block;

/// Returns a `NSSet<NSNumber *> *` with all the indexes inside.
@property (nonatomic, readonly) NSSet<NSNumber *> *pspdf_numberSet;

/// Converts an index set to a range.
///
/// @note This will use the first and last index, and build a range.
/// If the index set has holes, this will result in a lossy conversion.
/// Example: Set [1,2,4,5] will result in NSRange(pos: 1, length:4) = 1,2,3,4,5.
@property (nonatomic, readonly) NSRange pspdf_range;

@end

NS_ASSUME_NONNULL_END

#ifdef __cplusplus
#include <vector>

NS_ASSUME_NONNULL_BEGIN

@interface NSIndexSet (PSPDFFoundationCpp)

/// Converts the index set to a set of ranges.
@property (nonatomic, readonly) std::vector<NSRange> pspdf_rangeVector;

@end

NS_ASSUME_NONNULL_END
#endif
