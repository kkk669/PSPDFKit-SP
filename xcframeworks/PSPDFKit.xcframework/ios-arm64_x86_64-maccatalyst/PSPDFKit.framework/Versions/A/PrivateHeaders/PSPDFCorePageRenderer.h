//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAnnotation, PSPDFContextPostProcessor, PSPDFDocumentProvider, PSPDFRenderOptions;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFCorePageRenderer : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Whether to prevent core from creating copies of the document to reduce lock contention during concurrent renders.
///
/// Defaults to `false`.
///
/// @note This is ignored when the global `LowMemoryMode` is set. In that case multi document rendering is always disabled.
@property (nonatomic) BOOL preventMultiDocumentRendering;

/// An object that post processes the contents of a CGContextRef according to the CIFilters corresponding to an instance of
/// `PSPDFRenderOptions`. This same instance should be reused wherever possible.
@property (nonatomic, readonly) PSPDFContextPostProcessor *postProcessor;

/// Sends a request to the underlying core page renderer to cancel the rendering
/// operation in the next available checkpoint.
///
/// @param cancellationToken   The token that was used to start the rendering.
/// @param documentProvider    The document provider that serves the current rendering operation.
/// @param pageIndex           The index of the page that's being rendered.
///
/// @return `true` if the underlying renderer accepted the cancellation request. `false` if there was no rendering operation associated with the provided cancellation token active.
///
/// @note When this method returns `true`, it does not mean that the rendering operation *was* cancelled, but that it will eventually be cancelled. Cancellation call requires a core lock and might be slow; advisable to call on a background thread.
- (BOOL)cancelWithToken:(int)cancellationToken documentProvider:(PSPDFDocumentProvider *)documentProvider pageIndex:(PSPDFPageIndex)pageIndex;

/// Renders the current page index into a context.
- (BOOL)drawPageAtIndex:(PSPDFPageIndex)pageIndex ofDocumentProvider:(PSPDFDocumentProvider *)documentProvider inContext:(CGContextRef)context withOptions:(PSPDFRenderOptions *)options cancellationToken:(nullable NSNumber *)cancellationToken error:(NSError **)error;

/// Renders annotation appearance streams.
///
/// @return NO if rendering failed.
- (BOOL)renderAppearanceStream:(PSPDFAnnotation *)annotation inContext:(CGContextRef)context withOptions:(nullable PSPDFRenderOptions *)options error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
