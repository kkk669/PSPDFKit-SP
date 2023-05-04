//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

typedef NS_CLOSED_ENUM(NSInteger, PSPDFFeedbackType) {
    PSPDFFeedbackTypeLightImpact,
    PSPDFFeedbackTypeMediumImpact,
    PSPDFFeedbackTypeHeavyImpact,
    PSPDFFeedbackTypeSuccessNotification,
    PSPDFFeedbackTypeWarningNotification,
    PSPDFFeedbackTypeErrorNotification,
    PSPDFFeedbackTypeSelectionChanged,
};

PSPDF_APP_CLASS_SWIFT(FeedbackGenerator)
@interface PSPDFFeedbackGenerator : NSObject

- (void)generateFeedbackOfType:(PSPDFFeedbackType)feedbackType;

- (void)generateFeedbackForSelectingPageIndex:(PSPDFPageIndex)pageIndex withDocumentPageCount:(PSPDFPageCount)pageCount;

@end
