//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// Used to customize the image quality options offered for adding images.
typedef NS_OPTIONS(NSUInteger, PSPDFImageQuality) {
    /// Allow low image qualities. In the range of 800 × 600 pixels.
    PSPDFImageQualityLow = 1 << 0,
    /// Allow medium image qualities. In the range of 1600 × 1200 pixels.
    PSPDFImageQualityMedium = 1 << 1,
    /// Allow higher image qualities. In the range of 3200 × 2400 pixels.
    PSPDFImageQualityHigher = 1 << 3,
    /// Allow the original size of the image, up to a resolution of 5000 x 5000 pixels.
    PSPDFImageQualityBest = 1 << 2,
    /// Allow all image qualities.
    PSPDFImageQualityAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(ImagePickerController.ImageQuality);

@class PSPDFImagePickerController;

/// Delegate informing about image selection and editing in `PSPDFImagePickerController`.
PSPDF_PROTOCOL_SWIFT(ImagePickerControllerDelegate)
@protocol PSPDFImagePickerControllerDelegate<NSObject>

@optional

/// Called when the image picker selected an image from the photo library or when an image from the camera has been taken.
/// Dimensions of the image are derived from the original image, without modifications.
- (void)imagePickerController:(PSPDFImagePickerController *)picker didSelectImage:(UIImage *)image;

/// Called when the image picker did finish selecting an image or, if `shouldShowImageEditor` enabled, when the image editor finished.
/// Dimensions of the image are derived from the original image, without modifications, if `shouldShowImageEditor` is disabled
/// The cropped image dimensions from the image editor are used, if `shouldShowImageEditor` is enabled.
/// Images may be post processed to use a smaller size, depending on `allowedImageQualities`.
///
/// @param info The image info of the original image, selecting from the image picker.
- (void)imagePickerController:(PSPDFImagePickerController *)picker didFinishWithImage:(UIImage *)image andInfo:(NSDictionary<NSString *, id> *)info;

/// Called when the image picker or the image editor cancelled without selecting an image.
///
/// @note If you implement this method, you are responsible for dismissing the image picker. Otherwise it will be dismissed automatically.
- (void)imagePickerControllerCancelled:(PSPDFImagePickerController *)picker;

@end

/// Subclass of `UIImagePickerController` used in PSPDFKit when showing the image picker, like when adding an image annotation or when adding a new page to a document from an image.
///
/// Allows subclassing the image picker controller, for example if you need to block portrait:
/// https://stackoverflow.com/questions/11467361/taking-a-photo-in-an-ios-landscape-only-app
///
/// Shows a custom image editor after an image has been selected if `shouldShowImageEditor` is enabled.
///
/// When used in an app extension, a scaled down version of the image is used to avoid exceeding the
/// 120 MB limit of app extensions.
///
/// @note
/// `delegate` is set to `self`. Don't change this, as this will restrict presenting the image editor.
/// `imageDelegate` will be set when the picker is called from within PSPDFKit logic.
/// You can override the delegate as long as you correctly forward calls to the original target.
PSPDF_CLASS_SWIFT(ImagePickerController)
@interface PSPDFImagePickerController : UIImagePickerController<PSPDFOverridable>

/// Set this, to be informed about the selected and, if `shouldShowImageEditor` is enabled, the edited image.
/// Ensure to relay calls to the existing delegate, if one is set.
@property (nonatomic, weak) id<PSPDFImagePickerControllerDelegate> imageDelegate;

/// Controls showing the image editor after image selection. Defaults to `true`.
@property (nonatomic) BOOL shouldShowImageEditor;

/// The offered image qualities.
///
/// Defaults to `PSPDFImageQualityAll`.
///
/// If there is only one option set or the image is not large enough to offer scaling,
/// no quality sheet will be displayed. You can use `PSPDFImageQualityBest`, to disable
/// the picker and automatically select the best possible image quality.
@property (nonatomic) PSPDFImageQuality allowedImageQualities;

- (void)setDelegate:(nullable id <UINavigationControllerDelegate, UIImagePickerControllerDelegate>)delegate PSPDF_UNAVAILABLE("Do not set the delegate, the object requires the delegate to be set to self");

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFImagePickerController (SubclassingHooks)

/// The available image picker source types.
///
/// Then return value should only contain boxed values of `UIImagePickerControllerSourceType`, valid options are `UIImagePickerControllerSourceTypePhotoLibrary` and `UIImagePickerControllerSourceTypeCamera`.
/// Defaults to `@[@(UIImagePickerControllerSourceTypePhotoLibrary), @(UIImagePickerControllerSourceTypeCamera)]`.
///
/// @note To allow the user to take a photo with the camera, make sure you add `NSCameraUsageDescription` to your `Info.plist`.
/// See https://pspdfkit.com/guides/ios/getting-started/permissions/#image-permissions for further documentation.
+ (NSArray<NSNumber *> *)availableImagePickerSourceTypes;

@end

NS_ASSUME_NONNULL_END
