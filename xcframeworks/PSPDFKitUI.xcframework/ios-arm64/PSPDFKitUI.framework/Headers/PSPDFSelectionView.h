//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSelectionView;

/// Delegate for selection related events.
PSPDF_PROTOCOL_SWIFT(SelectionViewDelegate)
@protocol PSPDFSelectionViewDelegate<NSObject>

@optional

/// Called before we start selecting. If we return NO here, no selection will be drawn (but delegates will still be called)
- (BOOL)selectionView:(PSPDFSelectionView *)selectionView shouldStartSelectionAtPoint:(CGPoint)point;

/// Rect is updated. (`touchesMoved:`)
- (void)selectionView:(PSPDFSelectionView *)selectionView updateSelectedRect:(CGRect)rect;

/// Called when a rect was selected successfully. (`touchesEnded:`)
- (void)selectionView:(PSPDFSelectionView *)selectionView finishedWithSelectedRect:(CGRect)rect;

/// Called when rect selection was cancelled. (`touchesCancelled:`)
- (void)selectionView:(PSPDFSelectionView *)selectionView cancelledWithSelectedRect:(CGRect)rect;

/// Called when we did a single tap in the selection view (via tap gesture recognizer)
- (void)selectionView:(PSPDFSelectionView *)selectionView singleTappedWithGestureRecognizer:(UITapGestureRecognizer *)gestureRecognizer;

@end

/// Captures touches and shows selection boxes during dragging.
/// Shows the selection box during dragging when using the annotation selection tool. (The rectangle between the start location of dragging and the current touch location.)
/// With the highlight tool, this also shows the proposed text to be highlighted.
/// With the annotation selection tool, this also shows the proposed selected annotations.
/// The selection color is determined by the `tintColor` property inherited from `UIView`.
/// This is also used for text block debugging.
PSPDF_CLASS_SWIFT(SelectionView)
@interface PSPDFSelectionView : UIView<PSPDFOverridable>

/// Selection View delegate.
@property (nonatomic, weak) id<PSPDFSelectionViewDelegate> delegate;

/// The selection opacity. Defaults to 0.2.
@property (nonatomic) CGFloat selectionAlpha UI_APPEARANCE_SELECTOR;

/// The `CGRect`s  in the view that are marked for selection.
@property (nonatomic, copy, nullable) NSArray<NSValue *> *rects;

/// The touch types that should be used for selection.
/// Array of `UITouchType` wrapped in `NSNumber`.
/// The defaults are `direct`, `pencil`, and `indirectPointer`.
@property (nonatomic, copy) NSArray<NSNumber *> *allowedTouchTypes;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFSelectionView (SubclassingHooks)

/// Internal tap gesture.
@property (nonatomic, readonly) UITapGestureRecognizer *tapGestureRecognizer;

/// Internal pan gesture.
@property (nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer;

@end

NS_ASSUME_NONNULL_END
