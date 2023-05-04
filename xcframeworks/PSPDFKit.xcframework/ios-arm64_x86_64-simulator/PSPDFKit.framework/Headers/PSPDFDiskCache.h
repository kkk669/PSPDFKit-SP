//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFKitGlobal, PSPDFRenderRequest;

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFDiskCacheFileFormat) {
    /// JPEG encoding.
    PSPDFDiskCacheFileFormatJPEG,
    /// PNG encoding.
    PSPDFDiskCacheFileFormatPNG,
} PSPDF_ENUM_SWIFT(DiskCache.FileFormat);

/// The disk cache persists its metadata on disk together with the images and provides
/// cached images even after the app restarts.
///
/// The disk cache is designed to store and fetch images, including metadata, in a
/// fast way. No actual images will be held in memory (besides during the time they
/// are scheduled for writing to disk).
///
/// The disk cache can be accessed with `PSPDFKit.SDK.shared.cache.diskCache`.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(DiskCache)
@interface PSPDFDiskCache : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

// MARK: Settings

/// The maximum amount of disk space the cache is allowed to use (in bytes).
///
/// This value is a non strict maximum value. The cache might also start evicting images
/// before this limit is reached, depending on the memory and disk state of the device.
///
/// @note Set to 0 to disable the disk cache.
@property (nonatomic) long long allowedDiskSpace;

/// The disk space currently used by the cache (in bytes).
@property (nonatomic, readonly) long long usedDiskSpace;

/// The directory this disk cache uses to store and load images.
///
/// The default value is `<iOS Caches Directory>/PSPDFKit/Pages`. The iOS Caches
/// Directory is obtained by calling `NSSearchPathForDirectoriesInDomains`.
/// Example: `/var/mobile/Containers/Data/Application/<UUID>/Library/Caches/PSPDFKit/Pages`.
///
/// @note This directory is automatically created upon first cache write.
/// Clearing the cache will delete all sub-directories, but not the directory itself.
///
/// You can manually create this directory and set a custom iOS Data Protection level.
///
/// @see https://pspdfkit.com/guides/ios/customizing-the-interface/using-the-render-queue/#toc_the-cache
@property (nonatomic, copy) NSString *cacheDirectory;

/// The file format used to store images.
///
/// Defaults to JPEG.
@property (nonatomic) PSPDFDiskCacheFileFormat fileFormat;

/// If the file format is JPEG, this controls the quality (from 0.0 = bad to 1.0 = best).
///
/// Defaults to 0.9.
@property (nonatomic) CGFloat compression;

// MARK: Security

/// A block that is called to encrypt data before storing it to the disk.
///
/// @note This block is called on an arbitrary, concurrent background queue.
@property (nonatomic, copy, nullable) NSData *_Nullable (^encryptionHelper)(PSPDFRenderRequest *request, NSData *data);

/// A block that is called to decrypt data that was previously encrypted via the encryption
/// helper.
///
/// @note This block is called on an arbitrary, concurrent background queue.
@property (nonatomic, copy, nullable) NSData *_Nullable (^decryptionHelper)(PSPDFRenderRequest *request, NSData *encryptedData);

@end

NS_ASSUME_NONNULL_END
