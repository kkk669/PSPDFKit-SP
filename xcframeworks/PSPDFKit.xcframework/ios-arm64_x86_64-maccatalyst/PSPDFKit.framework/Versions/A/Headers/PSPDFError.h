//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// The PSPDFKit error domain.
PSPDF_EXPORT NSString *const PSPDFErrorDomain;

/// List of documented errors within the `PSPDFErrorDomain`.
///
/// @note Various PSPDFKit methods can also return errors from Apple error domains.
typedef NS_ERROR_ENUM(PSPDFErrorDomain, PSPDFErrorCode) {
    PSPDFErrorCodeOutOfMemory = 10,
    PSPDFErrorCodeFileNotFound = 11,
    PSPDFErrorCodeNoModificationDateAvailable = 21,
    PSPDFErrorCodePageInvalid = 100,
    PSPDFErrorCodeDocumentContainsNoPages = 101,
    PSPDFErrorCodeDocumentNotValid = 102,
    PSPDFErrorCodeDocumentLocked = 103,
    PSPDFErrorCodeDocumentInvalidFormat = 104,
    PSPDFErrorCodePageIndexOutOfBounds = 105,
    PSPDFErrorCodeDocumentNotLoaded = 106,
    PSPDFErrorCodeDocumentObjectInvalidated = 107,
    PSPDFErrorCodeDataProviderUnableToLoad = 108,
    PSPDFErrorCodeDataSinkShouldBeFinished = 120,
    PSPDFErrorCodeUnableToOpenPDF = 200,
    PSPDFErrorCodeUnableToGetPageReference = 210,
    PSPDFErrorCodeUnableToGetStream = 211,
    PSPDFErrorCodeDocumentNotSet = 212,
    PSPDFErrorCodeDocumentProviderNotSet = 213,
    PSPDFErrorCodeStreamPathNotSet = 214,
    PSPDFErrorCodeAssetNameNotSet = 215,
    PSPDFErrorCodeCantCreateStreamFile = 216,
    PSPDFErrorCodeCantCreateStream = 217,
    PSPDFErrorCodeCoreAnnotationNotSet = 218,
    PSPDFErrorCodeCoreAnnotationAdditionFailed = 219,
    PSPDFErrorCodePageRenderSizeIsEmpty = 220,
    PSPDFErrorCodePageRenderClipRectTooLarge = 230,
    PSPDFErrorCodePageRenderGraphicsContextNil = 240,
    PSPDFErrorCodeDocumentUnsupportedSecurityScheme = 302,
    PSPDFErrorCodeFailedToLoadAnnotations = 400,
    PSPDFErrorCodeExternalAnnotationFileLoadingDisabled = 401,
    PSPDFErrorCodeExternalAnnotationFileMissing = 402,
    PSPDFErrorCodeExternalAnnotationFileEmpty = 403,
    PSPDFErrorCodeFailedToLoadAnnotationFont = 404,
    PSPDFErrorCodeFailedToWriteAnnotations = 410,
    PSPDFErrorCodeCannotEmbedAnnotations = 420,
    PSPDFErrorCodeAnnotationSavingDisabled = 421,
    PSPDFErrorCodeCannotModifyAnnotationZIndices = 430,
    /// Saving has been disabled by setting the `annotationSaveMode` property on `Document` to `PSPDFAnnotationSaveModeDisabled`.
    PSPDFErrorCodeSavingDisabled = 450,
    PSPDFErrorCodeFailedToSaveBookmarks = 460,
    PSPDFErrorCodeFailedToSaveDocument = 470,
    PSPDFErrorCodeFailedToSaveDocumentCheckpoint = 480,
    PSPDFErrorCodeFailedToDeleteDocumentCheckpoint = 490,
    PSPDFErrorCodeOutlineParser = 500,
    PSPDFErrorCodeUnableToConvertToDataRepresentation = 600,
    PSPDFErrorCodeRemoveCacheError = 700,
    PSPDFErrorCodeFailedToConvertToPDF = 800,
    PSPDFErrorCodeFailedToGeneratePDFInvalidArguments = 810,
    PSPDFErrorCodeFailedToGeneratePDFDocumentInvalid = 820,
    PSPDFErrorCodeFailedToGeneratePDFCouldNotCreateContext = 830,
    PSPDFErrorCodeFailedToCopyPages = 840,
    PSPDFErrorCodeFailedToUpdatePageObject = 850,
    PSPDFErrorCodeFailedToMemoryMapFile = 860,
    PSPDFErrorCodeMicPermissionNotGranted = 900,
    PSPDFErrorCodeXFDFParserLackingInputStream = 1000,
    PSPDFErrorCodeXFDFParserAlreadyCompleted = 1010,
    PSPDFErrorCodeXFDFParserAlreadyStarted = 1020,
    PSPDFErrorCodeXMLParserError = 1100,
    PSPDFErrorCodeDigitalSignatureVerificationFailed = 1150,
    PSPDFErrorCodeDigitalSignatureSigningFailed = 1151,
    PSPDFErrorCodeXFDFWriterCannotWriteToStream = 1200,
    PSPDFErrorCodeFDFWriterCannotWriteToStream = 1250,
    PSPDFErrorCodeSoundEncoderInvalidInput = 1300,
    PSPDFErrorCodeGalleryInvalidManifest = 1400,
    PSPDFErrorCodeGalleryUnknownItem = 1450,
    PSPDFErrorCodeInvalidRemoteContent = 1500,
    PSPDFErrorCodeFailedToSendStatistics = 1600,
    PSPDFErrorCodeLibraryFailedToInitialize = 1700,
    PSPDFErrorCodeCantCreateCustomAPStream = 1800,
    PSPDFErrorCodeCantApplyCustomAPStream = 1810,
    PSPDFErrorCodeFormValidationError = 5000,
    PSPDFErrorCodeFormRemovalError = 5500,
    PSPDFErrorCodeFormInsertionError = 5501,
    PSPDFErrorCodeFormResetError = 5502,
    PSPDFErrorCodeImageProcessorInvalidImage = 6000,
    PSPDFErrorCodeOpenInNoApplicationsFound = 7000,
    PSPDFErrorCodeMessageNotSent = 7100,
    PSPDFErrorCodeEmailNotConfigured = 7200,
    PSPDFErrorCodeProcessorAnnotationModificationError = 7300,
    PSPDFErrorCodeProcessorUnableToInsertPage = 7301,
    PSPDFErrorCodeProcessorUnableToFlattenAnnotation = 7302,
    PSPDFErrorCodeProcessorUnableToRemoveAnnotation = 7304,
    PSPDFErrorCodeProcessorUnableToIncludeDrawingBlock = 7305,
    PSPDFErrorCodeProcessorUnableToAddItem = 7306,
    PSPDFErrorCodeProcessorUnableToWriteFile = 7307,
    PSPDFErrorCodeProcessorMiscError = 7308,
    PSPDFErrorCodeProcessorCancelled = 7309,
    PSPDFErrorCodeProcessorFileExists = 7310,
    PSPDFErrorCodeProcessorUnableToReadFile = 7311,
    PSPDFErrorCodeProcessorServerError = 7312,
    PSPDFErrorCodeDocumentEditorUnableToWriteFile = 7400,
    PSPDFErrorCodeDocumentEditorInvalidDocument = 7401,
    PSPDFErrorCodeDocumentEditorInaccessibleDocument = 7402,
    PSPDFErrorCodeDocumentEditorOperationCancelled = 7403,
    PSPDFErrorCodeFailedToFetchResource = 8000,
    PSPDFErrorCodeFailedToSetResource = 8500,
    /// The operation cannot be completed because the data provider did not finish loading yet.
    PSPDFErrorCodeDataProviderIsInFlight = 8600,
    PSPDFErrorCodeJSONDeserializationError = 9500,
    PSPDFErrorCodeJSONSerializationError = 9501,
    PSPDFErrorCodeJSONSerializationUnsupportedAnnotationTypeError = 9502,
    PSPDFErrorCodeFeatureNotEnabled = 100000,
    PSPDFErrorCodeSecurityNoPermission = 200000,
    PSPDFErrorCodeSecurityOwnerPasswordNotSet = 200001,
    PSPDFErrorCodeSecurityInvalidKeyLength = 200002,
    PSPDFErrorCodePKCS12CannotReadData = 300000,
    PSPDFErrorCodePKCS12CannotCopyData = 300001,
    PSPDFErrorCodePKCS12UnlockFailed = 300002,
    PSPDFErrorCodePKCS12NoItemsFound = 300003,
    PSPDFErrorCodePKCS12NoPrivateKeyFound = 300004,
    PSPDFErrorCodePKCS12PrivateKeyError = 300005,
    PSPDFErrorCodePKCS12CertificateNotFound = 300006,
    PSPDFErrorCodePKCS12CertificateError = 300007,
    PSPDFErrorCodePKCS12WrongPassword = 300008,
    PSPDFErrorCodeSearchCouldNotLoadDocument = 400000,
    PSPDFErrorCodeShapeTransformationInvalidInput = 500000,
    PSPDFErrorCodeUnknown = NSIntegerMax,
} PSPDF_ENUM_SWIFT(PSPDFKitError);

NS_ASSUME_NONNULL_END
