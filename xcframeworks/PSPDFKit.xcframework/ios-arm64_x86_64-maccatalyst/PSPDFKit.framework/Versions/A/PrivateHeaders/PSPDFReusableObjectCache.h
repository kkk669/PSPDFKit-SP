//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFReusable <NSObject>

/// The reuse identifier for this object.
///
/// @note You should not change this value yourself at any time. During initialization,
/// make sure the `reuseIdentifier` is set to what the initializer receives.
/// After that, this value should not change anymore.
@property (nonatomic, copy, readonly) NSString *reuseIdentifier;

/// The method is called when an object is enqueued to be reused later. It can be used
/// to prepare an object to be enqueued.
- (void)prepareForEnqueueing;

/// The method is called before an object is dequeued. It can be used to prepare the
/// object to be used again soon.
- (void)prepareForDequeueing;

@end

/// This class provides a generic implementation for reusable objects, similar to what
/// `UICollectionView` and `UITableView` do with their cells.
///
/// To be as generic as possible, instead of requiring a given initializer you can
/// instead register blocks that initialize new objects when the are needed. The cache
/// will just check that the `reuseIdentifier` is set properly during initialization.
///
/// # Threading
///
/// `PSPDFReusableObjectCache` is not thread safe. You should not call any methods
/// on it concurrently. It is, however, okay to call methods from multiple threads,
/// as long as this doesn't happen at the same time. So e.g. wrapping calls to this
/// class in a serial dispatch queue is fine.
PSPDF_SDK_CLASS_SWIFT(ReusableObjectCache)
@interface PSPDFReusableObjectCache<__covariant ObjectType> : NSObject

/// Registers an initializer that can then later be used to create objects for a given
/// identifier if there are no reusable objects available for that identifier.
///
/// @param initializer The block to be executed to initialize an object for the given reuseIdentifier.
/// @param reuseIdentifier The reuse identifier for the initializer.
- (void)registerInitializer:(ObjectType<PSPDFReusable>(^)(NSString *reuseIdentifier))initializer forReuseIdentifier:(NSString *)reuseIdentifier;

/// Dequeues an object for the given reuse identifier or creates a new instance if
/// no object is available for dequeuing.
///
/// @note Dequeuing an object transfers ownership from the receiver to the caller.
/// The cache will no longer hold on to or touch the returned object in any way.
///
/// @param reuseIdentifier The reuse identifier identifying an object to dequeue.
/// @return A dequeued or newly initialized object.
- (ObjectType)dequeueObjectForReuseIdentifier:(NSString *)reuseIdentifier;

/// Enqueues an object.
///
/// The object needs to have a proper reuse identifier set.
///
/// @note This method transfers ownership from the caller to the receiver. It is very
/// important that you no longer hold on to or modify the passed in object after
/// enqueuing it. The cache might hand this object back to a different owner.
///
/// @param object The object to be enqueued.
- (void)enqueueObject:(ObjectType<PSPDFReusable>)object;

@end

NS_ASSUME_NONNULL_END
