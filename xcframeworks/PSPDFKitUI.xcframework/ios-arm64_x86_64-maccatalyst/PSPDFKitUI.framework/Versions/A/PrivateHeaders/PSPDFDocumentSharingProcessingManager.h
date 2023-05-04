//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFProcessorConfiguration.h>
#import <PSPDFKitUI/PSPDFDocumentSharingConfiguration.h>
#import <PSPDFKitUI/PSPDFDocumentSharingContext.h>

@protocol PSPDFDocumentSharingProcessingManagerDelegate;

NS_ASSUME_NONNULL_BEGIN

/// Generates files to share with the PSPDFDocumentSharingViewController class.
NS_SWIFT_NAME(PDFDocumentSharingProcessingManager)
PSPDF_APP_EXPORT @interface PSPDFDocumentSharingProcessingManager : NSObject

/// Possible values of the `documentPreparationState` property.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFDocumentSharingPreparationState) {
    PSPDFDocumentSharingPreparationStateStale,
    PSPDFDocumentSharingPreparationStateExecuting,
    PSPDFDocumentSharingPreparationStateFinished,
    PSPDFDocumentSharingPreparationStateCancelled
};

/// The preparation state for the sharing of the documents.
@property (nonatomic) PSPDFDocumentSharingPreparationState documentPreparationState;

/// The manager's delegate.
@property (nonatomic, weak) id<PSPDFDocumentSharingProcessingManagerDelegate> delegate;

/// Creates a manager with a sharing context.
///
/// @param sharingContext  The sharing context associated with the current sharing session.
- (instancetype)initWithSharingContext:(PSPDFDocumentSharingContext *)sharingContext;

/// Starts the file crunching process with the given configuration, and returns whether the file generation was success.
///
/// @note This method is executed synchronously.
///
/// @param completion Called when the file crunching succeeds. Any error generated during this processes is passed to the delegate.
- (void)processFilesForSharingState:(PSPDFDocumentSharingConfiguration *)sharingConfiguration completion:(void (^)(NSArray<PSPDFFile *> *files))completion;

/// If there's any file crunching going on, it is cancelled.
- (void)cancelDocumentPreparationIfAny;

@end

// MARK: - Delegate API

NS_SWIFT_NAME(PDFDocumentSharingProcessingManagerDelegate)
@protocol PSPDFDocumentSharingProcessingManagerDelegate
@optional

/// Notifies the delegate about the file crunching progress. The delegate should take this information and update
/// the UI appropriately.
///
/// @param processingManager   The processing manager.
/// @param progress            The file crunching completion percentage, represented from 0 to 1.
- (void)sharingProcessingManager:(PSPDFDocumentSharingProcessingManager *)processingManager didUpdateProgress:(CGFloat)progress;

/// Notifies the delegate that the file crunching process has been cancelled.
///
/// @param processingManager   The processing manager.
- (void)sharingProcessingManagerDidCancelFileCrunching:(PSPDFDocumentSharingProcessingManager *)processingManager;

/// Asks the delegate for security options to apply when sharing the documents.
///
/// @param processingManager   The processing manager.
///
/// @return Security options. Can be nil.
- (nullable PSPDFDocumentSecurityOptions *)securityOptionForSharingProcessingManager:(PSPDFDocumentSharingProcessingManager *)processingManager;

/// Asks the delegate for the filename that should be used for the generated files when sharing the given document.
///
/// @note This method is only going to be called when PSPDFDocumentSharingFileFormatOptionPDF is selected. Custom filenames for PSPDFDocumentSharingFileFormatOptionImage or PSPDFDocumentSharingFileFormatOptionOriginal is currently not supported.
///
/// This method is going to be called once per sharing document, and the returned string shouldn't contain the ".pdf" suffix.
///
/// @param processingManager   The processing manager.
/// @param sharingDocument     The document that's being shared.
/// @param destination         The destination the document is going to be shared to.
- (nullable NSString *)sharingProcessingManager:(PSPDFDocumentSharingProcessingManager *)processingManager filenameForGeneratedFileForDocument:(PSPDFDocument *)sharingDocument destination:(PSPDFDocumentSharingDestination)destination;

/// Tells the delegate that the files have completed processing and if an error was generated during that process.
///
/// @param processingManager   The processing manager.
/// @param files               The files that were generated.
/// @param error               The error generated from processing the files.
- (void)sharingProcessingManager:(PSPDFDocumentSharingProcessingManager *)processingManager didFinishProcessingWithFiles:(NSArray<PSPDFFile *> *)files error:(NSError *)error;

/// Asks the delegate if the files should be handed over to the destination
///
/// @param processingManager   The processing manager.
/// @param files               The files that were generated.
/// @param destination         The destination the files are going to be shared to.
- (BOOL)sharingProcessingManager:(PSPDFDocumentSharingProcessingManager *)processingManager shouldShareFiles:(NSArray<PSPDFFile *> *)files toDestination:(PSPDFDocumentSharingDestination)destination;

/// Lets the delegate customize the processor that will be used to create the files.
///
/// @param processingManager       The processing manager.
/// @param processorConfiguration  The configuration that was created and will be used to crunch the files.
- (void)sharingProcessingManager:(PSPDFDocumentSharingProcessingManager *)processingManager processorConfiguration:(PSPDFProcessorConfiguration *)processorConfiguration;

/// Asks the delegate whether the document should be saved with the provided options.
///
/// The delegate can update the provided options at will, and those will be applied to the document if `true` is returned from this method.
///
/// @param processingManager       The processing manager.
/// @param document                The document that's being saved.
/// @param options                 The options that will be applied when saving the document.
///
/// @return Whether the document should be saved with the provided options.
///
/// @note If this method's implementation returns `false`, the current state of the document won't be saved and the document will be shared with the last saved state.
- (BOOL)sharingProcessingManager:(PSPDFDocumentSharingProcessingManager *)processingManager shouldSaveDocument:(PSPDFDocument *)document withOptions:(NSDictionary<PSPDFDocumentSaveOption, id> * _Nonnull * _Nonnull)options;

@end

NS_ASSUME_NONNULL_END
