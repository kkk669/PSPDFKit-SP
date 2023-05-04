//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFPageBinding.h>

NS_ASSUME_NONNULL_BEGIN

/// Holds results of a normalization in a list of bins.
///
/// @see - normalizeBinCountForUpTo:pageCount:usingSpreadsOf:usingSolitaryFirstPage:
struct PSPDFScrubberBinNormalization {
    NSUInteger actualBinCount;
    NSUInteger pagesPerBin;
    NSUInteger pageAllotmentLength;
};
typedef struct PSPDFScrubberBinNormalization PSPDFScrubberBinNormalization NS_SWIFT_NAME(ScrubberBin.Normalization);

/// Helper class to map touch coordinates along a line to pages
PSPDF_TEST_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ScrubberBin)
@interface PSPDFScrubberBin : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Whether or not this bin sits at a boundary.
/// Boundary bins have incidents in their lower/upper half always map to the lowest/highest page in their allotment
@property (nonatomic, readonly) BOOL isBoundary;

/// The range of pages that correspond to this bin.
@property (nonatomic, readonly) NSRange allottedPageRange;

/// The length along which incidents are mapped to pages.
@property (nonatomic, readonly) CGFloat allottedLength;

/// The offset defining the range in which the receiver should register incidents.
@property (nonatomic, readonly) CGFloat offset;

/// The maximum length of the page range for an incident. Defaults to 1.
@property (nonatomic, readonly) NSUInteger pagesPerSpread;

/// When pagesPerSpread is greater than 1, whether for each spread range r `r.location % r.length` equals 0 (`false`) or 1 (`true`).
@property (nonatomic, readonly) BOOL usesSolitaryFirstPage;

/// The binding of the pages that are represented by this bin.
@property (nonatomic, readonly) PSPDFPageBinding pageBinding;

// MARK: Representation

/// The range of pages that represent this bin. For a boundary this will be the first page or last spread, otherwise the central page/spread is returned.
@property (nonatomic, readonly) NSRange representingPageRange;

// MARK: Obtaining Instances

/// Convenience method that provides you with an array of bins that cover the specified distance.
///
/// @note This method will return nil for nonsensical input.
+ (nullable NSArray<PSPDFScrubberBin *> *)makeUpTo:(NSUInteger)binCount binsForPages:(PSPDFPageCount)pageCount overDistance:(CGFloat)activeLength startingAtOffset:(CGFloat)firstBinOffset usingSpreadsOf:(NSUInteger)pagesPerSpread usingSolitaryFirstPage:(BOOL)usesSolitaryFirstPage pageBinding:(PSPDFPageBinding)pageBinding;

/// Normalizes a proposed bin count (maxBinCount) taking into consideration how many pages should be accounted for (pageCount) and how the bins should be laid out (pagesPerSpread / usesSolitaryFirstPage).
///
/// The return value is a structure that holds the final values that should be taken into consideration when
/// laying out the bins across a given length.
+ (PSPDFScrubberBinNormalization)normalizeBinCountForUpTo:(const NSUInteger)maxBinCount pageCount:(const PSPDFPageCount)pageCount usingSpreadsOf:(const NSUInteger)pagesPerSpread usingSolitaryFirstPage:(const BOOL)usesSolitaryFirstPage;

// MARK: Hit Testing

/// The range of the page/spread that corresponds to an incident at the specified length.
///
/// If the incident length is within the bounds of the receiver, the range will have a length of maximumPagesPerHit unless it belongs to a boundary
///
/// @return The range for this incident or a range with a location of `NSNotFound` if the incidentLength is outside of this bin’s realm.
- (NSRange)pageRangeForIncidentLength:(CGFloat)incidentLength;

/// Reverse hit testing: Given a page, where is the centroid for it/the spread, that contains it?
- (CGFloat)centroidForPageAtIndex:(PSPDFPageIndex)pageIndex;

@end

NS_ASSUME_NONNULL_END
