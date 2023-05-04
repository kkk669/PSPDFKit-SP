//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationCreator.h>
#import <PSPDFKitUI/PSPDFImagePickerController.h>

@class PSPDFButtonFormElement;

NS_ASSUME_NONNULL_BEGIN

/// Handles state and actions required while we are in an image annotation creation flow.
@interface PSPDFImageAnnotationCreator : PSPDFAnnotationCreator <PSPDFImagePickerControllerDelegate>

/// If image creation is triggered via JavaScript's importingIcon() function,
/// we have a form annotation as target.
///
/// This annotation is set here in such a case.
///
/// If not set, insertion is done at the target point for a specific page.
@property (nonatomic, nullable) PSPDFButtonFormElement *importingIconAnnotation;

/// Displays a `PSPDFImagePickerController` or choose menu, based on available settings.
/// This will display an alert if the user selects UIImagePickerControllerSourceTypeCamera but does not grant permission.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
- (nullable UIViewController *)presentImagePickerController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

@end

NS_ASSUME_NONNULL_END
