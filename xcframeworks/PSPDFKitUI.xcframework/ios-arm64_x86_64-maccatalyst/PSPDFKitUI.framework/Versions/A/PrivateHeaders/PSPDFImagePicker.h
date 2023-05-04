//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFLocalizedStringKeys.h>

NS_ASSUME_NONNULL_BEGIN

/// Helper for handling available sources and privacy access for `UIImagePickerController`.
@interface PSPDFImagePicker : NSObject

/// Checks not only what is allowed from the OS but also what we configured in the policy settings.
+ (NSArray<NSNumber *> *)availableImagePickerSourceTypes;

/// Converts a `UIImagePickerControllerSourceType` to a corresponding string that is suitable as a localized string key.
+ (PSPDFLocalizedStringKey)localizedStringKeyFromImagePickerControllerSourceType:(UIImagePickerControllerSourceType)sourceType;

/// Requests user access for the given source type (showing the default privacy access alert) if access wasn't determined previously already.
///
/// @param handler Completion handler which is called on the main thread when the privacy access has been determined. This is called immediately when the access has been determined previously.
+ (void)requestAccessIfNotDeterminedForSourceType:(UIImagePickerControllerSourceType)sourceType completionHandler:(void (^_Nonnull)(void))handler;

/// Checks if the source type specified is accessible, and, if not, requires a manual alert to be displayed.
///
/// @param sourceType The source type to be checked.
/// @return YES if the source type requires an alert to be displayed.
+ (BOOL)imagePickerSourceTypeIsDeniedAndNeedsManualAlert:(UIImagePickerControllerSourceType)sourceType;

/// Returns a view controller that displays a message about access to the source being denied.
///
/// @param sourceType The source type that is denied access. The displayed text is changed depending on this.
/// @param handler The block to call after the alert has been dismissed
/// @return A configured UIViewController instance
+ (UIViewController *)accessDeniedControllerForSourceType:(UIImagePickerControllerSourceType)sourceType withDismissalHandler:(void (^_Nullable)(void))handler;

@end

NS_ASSUME_NONNULL_END
