//
//  Copyright © 2010-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !__has_feature(objc_arc)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#endif

// MARK: Common
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFLocalization.h>
#import <PSPDFKit/PSPDFLogging.h>
#import <PSPDFKit/PSPDFMacros.h>
#import <PSPDFKit/PSPDFError.h>
#import <PSPDFKit/PSPDFNamespace.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFBaseConfiguration.h>
#import <PSPDFKit/PSPDFKitGlobal.h>
#import <PSPDFKit/PSPDFRotation.h>
#import <PSPDFKit/PSPDFDocument+DataDetection.h>
#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFDocumentProvider.h>
#import <PSPDFKit/PSPDFDocumentProviderDelegate.h>
#import <PSPDFKit/PSPDFDocumentSecurityOptions.h>
#import <PSPDFKit/PSPDFDocumentFeatures.h>
#import <PSPDFKit/PSPDFImageDocument.h>
#import <PSPDFKit/PSPDFFeatureMask.h>
#import <PSPDFKit/PSPDFFileManager.h>
#import <PSPDFKit/PSPDFFilePresenterCoordinator.h>
#import <PSPDFKit/PSPDFModelObject+NSCoding.h>
#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFPageBinding.h>
#import <PSPDFKit/PSPDFPageInfo.h>
#import <PSPDFKit/PSPDFRenderManager.h>
#import <PSPDFKit/PSPDFRenderOptions.h>
#import <PSPDFKit/PSPDFRenderQueue.h>
#import <PSPDFKit/PSPDFRenderRequest.h>
#import <PSPDFKit/PSPDFRenderTask.h>
#import <PSPDFKit/PSPDFDocumentCheckpointer.h>
#import <PSPDFKit/PSPDFDirectory.h>

// MARK: Networking
#import <PSPDFKit/PSPDFDownloadManager.h>
#import <PSPDFKit/PSPDFDownloadManagerPolicy.h>
#import <PSPDFKit/PSPDFReachabilityStatus.h>
#import <PSPDFKit/PSPDFRemoteContentObject.h>
#import <PSPDFKit/PSPDFRemoteFileObject.h>

// MARK: Processor
#import <PSPDFKit/PSPDFProcessor.h>
#import <PSPDFKit/PSPDFProcessorDelegate.h>
#import <PSPDFKit/PSPDFConversionOperation.h>
#import <PSPDFKit/PSPDFAttributedStringConversionOperation.h>
#import <PSPDFKit/PSPDFHTMLConversionOperation.h>
#import <PSPDFKit/PSPDFOfficeConversionOperation.h>
#import <PSPDFKit/PSPDFURLConversionOperation.h>
#import <PSPDFKit/PSPDFProcessorConfiguration.h>
#import <PSPDFKit/PSPDFProcessorItem.h>
#import <PSPDFKit/PSPDFProcessorItemBuilder.h>
#import <PSPDFKit/PSPDFDocumentEditor.h>
#import <PSPDFKit/PSPDFEditingChange.h>

// MARK: Data Provider
#import <PSPDFKit/PSPDFCoordinatedFileDataProvider.h>
#import <PSPDFKit/PSPDFDataContainerProvider.h>
#import <PSPDFKit/PSPDFDataContainerSink.h>
#import <PSPDFKit/PSPDFDataProviding.h>
#import <PSPDFKit/PSPDFFileDataProviding.h>
#import <PSPDFKit/PSPDFCoordinatedFileDataProviding.h>
#import <PSPDFKit/PSPDFDataSink.h>
#import <PSPDFKit/PSPDFFile.h>
#import <PSPDFKit/PSPDFFileDataProvider.h>
#import <PSPDFKit/PSPDFFileDataSink.h>
#import <PSPDFKit/PSPDFFileConflictResolution.h>

// MARK: Annotations
#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFAbstractShapeAnnotation.h>
#import <PSPDFKit/PSPDFTextMarkupAnnotation.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationAuthorState.h>
#import <PSPDFKit/PSPDFAnnotationManager.h>
#import <PSPDFKit/PSPDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFAnnotationSet.h>
#import <PSPDFKit/PSPDFAnnotationStyle.h>
#import <PSPDFKit/PSPDFAnnotationStyleManager.h>
#import <PSPDFKit/PSPDFAnnotationStyleManager+Defaults.h>
#import <PSPDFKit/PSPDFAnnotationSummarizer.h>
#import <PSPDFKit/PSPDFAssetAnnotation.h>
#import <PSPDFKit/PSPDFCaretAnnotation.h>
#import <PSPDFKit/PSPDFCircleAnnotation.h>
#import <PSPDFKit/PSPDFContainerAnnotationProvider.h>
#import <PSPDFKit/PSPDFDrawingPoint.h>
#import <PSPDFKit/PSPDFFileAnnotation.h>
#import <PSPDFKit/PSPDFFileAnnotationProvider.h>
#import <PSPDFKit/PSPDFFreeTextAnnotation.h>
#import <PSPDFKit/PSPDFHighlightAnnotation.h>
#import <PSPDFKit/PSPDFInkAnnotation.h>
#import <PSPDFKit/PSPDFLineAnnotation.h>
#import <PSPDFKit/PSPDFLinkAnnotation.h>
#import <PSPDFKit/PSPDFMeasurementAnnotation.h>
#import <PSPDFKit/PSPDFMeasurementModels.h>
#import <PSPDFKit/PSPDFNoteAnnotation.h>
#import <PSPDFKit/PSPDFPolyLineAnnotation.h>
#import <PSPDFKit/PSPDFPolygonAnnotation.h>
#import <PSPDFKit/PSPDFPopupAnnotation.h>
#import <PSPDFKit/PSPDFRedactionAnnotation.h>
#import <PSPDFKit/PSPDFRichMediaAnnotation.h>
#import <PSPDFKit/PSPDFScreenAnnotation.h>
#import <PSPDFKit/PSPDFSoundAnnotation.h>
#import <PSPDFKit/PSPDFSoundAnnotationController.h>
#import <PSPDFKit/PSPDFSquareAnnotation.h>
#import <PSPDFKit/PSPDFSquigglyAnnotation.h>
#import <PSPDFKit/PSPDFStampAnnotation.h>
#import <PSPDFKit/PSPDFStrikeOutAnnotation.h>
#import <PSPDFKit/PSPDFUnderlineAnnotation.h>
#import <PSPDFKit/PSPDFWidgetAnnotation.h>
#import <PSPDFKit/PSPDFAppearanceCharacteristics.h>
#import <PSPDFKit/PSPDFSignatureContainer.h>
#import <PSPDFKit/PSPDFAppearanceStreamGenerating.h>
#import <PSPDFKit/PSPDFDrawingContextAppearanceStreamGenerator.h>
#import <PSPDFKit/PSPDFRetainExistingAppearanceStreamGenerator.h>
#import <PSPDFKit/PSPDFFileAppearanceStreamGenerator.h>
#import <PSPDFKit/PSPDFRotatable.h>
#import <PSPDFKit/PSPDFAnnotationUpdate.h>
#import <PSPDFKit/PSPDFAnnotationStyleKey.h>

// MARK: Forms
#import <PSPDFKit/PSPDFButtonFormElement.h>
#import <PSPDFKit/PSPDFButtonFormField.h>
#import <PSPDFKit/PSPDFChoiceFormElement.h>
#import <PSPDFKit/PSPDFChoiceFormField.h>
#import <PSPDFKit/PSPDFFormElement.h>
#import <PSPDFKit/PSPDFFormField.h>
#import <PSPDFKit/PSPDFFormOption.h>
#import <PSPDFKit/PSPDFFormParser.h>
#import <PSPDFKit/PSPDFSignatureFormElement.h>
#import <PSPDFKit/PSPDFSignatureFormField.h>
#import <PSPDFKit/PSPDFTextFieldFormElement.h>
#import <PSPDFKit/PSPDFTextFormField.h>

// MARK: Actions
#import <PSPDFKit/PSPDFAbstractFormAction.h>
#import <PSPDFKit/PSPDFAction.h>
#import <PSPDFKit/PSPDFBackForwardActionList.h>
#import <PSPDFKit/PSPDFEmbeddedGoToAction.h>
#import <PSPDFKit/PSPDFGoToAction.h>
#import <PSPDFKit/PSPDFHideAction.h>
#import <PSPDFKit/PSPDFJavaScriptAction.h>
#import <PSPDFKit/PSPDFNamedAction.h>
#import <PSPDFKit/PSPDFRemoteGoToAction.h>
#import <PSPDFKit/PSPDFRenditionAction.h>
#import <PSPDFKit/PSPDFResetFormAction.h>
#import <PSPDFKit/PSPDFRichMediaExecuteAction.h>
#import <PSPDFKit/PSPDFSubmitFormAction.h>
#import <PSPDFKit/PSPDFURLAction.h>

// MARK: Digital Signatures
#import <PSPDFKit/PSPDFDigitalSignatureReference.h>
#import <PSPDFKit/PSPDFDocumentSignerDelegate.h>
#import <PSPDFKit/PSPDFDocumentSignerDataSource.h>
#import <PSPDFKit/PSPDFPKCS12.h>
#import <PSPDFKit/PSPDFPKCS12Signer.h>
#import <PSPDFKit/PSPDFPKCS7.h>
#import <PSPDFKit/PSPDFPrivateKey.h>
#import <PSPDFKit/PSPDFRSAKey.h>
#import <PSPDFKit/PSPDFBlankSignatureContents.h>
#import <PSPDFKit/PSPDFSignatureContents.h>
#import <PSPDFKit/PSPDFSignatureInfo.h>
#import <PSPDFKit/PSPDFSignatureManager.h>
#import <PSPDFKit/PSPDFSignaturePropBuild.h>
#import <PSPDFKit/PSPDFSignaturePropBuildEntry.h>
#import <PSPDFKit/PSPDFSignatureStatus.h>
#import <PSPDFKit/PSPDFSignatureValidator.h>
#import <PSPDFKit/PSPDFSignatureAppearance.h>
#import <PSPDFKit/PSPDFSignatureBiometricProperties.h>
#import <PSPDFKit/PSPDFSignatureType.h>
#import <PSPDFKit/PSPDFAnnotationAppearanceStream.h>
#import <PSPDFKit/PSPDFSigner.h>
#import <PSPDFKit/PSPDFX509.h>

// MARK: Search
#import <PSPDFKit/PSPDFGlyph.h>
#import <PSPDFKit/PSPDFImageInfo.h>
#import <PSPDFKit/PSPDFSearchResult.h>
#import <PSPDFKit/PSPDFTextBlock.h>
#import <PSPDFKit/PSPDFTextParser.h>
#import <PSPDFKit/PSPDFTextSearch.h>
#import <PSPDFKit/PSPDFWord.h>
#import <PSPDFKit/PSPDFGlyphRange.h>

// MARK: Full-Text Search
#import <PSPDFKit/PSPDFDatabaseEncryptionProvider.h>
#import <PSPDFKit/PSPDFFileIndexItemDescriptor.h>
#import <PSPDFKit/PSPDFLibrary.h>
#import <PSPDFKit/PSPDFLibraryFileSystemDataSource.h>
#import <PSPDFKit/PSPDFLibraryPreviewResult.h>

// MARK: Outline
#import <PSPDFKit/PSPDFOutlineElement.h>
#import <PSPDFKit/PSPDFOutlineParser.h>

// MARK: Bookmarks
#import <PSPDFKit/PSPDFBookmark.h>
#import <PSPDFKit/PSPDFBookmarkManager.h>
#import <PSPDFKit/PSPDFBookmarkProvider.h>

// MARK: Metadata
#import <PSPDFKit/PSPDFMetadataName.h>
#import <PSPDFKit/PSPDFDocumentPDFMetadata.h>
#import <PSPDFKit/PSPDFDocumentXMPMetadata.h>

// MARK: Embedded Files
#import <PSPDFKit/PSPDFEmbeddedFile.h>

// MARK: Labels
#import <PSPDFKit/PSPDFLabelParser.h>
#import <PSPDFKit/PSPDFPageLabelFormatter.h>

// MARK: Cache
#import <PSPDFKit/PSPDFCache.h>
#import <PSPDFKit/PSPDFDiskCache.h>
#import <PSPDFKit/PSPDFMemoryCache.h>

// MARK: Plugin
#import <PSPDFKit/PSPDFApplicationPolicy.h>

// MARK: XFDF
#import <PSPDFKit/PSPDFXFDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFXFDFParser.h>
#import <PSPDFKit/PSPDFXFDFWriter.h>

// MARK: View Model
#import <PSPDFKit/PSPDFAnnotationGroup.h>
#import <PSPDFKit/PSPDFAnnotationGroupItem.h>
#import <PSPDFKit/PSPDFAnnotationToolbarConfiguration.h>
#import <PSPDFKit/PSPDFColorPreset.h>

// MARK: Encryption
#import <PSPDFKit/PSPDFAESCryptoDataProvider.h>
#import <PSPDFKit/PSPDFAESCryptoDataSink.h>
#import <PSPDFKit/PSPDFAESCryptoInputStream.h>
#import <PSPDFKit/PSPDFAESCryptoOutputStream.h>
#import <PSPDFKit/PSPDFCryptoInputStream.h>
#import <PSPDFKit/PSPDFCryptoOutputStream.h>
#import <PSPDFKit/PSPDFCryptor.h>

// MARK: Editing
#import <PSPDFKit/PSPDFDocumentEditorConfiguration.h>
#import <PSPDFKit/PSPDFNewPageConfiguration.h>
#import <PSPDFKit/PSPDFNewPageConfigurationBuilder.h>
#import <PSPDFKit/PSPDFRectAlignment.h>
#import <PSPDFKit/PSPDFPageTemplate.h>

// MARK: Comparison
#import <PSPDFKit/PSPDFComparisonProcessor.h>
#import <PSPDFKit/PSPDFComparisonConfiguration.h>

// MARK: Swift API
#import <PSPDFKit/PSPDFKit-Swift.h>

#if !__has_feature(objc_arc)
#pragma clang diagnostic pop
#endif
