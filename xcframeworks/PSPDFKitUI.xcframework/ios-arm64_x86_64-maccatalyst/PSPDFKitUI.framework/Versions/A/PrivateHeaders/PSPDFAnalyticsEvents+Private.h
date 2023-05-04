//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnalyticsEvents.h>

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbar.h>

@class PSPDFDocument;
@class PSPDFAnnotation;

NS_ASSUME_NONNULL_BEGIN

/// Private convenience category for log events methods. Encapsulates analytics events creation code.
PSPDF_SDK_VISIBLE
@interface PSPDFAnalyticsEvents : NSObject

+ (void)logEvent:(PSPDFAnalyticsEventName)event;

+ (void)logDocumentLoad:(PSPDFDocument *)document;

+ (void)logAnnotationsSelect:(NSArray<PSPDFAnnotation *> *)annotations;
+ (void)logAnnotationsCreate:(NSArray<PSPDFAnnotation *> *)annotations;
+ (void)logAnnotationsDelete:(NSArray<PSPDFAnnotation *> *)annotations;

+ (void)logDocumentEditorAction:(PSPDFAnalyticsEventAttributeValue)action;

+ (void)logOutlineAnnotationSelect:(PSPDFAnnotation *)annotation;

+ (void)logShare:(NSString *)activityType;

+ (void)logToolbarMove:(PSPDFFlexibleToolbarPosition)toolbarPosition;

+ (void)logSpreadChangeFromSpreadIndex:(NSInteger)oldSpreadIndex toSpreadIndex:(NSInteger)spreadIndex;

@end

NS_ASSUME_NONNULL_END
