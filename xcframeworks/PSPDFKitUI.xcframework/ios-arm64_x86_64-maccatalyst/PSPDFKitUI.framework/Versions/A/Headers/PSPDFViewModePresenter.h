//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFPresentationContext.h>

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// Protocol for presenting a collection view with customization options.
PSPDF_PROTOCOL_SWIFT(ViewModePresenter)
@protocol PSPDFViewModePresenter<NSObject>

/// Convenience initializer.
///
/// @param layout The layout to use when loading the collection view.
/// @note If `nil`, a controller specific default layout is selected.
- (instancetype)initWithCollectionViewLayout:(nullable UICollectionViewLayout *)layout;

/// Convenience initializer. Initializes the controller with the default layout and stores the document.
///
/// @param document The document.
- (instancetype)initWithDocument:(nullable PSPDFDocument *)document;

// MARK: Data

/// Current edited document.
@property (nonatomic, nullable) PSPDFDocument *document;

/// Used to access the configuration, class overrides, etc.
@property (nonatomic, weak) id<PSPDFPresentationContext> presentationContext;

// MARK: Cells

/// Class used for thumbnails.
///
/// @warning Will be ignored if the layout is not a flow layout or a subclass thereof.
@property (nonatomic) Class cellClass;

// MARK: Layout

/// A Boolean value specifying whether the thumbnails should be displayed in consistently spaced columns, or with consistent areas.
/// For documents where all pages are the same size, this setting has no effect.
/// If `true`, thumbnails are laid out in columns. Landscape pages will be smaller than portrait pages. This tends to look better.
/// If `false`, all thumbnails have approximately the same area.
/// Defaults to `true`.
@property (nonatomic) BOOL fixedItemSizeEnabled;

/// All visible page indexes.
@property (nonatomic, readonly) NSIndexSet *visiblePageIndexes;

/// Scrolls the receiver's content to the specified page index.
///
/// @param pageIndex The page index that is to be scrolled into view.
/// @document The document that is to be displayed. This is useful for `PSPDFViewModePresenter`s that support multiple documents.
/// @animated Specifies whether the scroll should be animated.
- (void)scrollToPageAtIndex:(PSPDFPageIndex)pageIndex document:(nullable PSPDFDocument *)document animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
