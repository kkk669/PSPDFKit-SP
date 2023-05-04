//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFHostingAnnotationView.h>
#import <PSPDFKitUI/PSPDFAnnotationViewRendering.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFHostingAnnotationView () <PSPDFAnnotationViewRendering>

/// If set to YES, the view will wait for calls to `enableAnnotationRendering` and `attachImage` from the `PDFPageView` until it shows content.
/// This prevents flickering, especially for transparent content. Defaults to YES.
@property (nonatomic) BOOL shouldSyncRemovalFromSuperview;

/// Frame of the annotation in PDF coordinate space.
@property (nonatomic, readonly) CGRect clipRect;

/// Additional options for annotation rendering.
@property (nonatomic, copy, nullable) PSPDFRenderOptions *additionalAnnotationRenderingOptions;

/**
 Clears the existing image, forcing a re-render the next time it is accessed.

 Because the correct display of the annotation depends on the render options, we have to clear the
 cached image at certain times. When this happens can depend on details only known in subclasses.
 */
- (void)clearExistingImage;

- (void)updateImageViewInSync:(BOOL)inSync animated:(BOOL)animated;

/// Update image content mode.
- (void)updateImageContentModeAndMask;

/// Use this to customize the annotation before rendering.
@property (nonatomic, readonly, nullable) PSPDFAnnotation *renderedAnnotation;

/// Forces all image rendering operations to be synchronous.
/// Defaults to `true`.
@property (nonatomic) BOOL forceSyncRendering;

@end

NS_ASSUME_NONNULL_END
