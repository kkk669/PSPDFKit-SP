//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDataSink.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// The data sink that works with `PSPDFAESCryptoDataProvider`
PSPDF_CLASS_SWIFT(AESCryptoDataSink)
@interface PSPDFAESCryptoDataSink : NSObject <PSPDFDataSink>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the data sink with a UID.
/// Initialization involves creating a temporary file and if PSPDFDataSinkOptionAppend is specified, copy the original file into it.
- (instancetype)initWithUID:(NSString *)UID passphraseProvider:(NSString * (^)(void))passphraseProvider options:(PSPDFDataSinkOptions)options NS_DESIGNATED_INITIALIZER;

/// Initializes the data sink with a file URL.
- (instancetype)initWithURL:(NSURL *)fileURL passphraseProvider:(NSString * (^)(void))passphraseProvider options:(PSPDFDataSinkOptions)options NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
