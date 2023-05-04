//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFScrubberBar;

/// Implement this delegate to get notified of scrubber bar events.
PSPDF_PROTOCOL_SWIFT(ScrubberBarDelegate)
@protocol PSPDFScrubberBarDelegate<NSObject>

/// Will be called when a page has been selected using the scrubber bar.
- (void)scrubberBar:(PSPDFScrubberBar *)scrubberBar didSelectPageAtIndex:(PSPDFPageIndex)pageIndex;

@end

/// PDF thumbnail scrubber bar - similar to Apple Books.
PSPDF_CLASS_SWIFT(ScrubberBar)
@interface PSPDFScrubberBar : UIView<PSPDFOverridable>

/// The delegate for touch events
@property (nonatomic, weak) id<PSPDFScrubberBarDelegate> delegate;

/// The data source.
@property (nonatomic, weak) id<PSPDFPresentationContext> dataSource;

/// Whether this is a horizontally or vertically laid out scrubber bar — defaults to horizontal.
///
/// @note Customizing `scrubberBarType` is supported only when `thumbnailBarMode` in the data source is `PSPDFThumbnailBarModeScrubberBar`.
/// Otherwise, setting this property to any value other than `PSPDFScrubberBarTypeHorizontal` won't have any effect.
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
@property (nonatomic, nullable) UIColor *barTintColor UI_APPEARANCE_SELECTOR  PSPDF_DEPRECATED(11.5, "Use standardAppearance and compactAppearance instead to customize the scrubber bar appearance.");

/// If set to a nonzero value, the scrubber bar will render with the standard translucency - blur effect.
/// Inferred from the dataSource by default.
@property (nonatomic, getter=isTranslucent) BOOL translucent UI_APPEARANCE_SELECTOR  PSPDF_DEPRECATED(11.5, "Use standardAppearance and compactAppearance instead to customize the the scrubber bar appearance.");

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

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFScrubberBar (SubclassingHooks)

/// Returns toolbar height. Defaults to the `intrinsicContentSize` height of `UIToolbar`.
@property (nonatomic, readonly) CGFloat scrubberBarHeight;

/// Returns size of the thumbnails. This depends on the `scrubberBarHeight`.
@property (nonatomic, readonly) CGSize scrubberBarThumbSize;

/// An image view that should be used when thumbnail images are still loading.
/// Called once for every thumbnail image.
/// This is not strictly a property because it is expected to return a new object on each call.
@property (nonatomic, readonly) UIImageView *emptyThumbnailImageView;

@end

NS_ASSUME_NONNULL_END
