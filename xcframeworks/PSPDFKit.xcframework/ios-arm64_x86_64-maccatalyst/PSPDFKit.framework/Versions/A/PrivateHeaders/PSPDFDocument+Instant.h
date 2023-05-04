//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>

#import <PSPDFKit/PSPDFThreadSafeMutableDictionary.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFCDocumentOpenResult;

@interface PSPDFDocument ()

/// Creates the Core document and returns a `PDFCDocumentOpenResult`.
///
/// Due to how Instant is set-up, we can't guarantee to return a `PDFCDocumentOpenResult` (`self.instantDocumentBackend` is
/// weak) and we also can't allocate a `PDFCDocumentOpenResult` (due to not compiling the class into the binary). Treat
/// a `nil` return value as an unknown error.
- (nullable PDFCDocumentOpenResult *)actuallyCreateCoreDocument:(nullable NSString *)password;

/// The currently active default render options for the document.
@property (nonatomic, readonly) PSPDFThreadSafeMutableDictionary<NSNumber *, PSPDFRenderOptions *> *renderOptionsMap;

/// All overrides that have been registered directly with this document.
@property (nonatomic, copy) NSDictionary<Class, Class> *overrideClassNames;

@end

NS_ASSUME_NONNULL_END
