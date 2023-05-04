//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFContainerViewController.h>

/// Defines an adaptive value.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFViewVisibility) {
    /// The view is always hidden.
    PSPDFViewVisibilityNever,
    /// The view is always visible.
    PSPDFViewVisibilityAlways,
    /// The view is visible when appropriate.
    PSPDFViewVisibilityAdaptive
} PSPDF_ENUM_SWIFT(ViewVisibility);

@interface PSPDFContainerViewController ()

/// Setup the filter segmented control to switch between view controllers.
- (void)updateSelectionSegment;

/// Update the frame of the filter segmented control.
- (void)updateFilterSegmentFrame;

/// Defines if the container should use the title of the visible view controller
/// as it's own title, which will be shown in the navigation bar.
///
/// Uses KVO to determine when the title changed.
/// Defaults to YES.
@property (nonatomic, readonly) BOOL useVisibleViewControllerTitle;

/// Control if filter segment should be visible. Set before loading view. Defaults to `.adaptive`.
@property (nonatomic) PSPDFViewVisibility filterSegmentVisibilityMode;

@end
