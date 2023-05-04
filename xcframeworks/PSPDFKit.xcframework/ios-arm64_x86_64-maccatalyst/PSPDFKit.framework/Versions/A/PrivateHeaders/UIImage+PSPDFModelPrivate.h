//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/UIImage+PSPDFModel.h>

/// Will load an image from the bundle. Will auto-manage legacy images and bundle directory.
PSPDF_EXPORT UIImage *_Nullable PSPDFBundleImage(NSString *_Nullable imageName);

/// Register a custom block to return custom images.
/// If this block is NULL or returns nil, PSPDFKit.bundle will use for the lookup.
PSPDF_EXPORT void PSPDFSetBundleImageBlock(UIImage *_Nullable (^_Nullable imageBlock)(NSString *_Nullable imageName));
