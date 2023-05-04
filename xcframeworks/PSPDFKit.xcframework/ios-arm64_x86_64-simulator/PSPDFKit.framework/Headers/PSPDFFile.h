//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>

NS_ASSUME_NONNULL_BEGIN

// Basic model object representing a file with a title.
PSPDF_CLASS_SWIFT(File)
@interface PSPDFFile : PSPDFModel

/// Initialize with a name and an URL or data. (do not set both, but needs at least one)
- (instancetype)initWithName:(NSString *)fileName URL:(nullable NSURL *)fileURL data:(nullable NSData *)fileData NS_DESIGNATED_INITIALIZER;

/// The name of the file.
@property (nonatomic, readonly) NSString *fileName;

/// The location of the file.
@property (nonatomic, readonly, nullable) NSURL *fileURL;

/// Data representation of the file.
/// If not set at construction time, we try to memory-map it on access.
///
/// @note Calling `fileDataMappedWithError:` is recommended, so potential errors can be caught.
@property (nonatomic, readonly, nullable) NSData *fileData;

/// The mime type of the document as derived from `fileName`, falling back to `application/pdf` if no mime type could be derived.
@property (nonatomic, readonly) NSString *mimeType;

/// Returns either the set data, or a memory-mapped version of `fileURL`.
/// Guaranteed to not return an empty NSData object.
- (nullable NSData *)fileDataMappedWithError:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
