//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSpreadView.h>

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFPageView;

/// Sent out just before a page view will be added to the reuse queue.
PSPDF_EXTERN NSNotificationName const PSPDFSpreadViewWillReusePageViewNotification;

/// Sent out after page view's page and document are set, but before the page view is added.
PSPDF_EXTERN NSNotificationName const PSPDFSpreadViewDidConfigurePageViewNotification;

/// Key specifying the affected page view in PSPDFSpreadViewWillReusePageViewNotification
/// and PSPDFSpreadViewDidConfigurePageViewNotification.
PSPDF_EXTERN NSString *const PSPDFPageViewKey;

NS_ASSUME_NONNULL_END
