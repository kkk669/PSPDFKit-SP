//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSData (PSPDFFoundation)

/// Returns the SHA256 hash of the contents of a local file at a given URL.
/// Fast, and does not read the whole file into memory.
+ (nullable NSData *)pspdf_SHA256FromFileURL:(NSURL *)fileURL error:(NSError **)error;

/// Decompress data.
@property (nonatomic, readonly, nullable) NSData *pspdf_zlibInflate;

/// Compress data stream. See zlib.h for valid options for `compressionLevel`.
///
/// Z_NO_COMPRESSION, Z_BEST_SPEED, Z_BEST_COMPRESSION, Z_DEFAULT_COMPRESSION.
/// Z_DEFAULT_COMPRESSION is a good choice.
- (nullable NSData *)pspdf_zlibDeflateWithCompressionLevel:(int)compressionLevel;

/// Calculates the MD5 hash.
///
/// @warning MD5 is an outdated hashing algorithm. Use SHA256 instead.
@property (nonatomic, readonly) NSData *pspdf_md5Hash;

/// Calculates the MD5 hash as string.
///
/// @warning MD5 is an outdated hashing algorithm. Use SHA256 instead.
@property (nonatomic, readonly) NSString *pspdf_md5HashString;

/// Calculates the SHA256 hash.
@property (nonatomic, readonly) NSData *pspdf_sha256Hash;

/// Calculates the SHA256 hash as string.
@property (nonatomic, readonly) NSString *pspdf_sha256HashString;

/// Returns the hex string representing the data.
@property (nonatomic, readonly, nullable) NSString *pspdf_hexRepresentation;

/// Returns random data via SecRandom.
+ (NSData *)pspdf_randomDataOfLength:(size_t)length NS_SWIFT_NAME(random(length:));

@end

NS_ASSUME_NONNULL_END
