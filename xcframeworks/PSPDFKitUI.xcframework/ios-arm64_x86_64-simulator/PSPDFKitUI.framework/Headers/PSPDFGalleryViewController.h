//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFGalleryItem.h>
#import <PSPDFKitUI/PSPDFGalleryContainerView.h>
#import <PSPDFKitUI/PSPDFGalleryVideoItem.h>
#import <PSPDFKitUI/PSPDFMultimediaViewController.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFLinkAnnotation, PSPDFMediaPlayerController, PSPDFGalleryConfiguration, PSPDFFullscreenTransitionController;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFGalleryViewControllerState) {
    /// The view controller is currently not doing anything.
    PSPDFGalleryViewControllerStateIdle,

    /// The manifest file is currently downloaded.
    PSPDFGalleryViewControllerStateLoading,

    /// The manifest file has been downloaded and the view controller is ready.
    PSPDFGalleryViewControllerStateReady,

    /// The view controller could not load or parse the manifest file.
    PSPDFGalleryViewControllerStateError
} PSPDF_ENUM_SWIFT(GalleryViewController.State);

@class PSPDFGalleryViewController;

/// Handles a gallery of one or multiple images, videos, audio or even web content.
PSPDF_CLASS_SWIFT(GalleryViewController)
@interface PSPDFGalleryViewController : PSPDFBaseViewController<PSPDFOverridable, PSPDFMultimediaViewController>

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// Create a new gallery view controller by passing in a link annotation.
- (instancetype)initWithLinkAnnotation:(PSPDFLinkAnnotation *)linkAnnotation NS_DESIGNATED_INITIALIZER;

/// The configuration. Defaults to `+[PSPDFGalleryConfiguration defaultConfiguration]`.
@property (nonatomic) PSPDFGalleryConfiguration *configuration;

// MARK: State

/// The current state.
@property (nonatomic, readonly) PSPDFGalleryViewControllerState state;

/// All items of this gallery. Only set if state is `PSPDFGalleryViewControllerStateReady`.
@property (nonatomic, copy, readonly, nullable) NSArray<__kindof PSPDFGalleryItem *> *items;

/// The link annotation that was used to instantiate the view controller.
@property (nonatomic, readonly) PSPDFLinkAnnotation *linkAnnotation;

/// Used to enter or exit the fullscreen mode.
///
/// @see setFullscreen:animated:.
@property (nonatomic, getter=isFullscreen) BOOL fullscreen;

/// Specifies whether the receiver is visible. In regular operation, this will be set by its owner.
/// There are cases where-in you might want to alter behavior based on the receiver's visibility.
@property (nonatomic, getter=isVisible) BOOL visible;

/// Used to enter or exit the fullscreen mode with or without animation.
/// The transition is only initiated, if all gallery items support fullscreen presentation.
///
/// @warning If you use this property programmatically, you must set it to `false` once
/// you're done with your instance of `PSPDFGalleryViewController`!
- (void)setFullscreen:(BOOL)fullscreen animated:(BOOL)animated;

/// The current zoom scale. Only valid when displayed as an embedded gallery within a PDF document.
/// Defaults to 1.0.
@property (nonatomic) CGFloat zoomScale;

// MARK: Gesture Recognizers

/// Single-Tap: Show/Hide image description.
@property (nonatomic, readonly) UITapGestureRecognizer *singleTapGestureRecognizer;

/// Double-Tap: Toggle Full-Screen.
@property (nonatomic, readonly) UITapGestureRecognizer *doubleTapGestureRecognizer;

/// Pan: Dismiss Full-Screen mode.
@property (nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer;

@end

NS_ASSUME_NONNULL_END
