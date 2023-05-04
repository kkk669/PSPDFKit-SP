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

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFScrubberThumbType) {
    /// The view contains a single, centered page image,
    PSPDFScrubberThumbTypeSinglePage,
    /// The view contains two facing page images, horizontally flush, centered vertically and horizontally.
    PSPDFScrubberThumbTypeSpread,
    /// The view contains a single page, positioned as if it was the second of two facing pages.
    PSPDFScrubberThumbTypeLowerBoundary,
    /// The view contains a single page, positioned as if it was the first of two facing pages.
    PSPDFScrubberThumbTypeUpperBoundary,
} NS_SWIFT_NAME(ScrubberThumbView.Kind);

@protocol PSPDFThumbnailImageViewProvider;

PSPDF_TEST_CLASS_SWIFT(ScrubberThumbView)
@interface PSPDFScrubberThumbView : UIView

PSPDF_DEFAULT_VIEW_INIT_UNAVAILABLE

- (instancetype)initWithFrame:(CGRect)frame imageProvider:(id<PSPDFThumbnailImageViewProvider>)imageProvider NS_DESIGNATED_INITIALIZER;

@property (nonatomic, unsafe_unretained, readonly, nullable) id<PSPDFThumbnailImageViewProvider> imageProvider;

@property (nonatomic) CGSize maximumThumbnailSize;

@property (nonatomic) PSPDFScrubberThumbType thumbType;

/// Whether this thumb view is acting as a marker on the scrubber bar (slightly larger).
@property (nonatomic) BOOL isCurrentPage;

/// The page binding of the displayed document. Defaults to `PSPDFPageBindingLeftEdge`.
@property (nonatomic) PSPDFPageBinding pageBinding;

- (void)setImage:(nullable UIImage *)image forPageAtIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animateUpdate;

/// Hides the receiver and disassociates it from its image provider.
- (void)recycle NS_REQUIRES_SUPER;

/// Associates the receiver with the specified image provider and unhides it.
- (void)reuseWithImageProvider:(id<PSPDFThumbnailImageViewProvider>)provider;

@end


@protocol PSPDFThumbnailImageViewProvider <NSObject>

/// @return A new empty thumbnail image view.
- (UIImageView *)newImageViewForThumbView:(PSPDFScrubberThumbView *)thumbView;

@end


NS_ASSUME_NONNULL_END
