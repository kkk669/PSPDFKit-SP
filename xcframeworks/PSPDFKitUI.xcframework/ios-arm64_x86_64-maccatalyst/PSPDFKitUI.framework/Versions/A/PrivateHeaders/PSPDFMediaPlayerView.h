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

@protocol PSPDFMediaPlayerViewDelegate;

typedef NS_CLOSED_ENUM(NSInteger, PSPDFMediaPlayerViewState) {
    /// Displays the cover view.
    PSPDFMediaPlayerViewStateIdle,

    /// Displays the loading view.
    PSPDFMediaPlayerViewStateLoading,

    /// Displays the error view.
    PSPDFMediaPlayerViewStateError,

    /// Displays the video view.
    PSPDFMediaPlayerViewStateReady
};

typedef NS_CLOSED_ENUM(NSInteger, PSPDFMediaPlayerViewControlEvent) {
    /// Indicates that the play control was triggered.
    PSPDFMediaPlayerViewControlEventPlay,

    /// Indicates that the pause control was triggered.
    PSPDFMediaPlayerViewControlEventPause,

    /// Indicates that the route selection (e.g. for AirPlay) was triggered.
    PSPDFMediaPlayerViewControlEventRouteOptions
};

@class PSPDFMediaPlayerVideoView, PSPDFMediaPlayerCoverView, PSPDFMediaPlayerPlaceholderView, PSPDFErrorView;

/// A view capable of displaying media. Use in combination with `AVPlayer`.
@interface PSPDFMediaPlayerView : UIView

// MARK: State

/// The current state. Controls which view is visible.
@property (nonatomic) PSPDFMediaPlayerViewState state;

/// The zoom scale. Set this property if the view is used in a `UIScrollView` to optimize
/// the way the view hierarchy is presented.
@property (nonatomic) CGFloat zoomScale;

/// The delegate.
@property (nonatomic, weak) id<PSPDFMediaPlayerViewDelegate> delegate;

// MARK: Subviews

/// The view used for displaying the video content.
@property (nonatomic, readonly) PSPDFMediaPlayerVideoView *videoView;

/// The cover view.
@property (nonatomic, readonly) PSPDFMediaPlayerCoverView *coverView;

/// The loading view.
@property (nonatomic, readonly) UIActivityIndicatorView *loadingView;

/// The error view.
@property (nonatomic, readonly) PSPDFErrorView *errorView;

@end

@protocol PSPDFMediaPlayerViewDelegate <NSObject>

// MARK: Control Events

/// Called when a control event should be performed.
- (void)mediaPlayerView:(PSPDFMediaPlayerView *)view performControlEvent:(PSPDFMediaPlayerViewControlEvent)controlEvent;

// MARK: Scrubbing

/// Called when the view begins scrubbing.
- (void)mediaPlayerViewDidBeginScrubbing:(PSPDFMediaPlayerView *)view;

/// Called when the view has scrubbed to the given time.
- (void)mediaPlayerView:(PSPDFMediaPlayerView *)view didScrubToTime:(NSTimeInterval)time;

/// Called when the view is done scrubbing.
- (void)mediaPlayerViewDidEndScrubbing:(PSPDFMediaPlayerView *)view;

@end

NS_ASSUME_NONNULL_END
