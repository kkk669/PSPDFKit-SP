//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^PSPDFAnimationConfigurationBlock)(CABasicAnimation *);

/// Compensates the effect of SLOW ANIMATIONS in the iOS Simulator.
/// Use for `CATransition` etc. UIKit animations are automatically slowed down.
PSPDF_SDK_EXPORT CGFloat PSPDFSimulatorAnimationDragCoefficient(void) NS_SWIFT_NAME(SimulatorAnimationDragCoefficient());

@interface CALayer (PSPDFFoundation)

/// Animates from the current value of `property` to the `presentationLayer` value of the same property.
///
/// @note The method will not perfomr any animations if the `presentationLayer` is currently not available.
/// This might be what you want (no animation if the layer is not yet on screen) or not - than use the explicit methods.
/// @see pspdf_animateKeyPath:fromValue:toValue:duration:configurationBlock:completionBlock:
- (nullable CABasicAnimation *)pspdf_animateKeyPath:(NSString *)keyPath duration:(NSTimeInterval)duration;

/// Animates from the current `presentationLayer` value of `property` to `newValue`.
///
/// @see pspdf_animateKeyPath:fromValue:toValue:duration:configurationBlock:completionBlock:
- (nullable CABasicAnimation *)pspdf_animateKeyPath:(NSString *)keyPath toValue:(id)newValue duration:(NSTimeInterval)duration;

/// Animates `oldValue` of `property` to `newValue`.
///
/// @see pspdf_animateKeyPath:fromValue:toValue:duration:configurationBlock:completionBlock:
- (nullable CABasicAnimation *)pspdf_animateKeyPath:(NSString *)keyPath fromValue:(id)oldValue toValue:(id)newValue duration:(NSTimeInterval)duration;

/// Animates `oldValue` of `property` to `newValue` with an optional completion block.
///
/// @see pspdf_animateKeyPath:fromValue:toValue:duration:configurationBlock:completionBlock:
- (nullable CABasicAnimation *)pspdf_animateKeyPath:(NSString *)keyPath fromValue:(id)oldValue toValue:(id)newValue duration:(NSTimeInterval)duration completionBlock:(nullable dispatch_block_t)completionBlock;

/// Animates from `oldValue` of `property` to `newValue`.
///
/// @param keyPath The layer property key path that should be animated.
/// @param oldValue The previous value of property (needs to be an object value).
/// @param newValue The new value of property (needs to be an object value).
/// @param duration If duration is 0 no animation is performed and `newValue` is set immediately.
/// @param configurationBlock Called before the animation is added to the layer for further customization.
/// @param completionBlock Called when the animation completes. Called immediately if `duration` is 0.
/// @return The returned animation is already added to the layer so it can no longer be mutated. Can be `nil` if the animation did not need to be performed.
- (nullable CABasicAnimation *)pspdf_animateKeyPath:(NSString *)keyPath fromValue:(id)oldValue toValue:(id)newValue duration:(NSTimeInterval)duration configurationBlock:(nullable PSPDFAnimationConfigurationBlock)configurationBlock completionBlock:(nullable dispatch_block_t)completionBlock;

@end

NS_ASSUME_NONNULL_END
