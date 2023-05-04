//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// If set as the `delegate` of a window scene’s `screenshotService`, a `PDFViewController` will
/// generate a complete PDF representation of its current document when the user takes a
/// screenshot. This is effectively a streamlined way to share the document with default options
/// (all pages, embed annotations).
///
/// The document is always shared in its current state in-memory, even if auto-save is disabled.
@interface PSPDFViewController (ScreenshotService) <UIScreenshotServiceDelegate>

@end

NS_ASSUME_NONNULL_END
