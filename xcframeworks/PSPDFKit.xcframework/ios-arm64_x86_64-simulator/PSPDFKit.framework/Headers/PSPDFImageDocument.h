//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

/// Specifies how a `PSPDFImageDocument` should save its contents.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFImageSaveMode) {
    /// The changes made to a `PSPDFImageDocument` will be flattened into the original image, and no
    /// additional metadata will be added to the image to allow these changes to be editable when reopened with
    /// `PSPDFImageDocument`.
    /// This option will not significantly change the file size.
    PSPDFImageSaveModeFlatten = 0,
    /// In addition to flattening all the changes to the original image, `PSPDFImageDocument` will store the original
    /// image along with the edits made as part of the image's metadata, allowing for previous changes like annotations
    /// to remain editable when reopened.
    /// Using this option will more than double the file size, and will increase as more edits are made.
    PSPDFImageSaveModeFlattenAndEmbed = 1,
} PSPDF_ENUM_SWIFT(ImageDocument.SaveMode);

/// A `Document` subclass that can be used to display and annotate
/// image files. Can handle JPEG, PNG and TIFF images.
///
/// @note Any transparency on PNG images will be lost after saving.
///
/// Saving changes flattens any annotations into the image and writes
/// it back to the original file. Creating a new document will then
/// reflect the new image with flattened changes. Keep the image document
/// in memory to preserve the ability to edit added annotations.
///
/// See https://pspdfkit.com/guides/ios/annotations/annotate-images/ for more information.
///
/// @note `PSPDFImageDocument` requires the Image Documents feature to be enabled for your license to work.
PSPDF_CLASS_SWIFT(ImageDocument)
@interface PSPDFImageDocument : PSPDFDocument

/// Creates a new image document using `PSPDFImageSaveModeFlattenAndEmbed`.
///
/// @param imageDataProvider A data provider that supplies the image content.
/// @return A new image document instance.
///
/// @note This method requires the Image Documents feature to be enabled for your license.
- (instancetype)initWithImageDataProvider:(id<PSPDFDataProviding>)imageDataProvider;

/// Creates a new image document using `PSPDFImageSaveModeFlattenAndEmbed`.
///
/// @param imageURL A file URL of the image.
/// @return A new image document instance.
///
/// @note This method requires the Image Documents feature to be enabled for your license.
- (instancetype)initWithImageURL:(NSURL *)imageURL;

/// The data provider that the image document was initialized with.
@property (nullable, nonatomic, readonly) id<PSPDFDataProviding> imageDataProvider;

/// The image file URL, if the image document was initialized via `initWithImageURL:` or with a file data provider.
@property (nullable, nonatomic, readonly) NSURL *imageURL;

/// The image is loaded and converted to PDF asynchronously. Use this call to wait until the process is complete.
///
/// @note This will block the current thread.
- (void)waitUntilLoaded;

/// Specifies what is written back to the original image URL when the receiver is saved.
/// If this property is `PSPDFImageSaveModeFlattenAndEmbed`, then this allows for changes made to the image to be saved
/// as metadata in the original file. If the same file is reopened with `PSPDFImageDocument`, all previous changes made will remain editable.
/// This will increase the amount of space the image takes on disk.
///
/// If this property is `PSPDFImageSaveModeFlatten`, the changes are simply written to the image, and will not be editable when reopened with `PSPDFImageDocument`.
///
/// @note For changes to this property to be effective, they must be made prior to calling `-[PSPDFImageDocument save:]`.
@property (atomic) PSPDFImageSaveMode imageSaveMode;

/// The compression quality for writing JPEG images.
///
/// Bound to a value between 0.0 (most compression) and 1.0 (least compression).
/// Defaults to 1.0 - best image quality and largest image size.
///
/// @note We recommend using a large `compressionQuality` value to prevent
/// quality degradation during subsequent editing sessions.
@property (nonatomic) CGFloat compressionQuality;

/// A set containing UTI types supported by the image document class.
@property (nonatomic, class, readonly) NSSet<UTType *> *supportedContentTypes;

@end

@interface PSPDFImageDocument (Unavailable)

- (instancetype)init PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;
- (instancetype)initWithURL:(NSURL *)url PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;
- (instancetype)initWithDataProviders:(NSArray<id<PSPDFDataProviding>> *)dataProviders loadCheckpointIfAvailable:(BOOL)loadCheckpoint PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;
- (instancetype)initWithDataProviders:(NSArray<id<PSPDFDataProviding>> *)dataProviders PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
