//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAlertController;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPresentationStyle) {
    /// Present the view controller using the style in its `modalPresentationStyle`.
    PSPDFPresentationStyleNone,

    /// Present the view controller full-width anchored to the bottom of the screen if the width is horizontally compact, and as a popover otherwise.
    PSPDFPresentationStyleHalfModal,
} PSPDF_ENUM_SWIFT(PresentationStyle);

/// The user interface style for the contents when presenting in a half-modal or a popover.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPresentationHalfModalStyle) {
    /// Content is displayed in the form of cards with a translucent navigation bar. This is the default value.
    PSPDFPresentationHalfModalStyleCard,

    /// Content is displayed edge to edge with a default navigation bar.
    PSPDFPresentationHalfModalStyleSystem
} PSPDF_ENUM_SWIFT(PresentationHalfModalStyle);

typedef NSString *PSPDFPresentationOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PresentationOption);

/// Presentation style.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionPresentationStyle; // See `PSPDFPresentationStyle`.

/// User interface style for the contents when presenting in a half-modal or a popover.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionHalfModalStyle; // See `PSPDFPresentationHalfModalStyle`.

/// Set to YES to prevent the presentation from adapting to a different style.
/// This may be used to show popovers in horizontally compact environments.
/// The object stored with this key is expected to be an `NSNumber` wrapping a Boolean value.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionNonAdaptive;

/// Specific for popovers:

/**
 A block than can be queried to get the current presentation source rectangle, used for popovers and half modal presentations.
 This is interpreted relative to the source view controller’s view.
 The type of the block is `CGRect (^)()`: it doesn’t take any arguments and return a `CGRect`.
 This works if the container view resizes, so is preferred over the rectangle in `PSPDFPresentationOptionSourceRect`.
 */
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionSourceRectProvider;

/// A convenience for setting the presented view controller’s `preferredContentSize` just before it is presented.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionContentSize;

/// Navigation Controller and close button logic.

/// Set to YES to embed the controller in a navigation controller. If the controller is already a navigation controller, no change is made.
/// This option is inferred if a close button should be added due to `PSPDFPresentationOptionCloseButton` being set.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionInNavigationController;

/// Set to YES to add a close button that dismisses the presented view controller.
/// This implies embedding in a navigation controller so it’s not necessary to also set `PSPDFPresentationOptionInNavigationController`.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionCloseButton;

/// If this is YES and there is an existing presentation in place that also set this to YES, and both presented view controllers are navigation controllers of the same class, then the existing presentation will be reused by setting the `viewControllers` of the existing navigation controller.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionReuseNavigationController;

/// Customize default arrow directions for popover.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionPopoverArrowDirections;

/// Customize the popover click-through views.
/// This is required as changing `passthroughViews` after the controller has been presented has no effect.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionPopoverPassthroughViews;

/// Customize the popover backdrop view background color (includes the arrow color).
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionPopoverBackgroundColor;

/// The presentation source rectangle, used for popovers and half modal presentations.
/// This is interpreted relative to the source view controller’s view.
/// `PSPDFPresentationOptionSourceRectProvider` is preferred.
PSPDF_EXPORT PSPDFPresentationOption const PSPDFPresentationOptionSourceRect;

/// Methods to present/dismiss view controllers.
/// UIViewController doesn't expose enough to conveniently present/dismiss controllers, so this protocol extends it.
PSPDF_PROTOCOL_SWIFT(PresentationActions)
@protocol PSPDFPresentationActions<NSObject>

/// Presents a view controller using the specified options.
///
/// @note If the presentation is blocked (e.g. return NO on the shouldShow delegate), the completion block will not be called.
/// @warning The presented view controller’s `presentationController` and `popoverPresentationController` should not be accessed before calling this method, because the presentation style or transitioning delegate may change.
/// If you need to configure the popover presentation, set values in the options with keys `PSPDFPresentationOptionSourceRectProvider`, `PSPDFPresentationOptionPopoverArrowDirections`, and `PSPDFPresentationOptionPopoverPassthroughViews`.
- (BOOL)presentViewController:(UIViewController *)viewController options:(nullable NSDictionary<PSPDFPresentationOption, id> *)options animated:(BOOL)animated sender:(nullable id)sender completion:(nullable void (^)(void))completion;

/// Dismisses a view controller of class `controllerClass` that was previously presented with `presentViewController:options:animated:sender:completion:`.
/// If `controllerClass` is `nil` then view controllers of any class may be dismissed.
- (BOOL)dismissViewControllerOfClass:(nullable Class)controllerClass animated:(BOOL)animated completion:(nullable void (^)(void))completion;

@end

NS_ASSUME_NONNULL_END
