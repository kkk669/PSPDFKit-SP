//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

/// A `PSPDFAnnotationAppearanceStream` manages an image to include as part of an annotation appearance (ie. a handwritten signature).
/// Supported filetypes are .JPG and .PDF. For PDF files, the first page of the document is used.
PSPDF_CLASS_SWIFT(Annotation.AppearanceStream)
@interface PSPDFAnnotationAppearanceStream : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

+ (instancetype)appearanceStreamWithImage:(UIImage *)image;
+ (instancetype)appearanceStreamWithFileURL:(NSURL *)imageFileURL;

/// The image that will be added to the annotation appearance stream.
@property (nonatomic, readonly, nullable) UIImage *image;

/// The URL of the asset that will be added to the annotation appearance stream. JPG or PDF files are supported.
@property (nonatomic, readonly, nullable) NSURL *imageFileURL;

@end

NS_ASSUME_NONNULL_END
