//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFStyleable.h>
#import <PSPDFKitUI/PSPDFDocumentSharingConfiguration.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>
#import <PSPDFKit/PSPDFMacros.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines a moment in the sharing process.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFDocumentSharingStep) {
    /// When the user is picking the options to share the document with.
    PSPDFDocumentSharingStepConfiguration,
    /// When the files have been generated and passed over to the destination, such as Mail or `UIActivityViewController`.
    PSPDFDocumentSharingStepDestination,
    /// When the files are being generated.
    PSPDFDocumentSharingStepFileGeneration
} PSPDF_ENUM_SWIFT(PDFDocumentSharingViewController.Step);

typedef NSString *PSPDFDocumentSharingUserInfoKey NS_TYPED_ENUM NS_SWIFT_NAME(PDFDocumentSharingUserInfoKey);

/// Key for referencing the URL to which a document was exported to.
PSPDF_EXPORT PSPDFDocumentSharingUserInfoKey const PSPDFDocumentSharingExportedURL;

/// Key for referencing the `UIDocumentPickerViewController` selected from the exporting interface.
PSPDF_EXPORT PSPDFDocumentSharingUserInfoKey const PSPDFDocumentSharingSelectedDocumentPicker;

/// Key for referencing the activity type selected when sharing to the Activity destination (`UIActivityViewController`).
PSPDF_EXPORT PSPDFDocumentSharingUserInfoKey const PSPDFDocumentSharingSelectedActivityType;

/// Key for referencing the `UIPrintInteractionController` that handled the printing process when sharing to the Print destination.
PSPDF_EXPORT PSPDFDocumentSharingUserInfoKey const PSPDFDocumentSharingPrintInteractionController;

@class PSPDFDocumentSharingViewController, PSPDFDocument, PSPDFFile, PSPDFProcessor, PSPDFProcessorConfiguration, PSPDFDocumentSecurityOptions, MFMailComposeViewController;

@protocol PSPDFVisiblePagesDataSource;

/// The delegate for the `PDFDocumentSharingViewController`
PSPDF_PROTOCOL_SWIFT(PDFDocumentSharingViewControllerDelegate)
@protocol PSPDFDocumentSharingViewControllerDelegate<NSObject>
@optional

/// Called when the destination has been handed over the generated files to share them.
///
/// For some actions that happen outside the host application, such as sharing to `UIActivityViewController` or Printing,
/// the fact that the error parameter is `nil` does not necessarily mean that the ultimate action was performed correctly, but that the
/// files were handed over to the destination process correctly.
///
/// @note This method is not guaranteed to be called from the main thread.
///
/// @param shareController     The controller performing the action.
/// @param configuration       The configuration use to create the files that were shared.
/// @param userInfo            Contextual information generated from the sharing action. See `PSPDFDocumentSharingUserInfoKey`.
/// @param error               The resulting error from trying to send the files to the destination.
- (void)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController didFinishSharingWithConfiguration:(PSPDFDocumentSharingConfiguration *)configuration userInfo:(NSDictionary<PSPDFDocumentSharingUserInfoKey, id> *)userInfo error:(nullable NSError *)error;

/// Called when the documents have been processed for being exported, and the resulting data has been
/// handed over to the appropriate destination, based on the current state of the controller.
///
/// @param shareController     The controller performing the action.
/// @param files               The files that were handed over to the destination.
/// @param configuration       The configuration to be used when sharing the document.
/// @param error               The error, if any, that was generated during file crunching.
- (void)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController didFinishGeneratingFiles:(NSArray<PSPDFFile *> *)files withConfiguration:(PSPDFDocumentSharingConfiguration *)configuration error:(nullable NSError *)error;

/// Sharing has been cancelled.
///
/// @param shareController     The sharing controller that was cancelled.
/// @param sharingStep         Indicates the step in which the sharing was cancelled.
/// @param configuration       The sharing configuration at the moment the sharing was cancelled.
- (void)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController didCancelSharingAtStep:(PSPDFDocumentSharingStep)sharingStep withConfiguration:(PSPDFDocumentSharingConfiguration *)configuration;

/// Called when the sharing configuration UI is dismissed by the user.
- (void)documentSharingViewControllerWasDismissed;

/// Notifies the delegate about the progress in the underlying file crunching process for the documents to be shared.
///
/// This method is going to be called both when the file crunching starts (progress = 0) and when it finishes (progress = 1).
///
/// @note This method is not guaranteed to be called from the main thread.
///
/// @param shareController     The sharing controller notifying about file processing progress.
/// @param progress            The progress of the total file crunching, represented from 0 to 1.
- (void)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController preparationProgress:(CGFloat)progress;

/// Asks the delegate for the filename that should be used for the generated files when sharing the given document.
///
/// This method is going to be called once per document being shared during the file crunching process. The returned name will be used to write the resulting document to disk. The name you return shouldn't include the `.pdf` file extension.
///
/// @note This method is only going to be called when sharing documents with PSPDFDocumentSharingFileFormatOptionPDF selected. Custom filenames for PSPDFDocumentSharingFileFormatOptionImage or PSPDFDocumentSharingFileFormatOptionOriginal are currently not supported.
///
/// Return `nil` to use the document's default filename.
///
/// @param shareController     The controller that's asking for the filename.
/// @param sharingDocument     The document that's being shared.
/// @param destination         The destination the document is going to be shared to.
- (nullable NSString *)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController filenameForGeneratedFileForDocument:(PSPDFDocument *)sharingDocument destination:(PSPDFDocumentSharingDestination)destination;

/// Defaults to `true`.
///
/// Called when the documents are being prepared to be shared. This method is called right before the file crunching process starts.
///
/// You can use this method as a checkpoint to avoid doing any processing on any files based on your own criteria.
///
/// @param shareController         The controller that's notifying the delegate.
/// @param sharingConfiguration    The configuration options that the documents are going to be exported with.
///
/// @return `true` to allow the files to be processed, `false` to stop the sharing process.
- (BOOL)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController shouldProcessForSharingWithState:(PSPDFDocumentSharingConfiguration *)sharingConfiguration;

/// Defaults to `true`.
///
/// Called as the last step before the files are handed over to their destination.
///
/// Return `false` to prevent the files from being handed over to the destination. This is useful if you wish to
/// handle the file sharing yourself if, for instance, you're in a secure environment in which the default destinations do
/// not fit your needs.
///
/// @param shareController     The controller that's notifying the delegate.
/// @param files               The files that are about to be handed over to the destination.
/// @param destination         The share destination.
///
/// @note It is your responsibility to dismiss the sharing view controller if you decide to stop the sharing process.
///
/// @return `true` to allow the files to be shared to the given destination, `false` to stop the sharing process.
- (BOOL)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController shouldShareFiles:(NSArray<PSPDFFile *> *)files toDestination:(PSPDFDocumentSharingDestination)destination;

/// Defaults to YES.
///
/// Asks the delegate if the document that's being shared should be saved before sharing.
///
/// This delegate method is not called if the `Document` being shared has its `annotationSaveMode` set to `disabled`.
///
/// @param shareController     The controller that's notifying the delegate.
/// @param document            The document that's being shared.
/// @param options             The options to apply when saving the document.
///
/// @return Whether the document should be saved with the provided options.
///
/// @note If this method's implementation returns `false`, the current state of the document won't be saved and the document will be shared with the last saved state.
- (BOOL)documentSharingViewController:(PSPDFDocumentSharingViewController *)shareController shouldSaveDocument:(PSPDFDocument *)document withOptions:(NSDictionary<PSPDFDocumentSaveOption, id> * _Nonnull * _Nonnull)options;

@end

/// These notifications represent a small subset of `UIDocumentInteractionControllerDelegate` (but the most important ones)
/// To get all callbacks, check `PDFDocumentSharingViewController` and implement the appropriate delegates.
PSPDF_EXPORT NSNotificationName const PSPDFDocumentInteractionControllerWillBeginSendingToApplicationNotification;
PSPDF_EXPORT NSNotificationName const PSPDFDocumentInteractionControllerDidEndSendingToApplicationNotification;

/// Displays an interface that allows the user to pick a set of options that determine how a set of PDF files should be processed before being shared to a destination. By default, the user can choose the file type, the page range, and how annotations should be handled.
///
/// Documents can be shared to different Destinations specified by the `PSPDFDocumentSharingDestination` enumeration. By default, the `PDFDocumentSharingViewController`
/// will share to`PSPDFDocumentSharingDestinationActivity`, which will let the user pick the ultimate action for the generated documents via a `UIActivityViewController` instance (which can be customized
/// via the `-activityViewControllerForSharingItems:sender:` method.).
///
/// A single `PDFDocumentSharingViewController` instance can offer multiple destinations to share the documents to to the user — they will be represented on a segmented control on the navigation bar of
/// the sharing view controller. However, a Share can only be performed to a single destination at a time. To add Destinations to the list the user can choose from, create a `PSPDFDocumentSharingConfiguration` object
/// and set the appropriate value on its builder's `destination` property, then add that configuration to the `sharingConfigurations` property on the sharing view controller.
///
/// Please note that Destinations are exclusive per sharing view controller instance, so you can't have 2 or more configurations with the same destination set.
///
/// Once the instance has been configured appropriately, call `-presentFromViewController:sender:` on it to present the UI.
PSPDF_CLASS_SWIFT(PDFDocumentSharingViewController)
@interface PSPDFDocumentSharingViewController : PSPDFBaseViewController<PSPDFStyleable, PSPDFOverridable>

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// Initializes a view controller to share the given documents using the default sharing configuration.
/// This uses the default sharing configuration for `PSPDFDocumentSharingDestinationActivity`.
///
/// @param documents   The documents to be shared. Required to contain at least one document.
- (instancetype)initWithDocuments:(NSArray<PSPDFDocument *> *)documents;

/// Initializes a view controller to share the given documents according the given configurations.
///
/// @param documents The documents to be shared. Required to contain at least one document.
/// @param sharingConfigurations The configurations for the possible sharing destinations. If nil or empty, the default sharing configuration for `PSPDFDocumentSharingDestinationActivity` is used.
- (instancetype)initWithDocuments:(NSArray<PSPDFDocument *> *)documents sharingConfigurations:(nullable NSArray<PSPDFDocumentSharingConfiguration *> *)sharingConfigurations NS_DESIGNATED_INITIALIZER;

/// List of documents this control has been initialized with.
@property (nonatomic, readonly) NSArray<PSPDFDocument *> *documents;

/// The configurations the user can pick to share to.
///
/// Initially uses the configurations passed to the initializer.
///
/// @note Setting 2 or more configurations with the same destination is invalid and will result in an assert.
@property (nonatomic) NSArray<PSPDFDocumentSharingConfiguration *> *sharingConfigurations;

/// The currently selected file format option to share the documents as.
///
/// Default value is determined based on the active destination.
///
/// Read more: https://pspdfkit.com/guides/ios/miscellaneous/document-sharing/
@property (nonatomic) PSPDFDocumentSharingFileFormatOptions selectedFileFormatOption;

/// The currently selected option for the page range to share from the documents being shared.
///
/// @note Default value is determined based on the active destination.
///
/// @discussion When sharing multiple documents, the only two valid options are PSPDFDocumentSharingPageSelectionAnnotated and
/// PSPDFDocumentSharingPageSelectionAll.
///
/// Read more: https://pspdfkit.com/guides/ios/miscellaneous/document-sharing/
@property (nonatomic) PSPDFDocumentSharingPagesOptions selectedPageSelectionOption;

/// The currently selected option for handling annotations in the documents being shared.
///
/// Default value is determined based on the active destination.
///
/// Read more: https://pspdfkit.com/guides/ios/miscellaneous/document-sharing/
@property (nonatomic) PSPDFDocumentSharingAnnotationOptions selectedAnnotationOption;

/// Returns the destination that's currently active on the view controller.
///
/// @note When setting this property, the new destination needs to be defined as the destination of one of the `sharingConfigurations` objects.
@property (nonatomic) PSPDFDocumentSharingDestination selectedDestination;

/// The document sharing controller delegate.
///
/// @note When sharing is invoked via the default PSPDFKit UI, this will be set to the
/// presenting `PDFViewController` instance.
@property (nonatomic, weak) IBOutlet id<PSPDFDocumentSharingViewControllerDelegate> delegate;

/// Delegate used for getting the list of visible pages.
///
/// @note This protocol is implemented on `PDFViewController`.
///
/// @note When sharing multiple documents, this delegate is ignored and all pages will be shared by default.
@property (nonatomic, weak) id<PSPDFVisiblePagesDataSource> visiblePagesDataSource;

/// The range from which the user can pick to share pages from the document.
/// This range is only valid when the `selectedPageSelectionOption` is set to `DocumentSharingConfiguration.PageOptions.range`.
///
/// @discussion When sharing multiple documents, the value of this property is ignored.
@property (nonatomic) NSRange shareablePageRange;

/// Checks if the controller has options *at all* - and simply calls the delegate if not.
/// This prevents showing the controller without any options and just a commit button.
/// Will return YES if the controller has options available, NO if the delegate has been called.
@property (nonatomic, readonly) BOOL checkIfControllerHasOptionsAvailableAndCallDelegateIfNot;

/// Button title for "commit".
@property (nonatomic, copy) NSString *commitButtonTitle;

/// Commits the sharing action based on the current configuration.
- (void)commitWithCurrentConfiguration;

/// Cancels the current file crunching operation, if any.
- (void)cancelDocumentPreparationIfAny;

/// Presents the sharing interface in the appropriate way to the user.
///
/// @note In some cases, such as when the document has no options to be configured (single page, so there are no pages to pick
/// from, or no annotations), the document will be automatically forwarded to the selected destination.
///
/// @param viewController  The view controller that should present the sharing interface.
/// @param sender          The action sender.
- (void)presentFromViewController:(UIViewController<PSPDFPresentationActions> *)viewController sender:(nullable id)sender;

/// Returns the currently selected options for a configuration with the given destination, if it exists.
///
/// @param destination     Destination to retrieve the options from.
///
/// @return The (modified by the user) sharing configuration associated with the provided destination.
- (nullable PSPDFDocumentSharingConfiguration *)currentSharingConfigurationForDestination:(PSPDFDocumentSharingDestination)destination;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFDocumentSharingViewController (SubclassingHooks)

/// May be used to specify custom `PSPDFDocumentSecurityOptions`, such as passwords and key length. Defaults to nil.
@property (nonatomic, readonly, nullable) PSPDFDocumentSecurityOptions *documentSecurityOptions;

/// Subclass to allow setting default printer info or changing the printer job name.
/// (see `printerID`, https://stackoverflow.com/questions/12898476/airprint-set-default-printer-in-uiprintinteractioncontroller)
@property (nonatomic, readonly) UIPrintInfo *printInfo;

/// Returns a preconfigured activity view controller suitable for sharing the items generated after processing
/// the documents with the selected configuration.
///
/// You can override this method and return your own UIActivityViewController instance if you wish to customize the options that are
/// available for sharing the documents.
///
/// @param activityItems   The items that the document processing generated, to be shared.
/// @param sender          The sender that requested the UIActivityViewController.
///
/// @return An `UIActivityViewController` instance suitable for sharing the provided activity items, or `nil` if the documents are not suitable to being shared.
- (nullable UIActivityViewController *)activityViewControllerForSharingItems:(NSArray *)activityItems sender:(id)sender;


/// Override this method to customize the mail compose view controller that's used when sharing to the Email destination.
///
/// @param mailComposeViewController   The mail compose view controller that'll be used to send the email.
- (void)configureMailComposeViewController:(MFMailComposeViewController *)mailComposeViewController;

/// Override this method to modify the processor configuration to be used when crunching the files after the configuration options have been selected.
///
/// @param processorConfiguration  The processor configuration created based on the sharing configuration.
- (void)configureProcessorConfigurationOptions:(PSPDFProcessorConfiguration *)processorConfiguration;

/// Override this method to customize the attachment data and information for documents being shared to Mail.app.
///
/// @note This method is only called when sharing to Mail destination.
///
/// @warning Your implementation must call super as its last step.
- (void)addAttachmentData:(NSData *)attachment mimeType:(NSString *)mimeType fileName:(NSString *)filename;

/// Override to customize the title that the segmented control on the sharing configuration interface displays
/// for the provided destination.
///
/// @param destination     Destination for which the title should be provided.
///
/// @return The title for the given destination.
- (NSString *)titleForDestination:(PSPDFDocumentSharingDestination)destination;

/// Override this method to return a custom location to export the document to for a given destination.
///
/// @see `PSPDFDocumentSharingDestination` for the available destinations.
///
/// @param destination     The destination the document is going to be shared to.
///
/// @return The directory path to export the document to. If `nil`, a default temporary directory is going to be created.
- (nullable NSString *)temporaryDirectoryForSharingToDestination:(PSPDFDocumentSharingDestination)destination;

/// Override this method to return a customized subtitle for the available annotation options.
///
/// @param option  The annotation option to return the title for. See `PSPDFDocumentSharingAnnotationOptions.`
///
/// @return The customized title for the option.
- (nullable NSString *)titleForAnnotationOptions:(PSPDFDocumentSharingAnnotationOptions)option;

/// Override this method to return a customized title for the available annotation options.
///
/// @param option  The annotation option to return the title for. See `PSPDFDocumentSharingAnnotationOptions.`
///
/// @return The customized title for the option or `nil` if a subtitle should not be displayed.
- (nullable NSString *)subtitleForAnnotationsOptions:(PSPDFDocumentSharingAnnotationOptions)option sharingConfiguration:(PSPDFDocumentSharingConfiguration *)sharingConfiguration;

@end

NS_ASSUME_NONNULL_END
