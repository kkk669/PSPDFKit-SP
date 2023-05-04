//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFGalleryContentViewProtocols.h>

NS_ASSUME_NONNULL_BEGIN

/// `PSPDFGalleryContainerViewContentState` controls which content view will be visible.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFGalleryContainerViewContentState) {
    /// The content is currently loading.
    PSPDFGalleryContainerViewContentStateLoading,

    /// The content is ready and presentable.
    PSPDFGalleryContainerViewContentStateReady,

    /// An error occurred.
    PSPDFGalleryContainerViewContentStateError
} PSPDF_ENUM_SWIFT(GalleryContainerView.ContentState);

/// `PSPDFGalleryContainerViewPresentationMode` controls which background view will be visible.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFGalleryContainerViewPresentationMode) {
    /// The embedded presentation mode.
    PSPDFGalleryContainerViewPresentationModeEmbedded,

    /// The fullscreen presentation mode.
    PSPDFGalleryContainerViewPresentationModeFullscreen
} PSPDF_ENUM_SWIFT(GalleryContainerView.PresentationMode);

@class PSPDFGalleryView, PSPDFCircularProgressView, PSPDFStatusHUDView;

// The following dummy classes are created to allow specific UIAppearance targeting.
// They do not have any functionality besides that.
PSPDF_CLASS_SWIFT(GalleryEmbeddedBackgroundView)
@interface PSPDFGalleryEmbeddedBackgroundView : UIView<PSPDFOverridable>
@end
PSPDF_CLASS_SWIFT(GalleryFullscreenBackgroundView)
@interface PSPDFGalleryFullscreenBackgroundView : UIView<PSPDFOverridable>
@end

/// Used to group the error, loading and gallery view and to properly lay them out.
PSPDF_CLASS_SWIFT(GalleryContainerView)
@interface PSPDFGalleryContainerView : UIView<PSPDFOverridable>

// MARK: State

/// The content state.
@property (nonatomic) PSPDFGalleryContainerViewContentState contentState;

/// The presentation mode.
@property (nonatomic) PSPDFGalleryContainerViewPresentationMode presentationMode;

// MARK: Subviews

/// The gallery view.
@property (nonatomic) PSPDFGalleryView *galleryView;

/// The loading view.
@property (nonatomic) UIView<PSPDFGalleryContentViewLoading> *loadingView;

/// The background view.
@property (nonatomic) PSPDFGalleryEmbeddedBackgroundView *backgroundView;

/// The fullscreen background view.
@property (nonatomic) PSPDFGalleryFullscreenBackgroundView *fullscreenBackgroundView;

/// The status HUD view.
@property (nonatomic) PSPDFStatusHUDView *statusHUDView;

/// This view conveniently groups together the `galleryView`, `loadingView` and `statusHUDView`.
@property (nonatomic, readonly) UIView *contentContainerView;

// MARK: HUD Presentation

/// Presents the HUD. After the given `timeout`, it will automatically be dismissed.
///
/// @note You can use a negative `timeout` to present the HUD indefinitely.
- (void)presentStatusHUDWithTimeout:(NSTimeInterval)timeout animated:(BOOL)animated;

/// Dismisses the HUD.
- (void)dismissStatusHUDAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
