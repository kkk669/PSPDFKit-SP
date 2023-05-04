//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFAnnotationView.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationPlayback.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSoundAnnotationPlaybackCoordinator;

/// Displays and manages a sound annotation.
PSPDF_TEST_CLASS_SWIFT(SoundAnnotationView)
@interface PSPDFSoundAnnotationView : PSPDFAnnotationView<PSPDFSoundAnnotationPlayback, PSPDFOverridable>

/// Manually controlling the if the sound view button should be highlighted.
/// Used when `PSPDFSoundAnnotationPlaybackBottomController` is shown.
@property (nonatomic) BOOL shouldHighlightButton;

/// Associated sound playback controller.
/// Used for showing the sound player when the sound annotation view will be shown.
@property (nonatomic, weak) PSPDFSoundAnnotationPlaybackCoordinator *soundAnnotationPlaybackCoordinator;

@end

NS_ASSUME_NONNULL_END
