//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>

@class PSPDFSoundAnnotation;
@class PSPDFSoundAnnotationPlaybackBottomController;
@class PSPDFSoundAnnotationPlaybackCoordinator;
@class PSPDFSoundAnnotationView;

NS_ASSUME_NONNULL_BEGIN

/// Delegate informing about playback changes.
@protocol PSPDFSoundAnnotationPlaybackCoordinatorDelegate

/// Called when the height of the sound annotation player changes.
- (void)soundAnnotationPlaybackCoordinator:(PSPDFSoundAnnotationPlaybackCoordinator *)soundAnnotationPlaybackCoordinator didChangePlayerHeightFrom:(CGFloat)oldPlayerHeight toPlayerHeight:(CGFloat)newPlayerHeight;

/// Called when the bottom controller will be shown and should be added to the view hierarchy.
- (void)soundAnnotationPlaybackCoordinator:(PSPDFSoundAnnotationPlaybackCoordinator *)soundAnnotationPlaybackCoordinator bottomControllerWillBeShown:(PSPDFSoundAnnotationPlaybackBottomController *)bottomController;

/// Called when the bottom controller was hidden and should be removed from the view hierarchy.
- (void)soundAnnotationPlaybackCoordinator:(PSPDFSoundAnnotationPlaybackCoordinator *)soundAnnotationPlaybackCoordinator bottomControllerDidHide:(PSPDFSoundAnnotationPlaybackBottomController *)bottomController;

@end

/// Controller used for sound annotation playback controlling.
/// Determines which player to use and responsible for showing and hiding the appropriate one.
@interface PSPDFSoundAnnotationPlaybackCoordinator : NSObject

/// Determines which sound player will be shown.
/// `soundAnnotationView` if `PSPDFSoundAnnotationPlayerStyleInline`: , or `soundAnnotationPlaybackBottomController` if `PSPDFSoundAnnotationPlayerStyleBottom`.
/// Set via `-[PSPDFConfiguration soundAnnotationPlayerStyle]`.
@property (nonatomic) PSPDFSoundAnnotationPlayerStyle soundAnnotationPlayerStyle;

/// Associated sound annotation view. Used to get the sound annotation.
/// Depending on `soundAnnotationPlayerStyle`, also used for playback.
@property (nonatomic, weak) PSPDFSoundAnnotationView *soundAnnotationView;

/// Bottom sound playback controller. Used if `soundAnnotationPlayerStyle` is set to `PSPDFSoundAnnotationPlayerStyleBottom`. Otherwise `nil`.
@property (nonatomic, readonly, nullable) PSPDFSoundAnnotationPlaybackBottomController *soundAnnotationPlaybackBottomController;

/// Delegate informing about changes.
@property (nonatomic, weak) id<PSPDFSoundAnnotationPlaybackCoordinatorDelegate> delegate;

/// Shows or hides the appropriate sound annotation player. Optionally animated.
- (void)setPlayerShown:(BOOL)playerShown animated:(BOOL)animated;

/// Returns `true` if the sound annotation player is shown, otherwise `false`.
@property (nonatomic, readonly, getter=isPlayerShown) BOOL playerShown;

/// The height of the sound annotation player.
/// Doesn't change depending on if the sound player is visible or not.
@property (nonatomic, readonly) CGFloat playerHeight;

/// The current bottom height of the sound player.
/// Only has a value greater than 0 if `soundAnnotationPlayerStyle` is `PSPDFSoundAnnotationPlayerStyleBottom`.
/// Changes depending on if the sound player is visible or not.
/// Otherwise, always 0.
@property (nonatomic, readonly) CGFloat currentBottomPlayerHeight;

@end

NS_ASSUME_NONNULL_END
