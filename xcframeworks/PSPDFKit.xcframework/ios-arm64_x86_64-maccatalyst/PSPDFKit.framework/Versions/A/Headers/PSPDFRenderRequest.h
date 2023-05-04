//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFRenderOptions.h>

NS_ASSUME_NONNULL_BEGIN

/// The render request cache policy controls if and how the request, once scheduled,
/// access the cache.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFRenderRequestCachePolicy) {
    /// The default policy that works best for the given platform and device.
    PSPDFRenderRequestCachePolicyDefault = 0,

    /// The request will always trigger a rendering as it ignores data from the cache.
    PSPDFRenderRequestCachePolicyReloadIgnoringCacheData,

    /// The request will first check the cache for data and request a rendering if there was no cache hit for that request.
    PSPDFRenderRequestCachePolicyReturnCacheDataElseLoad,

    /// The request will check the cache for data and return nothing if the cache did not contain an image.
    PSPDFRenderRequestCachePolicyReturnCacheDataDontLoad,
} PSPDF_ENUM_SWIFT(RenderRequest.CachePolicy);

@class PSPDFDocument, PSPDFAnnotation;

/// A render request specifies the exact parameters of how an image should be rendered.
/// You use it in order to configure a `PSPDFRenderTask` which can then be passed
/// to a `PSPDFRenderQueue` in order to fulfill the task.
///
/// To create a new render request you usually create a `PSPDFMutableRenderRequest`
/// and set the properties you need.
///
/// # Thread safety
///
/// PSPDFRenderRequest is not thread safe, you should never modify a mutable render
/// request from multiple threads nor should you modify a mutable render request while
/// reading data from it on a different thread.
///
/// As soon as you hand over ownership of a render request to the render engine, it
/// is copied, so that you do not need to worry about thread safety between your render
/// requests and the ones the render engine holds.
///
/// @see PSPDFRenderTask
/// @see PSPDFMutableRenderRequest
PSPDF_CLASS_SWIFT(RenderRequest)
@interface PSPDFRenderRequest : NSObject<NSCopying, NSMutableCopying>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new render request for rendering images of pages from the passed
/// in document.
///
/// @param document The document this request should render images from.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// The document that this object is requesting an image rendering from.
@property (nonatomic, readonly) PSPDFDocument *document;

/// The index of the page that should be rendered from the document.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

/// The requested size of the rendered image.
///
/// @note The actual image might be of a different size as the rendered image will
/// have the aspect ratio of `pdfRect` or the full pdf page, in case you don't
/// specify a `pdfRect`. The resulting image will be rendered aspect-fit inside
/// the requested `imageSize`, meaning in the resulting image at least one axis
/// will be equal to the requested one and the other might be smaller.
@property (nonatomic, readonly) CGSize imageSize;

/// The rectangle in PDF coordinates defining the area of the page that should be rendered.
///
/// The rectangle that is described here is rendered into the given `renderSize`.
///
/// Defaults to `CGRectNull`, which means the full page is rendered.
@property (nonatomic, readonly) CGRect pdfRect;

/// The scale factor the image should be rendered in.
///
/// Defaults to 0.0 which will use the main screen's scale factor on iOS and on macOS
/// will always use 1.0.
@property (nonatomic, readonly) CGFloat imageScale;

/// Contains the annotations to be rendered in the image.
///
/// If this property contains an empty array, no annotations will be rendered in the
/// image. If this property is nil, all annotations will be rendered in the image
/// (the default).
@property (nonatomic, copy, readonly, nullable) NSArray<__kindof PSPDFAnnotation *> *annotations;

/// Contains additional render options that should be used when rendering the image.
///
/// @note The image will rendered by combining those options with the render options from the
/// source document. Querying this property will not reflect the document options.
@property (nonatomic, copy, readonly) PSPDFRenderOptions *options;

/// The user info dictionary can contain any arbitrary user info that is just passed
/// through. Content in this dictionary is not touched at all and has no impact on
/// the render result.
///
/// @note Two render requests with different user info content can still be equal.
@property (nonatomic, copy, readonly) NSDictionary *userInfo;

/// Determines the cache policy that is used to fulfill the request. If the policy
/// is set to `PSPDFRenderRequestCachePolicyDefault` (the default value) the request
/// will try to fulfill the request as efficient as possible.
@property (nonatomic, readonly) PSPDFRenderRequestCachePolicy cachePolicy;

/// Compares the receiver and the passed in render request for equality.
///
/// @param renderRequest The request to compare the receiver to.
///
/// @return `true` if both requests are equal, `false` otherwise.
- (BOOL)isEqualRenderRequest:(PSPDFRenderRequest *)renderRequest;

@end

/// The mutual version of a render request can be used to configure it so that it
/// matches the desired request.
PSPDF_CLASS_SWIFT(MutableRenderRequest)
@interface PSPDFMutableRenderRequest : PSPDFRenderRequest

/// The index of the page that should be rendered from the document.
///
/// This defaults to the first page.
@property (nonatomic) PSPDFPageIndex pageIndex;

/// The requested size of the rendered image.
///
/// @note The actual image might be of a different size as the rendered image will
/// have the aspect ratio of `pdfRect` or the full pdf page, in case you don't
/// specify a `pdfRect`. The resulting image will be rendered aspect-fit inside
/// the requested `imageSize`, meaning in the resulting image at least one axis
/// will be equal to the requested one and the other might be smaller.
@property (nonatomic) CGSize imageSize;

/// The rectangle in PDF coordinates defining the area of the page that should be rendered.
///
/// The rectangle that is described here is rendered as aspect fit into the given `renderSize`.
///
/// Defaults to `CGRectNull`, which means the full page is rendered.
@property (nonatomic) CGRect pdfRect;

/// The scale factor the image should be rendered in.
///
/// Defaults to 0.0 which will use the main screen's scale factor on iOS and on macOS
/// will always use 1.0.
@property (nonatomic) CGFloat imageScale;

/// Contains the annotations to be rendered in the image.
///
/// If this property contains an empty array, no annotations will be rendered in the
/// image. If this property is nil, all annotations will be rendered in the image
/// (the default).
@property (nonatomic, copy, nullable) NSArray<__kindof PSPDFAnnotation *> *annotations;

/// Contains additional render options that should be used when rendering the image.
///
/// @note The image will rendered by combining those options with the render options from the
/// source document. Querying this property will not reflect the document options.
@property (nonatomic, copy) PSPDFRenderOptions *options;

/// Determines the cache policy that is used to fulfill the request. If the policy
/// is set to `PSPDFRenderRequestCachePolicyDefault` (the default value) the request
/// will try to fulfill the request as efficient as possible.
@property (nonatomic) PSPDFRenderRequestCachePolicy cachePolicy;

/// The user info dictionary can contain any arbitrary user info that is just passed
/// through. Content in this dictionary is not touched at all and has no impact on
/// the render result.
///
/// @note Two render requests with different user info content can still be equal.
@property (nonatomic, copy) NSDictionary *userInfo;

@end

NS_ASSUME_NONNULL_END
