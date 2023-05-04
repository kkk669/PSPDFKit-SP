//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFPageView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSearchResult;

/// The data source for the `SearchHighlightViewManager` to coordinate animations and highlighting.
PSPDF_PROTOCOL_SWIFT(SearchHighlightViewManagerDataSource)
@protocol PSPDFSearchHighlightViewManagerDataSource<NSObject>

/// Control if we should add search highlight views at all.
@property (nonatomic, readonly) BOOL shouldHighlightSearchResults;

/// Returns an array of PSPDFPageView objects.
@property (nonatomic, readonly) NSArray<PSPDFPageView *> *visiblePageViews;

@end

/// Manages views added on `PDFPageView`.
PSPDF_CLASS_SWIFT(SearchHighlightViewManager)
@interface PSPDFSearchHighlightViewManager : NSObject<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
///
/// Typically you shouldn’t create an instance of this class and should instead
/// use the `searchHighlightViewManager` property of `PDFViewController`.
- (instancetype)initWithDataSource:(id<PSPDFSearchHighlightViewManagerDataSource>)dataSource NS_DESIGNATED_INITIALIZER;

/// The data source for the search highlight manager.
@property (nonatomic, weak, readonly) id<PSPDFSearchHighlightViewManagerDataSource> dataSource;

/// Returns YES if there are search results displayed on a page view.
@property (nonatomic, readonly) BOOL hasVisibleSearchResults;

/// Hides search results.
///
/// @note `animated` is currently ignored.
- (void)clearHighlightedSearchResultsAnimated:(BOOL)animated;

/// Adds search result highlights to visible page views.
///
/// Adding results for pages that are not visible will have no effect. You should call this method again when the visible page views
/// change, which you can observe using the `PDFViewControllerDelegate` method `pdfViewController(_:willBeginDisplaying:forPageAt:)`.
///
/// Calling this multiple times with the equal search results has no effect. In other words, there is no need to worry about adding
/// duplicate highlights for the same result.
- (void)addHighlightSearchResults:(NSArray<PSPDFSearchResult *> *)searchResults animated:(BOOL)animated;

/// Animates a search result highlight with a zoom/flash animation to draw attention.
///
/// The highlight must have previously been added using `addHighlight(_:animated:)`.
///
/// This has no effect if the search result is on a page that is not visible.
- (void)animateSearchHighlight:(PSPDFSearchResult *)searchResult;

@end

NS_ASSUME_NONNULL_END
