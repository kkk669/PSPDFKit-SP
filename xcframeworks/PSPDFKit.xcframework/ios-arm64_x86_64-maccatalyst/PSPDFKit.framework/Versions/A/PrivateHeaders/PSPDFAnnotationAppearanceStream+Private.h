//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationAppearanceStream.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAnnotationAppearanceStream ()

/// Initializer for creating an appearance stream with either an image, a image URL or a data blob.
/// Make sure to only set one of the three possible parameters.
/// Will be called from the factory methods.
- (instancetype)initWithImage:(nullable UIImage *)image orImageURL:(nullable NSURL *)url orData:(nullable NSData *)data;

/// Factory method for creating an annotation appearance stream object with a data blob.
/// `data` must be a PDF format (e.g. an annotation's appearance stream).
+ (instancetype)appearanceStreamWithData:(NSData *)data;

/// The data object, containing the graphics appearance stream.
@property (nonatomic, readonly, nullable) NSData *data;

@end

NS_ASSUME_NONNULL_END

