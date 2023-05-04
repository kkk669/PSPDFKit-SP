//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>

#import <PSPDFKit/PSPDFDataProviding.h>
#import <PSPDFKit/PSPDFDocumentProviderDelegate.h>
#import <PSPDFKit/PSPDFRotation.h>
#import <PSPDFKit/PSPDFSignatureHashAlgorithm.h>
#import <PSPDFKit/PSPDFMeasurementModels.h>

@class PSPDFFormParser, PSPDFTextParser, PSPDFOutlineParser, PSPDFAnnotationManager, PSPDFDocumentProvider, PSPDFLabelParser, PSPDFDocument, PSPDFPageInfo;

NS_ASSUME_NONNULL_BEGIN

/// A set of flags specifying which operations shall be permitted when the document is opened with user access.
typedef NS_OPTIONS(NSUInteger, PSPDFDocumentPermissions) {
    PSPDFDocumentPermissionsNoFlags = 0,
    /// Print the document. See also `PSPDFDocumentPermissionsPrintHighQuality`. (Security handlers of revision 3 or greater)
    PSPDFDocumentPermissionsPrinting = 1 << 0,
    /// Modify the contents of the document
    PSPDFDocumentPermissionsModification = 1 << 1,
    /// (Security handlers of revision 2) Copy or otherwise extract text and graphics from the document, including extracting text and graphics (in support of accessibility to users with disabilities or for other purposes).
    /// (Security handlers of revision 3 or greater) Copy or otherwise extract text and graphics from the document by operations other than that controlled by bit 10.
    PSPDFDocumentPermissionsExtract = 1 << 2,
    /// Add or modify text annotations, fill in interactive form fields, and, if bit 4 is also set, create or modify interactive form fields (including signature fields).
    PSPDFDocumentPermissionsAnnotationsAndForms = 1 << 3,
    /// (Security handlers of revision 3 or greater) Fill in existing interactive form fields (including signature fields), even if bit 6 is clear.
    PSPDFDocumentPermissionsFillForms = 1 << 4,
    /// Unused. This bit was previously to restrict extracting text and graphics for accessibility (e.g. VoiceOver). PDF 2.0 deprecated this option. PSPDFKit ignores this option and does not show this option is the UI (`PDFDocumentSecurityViewController`). You should refrain from disabling this permission in order to improve accessibility in PDF readers that do not yet follow the recommendations of PDF 2.0.
    PSPDFDocumentPermissionsExtractAccessibility = 1 << 5,
    /// (Security handlers of revision 3 or greater) Assemble the document (insert, rotate, or delete pages and create document outline items or thumbnail images), even if bit 4 is clear.
    PSPDFDocumentPermissionsAssemble = 1 << 6,
    /// The PDF reference states that this permission may be restricted to only allow printing with degraded quality (if the printing permission is also granted). Since iOS only offers a single printing pipeline, restricting this permission has no effect on PSPDFKit for iOS. If the printing permission is granted then printing may always be high quality.
    PSPDFDocumentPermissionsPrintHighQuality = 1 << 7,
} NS_SWIFT_NAME(DocumentPermissions);

/// An enumeration that specifies document permissions level.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFDocumentPermissionsLevel) {
    /// The level that indicates no document permissions.
    PSPDFDocumentPermissionsLevelNone = 0,
    /// The level that indicates user document permissions.
    PSPDFDocumentPermissionsLevelUser,
    /// The level that indicates owner document permissions.
    PSPDFDocumentPermissionsLevelOwner
} NS_SWIFT_NAME(DocumentPermissionsLevel);

/// A `Document` consists of one or multiple `PSPDFDocumentProvider`'s.
/// Each document provider has exactly one data source (file/data/dataProvider)
///
/// @note This class is used within `Document` and should not be instantiated externally.
PSPDF_CLASS_SWIFT(PDFDocumentProvider)
@interface PSPDFDocumentProvider : NSObject<PSPDFOverridable>

/// Do not manually init this class - this can only be done SDK internally.
PSPDF_EMPTY_INIT_UNAVAILABLE

/// Referenced data provider.
@property (nonatomic, readonly) id<PSPDFDataProviding> dataProvider;

/// The data provider URL, if the data provider exposes it.
@property (nonatomic, readonly, nullable) NSURL *fileURL;

/// Returns a `Data` representation, memory-maps files, copies a data provider.
- (nullable NSData *)dataRepresentationWithError:(NSError **)error;

/// Returns the `fileSize` of this documentProvider.
@property (nonatomic, readonly) unsigned long long fileSize;

/// Accesses the parent document.
@property (nonatomic, weak, readonly) PSPDFDocument *document;

/// Delegate for writing annotations. Defaults to the current set document.
@property (atomic, weak) id<PSPDFDocumentProviderDelegate> delegate;

/// Returns the page info object for the supplied pageIndex, if it exists.
///
/// @note Unlike with `-[PSPDFDocument pageInfoForPageAtIndex:]` here the returned `PSPDFPageInfo`'s
/// `pageIndex` property always equals the supplied `pageIndex` argument
- (nullable PSPDFPageInfo *)pageInfoForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Number of pages in the PDF. 0 if source is invalid. Filtered by `pageRange`.
@property (nonatomic, readonly) PSPDFPageCount pageCount;

/// Returns the page offset relative to the document.
@property (nonatomic, readonly) NSUInteger pageOffsetForDocument;

/// Returns the password used to unlock the document.
@property (nonatomic, copy, readonly, nullable) NSString *password;

/// The attached content signature.
@property (nonatomic, copy, readonly, nullable) NSData *contentSignature;

/// Specifies what functions are allowed for a PDF document.
///
/// @note This replaces `allowsCopying` and `allowsPrinting` from earlier versions of the SDK.
@property (nonatomic, readonly) PSPDFDocumentPermissions permissions;

/// Returns the permissions status of the PDF document. You have PSPDFDocumentPermissionsLevelNone status for an encrypted
/// document that you have not supplied either a valid user or owner password. For a document with no encryption, you
/// automatically have PSPDFDocumentPermissionsLevelOwner status.
@property (nonatomic, readonly) PSPDFDocumentPermissionsLevel permissionsLevel;

/// Was the PDF file encrypted at file creation time?
@property (nonatomic, readonly) BOOL isEncrypted;

/// Was the PDF file encrypted with an User Password.
@property (nonatomic, readonly) BOOL isEncryptedWithUserPassword;

/// Specifies if the document has been unlocked with full access.
@property (nonatomic, readonly) BOOL isUnlockedWithFullAccess;

/// Specifies if the document has been unlocked with the user password.
@property (nonatomic, readonly) BOOL isUnlockedWithUserPassword;

/// Has the PDF file been unlocked? (is it still locked?).
@property (nonatomic, readonly) BOOL isLocked;

/// Are we able to add/change annotations in this file?
/// Annotations can't be added to encrypted documents or if there are parsing errors.
///
/// @note If `Features.annotationEditing` isn't available, this will return NO.
@property (nonatomic, readonly) BOOL canEmbedAnnotations;

/// A flag that indicates whether changing existing annotations or creating new annotations are allowed
///
/// @note Searches and checks the digital signatures on the first call (caches the result for subsequent calls)
@property (nonatomic, readonly) BOOL allowAnnotationChanges;

/// A file identifier.
///
/// @note A permanent identifier based on the contents of the file at the time it was originally created.
@property (nonatomic, copy, readonly, nullable) NSData *fileId;

/// Access the PDF title. (".pdf" will be truncated)
///
/// @note If there's no title in the PDF metadata, the file name will be used.
@property (nonatomic, copy, readonly, nullable) NSString *title;

/// Return a textParser for the specific document page. Page starts at 0.
/// Will parse the page contents before returning. Might take a while.
- (nullable PSPDFTextParser *)textParserForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Outline extraction class for current PDF.
/// Lazy initialized. Can be subclassed.
@property (nonatomic, readonly) PSPDFOutlineParser *outlineParser;

/// Returns the AcroForm parser.
/// Forms are a separate component and might not be enabled for your license.
/// If forms are not enabled or not part of your license, this will return nil.
///
/// @see `formsEnabled` on the `Document` class.
@property (nonatomic, readonly, nullable) PSPDFFormParser *formParser;

/// Annotation manager/coordinator for current PDF.
/// The actual annotation parsing happens in annotation providers managed by this class.
///
/// Lazy initialized. Can be subclassed.
@property (nonatomic, readonly) PSPDFAnnotationManager *annotationManager;

/// Page labels found in the current PDF.
///
/// Lazy initialized. Can be subclassed.
@property (nonatomic, readonly) PSPDFLabelParser *labelParser;

/// Access the PDF metadata.
@property (nonatomic, copy, readonly) NSDictionary<NSString *, id> *metadata;

/// Get the XMP metadata in XML format, if there is any.
@property (nonatomic, readonly, nullable) NSString *XMPMetadata;

/// Sets a page rotation for display without writing to the PDF.
///
/// @warning There are a lot of caveats with this API. Instead we recommend using `Processor` or `PDFDocumentEditor` to perform page rotations.
/// If you’re considering using this API, we recommend contacting us at https://pspdfkit.com/support/request/ to discuss your requirements.
///
/// The rotation is specified clockwise relative to the rotation stored in the PDF.
/// Therefore the final clockwise rotation of a page is the sum of the rotation stored in the PDF and any offset applied using this method.
///
/// Values set using this method may be read using `PDFPageInfo`’s `rotationOffset` property.
///
/// This method only works if the annotation providers for this document provider are instances of `PSPDFContainerAnnotationProvider`
/// or a subclass. The default `PDFFileAnnotationProvider` is fine. However this method is not compatible with PSPDFKit Instant.
///
/// This method does not work if the `fileAnnotationProvider` has been removed from the annotation manager’s `annotationProviders`.
///
/// This method is intended for temporary rotations for display purposes.
/// If you want a persistent rotation, you must use `Processor` or `PDFDocumentEditor`.
///
/// Changing the page rotation means that annotation properties in the page coordinate space must be updated.
/// Therefore a `PSPDFAnnotationChanged` notification may be posted many times when setting a rotation offset.
///
/// Combining using this method with saving annotations to an external file or in a custom annotation provider may incur additional
/// overhead when saving, and it may result in `PSPDFAnnotationChanged` notification being posted many times when saving.
///
/// A call to `reloadData` is required if the document is currently displayed in a `PDFViewController`.
/// You might also want to clear existing cache, so you don't get a malformed image while re-rendering.
/// `[self.pspdfkit.cache invalidateImagesFromDocument:self.document pageIndex:pageIndex];`
///
/// @warning Calling this method will invalidate the undo and redo stacks of the document's undo manager.
///
/// @param rotation The rotation offset. Valid rotation values are 0, 90, 180 and 270.
/// @param pageIndex The index of the page to be rotated.
- (void)setRotationOffset:(PSPDFRotation)rotation forPageAtIndex:(PSPDFPageIndex)pageIndex NS_SWIFT_NAME(setRotationOffset(_:forPageAt:));

/// Resolves a named destination. E.g. for a `PSPDFRemoteGoToAction`.
/// On success, returns a valid page index. On failure, `NSNotFound`.
- (NSUInteger)resolveNamedDestination:(NSString *)namedDestination;

// MARK: Digital Signatures

/// Returns the hash of the combination of byte ranges of the receiver.
///
/// This method is deprecated in favor of `hashOfData(inRanges:algorithm:)`.
///
/// @param range          The byte range of the part of the document that will be hashed.
///                       A byte range is an array of pairs (byte offset, length in bytes) that describe the (possibly discontiguous) region
///                       of the document that should be hashed. For an already prepared PDF document with a digital signature, you can get
///                       this information from the `byteRange` property of the `signatureInfo` property of a `SignatureFormElement`.
/// @param hashAlgorithm  The hash algorithm that will be used to generate the hashed data.
/// @param error          Collects any error that occurred while hashing the data. For example, the `range` argument may specify offsets
///                       outside of the boundaries of the document size.
- (nullable NSData *)hashDocumentProviderRange:(NSArray<NSNumber *>*)range hashAlgorithm:(PSPDFSignatureHashAlgorithm)hashAlgorithm error:(NSError **)error PSPDF_DEPRECATED(12.1, "Use hashOfData(inRanges:algorithm:) instead.");

/// Returns the hash of the combination of byte ranges of the receiver.
///
/// @param byteRanges The byte ranges of the parts of the document that will be hashed.
///                   For an already prepared PDF document with a digital signature, you can get this information
///                   from the `byteRanges` property of the `signatureInfo` property of a `SignatureFormElement`.
/// @param algorithm  The hash algorithm that will be used to generate the hashed data.
/// @param error      Collects any error that occurred while hashing the data. For example, the `ranges` argument may specify offsets
///                   outside of the boundaries of the document size.
- (nullable NSData *)hashOfDataInRanges:(NSIndexSet *)byteRanges algorithm:(PSPDFSignatureHashAlgorithm)algorithm error:(NSError **)error;

/// The methods in this section provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: - Subclassing Hooks

/// Saves changed annotations.
///
/// @warning You shouldn't call this method directly, use the high-level save method in `Document` instead.
- (BOOL)saveAnnotationsWithOptions:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)error;

/// Resolves a path like `/localhost/Library/test.pdf` into a full path.
/// If either `alwaysLocal` is set or `localhost` is part of the path, we'll handle this as a local URL.
- (NSString *)resolveTokenizedPath:(NSString *)path alwaysLocal:(BOOL)alwaysLocal;

// MARK: - Measurements

/// The currently active `measurementScale` settings. This value is used as the default measurement scale when creating new measurement annotations.
@property (nonatomic, readonly) PSPDFMeasurementScale *measurementScale;

/// Currently active `measurementPrecision` setting. This value is used as the default measurement precision when creating new measurement annotations.
@property (nonatomic, readonly) PSPDFMeasurementPrecision measurementPrecision;

@end

NS_ASSUME_NONNULL_END
