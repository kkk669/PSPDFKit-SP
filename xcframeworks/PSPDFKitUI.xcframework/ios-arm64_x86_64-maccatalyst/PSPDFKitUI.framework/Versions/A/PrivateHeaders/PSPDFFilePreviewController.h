//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <QuickLook/QuickLook.h>

NS_ASSUME_NONNULL_BEGIN

/// Use QuickLook to preview a single item.
PSPDF_SDK_CLASS_SWIFT(FilePreviewController)
@interface PSPDFFilePreviewController : QLPreviewController <QLPreviewControllerDataSource, QLPreviewControllerDelegate, PSPDFOverridable>

/// Convenience initializer.
- (instancetype)initWithPreviewURL:(NSURL *)previewURL;

/// URL to then item that should be previewed.
///
/// @note The file at `previewURL` can be moved to a different location
/// due to security settings and will be deleted when the controller deallocates.
@property (nonatomic, copy, nullable) NSURL *previewURL;

/// Can be set to provide a better animation. Optional.
@property (nonatomic) CGRect sourceRect;

@end

NS_ASSUME_NONNULL_END
