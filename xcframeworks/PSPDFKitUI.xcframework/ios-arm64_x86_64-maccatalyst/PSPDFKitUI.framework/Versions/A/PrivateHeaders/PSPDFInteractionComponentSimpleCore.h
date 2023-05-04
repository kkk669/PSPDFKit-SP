//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFInteractionComponentCore.h>

NS_ASSUME_NONNULL_BEGIN

/// Type-erased signature of an activation context provider block.
typedef id _Nullable (^PSPDFInteractionComponentSimpleCoreContextProviderBlock)(CGPoint point, id<UICoordinateSpace> coordinateSpace);

// MARK: -

/// An interaction component core that encapsulates a single action managed by an
/// interaction.
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFInteractionComponentSimpleCore<ContextType> : NSObject <PSPDFInteractionComponentCore>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new instance with the given array of gesture recognizers and a
/// block that provides an activation context at the given point.
- (instancetype)initWithGestureRecognizers:(NSArray<UIGestureRecognizer *> *)gestureRecognizers contextProvider:(ContextType _Nullable (^)(CGPoint point, id<UICoordinateSpace> coordinateSpace))contextProviderBlock NS_DESIGNATED_INITIALIZER;

// MARK: Obtaining the Activation Context

/// Asks the component to determine an activation context at the given location.
///
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
///
/// @return Activation context at the given location, or `nil` if there is none.
- (nullable ContextType)contextForActivationAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

// MARK: Evaluating the Activation Conditions

/// Evaluates all previously added activation conditions with the given context and
/// at the given point. This method stops evaluating if any of the conditions
/// returns `false`.
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
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
/// @param obeyPermissions Whether to obey the activation permissions.
///
/// @return `false` if activation context provider block failed to provide an object,
/// otherwise `true` if all condition blocks returned `true`, otherwise `false`.
- (BOOL)evaluateActivationConditionsAtPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace obeyPermissions:(BOOL)obeyPermissions;

// MARK: Executing the Activation Callbacks

/// Executes all previously added activation callbacks with the given context and
/// at the given point.
///
/// @param context Activation context object.
/// @param point Location of attempted activation.
/// @param coordinateSpace Coordinate space of `point`.
- (void)executeActivationCallbacksWithContext:(ContextType)context atPoint:(CGPoint)point inCoordinateSpace:(id<UICoordinateSpace>)coordinateSpace;

@end

NS_ASSUME_NONNULL_END
