//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFSoundAnnotation.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationPlayback.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAudioPlotSampler;

/// Empty UIView subclass used as the view of the sound annotation player.
PSPDF_APP_CLASS_SWIFT(SoundAnnotationPlaybackView)
@interface PSPDFSoundAnnotationPlaybackView : UIView
@end

#define PSPDFSoundAnnotationRedColor [UIColor colorWithRed:1.0 green:0.251 blue:0.067 alpha:1.0]
#define PSPDFSoundAnnotationBlueColor [UIColor colorWithRed:0.0 green:0.659 blue:0.949 alpha:1.0]

/// Sound annotation player.
@interface PSPDFSoundAnnotationPlaybackController : UIViewController <PSPDFSoundAnnotationPlayback>

/// Associated sound annotation, where media should be recorded to/played from.
@property (nonatomic, weak) PSPDFSoundAnnotation *soundAnnotation;

/// Set to `true` if the user is currently scrubbing on the sound player.
@property (nonatomic) BOOL isScrubbing;

/// Insets that is applied to the subviews (buttons, plot view and labels) during layout. Defaults to 6, 6, 6, 6.
@property (nonatomic) UIEdgeInsets contentInset;

/// Stack view used for the views that are visible in the playback state.
@property (nonatomic) UIStackView *playbackStackView;

/// Used to create the samples for the audio plot views.
@property (nonatomic, readonly) PSPDFAudioPlotSampler *plotSampler;

/// Setup colors and images for the views. Override this method to customize colors.
- (void)updateControlsWithColor:(UIColor *)color borderColor:(UIColor *)borderColor;

@end

NS_ASSUME_NONNULL_END

