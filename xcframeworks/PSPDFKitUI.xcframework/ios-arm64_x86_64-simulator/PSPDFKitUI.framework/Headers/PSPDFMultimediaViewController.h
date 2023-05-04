//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAction, PSPDFConfiguration;

/// A protocol that defines the interface that multimedia view controller plugins must conform to.
///
/// @warning The class that implements this protocol must be a `UIViewController` subclass!
PSPDF_PROTOCOL_SWIFT(MultimediaViewController)
@protocol PSPDFMultimediaViewController<NSObject>

/// Indicates if the controller is currently in fullscreen mode or changes the state.
@property (nonatomic, getter=isFullscreen) BOOL fullscreen;

/// Specifies whether the receiver is visible. In regular operation, this will be set by its owner.
/// There are cases where-in you might want to alter behaviour based on the receiver's visibility.
@property (nonatomic, getter=isVisible) BOOL visible;

/// Toggle fullscreen presentation, optionally animated
- (void)setFullscreen:(BOOL)fullscreen animated:(BOOL)animated;

/// The zoom scale at which the controller is presented.
@property (nonatomic) CGFloat zoomScale;

/// The delegate that can be used to override classes.
@property (nonatomic, weak) id overrideDelegate;

/// Called when a multimedia action (either `PSPDFRenditionAction` or `PSPDFRichMediaExecuteAction`)
/// should be performed.
- (void)performAction:(PSPDFAction *)action;

@optional

/// Configures the controller with the given `PDFConfiguration`.
- (void)configure:(PSPDFConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
