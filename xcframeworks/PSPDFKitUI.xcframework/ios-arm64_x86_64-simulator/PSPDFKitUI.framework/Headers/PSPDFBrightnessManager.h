//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Controls if and how the idle timer should be managed.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFIdleTimerManagement) {
    /// Don't allow managing the idle timer.
    PSPDFIdleTimerManagementManual,
    /// Extend the idle timer time by `extendedIdleTime`. Only honored if `PDFViewController` is on screen.
    PSPDFIdleTimerManagementExtendedTime,
    /// Like `PSPDFIdleTimerManagementExtendedTime` but also keeps screen screen always on when an external screen is detected.
    PSPDFIdleTimerManagementExtendedTimeExternalScreenDisablesTimer,
    /// Keeps screen awake as long as  `PDFViewController` is on screen.
    PSPDFIdleTimerManagementDisablesTimer
} PSPDF_ENUM_SWIFT(PSPDFBrightnessManager.IdleTimerManagement);

/// `PSPDFBrightnessManager` can be used to manage the screen idle timer.
PSPDF_CLASS_SWIFT(BrightnessManager)
@interface PSPDFBrightnessManager : NSObject

/// Controls how the idle timer (`idleTimerDisabled`) should be managed, or if you handle this manually.
/// Defaults to `PSPDFIdleTimerManagementManual`.
@property (nonatomic) PSPDFIdleTimerManagement idleTimerManagement;

/// Time in seconds in which the default idle time should be extended.
/// Defaults to 10 * 60 = 10 minutes.
///
/// @note Setting this will re-set the idle timer to the new time.
@property (nonatomic) NSTimeInterval extendedIdleTime;

@end

NS_ASSUME_NONNULL_END
