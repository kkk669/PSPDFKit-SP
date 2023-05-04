//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

#if TARGET_OS_MACCATALYST

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

PSPDF_PROTOCOL_SWIFT(AppKitObjcBridge)
@protocol PSPDFAppKitObjcBridge <NSObject>

/// Registers the PSPDFDocument object to the NSWindowController.
/// Doesn't require a window.
///
/// NOP if the document is already registered.
- (void)attachDocument:(PSPDFDocument *)document;

/// Deregisters the PSPDFDocument object from the NSWindowController.
/// Doesn't require a window.
///
/// NOP if the document is not registered.
- (void)detachDocument:(PSPDFDocument *)document;

/// Mark PSPDFDocument object as dirty. This modifies window handling.
- (void)markDocument:(PSPDFDocument *)pdfDocument asDirty:(BOOL)dirty;

/// Associate a PSPDFDocument with an NSWindowController
///
/// Neither side knows about both symbols so we need to use id here for everything.
/// If a window is already associated with a document, this is replaced.
- (void)attachDocument:(PSPDFDocument *)document toWindow:(id)nsWindow;

@end

PSPDF_CLASS_SWIFT(AppKitHelper)
@interface PSPDFAppKitHelper : NSObject <PSPDFAppKitObjcBridge>

@end

NS_ASSUME_NONNULL_END

#endif
