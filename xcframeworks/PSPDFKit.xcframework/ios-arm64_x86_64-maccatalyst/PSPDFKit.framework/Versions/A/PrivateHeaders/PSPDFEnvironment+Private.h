//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

// Enable Private API to improve features and to add various workarounds.
#define PSPDFKIT_ALLOW_PRIVATE_API 1

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFLogging+Private.h>
#import <PSPDFKit/PSPDFDispatch.h>
#import <PSPDFKit/PSPDFOverrideClass.h>
#import <PSPDFKit/NSArray+PSPDFFoundation.h>
#import <PSPDFKit/NSSet+PSPDFFoundation.h>
#import <PSPDFKit/NSOrderedSet+PSPDFFoundation.h>
#import <PSPDFKit/NSDictionary+PSPDFFoundation.h>
#import <PSPDFKit/PSPDFDispatchQueue.h>
#if TARGET_OS_OSX
#import <PSPDFKit/PSPDFMacOSCompatibility.h>
#else
#import <PSPDFKit/UIBezierPath+PSPDFMacOSCompatibility.h>
#endif
#else
#import "PSPDFEnvironment.h"
#import "PSPDFMacros+Private.h"
#import "PSPDFLogging+Private.h"
#import "PSPDFDispatch.h"
#import "ClassOverride/PSPDFOverrideClass.h"
#import "Categories/NSArray+PSPDFFoundation.h"
#import "Categories/NSSet+PSPDFFoundation.h"
#import "Categories/NSOrderedSet+PSPDFFoundation.h"
#import "Categories/NSDictionary+PSPDFFoundation.h"
#import "GCD/PSPDFDispatchQueue.h"
#if TARGET_OS_OSX
#import "macOS/PSPDFMacOSCompatibility.h"
#else
#import "macOS/UIBezierPath+PSPDFMacOSCompatibility.h"
#endif
#endif

NS_ASSUME_NONNULL_BEGIN

/// Executes given block as background task if supported on current platform and provides default expiration handler.
PSPDF_APP_EXPORT void PSPDFExecuteApplicationBackgroundTask(NSString *name, void(NS_NOESCAPE ^ block)(void(NS_NOESCAPE ^ completionBlock)(void))) NS_SWIFT_NAME(executeApplicationBackgroundTask(name:completionBlock:));

/// Always returns `false` on Mac and a result based on `UIApplicationState` on iOS.
///
/// Simplifies cross platform code.
PSPDF_APP_EXPORT BOOL PSPDFApplicationInBackground(void) NS_SWIFT_NAME(isApplicationInBackground());

/// Listens to `UI/NSApplicationWillTerminateNotification` and returns true if the application is being terminated.
///
/// Background threads can evaluate this to cancel what they do so they don't crash when calling into a semi-shutdown core. (Especially deallocated mutexes are dangerous).
///
/// @note Once this is set to YES, it will not be reset to NO, unless the app really restarts.
PSPDF_APP_EXPORT BOOL PSPDFApplicationIsTerminating(void) NS_SWIFT_NAME(isApplicationTerminating());

/// Returns YES if we're inside an XCTestCase.
PSPDF_APP_EXPORT BOOL PSPDFApplicationIsRunningTests(void) NS_SWIFT_NAME(isApplicationRunningTests());

/// Returns the slowest qualiy of service. Background for apps, Utility for tests.
PSPDF_TEST_EXPORT NSQualityOfService PSPDFSlowestQualityOfService(void) NS_SWIFT_NAME(slowestQualityOfService());

#define PSPDF_RETURN_EARLY_IF_APP_TERMINATING(returnValue) \
do { if (PSPDFApplicationIsTerminating()) { \
    PSPDFLogWarning(@"Skipping %@, app is shutting down.", NSStringFromSelector(_cmd)); \
return returnValue;}} while (0)

NS_ASSUME_NONNULL_END
