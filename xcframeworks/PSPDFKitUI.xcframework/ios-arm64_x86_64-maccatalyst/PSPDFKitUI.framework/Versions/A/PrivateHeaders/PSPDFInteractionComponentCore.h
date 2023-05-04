//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFGestureRecognizerGroup;

NS_ASSUME_NONNULL_BEGIN

/// Signature of an interaction component activation permission block.
typedef BOOL (^PSPDFInteractionComponentCorePermissionBlock)(void);

/// Type-erased signature of an interaction component activation condition block.
typedef BOOL (^PSPDFInteractionComponentCoreConditionBlock)(id context, CGPoint point, id<UICoordinateSpace> coordinateSpace);

/// Type-erased signature of an interaction component activation callback block.
typedef void (^PSPDFInteractionComponentCoreCallbackBlock)(id context, CGPoint point, id<UICoordinateSpace> coordinateSpace);

// MARK: -

/// A protocol that defines a common interface for different implementations of
/// `PSPDFInteractionComponent`.
@protocol PSPDFInteractionComponentCore <NSObject>

// MARK: Customizing the Component Activation Conditions

/// Adds a permission block that will be taken into consideration when evaluating
/// activation conditions.
///
/// In practice, this allows `enabled` property to be implemented independently
/// from activation conditions, be managed by multiple composite components and,
/// most importantly, be skipped when needed.
///
/// @param permissionBlock Permission block to add.
- (void)addActivationPermission:(PSPDFInteractionComponentCorePermissionBlock)permissionBlock;

/// Adds a condition block that will be evaluated before the component attempts to
/// activate.
///
/// @param conditionBlock Condition block to add.
- (void)addActivationCondition:(PSPDFInteractionComponentCoreConditionBlock)conditionBlock;

/// Checks if the component can activate at the given location.
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
/// @param callbackBlock Callback block to add.
- (void)addActivationCallback:(PSPDFInteractionComponentCoreCallbackBlock)callbackBlock;

// MARK: Setting up Relationships with Gesture Recognizers

/// A group of gesture recognizers that can be used to set up relationships with
/// other gesture recognizers.
@property (nonatomic, readonly) PSPDFGestureRecognizerGroup *gestureRecognizers;

@end

NS_ASSUME_NONNULL_END
