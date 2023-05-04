//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFModelObject.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSURL *_Nullable (^PSPDFGalleryItemURLResolver)(NSURL *_Nullable unresolvedURL);
@class PSPDFGalleryItemConfigurationBuilder;

/// Every item can have a custom configuration that can be used to configure item-specific behavior.
/// It is currently used to inject context knowledge from a bigger scope (item URL resolving) into
/// the item while maintaining an abstract architecture.
PSPDF_TEST_CLASS_SWIFT(GalleryItemConfiguration)
@interface PSPDFGalleryItemConfiguration : PSPDFModel

/// Returns a copy of the default gallery configuration.
+ (instancetype)defaultConfiguration;

/// Returns a copy of the default gallery configuration. You can provide a `builderBlock` to change
/// the value of properties.
+ (instancetype)configurationWithBuilder:(void (^)(PSPDFGalleryItemConfigurationBuilder *builder))builderBlock;

/// The block used to resolve URLs. URL resolving is the process of replacing a custom URL
/// (e.g "pspdfkit://localhost/Bundle/something.jpg") into an URL that points to the actual content.
@property (nonatomic, readonly) PSPDFGalleryItemURLResolver URLResolver;

@end

@interface PSPDFGalleryItemConfigurationBuilder : NSObject
@property (nonatomic, copy) PSPDFGalleryItemURLResolver URLResolver;
@end

NS_ASSUME_NONNULL_END
