//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

// Mac Catalyst does not yet support CoreSpotlight queries.
// Error Domain=NSCocoaErrorDomain Code=4097 "Couldn’t communicate with a helper application."
#define PSPDF_SPOTLIGHT_AVAILABLE !TARGET_OS_MACCATALYST
#if PSPDF_SPOTLIGHT_AVAILABLE

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

@class PSPDFLibrary, PSPDFDocument, CSSearchableIndex;

NS_ASSUME_NONNULL_BEGIN

/// This class observes its `PSPDFLibrary`'s underlying `PDFCDocumentLibrary`, and syncs the index index with CoreSpotlight, if enabled on the `PSPDFLibrary` object.
/// If Spotlight indexing is not supported on the device, that is, `+[CSSearchableIndex isIndexingAvailable]` returns NO, then this class does nothing.
PSPDF_TEST_CLASS_SWIFT(LibrarySpotlightIndexer)
@interface PSPDFLibrarySpotlightIndexer : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes an instance of the receiver.
- (instancetype)initWithLibrary:(PSPDFLibrary *)library NS_DESIGNATED_INITIALIZER;

/// The library with which to synchronize.
@property (atomic, weak, readonly) PSPDFLibrary *library;

/// The operation queue on which the indexer performs all its work.
@property (nonatomic, readonly) NSOperationQueue *indexingQueue;

@property (nonatomic, readonly) CSSearchableIndex *searchableIndex;

/// The library should call this method before it begins the indexing process, so that the indexer can interpose the library's notifications if necessary
- (void)noteLibraryWillBeginIndexing;

/// Checks if a document has been indexed for the specified user activity.
///
/// @param userActivity The user activity to check.
/// @return The document for the specified user activity if it exists, else NO
- (nullable PSPDFDocument *)indexedDocumentWithUserActivity:(NSUserActivity *)userActivity;

/// Removes documents with the specific UIDs indexed by spotlight.
///
/// @param uids The uids of the documents to be removed.
- (void)removeIndexedDocumentsWithUIDs:(NSArray<NSString *> *)uids;

/// Removes all documents from the index. Returns YES if successful.
- (BOOL)removeAllDocumentsFromIndex;

@end

NS_ASSUME_NONNULL_END

#endif
