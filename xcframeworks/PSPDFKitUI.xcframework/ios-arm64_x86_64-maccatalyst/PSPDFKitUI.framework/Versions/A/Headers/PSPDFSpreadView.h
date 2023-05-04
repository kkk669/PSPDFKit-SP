//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <UIKit/UIKit.h>

@class PSPDFDocumentViewLayout, PSPDFPageView;

NS_ASSUME_NONNULL_BEGIN

/// The spread view is responsible for laying out one or multiple page views.
///
/// It ensures the best display for the pages it is responsible for and makes sure
/// pages are shown in the correct order (e.g. respecting the page binding).
///
/// A spread describes a collection of continuous pages that are grouped in a logical
/// container from the layout. E.g. if you have a book, when the book is open you will
/// always see two pages next to each other. These two pages build one spread. If you
/// have a stack of loose paper on the other hand, you always only see one page, so
/// a spread only consists of one page in that example.
PSPDF_CLASS_SWIFT(PDFSpreadView)
@interface PSPDFSpreadView : UIView<PSPDFOverridable>

PSPDF_INIT_WITH_CODER_UNAVAILABLE

/// The layout this spread view is a part of.
@property (nonatomic, readonly, nullable) PSPDFDocumentViewLayout *layout;

/// The spread represented by this view.
///
/// To convert the spread index to the range of pages that it represents, use the methods
/// provided by the layout.
///
/// @see `-[PSPDFDocumentViewLayout pageRangeForSpreadAtIndex:]`
@property (nonatomic, readonly) NSInteger spreadIndex;

/// The page views maintained by this spread view.
@property (nonatomic, copy, readonly) NSArray<PSPDFPageView *> *pageViews;

/// Iterates through `pageViews` to find the page view for `pageIndex`.
///
/// @param pageIndex The index of the page for which the page view is required.
/// @return The `PDFPageView` displaying the page at `pageIndex`.
- (nullable PSPDFPageView *)pageViewForPageAtIndex:(PSPDFPageIndex)pageIndex;


@end

NS_ASSUME_NONNULL_END
