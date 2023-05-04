//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFDocumentViewSpreadMode.h>

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

PSPDF_CLASS_SWIFT(PSPDFDocumentViewLayoutInvalidationContext)
@interface PSPDFDocumentViewLayoutInvalidationContext : UICollectionViewLayoutInvalidationContext @end

/// A document view layout controls how a document is visualized on screen. It controls
/// where a spread (a set of pages) is placed on the screen and how scrolling and zooming
/// behaves.
///
/// ## Subclassing
///
/// `PSPDFDocumentViewLayout` is an abstract base class meant for subclassing. You
/// can either subclass `PSPDFContinuousScrollingLayout` or `PSPDFScrollPerSpreadLayout`
/// if you want a layout similar to these two but only need a couple of tweaks. If
/// you want to have more control but your layout still follows the general idea of
/// a layout that scrolls in a single direction, either vertically or horizontally,
/// `PSPDFStackViewLayout`, the superclass of the two aforementioned layouts, gives
/// you a lot of control while covering the basics and a couple of convenience methods
/// that make your life easier. This should be enough control for almost all designs.
/// However if your design is very specific, we also give you the same base class all
/// of our own layouts use: `PSPDFDocumentViewLayout`. With this layout you need to
/// do everything on your own but there are almost no limitations on what to do with it.
///
/// ## Spreads
///
/// The main thing that a document view layout cares about is a spread; this is what
/// it calculates the position of. A spread is a collection of pages that are always
/// viewed together. If you have the most basic layout, a layout with its spread mode
/// set to single, every spread corresponds to a single page in the document, which
/// means the amount of spreads is equal to the amount of pages. However you can also
/// have a double paged layout or a book layout. To convert between pages and spreads,
/// `PSPDFDocumentViewLayout` provides you with helper methods. To make your layout
/// work with all spread modes, it is important that you use these methods for conversion
/// and, in case you want to implement your own spreading algorithms, override these
/// methods and make them do the proper conversion, otherwise your layout may not work
/// correctly in all cases.
///
/// @see `PSPDFDocumentViewLayoutSpreadMode`
///
/// ## UICollectionViewLayout
///
/// It is very important to keep in mind that a document view layout is based on
/// `UICollectionViewLayout` and that this is what is used to calculate the position
/// of a spread on the screen in the end. `PSPDFDocumentViewLayout` and especially
/// its subclass `PSPDFStackViewLayout` offer you convenience methods that hide a lot
/// of the complexity of collection views but depending on how the layout you are building
/// should look, keep in mind that all the collection view layout methods can be used
/// as well.
///
/// While the collection view layout works with index paths as its item identifying
/// object, the document view layout does not need multiple levels of indexes. Each
/// layout only needs to deal with one section. The important identifier for a document
/// view layout is the spread index an item is representing. Therefore all the methods
/// a `PSPDFDocumentViewLayout` and its subclasses offer refer to the spread index
/// instead of an index path. For most layouts you will not come into contact with
/// any of the index path based methods, but in case you do need them, PSPDFKit offers
/// you two new methods on `NSIndexPath` to easily convert between index paths and
/// spread indexes: `+[NSIndexPath pspdf_indexPathForSpreadAtIndex:]` and
/// `-[NSIndexPath pspdf_spreadIndex]`. You should always use these methods to convert
/// back and forth between spread indexes and index paths and not make any assumptions
/// about how an index path maps to a spread index.
///
/// ## Additional APIs
///
/// Aside from the collection view layout, a document view layout also offers a few
/// additional things that the document view controller and its views use to determine
/// other behaviors, such as how zooming behaves (`spreadBasedZooming`), how spreads
/// map to pages, and how the actual view hierarchy is positioned in relation to the
/// view controller's view (`scrollViewFrameInsets`).
///
/// Make sure to use the methods `PSPDFDocumentViewLayout` and its subclasses offer
/// instead of just implementing everything by overriding the collection view layout
/// methods. If you override one of the collection view layout methods, it is up to
/// you to make sure that other methods such as `spreadIndexForPageAtIndex:`,
/// `pageRangeForSpreadAtIndex:`, `continuousSpreadIndexForContentOffset:`, or
/// `contentOffsetForContinuousSpreadIndex:` don't return conflicting values or otherwise
/// you might get unexpected results.
PSPDF_CLASS_SWIFT(PDFDocumentViewLayout)
@interface PSPDFDocumentViewLayout : UICollectionViewLayout

PSPDF_INIT_WITH_CODER_UNAVAILABLE;

/// The document that is laid out by the document view. Amongst other things it is
/// used to determine the number and size of pages.
@property (nonatomic, readonly) PSPDFDocument *document;

// MARK: Appearance

/// Spread based zooming means that each spread (a pair of pages in a double sided
/// layout, or a single page otherwise) zooms individually. If this is turned off, all
/// spreads will zoom together, making the whole document one giant zoomable canvas.
///
/// Spread based zooming results in an experience similar to what the Photos app does,
/// having it turned off is similar to what Safari does.
@property (nonatomic) BOOL spreadBasedZooming;

// MARK: View Positioning

/// The insets to apply to the scroll view's frame.
///
/// Subclasses can override this to inset the scroll view's frame that is needed to
/// layout spreads properly. If you override this, make sure to apply the
/// `additionalScrollViewFrameInsets` or otherwise setting additional frame insets
/// will have no effect.
///
/// @see `-additionalScrollViewFrameInsets`
@property (nonatomic, readonly) UIEdgeInsets scrollViewFrameInsets;

/// Additional insets to apply to the scroll view's frame.
///
/// Users of the layout can set insets here to customize the appearance of the layout.
///
/// Defaults to `UIEdgeInsetsZero`.
///
/// @see `-scrollViewFrameInsets`
@property (nonatomic) UIEdgeInsets additionalScrollViewFrameInsets;

// MARK: Managing Spreads and Pages

/// The continuous spread index at the passed in content offset.
///
/// This method converts a given content offset to a continuous spread index.
///
/// The continuous spread index represents the main visible spread as well as the scroll
/// position of that page. A continuous spread index of 2.5 means that the spread index
/// 2 is currently visible and already half way scrolled towards spread index 3.
///
/// For most layouts, the above example would result in something where the second
/// half of spread index 2 is visible and the first half of spread index 3.
///
/// If you are not interested in the inter-spread offset, there are integer based methods
/// available as well to read and modify the spread index.
///
/// @warning When subclassing `PSPDFDocumentViewLayout` directly, you need to implement
/// this method and do not call super. The base implementation of this method
/// throws an exception.
///
/// @see `-contentOffsetForContinuousSpreadIndex:`
///
/// @param contentOffset The content offset whose continuous spread index should be
/// calculated.
/// @return The continuous spread index of the passed in content offset.
- (CGFloat)continuousSpreadIndexForContentOffset:(CGPoint)contentOffset;

/// A content offset that has the passed in continuous spread index.
///
/// This method is used to convert a given continuous spread index to a content offset.
///
/// The continuous spread index represents the main visible spread as well as the scroll
/// position of that page. A continuous spread index of 2.5 means that the spread index
/// 2 is currently visible and already half way scrolled towards spread index 3.
///
/// For most layouts, the above example would result in something where the second
/// half of spread index 2 is visible and the first half of spread index 3.
///
/// If you are not interested in the inter-spread offset, there are integer based methods
/// available as well to read and modify the spread index.
///
/// @warning When subclassing `PSPDFDocumentViewLayout` directly, you need to implement
/// this method and do not call super. The base implementation of this method
/// throws an exception.
///
/// @see `-continuousSpreadIndexForContentOffset:`
///
/// @param continuousSpreadIndex The continuous spread index whose content offset should
/// be calculated.
/// @return The content offset of the passed in continuous spread index.
- (CGPoint)contentOffsetForContinuousSpreadIndex:(CGFloat)continuousSpreadIndex;

/// The total number of spreads in the document view.
///
/// This is a computed property. The default implementation derives the number of spreads
/// from converting the last page index to its spread index. Usually you do not need
/// to override this method in a subclass, instead adopt the conversion methods as
/// needed.
///
/// @see `-spreadIndexForPageAtIndex:`
/// @see `-pageIndexesForSpreadAtIndex:`
@property (nonatomic, readonly) NSInteger numberOfSpreads;

/// Converts a given page index to the spread index of the spread representing it.
///
/// @param pageIndex The page index of the document.
/// @return The spread index in the view hierarchy representing the given page index.
- (NSInteger)spreadIndexForPageAtIndex:(NSInteger)pageIndex;

/// Converts a given spread index to the page range its spread represents.
///
/// Usually a spread either represents one or two pages, but could represent more pages
/// if a custom layout is used. The only constraint is that a spread can only represent
/// adjacent pages.
///
/// @param spreadIndex The spread index of the view hierarchy.
/// @return The range of pages in the document, represented by the given spread index.
- (NSRange)pageRangeForSpreadAtIndex:(NSInteger)spreadIndex;

/// Controls how pages are converted into spreads and back.
///
/// This property is evaluated in the default implementations for `spreadIndexForPageAtIndex:`
/// and `pageRangeForSpreadAtIndex:`. If you override these methods the value of this
/// property may have no effect on the layout.
@property (nonatomic, readonly) PSPDFDocumentViewLayoutSpreadMode spreadMode;

// MARK: Invalidating the Layout

/// Call this method if general view configuration properties such as `spreadBasedZooming`
/// and `scrollViewFrameInsets` should be invalidated.
///
/// @note While `invalidateLayout` handles the invalidation of the spreads positions,
/// this method handles the overall configuration related to the document view.
- (void)invalidateConfiguration;

// MARK: Unavailable Inherited API

// Marked unavailable - use the viewport related methods instead:
- (BOOL)shouldInvalidateLayoutForBoundsChange:(CGRect)newBounds NS_UNAVAILABLE;
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForBoundsChange:(CGRect)newBounds NS_UNAVAILABLE;

@end

@interface PSPDFDocumentViewLayout (Subclassing)

/// The area that would currently be shown by the document view if no zooming would
/// be enabled.
///
/// While this may sound complicated, this is used by the layouts to know the visible
/// size of the collection view on default zoom scale.
@property (nonatomic, readonly) CGRect viewport;

/// Asks the layout object if the new viewport requires a layout invalidation.
///
/// The viewport defines the area that should be seen as the currently visible area
/// from the layouts perspective. Due to implementation details the viewport might
/// be different than the bounds of the collection view. In a custom layout you should
/// implement and use this method in favor of `shouldInvalidateLayoutForBoundsChange:`.
///
/// @param newViewport The new viewport of the collection view.
/// @return `true` if the collection view requires a layout update or `false` otherwise.
- (BOOL)shouldInvalidateLayoutForViewportChange:(CGRect)newViewport;

/// Returns an invalidation context that defines which parts of the layout should be
/// invalidated due to a change of the viewport.
///
/// The viewport defines the area that should be seen as the currently visible area
/// from the layouts perspective. Due to implementation details the viewport might
/// be different than the bounds of the collection view. In a custom layout you should
/// implement and use this method in favor of `invalidationContextForBoundsChange:`.
///
/// The default implementation creates an instance of the class provided by `invalidationContextClass`.
///
/// @param newViewport The new viewport of the collection view.
/// @return An invalidation context that describes the changes that need to be made.
/// Do not return `nil`.
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForViewportChange:(CGRect)newViewport;

// Upgraded to require a call to super when overriding:
- (void)invalidateLayoutWithContext:(UICollectionViewLayoutInvalidationContext *)context NS_REQUIRES_SUPER;

@end

@class PSPDFScrollPerSpreadLayout, PSPDFContinuousScrollingLayout;

@interface PSPDFDocumentViewLayout (Convenience)

/// Creates a scroll per spread layout as provided by `PSPDFScrollPerSpreadLayout`.
///
/// This is a layout that paginates from one spread to the next and does not stop at
/// intermediate spread positions.
///
/// @return A newly configured layout, ready to be used in a document view.
+ (PSPDFScrollPerSpreadLayout *)scrollPerSpreadLayout NS_SWIFT_NAME(scrollPerSpread());

/// Creates a continuous scrolling layout as provided by `PSPDFContinuousScrollingLayout`.
///
/// This is a layout that scrolls through spreads and pages continuously, without
/// any prominent scroll positions. When scrolling in a horizontal direction, the spread
/// mode is ignored and all spreads will always be treated as single spreads.
///
/// @return A newly configured layout, ready to be used in a document view.
+ (PSPDFContinuousScrollingLayout *)continuousScrollingLayout NS_SWIFT_NAME(continuousScrolling());

/// Creates a page curl layout.
///
/// This is a layout that looks similar to a book. The user can curl through pages.
/// It shows either single or double spreads and changes the page binding according
/// to the page binding option of the document.
///
/// @return A newly configured layout, ready to be used in a document view.
+ (PSPDFDocumentViewLayout *)pageCurlLayout NS_SWIFT_NAME(pageCurl());

@end

@interface NSIndexPath (PSPDFDocumentViewLayout)

/// Creates an index path with a given spread index, suitable for use on all the collection
/// view methods dealing with index paths instead of spread indexes.
///
/// @param spreadIndex The spread index to express as an index path.
/// @return The index path expressing the passed in spread index.
+ (NSIndexPath *)pspdf_indexPathForSpreadAtIndex:(NSInteger)spreadIndex;

/// The index identifying the spread in a `PSPDFDocumentViewLayout`.
@property (nonatomic, readonly) NSInteger pspdf_spreadIndex;

@end

NS_ASSUME_NONNULL_END
