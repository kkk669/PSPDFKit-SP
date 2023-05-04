//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFSoundAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

/// Protocol for displaying a sound annotation player.
@protocol PSPDFSoundAnnotationPlayback <NSObject>

/// Associated sound annotation.
@property (nonatomic, weak) PSPDFSoundAnnotation *soundAnnotation;

/// Shows or hides the sound annotation player. Optionally, animated.
- (void)setSoundAnnotationPlayerShown:(BOOL)soundAnnotationPlayerShown animated:(BOOL)animated completion:(void (^_Nullable)(BOOL finished))completionBlock;

/// Returns `true` if the sound annotation player is shown, otherwise `false`.
@property (nonatomic, readonly, getter=isSoundAnnotationPlayerShown) BOOL soundAnnotationPlayerShown;

@end

NS_ASSUME_NONNULL_END
