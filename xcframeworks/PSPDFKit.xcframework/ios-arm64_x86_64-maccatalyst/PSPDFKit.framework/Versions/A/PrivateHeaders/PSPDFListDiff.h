/// Copyright (c) 2016-present, Facebook, Inc.
/// All rights reserved.
///
/// This source code is licensed under the BSD-style license found in the
/// LICENSE file in the root directory of this source tree. An additional grant
/// of patent rights can be found in the PATENTS file in the same directory.

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFIndexPathDiff.h>
#import <PSPDFKit/PSPDFListDiffable.h>
#import <PSPDFKit/PSPDFListIndexPathResult.h>
#import <PSPDFKit/PSPDFListIndexSetResult.h>
#else
#import "PSPDFEnvironment.h"
#import "PSPDFIndexPathDiff.h"
#import "PSPDFListDiffable.h"
#import "PSPDFListIndexPathResult.h"
#import "PSPDFListIndexSetResult.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// An option for how to do comparisons between similar objects.
typedef NS_ENUM(NSInteger, PSPDFListDiffOption) {
    /// Compare objects using pointer personality.
    PSPDFListDiffPointerPersonality,
    /// Compare objects using `-[PSPDFListDiffable isEqualToDiffableObject:]`.
    PSPDFListDiffEquality
};

/// Creates a diff using indexes between two collections.
///
/// @param oldArray The old objects to diff against.
/// @param newArray The new objects.
/// @param option   An option on how to compare objects.
///
/// @return A result object containing affected indexes.
PSPDF_APP_EXPORT PSPDFListIndexSetResult *PSPDFListDiff(NSArray<id<PSPDFListDiffable>> *_Nullable oldArray, NSArray<id<PSPDFListDiffable>> *_Nullable newArray, PSPDFListDiffOption option);

/// Creates a diff using indexes between two collections of objects not conforming
/// to the `PSPDFListDiffable` protocol.
///
/// @param oldArray The old objects to diff against.
/// @param newArray The new objects.
/// @param diffIdentifier A block returning a key uniquely identifying `object`.
/// @param isEqual A block that returns whether `left` and `right` are equal, or nil
/// if you want to compare objects based on pointer equality.
///
/// @return A result object containing affected indexes.
PSPDF_APP_EXPORT PSPDFListIndexSetResult *PSPDFListDiffGeneric(NSArray *_Nullable oldArray, NSArray *_Nullable newArray, id<NSObject>(^diffIdentifier)(id object), BOOL(^ _Nullable isEqual)(id left, id _Nullable right));

/// Creates a diff using index paths between two collections.
///
/// @param fromSection The old section.
/// @param toSection   The new section.
/// @param oldArray    The old objects to diff against.
/// @param newArray    The new objects.
/// @param option      An option on how to compare objects.
///
/// @return A result object containing affected indexes.
PSPDF_APP_EXPORT PSPDFListIndexPathResult *PSPDFListDiffPaths(NSInteger fromSection, NSInteger toSection, NSArray<id<PSPDFListDiffable>> *_Nullable oldArray, NSArray<id<PSPDFListDiffable>> *_Nullable newArray, PSPDFListDiffOption option);

@interface PSPDFIndexPathDiff (ListDiffConversion)

/// Converts an index set result into an index path diff, which we use occasionally in public API.
///
/// @param sectionIndex Index of the section for the generated index paths — as in `+indexPathForRow:inSection:`.
/// @param indexSetResult The raw diff to convert into an `IndexPathDiff`.
+ (instancetype)indexPathDiffForSection:(NSUInteger)sectionIndex fromListIndexSetResult:(PSPDFListIndexSetResult *)indexSetResult;

@end

NS_ASSUME_NONNULL_END
