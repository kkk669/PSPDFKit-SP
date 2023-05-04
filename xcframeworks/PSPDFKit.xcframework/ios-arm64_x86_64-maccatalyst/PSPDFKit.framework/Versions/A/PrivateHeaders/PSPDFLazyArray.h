//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// A lazy array calls it's conversion block on the fly as data is requested,
/// and internally caches the result to ensure the (potentially expensive) conversion only happens once.
///
/// The `conversionBlock` is retained as long as either this object is alive,
/// or until all objects have been converted.
///
/// It behaves like an immutable `NSArray` and is thread safe.
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFLazyArray <ObjectType> : NSArray<ObjectType>

///  Initialize the array with a predefined size and the conversion block that should be used.
///
///  @param size            The size of the array
///  @param converter The conversion function (e.g. boxing CGPoint's into NSValue.
///
///  @return The lazy array subclass.
- (PSPDFLazyArray *)initWithSize:(NSUInteger)size converter:(ObjectType (^)(NSUInteger idx))converter;

@end

NS_ASSUME_NONNULL_END
