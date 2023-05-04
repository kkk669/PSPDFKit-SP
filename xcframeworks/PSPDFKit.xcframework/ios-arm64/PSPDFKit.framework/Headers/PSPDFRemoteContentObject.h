//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^PSPDFRemoteContentObjectAuthenticationBlock)(NSURLAuthenticationChallenge *, void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential));
typedef _Nullable id (^PSPDFRemoteContentObjectTransformerBlock)(NSURL *location);

/// Contains information about remote content.
PSPDF_PROTOCOL_SWIFT(RemoteContentObject)
@protocol PSPDFRemoteContentObject<NSObject>

/// The URL request used for loading the remote content.
@property (nonatomic, readonly, nullable) NSURLRequest *URLRequestForRemoteContent;

/// The remote content of the object. This property is managed by `PSPDFDownloadManager`.
@property (nonatomic, nullable) id remoteContent;

@optional

/// The loading state of the object. This property is managed by `PSPDFDownloadManager`.
@property (nonatomic, getter=isLoadingRemoteContent) BOOL loadingRemoteContent;

/// The download progress of the object. Only meaningful if `loadingRemoteContent` is YES.
/// This property is managed by `PSPDFDownloadManager`.
@property (nonatomic) CGFloat remoteContentProgress;

/// The remote content error of the object. This property is managed by `PSPDFDownloadManager`.
@property (nonatomic, nullable) NSError *remoteContentError;

/// Return YES if you want `PSPDFDownloadManager` to cache the remote content. Defaults to NO.
@property (nonatomic, readonly) BOOL shouldCacheRemoteContent;

/// Return YES if you want `PSPDFDownloadManager` to retry downloading remote content if a connection
/// error occurred. Defaults to NO.
@property (nonatomic, readonly) BOOL shouldRetryLoadingRemoteContentOnConnectionFailure;

/// Return a block if you need to handle a authentication challenge.
@property (nonatomic, readonly) PSPDFRemoteContentObjectAuthenticationBlock remoteContentAuthenticationChallengeBlock;

/// Return a custom `PSPDFRemoteContentObjectTransformerBlock`. The passed-in `URL` points to the
/// file that stores the downloaded data. The return value is set to `remoteContent`. If no transformer
/// block is provided, `remoteContent` will be set to data (represented by `Data`) of the downloaded
/// content.
///
/// @note If `shouldCacheRemoteContent` returns `true` the location of the file is not temporary.
/// @note `remoteContentTransformerBlock` will be called on a background queue, so you may perform
/// long-running tasks.
/// @warning Since this runs on a background queue, you should not access state outside of the block's
/// scope to avoid thread-safety problems.
@property (nonatomic, readonly, nullable) PSPDFRemoteContentObjectTransformerBlock remoteContentTransformerBlock;

/// Return `true` if the object actually has remote content. Since most `PSPDFRemoteContentObject`s
/// will have remote content, this method is optional. If it is not implemented, `true` will be assumed.
@property (nonatomic, readonly) BOOL hasRemoteContent;

/// The completion block, called after loading finished.
@property (nonatomic, copy, nullable) void (^completionBlock)(id<PSPDFRemoteContentObject> remoteObject);

@end

NS_ASSUME_NONNULL_END
