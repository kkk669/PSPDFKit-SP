//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDataProviding.h>
#import <PSPDFKit/PSPDFDocumentProvider.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

@protocol PSPDFCustomConcurrentQueue, PSPDFFileManager, PSPDFJSPlatformDelegate;
@class PDFCDocumentProvider, PDFCPage, PSPDFAnnotation, PSPDFCoreFormProvider, PSPDFDispatchQueue, PSPDFPageInfo, PSPDFResourceManager;

NS_ASSUME_NONNULL_BEGIN

/// Delivered when an action, including a JavaScript action, has finished execution.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFActionFinishedExecutionNotification;

@interface PSPDFDocumentProvider () <PSPDFOverrideProvider>

/// Initialize with an object conforming to `DataProviding`.
- (instancetype)initWithDataProvider:(id<PSPDFDataProviding>)dataProvider index:(NSUInteger)index document:(PSPDFDocument *)document coreDocumentProvider:(nullable PDFCDocumentProvider *)coreDocumentProvider contentSignature:(nullable NSData *)contentSignature isLocked:(BOOL)isLocked NS_DESIGNATED_INITIALIZER;

/// Called by the document after establishing the document <->> provider relationship to finalize setup.
///
/// Avoids complex, and deadlock-prone lazy initialization such as setting up the core form provider.
- (void)awakeAfterEstablishingConnectionToDocument:(PSPDFDocument *)document NS_REQUIRES_SUPER;

/// Specifies the maximum number of alternate documents.
///
/// Alternate documents are used in Core to render "multi-threaded".
/// By default, this is in the range of 0-4, depending on hardware CPUs available.
@property (nonatomic) NSUInteger maximumNumberOfAlternateDocuments;

/// Index of the array of document providers in the parent document.
///
/// @note Core API references internal document providers via index. This is a helper for that.
/// If we access the document and then document providers, we could run into a race where they are already deallocated
/// And subsequently cause a document provider reload. Caching seems the more sensible approach.
@property (nonatomic, readonly) NSUInteger index;

/// The file manager used to for file access for this document provider
@property (nonatomic, readonly) id<PSPDFFileManager> fileManager;

/// Queries the PageInfo, but doesn't fetch new data.
- (nullable PSPDFPageInfo *)pageInfoForPageIndexNoFetching:(PSPDFPageIndex)pageIndex;

/// The range of the pageIndexes in the associated document.
@property (nonatomic, readonly) NSRange rangeInDocument;

/// Helper that resolves a tokenized path to an URL.
- (nullable NSURL *)URLForTokenizedPath:(NSString *)path;

/// Checks if the text parser has already been loaded.
- (BOOL)hasLoadedTextParserForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Clear all text parsers, releases memory.
- (void)clearAllTextParsers;

/// Builds the page info cache to access page info fast (might need a pdfium lock if not cached)
- (void)fillPageInfoCache;

/// Output saved content to a file.
- (BOOL)writeToFile:(NSString *)path error:(NSError **)error;

/// Returns `true` if the associated data provider can be written to.
@property (nonatomic, readonly) BOOL canWriteToDataProvider;

/// Invalidates the receiver in a deterministic manner.
- (void)invalidate;

/// Queue that coordinates reads and writes to annotation properties.
@property (nonatomic, readonly) PSPDFDispatchQueue<PSPDFCustomConcurrentQueue> *annotationPropertyAccessQueue;

/// Whether there are (or might be) unsaved annotation changes. This adds some additional checks on top of annotationManager.shouldSaveAnnotations.
@property (nonatomic, readonly) BOOL shouldSaveAnnotations;

@end

@interface PSPDFDocumentProvider (JavaScript)

/// Returns the document-level JavaScript objects, if any.
@property (nonatomic, readonly) NSArray<NSString *> *documentLevelJavaScripts;

/// Sets the JavaScript platform delegate for this document provider, responsible for implementing the part of the
/// JavaScript API that cannot be implemented in Core.
- (void)setJavaScriptDelegate:(id<PSPDFJSPlatformDelegate>)delegate;

/// Evaluates JavaScript scripts that are linked to the "Doc Open" event, that is, triggered when the user
/// presents a document in a view controller, or calls `loadDocumentLevelJavaScriptActionsWithError:` explicitly on a
/// `Document` instance.
- (BOOL)loadDocumentLevelJavaScriptActions:(NSError **)error;

@end

@interface PSPDFDocumentProvider (PSPDFInternals)

/// Access internal PDF core document provider.
@property (atomic, nullable, readonly) PDFCDocumentProvider *coreDocumentProvider;

/// Retrieves the `PDFCPage`. Handles all possible exceptions.
- (nullable PDFCPage *)pageForPageAtIndex:(PSPDFPageIndex)pageIndex error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
