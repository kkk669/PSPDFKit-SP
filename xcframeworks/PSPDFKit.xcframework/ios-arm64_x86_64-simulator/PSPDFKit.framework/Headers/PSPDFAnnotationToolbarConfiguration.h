//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFModelObject.h>

@class PSPDFAnnotationGroup;

NS_ASSUME_NONNULL_BEGIN

/// Specifies a list the toolbar annotation items and their grouping.
/// The `AnnotationToolbar` accepts multiple configurations and will use the most matching one.
PSPDF_CLASS_SWIFT(AnnotationToolConfiguration)
@interface PSPDFAnnotationToolbarConfiguration : PSPDFModel

/// Creates a new configuration with the provided annotation groups.
- (instancetype)initWithAnnotationGroups:(NSArray<PSPDFAnnotationGroup *> *)annotationGroups NS_DESIGNATED_INITIALIZER;

/// The set annotation groups.
@property (nonatomic, readonly) NSArray<PSPDFAnnotationGroup *> *annotationGroups;

@end

NS_ASSUME_NONNULL_END
