//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFileManager.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFFileManager.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Checks if the `url` is a file URL an the file at its destination is writable using `fileManager`.
///
/// @see pspdf_isWritableFileAtPath:
PSPDF_EXTERN BOOL PSPDFIsWritableFileAtURL(id<PSPDFFileManager> fileManager, NSURL *url);

/// Checks if the file at the given path is writable using `fileManager`. Also adds special handling for certain
/// directories that would be writable on the simulator, but not on the device.
PSPDF_SDK_EXPORT BOOL PSPDFIsWritableFileAtPath(id<PSPDFFileManager> fileManager, NSString *path);

/// Checks if the file at the given path is deletable using `fileManager`. Also adds special handling for certain
/// directories that would be deletable on the simulator, but not on the device.
///
/// @note It will always return YES if the path is of a file located in the `Documents/Inbox` directory.
PSPDF_SDK_EXPORT BOOL PSPDFIsDeletableFileAtPath(id<PSPDFFileManager> fileManager, NSString *path);

@interface PSPDFDefaultFileManager ()

- (BOOL)createSymbolicLinkAtURL:(NSURL *)url withDestinationURL:(NSURL *)destURL error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
