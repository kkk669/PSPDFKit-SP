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

/// Does a binary search in a given index range and calls a compare block for every
/// index it is checking.
///
/// This is an abstract binary search that works with every set of data that can be
/// represeted in an integer based way.
///
/// The searched range is [first, last).
///
/// @param first The first index to check for.
/// @param last The last item (this item is not checked).
/// @param compare The compare block to be executed, passing in the element to compare
/// what you are looking for against. The result expresses the order
/// of current..target.
/// @return The integer that matches the value you are looking for or the index where
/// the element you are looking for should be added if no matching item was
/// found.
PSPDF_SDK_EXPORT NSInteger PSPDFBinaryIndexSearch(NSInteger first, NSInteger last, NSComparisonResult(^compare)(NSInteger current));

NS_ASSUME_NONNULL_END
