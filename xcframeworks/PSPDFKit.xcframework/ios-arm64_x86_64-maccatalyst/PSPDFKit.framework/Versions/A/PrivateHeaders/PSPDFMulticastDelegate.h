//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
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

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFMulticastDelegateReturnValueChaining) {
    // Stops at the first implementation and returns that result.
    PSPDFMulticastDelegateReturnValueChainingStopOnFirstCall,

    // Calls all implementations, discards all returns except the first.
    PSPDFMulticastDelegateReturnValueChainingCallAllReturnFirst
} NS_SWIFT_UNAVAILABLE("This should not exist in the first place — please do not write new code using it");

/// May be used to set a delegate that forwards to multiple targets.
/// Use this as the delegate for single delegate APIs.
///
/// @note If a delegate's return type is anything other than void, the last return type will be used and all previous ones are unused/discarded.
///
/// @warning Will not work for `UITextView` or `UITextField` due to UIKit implementation details.
/// Some UIKit classes might cache respondsToSelector, in which case you need to call `copy` and set the new multicast delegate as delegate.
// TODO(Q): Necessary? Also: Only makes sense for Observers — never for delegates (see remarks on Chaining enums)
PSPDF_SDK_CLASS_SWIFT(MulticastDelegate)
@interface PSPDFMulticastDelegate<DelegateType> : NSProxy <NSCopying, NSMutableCopying>

/// If `owner` is set, associated objects will be used to keep the multicast delegate alive until owner dealloc's.
+ (nullable instancetype)multicastWithOwner:(nullable id)owner delegates:(nullable DelegateType)firstDelegate, ... NS_REQUIRES_NIL_TERMINATION;

/// Returns a delegate that can be used to receive delegate calls on both `owner` and `delegate`.
/// Can return either a new `PSPDFMulticastDelegate` or `delegate`.
///
/// The multicast delegate will be kept alive until owner dealloc's.
/// `delegate`, if available, will be prioritized over `owner` for calls that don't return void.
+ (nullable instancetype)delegateToOwner:(id)owner forwardingTo:(nullable DelegateType)delegate;

/// Initializer. `owner` is optional.
/// Will return nil if there delegates array is empty and no protocol is set.
- (nullable instancetype)initWithDelegates:(nullable NSArray<DelegateType> *)delegates owner:(nullable id)owner protocol:(nullable Protocol *)protocol;

/// All delegates attached to this multicast delegate.
///
/// @note Delegates are saved weakly, so this might just return an empty array.
@property (nonatomic, readonly) NSArray<DelegateType> *delegates;

// MARK: Invocation behavior

/// Creates a copy and updates the defaultReturnValue.
- (instancetype)copyThatDefaultsTo:(nullable NSObject *)defaultValue;

/// The default return value, used to initialize BOOL delegate chains and returned,
/// if no delegates implement a non-void selector. Defaults to `nil`.
@property (atomic, nullable) NSObject *defaultReturnValue;

/// Defines how delegates that return non-void and non-BOOL methods are called.
/// Defaults to `PSPDFMulticastDelegateReturnValueChainingStopOnFirstCall`.
///
/// Methods that return a value but which is dicarded might be unepxected, but is convenient if your delegate implementation just requires to be notified on a call. In that case use `PSPDFMulticastDelegateReturnValueChainingCallAllReturnFirst`.
@property (nonatomic) PSPDFMulticastDelegateReturnValueChaining valueChaining NS_SWIFT_UNAVAILABLE("This API should not have existed in the first place — please do not write new code using it");

@end

#define PSPDFMutableMulticastDelegateType(Protocol) PSPDFMutableMulticastDelegate<id<Protocol>><Protocol>

#define PSPDFCreateMutableMulticastDelegate(Protocol) (PSPDFMutableMulticastDelegateType(Protocol) *)[[PSPDFMutableMulticastDelegate alloc] initWithDelegates:@[] owner:nil protocol:@protocol(Protocol)]

/// Mutable multicast variant. Useful to build API that can add/remove delegates.
PSPDF_SDK_CLASS_SWIFT(MutableMulticastDelegate)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFMutableMulticastDelegate<DelegateType> : PSPDFMulticastDelegate<DelegateType>

/// Adds a new delegate to the subscriber list.
///
/// @note Delegates are weakly retained, but be a good citizen and manually deregister.
- (void)addDelegate:(DelegateType)delegate NS_SWIFT_NAME(add(delegate:));

/// Removes an existing delegate from the subscriber list.
///
/// @return `true`, if the object was removed, `false` otherwise.
- (BOOL)removeDelegate:(DelegateType)delegate NS_SWIFT_NAME(remove(delegate:));
;

@end

NS_ASSUME_NONNULL_END
