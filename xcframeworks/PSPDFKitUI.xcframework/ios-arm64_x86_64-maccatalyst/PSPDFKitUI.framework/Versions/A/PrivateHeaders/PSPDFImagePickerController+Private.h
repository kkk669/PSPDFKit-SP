//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFImagePickerController.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFImagePickerController ()

/// Checks not only what is allowed from the OS but also what is configured in the policy settings and what the user specified by overriding `resolvedImagePickerSourceTypes`.
+ (NSArray<NSNumber *> *)resolvedImagePickerSourceTypes;

@end

NS_ASSUME_NONNULL_END
