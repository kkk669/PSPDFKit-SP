
//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFScrubberBarContentView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFScrubberBin, PSPDFScrubberThumbView, PSPDFRenderRequest;

@interface PSPDFScrubberBarContentView ()

/// Used internally to compute the page range of thumbnails at a point in the scrubber bar.
/// Exposed privately for use in ScrubberBarUITests.
@property (nonatomic, nullable, copy, readonly) NSArray<PSPDFScrubberBin *> *scrubberBins;


/// Holds a reference to the thumbnail (`PSPDFScrubberThumbView`) of the currently opened page.
/// Exposed privately for use in ScrubberBarUITests.
@property (nonatomic, nullable, readonly) PSPDFScrubberThumbView *markerView;

/// MARK: Exposed for Tests

// This takes away stress from the render engine as previously we requested the image for all bin
// images from the render caches every time the user switched the page.
// See https://github.com/PSPDFKit/PSPDFKit/pull/8506 for more info.
@property (nonatomic, readonly) NSMutableDictionary<PSPDFRenderRequest *, UIImage *> *thumbnailImageCache;
@property (nonatomic, readonly) NSMutableDictionary<PSPDFRenderRequest *, UIImage *> *markerImageCache;

/// Checks whether the content view is calculating the document's average aspect ratio.
/// The property is not KVO compliant
@property (nonatomic, readonly) BOOL isCalculatingAverageAspectRatio;

@end

NS_ASSUME_NONNULL_END
