//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFMediaPlayerController.h>

@class PSPDFMediaPlayerView;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFMediaPlayerController ()

/// The player view managed by the media controller. Defaults to `nil`.
@property (nonatomic, nullable) PSPDFMediaPlayerView *view;

/// Setup the player for playback.
- (void)prepareForPlayback;

/// Sets the volume for all instances to 1.
+ (void)turnUpVolumeForAllInstances;

@end

NS_ASSUME_NONNULL_END
