//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents a possible destination directory.
PSPDF_CLASS_SWIFT(Directory)
@interface PSPDFDirectory : PSPDFModel

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Returns a new save directory with a `nil` name.
+ (instancetype)directoryWithPath:(NSString *)path;

/// Returns a new save directory with a `path` and `name`.
///
/// @see initWithPath:name:
+ (instancetype)directoryWithPath:(NSString *)path name:(nullable NSString *)name;

/// Initializes a save directory with the given path and (non-localized) name.
/// You should make sure that the path is valid and writable by the app.
- (instancetype)initWithPath:(NSString *)path name:(nullable NSString *)name NS_DESIGNATED_INITIALIZER;

/// Returns a special directory that is used to show a `UIDocumentPickerViewController`.
+ (instancetype)documentPickerDirectory;

/// The directory path.
@property (nonatomic, readonly) NSString *path;

/// The name used to identify this directory.
@property (nonatomic, nullable, readonly) NSString *name;

/// Localized version of `name`, suitable for display.
/// Will return the last path component if `name` is not set.
@property (nonatomic, readonly) NSString *localizedName;

@end

NS_ASSUME_NONNULL_END
