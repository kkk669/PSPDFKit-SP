//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAvoidingScrollView.h>

@class PSPDFMulticastDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NSString *PSPDFInsetIdentifier NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(InsetIdentifier);

PSPDF_EXPORT PSPDFInsetIdentifier const PSPDFInsetIdentifierDefault;

@interface PSPDFAvoidingScrollView ()

/// If you 'upgrade' the delegate in a subclass, make sure to return the right protocol
/// here or you might get some nasty crashes when calling the added delegate methods
/// in some scenarios.
///
/// @return The protocol the `delegate` property holds.
+ (Protocol *)delegateProtocol;

/// Support for multiple simultaneously applied content insets.
- (void)setContentInset:(UIEdgeInsets)contentInset withIdentifier:(PSPDFInsetIdentifier)identifier;
- (UIEdgeInsets)contentInsetForIdentifier:(PSPDFInsetIdentifier)identifier;
- (void)setScrollIndicatorInsets:(UIEdgeInsets)scrollIndicatorInsets withIdentifier:(PSPDFInsetIdentifier)identifier;
- (UIEdgeInsets)scrollIndicatorInsetsForIdentifier:(PSPDFInsetIdentifier)identifier;

/// Additional edge insets to take into consideration when accepting touches.
@property (nonatomic) UIEdgeInsets hitTestingInsets;

/// Cancels any scheduled keyboard operations and resets `keyboardVisible` and `halfModalVisible`.
- (void)prepareForReuse NS_REQUIRES_SUPER;

/// To manually fake a keyboard.
- (void)moveScrollViewUpForRect:(CGRect)rect focusRect:(CGRect)focusRect animated:(BOOL)animated;

/// Adjusts the receiver’s `contentInset`, `scrollIndicatorInsets` and `contentOffset` for a given avoidance rectangle and focused view or rectangle.
/// Exposed in header for tests.
///
/// @param rect The rectangle to be avoided (in the screen coordinate space). I.e. the keyboard frame.
/// @param focusRect An optional rectangle to keep visible (in the receiving scroll view’s coordinate space). This may be CGRectZero, which is like nil. If checkFirstResponder is set, then the first responder takes priority over this parameter.
/// @param checkFirstResponder If true, check for a focus rectangle from the first responder, which will be given priority over `focusRect`.
/// @param animatorBlock This block will be called to run the animation and will passed a block to make the property updates.
- (BOOL)moveScrollViewUpForRect:(CGRect)rect focusRect:(CGRect)focusRect checkFirstResponder:(BOOL)checkFirstResponder animatorBlock:(void (^)(dispatch_block_t animationBlock))animatorBlock;

- (void)moveScrollViewDownAnimated:(BOOL)animated;

- (BOOL)moveScrollViewDownWithAnimatorBlock:(void (^)(dispatch_block_t animationBlock))animatorBlock;

/// Indicates if the keyboard is visible.
///
/// @note Allows KVO bindings. Changed after internal state and contentInset has been
/// updated.
@property (nonatomic, readonly) BOOL isKeyboardVisible;

/// Specifies whether the insets to apply to the receiver that will center the content
/// should be applied automatically.
///
/// Defaults to `false`. See https://github.com/PSPDFKit/PSPDFKit/issues/12365 for the
/// issue this resolves.
@property (nonatomic) BOOL automaticallyApplyContentCenteringInsets;

/// Moves the content offset so that it is outside of the top / left content insets
/// area, if it is currently inside.
///
/// @param animated Whether the content inset change should be animated or not.
- (void)scrollToAvoidContentInsetAnimated:(BOOL)animated;

// MARK: Multi Delegate

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
- (void)addDelegate:(id<UIScrollViewDelegate>)delegate;

/// Removes a delegate from the list.
///
/// @see `-addDelegate:`
///
/// @param delegate The delegate to remove.
- (void)removeDelegate:(id<UIScrollViewDelegate>)delegate;

/// Called when the multicast delegate is updated so subclasses can access it.
///
/// @param delegate The new multicast delegate.
- (void)multicastDelegateDidChange:(PSPDFMulticastDelegate<UIScrollViewDelegate> *)delegate;

@end

NS_ASSUME_NONNULL_END
