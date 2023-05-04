//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationGroupItem.h>

@class PSPDFAnnotationGroup;

@interface PSPDFAnnotationGroupItem ()

// Weak connection to the attached group, if any is set.
@property (nonatomic, weak) PSPDFAnnotationGroup *group;

// Amalgamation of type and variant.
@property (nonatomic, readonly) PSPDFAnnotationStateVariantID key;

@end
