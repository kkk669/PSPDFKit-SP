//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>
#import <PSPDFKitUI/PSPDFScrubberBar.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_EXPORT const CGFloat PSPDFFloatingScrubberBarPadding;

@class PSPDFScrubberBarContentView, PSPDFAdornmentContainerView;

@protocol PSPDFScrubberBarDelegate;

@protocol PSPDFScrubberBarLayout <NSObject>

/// Asks the delegate to return a size to take as reference when making the calculations for the minimum
/// length required to lay out as many thumbnails as possible on the scrubber bar.
///
/// @see -minimumRequiredLengthForFittingMaxNumberOfBins.
///
/// @param scrubberBar     The scrubber bar asking for the frame reference.
/// @return The size to take as reference. Internally uses the appropriate length for vertical or horizontal configurations.
- (CGSize)maximumSizeForScrubberBar:(PSPDFScrubberBarContentView *)scrubberBar;

@end

/// PDF thumbnail scrubber bar - similar to Apple Books.
@interface PSPDFScrubberBarContentView : UIView

/// The delegate for touch events
@property (nonatomic, weak) id<PSPDFScrubberBarDelegate> delegate;

/// The data source.
@property (nonatomic, weak) id<PSPDFPresentationContext> dataSource;

/// Whether this is a horizontally or vertically laid out scrubber bar — defaults to horizontal.
@property (nonatomic) PSPDFScrubberBarType scrubberBarType;

/// Updates toolbar, re-aligns page screenshots. Registers in the runloop and works later.
- (void)updateToolbarAnimated:(BOOL)animated;

/// *Instantly* updates toolbar.
- (void)updateToolbarForced;

/// Current selected page.
@property (nonatomic) PSPDFPageIndex pageIndex;

/// Taps left/right of the pages area (if there aren't enough pages to fill up space) by default count as first/last page. Defaults to YES.
@property (nonatomic) BOOL allowTapsOutsidePageArea;

// MARK: Styling

/// The background tintColor.
/// Defaults to the PSPDFViewController navigationBar barTintColor (if available).
@property (nonatomic, nullable) UIColor *barTintColor UI_APPEARANCE_SELECTOR PSPDF_DEPRECATED(11.5, "Use standardAppearance and compactAppearance instead to customize the scrubber bar appearance.");

/// If set to a nonzero value, the scrubber bar will render with the standard translucency - blur effect.
/// Inferred from the dataSource by default.
@property (nonatomic, getter=isTranslucent) BOOL translucent UI_APPEARANCE_SELECTOR PSPDF_DEPRECATED(11.5, "Use standardAppearance and compactAppearance instead to customize the scrubber bar appearance.");

/// Appearance style to be used by the for the standard height toolbar.
/// Inferred from the dataSource by default.
@property (nonatomic, nullable) UIToolbarAppearance *standardAppearance UI_APPEARANCE_SELECTOR;

/// Appearance style to be used by the for the compact height toolbar.
/// Inferred from the dataSource by default.
@property (nonatomic, nullable) UIToolbarAppearance *compactAppearance UI_APPEARANCE_SELECTOR;

/// Left border margin. Defaults to `thumbnailMargin`. Set higher to allow custom buttons.
@property (nonatomic) CGFloat leftBorderMargin;

/// Right border margin. Defaults to `thumbnailMargin`. Set higher to allow custom buttons.
@property (nonatomic) CGFloat rightBorderMargin;

/// Margin between thumbnails. Defaults to 2.
@property (nonatomic) CGFloat thumbnailMargin;

/// Size multiplier for the current page thumbnail. Defaults to 1.35.
@property (nonatomic) CGFloat pageMarkerSizeMultiplier;

/// Thumbnail border color.
/// Defaults to a lighter (#A9AEB7) and a darker (#606671) shade of gray in light and dark mode respectively.
@property (nonatomic, nullable) UIColor *thumbnailBorderColor UI_APPEARANCE_SELECTOR;

/// Access the internally used toolbar. Can be used to customize the background appearance.
///
/// @note If you override this to return — e.g. — an instance of a custom toolbar class, be aware that the default implementation makes itself the delegate of the toolbar to support drawing a bezel along the appropriate edge.
@property (nonatomic, readonly) UIToolbar *toolbar;

/// The view that houses the scrubber bar adornments.
@property (nonatomic, readonly) PSPDFAdornmentContainerView *adornmentContainer;

@end

/// MARK: Containment

@interface PSPDFScrubberBarContentView ()

/// Convenience accessor
@property (nonatomic, readonly) PSPDFScrubberBar *scrubberContainer;

@property (nonatomic, weak) id<PSPDFScrubberBarLayout> layoutDelegate;

/// The actual frame that can be used to lay out the thumbnails. Accounts for safe area insets.
@property (nonatomic) CGRect contentFrame;

/// The returned value can be used as the width in cases where the scrubber bar needs to "hug" the
/// thumbnails it contains. It accounts for the margins.
///
/// @return The minimum length thats required to fit as many thumbnails (bins) as possible.
- (CGFloat)minimumRequiredLengthForFittingMaxNumberOfBins;

@end

NS_ASSUME_NONNULL_END
