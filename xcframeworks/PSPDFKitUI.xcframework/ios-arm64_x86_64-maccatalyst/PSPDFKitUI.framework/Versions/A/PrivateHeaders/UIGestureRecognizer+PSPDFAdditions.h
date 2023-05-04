//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Return `true` if the given `state` is either began or changed.
PSPDF_EXTERN BOOL PSPDFGestureRecognizerStateIsInProgress(UIGestureRecognizerState state) NS_REFINED_FOR_SWIFT;

/// Returns `true` if the given `state` is ended, failed or cancelled.
PSPDF_EXTERN BOOL PSPDFGestureRecognizerStateIsTerminal(UIGestureRecognizerState state) NS_REFINED_FOR_SWIFT;

/// Return `true` if the given `state` is either failed or cancelled.
PSPDF_EXTERN BOOL PSPDFGestureRecognizerStateIsInterrupted(UIGestureRecognizerState state) NS_REFINED_FOR_SWIFT;

NS_ASSUME_NONNULL_END
