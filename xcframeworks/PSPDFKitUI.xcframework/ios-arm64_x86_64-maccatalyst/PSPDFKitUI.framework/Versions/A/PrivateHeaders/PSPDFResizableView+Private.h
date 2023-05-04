//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFResizableView.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// The default value of `innerEdgeInsets` property.
PSPDF_EXTERN UIEdgeInsets const PSPDFResizableViewDefaultInnerEdgeInsets;

/// If trackedView responds to this delegate, we will set it.
@protocol PSPDFResizableTrackedViewDelegate <NSObject>

/// The resizable tracker, if currently available.
@property (nonatomic, weak) PSPDFResizableView *resizableView;

/// Query the annotation of the tracked view.
@property (nonatomic, readonly, nullable) PSPDFAnnotation *annotation;

@end

/// Datasource for magnifying glass operations.
PSPDF_PROTOCOL_SWIFT(ResizableViewDataSource)
@protocol PSPDFResizableViewDataSource<NSObject>

@optional

/// Called when the resizable view needs a reference view for the magnifying glass loupe. Return `nil` to prevent display of the loupe.
- (nullable UIView *)loupeReferenceViewForResizableView:(PSPDFResizableView *)resizableView;

@end

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFResizableViewLimitMode) {
    /// The view can bee freely moved outside of it's superview.
    PSPDFResizableViewLimitModeNone,
    /// The content frame has to stay inside the superview bounds.
    PSPDFResizableViewLimitModeContentFrame,
    /// The bounding box (blue) has to stay inside the superview bounds.
    PSPDFResizableViewLimitModeBoundingBox,
    /// The entire resizable view frame has to stay inside the superview bounds.
    PSPDFResizableViewLimitModeViewFrame
} NS_SWIFT_NAME(ResizableViewLimitMode);

@class PSPDFMeasurementSnapper;

@interface PSPDFResizableView ()

/// Returns the edge insets that are currently in effect. This is either `UIEdgeInsetsZero` or `innerEdgeInsets`.
@property (nonatomic, readonly) UIEdgeInsets effectiveInnerEdgeInsets;

/// Returns the edge insets that are currently in effect. This is `outerEdgeInsets` / `zoomScale`.
@property (nonatomic, readonly) UIEdgeInsets effectiveOuterEdgeInsets;

/// Returns the minimum size that is currently in effect.
@property (nonatomic, readonly) CGSize effectiveMinimumSize;

/// Defines the resizable view behavior when dragged outside of it's superview.
/// Defaults to PSPDFResizableViewLimitModeContentFrame.
@property (nonatomic) PSPDFResizableViewLimitMode limitMode;

/// The size of the resizable content. This might be smaller than the size of the
/// bounds of the view due to padding. Changing the contentSize affects the bounds.
///
/// @warning Always change the view's frame/bounds by setting this property or the contentCenter. Do not use the UIView properties directly.
@property (nonatomic) CGSize contentSize;

/// The center of the content. Changing the contentCenter affects the view center.
///
/// @warning Always change the view's frame/center by setting this property or the contentSize. Do not use the UIView properties directly.
@property (nonatomic) CGPoint contentCenter;

/// The rotation of the content in degrees, counterclockwise from horizontal. Setting this affects the view transform.
///
/// @warning Always change the view's transform using this method. Do not use the transform property directly.
@property (nonatomic) NSUInteger contentRotation;

/// The frame in the superview’s coordinate space that encloses the content.
/// If converted to the PDF coordinate space this would be the annotation bounding box.
@property (nonatomic, readonly) CGRect enclosingUnrotatedContentFrame;

/// The length of the rotation stick/handle in points. (Distance of the rotation knob from the bottom-center knob.)
@property (nonatomic, readonly, class) CGFloat rotationStickLength;

/// The associated pageView.
@property (nonatomic, weak) PSPDFPageView *pageView;

/// Internal flag for hiding the rotation knob.
/// Used to hide the rotation knob for a free text annotation when it is being edited.
@property (nonatomic) BOOL shouldDisableRotatingInternally;

/// DataSource called for loupe reference view.
@property (nonatomic, weak) IBOutlet id<PSPDFResizableViewDataSource> dataSource;

/// The measurement snapper object to use for measurement annotation snapping.
@property (nonatomic, weak) PSPDFMeasurementSnapper *measurementSnapper;

/// Adds an additional delegate.
///
/// The delegate is stored weak. It is not necessary to remove a delegate when it is deallocated.
///
/// @warning For internal use, this API should be favored over `setDelegate:` as the
/// delegate property is reserved for external use.
///
/// @see `-removeDelegate:`
///
/// @param delegate The delegate to add to the delegate list.
- (void)addDelegate:(id<PSPDFResizableViewDelegate>)delegate;

/// Removes a delegate from the list.
///
/// @see `-addDelegate:`
///
/// @param delegate The delegate to remove.
- (void)removeDelegate:(id<PSPDFResizableViewDelegate>)delegate;

/// Prepare for forwarding touches starting at the given point. This needs to be
/// called before `processTouchesFromGestureRecognizer:`.
///
/// This method will check if the resizable view can handle the gesture and set its
/// mode to the appropriate value and return a boolean value indicating that.
///
/// @param point The initial point of a gesture in resizable view's coordinate space.
/// @param dryRun If `true`, the mode will not be changed.
///
/// @returns A mode other than `PSPDFResizableViewModeIdle` if the selection view
/// will have the ability to process touches at the given point, otherwise
/// `PSPDFResizableViewModeIdle`.
- (PSPDFResizableViewMode)prepareForForwardingTouchesBeginningAtPoint:(CGPoint)point dryRun:(BOOL)dryRun;

/// The boolean value that indicates whether the resizable view has decided to
/// show outer resizable knobs or not.
@property (nonatomic, readonly) BOOL shouldShowOuterKnobs;

/// The boolean value that indicates whether the resizable view has decided to
/// show inner resizable knobs or not.
@property (nonatomic, readonly) BOOL shouldShowInnerKnobs;

/// The boolean value that indicates whether the resizable view has decided to
/// show the rotation knob or not.
@property (nonatomic, readonly) BOOL shouldShowRotationKnob;

@end

NS_ASSUME_NONNULL_END
