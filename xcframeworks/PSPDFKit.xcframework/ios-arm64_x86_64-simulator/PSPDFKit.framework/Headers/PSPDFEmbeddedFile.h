//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// Represents an embedded file.
PSPDF_CLASS_SWIFT(EmbeddedFile)
@interface PSPDFEmbeddedFile : PSPDFModel

/// Initializes a `PSPDFEmbeddedFile` with the given `fileName`, `fileURL`, `fileDescription`, and `modificationDate`.
///
/// @param fileURL A local file URL of the attachment.
/// @param fileDescription The optional description of the file. If set, it will override the file annotation's `contents`.
- (instancetype)initWithFileURL:(NSURL *)fileURL fileDescription:(nullable NSString *)fileDescription;

/// The document, if available.
@property (nonatomic, weak, readonly) PSPDFDocument *document;

/// File name.
@property (nonatomic, readonly) NSString *fileName;

/// File size.
@property (nonatomic, readonly) uint64_t fileSize;

/// File description. Optional.
///
/// @note If the embedded file is part of a `PSPDFFileAnnotation` the value of `fileDescription` is equal to the file annotation's `contents`.
@property (nonatomic, readonly, nullable) NSString *fileDescription;

/// File modification date (if set).
@property (nonatomic, readonly, nullable) NSDate *modificationDate;

/// If the file URL has been extracted by XFDF or external saving, it is set here.
///
/// @note In most cases, you should call `fileURLWithError:` instead to fetch the URL.
@property (nonatomic, readonly, nullable) NSURL *fileURL;

/// Retrieves the embedded stream and returns a file URL to the data.
/// This also sets `fileURL` if successful.
///
/// @return a file URL to the data.
- (nullable NSURL *)fileURLWithError:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
