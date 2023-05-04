//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFInteractionComponent.h>

@class PSPDFGestureRecognizerGroup;
@class PSPDFInteractionComponentSimpleCore<ContextType>;
@class PSPDFInteractionComponentCompositeCore;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFInteractionComponent<ContextType> ()

/// Initializes a simple component with the given simple core.
+ (instancetype)simpleComponentWithCore:(PSPDFInteractionComponentSimpleCore<ContextType> *)core;

/// Initializes a simple component with the given array of gesture recognizers and a
/// block that provides an activation context at the given point.
+ (instancetype)simpleComponentWithGestureRecognizers:(NSArray<UIGestureRecognizer *> *)gestureRecognizers contextProvider:(ContextType _Nullable (^)(CGPoint point, id<UICoordinateSpace> coordinateSpace))contextProviderBlock;

/// Initializes a composite component with the given composite core.
+ (instancetype)compositeComponentWithCore:(PSPDFInteractionComponentCompositeCore *)core;

/// Initializes a composite component with the given array of underlying components.
+ (instancetype)compositeComponentWithOtherComponents:(NSArray<PSPDFInteractionComponent *> *)components;

/// Initialize a component that has no activation context and is always disabled.
/// This component doesn't have much use except for being a placeholder.
+ (instancetype)nullComponent;

// MARK: Conveniently Accessing the Core

/// A group of gesture recognizers that can be used to set up relationships with
/// other gesture recognizers.
@property (nonatomic, readonly) PSPDFGestureRecognizerGroup *gestureRecognizers;

/// Asks the component to determine an activation context at the given location.
///
/// @warning Calling this method on a component with composite core is a programmer
/// error. This method will assert.
///
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return Activation context at the given location, or `nil` if there is none.
- (nullable ContextType)contextForActivationAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

/// Evaluates all previously added activation conditions with the given context and
/// at the given point. This method stops evaluating if any of the conditions
/// returns `false`.
///
/// @warning Calling this method on a component with composite core is a programmer
/// error. This method will assert.
///
/// @param context Activation context object.
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
/// @param obeyPermissions Whether to obey the activation permissions.
///
/// @return `true` if all condition blocks returned `true`, otherwise `false`.
- (BOOL)evaluateActivationConditionsWithContext:(ContextType)context atPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace obeyPermissions:(BOOL)obeyPermissions;

/// Evaluates all previously added activation conditions at the given point. This
/// method stops evaluating if any of the conditions returns `false`.
///
/// @warning Calling this method on a component with composite core is a programmer
/// error. This method will assert.
///
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
/// @param obeyPermissions Whether to obey the activation permissions.
///
/// @return `false` if activation context provider block failed to provide an object,
/// otherwise `true` if all condition blocks returned `true`, otherwise `false`.
- (BOOL)evaluateActivationConditionsAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace obeyPermissions:(BOOL)obeyPermissions;

/// Executes all previously added activation callbacks with the given context and
/// at the given point.
///
/// @warning Calling this method on a component with composite core is a programmer
/// error. This method will assert.
///
/// @param context Activation context object.
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
- (void)executeActivationCallbacksWithContext:(ContextType)context atPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Setting up Relationships with Other Components

/// Creates a relationship with gesture recognizers in the given component that
/// will prevent the gesture recognizers in this component from transitioning from
/// `Possible` state until all gesture recognizers in `otherComponent` transition
/// to `Failed` state.
///
/// If any gesture recognizer in `otherComponent` transitions to `Began` or `Ended`
/// state then the gesture recognizers in this component will instead transition to
/// `Failed` state.
///
/// @note Not all components are backed by gesture recognizers, and some components
/// can be backed by gesture recognizers just on one iOS version. Be sure to check
/// documentation of individual components to learn more.
///
/// @param otherComponent Other interaction component.
- (void)requireGestureRecognizersInComponentToFail:(PSPDFInteractionComponent *)otherComponent;

/// Creates a relationship with gesture recognizers in the given component that
/// will allow the gesture recognizers in this component to transition out of
/// `Possible` state at the same time as any gesture recognizer in `otherComponent`.
///
/// @note Not all components are backed by gesture recognizers, and some components
/// can be backed by gesture recognizers just on one iOS version. Be sure to check
/// documentation of individual components to learn more.
///
/// @param otherComponent Other interaction component.
- (void)allowSimultaneousRecognitionWithGestureRecognizersInComponent:(PSPDFInteractionComponent *)otherComponent;

// MARK: Transforming the Activation Context

/// Creates an interaction component that will transform the activation context
/// of this interaction component using the given `transformBlock`.
///
/// This can be useful to type-erase interaction components or map a private
/// activation context type into a public one.
///
/// - Parameters:
///     - transformBlock A block that transforms the activation context.
///
/// - Returns: A new interaction component that transforms the activation
///   context of this interaction component using the given `transformBlock`.
///   The returned interaction component will be generic over the return type of
///   the block.
- (PSPDFInteractionComponent *)componentByTransformingContext:(id (^)(ContextType context))transformBlock;

@end

NS_ASSUME_NONNULL_END
