//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// A formatter to convert a range of pages into a user facing string.
///
/// The page label formatter uses the label of a document's page if it has one assigned
/// to it and falls back to the page number (the page index + 1 that is) otherwise.
///
/// All page ranges are treated as referring to a page's index, starting at 0. The
/// first page therefore has index 0 and is visualized as page 1 if there is no label
/// set for the page.
PSPDF_CLASS_SWIFT(PageLabelFormatter)
@interface PSPDFPageLabelFormatter : NSFormatter

/// Creates a user facing string that represents the given page range for the given document.
///
/// @param pageRange The range of pages to visualize, referring to the page indexes.
/// @param document The document the page range belongs to, used to derive information such as the label of pages.
/// @return A localized string representing the passed in page range.
+ (NSString *)localizedStringFromPageRange:(NSRange)pageRange document:(PSPDFDocument *)document;

/// The document this formatter is using to derive page labels and other informations
/// about the page ranges it is formatting.
@property (nonatomic, nullable) PSPDFDocument *document;

/// Creates a user facing string that represents the given page range for the document
/// assigned to the receiver.
///
/// @param pageRange The range of pages to visualize, referring to the page indexes.
/// @return A localized string representing the passed in page range.
- (NSString *)stringFromRange:(NSRange)pageRange;

@end

NS_ASSUME_NONNULL_END
