//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFImageDocument.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFImageDocument ()

/// A file name, either taken from `imageURL` or inferred from image's encoding.
/// Returns `nil` if file extension can't be inferred.
@property (nullable, nonatomic, readonly) NSString *imageFileNameWithExtension;

/// Render the image document in its current state to the specified data provider using the passed in configuration.
///
/// @param dataProvider The dataProvider to which a copy of the image in its current state is to be written.
/// @param imageSaveMode The save mode with which the copy is to be created.
/// @param compressionQuality The compression quality for writing JPEG images. Bound to a value between 0.0 (most compression) and 1.0 (least compression).
/// @param error A pointer to an `NSError` that will be set in case the save fails.
///
/// @return `true` if the save succeeded, else `false`.
///
/// @note This method does not save the `Document` itself. It is, however, useful to make a copy of the image.
- (BOOL)renderImageToDataProvider:(id<PSPDFDataProviding>)dataProvider saveMode:(PSPDFImageSaveMode)imageSaveMode compressionQuality:(CGFloat)compressionQuality error:(NSError **)error;

/// Render the image in its current state using the passed in configuration.
///
/// @param imageSaveMode The save mode with which the copy is to be created.
/// @param compressionQuality The compression quality for writing JPEG images. Bound to a value between 0.0 (most compression) and 1.0 (least compression).
/// @param error A pointer to an `NSError` that will be set in case the save fails.
///
/// @return Rendered image if the save succeeded, else `nil`.
///
/// @note This method does not save the `Document` itself. It is, however, useful to make a copy of the image.
- (nullable UIImage *)renderImageWithSaveMode:(PSPDFImageSaveMode)imageSaveMode compressionQuality:(CGFloat)compressionQuality error:(NSError **)error;

/// This loads the image header only to return the image size.
/// This method doesn't load the whole image into memory and thus is fast.
///
/// Returns CGSizeZero in case of an error.
- (CGSize)sizeOfImageWithoutLoadingFile;

@end

NS_ASSUME_NONNULL_END
