//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFCache.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFTableViewCell.h>
#import <PSPDFKitUI/PSPDFSearchViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSearchResult;

/// Cell that is used to display a search result.
PSPDF_APP_CLASS_SWIFT(SearchResultCell)
@interface PSPDFSearchResultCell : PSPDFTableViewCell<PSPDFSearchResultViewable>

/// Searches the outline for the most matching entry, displays e.g. "Section 100, Page 2" instead of just "Page 2".
///
/// This needs to be set before the cell displays.
///
/// @note This option can potentially invoke expensive outline parsing. Be sure to test search within
/// your documents for performance issues with this option enabled.
@property (nonatomic) BOOL useOutlineForPageNames;

/// The image view used for displaying the thumbnail
@property (nonatomic, readonly) UIImageView *pageImageView;

/// The label used for displaying the page number
@property (nonatomic, readonly) UILabel *pageLabel;

/// The label used for displaying the preview text
@property (nonatomic, readonly) UILabel *resultLabel;

// unavailable:
@property (nonatomic, readonly, nullable) UIImageView *imageView NS_UNAVAILABLE;
@property (nonatomic, readonly, nullable) UILabel *textLabel NS_UNAVAILABLE;
@property (nonatomic, readonly, nullable) UILabel *detailTextLabel NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
