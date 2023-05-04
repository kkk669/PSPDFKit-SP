//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFProcessorItem.h>
#import <PSPDFKit/PSPDFRenderRequest.h>
#import <PSPDFKit/PSPDFFormField.h>
#import <PSPDFKit/PSPDFRotation.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;
@class PSPDFNewPageConfiguration;

/// Specifies how a annotation should be included in the resulting document.
/// See `modifyAnnotationsOfType:change:` and `modifyAnnotations:change:error:`.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationChange) {
    /// The annotation will be flattened. It can no longer be modified in the resulting document.
    PSPDFAnnotationChangeFlatten,

    /// The annotation will be removed.
    PSPDFAnnotationChangeRemove,

    /// The annotation will be embedded into the resulting document, allowing it to still be modified.
    PSPDFAnnotationChangeEmbed,

    /// Processes the document for printing. Flattens annotations that can be printed, removes the remaining ones.
    PSPDFAnnotationChangePrint
} PSPDF_ENUM_SWIFT(AnnotationChange);

/// Container for various settings for manipulating documents with `PSPDFProcessor`.
///
/// @note Some basic options are available without the Document Editor component,
/// however most options do require this component to be licensed.
/// Learn more at https://pspdfkit.com/pdf-sdk/ios/document-editor/
PSPDF_CLASS_SWIFT(Processor.Configuration)
@interface PSPDFProcessorConfiguration : NSObject<NSCopying>

///  Designated initializer
///
///  @param document The document that the configuration is based on.
///  If a document is given, it needs to be valid, else we return nil.
///
///  @return The processor configuration or nil in case the document
///  cannot be processed or is not valid.
- (nullable instancetype)initWithDocument:(nullable PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// The source document.
@property (nonatomic, readonly, nullable) PSPDFDocument *document;

/// Returns the page count of the currently configured generated document.
@property (nonatomic, readonly) NSInteger pageCount;

/// Instructs the processor to change form field names as described in the mapping.
/// The partial field name (see PDF Reference 1.7, 12.7.3.2, “Field Names”).
///
/// @note This method requires the Document Editor component to be enabled for your license.
@property (nonatomic, copy) NSDictionary<NSString *, NSString *> *formFieldNameMappings;

/// Instructs the processor to change form mapping names as described in the mapping.
/// The mapping name that shall be used when exporting interactive form field data from the document.
///
/// @note This method requires the Document Editor component to be enabled for your license.
@property (nonatomic, copy) NSDictionary<NSString *, NSString *> *formMappingNameMappings;

/// Moves pages from the specified indexes to the destination index.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)movePages:(NSIndexSet *)indexes toDestinationIndex:(PSPDFPageIndex)destinationPageIndex;

/// Removes pages from the document. This will also update `pageCount`.
- (void)removePages:(NSIndexSet *)indexes;

/// If this is set to @YES, all blank pages will be removed from the generated document.
/// This does NOT update `pageCount` as it only goes into effect while processing the document.
- (void)setShouldStripBlankPagesOnGenerate:(BOOL)shouldStrip;

/// Removes all pages that are not listed in `indexes`.
- (void)includeOnlyIndexes:(NSIndexSet *)indexes;

/// Rotates a page. `degrees` must be a value of 0, 90, 180 or 270.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)rotatePage:(PSPDFPageIndex)pageIndex by:(PSPDFRotation)degrees;

/// Scales the given page index to the given size. The size must be specified in PDF points.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)scalePage:(PSPDFPageIndex)pageIndex toSize:(CGSize)size;

/// Scales the given page index to the given size. The size must be specified in millimeters.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)scalePage:(PSPDFPageIndex)pageIndex toSizeInMillimeter:(CGSize)mmSize;

/// Changes the `CropBox` for the given page to the given rect. The rect must be specified in points.
/// This does NOT scale the page. See `scalePage:toSizeInMillimeter:` and `scalePage:toSize:`.
/// Definition of a `CropBox` from the PDF spec:
/// The crop box defines the region to which the contents of the page shall be clipped (cropped) when
/// displayed or printed. Unlike the other boxes, the crop box has no defined meaning in terms of physical
/// page geometry or intended use; it merely imposes clipping on the page contents. However, in the absence
/// of additional information (such as imposition instructions specified in a JDF or PJTF job ticket), the crop
/// box determines how the page’s contents shall be positioned on the output medium. The default value is the
/// page’s media box.
/// TL;DR: The visible part of the page.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)changeCropBoxForPageAtIndex:(PSPDFPageIndex)pageIndex toRect:(CGRect)rect;

/// Changes the `MediaBox` for the given page to the given rect. The rect must be specified in points.
/// This does NOT scale the page. See `scalePage:toSizeInMillimeter:` and `scalePage:toSize:`.
/// Definition of a `MediaBox` from the PDF spec:
/// The media box defines the boundaries of the physical medium on which the page is to be printed. It may
/// include any extended area surrounding the finished page for bleed, printing marks, or other such purposes.
/// It may also include areas close to the edges of the medium that cannot be marked because of physical
/// limitations of the output device. Content falling outside this boundary may safely be discarded without
/// affecting the meaning of the PDF file.
/// TL;DR: The size of the page.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)changeMediaBoxForPageAtIndex:(PSPDFPageIndex)pageIndex toRect:(CGRect)rect;

/// Adds a new page at `destinationPageIndex`.
/// If `newPageConfiguration` is nil, the size of the new page will match the page size of the first page.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)addNewPageAtIndex:(PSPDFPageIndex)destinationPageIndex configuration:(nullable PSPDFNewPageConfiguration *)newPageConfiguration;

/// This method allows you to change how a certain type of annotation is included in the resulting document.
/// If all annotations should be changed, use `PSPDFAnnotationTypeAll` as the `annotationTypes`.
/// If finer control is needed, look at `modifyAnnotations:change:error:`.
- (void)modifyAnnotationsOfTypes:(PSPDFAnnotationType)annotationTypes change:(PSPDFAnnotationChange)annotationChange;

/// This method allows you to change the way certain annotations are included in the resulting document.
/// The annotations selected here take priority over the changes specified using `modifyAnnotationsOfType:change:` or `modifyFormsOfType:change:`.
///
/// @note This method might take a long time if you specify a lot of `annotations`. Use carefully.
- (BOOL)modifyAnnotations:(NSArray<PSPDFAnnotation *> *)annotations change:(PSPDFAnnotationChange)annotationChange error:(NSError **)error;

/// This method allows you to change the way certain form types are included in the resulting document.
/// For example, you can choose to only remove signature form elements.
///
/// @note This method requires the AcroForm component to be enabled for your license.
- (void)modifyFormsOfType:(PSPDFFormFieldType)formFieldType change:(PSPDFAnnotationChange)annotationChange;

/// Merges the `item` onto the page with index `destinationPageIndex`.
/// An item can be an image or another PDF page, see `ProcessorItem`.
/// For example, you can use this method to merge (add) the image of a PDF page into the destination page index of the specified document.
///
/// @note This method requires the Document Editor component to be enabled for your license.
- (void)mergeItem:(PSPDFProcessorItem *)item onPage:(PSPDFPageIndex)destinationPageIndex;

/// Adds drawing commands to every page.
///
/// The drawing block of type `PSPDFRenderDrawBlock` will be called for each page.
/// The drawing will get flattened on each page currently configured to be exported.
///
/// This will set up a similar drawing block as you'd get with calling `UIGraphicsBeginImageContext`.
/// The origin will be in the top-left of the visible area of the page.
/// The page rectangle passed to the drawing block has zero origin and the size has the page rotation applied.
///
/// @note Only the most recent rendering made using this method is drawn on the document.
- (void)drawOnAllCurrentPages:(PSPDFRenderDrawBlock)drawBlock NS_SWIFT_NAME(drawOnAllCurrentPages(_:));

// MARK: Comparison

/// Adjusts the stroke color of a given page.
///
/// @param pageIndex Index of the page, whose stroke color should be changed.
/// @param color The new color used to change the strokes.
///
/// @note This method requires the Comparison component to be enabled for your license.
- (void)changeStrokeColorOnPageAtIndex:(PSPDFPageIndex)pageIndex toColor:(UIColor *)color;

/// Merges a page from a source document with a page of the configuration's document. The source page will be auto-rotated to match the rotation of the configuration's document.
///
/// @param sourceDocument Document containing the page that should be merged.
/// @param password The password the source document is encrypted with. Use `nil` if the source document is not encrypted.
/// @param sourcePageIndex Index of the source document's page that should be used for merging.
/// @param destinationPageIndex Index of the destination document's page the source page should be merged into.
/// @param transform Defines how the merged page should be transformed. Use `identity` to leave it unchanged.
/// @param blendMode Defines how the two pages should be blended into each other.
///
/// @note `sourceDocument` can only contain a single data provider.
///
/// @note This method requires the Comparison component to be enabled for your license.
- (void)mergeAutoRotatedPageFromDocument:(PSPDFDocument *)sourceDocument password:(nullable NSString *)password sourcePageIndex:(PSPDFPageIndex)sourcePageIndex destinationPageIndex:(PSPDFPageIndex)destinationPageIndex transform:(CGAffineTransform)transform blendMode:(CGBlendMode)blendMode;

// MARK: Redaction

/// Applies all redaction annotations on all pages of the document.
/// Only takes effect once the document is processed with `PSPDFProcessor`.
///
/// @note This method requires the Redaction component to be enabled for your license.
- (void)applyRedactions;

/// Applies all redaction annotations on a specified page index of the document.
/// Only takes effect once the document is processed with `PSPDFProcessor`.
///
/// @param pageIndex Index of the page where all redaction annotations should be applied.
///
/// @note This method requires the Redaction component to be enabled for your license.
- (void)applyRedactionsOnPageAtIndex:(PSPDFPageIndex)pageIndex;

@end

@interface PSPDFProcessorConfiguration (Metadata)

/// Returns the metadata that will be written into the new document.
/// By default, this is set to the metadata of the original document.
///
/// @note On writing metadata to the new document, `PSPDFMetadataModDateKey` will be set to the current date and time and
/// `PSPDFMetadataProducerKey` will be set to `PSPDFKit`. You can overwrite these values by setting them with `updateMetadata`.
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *metadata;

/// Updates the metadata that will be saved in the generated PDF.
/// Any value you pass along here will either be replaced or inserted into the current metadata configuration.
/// See `PSPDFMetadataTitleKey` for examples of what keys to use.
///
/// @note This does not remove any metadata entries. See `clearMetadata`.
- (void)updateMetadata:(NSDictionary<NSString *, NSString *> *)metadata;

/// Clears any previous metadata.
///
/// @note `PSPDFMetadataModDateKey` and `PSPDFMetadataProducerKey` will still be set in the resulting PDF. See `metadata`.
- (void)clearMetadata;

@end

NS_ASSUME_NONNULL_END
