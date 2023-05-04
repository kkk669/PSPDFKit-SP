//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (PSPDFSerialization)

/// Returns an image (or animated image) instance from the previously serialized data.
+ (nullable UIImage *)pspdf_imageWithSerializedData:(NSData *)data NS_SWIFT_NAME(imageWithSerializedData(_:));

@end

/// Serialize image or animated image to data.
PSPDF_EXTERN NSData *PSPDFUIImageSerializedDataRepresentation(UIImage *image) NS_SWIFT_NAME(UIImageSerializedDataRepresentation(_:));

NS_ASSUME_NONNULL_END
