//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines the style of the status HUD.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFStatusHUDStyle) {
    /// User interactions enabled, no UI mask.
    PSPDFStatusHUDStyleNone = 0,
    /// User interactions disabled, clear UI mask.
    PSPDFStatusHUDStyleClear,
    /// User interactions disabled, black UI mask.
    PSPDFStatusHUDStyleBlack
} PSPDF_ENUM_SWIFT(StatusHUDItem.Style);

@class PSPDFStatusHUDItem;


@protocol PSPDFStatusHUDItemDelegate
- (void)statusHUDItemDidTapActionButton:(nullable PSPDFStatusHUDItem *)hudItem;
@end

/// Represents a single HUD item.
///
/// @warning Only use this class on the main thread.
PSPDF_CLASS_SWIFT(StatusHUDItem)
@interface PSPDFStatusHUDItem : NSObject

/// The title to display. Can be nil.
@property (nonatomic, copy, nullable) NSString *title;

/// The subtitle to display. Can be nil.
@property (nonatomic, copy, nullable) NSString *subtitle;

/// The main text to display. Can be nil.
@property (nonatomic, copy, nullable) NSString *text;

@property (nonatomic, copy, nullable) NSString *actionTitle;

/// Set if we should show progress.
@property (nonatomic) CGFloat progress;

/// An attached view.
@property (nonatomic, nullable) UIView *view;

/// The item's delegate to handle actions. Can be nil.
@property (nonatomic, weak) id<PSPDFStatusHUDItemDelegate> delegate;

/// Creates a status HUD item with progress, and adds an action button to it.
///
/// @param text Text that should be shown on the HUD item.
/// @param title The title for the action associated with the HUD item.
+ (instancetype)progressWithText:(nullable NSString *)text actionTitle:(nullable NSString *)title;

/// Creates a status HUD item with progress.
///
/// @param text Text that should be shown on the HUD item.
+ (instancetype)progressWithText:(nullable NSString *)text;

/// Creates a status HUD item with an indeterminate progress, and adds an action button to it.
///
/// @param text Text that should be shown on the HUD item.
/// @param title The title for the action associated with the HUD item.
+ (instancetype)indeterminateProgressWithText:(nullable NSString *)text actionTitle:(nullable NSString *)title;

/// Creates a status HUD item with an indeterminate progress.
///
/// @param text Text that should be shown on the HUD item.
+ (instancetype)indeterminateProgressWithText:(nullable NSString *)text;

/// Creates a status HUD item with a success indicator.
///
/// @param text Text that should be shown on the HUD item.
+ (instancetype)successWithText:(nullable NSString *)text;

/// Creates a status HUD item with an error indicator.
///
/// @param text Text that should be shown on the HUD item.
+ (instancetype)errorWithText:(nullable NSString *)text;

/// Creates a status HUD item with a text and an image.
///
/// @param text Text that should be shown on the HUD item.
/// @param image Image that should be shown on the HUD item.
+ (instancetype)itemWithText:(nullable NSString *)text image:(nullable UIImage *)image;

/// Change how the HUD should be styled.
- (void)setHUDStyle:(PSPDFStatusHUDStyle)style;

/// Show the HUD item on the provided window. Doesn't do anything if the window is nil.
///
/// @note The `completion` block will not be called if the window is `nil`.
- (void)pushAnimated:(BOOL)animated onWindow:(nullable UIWindow *)window completion:(nullable void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

/// Show the HUD item on the provided window and schedule a dismissal time. If the window is nil, 
/// the completion block is still called, but no operation is performed.
///
/// @note The `completion` block will not be called if the window is `nil` or
/// if this item is not displayed in the window's HUD.
- (void)pushAndPopWithDelay:(NSTimeInterval)interval animated:(BOOL)animated onWindow:(nullable UIWindow *)window completion:(nullable void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

/// Hide the HUD item.
///
/// @note The `completion` block will not be called if the window is `nil` or
/// if this item is not displayed in the window's HUD.
- (void)popAnimated:(BOOL)animated completion:(nullable void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

@end

/// A progress view/status HUD.
PSPDF_CLASS_SWIFT(StatusHUD)
@interface PSPDFStatusHUD : NSObject

/// All the status HUD items to be shown.
+ (nullable NSArray<PSPDFStatusHUDItem *> *)itemsForHUDOnWindow:(nullable UIWindow *)window;

/// Hide all visible status HUD items, if any. Doesn't do anything if the window is nil.
///
/// @note The `completion` block will not be called if the window is `nil`.
/// Otheriwse, it may be called multiple times, once for every visible item.
+ (void)popAllItemsAnimated:(BOOL)animated forHUDOnWindow:(nullable UIWindow *)window completion:(nullable void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

@end

/// Status HUD view that represents a given status HUD item.
PSPDF_CLASS_SWIFT(StatusHUDView)
@interface PSPDFStatusHUDView : UIView<PSPDFOverridable>

/// Status HUD item to be shown on the view.
@property (nonatomic, nullable) PSPDFStatusHUDItem *item;

@end

NS_ASSUME_NONNULL_END
