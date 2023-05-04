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
#import <PSPDFKit/PSPDFIndexPathMove.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFIndexPathMove.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// A simple value object representing a tree diff with index paths. The exact
/// sematics of the contents are defined by the diffing algorithm, not this object.
PSPDF_SDK_CLASS_SWIFT(IndexPathDiff)
@interface PSPDFIndexPathDiff : NSObject <NSCopying, NSMutableCopying>

/// Index paths for objects that have been deleted.
@property (nonatomic, readonly) NSArray<NSIndexPath *> *deletes;

/// Index paths at which objects have been inserted.
@property (nonatomic, readonly) NSArray<NSIndexPath *> *inserts;

/// Index paths for objects that have been updated.
@property (nonatomic, readonly) NSArray<NSIndexPath *> *updates;

/// A set of moves for objects that have been moved.
@property (nonatomic, readonly) NSArray<PSPDFIndexPathMove *> *moves;

/// Convenience property, returns all section deletes (index paths of length 1) as
/// an `NSIndexSet`. Useful for updating sections of a table view. Cached for
/// better performance.
@property (nonatomic, readonly) NSIndexSet *sectionDeletes;

/// Convenience property, returns all section inserts (index paths of length 1) as
/// an `NSIndexSet`. Useful for updating sections of a table view.
@property (nonatomic, readonly) NSIndexSet *sectionInserts;

/// Convenience property, returns all section updates (index paths of length 1) as
/// an `NSIndexSet`. Useful for updating sections of a table view.
@property (nonatomic, readonly) NSIndexSet *sectionUpdates;

/// Convenience property, returns all section moves (`from` and `to` index paths
/// must both be of length 1). Useful for updating sections of a table view.
@property (nonatomic, readonly) NSArray<PSPDFIndexPathMove *> *sectionMoves;

/// Convenience property, returns all row deletes (index paths of length 2). Useful
/// for updating rows of a table view. Cached for better performance.
@property (nonatomic, readonly) NSArray<NSIndexPath *> *rowDeletes;

/// Convenience property, returns all row inserts (index paths of length 2). Useful
/// for updating rows of a table view. Cached for better performance.
@property (nonatomic, readonly) NSArray<NSIndexPath *> *rowInserts;

/// Convenience property, returns all row updates (index paths of length 2). Useful
/// for updating rows of a table view. Cached for better performance.
@property (nonatomic, readonly) NSArray<NSIndexPath *> *rowUpdates;

/// Convenience property, returns all row moves (`from` and `to` index paths
/// must both be of length 2). Useful for updating rows of a table view. Cached for
/// better performance.
@property (nonatomic, readonly) NSArray<PSPDFIndexPathMove *> *rowMoves;

/// Returns true if there are no changes set.
@property (nonatomic, readonly) BOOL isEmpty;

/// Returns an empty index path diff.
+ (instancetype)indexPathDiff;

/// Returns a new index path diff initialized with another index path diff.
+ (instancetype)indexPathDiffWithIndexPathDiff:(PSPDFIndexPathDiff *)indexPathDiff;

/// Returns a new index path diff initialized with the given `deletes`, `inserts`,
/// `updates`, and `moves`.
+ (instancetype)indexPathDiffWithDeletes:(NSArray<NSIndexPath *> *)deletes inserts:(NSArray<NSIndexPath *> *)inserts updates:(NSArray<NSIndexPath *> *)updates moves:(NSArray<PSPDFIndexPathMove *> *)moves;

/// Initializes a new index path diff with another index path diff.
- (instancetype)initWithIndexPathDiff:(PSPDFIndexPathDiff *)indexPathDiff;

/// Initializes a new index path diff with the given `deletes`, `inserts`,
/// `updates`, and `moves`.
- (instancetype)initWithDeletes:(NSArray<NSIndexPath *> *)deletes inserts:(NSArray<NSIndexPath *> *)inserts updates:(NSArray<NSIndexPath *> *)updates moves:(NSArray<PSPDFIndexPathMove *> *)moves NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
