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
#import <PSPDFKit/PSPDFProcessorItem.h>
#import <PSPDFKit/PSPDFRotation.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(NewPageConfigurationBuilder)
@interface PSPDFNewPageConfigurationBuilder : PSPDFModel

/// The page size. This is `CGSizeZero` by default - the size of the first page in the resulting document will be used.
@property (nonatomic) CGSize pageSize;

/// Can only be 0, 90, 180 or 270. This is 0 by default.
@property (nonatomic) PSPDFRotation pageRotation;

/// The background color. If nil, the PDF page will not have a background color specified.
@property (nonatomic, nullable) UIColor *backgroundColor;

/// Add a image or PDF file to the page.
@property (nonatomic, nullable) PSPDFProcessorItem *item;

/// Allows you to specify page margins. This allows you to align items around the page margins instead of the edge of the document.
@property (nonatomic) UIEdgeInsets pageMargins;

@end

NS_ASSUME_NONNULL_END
