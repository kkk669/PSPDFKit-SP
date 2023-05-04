//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Detects any iPad.
PSPDF_APP_EXPORT BOOL PSPDFIsiPad(void) NS_SWIFT_NAME(isiPad());

/// Returns YES if the application is compiled as Mac Catalyst. Useful in Swift code as a boolean check.
PSPDF_APP_EXPORT BOOL PSPDFIsMacCatalyst(void) NS_SWIFT_NAME(isMacCatalyst());

/// Returns YES if the application is compiled as Mac Catalyst and running on macOS Big Sur 11.0 AND using Optimized for Mac Idiom.
PSPDF_APP_EXPORT BOOL PSPDFIsMacCatalystOptimized(void) NS_SWIFT_NAME(isMacCatalystOptimized());

/// Returns YES if the application runs as iOS app on Mac (Only possible with Apple Silicon)
PSPDF_APP_EXPORT BOOL PSPDFIsiOSAppOnMac(void) NS_SWIFT_NAME(isiOSAppOnMac());

/// Simulator detection.
PSPDF_APP_EXPORT BOOL PSPDFIsSimulator(void) NS_SWIFT_NAME(isSimulator());

/// Returns YES if this instance is a development build. Will always return YES in the Simulator.
PSPDF_EXTERN BOOL PSPDFIsDevelopmentBuild(void) NS_SWIFT_NAME(isDevelopmentBuild());

/// Detect if we run inside an app extension.
PSPDF_SDK_EXPORT BOOL PSPDFRunningInAppExtension(void) NS_SWIFT_NAME(isRunningInAppExtension());

/// Checks if `key` is set inside the main bundle info dictionary.
/// `reason` will be part of the explanatory log message.
PSPDF_SDK_EXPORT BOOL PSPDFCheckUsageDescriptionKey(NSString *key, NSString *reason);

NS_ASSUME_NONNULL_END
