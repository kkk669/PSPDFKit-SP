//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFAnnotationUpdate.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFAnnotationPresenting;
@class PSPDFDocumentProvider, PSPDFFileAnnotationProvider;

/// Collects annotations from the various `PSPDFAnnotationProvider` implementations.
///
/// Usually you want to add your custom PSPDFAnnotationProvider instead of subclassing this class.
/// If you subclass, use `overrideClass:withClass:` in `Document`.
///
/// This class will set the `documentProvider` on both annotation adding and retrieving. You don't have to handle this in your `annotationProvider` subclass.
PSPDF_CLASS_SWIFT(AnnotationManager)
@interface PSPDFAnnotationManager : NSObject<PSPDFAnnotationProviderChangeNotifier, PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the annotation manager with the associated `documentProvider`.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// The simplest way to extend `PSPDFAnnotationManager` is to register a custom `PSPDFAnnotationProvider`.
/// Remove the default `PSPDFFileAnnotationProvider` if you don't need file-based annotations.
///
/// By default, this array will contain the `fileAnnotationProvider`.
///
/// Important: Only the first annotation provider implementing `saveAnnotationsWithOptions:error:`
/// will be used for saving.
///
/// @note The order of the array is important.
/// The `PSPDFFileAnnotationProvider` also implements autodetected annotations.
///
/// @warning Only change this before the document is presented.
@property (nonatomic, copy) NSArray<id<PSPDFAnnotationProvider>> *annotationProviders;

/// Shortcut to the `PSPDFFileAnnotationProvider` if it exists in the annotationProviders array.
///
/// @note In earlier versions of PSPDFKit, the fileAnnotationProvider always existed.
/// We now allow deallocation if it is not used, and this property just checks the existing `annotationProviders` array and returns the first matching class.
/// This implies that we might not find an object anymore and may return nil.
@property (nonatomic, readonly, nullable) PSPDFFileAnnotationProvider *fileAnnotationProvider;

/// Return annotation array for specified page.
///
/// This method will be called OFTEN. Multiple times during a page display, and basically each time you're scrolling or zooming. Ensure it is fast.
/// This will query all annotationProviders and merge the result.
/// For example, to get all annotations except links, use `PSPDFAnnotationTypeAll &~ PSPDFAnnotationTypeLink` as type.
///
/// @note Fetching annotations may take a while. You can do this in a background thread.
- (nullable NSArray<__kindof PSPDFAnnotation *> *)annotationsForPageAtIndex:(PSPDFPageIndex)pageIndex type:(PSPDFAnnotationType)type;

/// Returns all annotations of all `annotationProviders`.

/// Returns dictionary `NSNumber`->`NSArray`. Only adds entries for a page if there are annotations.
///
/// @warning This might take some time if the annotation cache hasn't been built yet.
- (NSDictionary<NSNumber *, NSArray<__kindof PSPDFAnnotation *> *> *)allAnnotationsOfType:(PSPDFAnnotationType)annotationType;

/// YES if annotations are loaded for a specific page.
/// This is used to determine if annotationsForPageAtIndex:type: should be called directly or in a background thread.
- (BOOL)hasLoadedAnnotationsForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Any annotation that returns YES on `isOverlay` needs a view class to be displayed.
/// Will be called on all `annotationProviders` until someone doesn't return nil.
/// If no class is found, the view will be ignored.
- (nullable Class)annotationViewClassForAnnotation:(PSPDFAnnotation *)annotation;

/// Add `annotations` to the currently set annotation providers.
/// `pageIndex` is defined through the set page in each annotation object.
///
/// @param annotations An array of `PSPDFAnnotation` objects to be added.
/// @param options Insertion options. See `AnnotationManager.ChangeBehaviorKey`.
///
/// @note `PSPDFAnnotationManager` will query all registered annotationProviders until one returns YES on addAnnotations.
///
/// Will return false if no annotation provider can handle the annotations. (By default, the `PDFFileAnnotationProvider` will handle all annotations.)
///
/// If you're just interested in being notified, you can register a custom `annotationProvider` and set in the array before the file `annotationProvider`. Implement `addAnnotations:` and return NO. You'll be notified of all add operations.
- (BOOL)addAnnotations:(NSArray<PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options;

/// Inserts `annotation` to the currently set annotation providers at a specific z-index.
///
/// @param annotation A `PSPDFAnnotation` object to be added.
/// @param destinationIndex z-index the annotation should be inserted at.
/// @param options Insertion options (see `PSPDFAnnotationOption` constants in `PSPDFAnnotationManager.h`).
///
/// Will return NO if no annotation provider can handle the annotation. (By default, the `PSPDFFileAnnotationProvider` will handle all annotations.)
- (BOOL)insertAnnotation:(PSPDFAnnotation *)annotation atZIndex:(NSUInteger)destinationIndex options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options error:(NSError **)error;

/// Update annotations for a given page in a safe scope.
///
/// @note Currently only used for annotation z-index moving.
///
/// @param pageIndex The index of the page you are updating annotations on.
/// @param updateBlock Block that should perform all the annotation updates. `updateError` parameter should be used to report errors that occurred in the updateBlock.
- (BOOL)updateAnnotationsOnPageAtIndex:(PSPDFPageIndex)pageIndex error:(NSError **)error withUpdateBlock:(NS_NOESCAPE BOOL (^)(id<PSPDFAnnotationUpdate> annotationUpdate, NSError **updateError))updateBlock NS_REFINED_FOR_SWIFT;

/// Whether an annotation can be moved to a different z-index.
- (BOOL)canMoveAnnotation:(PSPDFAnnotation *)annotation error:(NSError **)error;

/// If the annotation can be moved by a specified z-index move.
- (BOOL)canExecuteZIndexMove:(PSPDFAnnotationZIndexMove)zIndexMove forAnnotation:(PSPDFAnnotation *)annotation;

/// Remove `annotations` from the pages they are registered in.
///
/// If the annotations have replies, those will be removed too. If you don’t want this copy the annotations you want to keep and add them back.
///
/// @param annotations An array of `Annotation` objects to be removed.
/// @param options Deletion options. See `AnnotationManager.ChangeBehaviorKey`.
///
/// @note Will return false if no annotationProvider can handle deleting the annotations. (By default, the `PDFFileAnnotationProvider` will handle all annotations.)
- (BOOL)removeAnnotations:(NSArray<PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options;

/// Will be called by PSPDF internally every time an annotation is changed.
/// Call will be relayed to all `annotationProviders`.
///
/// This method will be called on ALL annotations, not just the ones that you provided.
///
/// @note If you have custom code that changes annotations and you rely on the `didChangeAnnotation:` event, you need to call it manually.
///
/// `options` is used internally to determine of the file annotation provider should request an annotation update. (the `userInfo` notification dict will be forwarded.)
- (void)didChangeAnnotation:(__kindof PSPDFAnnotation *)annotation keyPaths:(NSArray<NSString *> *)keyPaths options:(nullable NSDictionary<NSString *, id> *)options;

/// Save annotations. (returning NO + eventually an error if it fails)
/// Saving will be forwarded to all annotation providers.
/// Usually you want to override the method in `PSPDFFileAnnotationProvider` instead.
- (BOOL)saveAnnotationsWithOptions:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)error;

/// Return YES if the manager requires saving.
///
/// @note You should first ensure the `state` property in the `annotationStateManager` to nil to commit any draft annotations.
@property (nonatomic, readonly) BOOL shouldSaveAnnotations;

/// Provided to the `PSPDFAnnotationProviders` via `PSPDFAnnotationProviderChangeNotifier`.
/// Will update any visible annotation.
- (void)updateAnnotations:(NSArray<PSPDFAnnotation *> *)annotations animated:(BOOL)animated;

/// Will parse the annotations in the array and add the ones that are included in the group (have the same grouping ID)
/// `annotations` need to be handled in the annotation manager.
- (NSArray<PSPDFAnnotation *> *)annotationsIncludingGroupsFromAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Change the protocol that's used to parse PSPDFKit-additions (links, audio, video). Defaults to `pspdfkit://`.
///
/// @note This will affect all parsers that generate PSPDFAction objects.
///
/// @warning Set this early on or manually clear the cache to update the parsers.
@property (nonatomic, copy) NSArray<NSString *> *protocolStrings;

/// The fileType translation table is used when we encounter `pspdfkit://` links (or whatever is set to `document.protocolStrings`)
/// Maps e.g. "mpg" to `PSPDFLinkAnnotationVideo`. (NSString -> NSNumber)
///
/// @note If you need file translation categorization that is not related to annotations,
/// use `PSPDFFileHelperGetFileCategory()` instead.
+ (NSDictionary<NSString *, NSNumber *> *)fileTypeTranslationTable;

/// Document provider for annotation parser.
@property (nonatomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFAnnotationManager (SubclassingHooks)

/// Searches the annotation cache for annotations that have the dirty flag set.
/// Dictionary key are the pages, object an array of annotations.
@property (nonatomic, readonly, nullable) NSDictionary<NSNumber *, NSArray<__kindof PSPDFAnnotation *> *> *dirtyAnnotations;

/// Filtered `fileTypeTranslationTable` that only returns video or audio elements.
+ (NSArray<NSString *> *)mediaFileTypes;

/// Returns the view class that can host the specific annotation subtype.
///
/// @note Usually you want to write an annotation provider and implement `annotationViewClassForAnnotation:` instead of subclassing.
- (nullable Class)defaultAnnotationViewClassForAnnotation:(PSPDFAnnotation *)annotation;

@end

NS_ASSUME_NONNULL_END
