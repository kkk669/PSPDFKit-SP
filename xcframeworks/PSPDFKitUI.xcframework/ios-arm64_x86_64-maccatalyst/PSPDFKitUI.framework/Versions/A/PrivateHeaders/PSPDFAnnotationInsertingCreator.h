//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationCreator.h>

@class PSPDFAnnotation, PSPDFPage, PSPDFAnnotationSet;

NS_ASSUME_NONNULL_BEGIN

/// This creator is to be used to insert annotations that are already created.
/// The annotations inserted by this class will always be centered around the `targetPDFRect`'s center.
@interface PSPDFAnnotationInsertingCreator : PSPDFAnnotationCreator

/// Initializes a `PSPDFAnnotationInsertingCreator` with a single annotation that is to be inserted.
///
/// @param annotation The annotation that is to be inserted.
/// @param page The `PSPDFPage` object into which the annotation is to be inserted.
/// @param targetPDFRect The rect, in PDF coordinates, at which the annotation is to be inserted. (See `-performInsertion`).
/// @return An instance of `PSPDFAnnotationInsertingCreator`.
///
/// @note The annotation is centered around the targetPDFRect's center when this initializer returns.
- (instancetype)initWithAnnotation:(PSPDFAnnotation *)annotation page:(PSPDFPage *)page targetPDFRect:(CGRect)targetPDFRect NS_DESIGNATED_INITIALIZER;

/// Initializes a `PSPDFAnnotationInsertingCreator` with a set of annotations that are to be inserted.
///
/// @param annotationSet The set of annotations that are to be inserted.
/// @param page The `PSPDFPage` object into which the annotations are to be inserted.
/// @param targetPDFRect The rect, in PDF coordinates, where the annotations are to be inserted. (See `-performInsertion`).
/// @return An instance of `PSPDFAnnotationInsertingCreator`.
///
/// @note The annotations in the set are centered around the targetPDFRect's center when this initializer returns.
- (instancetype)initWithWithAnnotationSet:(PSPDFAnnotationSet *)annotationSet page:(PSPDFPage *)page targetPDFRect:(CGRect)targetPDFRect NS_DESIGNATED_INITIALIZER;

/// Inserts the annotations that the receiver was initialized with.
/// The annotations are centered around the `targetPDFRect`'s center.
///
/// If this method has been already been called, then calling it again does nothing.
- (void)performInsertion;

@end

NS_ASSUME_NONNULL_END
