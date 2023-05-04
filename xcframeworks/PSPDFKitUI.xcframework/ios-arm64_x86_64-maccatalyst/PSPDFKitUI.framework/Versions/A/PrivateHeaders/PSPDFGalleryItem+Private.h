//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFGalleryItem+Subclassing.h>

#import <PSPDFKit/PSPDFFileCategorizer.h>
#import <PSPDFKitUI/PSPDFGalleryItemConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/// A custom configuration for the item.
PSPDF_TEST_EXPORT PSPDFGalleryItemProperty const PSPDFGalleryItemPropertyConfiguration;

@interface PSPDFGalleryItem ()

/// Private factory methods that allow custom configurations.
+ (nullable NSArray<PSPDFGalleryItem *> *)itemsFromJSONData:(NSData *)data configuration:(nullable PSPDFGalleryItemConfiguration *)config error:(NSError **)outError;
+ (nullable PSPDFGalleryItem *)itemFromLinkAnnotation:(PSPDFLinkAnnotation *)annotation configuration:(nullable PSPDFGalleryItemConfiguration *)config error:(NSError **)error;

/// Returns the model class for a given file category.
+ (Class)itemClassFromFileCategory:(PSPDFFileCategory)category;

/// Overrides `error to be readwrite. See `-[PSPDFGalleryItem error]`.
@property (nonatomic, strong, readwrite, nullable) NSError *error;

/// The configuration of the item.
@property (nonatomic) PSPDFGalleryItemConfiguration *configuration;

/// Resolves the item into an item with different type while maintaining the appropriate state
/// information.
- (PSPDFGalleryItem *)resolveItemToDifferentItemClass:(Class)galleryItemClass;

@end

NS_ASSUME_NONNULL_END
