//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Returns the scale of the screen the view is on, or `PSPDFDefaultScale()` if the view is nil or not attached to a screen.
PSPDF_EXTERN CGFloat PSPDFScaleForView(UIView *_Nullable view);

#define PSPDFClosestSuperviewOfClass(__view__, __class__) (__class__ *_Nullable)[__view__ pspdf_closestSuperviewOfClass:__class__.class]
#define PSPDFClosestSubviewOfClass(__view__, __class__) (__class__ *_Nullable)[__view__ pspdf_closestSubviewOfClass:__class__.class]
#define PSPDFClosestSubviewOfClassAtPoint(__view__, __class__, __point__) (__class__ *_Nullable)[__view__ pspdf_closestSubviewOfClass:__class__.class atPoint:__point__]
#define PSPDFClosestSuperviewConformingToProtocol(__view__, __protocol__) (id<__protocol__> _Nullable)[__view__ pspdf_closestSuperviewConformingToProtocol:@protocol(__protocol__)]

@interface UIView (PSPDFAdditions)

// MARK: Appearance

/// The tint color without adjustment or darkening.
/// The returned color should be the same as one set with `setTintColor:`.
/// This should be used when the returned color is set as another view’s `tintColor`.
/// The raw tint color should not be shown to the user.
///
/// This workaround may no longer be necessary. The system seems smarter about this.
@property (nonatomic, readonly) UIColor *pspdf_rawTintColor;

/// Returns the effective background color that a bar has.
///
/// @param bar A `UINavigationBar`, `UIToolbar` or any other view that responds to
/// `standardAppearance`.
///
/// @return A `UIColor` that the bar uses as background color. Returns `nil` if `bar`
/// doesn't have a background color or it's transparent.
+ (nullable UIColor *)pspdf_effectiveBackgroundColorOfBar:(nullable UIView *)bar;

/// Returns the tint color to be used for selection effect, which matches the color
/// of the navigation bar or toolbar.
///
/// Effectively, this uses `pspdf_effectiveBackgroundColorOfBar` but tries to additionally
/// infer the color based on bar style and system appearance mode.
///
/// @param bar A `UINavigationBar`, `UIToolbar` or any other view that responds to
/// `standardAppearance`.
///
/// @return A `UIColor` which can be used as tint color for selection effect. Returns
/// `nil` if `bar` doesn't have a background color and it's impossible to inefer it
/// from other properties.
+ (nullable UIColor *)pspdf_selectedTintColorMatchingBar:(nullable UIView *)bar;

/// Returns the scale of the current screen if present, otherwise returns `PSPDFDefaultScale()`.
@property (nonatomic, readonly) CGFloat pspdf_currentScreenScale;

/// Customize the first responder focus ring on Mac Catalyst.
@property (nonatomic) BOOL pspdf_focusRingEnabled NS_SWIFT_NAME(focusRingEnabled);

// MARK: Animations

/// Default view animations with a predefined duration, matching most system animations.
+ (void)pspdf_animate:(BOOL)animate withBlock:(void (^)(void))animations;
+ (void)pspdf_animate:(BOOL)animate withOptions:(UIViewAnimationOptions)options block:(void (^)(void))animations completion:(nullable void (^)(BOOL finished))completion;

/// A springy animation with a predefined duration.
+ (void)pspdf_springAnimate:(BOOL)animate withBlock:(void (^)(void))animations;
+ (void)pspdf_springAnimate:(BOOL)animate withOptions:(UIViewAnimationOptions)options block:(void (^)(void))animations completion:(nullable void (^)(BOOL finished))completion;

/// Mimics the iOS keyboard and modal view controller animations.
+ (void)pspdf_smoothAnimate:(BOOL)animate withBlock:(void (^)(void))animations;
+ (void)pspdf_smoothAnimate:(BOOL)animate withOptions:(UIViewAnimationOptions)options block:(void (^)(void))animations completion:(nullable void (^)(BOOL finished))completion;

/// Removes a lot of boiler plate by properly setting up the animation context (smartly only animates if animationTime
/// is > 0, makes sure spring animations have enough time to complete and work in slow animations mode, etc.).
+ (void)pspdf_animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay springy:(BOOL)springy options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(nullable void (^)(BOOL finished))completion;

/// As above, but with spring options and without time adjustments for spring animations.
+ (void)pspdf_animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay springy:(BOOL)springy springDamping:(CGFloat)springDamping initialVelocity:(CGFloat)initialVelocity options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(nullable void (^)(BOOL finished))completion;

/// Performs a fade on the receiver.
- (void)pspdf_fadeAnimated:(BOOL)animated withActions:(void (^)(void))actions;
- (void)pspdf_fadeWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay actions:(void (^)(void))actions completion:(nullable void (^)(BOOL finished))completion;

/// Removes animations in view and all subviews
- (void)pspdf_removeAnimationsRecursively NS_SWIFT_NAME(removeAnimationsRecursively());

// MARK: View Introspection

/// Walks up the responder chain to find the closest view controller attached to this view.
/// Might return nil if the view is not in the window hierarchy.
@property (nonatomic, nullable, readonly) UIViewController *pspdf_closestViewController;

/// Walks up the responder chain to find the closest view controller attached to the
/// receiver that is of the passed in class.
///
/// @param viewControllerClass A class of kind `UIViewController` to look for.
/// @return The closest found view controller or `nil` if none was found.
- (nullable __kindof UIViewController *)pspdf_closestViewControllerOfClass:(Class)viewControllerClass NS_REFINED_FOR_SWIFT;

/// Walks up the responder chain to find the closest navigation controller attached to this view.
/// Might return nil if the view is not in the window hierarchy.
@property (nonatomic, nullable, readonly) UINavigationController *pspdf_closestNavigationController;

/// Queries the view’s ancestor chain for objects of `viewClass` and returns the first match or `nil`.
/// Swift: closestSuperview(of:)
- (nullable __kindof UIView *)pspdf_closestSuperviewOfClass:(Class)viewClass NS_REFINED_FOR_SWIFT;

/// Queries subview hierarchy for a specific class. Faster than the prefix or suffix searches.
/// Swift: closestSubview(of:)
- (nullable __kindof UIView *)pspdf_closestSubviewOfClass:(nullable Class)viewClass NS_REFINED_FOR_SWIFT;

/// Searches for the closest descendant at the given point that is of the specified class.
///
/// @param viewClass The class to look for.
/// @param point The point where to look at.
/// @return The found view or `nil` if no view was found at this point matching the class.
- (nullable __kindof UIView *)pspdf_closestSubviewOfClass:(nullable Class)viewClass atPoint:(CGPoint)point;

/// Queries the superview hierarchy for objects that conform to `protocol` and returns the first match or `nil`.
- (nullable __kindof UIView *)pspdf_closestSuperviewConformingToProtocol:(Protocol *)protocol;

/// Queries subviews for a specific class prefix. Usually used for subview-querying.
- (nullable UIView *)pspdf_closestSubviewWithClassPrefix:(NSString *)classNamePrefix;

/// Queries subviews for a specific class suffix. Usually used for subview-querying.
- (nullable UIView *)pspdf_closestSubviewWithClassSuffix:(NSString *)classNameSuffix;

/// The flattened subview tree, omitting the receiver.
@property (nonatomic, readonly) NSSet<UIView *> *pspdf_recursiveSubviews;

/// Check the superview hierarchy for "classes". Return YES if found.
- (BOOL)pspdf_hasAnySuperviewWithClassInClasses:(NSArray<Class> *)classes;

/// Check if the view is in the hierachy of a given parent view.
- (BOOL)pspdf_isInside:(UIView *)parentView;

/// Performs the block passed by using the view's trait collection as the current trait collection.
/// When the view trait collection is already set as the current trait collection,
/// the block operation is executed directly.
/// Wrapper to avoid the availability checks to resolve colors in a block.
- (void)pspdf_performBlockUsingViewTraitCollection:(NS_NOESCAPE void(^)(void))block;

/// Excecutes the `block` if the view's current trait collection has different color appearance
/// than the previous trait collection passed.
/// The changes in the `block` are themselves responsible for resolving the dynamic colors.
- (void)pspdf_performBlockIfAppearanceChangedFrom:(nullable UITraitCollection *)previousTraitCollection block:(NS_NOESCAPE void(^)(void))block NS_SWIFT_NAME(performIfAppearanceChanged(from:action:));

@end

NS_ASSUME_NONNULL_END
