//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFRenderManager.h>
#import <PSPDFKit/PSPDFRenderRequest.h>
#import <PSPDFKit/PSPDFRenderOptions.h>

@class PSPDFCorePageRenderer;

NS_ASSUME_NONNULL_BEGIN

/// The key of a `PSPDFRenderManagerRenderResultDidChangeNotification` userInfo's dictionary,
/// containing an NSArray with annotations that triggered the render result changes.
///
/// Will be `nil`, if annotations did not tigger the change.
PSPDF_EXPORT NSString *const PSPDFRenderManagerRenderResultChangedAnnotationsKey;

@protocol PSPDFRenderManagerPrivate <PSPDFRenderManager>

/// Renders a page inside a rectangle. Set context CTM and clipRect to control rendering.
/// Returns the renderingRectangle.
/// `options` contains render keys.
///
/// @note `pageInfo` is required.
- (BOOL)renderPageAtIndex:(PSPDFPageIndex)pageIndex documentProvider:(PSPDFDocumentProvider *)documentProvider inContext:(CGContextRef)context rectangle:(CGRect)rectangle pageInfo:(PSPDFPageInfo *)pageInfo annotations:(nullable NSArray<__kindof PSPDFAnnotation *> *)annotations options:(PSPDFRenderOptions *)options cancellationToken:(nullable NSNumber *)cancellationToken error:(NSError **)error;

/// Renders a page; defined by point and zoom. Use `zoom=100` and `point = CGPointZero` for defaults.
/// `options` contains render keys.
- (BOOL)renderPageAtIndex:(PSPDFPageIndex)pageIndex documentProvider:(PSPDFDocumentProvider *)documentProvider inContext:(CGContextRef)context atPoint:(CGPoint)point withZoom:(CGFloat)zoom pageInfo:(PSPDFPageInfo *)pageInfo annotations:(nullable NSArray<__kindof PSPDFAnnotation *> *)annotations options:(PSPDFRenderOptions *)options cancellationToken:(nullable NSNumber *)cancellationToken error:(NSError **)error;

/// This method posts a `PSPDFRenderManagerRenderResultDidChangeNotification` with
/// all the pages from the annotations in the passed in array.
///
/// @param annotations The annotations that changed to check for their pages.
- (void)notifyAboutRenderResultChangedWithAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

@end

@interface UIColor (PSPDFRenderManager)

/// Parses the render option and returns an adapted color (inverted/color correct inverted)
- (UIColor *)pspdf_colorFromRenderOptions:(nullable PSPDFRenderOptions *)renderOptions;

@end

NS_ASSUME_NONNULL_END
