//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFNewPageConfigurationBuilder.h>
#import <PSPDFKit/PSPDFPageTemplate.h>
#import <PSPDFKit/PSPDFRectAlignment.h>
#import <PSPDFKit/PSPDFRotation.h>

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// This class configures a new page for the `PSPDFProcessor` or `PSPDFDocumentEditor`.
/// You can configure what type of page it should be and also add images or logos from a PDF.
PSPDF_CLASS_SWIFT(PDFNewPageConfiguration)
@interface PSPDFNewPageConfiguration : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Instantiates a new page configuration from the provided template and configuration block.
///
/// @param pageTemplate    The `PSPDFPageTemplate` to use for the new page configuration.
/// @param builderBlock    Block that'll be executed to build the new page configuration.
+ (instancetype)newPageConfigurationWithPageTemplate:(PSPDFPageTemplate *)pageTemplate builderBlock:(nullable void (^)(PSPDFNewPageConfigurationBuilder *builder))builderBlock;

/// The configured page size. If this is `CGSizeZero`, the size of the first page in the resulting document will be used.
@property (nonatomic, readonly) CGSize pageSize;

/// The configured page rotation. Can only be 0, 90, 180 or 270.
@property (nonatomic, readonly) PSPDFRotation pageRotation;

/// The configured background color. If nil, no background color will be set in the resulting page.
@property (nonatomic, readonly, nullable) UIColor *backgroundColor;

/// The page margins. This is mainly useful for aligning items.
@property (nonatomic, readonly) UIEdgeInsets pageMargins;

/// The tiled pattern that is configured.
@property (nonatomic, readonly, nullable) PSPDFPageTemplate *pageTemplate;

/// The `item` that will be added to the new page.
@property (nonatomic, readonly, nullable) PSPDFProcessorItem *item;

@end

NS_ASSUME_NONNULL_END
