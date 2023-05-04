//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFKeyboardTrackerState) {
    /// The keyboard is not visible.
    PSPDFKeyboardTrackerStateNotVisible,
    /// The keyboard is changing frame. This can be hide->show but also a resize, custom keyboard frame change.
    /// Changing frame is set before the switch to .appearing or .disappearing.
    PSPDFKeyboardTrackerStateChangingFrame,
    /// The keyboard is about to be presented.
    PSPDFKeyboardTrackerStateAppearing,
    /// The keyboard is disappearing.
    PSPDFKeyboardTrackerStateDisappearing,
    /// The keyboard is visible. (All states)
    PSPDFKeyboardTrackerStateVisible,
} NS_SWIFT_NAME(KeyboardTrackerState);

/// Container that offers better typed variants of the keyboard data received in notifications.
PSPDF_APP_CLASS_SUBCLASSING_RESTRICTED_SWIFT(KeyboardNotificationData)
@interface PSPDFKeyboardNotificationData : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initialize with the user info received from a keyboard notification.
- (instancetype)initWithKeyboardUserInfo:(NSDictionary<NSString*, id> *)keyboardInfo NS_DESIGNATED_INITIALIZER;

/// The current frame in which the keyboard is displayed. Coordinates are not rotated.
@property (nonatomic, readonly) CGRect frame;

/// Helper that gets the keyboard height from `keyboardFrame`.
@property (nonatomic, readonly) CGFloat height;

/// Checks if the keyboard is floating (introduced in iOS 13) or in split mode/undocked (Introduced in iOS 5).
///
/// @see https://support.apple.com/en-us/HT207521
/// @note The split keyboard isn't available on iPad Pro (12.9-inch) or iPad Pro 11-inch. Floating is available on all iPad models.
@property (nonatomic, readonly) BOOL isFloating;

/// Checks if the keyboard's frame is on the main screen.
@property (nonatomic, readonly) BOOL isVisible;

/// Checks if the keyboard is presented by us. (`UIKeyboardIsLocalUserInfoKey`).
/// Keyboard can be also presented because we're in split screen mode and the other app requires it.
///
/// @see https://useyourloaf.com/blog/split-views-and-unexpected-keyboards/
@property (nonatomic, readonly) BOOL isLocal;

/// Raw keyboard info data based on the last notification received.
@property (nonatomic, readonly) NSDictionary<NSString*, id> *keyboardInfo;

// MARK: Animation options

@property (nonatomic, readonly) CGRect beginFrame;
@property (nonatomic, readonly) UIViewAnimationOptions animationOptions;
@property (nonatomic, readonly) NSTimeInterval animationDuration;

@end

/// Tracks the keyboard state. Operates on the main thread only.
PSPDF_APP_CLASS_SUBCLASSING_RESTRICTED_SWIFT(KeyboardTracker)
@interface PSPDFKeyboardTracker : NSObject

/// Initialze keyboard tracker with update block.
+ (instancetype)keyboardTrackerWithUpdateBlock:(nullable void( (^))(PSPDFKeyboardTracker *tracker))updateBlock;

/// Tracks if the keyboard is currently visible.
/// Evaluates `keyboardState` and returns YES if not invisible or currently disappearing. KVO observable.
@property (nonatomic, getter=isKeyboardVisible, readonly) BOOL keyboardVisible;

/// Current keyboard state (if animating). KVO observable.
///
/// This class guarantees that we always run through a full series of state transitions, no matter how the keyboard is presented:
/// .notVisible -> .changingFrame -> .appearing -> .visible -> .changingFrame -> .disappearing -> .notVisible
@property (nonatomic, readonly) PSPDFKeyboardTrackerState state;

/// Access details about the current keyboard presentation.
@property (nonatomic, readonly) PSPDFKeyboardNotificationData *data;

/// Block will be called when `state` or `keyboardFrame` changes.
@property (nonatomic, copy, readonly, nullable) void (^keyboardUpdatedBlock)(PSPDFKeyboardTracker *keyboardTracker);

/// Animate changes alongside the keyboard.
- (void)animateWithOptions:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(nullable void (^)(BOOL finished))completion;

@end

NS_ASSUME_NONNULL_END
