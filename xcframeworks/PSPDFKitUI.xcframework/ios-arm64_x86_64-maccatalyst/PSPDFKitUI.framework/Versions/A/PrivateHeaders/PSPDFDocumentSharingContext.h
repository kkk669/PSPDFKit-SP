//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFDocument+Private.h>
#import <PSPDFKitUI/PSPDFDocumentSharingConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/// The max number of pages that a user can export as images at once from a document.
static const NSInteger PSPDFDocumentSharingAsImagePageLimit = 20;

@class PSPDFDocumentSharingContext, PSPDFFile;

@protocol PSPDFVisiblePagesDataSource;

/// Protocol that lets consumers interact get notified of the work that's going on
/// in the sharing context realm.
NS_SWIFT_NAME(PDFDocumentSharingContextDelegate)
@protocol PSPDFDocumentSharingContextDelegate

@optional

/// Tells the delegate that the sharing configurations in the context were updated so that it can perform
/// any UI updates necessary.
///
/// @param sharingContext  The context that's notifying the delegate.
- (void)documentSharingContextDidUpdateSharingConfigurations:(PSPDFDocumentSharingContext *)sharingContext;

/// Tells the delegate that the documents in the context were updated so that it can perform
/// any UI updates necessary.
///
/// @param sharingContext  The context that's notifying the delegate.
- (void)documentSharingContextDidUpdateDocuments:(PSPDFDocumentSharingContext *)sharingContext;

@end

/// A `PSPDFDocumentSharingContext` holds information related to the sharing of some documents via `PDFDocumentSharingViewController`.
///
/// @note The sharing context does not hold state — that's handled by `PDFDocumentSharingViewController`.
NS_SWIFT_NAME(PDFDocumentSharingContext)
PSPDF_APP_EXPORT @interface PSPDFDocumentSharingContext : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Creates a sharing context from the given documents and configurations.
///
/// @param documents The documents to share.
/// @param sharingConfigurations The sharing configurations.
- (instancetype)initWithDocuments:(NSArray<PSPDFDocument *> *)documents sharingConfigurations:(NSArray<PSPDFDocumentSharingConfiguration *> *)sharingConfigurations NS_DESIGNATED_INITIALIZER;

/// The documents being shared. Set when initializing.
@property (nonatomic, readonly) NSArray<PSPDFDocument *> *documents;

/// The files that were generated as a result of the documents being shared.
@property (nonatomic, nullable) NSArray<PSPDFFile *> *generatedFiles;

/// The configurations that the user can pick from to share the documents. Set when initializing.
@property (nonatomic, readonly) NSArray<PSPDFDocumentSharingConfiguration *> *sharingConfigurations;

/// The destinations that are currently available based on the provided configurations.
@property (nonatomic, readonly) NSArray<PSPDFDocumentSharingDestination> *availableDestinations;

/// `true` if at least one document in the context is an image.
@property (nonatomic, readonly) BOOL atLeastOneDocumentIsImage;

/// Whether all the documents are images.
@property (nonatomic, readonly) BOOL documentsAreImages;

/// Whether every document is single page.
@property (nonatomic, readonly) BOOL documentsAreSinglePage;

/// Whether the documents have original files (defaults to YES for image documents.)
@property (nonatomic, readonly) BOOL documentsHaveOriginalFiles;

/// The sum of the page count for all the documents in this context.
@property (nonatomic, readonly) NSUInteger totalPageCount;

/// Annotation types that are relevant for sharing documents.
@property (nonatomic, readonly) PSPDFAnnotationType relevantAnnotationTypes;

/// The data source that tells the delegate which pages are visible so that the user can pick from them when sharing documents.
///
/// Set this property, but don’t read from it. If you want to know which page is visible, use `mainVisiblePageIndex`
/// instead of `visiblePagesDataSource.pageIndex`.
@property (nonatomic, weak) id<PSPDFVisiblePagesDataSource> visiblePagesDataSource;

/// The index of a single page that should be considered the current visible page.
///
/// This will be the index of the first page in the spread that is at the center of the viewport.
@property (nonatomic, readonly) PSPDFPageIndex mainVisiblePageIndex;

/// Returns a BOOL indicating whether the UI that this context is attached to should hide the dynamic page selection options
/// (All and Annotated) for a given file format, based on the total page count in the context.
- (BOOL)shouldRestrictDynamicPageSelectionOptionsForFileFormat:(PSPDFDocumentSharingFileFormatOptions)fileFormatOption;

/// Sets the sharing configurations on the context, and notifies the delegates about it if `notifyDelegates` is `true`.
///
/// @param sharingConfigurations   The new configurations to set on the context.
/// @param notifyDelegates         Whether the delegates should be notified about the configurations update.
- (void)setSharingConfigurations:(NSArray<PSPDFDocumentSharingConfiguration *> *)sharingConfigurations notifyDelegates:(BOOL)notifyDelegates;

/// Sets the documents on the context, and notifies the delegates about it if `notifyDelegates` is `true`.
///
/// @param documents           The new documents to set on the context.
/// @param notifyDelegates     Whether the delegates should be notified about the documents update.
- (void)setDocuments:(NSArray<PSPDFDocument *> *)documents notifyDelegates:(BOOL)notifyDelegates;

/// Adds a delegate to the delegate list.
///
/// Be sure to call `removeDelegate` when you don't need to keep track of the progress anymore.
- (void)addDelegate:(id<PSPDFDocumentSharingContextDelegate>)delegate;

/// Removes a delegate from the delegate list.
- (void)removeDelegate:(id<PSPDFDocumentSharingContextDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
