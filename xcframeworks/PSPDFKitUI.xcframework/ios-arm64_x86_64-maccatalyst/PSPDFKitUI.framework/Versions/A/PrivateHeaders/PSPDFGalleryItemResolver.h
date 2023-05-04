//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFGalleryItem.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^PSPDFGalleryItemResolverCompletionBlock)(NSArray<PSPDFGalleryItem *> *_Nullable resolvedItems, NSError *_Nullable error);

/// `PSPDFGalleryItemResolver` takes multiple items and attempts to resolve all unknown items, that
/// is all items of type `PSPDFGalleryUnknownItem`.
PSPDF_TEST_CLASS_SWIFT(GalleryItemResolver)
@interface PSPDFGalleryItemResolver : NSObject

/// Starts resolving all items of type `PSPDFGalleryUnknownItem`.
///
/// @warning `completionBlock` might be called on a background thread.
- (void)resolveItems:(NSArray<PSPDFGalleryItem *> *)items completionBlock:(PSPDFGalleryItemResolverCompletionBlock)completionBlock;

/// Cancels an ongoing resolve.
///
/// @note Calling `cancel` will call the `completionBlock`s of all ongoing resolve operations with a
/// set error argument.
- (void)cancel;

/// Internally used timeout. Defaults to 10 seconds.
///
/// @note This will not reflect operations already running or enqueued.
@property (nonatomic) NSTimeInterval timeoutIntervalForRequest;

@end

NS_ASSUME_NONNULL_END
