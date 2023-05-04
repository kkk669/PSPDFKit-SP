//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
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

/// Represents a single move of an object within a tree diff with index paths.
PSPDF_SDK_CLASS_SWIFT(IndexPathMove)
@interface PSPDFIndexPathMove : NSObject <NSCopying>

/// The index path the object has moved from.
@property (nonatomic, readonly) NSIndexPath *from;

/// The index path the object has moved to.
@property (nonatomic, readonly) NSIndexPath *to;

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Returns an index path move with `from` and `to` index path.
+ (instancetype)indexPathMoveFrom:(NSIndexPath *)from to:(NSIndexPath *)to;

/// Initializes an index path move with `from` and `to` index path.
- (instancetype)initFrom:(NSIndexPath *)from to:(NSIndexPath *)to NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
