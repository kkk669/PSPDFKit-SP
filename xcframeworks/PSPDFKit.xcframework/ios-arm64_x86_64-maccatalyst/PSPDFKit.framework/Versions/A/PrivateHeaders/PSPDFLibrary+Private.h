//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFLibrary.h>

@protocol PSPDFDatabaseEncryptionProvider;

/// Options for enqueueing documents. Same as PDFCLibraryEnqueueOptions.
/// By default, the document library will not index documents that are already indexed, nor will it send the observers notifications.
typedef NS_OPTIONS(NSUInteger, PSPDFLibraryEnqueueOptions)
{
    /// No flags
    PSPDFLibraryEnqueueOptionsNone = 0,
    /// Force a re-index, even if the document is already in our database. This will notify observers and perform the requisite database operations.
    PSPDFLibraryEnqueueOptionsForceReIndex = 1 << 0,
    /// Don't index the document if it exists, only call the observer callbacks and update metadata, without performing any database operations.
    PSPDFLibraryEnqueueOptionsDontIndexIfExists = 1 << 1,
    /// Ignores annotations in the document
    PSPDFLibraryEnqueueOptionsIgnoreAnnotations = 1 << 2,
    /// Ignored document text. For use when descriptor with annotations are enqueued.
    PSPDFLibraryEnqueueOptionsIgnoreDocumentText = 1 << 3,
};

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PDFCDocumentLibraryQuery, PSPDFLibrarySpotlightIndexer;

@interface PSPDFLibrary ()

/// Sets the maximum number of concurrent operations.
@property (nonatomic) NSUInteger maxConcurrentOperations;

/// Initializes a new library. Convenience initializer.
///
/// @param path The path (directory) at which the library is to be created.
/// @param keyProvider The encryption key provider. If nil, the library is unencrypted.
/// @param priority The indexing priority.
/// @param ftsVersion The fts version to use. Will cause an error if the specified version is unavailable.
/// @param tokenizer The tokenizer to use. Uses the internal default porter if nil.
/// @param error The error, if any that occurred during initialization.
- (nullable instancetype)initWithPath:(NSString *)path encryptionKeyProvider:(nullable NSData * (^)(void))keyProvider indexingPriority:(PSPDFLibraryIndexingPriority)priority ftsVersion:(PSPDFLibraryFTSVersion)ftsVersion tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

/// Initializes a new library. Convenience initializer.
///
/// @param path The path (directory) at which the library is to be created.
/// @param lowMemoryMode Specifies if the library must use low memory.
/// @param keyProvider The encryption key provider. If nil, the library is unencrypted.
/// @param databaseEncryptionProvider The provider to encrypt the database.
/// @param priority The indexing priority.
/// @param ftsVersion The fts version to use. Will cause an error if the specified version is unavailable.
/// @param tokenizer The tokenizer to use. Uses the internal default porter if nil.
/// @param error The error, if any that occurred during initialization.
- (nullable instancetype)initWithPath:(NSString *)path lowMemoryMode:(BOOL)lowMemoryMode encryptionKeyProvider:(nullable NSData * (^)(void))keyProvider databaseEncryptionProvider:(nullable id<PSPDFDatabaseEncryptionProvider>)databaseEncryptionProvider indexingPriority:(PSPDFLibraryIndexingPriority)priority ftsVersion:(PSPDFLibraryFTSVersion)ftsVersion tokenizer:(nullable NSString *)tokenizer error:(NSError **)error;

/// Updates the index by asking the data source for information.
///
/// @param completionHandler The block to call after all documents have been indexed.
/// @param enqueueHandler The block to call after documents to be indexed have been placed in the queue.
///
/// @warning The blocks may be called on a background thread.
- (void)updateIndexWithCompletionHandler:(nullable dispatch_block_t)completionHandler enqueueHandler:(nullable dispatch_block_t)enqueueHandler;

/// Enqueues the documents with the specified options to be passed into the Core Document Library.
///
/// @param documents The documents to be queued.
/// @param options The options with which the documents are to be indexed.
- (void)enqueueDocuments:(NSArray<PSPDFDocument *> *)documents options:(PSPDFLibraryEnqueueOptions)options;

@end

NS_ASSUME_NONNULL_END
