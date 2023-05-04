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

/// The `PSPDFListDiffable` protocol provides methods needed to compare the identity and equality of two objects.
@protocol PSPDFListDiffable

/// Returns a key that uniquely identifies the object.
///
/// @return A key that can be used to uniquely identify the object.
///
/// @note Two objects may share the same identifier, but are not equal. A common pattern is to use the `NSObject`
/// category for automatic conformance. However this means that objects will be identified on their
/// pointer value so finding updates becomes impossible.
///
/// @warning This value should never be mutated.
@property (nonatomic, readonly, nonnull) id<NSObject> diffIdentifier;

/// Returns whether the receiver and a given object are equal.
///
/// @param object The object to be compared to the receiver.
///
/// @return `true` if the receiver and object are equal, otherwise `false`.
- (BOOL)isEqualToDiffableObject:(nullable id<PSPDFListDiffable>)object;

@end
