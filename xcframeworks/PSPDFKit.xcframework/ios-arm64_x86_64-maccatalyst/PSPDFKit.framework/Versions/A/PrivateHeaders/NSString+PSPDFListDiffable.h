/// Copyright (c) 2016-present, Facebook, Inc.
/// All rights reserved.
///
/// This source code is licensed under the BSD-style license found in the
/// LICENSE file in the root directory of this source tree. An additional grant
/// of patent rights can be found in the PATENTS file in the same directory.

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFListDiffable.h>
#else
#import "PSPDFEnvironment.h"
#import "PSPDFListDiffable.h"
#endif

/// This category provides default `PSPDFListDiffable` conformance for `NSString`.
@interface NSString (PSPDFListDiffable) <PSPDFListDiffable>

@end
