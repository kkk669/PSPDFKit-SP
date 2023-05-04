//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFViewState.h>
#import <PSPDFKit/PSPDFAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFViewState ()

/// The view's selected annotations UUIDs.
@property (nonatomic, readonly, nullable) NSArray<NSString *> *selectedAnnotationNames;

/// Whether the stored `viewPort` does not have the page transform applied.
///
/// The viewport used untransformed coordinates before 8.0.
/// This property is YES when old archives are read, in which
/// case the page transform should be applied to `viewPort`.
@property (nonatomic, readonly) BOOL requiresCoordinateTransformation;

/// The currently active state of the annotation state manager.
@property (nonatomic, nullable) PSPDFAnnotationStateVariantID annotationState;

@end

NS_ASSUME_NONNULL_END
