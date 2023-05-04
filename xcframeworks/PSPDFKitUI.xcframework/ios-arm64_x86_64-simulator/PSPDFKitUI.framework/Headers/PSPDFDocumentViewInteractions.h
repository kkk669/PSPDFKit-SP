//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFLinkAnnotation.h>
#import <PSPDFKitUI/PSPDFAnnotationSelectionContext.h>
#import <PSPDFKitUI/PSPDFAnnotationTransformationContext.h>
#import <PSPDFKitUI/PSPDFFastScrollContext.h>
#import <PSPDFKitUI/PSPDFInteractionComponent.h>
#import <PSPDFKitUI/PSPDFSmartZoomContext.h>

NS_ASSUME_NONNULL_BEGIN

/// A protocol that provides a collection of customizable interaction components.
PSPDF_PROTOCOL_SWIFT(DocumentViewInteractions)
@protocol PSPDFDocumentViewInteractions <NSObject>

// MARK: Selecting and Deselecting an Annotation

/// Component responsible for selecting annotations.
///
/// This component is backed by several gesture recognizers, including long press
/// and tap gesture recognizers. This component provides an additional activation
/// context that contains information about the annotation being selected and a
/// page view that contains it.
///
/// You can take advantage of component activation conditions to allow or disallow
/// annotation selection based on the given context and location. For example, to
/// disallow selecting annotations of a specific type (say, ink annotations), you
/// can write:
///
/// ```
/// selectAnnotation.addActivationCondition { context, _, _ in
///     !(context.annotation is InkAnnotation)
/// }
/// ```
@property (nonatomic, readonly) PSPDFInteractionComponent<PSPDFAnnotationSelectionContext *> *selectAnnotation;

/// Attempts to select an annotation at the given location.
///
/// @note This method will respect the activation conditions of `selectAnnotation`
/// interaction component but it will ignore its `enabled` property.
///
/// @param point Location of touch.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the attempt to select an annotation succeeded as the result of
/// calling this method, otherwise `false`.
- (BOOL)tryToSelectAnnotationAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

/// Component responsible for discarding annotation selection and ending editing
/// form elements and free text annotations.
///
/// This component is backed by a tap gesture recognizer. This component provides
/// no additional activation context.
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *deselectAnnotation;

// MARK: Editing and Transforming an Annotation

/// Component responsible for showing the action sheet for link annotations and
/// starting editing form elements and free text annotations.
///
/// This component is backed by several gesture recognizers, including long press
/// and tap gesture recognizers. This component provides an additional activation
/// context that contains information about an annotation or form element being
/// edited and a page view that contains it.
@property (nonatomic, readonly) PSPDFInteractionComponent<PSPDFAnnotationSelectionContext *> *editAnnotation;

/// Attempts to begin editing an annotation at the given location.
///
/// @note This method will respect the activation conditions of `editAnnotation`
/// interaction component but it will ignore its `enabled` property.
///
/// @param point Location of touch.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the attempt to begin editing an annotation succeeded as the
/// result of calling this method, otherwise `false`.
- (BOOL)tryToEditAnnotationAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

/// Component responsible for moving, rotating and resizing annotations.
///
/// This component is backed by a long press gesture recognizer. This component
/// provides an additional activation context that contains additional information
/// about a transformation mode, an annotation being transformed a the page view
/// that contains it.
@property (nonatomic, readonly) PSPDFInteractionComponent<PSPDFAnnotationTransformationContext *> *transformAnnotation;

// MARK: Opening a Link Annotation

/// Component responsible for "opening" link annotations, or, in other words,
/// executing their action.
///
/// This component is backed by a tap gesture recognizer. This component provides
/// an additional activation context that contains information about a link
/// annotation being opened and a page view that contains it.
@property (nonatomic, readonly) PSPDFInteractionComponent<PSPDFAnnotationSelectionContext<PSPDFLinkAnnotation *> *> *openLinkAnnotation;

/// Attempts to open a link annotation at the given location.
///
/// @note This method will respect the activation conditions of `openLinkAnnotation`
/// interaction component but it will ignore its `enabled` property.
///
/// @param point Location of touch.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the attempt to open a link annotation succeeded as the result
/// of calling this method, otherwise `false`.
- (BOOL)tryToOpenLinkAnnotationAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Showing the Annotation Menu

/// Component responsible for showing annotation creation/pasting menu.
///
/// This component is backed by a long press gesture recognizer. This component
/// provides no additional activation context.
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *showAnnotationMenu;

/// Attempts to show an annotation creation/pasting and menu at the given location.
///
/// @note This method will respect the activation conditions of `showAnnotationMenu`
/// interaction component but it will ignore its `enabled` property.
///
/// @param point Location of touch.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the attempt to show an annotation creation/pasting menu
/// succeeded as the result of calling this method, otherwise `false`.
- (BOOL)tryToShowAnnotationMenuAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Performing Fast Scroll

/// Component responsible for performing fast scroll.
///
/// This component is backed by a tap gesture recognizer. This component provides
/// an additional activation context that contains information about the direction
/// of fast scroll.
///
/// You can take advantage of component activation conditions to allow or disallow
/// fast scroll based on the given context and location. For example, to only allow
/// forward fast scroll, you can write:
///
/// ```
/// fastScroll.addActivationCondition { context, _, _ in
///     context.direction == .forward
/// }
/// ```
@property (nonatomic, readonly) PSPDFInteractionComponent<PSPDFFastScrollContext *> *fastScroll;

/// Attempts to perform fast scroll at the given location.
///
/// @note This method will respect the activation conditions of `fastScroll`
/// interaction component but it will ignore its `enabled` property.
///
/// @param point Location of touch.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the attempt to perform fast scroll succeeded as the result of
/// calling this method, otherwise `false`.
- (BOOL)tryToPerformFastScrollAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Performing Smart Zoom

/// Component responsible for performing smart zoom.
///
/// This component is backed by a double tap gesture recognizer. This component
/// provides an additional activation context that contains information about the
/// target zoom rectangle and the scroll view which is being zoomed.
///
/// You can take advantage of component activation conditions to allow or disallow
/// smart zoom based on the given context and location. For example, to disallow
/// smart zoom on a certain page, you can write:
///
/// ```
/// smartZoom.addActivationCondition { _, point, coordinateSpace in
///     let containingPageView = visiblePageViews.first { pageView in
///         let pointInPageView = pageView.convert(point, from: coordinateSpace)
///         return pageView.bounds.contains(pointInPageView)
///     }
///     if let containingPageView {
///         return containingPageView.pageIndex != 0
///     } else {
///         return true
///     }
/// }
/// ```
@property (nonatomic, readonly) PSPDFInteractionComponent<PSPDFSmartZoomContext *> *smartZoom;

/// Attempts to perform smart zoom at the given location.
///
/// @note This method will respect the activation conditions of `smartZoom`
/// interaction components but it will ignore its `enabled` property.
///
/// @param point Location of touch.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the attempt to perform smart zoom succeeded as the result of
/// calling this method, otherwise `false`.
- (BOOL)tryToPerformSmartZoomAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Selecting and Deselecting Text

/// Component responsible for beginning text selection.
///
/// This component is backed by several gesture recognizers, including long press,
/// double tap and triple tap gesture recognizers. This component provides no
/// additional activation context.
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *selectText;

/// Component responsible for discarding text selection.
///
/// This component is backed by a tap gesture recognizer. This component provides
/// no additional activation context.
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *deselectText;

// MARK: Toggling the User Interface

/// Component responsible for toggling user interface.
///
/// This component is backed by a tap gesture recognizer. This component provides
/// no additional activation context.
///
/// You can take advantage of component activation conditions to allow or disallow
/// toggling user interface based on the provided location. For example, to only
/// allow toggling user interface outside of visible spread views, you can write:
///
/// ```
/// toggleUserInterface.addActivationCondition { _, point, coordinateSpace in
///     documentViewController.visibleSpreadViews.allSatisfy { spreadView in
///         let pointInSpreadView = spreadView.convert(point, from: coordinateSpace)
///         return !spreadView.bounds.contains(pointInSpreadView)
///     }
/// }
/// ```
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *toggleUserInterface;

/// Attempts to toggle user interface at the given location.
///
/// @note This method will respect the activation conditions of `toggleUserInterface`
/// interaction component but it will ignore its `enabled` property.
///
/// @param point Location of touch.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the attempt to toggle user interface succeeded as the result
/// of calling this method, otherwise `false`.
- (BOOL)tryToToggleUserInterfaceAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Customizing Multiple Interaction Components

/// A component composed of all other components: `selectAnnotation`,
/// `deselectAnnotation`, `editAnnotation`, `transformAnnotation`,
/// `openLinkAnnotation`, `showAnnotationMenu`, `fastScroll`, `smartZoom`,
/// `selectText`, `deselectText` and `toggleUserInterface`.
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *allInteractions;

/// Component composed of other components related to annotations: `selectAnnotation`,
/// `deselectAnnotation`, `editAnnotation`, `transformAnnotation`,
/// `openLinkAnnotation` and `showAnnotationMenu`.
///
/// You can take advantage of component activation conditions to allow or disallow
/// all interactions with annotations based on the given location. For example, to
/// disallow interacting in any way with annotations, you can write:
///
/// ```
/// allAnnotationInteractions.isEnabled = false
/// ```
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *allAnnotationInteractions;

/// Component composed of other components related to text selection: `selectText`
/// and `deselectText`.
@property (nonatomic, readonly) PSPDFInteractionComponent<NSNull *> *allTextInteractions;

@end

NS_ASSUME_NONNULL_END
