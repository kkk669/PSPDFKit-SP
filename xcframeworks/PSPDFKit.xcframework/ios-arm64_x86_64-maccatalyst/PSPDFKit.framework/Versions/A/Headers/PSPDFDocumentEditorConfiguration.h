//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFNewPageConfiguration.h>
#import <PSPDFKit/PSPDFBaseConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFDocumentOrientation) {
    PSPDFDocumentOrientationPortrait,
    PSPDFDocumentOrientationLandscape,
} PSPDF_ENUM_SWIFT(PDFDocumentOrientation);

@class PSPDFPageTemplate, PSPDFPageSize, PSPDFDirectory, PSPDFCompression;

PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFDocumentEditor.ConfigurationBuilder)
@interface PSPDFDocumentEditorConfigurationBuilder : PSPDFBaseConfigurationBuilder

/// @see PSPDFDocumentEditorConfiguration.pageTemplates.
@property (nonatomic, copy) NSArray<PSPDFPageTemplate *> *pageTemplates;
/// @see PSPDFDocumentEditorConfiguration.currentDocumentPageSize.
@property (nonatomic, nullable) PSPDFPageSize *currentDocumentPageSize;
/// @see PSPDFDocumentEditorConfiguration.pageSizes.
@property (nonatomic) NSArray<PSPDFPageSize *> *pageSizes;
/// @see PSPDFDocumentEditorConfiguration.currentDocumentDirectory.
@property (nonatomic, nullable) PSPDFDirectory *currentDocumentDirectory;
/// @see PSPDFDocumentEditorConfiguration.saveDirectories.
@property (nonatomic) NSArray<PSPDFDirectory *> *saveDirectories;
/// @see PSPDFDocumentEditorConfiguration.compressions.
@property (nonatomic) NSArray<PSPDFCompression *> *compressions;
/// @see PSPDFDocumentEditorConfiguration.selectedTemplate.
@property (nonatomic, nullable) PSPDFPageTemplate *selectedTemplate;
/// @see PSPDFDocumentEditorConfiguration.selectedPageSize.
@property (nonatomic, nullable) PSPDFPageSize *selectedPageSize;
/// @see PSPDFDocumentEditorConfiguration.selectedOrientation.
@property (nonatomic) PSPDFDocumentOrientation selectedOrientation;
/// @see PSPDFDocumentEditorConfiguration.selectedColor.
@property (nonatomic, nullable) UIColor *selectedColor;
/// @see PSPDFDocumentEditorConfiguration.selectedImage.
@property (nonatomic, nullable) UIImage *selectedImage;
/// @see PSPDFDocumentEditorConfiguration.selectedImagePageSize.
@property (nonatomic, nullable) PSPDFPageSize *selectedImagePageSize;
/// @see PSPDFDocumentEditorConfiguration.selectedCompression.
@property (nonatomic, nullable) PSPDFCompression *selectedCompression;
/// @see PSPDFDocumentEditorConfiguration.selectedSaveDirectory.
@property (nonatomic, nullable) PSPDFDirectory *selectedSaveDirectory;
/// @see PSPDFDocumentEditorConfiguration.userFacingCompressionEnabled.
@property (nonatomic) BOOL userFacingCompressionEnabled;
/// @see PSPDFDocumentEditorConfiguration.allowExternalFileSource.
@property (nonatomic) BOOL allowExternalFileSource;

@end

/// Configuration options for various document editor controllers.
///
/// @note Set the configuration values before passing this object to view controllers for display.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFDocumentEditor.Configuration)
@interface PSPDFDocumentEditorConfiguration : PSPDFBaseConfiguration<PSPDFDocumentEditorConfigurationBuilder *>

// MARK: Presets

/// A list of predefined page patterns.
@property (nonatomic, readonly) NSArray<PSPDFPageTemplate *> *pageTemplates;

/// A page size that represents a representative page on the current
/// Needs to be set based on the current document.
///
/// @note Can't be `nil` if `pageSizes` is empty.
@property (nonatomic, readonly) PSPDFPageSize *currentDocumentPageSize;

/// A list of predefined page sizes.
///
/// @note Can't be empty if `currentDocumentPageSize` is `nil`.
@property (nonatomic, readonly) NSArray<PSPDFPageSize *> *pageSizes;

/// Represents the directory of the current document.
///
/// @note Can't be `nil` if `saveDirectories` is empty.
@property (nonatomic, readonly) PSPDFDirectory *currentDocumentDirectory;

/// A list of predefined save directories.
/// Defaults to `Directory.documentPickerDirectory` to show the system document picker automatically.
///
/// @note Can't be empty if `currentDocumentDirectory` is `nil`.
@property (nonatomic, readonly) NSArray<PSPDFDirectory *> *saveDirectories;

/// A list of predefined compressions.
///
/// @note Can't be empty if `selectedCompression` is `nil`.
@property (nonatomic, readonly) NSArray<PSPDFCompression *> *compressions;

// MARK: Selection

/// The currently selected page pattern. Defaults to nil (no page pattern).
@property (nonatomic, readonly) PSPDFPageTemplate *selectedTemplate;

/// The currently selected page size.
/// Defaults to `currentDocumentPageSize` if available, otherwise the first item in `pageSizes` is used.
@property (nonatomic, readonly) PSPDFPageSize *selectedPageSize;

/// The currently selected page orientation. Defaults to `PSPDFDocumentOrientationPortrait`.
@property (nonatomic, readonly) PSPDFDocumentOrientation selectedOrientation;

/// The currently selected page background color.
/// Setting this to `nil` will result in the default white color being used.
@property (nonatomic, readonly) UIColor *selectedColor;

/// The currently selected page image.
/// Setting this to `nil` will result in no image being used.
@property (nonatomic, readonly) UIImage *selectedImage;

/// A page size that represents a the size of the selected image.
///
/// @note Will be `nil` when `selectedImage` is nil.
@property (nonatomic, readonly) PSPDFPageSize *selectedImagePageSize;

/// Represents the compression for the selected image.
///
/// @note Will be `nil` when `selectedImage` is nil.
@property (nonatomic, readonly) PSPDFCompression *selectedCompression;

/// The currently selected save directory.
/// Defaults to `currentDocumentDirectory` if available, otherwise the first item in `saveDirectories` is used.
@property (nonatomic, readonly) PSPDFDirectory *selectedSaveDirectory;

/// Defines, whether the image compression should be editable by the user. Defaults to `true`.
/// When set to NO, images will use the default compression of 0.8
@property (nonatomic, readonly) BOOL userFacingCompressionEnabled;

/// Defines, whether the available source of new pages should be external file. Defaults to `false`.
/// When set to NO, file selector is not available.
///
/// @note On iOS 10 and earlier, an application initializing a document picker requires the iCloud entitlement set.
@property (nonatomic, readonly) BOOL allowExternalFileSource;

@end

/// Represents a page size option for new pages.
PSPDF_CLASS_SWIFT(PageSize)
@interface PSPDFPageSize : PSPDFModel

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Returns a new save directory with a `size` and `name`.
///
/// @see initWithSize:name
+ (instancetype)size:(CGSize)size name:(NSString *)name;

/// Initializes a new page size with the given size and (non-localized) name.
- (instancetype)initWithSize:(CGSize)size name:(NSString *)name NS_DESIGNATED_INITIALIZER;

/// The size in pdf points.
@property (nonatomic, readonly) CGSize size;

/// The name for this size configuration.
@property (nonatomic, readonly) NSString *name;

/// Localized version of `name`, suitable for display.
@property (nonatomic, readonly) NSString *localizedName;

/// A localized string representation of the `size`.
@property (nonatomic, readonly) NSString *localizedSize;

/// The `size` adjusted for the given `orientation`.
/// Makes sure that either the height or width is the larger dimension.
- (CGSize)sizeForOrientation:(PSPDFDocumentOrientation)orientation;

@end

/// Define a compression used for image compression.
PSPDF_CLASS_SWIFT(Compression)
@interface PSPDFCompression : PSPDFModel

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Create a new compression instance.
///
/// @param compression Used compression value.
/// @param name Name of this compression configuration.
+ (instancetype)compression:(CGFloat)compression name:(NSString *)name;

/// Create a new compression instance.
///
/// @param compression Used compression value.
/// @param name Name of the compression.
- (instancetype)initWithCompression:(CGFloat)compression name:(NSString *)name NS_DESIGNATED_INITIALIZER;

/// Used compression value.
@property (nonatomic, readonly) CGFloat compression;

/// The name for this compression configuration.
@property (nonatomic, readonly) NSString *name;

/// Localized version of `name`, suitable for display.
@property (nonatomic, readonly) NSString *localizedName;

@end

/// Implemented in classes that use or modify the document editor configuration.
///
/// @see e.g. `PSPDFNewPageViewController`
PSPDF_PROTOCOL_SWIFT(PDFDocumentEditorConfigurationConfigurable)
@protocol PSPDFDocumentEditorConfigurationConfigurable<NSObject>

/// Initializes the controller with a document editor configuration.
- (instancetype)initWithDocumentEditorConfiguration:(PSPDFDocumentEditorConfiguration *)configuration;

/// Contains all possible page configuration options.
@property (nonatomic, readonly) PSPDFDocumentEditorConfiguration *documentEditorConfiguration;

@end

NS_ASSUME_NONNULL_END
