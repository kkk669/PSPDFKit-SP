//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <MessageUI/MessageUI.h>
#import <PSPDFKitUI/PSPDFFormSubmissionDelegate.h>
#import <PSPDFKitUI/PSPDFURLExecutor.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFActionExecutor, PSPDFURLAction, PSPDFSubmitFormAction, PSPDFDocument, PSPDFAnnotation;
@protocol PSPDFAnnotationPresenting;

@protocol PSPDFActionExecutorDelegate <PSPDFPageControls, PSPDFFormSubmissionDelegate, PSPDFURLExecutorDelegate>

- (nullable UIView<PSPDFAnnotationPresenting> *)annotationViewForAnnotation:(PSPDFAnnotation *)annotation;

- (void)showDocument:(PSPDFDocument *)document animated:(BOOL)animated configurationBlock:(nullable void (^)(PSPDFViewController *pdfController))configurationBlock completion:(nullable void (^)(void))completion;
- (void)presentPDFViewControllerWithDocument:(PSPDFDocument *)document options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options sender:(nullable id)sender animated:(BOOL)animated configurationBlock:(nullable void (^)(PSPDFViewController *pdfController))configurationBlock completion:(nullable void (^)(void))completion;

@optional

/// Some actions will create a document to present; this is a hook that allows customizing the object.
- (nullable PSPDFDocument *)actionExecutor:(PSPDFActionExecutor *)actionExecuter documentForRelativePath:(NSString *)relativePath;

/// Called every time before an action will be executed.
/// Return NO to prevent the PDF action from being executed.
- (BOOL)actionExecutor:(PSPDFActionExecutor *)actionExecuter shouldExecuteAction:(PSPDFAction *)action;

/// Called every time after an action has been executed.
- (void)actionExecutor:(PSPDFActionExecutor *)actionExecuter didExecuteAction:(PSPDFAction *)action;

/// Called to check if saving the document is allowed before generating the data from the document to
/// share with the submit form action along with the document save options to be used for creating
/// the `PSPDFFormSubmissionController` object to execute the action.
///
/// @param actionExecuter PSPDFActionExecutor executing the action.
/// @param submitFormAction PSPDFSubmitFormAction about to be executed.
/// @param document PSPDFDocument containing the submit form action.
/// @param options The options to be used while saving the document.
///
/// @return BOOL Whether the document should be saved before generating the data for the submit form action.
- (BOOL)actionExecutor:(PSPDFActionExecutor *)actionExecuter executingSubmitFormAction:(PSPDFSubmitFormAction *)submitFormAction shouldSaveContainingDocument:(PSPDFDocument *)document  withSaveOptions:(NSDictionary<PSPDFDocumentSaveOption, id> *_Nonnull *_Nonnull)options;

@end

@class PSPDFAction, PSPDFDocument;

/// Executes PDF actions.
/// Actions can do a lot in PDF; from changing the page/document to opening the print sheet.
PSPDF_TEST_CLASS_SWIFT(ActionExecutor)
@interface PSPDFActionExecutor : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

@property (nonatomic) PSPDFDocument *document;

@property (nonatomic, weak) id<PSPDFActionExecutorDelegate> delegate;

@property (nonatomic, weak) UIViewController<PSPDFPresentationActions> *sourceViewController;

/// Executes a passed in PDF action.
///
/// @param action The action to execute.
/// @param targetRect The rect that triggered this action in the receiver's view coordinate space.
/// @param pageIndex The current page index. This is used for relative actions like `NamedActionType.nextPage` and to register a back action in the back-forward action list.
/// @param animated Whether the transition the action is describing should be animated.
/// @param actionContainer The sender that triggered the execution of this action, such as an annotation or a button.
/// @return Whether the action or at least one of its sub-actions should be added to the back-forward action list.
- (BOOL)executePDFAction:(nullable PSPDFAction *)action targetRect:(CGRect)targetRect pageIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animated actionContainer:(nullable id)actionContainer;

/// Feature hooks needed. Can be injected from the PSPDFKit shared instance.
@property (nonatomic) id<PSPDFApplication> application;
@property (nonatomic) id<PSPDFFileManager> fileManager;
@property (nonatomic) id<PSPDFApplicationPolicy> policy;

@end

NS_ASSUME_NONNULL_END
