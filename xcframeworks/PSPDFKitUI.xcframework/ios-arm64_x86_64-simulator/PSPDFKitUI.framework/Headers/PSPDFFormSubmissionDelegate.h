//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFFormRequest, PSPDFFormSubmissionController;

NS_ASSUME_NONNULL_BEGIN

/// Delegate for form submission actions. When a form submission action is run, the delegate will be queried in this order:
/// 1.  `formSubmissionControllerShouldPresentResponseInWebView:` -- should the view controller push a web view with the received response data. If yes then the web view takes responsibility for the connection and call 4 is not made.
/// 2.  `formSubmissionController:shouldSubmitFormRequest:` -- if no then the operation is cancelled.
/// 3.  `formSubmissionController:willSubmitFormValues:`   -- the submission is going ahead.
/// 4.a `formSubmissionController:didReceiveResponseData:` -- the submission has completed successfully  OR
/// 4.b `formSubmissionController:didFailWithError:`       -- the submission has failed
PSPDF_PROTOCOL_SWIFT(PDFFormSubmissionDelegate)
@protocol PSPDFFormSubmissionDelegate<NSObject>

@optional

/// The user has activated a submission action, return to indicate whether it should be sent. Defaults to YES if not implemented.
- (BOOL)formSubmissionController:(PSPDFFormSubmissionController *)formSubmissionController shouldSubmitFormRequest:(PSPDFFormRequest *)formRequest;

/// The user has activated a submission action, which will go ahead.
- (void)formSubmissionController:(PSPDFFormSubmissionController *)formSubmissionController willSubmitFormValues:(PSPDFFormRequest *)formRequest;

/// The submission connection has succeeded and the server has responded with the given data.
- (void)formSubmissionController:(PSPDFFormSubmissionController *)formSubmissionController didReceiveResponseData:(NSData *)responseData;

/// The submission has failed with an error.
- (void)formSubmissionController:(PSPDFFormSubmissionController *)formSubmissionController didFailWithError:(NSError *)error;

/// If YES is returned then a web view containing the response data will be shown. Defaults to YES if not implemented.
- (BOOL)formSubmissionControllerShouldPresentResponseInWebView:(PSPDFFormSubmissionController *)formSubmissionController NS_SWIFT_NAME(formSubmissionControllerShouldPresentResponseInWebView(_:));

@end

NS_ASSUME_NONNULL_END
