//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFViewController, PSPDFScreenController;

PSPDF_PROTOCOL_SWIFT(ScreenControllerDelegate)
@protocol PSPDFScreenControllerDelegate<NSObject>

@optional

/// Started mirroring on `screen`.
///
/// This delegate is called after the `UIWindow` has been created and the `rootViewController` is configured.
/// Use this for additional customization.
///
/// @note Replacing the `rootViewController` on the mirroring window is supported,
/// as long as the `PDFViewController` is correctly registered as a child view controller.
///
/// Use `mirrorControllerForScreen:` to access the window if required.
- (void)screenController:(PSPDFScreenController *)screenController didStartMirroringForScreen:(UIScreen *)screen;

/// Stopped mirroring on `screen`.
///
/// This delegate is called after the mirroring window is hidden and is about to be deallocated.
- (void)screenController:(PSPDFScreenController *)screenController didStopMirroringForScreen:(UIScreen *)screen;

/// Implement this method to return a custom controller that should be used for mirroring.
/// If you return a custom controller, ensure that it is configured correctly.
///
/// This is called just before mirroring starts.
///
/// @note The default implementation uses various sensible options such as
/// hiding the thumbnail bar, document label and page label. It also completely mirrors the most relevant
/// configuration settings of the original controller.
///
/// @warning `PageTransition.scrollPerSpread` is the only supported page mode for mirroring currently.
///
/// Gallery considerations: We recommend at least following options to ensure the gallery works as expected:
/// `builder.allowPlayingMultipleInstances = YES;`
/// `builder.usesExternalPlaybackWhileExternalScreenIsActive = NO;`
/// See `galleryConfiguration` on `PDFConfiguration` for details.
- (PSPDFViewController *)createPDFViewControllerForMirroring:(PSPDFScreenController *)screenController;

/// This delegate can be used to decide whether the mirrored controller should copy the configuration of the original controller or not.
///
/// If not implemented, defaults to YES.
- (BOOL)screenController:(PSPDFScreenController *)screenController shouldSyncConfigurationTo:(PSPDFViewController *)mirroredPDFController;

@end

/// The screen controller will automatically watch for connected screens and external scenes
/// if the property `pdfControllerToMirror` is set, and will release such mirrors once
/// this property has been set to nil.
///
/// `UIWindow` objects are automatically created for each connected screen,
/// and destroyed once a screen is disconnected or `pdfControllerToMirror` is set to nil.
///
/// @note Use this class from the main thread only.
PSPDF_CLASS_SWIFT(ScreenController)
@interface PSPDFScreenController : NSObject

/// Attach a pdf controller to automatically start mirroring.
/// Set to nil to stop mirroring again. View position is kept automatically in sync.
///
/// @note This should be the controller you show on the device.
/// This class will automatically create a managed copy and mirrors the position.
@property (nonatomic, nullable) PSPDFViewController *pdfControllerToMirror;

/// Returns the view controller for `screen` if mirrored.
- (nullable PSPDFViewController *)mirrorControllerForScreen:(UIScreen *)screen;

/// Delegate that calls back when mirroring is started or stopped.
///
/// @note This delegate is not used by PSPDFKit and can be used freely to customize the screen mirroring
@property (nonatomic, weak) id<PSPDFScreenControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
