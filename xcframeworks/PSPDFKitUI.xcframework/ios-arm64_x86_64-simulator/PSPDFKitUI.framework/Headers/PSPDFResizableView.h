//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

@class PSPDFResizableView, PSPDFAnnotation, PSPDFPageView;

/// The set of predefined knobs to resize the annotation.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFResizableViewOuterKnob) {
    PSPDFResizableViewOuterKnobUnknown,
    PSPDFResizableViewOuterKnobTopLeft,
    PSPDFResizableViewOuterKnobTopMiddle,
    PSPDFResizableViewOuterKnobTopRight,
    PSPDFResizableViewOuterKnobMiddleLeft,
    PSPDFResizableViewOuterKnobMiddleRight,
    PSPDFResizableViewOuterKnobBottomLeft,
    PSPDFResizableViewOuterKnobBottomMiddle,
    PSPDFResizableViewOuterKnobBottomRight,
} PSPDF_ENUM_SWIFT(ResizableView.OuterKnob);

/// Constant used to always force guide snapping.
PSPDF_EXPORT CGFloat const PSPDFGuideSnapAllowanceAlways;

NS_ASSUME_NONNULL_BEGIN

/// Delegate to be notified on session begin/end and frame changes.
PSPDF_PROTOCOL_SWIFT(ResizableViewDelegate)
@protocol PSPDFResizableViewDelegate<NSObject>

@optional

/// The editing session has begun.
- (void)resizableViewDidBeginEditing:(PSPDFResizableView *)resizableView;

/// Called after frame change.
/// On the first call, `isInitialChange` will be true.
- (void)resizableViewChangedFrame:(PSPDFResizableView *)resizableView outerKnobType:(PSPDFResizableViewOuterKnob)outerKnobType isInitialChange:(BOOL)isInitialChange;

/// Called if the annotation's shape is changed (e.g. polyline shape).
- (void)resizableView:(PSPDFResizableView *)resizableView adjustedProperty:(NSString *)propertyName ofAnnotation:(PSPDFAnnotation *)annotation;

/// The editing session has ended.
- (void)resizableViewDidEndEditing:(PSPDFResizableView *)resizableView didChangeFrame:(BOOL)didChangeFrame;

@end

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFKnobType) {
    /// Used to resize the annotation.
    PSPDFKnobTypeOuter,
    /// Used to adjust the `points` of supported annotations, such as the start and end points of a `PSPDFLineAnnotation`.
    PSPDFKnobTypeInner,
    /// Used to rotate the annotation.
    PSPDFKnobTypeRotation,
} PSPDF_ENUM_SWIFT(KnobType);

/// Required methods for views that represent resizable view knobs.
PSPDF_PROTOCOL_SWIFT(KnobView)
@protocol PSPDFKnobView<NSObject>

/// The knob type. Use to display inner and outer knobs differently.
/// Redraw if this property changes.
@property (nonatomic) PSPDFKnobType type;

/// The preferred knob size at zoom level 1.
/// The frame will be adjusted when zooming, based on this size.
@property (nonatomic, readonly) CGSize knobSize;

@end

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFResizableViewMode) {
    /// Nothing is currently happening.
    PSPDFResizableViewModeIdle,
    /// The annotation is being moved.
    PSPDFResizableViewModeMove,
    /// The annotation is being resized.
    PSPDFResizableViewModeResize,
    /// The shape of the annotation is being adjusted (e.g. polyline shape)
    PSPDFResizableViewModeAdjust,
    /// The annotation is being rotated.
    PSPDFResizableViewModeRotate,
} PSPDF_ENUM_SWIFT(ResizableView.Mode);

/// A view that shows borders around selected annotations, with handles the user can use to resize the annotation.
/// The handle and border color is determined by the `tintColor` property inherited from `UIView`.
PSPDF_CLASS_SWIFT(ResizableView)
@interface PSPDFResizableView : UIView<PSPDFOverridable>

/// Delegate called on frame change.
/// Users can set this property to get callbacks.
@property (nonatomic, weak) IBOutlet id<PSPDFResizableViewDelegate> delegate;

/// The mode that the resizable view is currently in.
@property (nonatomic) PSPDFResizableViewMode mode;

/// View that will be changed on selection change.
@property (nonatomic, copy, nullable) NSSet<UIView *> *trackedViews;

/// The annotations corresponding to the `trackedViews` — cached.
@property (nonatomic, readonly) NSSet<PSPDFAnnotation *> *trackedAnnotations;

/// Set zoom scale to be able to draw the page knobs at the correct size.
@property (nonatomic) CGFloat zoomScale;

/// The insets of the selection border and resize knobs from the tracked annotation view.
/// Since padding is usually desirable, the values of these insets should usually be negative.
/// Defaults to -20.0 for top, bottom, right, and left.
///
/// These insets will be combined with `outerEdgeInsets` to map between the content size and center
/// and the resizable view bounds and center.
///
/// @note `updateAnnotationSelectionView` in `PDFPageView` is used to set the inner edge insets
/// of non-resizable annotations (e.g. note annotations) to -2 for top, bottom, right, and left
/// (ignoring the `innerEdgeInsets` property). If you want to change this, you need to subclass
/// `PDFPageView` and override `updateAnnotationSelectionView`.
@property (nonatomic) UIEdgeInsets innerEdgeInsets;

/// The insets of the resizable view bounds from the selection border and resize knobs.
/// Subviews usually lie within the bounds of their superview, so the values of these insets should usually be negative.
/// Defaults to -40.0 for top, bottom, right, and left.
///
/// These insets will be combined with `innerEdgeInsets` to map between the content size and center
/// and the resizable view bounds and center.
@property (nonatomic) UIEdgeInsets outerEdgeInsets;

/// If set to NO, won't show selection knobs and dragging. Defaults to YES.
@property (nonatomic) BOOL allowEditing;

/// Allows view resizing, shows resize knobs.
/// If set to NO, view can only be moved or adjusted, no resize knobs will be displayed. Depends on `allowEditing`. Defaults to YES.
@property (nonatomic) BOOL allowResizing;

/// Allows view adjusting, shows knobs to move single points.
/// If set to NO, view can only be moved or resized, no adjust knobs will be displayed. Depends on `allowEditing`. Defaults to YES.
@property (nonatomic) BOOL allowAdjusting;

/// Whether to allow rotatable annotations to be rotated.
/// Defaults to YES.
/// Being able to rotate also depends on `allowEditing`.
@property (nonatomic) BOOL allowRotating;

/// The rotation of the content in degrees, counterclockwise from horizontal.
@property (nonatomic, readonly) NSUInteger contentRotation;

/// Enables resizing helper so that aspect ratio can be preserved easily.
/// Defaults to YES.
@property (nonatomic) BOOL enableResizingGuides;

/// Shows the bounding box. Defaults to YES.
@property (nonatomic) BOOL showBoundingBox;

/// Defines how aggressively the guide works. Defaults to 20.0.
/// Set to `PSPDFGuideSnapAllowanceAlways` if you want to always snap to guides.
@property (nonatomic) CGFloat guideSnapAllowance;

/// Override the minimum allowed width. This value is ignored if the view is smaller to begin with
/// or the annotation specifies a bigger minimum width. Default is 0.0.
@property (nonatomic) CGFloat minWidth;

/// Override the minimum allowed height. This value is ignored if the view is smaller to begin with
/// or the annotation specifies a bigger minimum height. Default is 0.0.
@property (nonatomic) CGFloat minHeight;

/// Border size. Defaults to 1.0.
@property (nonatomic) CGFloat selectionBorderWidth UI_APPEARANCE_SELECTOR;

/// Guide color. Defaults to `UIColor.pspdf_guideColor`.
@property (nonatomic, nullable) UIColor *guideBorderColor UI_APPEARANCE_SELECTOR;

/// Corner radius size. Defaults to 2.0.
@property (nonatomic) CGFloat cornerRadius UI_APPEARANCE_SELECTOR;

/// Returns a specified knob view used to resize the annotation.
///
/// This will return nil if passed the type `.unknown`. If passed a valid knob type, the return value will not be nil.
///
/// Knobs can be hidden individually by removing them from the superview like this: `outerKnob(ofType: .middleLeft)!.removeFromSuperview()`.
/// Properties like `allowEditing`/`allowResizing` will update the `isHidden` property of the knob views, so just setting `isHidden` to remove a knob will not be sufficient.
///
/// There is typically no need to override this method.
- (nullable UIView<PSPDFKnobView> *)outerKnobOfType:(PSPDFResizableViewOuterKnob)knobType;

/// The knob for rotating annotations that are rotatable.
/// This will be hidden if the annotation does not support rotation or `allowRotating` is disabled.
@property (nonatomic, readonly) UIView<PSPDFKnobView> *rotationKnob;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFResizableView (SubclassingHooks)

/// Forward touches from a parent view's gesture recognizer.
- (void)forwardTouchesFromGestureRecognizer:(UIGestureRecognizer *)gestureRecognizer;

/// Returns the position for a resizing knob. May be overridden to customize the position.
///
/// @note There is a known issue where altering this point may cause aspect ratio locked resizing to slightly change the aspect ratio.
/// If you are experiencing this issue, please contact us at https://pspdfkit.com/support/request/
///
/// @param knobType The knob whose center position should be calculated.
/// @param frame The frame in which the knob is positioned. Usually this is `self.bounds`, but during resizing, this might be different.
/// @return The center point of where the knob view should be placed.
- (CGPoint)centerPointForOuterKnob:(PSPDFResizableViewOuterKnob)knobType inFrame:(CGRect)frame;

/// Returns the point where the `rotationKnob` center should be placed. May be overridden to customize the position.
///
/// @param frame The frame in which the knob is positioned. Usually this is `self.bounds`, but during resizing, this might be different.
/// @return The center point of where `rotationKnob` should be placed.
- (CGPoint)centerPointForRotationKnobInFrame:(CGRect)frame;

/// Creates and configures a new knob view.
///
/// Override this to use custom views for the knobs.
///
/// This may be called before the resizable view has finished initializing so you must not refer to `self`
/// in an override of this method. Doing so may result in a crash.
- (UIView<PSPDFKnobView> *)newKnobViewForType:(PSPDFKnobType)type;

/// Update the knobs.
- (void)updateKnobsAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
