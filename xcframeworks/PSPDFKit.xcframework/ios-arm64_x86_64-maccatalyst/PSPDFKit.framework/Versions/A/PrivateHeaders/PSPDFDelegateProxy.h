//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFRuntime.h>
#import <PSPDFKit/PSPDFMacros.h>
#else
#import "PSPDFRuntime.h"
#import "PSPDFMacros.h"
#endif

@class PSPDFDispatchQueue;

NS_ASSUME_NONNULL_BEGIN

/// Add one of the three defines below into your implementation to save the delegate into the delegate proxy.
/// You will also require an internal declaration as follows:
/// PSPDF_DELEGATE_PROXY_PROPERTY(XXXDelegate)
#define PSPDF_DELEGATE_PROXY_CUSTOM_RETURN(protocolName, GETTER, SETTER, returnValue, setterCode, TARGETQUEUE)                                                                                                              \
    -(nullable id<protocolName>)GETTER {                                                                                                                                                                       \
        return ((PSPDFDelegateProxy *)self.GETTER##Proxy).delegate;                                                                                                                                            \
    }                                                                                                                                                                                                          \
    -(void)SETTER : (nullable id<protocolName>)delegate {                                                                                                                                                      \
        self.GETTER##Proxy = (id<protocolName, PSPDFDelegateProxying>)[[PSPDFDelegateProxy alloc] initWithDelegate:delegate conformingToProtocol:@protocol(protocolName) defaultReturnValue:returnValue targetQueue:TARGETQUEUE]; \
        setterCode                                                                                                                                                                                             \
    }                                                                                                                                                                                                          \
    -(nonnull id<protocolName, PSPDFDelegateProxying>)GETTER##Proxy {                                                                                                                                     \
        if (!self.GETTER##ProxyStorage) {                                                                                                                                                                      \
            self.GETTER = nil;                                                                                                                                                                                 \
        }                                                                                                                                                                                                      \
        return (id<protocolName, PSPDFDelegateProxying> _Nonnull)self.GETTER##ProxyStorage;                                                                                                               \
    }                                                                                                                                                                                                          \
    -(void)SETTER##Proxy : (nullable id<protocolName, PSPDFDelegateProxying>)delegateProxy {                                                                                                              \
        self.GETTER##ProxyStorage = delegateProxy;                                                                                                                                                             \
    }

// Useful when your delegate is named differently than `delegate`.
#define PSPDF_DELEGATE_PROXY_CUSTOM(protocolName, GETTER, SETTER) PSPDF_DELEGATE_PROXY_CUSTOM_QUEUE(protocolName, GETTER, SETTER, nil)

// Useful when your delegate is named differently than `delegate` + has a defined queue.
#define PSPDF_DELEGATE_PROXY_CUSTOM_QUEUE(protocolName, GETTER, SETTER, TARGETQUEUE) PSPDF_DELEGATE_PROXY_CUSTOM_RETURN(protocolName, GETTER, SETTER, nil, {}, TARGETQUEUE)

// This is the method you usually want to implement right after your @synthesize.
#define PSPDF_DELEGATE_PROXY(protocolName) PSPDF_DELEGATE_PROXY_CUSTOM(protocolName, delegate, setDelegate)

/// Add one of the two defines below into your private class extension.
#define PSPDF_DELEGATE_PROXY_PROPERTY_CUSTOM(protocolName, delegateName)                                  \
    @property (atomic, nullable) id<protocolName, PSPDFDelegateProxying> delegateName##ProxyStorage; \
    @property (nonatomic, null_resettable) id<protocolName, PSPDFDelegateProxying> delegateName##Proxy;

// Shortcut for the property definition.
#define PSPDF_DELEGATE_PROXY_PROPERTY(protocolName) PSPDF_DELEGATE_PROXY_PROPERTY_CUSTOM(protocolName, delegate)

// TODO(Q): Do these make sense for Swift at all?
PSPDF_PROTOCOL_SWIFT(DelegateProxying)
@protocol PSPDFDelegateProxying

/// Creates a copy of the delegate proxy with the specified `defaultValue`.
///
/// @note Make sure you're not calling this on `nil`. Using the PSPDF_DELEGATE_PROXY macros should already make sure that can't happen.
- (instancetype)copyThatDefaultsTo:(nullable NSObject *)defaultValue;

/// Creates a copy of the delegate proxy with @YES as the `defaultValue`.
- (instancetype)copyThatDefaultsToYES;

/// Creates a copy of the delegate proxy with `NSNotFound` as the `defaultValue`.
- (instancetype)copyThatDefaultsToNSNotFound;

@end

/// Forwards calls to a delegate.
/// Uses modern message forwarding with almost no runtime overhead.
PSPDF_SDK_CLASS_SWIFT(DelegateProxy)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFDelegateProxy : NSProxy<PSPDFDelegateProxying>

/// Designated initializer. `delegate` can be nil.
/// `returnValue` will unbox on method signatures that return a primitive number (e.g. @YES)
/// Method signatures that don't match the unboxed type in `returnValue` will be ignored.
- (instancetype)initWithDelegate:(nullable id)delegate conformingToProtocol:(Protocol *)protocol defaultReturnValue:(nullable NSObject *)returnValue targetQueue:(nullable PSPDFDispatchQueue *)targetQueue;

/// The internal (weak) delegate.
@property (atomic, weak, readonly) id delegate;

/// The property we allow calling to.
@property (atomic, readonly) Protocol *protocol;

/// Allows to set the target queue for delegate calls.
/// Defaults to nil. Type is PSPDFDispatchQueue.
///
/// @note Setting a queue will force the slow path for delegate forwarding.
@property (atomic, nullable, readonly) PSPDFDispatchQueue *targetQueue;

/// The default return value if the method isn't implemented. Defaults to `nil`.
///
/// @see copyThatDefaultsTo:
@property (atomic, readonly, nullable) NSObject *defaultReturnValue;

@end

NS_ASSUME_NONNULL_END
