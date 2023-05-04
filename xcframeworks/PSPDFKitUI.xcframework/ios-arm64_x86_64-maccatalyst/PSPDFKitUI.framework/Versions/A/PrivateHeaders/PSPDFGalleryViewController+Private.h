//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFGalleryViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFGalleryContainerView, PSPDFFullscreenTransitionViewController;

@interface PSPDFGalleryViewController ()

/// Convenience getter to the current media player.
- (nullable PSPDFMediaPlayerController *)currentMediaPlayerController;

/// The container view responsible for displaying the current state.
@property (nonatomic) PSPDFGalleryContainerView *containerView;

/// Handles transitioning between fullscreen and in-page mode.
@property (nonatomic) PSPDFFullscreenTransitionViewController *fullscreenController;

@end

NS_ASSUME_NONNULL_END
