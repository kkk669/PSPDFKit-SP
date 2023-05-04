//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationToolbarConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotationGroupItem;

@interface PSPDFAnnotationToolbarConfiguration (PSPDFPresets)

/// Default toolbar configurations, designed for adaptivity.
+ (NSArray<PSPDFAnnotationToolbarConfiguration *> *)defaultConfigurations;

/// Creates an item for a tool. Simply forwards to the `PSPDFAnnotationGroupItem` factory method.
/// Exposed as a subclassing hook for PDF Viewer to mark some tools as Pro features.
+ (PSPDFAnnotationGroupItem *)itemWithType:(PSPDFAnnotationString)type variant:(nullable PSPDFAnnotationVariantString)variant configurationBlock:(nullable PSPDFAnnotationGroupItemConfigurationBlock)block;

@end

NS_ASSUME_NONNULL_END
