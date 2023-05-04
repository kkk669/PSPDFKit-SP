//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Find the closest class that all `classes` are subclasses of. Assuming all
/// classes inherit from `NSObject`, this can only be `Nil` if the array is
/// empty.
///
/// ```
/// // This returns PSPDFAbstractLineAnnotation.
/// PSPDFClosestSuperclassAmong(@[PSPDFPolygonAnnotation.class, PSPDFPolyLineAnnotation.class]);
/// ```
PSPDF_SDK_EXPORT Class _Nullable PSPDFClosestSuperclassAmong(NSArray<Class> *classes);

/// Find the closest class that all `objects` are subclasses of. Assuming all
/// objects inherit from `NSObject`, this can only be `Nil` if the array is
/// empty.
///
/// ```
/// // This returns PSPDFFormElement.
/// PSPDFClosestSuperclassAmongObjects(@[buttonFormElement, textFieldFormElement]);
/// ```
PSPDF_SDK_EXPORT Class _Nullable PSPDFClosestSuperclassAmongObjects(NSArray *objects);

NS_ASSUME_NONNULL_END
