//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationPlaybackController.h>

NS_ASSUME_NONNULL_BEGIN

/// Style of the sound annotation playback view.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSoundAnnotationPlaybackViewStyle) {
    /// Light style.
    PSPDFSoundAnnotationPlaybackViewStyleLight,
    /// Dark style.
    PSPDFSoundAnnotationPlaybackViewStyleDark,
} NS_SWIFT_NAME(SoundAnnotationPlaybackViewStyle);

/// View used for the bottom sound annotation player. Ignores its `backgroundColor` and sets it to transparent. Uses a blurred background with the style of `style`.
PSPDF_APP_CLASS_SWIFT(SoundAnnotationPlaybackBarView)
@interface PSPDFSoundAnnotationPlaybackBarView : PSPDFSoundAnnotationPlaybackView

/// Determines the style of the blurred background. Defaults to light style.
/// Does not do anything on iOS 13 and above as the UI is styled based on the `traitCollection`.
@property (nonatomic) PSPDFSoundAnnotationPlaybackViewStyle style UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END
