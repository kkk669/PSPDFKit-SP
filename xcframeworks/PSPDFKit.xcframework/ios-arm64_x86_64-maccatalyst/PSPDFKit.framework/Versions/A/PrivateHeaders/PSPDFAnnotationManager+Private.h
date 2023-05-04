//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationManager.h>

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFAnnotationViewMapper.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAnnotationManager ()

/// The object to use as the `annotationViewMapper` unless specified otherwise.
///
/// @note If you plan on replacing the default value, do so at a well-defined time in the application
/// lifecycle. **Implementations of `+load` or `+initialize` are not suitable for that purpose!**
@property (nullable, nonatomic, class) id<PSPDFAnnotationViewMapper> defaultAnnotationViewMapper;

/// The object used to look up the appropriate class for displaying an annotation.
///
/// Will be set to the `PSPDFAnnotationManager.defaultAnnotationViewMapper` during initialization. In
/// general, this property should only be `nil` when you do not link the PSPDFKitUI framework.
@property (nonatomic, nullable) id<PSPDFAnnotationViewMapper> annotationViewMapper;

/// Moves an annotation from its current z-index to a new z-index.
/// A z-index of 0 means that the annotation is located at the bottom of the stack. The higher the z-index, the higher up to the top the annotation will be on the stack.
///
/// @param sourceIndex Index of annotation that should be moved.
/// @param pageIndex Page index the annotation is located on.
/// @param destinationIndex z-index the annotation should be moved to.
///
/// @note This should only be called in an update block via `PSPDFAnnotationUpdate`.
- (BOOL)moveAnnotationAtZIndex:(NSUInteger)sourceIndex ofPageAtIndex:(PSPDFPageIndex)pageIndex toZIndex:(NSUInteger)destinationIndex error:(NSError **)error;

/// Get the current z-index for a specific annotation.
- (NSUInteger)zIndexForAnnotation:(PSPDFAnnotation *)annotation;

/// Whether all annotation providers are entirely backed by Core. We can be a bit more optimal in saving when entirely backed by Core.
@property (nonatomic, readonly) BOOL isEntirelyBackedByCore;

/// Tells the annotation providers to flush any annotation changes to their store if possible
- (void)flushPendingChangesToCore;

@end

NS_ASSUME_NONNULL_END
