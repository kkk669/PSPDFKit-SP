//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

/// Protocol allowing annotation updates.
PSPDF_PROTOCOL_SWIFT(AnnotationUpdate)
@protocol PSPDFAnnotationUpdate <NSObject>

/// Annotations that are being worked with.
@property (nonatomic, readonly) NSArray<PSPDFAnnotation *> *annotations;

/// Moves an annotation from its current z-index to a new z-index.
/// A z-index of 0 means that the annotation is located at the bottom of the stack. The higher the z-index, the higher up to the top the annotation will be on the stack.
///
/// @param sourceIndex The index of the `PSPDFAnnotation` object to be moved.
/// @param destinationIndex z-index the annotation should be moved to.
- (BOOL)moveAnnotationAtZIndex:(NSUInteger)sourceIndex toZIndex:(NSUInteger)destinationIndex error:(NSError **)error;

/// Move the annotation by a specified z-index move.
- (BOOL)executeZIndexMove:(PSPDFAnnotationZIndexMove)zIndexMove forAnnotationAtZIndex:(NSUInteger)soureIndex error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
