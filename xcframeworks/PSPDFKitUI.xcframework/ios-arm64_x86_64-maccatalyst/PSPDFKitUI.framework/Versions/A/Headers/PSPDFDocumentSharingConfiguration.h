//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>

#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKitUI/PSPDFPrintConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/// The possible file formats that can be used for sharing documents.
typedef NS_OPTIONS(NSUInteger, PSPDFDocumentSharingFileFormatOptions) {
    /// Share as PDF document
    PSPDFDocumentSharingFileFormatOptionPDF = 1 << 0,

    /// Offer to use the original file for sharing. See `originalFile` in `Document`.
    /// This can be used if, for example, the PDF is created from a converted Word document, and you'd like to offer the Word file for sharing.
    ///
    /// If enabled, neither page selection nor annotation options apply.
    ///
    /// @note If the document isn't backed by a file, then it is written to a file temporarily.
    PSPDFDocumentSharingFileFormatOptionOriginal = 1 << 1,

    /// Share the current PDF page as an image. For this option, page selection does not apply.
    ///
    /// When sharing a `PSPDFImageDocument`, the image is flattened is shared without embedded metadata.
    /// This reduces the image file size, but disallows further edits of embedded annotations.
    PSPDFDocumentSharingFileFormatOptionImage = 1 << 2,
} NS_SWIFT_NAME(DocumentSharingConfiguration.FileFormatOptions);

typedef NS_OPTIONS(NSUInteger, PSPDFDocumentSharingPagesOptions) {
    /// Only the page set in `pageIndex` of `PDFViewController`.
    /// I.e. the first page of the spread in the center of the viewport.
    PSPDFDocumentSharingPagesOptionCurrent = 1 << 0,

    /// Let the user select a range of pages to share.
    PSPDFDocumentSharingPagesOptionRange = 1 << 1,

    /// Send the whole document.
    PSPDFDocumentSharingPagesOptionAll = 1 << 2,

    /// Share all pages that contain annotations.
    PSPDFDocumentSharingPagesOptionAnnotated = 1 << 3
} NS_SWIFT_NAME(DocumentSharingConfiguration.PageOptions);

typedef NS_OPTIONS(NSUInteger, PSPDFDocumentSharingAnnotationOptions) {
    /// Save annotations in the PDF.
    ///
    /// Embed annotations into the PDF.
    ///
    /// @warning When using this option for printing, no annotations may be printed. This is a result of internal limitations of the printing system on iOS.
    /// @see [3rd-Party Compatibility](https://pspdfkit.com/guides/ios/miscellaneous/3rd-party-compatibility/)
    PSPDFDocumentSharingAnnotationOptionEmbed = 1 << 0,

    /// Render annotations into the PDF.
    PSPDFDocumentSharingAnnotationOptionFlatten = 1 << 1,

    /// Similar to `PSPDFDocumentSharingAnnotationOptionFlatten`, but renders annotations
    /// into the PDF with applied visibility settings for printing and converts notes to printable text.
    ///
    /// @note Use this option to ensure `PSPDFAnnotationFlagPrint` is correctly applied. If annotations
    /// are passed to the iOS printing service without previous flattening, visibility flags might not be
    /// honored correctly and annotations might appear different than in PSPDFKit.
    PSPDFDocumentSharingAnnotationOptionFlattenForPrint = 1 << 2,

    /// Save annotations + add summary. Not available on macOS.
    PSPDFDocumentSharingAnnotationOptionSummary = 1 << 3,

    /// Remove all annotations.
    PSPDFDocumentSharingAnnotationOptionRemove = 1 << 4
} NS_SWIFT_NAME(DocumentSharingConfiguration.AnnotationOptions);

/// The destination action or controller for the sharing flow.
typedef NSString *PSPDFDocumentSharingDestination NS_TYPED_ENUM NS_SWIFT_NAME(DocumentSharingConfiguration.Destination);

/// Printing the document.
PSPDF_EXPORT PSPDFDocumentSharingDestination const PSPDFDocumentSharingDestinationPrint;

/// The document is exported.
PSPDF_EXPORT PSPDFDocumentSharingDestination const PSPDFDocumentSharingDestinationExport;

/// The document is shared through the standard `UIActivityViewController` interface.
PSPDF_EXPORT PSPDFDocumentSharingDestination const PSPDFDocumentSharingDestinationActivity;

/// The document is shared through Messages.app directly. Attachment capabilities are required.
PSPDF_EXPORT PSPDFDocumentSharingDestination const PSPDFDocumentSharingDestinationMessages;

/// The document is shared through Mail.app.
PSPDF_EXPORT PSPDFDocumentSharingDestination const PSPDFDocumentSharingDestinationEmail;

/// The document is shared through `UIDocumentInteractionController`.
PSPDF_EXPORT PSPDFDocumentSharingDestination const PSPDFDocumentSharingDestinationOtherApplication;

PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(DocumentSharingConfigurationBuilder)
@interface PSPDFDocumentSharingConfigurationBuilder : PSPDFBaseConfigurationBuilder
@end

/// A `PSPDFDocumentSharingConfiguration` instance configures how the sharing view controller behaves, and what options it
/// lets the user customize.
PSPDF_CLASS_SWIFT(DocumentSharingConfiguration)
@interface PSPDFDocumentSharingConfiguration : PSPDFBaseConfiguration<PSPDFDocumentSharingConfigurationBuilder *>

/// Returns a configuration suitable for the given destination.
///
/// ## File Format Options
///
/// The Messages, Email, Other Application, Export, and Activity destinations, by default, have the following file format options enabled:
///
/// ```
/// PSPDFDocumentSharingFileFormatOptionPDF | PSPDFDocumentSharingFileFormatOptionImage | PSPDFDocumentSharingFileFormatOptionOriginal
/// ```
///
/// The Print destination has only one file format option enabled by default:
///
/// ```
/// PSPDFDocumentSharingFileFormatOptionPDF
/// ```
///
/// @note Please keep in mind that in the context of the Printing destination, the file format option is largely irrelevant.
///
/// ## Page Selection Options
///
/// Every destination has the following pages options selected by default:
///
/// ```
/// PSPDFDocumentSharingPagesOptionCurrent | PSPDFDocumentSharingPagesOptionRange | PSPDFDocumentSharingPagesOptionAll | PSPDFDocumentSharingPagesOptionAnnotated
/// ```
///
/// ## Annotation Options
///
/// The Messages, Email, Other Application, Export, and Activity destinations, by default, have the following annotation options enabled:
///
/// ```
/// PSPDFDocumentSharingAnnotationOptionEmbed | PSPDFDocumentSharingAnnotationOptionFlatten | PSPDFDocumentSharingAnnotationOptionRemove | PSPDFDocumentSharingAnnotationOptionSummary
/// ```
///
/// The Print destination has by default the following annotation options enabled:
///
/// ```
/// PSPDFDocumentSharingAnnotationOptionFlattenForPrint | PSPDFDocumentSharingAnnotationOptionRemove | PSPDFDocumentSharingAnnotationOptionSummary
/// ```
///
/// See `PSPDFDocumentSharingAnnotationOptionFlattenForPrint` for additional notes on printing.
+ (PSPDFDocumentSharingConfiguration *)defaultConfigurationForDestination:(PSPDFDocumentSharingDestination)destination;

/// The file formats the documents should be allowed to be shared in.
@property (nonatomic, readonly) PSPDFDocumentSharingFileFormatOptions fileFormatOptions;

/// Which pages from the documents should be shared.
@property (nonatomic, readonly) PSPDFDocumentSharingPagesOptions pageSelectionOptions;

/// How the annotations should be processed when sharing the documents.
@property (nonatomic, readonly) PSPDFDocumentSharingAnnotationOptions annotationOptions;

/// The destination where the documents are going to be shared to.
@property (nonatomic, readonly) PSPDFDocumentSharingDestination destination;

/// The print configuration to apply when sharing via the `.print` destination. Defaults to `nil`.
///
/// @note Due to API limitations, this is not used when printing is invoked via the .activity destination.
@property (nonatomic, readonly) PSPDFPrintConfiguration *printConfiguration;

/// Passed as the `applicationActivities` parameter when creating the `UIActivityViewController`.
///
/// Defaults to an empty array.
@property (nonatomic, copy, readonly) NSArray<UIActivity *> *applicationActivities;

/// Used for the activity action when the `UIActivityViewController` is displayed.
///
/// Defaults to `UIActivityTypeCopyToPasteboard`, `UIActivityTypeAssignToContact`,
/// `UIActivityTypePostToFacebook`, `UIActivityTypePostToTwitter`, `UIActivityTypePostToWeibo`.
///
/// The “Add to Photos” activity on Mac Catalyst will always be excluded because a system issue
/// means selecting that option disables almost all the app’s buttons and menu items. (FB9727325)
@property (nonatomic, copy, readonly) NSArray<UIActivityType> *excludedActivityTypes;

/// A closure that provides a string to describe each page in the page range picker.
///
/// The page range picker is shown for the option `DocumentSharingConfiguration.PageOptions.range`.
/// The closure is passed the index of the page to be described and the document that is being shared.
/// Page indexes start at 0.
///
/// By default this returns a string displaying `pageIndex + 1`.
/// Set this property to a custom closure to show the page label or any other custom description.
@property (nonatomic, copy, readonly) NSString * (^pageDescriptionProvider)(PSPDFPageIndex pageIndex, PSPDFDocument *document);

/// A block that provides a string to describe selected pages in the sharing UI.
///
/// The block is passed the selected range option, the selected page range if applicable, and the documents being shared.
/// `pagesOption` will always have exactly one bit set.
/// The `selectedPages` is not applicable when sharing all pages or annotated pages and should be ignored in those cases.
/// When sharing the current page, the `selectedPages` will contain exactly 1 index.
/// Sharing the current page or a specific range is only possible when sharing a single document, so `documents` can be assumed to contain a single entry in those cases.
///
/// To use the default PSPDFKit description in some cases, keep a reference to the original block and call through to it.
/// Set this property to a custom block to show the page label or any other custom description.
///
/// This block does *not* call through to `pageDescriptionProvider`. Set both blocks if you want to describe pages in a consistent way.
@property (nonatomic, copy, readonly) NSString * (^selectedPagesDescriptionProvider)(PSPDFDocumentSharingPagesOptions pagesOption, NSIndexSet *selectedPages, NSArray<PSPDFDocument *> *documents) NS_REFINED_FOR_SWIFT;

@end

@interface PSPDFDocumentSharingConfigurationBuilder ()

/// Defaults to `PSPDFDocumentSharingDestinationActivity`.
@property (nonatomic) PSPDFDocumentSharingDestination destination;

/// Defaults to `PSPDFDocumentSharingFileFormatOptionPDF | PSPDFDocumentSharingFileFormatOptionImage | PSPDFDocumentSharingFileFormatOptionOriginal`.
@property (nonatomic) PSPDFDocumentSharingFileFormatOptions fileFormatOptions;

/// Defaults to `PSPDFDocumentSharingPagesOptionCurrent | PSPDFDocumentSharingPagesOptionRange | PSPDFDocumentSharingPagesOptionAll | PSPDFDocumentSharingPagesOptionAnnotated`.
@property (nonatomic) PSPDFDocumentSharingPagesOptions pageSelectionOptions;

/// Defaults to `PSPDFDocumentSharingAnnotationOptionEmbed | PSPDFDocumentSharingAnnotationOptionFlatten | PSPDFDocumentSharingAnnotationOptionRemove | PSPDFDocumentSharingAnnotationOptionSummary`.
@property (nonatomic) PSPDFDocumentSharingAnnotationOptions annotationOptions;

/// Defaults to `PSPDFPrintConfiguration.defaultConfiguration`.
@property (nonatomic, nullable) PSPDFPrintConfiguration *printConfiguration;

/// Defaults to an empty array.
@property (nonatomic, copy) NSArray<UIActivity *> *applicationActivities;

/// Used for the activity action when the `UIActivityViewController` is displayed.
///
/// Defaults to `UIActivityTypeCopyToPasteboard`, `UIActivityTypeAssignToContact`,
/// `UIActivityTypePostToFacebook`, `UIActivityTypePostToTwitter`, `UIActivityTypePostToWeibo`.
///
/// The “Add to Photos” activity on Mac Catalyst will always be excluded because a system issue
/// means selecting that option disables almost all the app’s buttons and menu items. (FB9727325)
@property (nonatomic, copy) NSArray<UIActivityType> *excludedActivityTypes;

/// A closure that provides a string to describe each page in the page range picker.
///
/// The page range picker is shown for the option `DocumentSharingConfiguration.PageOptions.range`.
/// The closure is passed the index of the page to be described and the document that is being shared.
/// Page indexes start at 0.
///
/// By default this returns a string displaying `pageIndex + 1`.
/// Set this property to a custom closure to show the page label or any other custom description.
@property (nonatomic, copy) NSString * (^pageDescriptionProvider)(PSPDFPageIndex pageIndex, PSPDFDocument *document);

/// A block that provides a string to describe selected pages in the sharing UI.
///
/// The block is passed the selected range option, the selected page range if applicable, and the documents being shared.
/// `pagesOption` will always have exactly one bit set.
/// The `selectedPages` is not applicable when sharing all pages or annotated pages and should be ignored in those cases.
/// When sharing the current page, the `selectedPages` will contain exactly 1 index.
/// Sharing the current page or a specific range is only possible when sharing a single document, so `documents` can be assumed to contain a single entry in those cases.
///
/// To use the default PSPDFKit description in some cases, keep a reference to the original block and call through to it.
/// Set this property to a custom block to show the page label or any other custom description.
///
/// This block does *not* call through to `pageDescriptionProvider`. Set both blocks if you want to describe pages in a consistent way.
@property (nonatomic, copy) NSString * (^selectedPagesDescriptionProvider)(PSPDFDocumentSharingPagesOptions pagesOption, NSIndexSet *selectedPages, NSArray<PSPDFDocument *> *documents) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
