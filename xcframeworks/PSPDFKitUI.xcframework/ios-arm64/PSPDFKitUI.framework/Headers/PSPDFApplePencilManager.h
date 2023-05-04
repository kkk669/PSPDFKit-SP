//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFApplePencilController.h>

NS_ASSUME_NONNULL_BEGIN

/// Notification posted on the main thread whenever `detected` is set to `true` even if it was `true` before.
PSPDF_EXPORT NSNotificationName const PSPDFApplePencilDetectedNotification;

/// Notification posted on the main thread whenever `enabled` is updated.
PSPDF_EXPORT NSNotificationName const PSPDFApplePencilEnabledChangedNotification;

/// Tracks the state of use of the Apple Pencil.
///
/// This class should not be instantiated manually but fetched from the `PSPDFKitGlobal` shared object.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ApplePencilManager)
@interface PSPDFApplePencilManager : NSObject

/// Whether or not an Apple Pencil has been detected by the system.
///
/// PSPDFKit automatically sets this to `true` when an Apple Pencil is used to draw,
/// or select annotations in a document.
@property (nonatomic) BOOL detected;

/// If `true`, sets `enabled` to `true` whenever `PSPDFApplePencilDetectedNotification`
/// is posted, resulting in enabling Apple Pencil whenever a touch from one is detected.
///
/// Defaults to `true`.
///
/// @note Setting this property does not directly set `enabled`, so if you want to disable Apple Pencil
/// and disable automatic enabling, you should set both properties to `false`, and if you want to enable
/// Apple Pencil immediately and re-enable automatic enabling, you should set both properties to `true`.
@property (nonatomic) BOOL enableOnDetection;

/// Enables/disables the use of the Apple Pencil, if it has been detected.
@property (nonatomic) BOOL enabled;

@end

NS_ASSUME_NONNULL_END
