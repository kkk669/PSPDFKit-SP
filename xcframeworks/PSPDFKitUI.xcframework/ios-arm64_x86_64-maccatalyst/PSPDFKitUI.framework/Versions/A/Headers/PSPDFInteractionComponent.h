//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that encapsulates one or more user actions handled by the framework.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(InteractionComponent)
@interface PSPDFInteractionComponent<ContextType> : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

// MARK: Customizing the Component Activation Conditions

/// A boolean value that indicates whether the component is enabled or not. If this
/// property is `false`, the component will not activate and all (if any) underlying
/// gesture recognizers will transition to `Failed` state.
@property (nonatomic, getter = isEnabled) BOOL enabled;

/// Adds a condition block that will be evaluated before the component attempts to
/// activate. If any condition block returns `false`, the component will not activate
/// and all (if any) underlying gesture recognizers will transition to `Failed`
/// state.
///
/// @note If any condition block returns `false`, subsequent condition blocks will not
/// be executed.
///
/// @param conditionBlock Condition block to add.
- (void)addActivationCondition:(BOOL (^)(ContextType context, CGPoint point, id<UICoordinateSpace> coordinateSpace))conditionBlock;

/// Checks if the component can activate at the given location. This method will
/// first try to determine an activation context at the given location and then it
/// will evaluate the previously added activation conditions, including the ones
/// added by the framework itself.
///
/// @note This method will respect the activation conditions of this interaction
/// component but it will ignore the value of `enabled` property.
///
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return `true` if the interaction component can activate at the given location,
/// otherwise `false`.
- (BOOL)canActivateAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Responding to Component Activation

/// Adds a callback block that will be executed **just before** the component
/// performs its action.
///
/// @note It is too late to prevent the component from activating inside the
/// callback block. For that, use `addActivationCondition`.
///
/// @param callbackBlock Callback block to add.
- (void)addActivationCallback:(void (^)(ContextType context, CGPoint point, id<UICoordinateSpace> coordinateSpace))callbackBlock;

// MARK: Setting up Relationships with Other Gesture Recognizers

/// Check if this component contains the given gesture recognizer.
- (BOOL)containsGestureRecognizer:(UIGestureRecognizer *)gestureRecognizer;

/// Creates a relationship with the given gesture recognizer that will prevent the
/// gesture recognizers in this component from transitioning from `Possible` state
/// until `otherGestureRecognizer` transitions to `Failed` state.
///
/// If `otherGestureRecognizer` transitions to `Began` or `Ended` state then the
/// gesture recognizers in this component will instead transition to `Failed`
/// state.
///
/// @note Not all components are backed by gesture recognizers, and some components
/// can be backed by gesture recognizers just on one iOS version. Be sure to check
/// documentation of individual components to learn more.
///
/// @param otherGestureRecognizer Other gesture recognizer.
- (void)requireGestureRecognizerToFail:(UIGestureRecognizer *)otherGestureRecognizer NS_SWIFT_NAME(require(toFail:));

/// Creates a relationship with the given gesture recognizer that will allow the
/// gesture recognizers in this component to transition out of `Possible` state at
/// the same time as `otherGestureRecognizer`.
///
/// @note Not all components are backed by gesture recognizers, and some components
/// can be backed by gesture recognizers just on one iOS version. Be sure to check
/// documentation of individual components to learn more.
///
/// @param otherGestureRecognizer Other gesture recognizer.
- (void)allowSimultaneousRecognitionWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

@end

// MARK: -

@interface UIGestureRecognizer (PSPDFInteractionComponentSupport)

// MARK: Setting up Relationships with Other Components

/// Creates a relationship with gesture recognizers in the given component that
/// will prevent this gesture recognizer from transitioning from `Possible` state
/// until all gesture recognizers in `otherComponent` transition to `Failed` state.
///
/// If any gesture recognizer in `otherComponent` transitions to `Began` or `Ended`
/// state then this gesture recognizer will instead transition to `Failed` state.
///
/// @note Not all components are backed by gesture recognizers, and some components
/// can be backed by gesture recognizers just on one iOS version. Be sure to check
/// documentation of individual components to learn more.
///
/// @param otherComponent Other interaction component.
- (void)pspdf_requireGestureRecognizersInComponentToFail:(PSPDFInteractionComponent *)otherComponent NS_SWIFT_UNAVAILABLE("Use `require(toFail:)` instead.");

@end

NS_ASSUME_NONNULL_END
