/// Copyright (c) 2016-present, Facebook, Inc.
/// All rights reserved.
///
/// This source code is licensed under the BSD-style license found in the
/// LICENSE file in the root directory of this source tree. An additional grant
/// of patent rights can be found in the PATENTS file in the same directory.

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFListDiff.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFListDiff.h"
#endif

/// Bitmask-able options used for pre-release feature testing.
typedef NS_OPTIONS(NSInteger, PSPDFListExperiment) {
    /// Specifies no experiements.
    PSPDFListExperimentNone = 1 << 1,
};

/// Check if an experiment is enabled in a bitmask.
///
/// @param mask   The bitmask of experiments.
/// @param option The option to compare with.
///
/// @return `true` if the option is in the bitmask, otherwise `false`.
static inline BOOL PSPDFListExperimentEnabled(PSPDFListExperiment mask, PSPDFListExperiment option) { return (mask & option) != 0; }

NS_ASSUME_NONNULL_BEGIN

/// Performs an index diff with an experiment bitmask.
///
/// @param oldArray    The old array of objects.
/// @param newArray    The new array of objects.
/// @param option      Option to specify the type of diff.
/// @param experiments Optional experiments.
///
/// @return An index set result object contained the changed indexes.
///
/// @see `PSPDFListDiff()`.
PSPDF_APP_EXPORT PSPDFListIndexSetResult *PSPDFListDiffExperiment(NSArray<id<PSPDFListDiffable>> *_Nullable oldArray, NSArray<id<PSPDFListDiffable>> *_Nullable newArray, PSPDFListDiffOption option, PSPDFListExperiment experiments);

/// Performs a index path diff with an experiment bitmask.
///
/// @param fromSection The old section.
/// @param toSection   The new section.
/// @param oldArray    The old array of objects.
/// @param newArray    The new array of objects.
/// @param option      Option to specify the type of diff.
/// @param experiments Optional experiments.
///
/// @return An index path result object containing the changed indexPaths.
///
/// @see `PSPDFListDiffPaths()`.
PSPDF_APP_EXPORT PSPDFListIndexPathResult *PSPDFListDiffPathsExperiment(NSInteger fromSection, NSInteger toSection, NSArray<id<PSPDFListDiffable>> *_Nullable oldArray, NSArray<id<PSPDFListDiffable>> *_Nullable newArray, PSPDFListDiffOption option, PSPDFListExperiment experiments);

NS_ASSUME_NONNULL_END
