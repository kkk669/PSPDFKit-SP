//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
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

NS_ASSUME_NONNULL_BEGIN

/// Will call `handler` when `trigger` is called, but always adds `delay`.
/// If the object is deallocated, it might not trigger the last pending trigger action.
///
/// Typically you create one timer per method or action you want to debounce. Instead
/// of calling this method directly, you then always either call `trigger` or `triggerAndReset`
/// on the debounce timer. The debounce timer will then make sure that it does not
/// call the method or action it is set up with more often than `delay.
///
/// The first call to `trigger` will set up a timer that calls the linked action after
/// the given delay. All subsequent calls to `trigger` do nothing until the timer fires.
/// When this happens, the timer is invalidated and another call to `trigger` will start
/// this cycle again. Instead of calling `trigger` you can also call `triggerAndReset`,
/// which basically does the same with one exception: When calling `triggerAndReset`
/// while the timer is already set up, the timer's fire date is reset to fire in the
/// configured delay from now on.
PSPDF_SDK_CLASS_SUBCLASSING_RESTRICTED_SWIFT(DebouncedTimer)
@interface PSPDFDebouncedTimer : NSObject

/// Convenience initializer for the main thread with reasonable value for leeway.
+ (instancetype)timerWithDelay:(NSTimeInterval)delay handler:(void (^)(id sender))handler;

/// Convenience initializer for the main thread with reasonable value for leeway with target/action pattern.
///
/// @param delay The dealy after witch the targete should be fired.
/// @param target The object on which `action` is to be called.
/// @param action The selector to call on the object.
/// @return An instance of `PSPDFDebouncedTimer`.
+ (instancetype)timerWithDelay:(NSTimeInterval)delay target:(NSObject *)target action:(SEL)action;

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initialize with the wanted delay and the action block handler.
/// `queue` defaults to the main thread queue if not set.
/// `leeway` helps with energy usage if delay doesn't has to be super specific.
- (instancetype)initWithDelay:(NSTimeInterval)delay leeway:(NSTimeInterval)leeway queue:(nullable dispatch_queue_t)queue handler:(void (^)(id sender))handler NS_DESIGNATED_INITIALIZER;

/// Triggers calling the handler block after the set delay.
///
/// If the timer is already triggered and delay has not passed yet, this method
/// does nothing.
- (void)trigger;

/// Triggers and also re-sets the timer to `delay`.
///
/// If the timer is already triggered and delay has not passed yet, this method
/// resets the delay to it's original value, expanding the overall time the timer
/// waits before actually calling the handler.
///
/// @note If you call this method to often and periodically, you could potentially
/// build a debounce timer that never fires. Make sure to use this method only
/// for trigger that happen in bursts with a guaranteed period where this method
/// is not called and that is longer than the configured delay.
- (void)triggerAndReset;

/// Cancels trigger event (if one is set)
- (void)cancel;

/// The attached handler block
@property (nonatomic, copy, readonly) void (^handler)(id sender);

/// The trigger delay.
@property (nonatomic, readonly) NSTimeInterval delay;

/// Internal leeway for timer.
/// Optimize CPU wakeup and energy usage by setting this to a non-nil value.
/// See `dispatch_source_set_timer` for details.
@property (nonatomic, readonly) NSTimeInterval leeway;

/// The target queue for block execution.
@property (nonatomic, readonly) dispatch_queue_t queue;

@end

NS_ASSUME_NONNULL_END
