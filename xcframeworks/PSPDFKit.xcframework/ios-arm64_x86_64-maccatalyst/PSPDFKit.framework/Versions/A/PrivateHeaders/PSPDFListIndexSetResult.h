/// Copyright (c) 2016-present, Facebook, Inc.
/// All rights reserved.
///
/// This source code is licensed under the BSD-style license found in the
/// LICENSE file in the root directory of this source tree. An additional grant
/// of patent rights can be found in the PATENTS file in the same directory.

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFListMoveIndex.h>
#else
#import "PSPDFEnvironment.h"
#import "PSPDFListMoveIndex.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// A result object returned when diffing with indexes.
PSPDF_APP_CLASS_SWIFT(ListIndexSetResult)
@interface PSPDFListIndexSetResult : NSObject

/// The indexes inserted into the new collection.
@property (nonatomic, strong, readonly) NSIndexSet *inserts;

/// The indexes deleted from the old collection.
@property (nonatomic, strong, readonly) NSIndexSet *deletes;

/// The indexes in the old collection that need updated.
@property (nonatomic, strong, readonly) NSIndexSet *updates;

/// The moves from an index in the old collection to an index in the new collection.
@property (nonatomic, copy, readonly) NSArray<PSPDFListMoveIndex *> *moves;

/// A Read-only boolean that indicates whether the result has any changes or not.
/// `true` if the result has changes, `false` otherwise.
@property (nonatomic, assign, readonly) BOOL hasChanges;

/// Returns the index of the object with the specified identifier *before* the diff.
///
/// @param identifier The diff identifier of the object.
///
/// @return The index of the object before the diff, or `NSNotFound`.
///
/// @see `-[PSPDFListDiffable diffIdentifier]`.
- (NSInteger)oldIndexForIdentifier:(id<NSObject>)identifier;

/// Returns the index of the object with the specified identifier *after* the diff.
///
/// @param identifier The diff identifier of the object.
///
/// @return The index path of the object after the diff, or `NSNotFound`.
///
/// @see `-[PSPDFListDiffable diffIdentifier]`.
- (NSInteger)newIndexForIdentifier:(id<NSObject>)identifier;

/// Creates a new result object with operations safe for use in `UITableView` and `UICollectionView` batch updates.
@property (nonatomic, readonly) PSPDFListIndexSetResult *resultForBatchUpdates;

/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;

/// :nodoc:
+ (instancetype) new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
