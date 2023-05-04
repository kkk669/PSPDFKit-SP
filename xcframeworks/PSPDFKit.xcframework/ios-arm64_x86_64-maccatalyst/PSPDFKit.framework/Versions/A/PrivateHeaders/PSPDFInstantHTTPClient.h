//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
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
/**
 Adapts the Djinni generated HTTPClient API to NSURLSession.
 */
PSPDF_SDK_CLASS_SWIFT(InstantHTTPClient)
@interface PSPDFInstantHTTPClient : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/**
 Returns a newly created HTTP client object.

 @note **Important:**
 Although not a singleton, HTTP clients keep themselves alive until they have been invalidated.
 If you fail to do so, the application leaks memory.
 */
+ (instancetype)client;

/**
 Returns a newly created HTTP client object that includes the specified headers with every request.
 */
+ (instancetype)clientWithAdditionalHeaders:(NSDictionary<NSString *, NSString *> *)additionalHeaders;

/**
 Invalidates the receiver, breaking the strong reference cycle that would otherwise keep it alive, and cancels all pending/running requests.

 @warning Calling any method from the `PDFIHTTPClient` protocol on the object after invalidating it raises an exception.
 */
- (void)invalidate;

@end
NS_ASSUME_NONNULL_END
