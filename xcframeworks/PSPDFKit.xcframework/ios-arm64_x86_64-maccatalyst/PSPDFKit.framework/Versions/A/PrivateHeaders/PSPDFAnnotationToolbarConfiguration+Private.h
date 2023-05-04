//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationToolbarConfiguration.h>

@class PSPDFAnnotationGroup;

@interface PSPDFAnnotationToolbarConfiguration ()

/// A subset of those `annotationGroups` that have at least one editable item.
@property (nonatomic, readonly) NSArray<PSPDFAnnotationGroup *> *editableAnnotationGroups;

/// Set editable annotation types on all annotation groups.
- (void)setEditableTypes:(NSSet<NSString *> *)editableTypes;

@end
