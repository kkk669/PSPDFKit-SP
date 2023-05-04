//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// The `PSPDFImageFile` class can be used to load images with memory consumption in mind.
/// It decouples the actual `UIImage` from its file representation, allowing you to release most of
/// the memory while making it easy to reload the image data if necessary.
@interface PSPDFImageFile : NSObject <NSDiscardableContent>

// MARK: Creating an Image File

/// Creates a new image file with a given path.
+ (nullable instancetype)imageFileWithData:(NSData *)data;

/// Creates a new image file with a given path.
- (nullable instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

// MARK: Attributes

/// The underlying image. Only valid if `isContentDiscarded` is `false`.
///
/// @warning Throws an exception if `isContentDiscarded` is `false`.
@property (nonatomic, readonly, nullable) UIImage *image;

/// The size of the image. Always valid.
@property (nonatomic, readonly) CGSize imageSize;

@end

NS_ASSUME_NONNULL_END
