//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Broadcasts that media playback is about to start.
///
/// @note Those notifications can be invoked on a private queue. To ensure callbacks are done on the main thread use `pspdf_registerForMediaPlaybackNotifications` .
PSPDF_EXPORT NSNotificationName const PSPDFMediaPlaybackWillStartNotification;

@protocol PSPDFMediaPlaybackNotificationObserver <NSObject>

/// This is useful to stop current playback if other player is about to start playing.
- (void)mediaPlaybackWillStartNotification:(NSNotification *)notification;

@end

@interface NSNotificationCenter (PSPDFMediaPlayback)

/// Convenience method to register for PSPDFMediaPlayback notifications.
/// Guarantees that mediaPlaybackWillStartNotification: is called on the main queue.
- (void)pspdf_registerForMediaPlaybackNotifications:(id<PSPDFMediaPlaybackNotificationObserver>)observer;

/// Convenience method to unregister for PSPDFMediaPlayback notifications.
- (void)pspdf_unregisterFromMediaPlaybackNotifications:(id<PSPDFMediaPlaybackNotificationObserver>)observer;

@end

NS_ASSUME_NONNULL_END
