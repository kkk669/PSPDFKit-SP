//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Manages the audio session used in PSPDFKit for sound annotations, media playback and speech synthesis.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AudioSessionManager)
@interface PSPDFAudioSessionManager : NSObject

// MARK: Managing recorders

/// Register an object as recorder and reconfigure the audio session.
///
/// @note Objects are registered weakly. Thread safe.
- (void)addRecorder:(id)recorder;

/// Remove an object as recorder and reconfigure the audio session.
///
/// @note Thread safe.
- (void)removeRecorder:(id)recorder;

// MARK: Managing players

/// Register an object as a player and reconfigure the audio session.
///
/// @note Objects are registered weakly. Thread safe.
- (void)addPlayer:(id)player;

/// Remove an object as a player and reconfigure the audio session.
///
/// @note Thread safe.
- (void)removePlayer:(id)player;

@end

NS_ASSUME_NONNULL_END
