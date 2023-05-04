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

/// Names of analytics events.
typedef NSString *PSPDFAnalyticsEventName NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(PDFAnalytics.EventName);

/// Names of attributes for an analytics event.
typedef NSString *PSPDFAnalyticsEventAttributeName NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(PDFAnalytics.EventAttributeName);

/// Values for an analytics event attribute.
typedef NSString *PSPDFAnalyticsEventAttributeValue NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(PDFAnalytics.EventAttributeValue);

/// Protocol for analytics events consumers.
/// Implement this protocol to forward analytics events to an analytics service of your choice.
/// To receive events you must register your `PSPDFAnalyticsClient` instance with `-[PSPDFAnalytics addAnalyticsClient:]` method.
PSPDF_PROTOCOL_SWIFT(PDFAnalyticsClient)
@protocol PSPDFAnalyticsClient

/// This method is called when an analytics event occurs.
///
/// @param event      event name
/// @param attributes event attributes
- (void)logEvent:(PSPDFAnalyticsEventName)event attributes:(nullable NSDictionary<NSString *, id> *)attributes;

@end

/// This is a PSPDFKit provided `PSPDFAnalyticsClient` implementation that dispatches events to all registered clients.
/// Events are dispatched on a background queue.
PSPDF_CLASS_SWIFT(PDFAnalytics)
@interface PSPDFAnalytics : NSObject<PSPDFAnalyticsClient>

/// Events will be dispatched only if `enabled` is set to `true`. Defaults to `false`.
@property (nonatomic) BOOL enabled;

/// Register your `PSPDFAnalyticsClient` instance to start receiving events.
- (void)addAnalyticsClient:(id<PSPDFAnalyticsClient>)analyticsClient;

/// Unregister your `PSPDFAnalyticsClient` instance to stop receiving events.
- (void)removeAnalyticsClient:(id<PSPDFAnalyticsClient>)analyticsClient;

/// Convenience method for events without additional attributes.
- (void)logEvent:(PSPDFAnalyticsEventName)event;

@end

NS_ASSUME_NONNULL_END
