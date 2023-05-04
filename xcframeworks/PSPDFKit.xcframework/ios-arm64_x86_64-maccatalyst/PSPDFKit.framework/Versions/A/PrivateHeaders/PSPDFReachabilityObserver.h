//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFReachabilityStatus.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFReachabilityStatus.h"
#endif

/// Posted when the reachability changes.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFReachabilityDidChangeNotification;

PSPDF_TEST_CLASS_SWIFT(ReachabilityObserver)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFReachabilityObserver : NSObject

/// The current reachability. This property is only meaningful if `startObserving` has been called.
@property (nonatomic, readonly) PSPDFReachability reachability;

/// Returns YES if the reachability is either `PSPDFReachabilityStatusWiFi` or `PSPDFReachabilityStatusWWAN`.
@property (nonatomic, readonly, getter=isReachable) BOOL reachable;

/// Returns the default reachability observer.
+ (instancetype)defaultObserver;

/// Returns a reachability observer that traces the server hosting the specified URL.
///
/// Use this method to observe the reachability of a specific host.
///
/// @warning Asserts that the URL has a `host`.
/// @param hostURL A URL hosted by the server you want to track.
+ (instancetype)observerForURL:(NSURL *)hostURL;

/// Starts observing the reachability. This method is stack-based, so multiple calls are fine.
- (void)startObserving;

/// Stops observing the reachability. This method is stack-based, so multiple calls
/// (as long as they are balanced with `startObserving`) are fine.
- (void)stopObserving;

@end

/// Convenience tracker that uses the `defaultObserver` internally.
PSPDF_SDK_CLASS_SWIFT(ReachabilityTracker)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFReachabilityTracker : NSObject

/// `reachabilityBlock` will be executed once reachability changes in a way where it becomes reachable.
+ (instancetype)trackReachabilityWithBlock:(void (^)(void))reachabilityBlock;

@end
