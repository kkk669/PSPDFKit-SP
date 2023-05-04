//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
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

/// The category of a file.
typedef NS_ENUM(NSInteger, PSPDFFileCategory) {
    /// Unknown category.
    PSPDFFileCategoryUnknown = -1,

    /// The file is an image.
    PSPDFFileCategoryImage,

    /// The file is an audio file.
    PSPDFFileCategoryAudio,

    /// The file is a video.
    PSPDFFileCategoryVideo,

    /// The file is a document.
    PSPDFFileCategoryDocument
};

/// Categorizes a given path into a file category. If no matching category exists,
/// this method returns `PSPDFFileCategoryUnknown`.
PSPDF_SDK_EXPORT PSPDFFileCategory PSPDFFileHelperGetFileCategory(NSString *_Nullable path);

/// Categorizes a given MIME type into a file category. If no matching category exists,
/// this method returns `PSPDFFileCategoryUnknown`.
PSPDF_SDK_EXPORT PSPDFFileCategory PSPDFFileHelperGetFileCategoryFromMIMEType(NSString *_Nullable MIMEType);

/// Returns the entire file translation table. The table maps extension (`NSString`) to
/// category (`PSPDFFileCategory` wrapped in an `NSNumber`).
PSPDF_EXTERN NSDictionary<NSString *, NSNumber *> *PSPDFFileHelperGetFileTranslationTable(void);

NS_ASSUME_NONNULL_END
