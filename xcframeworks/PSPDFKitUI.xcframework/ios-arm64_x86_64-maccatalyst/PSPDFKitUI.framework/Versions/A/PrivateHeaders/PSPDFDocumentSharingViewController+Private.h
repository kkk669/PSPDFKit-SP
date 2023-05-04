//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentSharingViewController.h>

#import <PSPDFKit/PSPDFDelegateProxy.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFDocumentSharingContext.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFCheckboxSectionModel, PSPDFConfiguration, PSPDFDocumentSharingTableViewData, PSPDFDocumentSharingProcessingManager, MFMailComposeViewController;

/// Constant used in the document sharing view controller's cells `userInfo` to determine which `PSPDFDocumentSharingOptions` a cell represents.
PSPDF_EXPORT NSString *const PSPDFCellOptionKey;

PSPDF_EXTERN PSPDFDocumentSharingAnnotationOptions PSPDFFilterDocumentSharingAnnotationOptionsForEnabledLicenseFeatures(PSPDFDocumentSharingAnnotationOptions options, PSPDFDocumentSharingFileFormatOptions fileFormat);

PSPDF_EXTERN PSPDFDocumentSharingFileFormatOptions PSPDFFilterDocumentSharingFileFormatOptionsForEnabledLicenseFeatures(PSPDFDocumentSharingFileFormatOptions options);

@interface PSPDFDocumentSharingViewController ()

/// Delegate proxy used by the Destination categories.
PSPDF_DELEGATE_PROXY_PROPERTY(PSPDFDocumentSharingViewControllerDelegate)

/// The sharing context holds information related to what we're sharing and what options we have available. Used throughout the sharing flow.
@property (nonatomic, readonly) PSPDFDocumentSharingContext *sharingContext;

/// The manager in charge of file crunching.
@property (nonatomic, readonly) PSPDFDocumentSharingProcessingManager *processingManager;

/// The original, unmodified sharing configuration associated with the current destination. Used as a template.
@property (nonatomic, readonly) PSPDFDocumentSharingConfiguration *currentSharingConfiguration;

/// The updated, modified sharing configuration associated with the current destination. Used as a state holder.
@property (nonatomic) PSPDFDocumentSharingConfiguration *currentSharingState;

/// Holds the logic for what sections to show on the table v=iew.
@property (nonatomic, readonly) PSPDFDocumentSharingTableViewData *tableViewData;

/// Provides the text to be displayed in the main sharing screen when the particular option is selected.
///
/// @param option  The annotation option to return the accessory text for. See `PSPDFDocumentSharingAnnotationOptions.`
///
/// @return The customized text for the option.
- (nullable NSString *)accessoryTextForAnnotationOptions:(PSPDFDocumentSharingAnnotationOptions)option;

// MARK: Destinations Support

/// Printing
@property (nonatomic) BOOL printInProgress;
@property (nonatomic, weak) UIPrintInteractionController *printInteractionController;

/// Email
@property (nonatomic, weak) MFMailComposeViewController *mailComposeViewController;

/// Open In Support
@property (nonatomic) BOOL didStartSendingToOtherApplication;

// MARK: Misc

/// Reference to the "Annotations" table view section.
@property (nonatomic, nullable) PSPDFCheckboxSectionModel *annotationSection;

/// The documents' combined title.
@property (nonatomic, readonly) NSString *documentsTitle;

/// The controller that should present subsequent controllers.
@property (nonatomic, weak) UIViewController<PSPDFPresentationActions> *targetController;

/// Reference to the sender.
@property (nonatomic, weak) id sender;

/// Sets a flag that tells the view controller to show the final destination UI when it should be presented.
///
/// Useful to skip the configuration UI in some cases.
@property (nonatomic) BOOL shouldCommitImmediately;

/// Used in Viewer to get notified when the annotation sections have been laid out so we can lock down
/// the Image Documents feature.
///
/// Called after all the sections have been resolved.
- (void)didFinishConfiguringSections;


/// Cleans up the files that were generated when sharing the documents.
- (void)cleanUpSharedFilesCache;

@end

NS_ASSUME_NONNULL_END
