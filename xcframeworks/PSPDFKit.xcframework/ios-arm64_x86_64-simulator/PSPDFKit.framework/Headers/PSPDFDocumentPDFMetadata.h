//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMetadataName.h>

@class PSPDFDocument, PSPDFDocumentProvider;

NS_ASSUME_NONNULL_BEGIN

/// This class allows you to modify a PDF document’s metadata.
/// Metadata is defined in two ways in the PDF spec (§ 14.3):
///
/// - The Info PDF dictionary. This class is handling this.
/// - A metadata stream containing XMP data. See `PSPDFDocumentXMPMetadata` for that. (https://en.wikipedia.org/wiki/Extensible_Metadata_Platform)
///
/// ### Info dictionary support
///
/// All values specified in the Info dictionary are represented by the following types:
///
/// - `NSString`
/// - `NSNumber`
/// - `NSDate`
/// - `NSArray<id>`: can include any of the types mentioned.
/// - `NSDictionary<NSString*, id>`: value can be any of the types mentioned.
///
/// These types can be combined in any way you see fit and it will be converted into the proper PDF types.
///
/// @note The PDF stream type is not yet supported.
///
PSPDF_CLASS_SWIFT(PDFMetadata)
@interface PSPDFDocumentPDFMetadata : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the `PSPDFDocumentPDFMetadata` with a document.
/// The document needs to be valid. If it is not, reading or setting values will fail gracefully.
///
/// @note If `document` is a compound document, this will provide access to ONLY the first `PSPDFDocumentProvider`.
- (nullable instancetype)initWithDocument:(PSPDFDocument *)document;

/// Initializes the `PSPDFDocumentPDFMetadata` with a document provider.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// Provides access to the document this instance is handling.
@property (nonatomic, readonly, weak) PSPDFDocument *document;

/// Provides access to the document provider this instance is handling.
@property (nonatomic, readonly) PSPDFDocumentProvider *documentProvider;

/// Returns a list of all the keys set in the `Info` dictionary.
@property (nonatomic, readonly) NSArray<PSPDFMetadataName> *allInfoKeys;

/// Returns the object that is set in the `Info` dictionary for `key`
///
/// @note Please see the class documentation for types that might be returned.
- (nullable id)objectForInfoDictionaryKey:(PSPDFMetadataName)key;

/// Sets the given object in the `Info` dictionary for `key`.
///
/// @note Please see the class documentation for valid types for `value`. If you pass a invalid type, a exception will
/// be raised.
- (void)setObject:(nullable id)object forInfoDictionaryKey:(PSPDFMetadataName)key;

/// Allows generic dictionary access.
- (nullable id)objectForKeyedSubscript:(PSPDFMetadataName)key;

/// Allows generic dictionary access.
- (void)setObject:(nullable id)object forKeyedSubscript:(PSPDFMetadataName)key;

@end

NS_ASSUME_NONNULL_END
