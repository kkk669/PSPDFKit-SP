//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFDispatchQueue;

/// Sent when core has calculated different tab order.
extern NSNotificationName const PSPDFFormTabOrderUpdated;

/// Sent when core finds a new field.
extern NSNotificationName const PSPDFFormNewFieldFound;

/// Sent when we receive a core notification that we don't know about.
extern NSNotificationName const PSPDFUnknownCoreNotification;

/// The core notification name in the info dictionary.
extern NSString *const PSPDFUnknownCoreNotificationNameKey;

/// The `PSPDFCoreNotificationHandler` replaces the `PDFCFormNotificationsProviderIndexInfoKey` with a actual reference
/// to a `PSPDFDocumentProvider` stored under the following key.
extern NSString *const PSPDFResolvedDocumentProviderKey;

/// If there's a specific form field a notification refers to, the FQN will be set under the following key.
extern NSString *const PSPDFFormFieldFQN;

/// This class translates core notifications to platform notifications.
/// All notifications will be dispatched on a configurable queue using the `NSNotificationCenter`
@interface PSPDFCoreNotificationHandler : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the handler with a document and queue.
/// If queue is nil, a default, global notification queue will be used.
- (instancetype)initWithDocument:(PSPDFDocument *)document queue:(nullable PSPDFDispatchQueue *)queue NS_DESIGNATED_INITIALIZER;

/// The document we're dispatching events for.
@property (nonatomic, readonly, weak) PSPDFDocument *document;

/// The queue where we dispatch notifications.
@property (nonatomic, readonly) PSPDFDispatchQueue *queue;

@end

NS_ASSUME_NONNULL_END
