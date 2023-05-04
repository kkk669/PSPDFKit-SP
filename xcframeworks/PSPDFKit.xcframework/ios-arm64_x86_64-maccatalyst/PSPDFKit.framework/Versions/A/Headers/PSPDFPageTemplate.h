//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// The type of new page that will be added
typedef NS_CLOSED_ENUM(NSInteger, PSPDFNewPageType) {
    /// A empty page
    PSPDFNewPageTypeEmptyPage,

    /// A page with a pattern
    PSPDFNewPageTypeTiledPatternPage,

    /// A page from another document
    PSPDFNewPageTypeFromDocument,
} PSPDF_ENUM_SWIFT(PageTemplate.NewPageType);

typedef NSString *PSPDFTemplateIdentifier NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PageTemplate.Identifier);

/// Specifies a blank page.
PSPDF_EXPORT PSPDFTemplateIdentifier const PSPDFTemplateIdentifierBlank;

/// Specifies a pattern for a new page with a dot grid that is 5mm apart.
PSPDF_EXPORT PSPDFTemplateIdentifier const PSPDFTemplateIdentifierDot5mm;

/// Specifies a pattern for a new page with a grid that is 5mm apart.
PSPDF_EXPORT PSPDFTemplateIdentifier const PSPDFTemplateIdentifierGrid5mm;

/// Specifies a pattern for a new page with lines that are 5mm apart.
PSPDF_EXPORT PSPDFTemplateIdentifier const PSPDFTemplateIdentifierLines5mm;

/// Specifies a pattern for a new page with lines that are 7mm apart.
PSPDF_EXPORT PSPDFTemplateIdentifier const PSPDFTemplateIdentifierLines7mm;

/// Specifies a pattern for a new page with image.
PSPDF_EXPORT PSPDFTemplateIdentifier const PSPDFTemplateIdentifierImage;


/// A `PSPDFPageTemplate` helps `PSPDFNewPageConfiguration` configure a new page to
/// be added to a document correctly.
///
/// You can modify the templates available via `PDFConfiguration`, or setting the
/// `pageTemplates` property on the `PSPDFDocumentEditorConfiguration` builder.
PSPDF_CLASS_SWIFT(PageTemplate)
@interface PSPDFPageTemplate : PSPDFModel


/// Instantiates a new page template that will take the page at sourcePageIndex from the provided document
/// to insert into a new document.
///
/// @param document        The source document to get the template from.
/// @param sourcePageIndex The page index to extract the template from the document.
- (instancetype)initWithDocument:(PSPDFDocument *)document sourcePageIndex:(NSUInteger)sourcePageIndex;

/// Instantiates a new page template that will tile the a page at sourcePageIndex
/// from the provided document, to insert as a new page into another document.
///
/// @param document        The document the tiled pattern should be extracted from.
/// @param sourcePageIndex The page index to extract the template from the document.
- (instancetype)initWithTiledPatternFromDocument:(PSPDFDocument *)document sourcePageIndex:(NSUInteger)sourcePageIndex;

/// Instantiates a template with a given page type and identifier.
///
/// @param pageType    The page type to assign to this pattern.
/// @param identifier  Arbitrary identifier to assign to the template.
- (instancetype)initWithPageType:(PSPDFNewPageType)pageType identifier:(nullable PSPDFTemplateIdentifier)identifier;

/// A thumbnail representative of the page template.
///
/// For tiled templates, the resulting image is itself a pattern and needs to be rendered
/// as such.
///
/// @param completion  Block to call when the rendering succeeds or fails. If there was an error while rendering the thumbnail, the first parameter will be `nil`, and the second parameter will contain the reason.
- (void)renderThumbnailWithSize:(CGSize)size completion:(void (^)(UIImage * _Nullable, NSError * _Nullable))completion;

/// The type of page that will be created.
@property (nonatomic, readonly) PSPDFNewPageType pageType;

/// The template's identifier, if this is one of the predefined patterns.
@property (nonatomic, readonly, nullable) PSPDFTemplateIdentifier identifier;

/// The name of the template, not localized.
///
/// @warning Renaming internal default templates will assert.
@property (nonatomic, copy, nullable) PSPDFTemplateIdentifier templateName;

/// Localized version of the identifier, suitable for display.
@property (nonatomic, readonly) NSString *localizedName;

/// The template's resource URL. Can be nil.
///
/// This is the source PDF of `sourceDocument` or of the predefined page patterns PDFs.
@property (nonatomic, readonly, nullable) NSURL *resourceURL;

/// The template's source document, if it was instantiated with one. Can be nil.
@property (nonatomic, readonly, nullable) PSPDFDocument *sourceDocument;

/// The source document's page index to take the page from when processing the template.
@property (nonatomic, readonly, assign) NSUInteger sourcePageIndex;

@end

@interface PSPDFPageTemplate (Convenience)

/// Array containing the default set of templates provided by PSPDFKit.
/// This contains .blank, .imagePicker, .dot5mm, .grid5mm, .lines5mm, and .lines7mm.
@property (nonatomic, readonly, class) NSArray<PSPDFPageTemplate *> *defaultTemplates;

/// Instantiates a blank page template.
///
/// @return PSPDFPageTemplate instance with `PSPDFNewPageTypeEmptyPage` and `PSPDFTemplateIdentifierBlank`.
@property (nonatomic, readonly, class) PSPDFPageTemplate *blankTemplate;

/// Instantiates a page template that acts as a placeholder to let the user import an image to use as background for a new page.
///
/// This template has no actual content attached to it. When a user taps this option from the page background picker in `PSPDFNewPageViewController`, then an image can be imported from either the Photo Library or Camera.
///
/// To provide a default image to use with this template, set `PSPDFDocumentEditorConfiguration.selectedImage`.
///
/// @see +[PSPDFImagePickerController availableImagePickerSourceTypes];
@property (nonatomic, readonly, class) PSPDFPageTemplate *imagePickerTemplate;

@end

NS_ASSUME_NONNULL_END
