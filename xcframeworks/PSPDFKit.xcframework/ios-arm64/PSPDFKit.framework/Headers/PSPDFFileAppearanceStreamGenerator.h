//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFAppearanceStreamGenerating.h>

NS_ASSUME_NONNULL_BEGIN

/// An appearance stream generator that takes an `URL` to any PDF file and returns it as the appearance stream.
///
/// Custom appearance streams are only intended to be used with stamp annotations to create a vector stamp.
/// Using this class with other annotation types is not supported.
PSPDF_CLASS_SWIFT(FileAppearanceStreamGenerator)
@interface PSPDFFileAppearanceStreamGenerator : NSObject<PSPDFAppearanceStreamGenerating>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the `PSPDFFileAppearanceStreamGenerator` with the given file URL.
- (instancetype)initWithFileURL:(NSURL *)fileURL NS_DESIGNATED_INITIALIZER;

/// The file URL that will be used to generate the appearance stream from.
@property (nonatomic, readonly) NSURL* fileURL;

/// If set, gets called with a `CGContextRef` instance that can be used to customize how the annotation gets drawn in the document.
/// This may be used to create a vector stamps by drawing in code.
///
/// The context will be set up with the y-axis increasing upwards. It may be easiest to use Core Graphics and Core Text
/// because using the UIKit drawing API will result in flipped images unless you flip the coordinate space.
///
/// Drawing will be aligned with the stamp annotation rotation.
/// This means the annotation boundingBox is not appropriate to use if the annotation rotation is not zero.
/// For now, our recommendation is to ensure the annotation is not rotated when the appearance stream is generated.
@property (nonatomic, copy, nullable) void (^drawingBlock)(CGContextRef context);

@end

NS_ASSUME_NONNULL_END
