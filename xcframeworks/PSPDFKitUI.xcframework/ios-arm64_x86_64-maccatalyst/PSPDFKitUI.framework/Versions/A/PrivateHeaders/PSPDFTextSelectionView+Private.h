//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/NSString+PSPDFFoundation.h>
#import <PSPDFKitUI/PSPDFSelectionState.h>
#import <PSPDFKitUI/PSPDFTextSelectionView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSelectionBlock, PSPDFWord, PSPDFTextSelectionConfiguration, PSPDFParagraph;
@protocol PSPDFPresentationContext;

@protocol PSPDFTextSelectionViewDataSource <UICoordinateSpace>

/// The document we're operating on.
@property (nonatomic, readonly) PSPDFDocument *document;

/// The current page index.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

/// The parent zoom scale.
@property (nonatomic, readonly) UIScrollView *zoomView;

/// The view that is displaying the current spread. Used for setting up the magnification loupe.
@property (nonatomic, readonly) UIView *spreadView;

/// Coordinate space of the PDF. Used to convert rects and points.
/// Needed in addition to the `UICoordinateSpace` conformance on `PSPDFTextSelectionViewDataSource` itself.
@property (nonatomic, readonly) id<UICoordinateSpace> pdfCoordinateSpace;

/// Presentation context in which the text selection view is.
@property (nonatomic, readonly) id<PSPDFPresentationContext> presentationContext;

@optional

/// Forwarded settings.
@property (nonatomic, getter=isTextSelectionEnabled, readonly) BOOL textSelectionEnabled;
@property (nonatomic, getter=isImageSelectionEnabled, readonly) BOOL imageSelectionEnabled;
@property (nonatomic, readonly) PSPDFTextSelectionMode textSelectionMode;

/// The view that is used as a reference view of the text selection loupe.
- (UIView *)loupeReferenceViewForTextSelectionView:(PSPDFTextSelectionView *)textSelectionView;

@end

/// The identifier of a text selection handle.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFTextSelectionHandleIdentifier) {
    PSPDFTextSelectionHandleIdentifierNone = -1,
    PSPDFTextSelectionHandleIdentifierStart = 0,
    PSPDFTextSelectionHandleIdentifierEnd = 1
};

@interface PSPDFTextSelectionView ()

/// The text selection data source.
@property (nonatomic, weak) id<PSPDFTextSelectionViewDataSource> dataSource;

/// The current state of the selection view, if a selection exists
@property (nonatomic, readonly, nullable) PSPDFSelectionState *selectionState;

@property (nonatomic, getter=isDragHandleSelected, readonly) BOOL dragHandleSelected;

/// The handle currently being dragged.
@property (nonatomic) PSPDFTextSelectionHandleIdentifier draggingHandle;

/// The direction of the text being selected.
@property (nonatomic, readonly) PSPDFTextDirection selectedTextDirection;

/// The blocks currently selected.
@property (nonatomic, readonly, nullable) NSArray<PSPDFSelectionBlock *> *selectedBlocks;

/// Applies the specified state to the receiver.
- (void)applySelectionState:(PSPDFSelectionState *)state;

/// Resolve the new preferred text selection mode.
- (PSPDFTextSelectionMode)resolveTextSelectionModeWithPreferredMode:(PSPDFTextSelectionMode)preferredTextSelectionMode;

/// Update the visibility of text selection handles.
///
/// @param animated Animate handles in, if not already visible.
- (void)updateHandlesVisibilityAnimated:(BOOL)animated;

/// Hit test the point to see if it hits either the start or the end handle.
/// Padding will be applied.
///
/// @param point Point in the text selection view's coordinate space.
- (PSPDFTextSelectionHandleIdentifier)handleAtPoint:(CGPoint)point;

/// Checks if a point in the selection view coordinate system is contained in any of firstLineRect, innerRect, and lastLineRect.
- (BOOL)selectionRectsContainPoint:(CGPoint)point;

/// Returns a selectable word at the given location.
- (nullable PSPDFWord *)wordAtLocation:(CGPoint)location;

/// Returns a selectable image at the given location.
- (nullable PSPDFImageInfo *)imageAtLocation:(CGPoint)location;

/// Returns a selectable paragraph at the given location.
- (nullable PSPDFParagraph *)paragraphAtLocation:(CGPoint)location;

// MARK: Subclassing Hooks

/// The start handle's image view.
@property (nonatomic, readonly, nullable) UIImageView *startHandle;

/// The end handle's image view.
@property (nonatomic, readonly, nullable) UIImageView *endHandle;

/// Specifies whether selection handles should be displayed.
///
/// On iOS returns `true` when selecting text via regular selection, `false` via simple selection and `false` when selecting images.
/// On Mac Catalyst this is always `false`.
///
/// Overridable by subclasses.
- (BOOL)shouldShowSelectionHandlesForTextSelectionMode:(PSPDFTextSelectionMode)textSelectionMode;

// Subclasses can override the mode returned by the data source.
@property (nonatomic, readonly) PSPDFTextSelectionMode textSelectionMode;

// Default implementation for data source
@property (nonatomic, getter=isTextSelectionEnabled, readonly) BOOL textSelectionEnabled;
@property (nonatomic, getter=isImageSelectionEnabled, readonly) BOOL imageSelectionEnabled;

/// Indicates whether menus should be invoked via the context menu gesture instead of being displayed automatically.
/// Defaults to `false`.
@property (nonatomic) BOOL usesContextMenus;

// MARK: Text Interaction Support

/// Highlight a word or an image at the given location. Passing `PSPDFPointNil`
/// will reset the highlight.
///
/// @param point Point in text selection view's coordinate space.
- (void)highlightWordOrImageAtPoint:(CGPoint)point;

/// Check if the text selection view can select a word or an image based on
/// previously highlighted one.
///
/// @return `true` if selection is possible, otherwise `false`.
- (BOOL)canCommitSelectionWithHighlightedWordOrImage;

/// Select a word or an image based on previously highlighted one.
///
/// @param preferredMode Preferred text selection mode. Will be resolved against actual mode.
/// @param showMenu Whether to show menu after selection.
/// @param animated Whether the selection (and showing menu) should be animated.
- (void)commitSelectionWithHighlightedWordOrImageWithPreferredMode:(PSPDFTextSelectionMode)preferredMode showMenu:(BOOL)showMenu animated:(BOOL)animated;

/// Check if a word or an image can be selected at the given location. Does not
/// mutate the selection.
///
/// @param point Point in text selection view's coordinate space.
///
/// @return `true` if selection is possible, otherwise `false`.
- (BOOL)canSelectWordOrImageAtPoint:(CGPoint)point;

/// Select a word or an image at the given location.
///
/// @param point Point in text selection view's coordinate space.
/// @param preferredMode Preferred text selection mode. Will be resolved against actual mode.
/// @param showMenu Whether to show menu after selection.
/// @param animated Whether the selection (and showing menu) should be animated.
- (void)selectWordOrImageAtPoint:(CGPoint)point withPreferredMode:(PSPDFTextSelectionMode)preferredMode showMenu:(BOOL)showMenu animated:(BOOL)animated;

/// Select a paragraph of text at the given location.
///
/// @param point Point in text selection view's coordinate space.
/// @param preferredMode Preferred text selection mode. Will be resolved against actual mode.
/// @param showMenu Whether to show menu after selection.
/// @param animated Whether the selection (and showing menu) should be animated.
- (void)selectParagraphAtPoint:(CGPoint)point withPreferredMode:(PSPDFTextSelectionMode)preferredMode showMenu:(BOOL)showMenu animated:(BOOL)animated;

/// Check if given `point` is inside any of the current selection rects.
///
/// @param point Point in text selection view's coordinate space.
///
/// @return `true` if `point` is inside any selection rect, otherwise `false`.
- (BOOL)pointInsideAnySelectionRect:(CGPoint)point;

/// Process a text selecting touch, usually from `PSPDFTextInteraction`.
///
/// @param location Current location of touch in this view's coordinate space.
/// @param initialLocation Initial location of touch in this view's coordinate space.
/// @param state State of the gesture recognizer that the touch comes from.
/// @param configuration Preferred configuration for performing text selection.
- (void)processTextSelectingTouchAtPoint:(CGPoint)location initialPoint:(CGPoint)initialLocation gestureRecognizerState:(UIGestureRecognizerState)state preferredConfiguration:(PSPDFTextSelectionConfiguration *)configuration;

/// Process a handle dragging touch, usually from `PSPDFTextInteraction`.
///
/// @param location Current location of touch in this view's coordinate space.
/// @param initialLocation Initial location of touch in this view's coordinate space.
/// @param state State of the gesture recognizer that the touch comes from.
/// @param configuration Preferred configuration for performing text selection.
- (void)processHandleDraggingTouchAtPoint:(CGPoint)location initialPoint:(CGPoint)initialLocation gestureRecognizerState:(UIGestureRecognizerState)state preferredConfiguration:(PSPDFTextSelectionConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
