//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>

@class PSPDFAnnotation, PSPDFPage, PSPDFPageView, PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationCreatorStatus) {
    /// Creator is prepared, not yet started.
    PSPDFAnnotationCreatorStatusIdle,
    /// Creator is presenting UI, flow is in process.
    PSPDFAnnotationCreatorStatusPresenting,
    /// Creator finished, annotations are likely inserted.
    PSPDFAnnotationCreatorStatusFinished,
    /// Creator has been cancelled.
    PSPDFAnnotationCreatorStatusCancelled
} PSPDF_ENUM_SWIFT(AnnotationCreatorStatus);

/// Handles user-controlled creating annotations, usually with presenting UI.
///
/// @note This is a UI flow helper that deal with model creation and UI presentation.
/// This class only operates on the main thread.
PSPDF_TEST_CLASS_SWIFT(AnnotationCreator)
@interface PSPDFAnnotationCreator : NSObject <PSPDFOverrideProvider>

/// Initalizes the creator with a document page.
- (instancetype)initWithPage:(PSPDFPage *)page NS_DESIGNATED_INITIALIZER;

/// Uses the `pageView` to setup the creator's `pdfPage` and `visiblePDFRect`.
- (instancetype)initWithPageView:(PSPDFPageView *)pageView;

/// Initalizes the creator with a document and target page.
- (instancetype)initWithDocument:(PSPDFDocument *)document pageIndex:(PSPDFPageIndex)pageIndex;

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Status of the creator. KVO observable.
@property (nonatomic, readonly) PSPDFAnnotationCreatorStatus status;

/// The target page for the annotation insertion operation.
@property (nonatomic) PSPDFPage *pdfPage;

/// Annotation insertion point. If the rect is empty (zero area), then the annotation will be centered around the origin.
/// If `targetPDFRect` is set to `CGRectNull` (the default), the annotation is centered on the page.
@property (nonatomic) CGRect targetPDFRect;

/// The visible part of the current PDF page, used for centering.
@property (nonatomic) CGRect visiblePDFRect;

/// View Controller that is used for presenting/dismissing UI.
///
/// @note In most cases this will be the main `PDFViewController`.
@property (nonatomic, weak) UIViewController<PSPDFPresentationActions> *targetViewController;

/// Delegate for overriding.
@property (nonatomic, weak) id<PSPDFOverrideProvider> overrideDelegate;

/// Cancelling an active creator will dismiss any presented UI, optionally in an animated way.
///
/// @note Calling cancel will be a NOP if the creator's is already in `PSPDFAnnotationCreatorStatusCancelled` or `PSPDFAnnotationCreatorStatusFinished`.
- (void)cancelAnimated:(BOOL)animated NS_REQUIRES_SUPER;

/// Annotations that are inserted once the creator is finished. Can be KVO observed.
@property (nonatomic, copy, nullable) NSArray<PSPDFAnnotation *> *insertedAnnotations;

@end

/// Block to perform last minute customizations before actually inserting the annotation into the document.
typedef void (^PSPDFAnnotationCreatorPreInsertionHandler)(__kindof PSPDFAnnotation *annotationToInsert);

NS_ASSUME_NONNULL_END
