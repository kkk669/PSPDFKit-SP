//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFSearchResult.h>

@class PSPDFDocument, PSPDFTextSearch;

NS_ASSUME_NONNULL_BEGIN

/// Search status delegate. All delegates are guaranteed to be called within the main thread.
PSPDF_PROTOCOL_SWIFT(TextSearchDelegate)
@protocol PSPDFTextSearchDelegate<NSObject>

@optional

/// Called when search is started.
- (void)willStartSearch:(PSPDFTextSearch *)textSearch term:(NSString *)searchTerm isFullSearch:(BOOL)isFullSearch;

/// Search was updated, a new page has been scanned.
/// Consider `page` a hint. There might be situations where this is called with a larger set of search results. page in this case is set to `NSNotFound`.
- (void)didUpdateSearch:(PSPDFTextSearch *)textSearch term:(NSString *)searchTerm newSearchResults:(NSArray<PSPDFSearchResult *> *)searchResults pageIndex:(PSPDFPageIndex)pageIndex;

/// Called when a text search operation was aborted due to an error.
///
/// @param textSearch The text search operation which was stopped.
/// @param error The error for which it was stopped.
- (void)didFailSearch:(PSPDFTextSearch *)textSearch withError:(NSError *)error;

/// Search has finished.
- (void)didFinishSearch:(PSPDFTextSearch *)textSearch term:(NSString *)searchTerm searchResults:(NSArray<PSPDFSearchResult *> *)searchResults isFullSearch:(BOOL)isFullSearch pageTextFound:(BOOL)pageTextFound;

/// Search has been cancelled.
- (void)didCancelSearch:(PSPDFTextSearch *)textSearch term:(NSString *)searchTerm isFullSearch:(BOOL)isFullSearch;

@end

/// Manages search operations for a specific document.
/// You can copy this class to be able to use it on your custom class. (and set a different delegate)
/// Copying will preserve all settings except the delegate.
PSPDF_CLASS_SWIFT(TextSearch)
@interface PSPDFTextSearch : NSObject<NSCopying, PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initialize with the document.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// Searches for text occurrence.
/// If document was not yet parsed, it will be now. Searches entire document.
/// Will search the whole document and cancel any previous search requests.
- (void)searchForString:(NSString *)searchTerm;

/// Searches for text on the specified page ranges. If ranges is nil, will search entire document.
/// If rangesOnly is set to NO, ranges will be searched first, then the rest of the document.
- (void)searchForString:(NSString *)searchTerm inRanges:(nullable NSIndexSet *)ranges rangesOnly:(BOOL)rangesOnly cancelOperations:(BOOL)cancelOperations;

/// Cancels all operations. Returns immediately.
- (void)cancelAllOperations;

/// Cancels all operations. Blocks current thread until all operations are processed.
///
/// @note Use `cancelAllOperations` if you don't with to wait until all operations are processed.
- (void)cancelAllOperationsAndWait;

/// Defaults to `NSCaseInsensitiveSearch|NSDiacriticInsensitiveSearch|NSWidthInsensitiveSearch|NSRegularExpressionSearch`.
/// With `NSDiacriticInsensitiveSearch`, e.g. an ö character will be treated like an o.
/// See NSString comparison documentation for details.
///
/// @note PSPDF has extensions that will allow a combination of `NSRegularExpressionSearch` and `NSDiacriticInsensitiveSearch`.
/// If `NSRegularExpressionSearch` is enabled, hyphenations and newlines between the body text will be ignored (which is good, better results)
@property (nonatomic) NSStringCompareOptions compareOptions;

/// Customizes the range of the preview string. Defaults to 20/160.
@property (nonatomic) NSRange previewRange;

/// Will include annotations that have a matching type into the search results. (contents will be searched).
///
/// @note Requires the `Features.annotationEditing` feature flag.
@property (nonatomic) PSPDFAnnotationType searchableAnnotationTypes;

/// We have to limit the number of search results to something reasonable. Defaults to 600.
@property (nonatomic) NSUInteger maximumNumberOfSearchResults;

/// The document that is searched.
@property (nonatomic, weak, readonly) PSPDFDocument *document;

/// The search delegate to be informed when search starts/updates/finishes.
@property (nonatomic, weak) id<PSPDFTextSearchDelegate> delegate;

/// The methods in this section provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: - Subclassing Hooks

/// Exposed internal search queue.
@property (nonatomic, readonly) NSOperationQueue *searchQueue;

@end

NS_ASSUME_NONNULL_END
