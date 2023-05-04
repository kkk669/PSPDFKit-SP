//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKitUI/PSPDFImageCropView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFImageEditViewController;

@protocol PSPDFImageEditViewControllerDelegate <NSObject>

- (void)imageEditViewController:(PSPDFImageEditViewController *)imageEditViewController didFinishWithImage:(nullable UIImage *)image;

@end

/// An image editor allowing you to crop/zoom/pinch an image to a resizable crop rect.
@interface PSPDFImageEditViewController : UIViewController

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// Initialize the view controller with the image to be transformed.
- (instancetype)initWithImage:(UIImage *)image NS_DESIGNATED_INITIALIZER;

/// Image to be transformed. Set in `initWithImage:`.
@property (nonatomic, readonly) UIImage *image;

/// The minimum scale the image can be zoomed to. Not set by default.
@property (nonatomic) CGFloat minimumScale;

/// The maximum scale the image can be zoomed to. Not set by default.
@property (nonatomic) CGFloat maximumScale;

/// If enabled, checks if the image is inside the crop rect after a transform or resize happened and snaps back to a valid crop rect/transform.
@property (nonatomic) BOOL checkBounds;

/// The done button item to finish the image editing.
@property (nonatomic) UIBarButtonItem *doneButton;

/// Enables/disables the pinch gesture recognizer.
@property (nonatomic) BOOL pinchingEnabled;

/// Enables/disables the rotation gesture recognizer.
@property (nonatomic) BOOL rotatingEnabled;

/// Enables/disables the pan gesture recognizer.
@property (nonatomic) BOOL panningEnabled;

/// Sets a maximum size the crop rect can size to. Will snap back to this size if the crop rect exceeds.
@property (nonatomic) CGSize maxCropRectSize;

/// Delegate for the finished image transform callback.
@property (nonatomic, weak) id<PSPDFImageEditViewControllerDelegate> delegate;

// MARK: - Used for tests (PSPDFImageEditViewControllerTests)

/// Image view which hosts the image. All image transforms are applied to this imageView.
@property (nonatomic, nullable) UIImageView *imageView;

/// Crop view which manages the cropping rectangle.
@property (nonatomic, nullable) PSPDFImageCropView *cropView;

/// Returns the cropped, rotated, and/or scaled image.
- (UIImage *)transformedImage;

@end

NS_ASSUME_NONNULL_END
