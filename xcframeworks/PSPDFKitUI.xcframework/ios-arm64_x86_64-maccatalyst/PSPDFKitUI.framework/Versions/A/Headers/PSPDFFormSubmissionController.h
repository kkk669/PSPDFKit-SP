//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFSubmitFormAction.h>
#import <PSPDFKitUI/PSPDFFormRequest.h>
#import <PSPDFKitUI/PSPDFFormSubmissionDelegate.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_EXPORT NSNotificationName const PSPDFFormSubmissionControllerDidStartLoadingNotification;
PSPDF_EXPORT NSNotificationName const PSPDFFormSubmissionControllerDidFinishLoadingNotification;
PSPDF_EXPORT NSNotificationName const PSPDFFormSubmissionControllerDidFailToLoadNotification;

typedef BOOL (^PSPDFSubmissionControllerShouldContinueBlock)(PSPDFFormRequest *formRequest);
typedef void (^PSPDFSubmissionControllerBeforeSubmissionBlock)(PSPDFFormRequest *formRequest);
typedef void (^PSPDFSubmissionControllerCompletionBlock)(NSData *data, NSURLResponse *response);
typedef void (^PSPDFSubmissionControllerErrorBlock)(NSError *error);

/// An object that executes a `SubmitFormAction` by sending the values of a filled PDF form to a web service using an HTTP request.
PSPDF_CLASS_SWIFT(PDFFormSubmissionController)
@interface PSPDFFormSubmissionController : NSObject

- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider action:(PSPDFSubmitFormAction *)action NS_DESIGNATED_INITIALIZER;

PSPDF_EMPTY_INIT_UNAVAILABLE

@property (nonatomic, readonly) PSPDFDocumentProvider *documentProvider;
@property (nonatomic, readonly) PSPDFSubmitFormAction *action;
@property (nonatomic) PSPDFFormRequest *formRequest;

/// The path extension if the submission is to be saved to file.
@property (nonatomic, readonly) NSString *submissionPathExtension;

- (void)submitContinueWhen:(PSPDFSubmissionControllerShouldContinueBlock)continueBlock beforeSubmission:(PSPDFSubmissionControllerBeforeSubmissionBlock)beforeSubmissionBlock onCompletion:(PSPDFSubmissionControllerCompletionBlock)completionBlock onError:(PSPDFSubmissionControllerErrorBlock)errorBlock;
@end

NS_ASSUME_NONNULL_END
