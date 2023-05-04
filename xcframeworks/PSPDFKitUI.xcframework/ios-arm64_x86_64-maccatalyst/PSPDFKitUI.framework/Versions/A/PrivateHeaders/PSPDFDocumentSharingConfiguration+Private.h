//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentSharingConfiguration.h>

#import <PSPDFKitUI/PSPDFDocumentSharingContext.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDocumentSharingConfigurationBuilder ()
@property (nonatomic) NSRange pageRangeToExport;
@end

@interface PSPDFDocumentSharingConfiguration ()

/// The explicit page range to export. Only valid for PSPDFDocumentSharingPageSelectionOptionRange and PSPDFDocumentSharingPageSelectionOptionCurrent.
@property (nonatomic) NSRange pageRangeToExport;

/// Whether the configuration is valid and can be used to perform the share.
///
/// @param sharingContext      The context in which this configuration is being used.
/// @param sharingState        The current selected options.
/// @param error               Error pointer to be populated if the configuration instance is not valid.
///
/// @return Whether the configuration is valid or not.
- (BOOL)isValidConfigurationForContext:(PSPDFDocumentSharingContext *)sharingContext sharingState:(PSPDFDocumentSharingConfiguration *)sharingState error:(NSError *__autoreleasing*)error;

/// Whether the documents can be sent as email attachments. Result is based on the device configuration itself.
+ (BOOL)canSendEmail;

/// Whether the documents can be sent as Messages.app attachments. Result is based on the device configuration itself.
+ (BOOL)canSendMessage;

/// Option availability

/// Returns the count for available file format options in this configuration.
- (NSUInteger)fileFormatOptionsAvailabilityCountForSharingContext:(PSPDFDocumentSharingContext *)sharingContext;

/// Returns the count for available page selection options in this configuration.
- (NSUInteger)pageSelectionOptionsAvailabilityCountForSharingContext:(PSPDFDocumentSharingContext *)sharingContext;

/// Returns the count for available annotation options in this configuration.
- (NSUInteger)annotationOptionsAvailabilityCountForSharingState:(PSPDFDocumentSharingConfiguration *)sharingState;

/// Sanitization

/// Whether the file format options are valid in the current context.
- (BOOL)fileFormatOptionsAreValidForContext:(PSPDFDocumentSharingContext *)sharingContext withError:(NSError * __autoreleasing *)error;

/// Whether the current annotation options are valid with the state.
- (BOOL)annotationOptionsAreValidForSharingState:(PSPDFDocumentSharingConfiguration *)sharingState error:(NSError *__autoreleasing*)error;

/// Wether the page selection options are valid in the current context, with state.
- (BOOL)pageSelectionOptionsAreValidForContext:(PSPDFDocumentSharingContext *)sharingContext sharingState:(PSPDFDocumentSharingConfiguration *)sharingState error:(NSError *__autoreleasing*)error;

/// Takes the current file format options on the configuration and removes any options that wouldn't be
/// viable to take into consideration given the current sharing context.
///
/// Use case: if the document does not have an original file set, don't show that option on the UI even though it's available on the configuration.
- (PSPDFDocumentSharingFileFormatOptions)sanitizedFileFormatOptionsForSharingContext:(PSPDFDocumentSharingContext *)sharingContext;

/// Takes the current page selection options on the configuration and removes any options that wouldn't be
/// viable to take into consideration given the current sharing context, and reports an error.
///
/// Use case: if the file we're sharing is an image document, we remove the Range and the Current options since they're not relevant anymore.
- (PSPDFDocumentSharingPagesOptions)sanitizedPageSelectionOptionsForSharingContext:(PSPDFDocumentSharingContext *)sharingContext sharingState:(nullable PSPDFDocumentSharingConfiguration *)sharingState;

/// Takes the current annotation options on the configuration and removes any options that wouldn't be
/// viable to take into consideration given the current sharing context.
///
/// Use case: remove the ability to embed annotations in to the document if there license does not include that component.
- (PSPDFDocumentSharingAnnotationOptions)sanitizedAnnotationOptionsForSelectedFileFormatOption:(PSPDFDocumentSharingFileFormatOptions)fileFormatOption;

/// Default Selections

/// Returns the most appropriate annotation option to act as a default selection.
///
/// The appropriate option is determined via importance level. Read more: https://pspdfkit.com/guides/ios/miscellaneous/document-sharing/#sharing-configurations
- (PSPDFDocumentSharingAnnotationOptions)bestAvailableAnnotationOptionForSelectedFileFormatOption:(PSPDFDocumentSharingFileFormatOptions)fileFormatOption;

/// Returns the most appropriate page selection option to act as a default selection.
///
/// The appropriate option is determined via importance level. Read more: https://pspdfkit.com/guides/ios/miscellaneous/document-sharing/#sharing-configurations
- (PSPDFDocumentSharingPagesOptions)bestAvailablePagesSelectionOptionForSharingContext:(PSPDFDocumentSharingContext *)sharingContext selectedFileFormatOption:(PSPDFDocumentSharingFileFormatOptions)fileFormatOption;

/// Returns the most appropriate file format option to act as a default selection given the current sharing context.
///
/// Read more: https://pspdfkit.com/guides/ios/miscellaneous/document-sharing/#sharing-configurations
- (PSPDFDocumentSharingFileFormatOptions)bestAvailableFileFormatOptionForSharingContext:(PSPDFDocumentSharingContext *)sharingContext;

@end

NS_ASSUME_NONNULL_END
