//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFStackViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_CLASS_SWIFT(ContinuousScrollingLayout)
@interface PSPDFContinuousScrollingLayout : PSPDFStackViewLayout

/// Ensures that the space alongside the transverse axis (the axis orthogonal to the
/// scroll direction) is fully used by the page. When enabling this, spreads might
/// not fully fit the screen and the user needs to scroll to completely see the spread.
///
/// This means, when in horizontal scroll directions all spreads will have the height
/// of the surrounding scroll view even though that means they become wider than the
/// visible screen. For vertical scroll direction the opposite is the case: all spreads
/// will have the width of the surrounding scroll view even though that means that
/// tall pages might not entirely fit the visible screen and the user needs to scroll
/// to completely see the page.
@property (nonatomic) BOOL fillAlongsideTransverseAxis;

@end

NS_ASSUME_NONNULL_END
