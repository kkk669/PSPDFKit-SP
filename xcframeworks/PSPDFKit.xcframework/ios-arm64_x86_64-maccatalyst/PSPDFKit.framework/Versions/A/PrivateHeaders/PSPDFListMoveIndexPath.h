/// Copyright (c) 2016-present, Facebook, Inc.
/// All rights reserved.
///
/// This source code is licensed under the BSD-style license found in the
/// LICENSE file in the root directory of this source tree. An additional grant
/// of patent rights can be found in the PATENTS file in the same directory.

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// An object representing a move between indexes.
PSPDF_APP_CLASS_SWIFT(ListMoveIndexPath)
@interface PSPDFListMoveIndexPath : NSObject

/// An index path in the old collection.
@property (nonatomic, strong, readonly) NSIndexPath *from;

/// An index path in the new collection.
@property (nonatomic, strong, readonly) NSIndexPath *to;

/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;

/// :nodoc:
+ (instancetype) new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
