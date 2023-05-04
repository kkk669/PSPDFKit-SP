//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

// MARK: Base classes
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFAssert.h>
#import <PSPDFKit/PSPDFLogging+Private.h>
#import <PSPDFKit/PSPDFError+Private.h>
#import <PSPDFKit/PSPDFModelObject+Private.h>
#import <PSPDFKit/PSPDFDependencyInjection.h>
#import <PSPDFKit/PSPDFPathResolving.h>
#import <PSPDFKit/PSPDFFileManager+Private.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>

// MARK: Models
#import <PSPDFKit/PSPDFKitGlobal+Private.h>
#import <PSPDFKit/PSPDFDocument+Private.h>
#import <PSPDFKit/PSPDFDocument+Passwords.h>
#import <PSPDFKit/PSPDFDocumentProvider+Private.h>
#import <PSPDFKit/PSPDFDocumentProvider+Passwords.h>
#import <PSPDFKit/PSPDFDocumentProvider+JavaScriptAdditions.h>
#import <PSPDFKit/PSPDFDocument+Instant.h>
#import <PSPDFKit/PSPDFDocument+Validation.h>
#import <PSPDFKit/PSPDFDocumentSecurityOptions+Private.h>
#import <PSPDFKit/PSPDFDocumentCheckpointer+Private.h>
#import <PSPDFKit/PSPDFPage+Private.h>
#import <PSPDFKit/PSPDFPageInfo+Private.h>
#import <PSPDFKit/PSPDFLibrary+Private.h>
#import <PSPDFKit/PSPDFLibrarySpotlightIndexer.h>
#import <PSPDFKit/PSPDFFile+Private.h>
#import <PSPDFKit/PSPDFCache+Private.h>
#import <PSPDFKit/PSPDFDiskCache+Private.h>
#import <PSPDFKit/PSPDFMemoryCache+Private.h>
#import <PSPDFKit/PSPDFCacheStore.h>
#import <PSPDFKit/PSPDFAction+Private.h>
#import <PSPDFKit/PSPDFGoToAction+Private.h>
#import <PSPDFKit/PSPDFRemoteGoToAction+Private.h>
#import <PSPDFKit/PSPDFOutlineElement+Private.h>
#import <PSPDFKit/PSPDFOutlineParser+Private.h>
#import <PSPDFKit/PSPDFTextParser+Private.h>
#import <PSPDFKit/PSPDFGlyph+Private.h>
#import <PSPDFKit/PSPDFWord+Private.h>
#import <PSPDFKit/PSPDFTextBlock+Private.h>
#import <PSPDFKit/PSPDFParagraph.h>
#import <PSPDFKit/PSPDFSearchResult+Private.h>
#import <PSPDFKit/PSPDFAnnotationStyleManager+Private.h>
#import <PSPDFKit/PSPDFBorderStylePreset.h>
#import <PSPDFKit/PSPDFValueTransformer+Private.h>
#import <PSPDFKit/PSPDFImageDocument+Private.h>
#import <PSPDFKit/PSPDFBaseDocumentFeatures.h>
#import <PSPDFKit/PSPDFDocumentFeatures+Private.h>
#import <PSPDFKit/PSPDFImageInfo+Private.hpp>
#import <PSPDFKit/PSPDFAnnotationSummarizer+Private.h>
#import <PSPDFKit/NSValueTransformer+PSPDFModel.h>
#import <PSPDFKit/NSValueTransformer+UIFontAttributes.h>
#import <PSPDFKit/PSPDFEmbeddedGoToAction+Private.h>

// MARK: Annotation Models
#import <PSPDFKit/PSPDFAnnotation+Private.h>
#import <PSPDFKit/PSPDFFreeTextAnnotation+Private.h>
#import <PSPDFKit/PSPDFInkAnnotation+Private.h>
#import <PSPDFKit/PSPDFStampAnnotation+Private.h>
#import <PSPDFKit/PSPDFSoundAnnotation+Private.h>
#import <PSPDFKit/PSPDFFormElement+Private.h>
#import <PSPDFKit/PSPDFSignatureFormElement+Private.h>
#import <PSPDFKit/PSPDFTextFieldFormElement+Private.h>
#import <PSPDFKit/PSPDFChoiceFormElement+Private.h>
#import <PSPDFKit/PSPDFFormField+Private.h>
#import <PSPDFKit/PSPDFFormParser+Private.h>
#import <PSPDFKit/PSPDFAbstractLineAnnotation+Private.h>
#import <PSPDFKit/PSPDFAbstractShapeAnnotation+Private.h>
#import <PSPDFKit/PSPDFLineHelper.h>
#import <PSPDFKit/PSPDFTextHelper.h>
#import <PSPDFKit/PSPDFPointArray.h>
#import <PSPDFKit/PSPDFQuadrilateral.h>
#import <PSPDFKit/PSPDFNaturalDrawingPaths.h>
#import <PSPDFKit/PSPDFJavaScriptFormField.h>
#import <PSPDFKit/PSPDFAnnotationReviewSummary.h>
#import <PSPDFKit/PSPDFGraphicsState.h>
#import <PSPDFKit/PSPDFGraphicsState+Private.h>
#import <PSPDFKit/PSPDFLinkAnnotation+Private.h>
#import <PSPDFKit/PSPDFAnnotationAppearanceStream+Private.h>
#import <PSPDFKit/PSPDFRedactionTracker.h>
#import <PSPDFKit/PSPDFRotatableInternal.h>
#import <PSPDFKit/PSPDFEraserAnnotation.h>
#import <PSPDFKit/PSPDFUndefinedAnnotation.h>
#import <PSPDFKit/PSPDFWidgetAnnotation+Private.h>

// MARK: Config Classes
#import <PSPDFKit/PSPDFAnnotationGroup+Private.h>
#import <PSPDFKit/PSPDFAnnotationGroupItem+Private.h>
#import <PSPDFKit/PSPDFAnnotationToolbarConfiguration+Private.h>
#import <PSPDFKit/PSPDFDocumentEditorConfiguration+Private.h>
#import <PSPDFKit/PSPDFDocumentEditor+Private.h>

// MARK: Class Helper
#import <PSPDFKit/PSPDFKeychain.h>
#import <PSPDFKit/PSPDFLicenseManager.h>
#import <PSPDFKit/PSPDFOverrideClass.h>
#import <PSPDFKit/PSPDFRegularExpression.h>
#import <PSPDFKit/PSPDFFileCategorizer.h>
#import <PSPDFKit/PSPDFDownloadManagerGlobalPolicy.h>
#import <PSPDFKit/PSPDFDownloadManager+Private.h>
#import <PSPDFKit/PSPDFAnnotationMapper.h>
#import <PSPDFKit/PSPDFSecurityScopedURL.h>
#import <PSPDFKit/PSPDFSerialInputStream.h>

// MARK: Rendering
#import <PSPDFKit/PSPDFRenderRequest+Private.h>
#import <PSPDFKit/PSPDFRenderManager+Private.h>
#import <PSPDFKit/PSPDFRenderQueue+Private.h>
#import <PSPDFKit/PSPDFRenderTask+Private.h>
#import <PSPDFKit/PSPDFRenderOptions+Private.h>
#import <PSPDFKit/PSPDFContextPostProcessor.h>
#import <PSPDFKit/PSPDFCorePageRenderer.h>
#import <PSPDFKit/PSPDFCorePageRenderer+Private.h>
#import <PSPDFKit/PSPDFImageFile.h>
#import <PSPDFKit/PSPDFFDFWriter.h>

// MARK: General Helper
#import <PSPDFKit/PSPDFFontDownloader.h>
#import <PSPDFKit/PSPDFSearchHelper.h>
#import <PSPDFKit/PSPDFWikipediaHelper.h>
#import <PSPDFKit/PSPDFStatisticsGenerator.h>
#import <PSPDFKit/PSPDFBinarySearch.h>
#import <PSPDFKit/PSPDFFeatureFlags.h>

// MARK: Localization
#import <PSPDFKit/PSPDFLocalization+Private.h>
#import <PSPDFKit/PSPDFLocalizedStringKeys.h>
#import <PSPDFKit/PSPDFAnnotationPropertyLocalization.h>

// MARK: Crypto
#import <PSPDFKit/PSPDFAESDecryptor.h>
#import <PSPDFKit/PSPDFAESEncryptor.h>
#import <PSPDFKit/PSPDFSigner+Private.h>

// MARK: Core
#import <PSPDFKit/PDFCFilesCache.h>

// MARK: List diffing
#import <PSPDFKit/PSPDFListCompatibility.h>
#import <PSPDFKit/NSNumber+PSPDFListDiffable.h>
#import <PSPDFKit/NSString+PSPDFListDiffable.h>
#import <PSPDFKit/PSPDFListBatchUpdateData.h>
#import <PSPDFKit/PSPDFListDiff.h>
#import <PSPDFKit/PSPDFListDiffable.h>
#import <PSPDFKit/PSPDFListExperiments.h>
#import <PSPDFKit/PSPDFListIndexPathResult.h>
#import <PSPDFKit/PSPDFListIndexSetResult.h>
#import <PSPDFKit/PSPDFListMoveIndex.h>
#import <PSPDFKit/PSPDFListMoveIndexPath.h>
#import <PSPDFKit/PSPDFIndexPathMove.h>
#import <PSPDFKit/PSPDFIndexPathDiff.h>
#import <PSPDFKit/PSPDFBookmarkListDataSource.h>
#import <PSPDFKit/PSPDFBookmarkListDataSourceDelegate.h>
#import <PSPDFKit/PSPDFBookmark+PSPDFListDiffable.h>
#import <PSPDFKit/PSPDFBookmarkManager+Private.h>

// MARK: Categories
#import <PSPDFKit/UIImage+PSPDFModelPrivate.h>
#import <PSPDFKit/UIColor+PSPDFModel.h>
#import <PSPDFKit/UIScreen+PSPDFAdditions.h>
#import <PSPDFKit/NSNotificationCenter+PSPDFMediaPlayback.h>
#import <PSPDFKit/UIFont+PSPDFModel.h>
#import <PSPDFKit/UIFontDescriptor+PSPDFDiscovery.h>

// MARK: Foundation Helpers
#import <PSPDFKit/PSPDFAvailability.h>
#import <PSPDFKit/PSPDFDebouncedTimer.h>
#import <PSPDFKit/PSPDFDebouncedBlock.h>
#import <PSPDFKit/PSPDFDispatch.h>
#import <PSPDFKit/PSPDFDispatchQueue.h>
#import <PSPDFKit/PSPDFFastEnumeration.h>
#import <PSPDFKit/PSPDFKVOController.h>
#import <PSPDFKit/PSPDFRuntime.h>
#import <PSPDFKit/PSPDFGeometry.h>
#import <PSPDFKit/PSPDFDelegateProxy.h>
#import <PSPDFKit/PSPDFMulticastDelegate.h>
#import <PSPDFKit/PSPDFCollectionNullability.h>
#import <PSPDFKit/PSPDFRecursiveReadWriteLock.h>
#import <PSPDFKit/PSPDFCoordinatedFileDataProvider+Private.h>
#import <PSPDFKit/PSPDFFileChangeTracker.h>
#import <PSPDFKit/PSPDFCompletionCallingProgress.h>

// MARK: Data Structures
#import <PSPDFKit/PSPDFLazyArray.h>
#import <PSPDFKit/PSPDFOrderedDictionary.h>
#import <PSPDFKit/PSPDFTaskCollection.h>
#import <PSPDFKit/PSPDFThreadSafeMutableDictionary.h>
#import <PSPDFKit/PSPDFReachabilityObserver.h>
#import <PSPDFKit/PSPDFReusableObjectCache.h>

// MARK: Shape Detection
#import <PSPDFKit/PSPDFShapeDetector.h>
#import <PSPDFKit/PSPDFShapeTemplate.h>
#import <PSPDFKit/PSPDFShapeTemplateIdentifier.h>
#import <PSPDFKit/PSPDFShapeTemplateStore.h>

// MARK: Foundation Categories
#import <PSPDFKit/NSObject+PSPDFHooks.h>
#import <PSPDFKit/NSObject+PSPDFFoundation.h>
#import <PSPDFKit/NSString+PSPDFURLTypeDetection.h>
#import <PSPDFKit/NSURL+PSPDFFoundation.h>
#import <PSPDFKit/NSURL+PSPDFSanitize.h>
#import <PSPDFKit/UIImage+PSPDFFoundation.h>
#import <PSPDFKit/UIImage+PSPDFSerialization.h>
#import <PSPDFKit/NSArray+PSPDFFoundation.h>
#import <PSPDFKit/NSBundle+PSPDFFoundation.h>
#import <PSPDFKit/NSCoder+PSPDFSecureCoding.h>
#import <PSPDFKit/NSData+PSPDFFoundation.h>
#import <PSPDFKit/NSDate+PSPDFFoundation.h>
#import <PSPDFKit/NSDictionary+PSPDFFoundation.h>
#import <PSPDFKit/NSError+PSPDFFoundation.h>
#import <PSPDFKit/NSHashTable+PSPDFFoundation.h>
#import <PSPDFKit/NSIndexSet+PSPDFFoundation.h>
#import <PSPDFKit/NSNotificationCenter+PSPDFFoundation.h>
#import <PSPDFKit/NSNumber+PSPDFFoundation.h>
#import <PSPDFKit/NSObject+PSPDFFoundation.h>
#import <PSPDFKit/NSScanner+PSPDFFoundation.h>
#import <PSPDFKit/NSSet+PSPDFFoundation.h>
#import <PSPDFKit/NSString+FileSizeFormatting.h>
#import <PSPDFKit/NSString+PSPDFFoundation.h>
#import <PSPDFKit/NSUserDefaults+PSPDFFoundation.h>
#import <PSPDFKit/NSURL+PSPDFFileHelper.h>
#import <PSPDFKit/UIColor+PSPDFFoundation.h>
#import <PSPDFKit/CALayer+PSPDFFoundation.h>
#import <PSPDFKit/NSOrderedSet+PSPDFFoundation.h>
#import <PSPDFKit/NSPointerArray+PSPDFFoundation.h>
#import <PSPDFKit/NSProgress+PSPDFFoundation.h>
#import <PSPDFKit/NSFileCoordinator+PSPDFKit.h>
#import <PSPDFKit/NSProgress+PSPDFFoundation.h>
#import <PSPDFKit/NSOperation+PSPDFFoundation.h>
#import <PSPDFKit/NSOperationQueue+PSPDFFoundation.h>
#import <PSPDFKit/NSFileManager+PSPDFFoundation.h>
#import <PSPDFKit/PSPDFSuperclassLookup.h>
#import <PSPDFKit/NSValue+PSPDFExtensions.h>

// MARK: Database
#import <PSPDFKit/PSPDFDatabase.h>
#import <PSPDFKit/PSPDFDatabaseManager.h>
#import <PSPDFKit/PSPDFDatabaseQueue.h>
#import <PSPDFKit/PSPDFResultSet.h>

// MARK: Exported for Tests
#import <PSPDFKit/PSPDFLibrary+Testing.h>
#import <PSPDFKit/PSPDFLibraryFileSystemDataSource+Private.h>
#import <PSPDFKit/PSPDFCacheDocumentHashManager.h>
#import <PSPDFKit/PSPDFCacheMetadata.h>
#import <PSPDFKit/PSPDFFilePresenterCoordinator+Private.h>
#import <PSPDFKit/PSPDFCacheInfo.h>
#import <PSPDFKit/PSPDFDiskCache+Private.h>
#import <PSPDFKit/PSPDFDiskCacheDatabase.h>
#import <PSPDFKit/PSPDFLock.h>
#import <PSPDFKit/PSPDFDocumentCheckpointCleaner.h>
#import <PSPDFKit/PSPDFDocumentCheckpointer+Private.h>
#import <PSPDFKit/PSPDFAPStreamDocumentGenerator+Tests.h>
#import <PSPDFKit/PSPDFAnnotation+Core.h>
#import <PSPDFKit/PSPDFCoreAnnotation.h>
#import <PSPDFKit/PSPDFCoreAnnotationSyncOption.h>
#import <PSPDFKit/NSDate+PSPDFModel.h>
#import <PSPDFKit/PSPDFFileChangeTracker+Testing.h>
#import <PSPDFKit/PSPDFChangeTrackingDocumentUpdater+Testing.h>
#import <PSPDFKit/PSPDFDispatchQueue+Private.h>
#import <PSPDFKit/PSPDFSearchOperation.h>
#import <PSPDFKit/PSPDFDocumentValidator.h>
#import <PSPDFKit/PSPDFiOSToCoreDeserializationHelper.h>
#import <PSPDFKit/PSPDFCoreNotificationHandler.h>

// :MARK Objective-C++ additions
#import <PSPDFKit/PSPDFObjectiveCppBridge.hpp>
#import <PSPDFKit/PSPDFLineHelper.hpp>
#import <PSPDFKit/PSPDFDrawingPoint.hpp>
#import <PSPDFKit/PSPDFPointArray.hpp>

// MARK: Instant
#import <PSPDFKit/PSPDFAnnotationManager+Private.h>
#import <PSPDFKit/PSPDFAnnotationProvider+Private.h>
#import <PSPDFKit/PSPDFAnnotationViewMapper.h>
#import <PSPDFKit/PSPDFFileDataProvider+Private.h>
#import <PSPDFKit/PSPDFInstantAnnotationProvider.h>
#import <PSPDFKit/PSPDFInstantHTTPClient.h>

// MARK: Measurements
#import <PSPDFKit/PSPDFMeasurementLabelFormatter.h>
#import <PSPDFKit/PSPDFMeasurementModels+Private.h>
#import <PSPDFKit/PSPDFMeasurementSnapper.h>

// MARK: JavaScript
#import <PSPDFKit/PSPDFJavaScriptAPI.h>
#import <PSPDFKit/PSPDFJSPlatformDelegate.h>
#import <PSPDFKit/PSPDFJSScriptDescriptor.h>
#import <PSPDFKit/PSPDFJavaScriptActionEvent.h>
#import <PSPDFKit/PSPDFJavaScriptAction+Private.h>
#import <PSPDFKit/PSPDFJSResult.h>

// MARK: Audio
#import <PSPDFKit/PSPDFAudioSessionManager.h>

// MARK: Reader View
#import <PSPDFKit/PSPDFReflowOperation.h>

// MARK: OCR
#import <PSPDFKit/PSPDFProcessorConfiguration+OCRPrivate.h>

// MARK: Undo
#import <PSPDFKit/PSPDFUndoDiffable.h>
#import <PSPDFKit/PSPDFUndoLocalization.h>

// MARK: MacCatalyst
#if TARGET_OS_IOS
#import <PSPDFKit/PSPDFAppKitHelper.h>
#endif

// MARK: MacOS
#if TARGET_OS_OSX
#import <PSPDFKit/PSPDFMacOSCompatibility.h>
#endif
