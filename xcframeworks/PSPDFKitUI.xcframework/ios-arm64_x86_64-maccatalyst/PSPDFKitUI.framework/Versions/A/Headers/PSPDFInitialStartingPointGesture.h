//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Protocol for gesture recognizers to indicate that they remember
/// the starting point of the first touch event they receive.
PSPDF_PROTOCOL_SWIFT(InitialStartingPointGesture)
@protocol PSPDFInitialStartingPointGesture

/// Helper for getting the actual initial starting point of the gesture.
///
/// Can be used instead of `locationInView:` when in the UIGestureRecognizerStateBegan state,
/// to get the location of the first touch the gesture received,
/// instead of the location where the gesture has been detected as started.
///
/// @note If that point hasn't been determined yet, falls back to the current location.
- (CGPoint)initialOrCurrentLocationInView:(nullable UIView *)view;

@end

NS_ASSUME_NONNULL_END
