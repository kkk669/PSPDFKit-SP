//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFSearchOperation, PSPDFSearchResult;

/// Get updates while the search operation is running.
@protocol PSPDFSearchOperationDelegate <NSObject>

/// Search was updated, a new page has been scanned.
- (void)didUpdateSearchOperation:(PSPDFSearchOperation *)operation forString:(NSString *)searchTerm newSearchResults:(NSArray<PSPDFSearchResult *> *)searchResults forPageAtIndex:(PSPDFPageIndex)pageIndex;

@optional

/// Called when search is started.
- (void)willStartSearchOperation:(PSPDFSearchOperation *)operation forString:(NSString *)searchTerm isFullSearch:(BOOL)isFullSearch;

/// Called if an error occurs during the search.
- (void)didFailSearchOperation:(PSPDFSearchOperation *)operation withError:(NSError *)error;

@end

/// Search operation to find text inside a all or specific pages of a `Document`.
/// Settings need to be configured before the operation is started.
@interface PSPDFSearchOperation : NSOperation<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initialize with document reference and the search term. Raises an exception if `document` is locked or invalid.
- (instancetype)initWithDocument:(PSPDFDocument *)document searchTerm:(NSString *)searchTerm NS_DESIGNATED_INITIALIZER;

/// Customize range of pages that should be searched. Set to nil to search whole document.
@property (nonatomic, copy, nullable) NSIndexSet *pageRanges;

/// If set to YES, `pageRanges` will be searched first, then all following pages.
/// If NO, only `pageRanges` will be searched.
/// Defaults to YES.
@property (nonatomic) BOOL shouldSearchAllPages;

/// We have to limit the number of search results to something reasonable (memory constraints)
/// Defaults to 600.
@property (nonatomic) NSUInteger maximumNumberOfSearchResults;

/// Set the text compare options for the search operation.
/// Defaults to `NSCaseInsensitiveSearch|NSDiacriticInsensitiveSearch|NSWidthInsensitiveSearch|NSRegularExpressionSearch`.
@property (nonatomic) NSStringCompareOptions compareOptions;

/// Will include annotations that have a matching type into the search results. (contents will be searched).
///
/// @note Requires the `Features.annotationEditing` feature flag.
@property (nonatomic) PSPDFAnnotationType searchableAnnotationTypes;

/// Search delegate.
/// Allows calling back when new search results are ready.
@property (nonatomic, weak) id<PSPDFSearchOperationDelegate> delegate;

/// Array of `PSPDFSearchResult` (will be set once the operation is finished)
///
/// @note Thread-safe. Can be accessed while the operation is running.
@property (nonatomic, copy, readonly) NSArray<PSPDFSearchResult *> *searchResults;

/// Current search term.
@property (nonatomic, copy, readonly) NSString *searchTerm;

/// Associated document.
@property (nonatomic, weak, readonly) PSPDFDocument *document;

/// Call after operation completed. Will be NO if no page text was found.
@property (nonatomic, readonly) BOOL pageTextFound;

@end

@interface PSPDFSearchOperation (Advanced)

/// Customize start/length of the preview string, in relation to the found element.
/// Defaults to 20/160.
@property (nonatomic) NSRange previewRange;

@end

NS_ASSUME_NONNULL_END
