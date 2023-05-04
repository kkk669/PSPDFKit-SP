//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFSoundAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

#define PSPDF_HAS_RECORDING_FEATURE TARGET_OS_IOS || TARGET_OS_OSX

/// Posted when recording or playback is started, paused or stopped.
PSPDF_EXPORT NSNotificationName const PSPDFSoundAnnotationChangedStateNotification;

/// Posted when `+stopRecordingOrPlaybackForAllExcept:` is invoked.
PSPDF_EXPORT NSNotificationName const PSPDFSoundAnnotationStopAllNotification;

/// Sound annotation recording and playback states.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFSoundAnnotationState) {
    /// Stopped state.
    PSPDFSoundAnnotationStateStopped = 0,
    /// Recording state.
    PSPDFSoundAnnotationStateRecording,
    /// Recording paused state.
    PSPDFSoundAnnotationStateRecordingPaused,
    /// Recording finished state.
    PSPDFSoundAnnotationStateRecordingFinished,
    /// Playing state.
    PSPDFSoundAnnotationStatePlaying,
    /// Playing paused state.
    PSPDFSoundAnnotationStatePlaybackPaused,
} PSPDF_ENUM_SWIFT(SoundAnnotation.State);

/// Manages sound playback for sound annotations.
PSPDF_CLASS_SWIFT(SoundAnnotationController)
@interface PSPDFSoundAnnotationController : NSObject

/// Stops any currently active recording or playback, except the sender.
/// If the sender is nil, all annotations are stopped.
+ (void)stopRecordingOrPlaybackForAllExcept:(nullable id)sender;

/// Checks if we have permission to record.
+ (void)requestRecordPermission:(nullable void (^)(BOOL granted))block;

PSPDF_EMPTY_INIT_UNAVAILABLE

- (instancetype)initWithSoundAnnotation:(PSPDFSoundAnnotation *)annotation NS_DESIGNATED_INITIALIZER;

/// The controlled sound annotation.
@property (nonatomic, weak, readonly) PSPDFSoundAnnotation *annotation;

/// The current playback state.
@property (nonatomic, readonly) PSPDFSoundAnnotationState state;

/// The duration of the audio playback
@property (nonatomic, readonly) NSTimeInterval playbackDuration;

/// Starts or resumes playback.
- (BOOL)startPlayback:(NSError **)error;

/// Pauses playback or recording.
- (void)pause;

/// Stops playback or recording.
- (BOOL)stop:(NSError **)error;

/// The audio player object. Only available if playback is ongoing or prepared.
@property (nonatomic, readonly, nullable) AVAudioPlayer *audioPlayer;

#if PSPDF_HAS_RECORDING_FEATURE

/// Starts or resumes recording.
- (BOOL)startRecording:(NSError **)error;

/// Discards the current recording.
- (void)discardRecording;

#endif

@end

NS_ASSUME_NONNULL_END
