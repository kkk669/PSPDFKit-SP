//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDownloadManager.h>

@class PDFCFilesCache;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDownloadManager ()

/// Designated initializer. Requires a file cache and file Manager.
/// The `downloadManagerPolicy` class is optional.
/// The `fileCache` is also optional.
- (instancetype)initWithFileCache:(nullable PDFCFilesCache *)fileCache fileManager:(id<PSPDFFileManager>)fileManager downloadManagerPolicy:(nullable id<PSPDFDownloadManagerPolicy>)downloadManagerPolicy NS_DESIGNATED_INITIALIZER;

/// The download manager file cache.
@property (nonatomic, nullable, readonly) PDFCFilesCache *cache;

@end

NS_ASSUME_NONNULL_END
