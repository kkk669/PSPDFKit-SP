//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFContainerAnnotationProvider.h>
#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFLinkAnnotation;

/// An implementation of the `PSPDFAnnotationProvider` protocol that uses the PDF document as source/target to load/save
/// annotations. You almost always want to use the `PSPDFFileAnnotationProvider` in your `PSPDFAnnotationManager`. You can
/// also use this class inside a custom annotation provider, to parse PDF annotations once and then manage them in your
/// custom database.
///
/// @note Subclassing `PSPDFFileAnnotationProvider` will lead to slower `PSPDFProcessor` performance and **is strongly
/// discouraged**. This will be blocked in future versions.
PSPDF_CLASS_SWIFT(PDFFileAnnotationProvider)
@interface PSPDFFileAnnotationProvider : PSPDFContainerAnnotationProvider<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the file annotation provider with the document provider and uses the default path.
///
/// The default annotation path is created based on the following rules:
/// `self.documentProvider.document.cacheDirectory` + "annotations_%d.pspdfkit". The number is omitted in the
/// usual case with only one `documentProvider`. For documents with multiple providers, we write "annotations.pspdfkit", "annotations_2.pspdfkit", and so on.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Initializes the file annotation provider with the document provider and a custom file url (path).
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider fileURL:(nullable NSURL *)annotationFileURL NS_DESIGNATED_INITIALIZER;

/// Set to enable auto-detection of various link types. Defaults to `PSPDFTextCheckingTypeNone`.
///
/// @warning Detecting links might be an expensive operation.
@property (nonatomic) PSPDFTextCheckingType autodetectTextLinkTypes;

/// Performance optimized access.
///
/// This method uses a cache (and is of course thread safe). After the first expensive call, this method is basically free.
///
/// @note Soft deleted annotations are not returned from this method. They are, however, returned by `dirtyAnnotations`
/// until the document has been saved successfully.
/// @see `removeAnnotations:options:`
- (nullable NSArray<__kindof PSPDFAnnotation *> *)annotationsForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Adds the given annotations to the appropriate pages. Will accept any annotations.
///
/// Returns the annotations that have actually been added. These objects will be returned from `allAnnotations` until they
/// are removed from the receiver — either by passing them to `removeAnnotations:options:` or deleting them in the UI.
///
/// @param annotations An array of PSPDFAnnotation objects to be added.
/// @param options Insertion options (see the `PSPDFAnnotationOption...` constants in `PSPDFAnnotationManager.h`).
- (nullable NSArray<__kindof PSPDFAnnotation *> *)addAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options;

/// Removes the given annotations from the backing store and posts a `PSPDFAnnotationsRemovedNotification` for the deleted
/// objects on the main queue.
///
/// @note The annotations are soft-deleted. Meaning while they are removed from `allAnnotations`, they are returned from
/// `dirtyAnnotations` until the next successful call to `saveAnnotationsWithOptions:error:`.
///
/// @param annotations The annotations that have actually been removed.
/// @param options Deletion options (see `PSPDFAnnotationOption` constants in `PSPDFAnnotationManager.h`).
/// @return Returns the annotations that have been removed from `allAnnotations`.
- (nullable NSArray<__kindof PSPDFAnnotation *> *)removeAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options;

/// Removes all annotations and re-evaluates the document on next access.
- (void)clearCache;

@end

@interface PSPDFFileAnnotationProvider (Advanced)

/// Defaults to `PSPDFAnnotationTypeAll&~PSPDFAnnotationTypeLink`.
///
/// Change this to `PSPDFAnnotationTypeAll` to also allow saving link annotations. (Links are not saved by default because
/// some documents have a crazy high amount of link annotations which would make saving slow.)
///
/// @warning Never exclude `PSPDFAnnotationTypeWidget` - forms are specially handled.
@property (nonatomic) PSPDFAnnotationType saveableTypes;

/// What annotation types should be parsed from the PDF.
/// Defaults to `PSPDFAnnotationTypeAll`.
@property (nonatomic) PSPDFAnnotationType parsableTypes;

/// Path where annotations are being saved if saving to external file is enabled.
///
/// @note This was settable in earlier versions of PSPDFKit.
/// To change the annotation path, create a new file annotation provider object and set it on the annotation manager.
@property (nonatomic, readonly) NSString *annotationsPath;

/// The methods in this section provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: - Subclassing Hooks

/// Parses the page annotation dictionary and returns the newly created annotations.
///
/// @note **Important:** This method is meant to be overridden to customize annotations right after parsing. **You should
/// not call it yourself!** Instead, this is called as a part of `annotationsForPageAtIndex:` from within a
/// `performBlockForWritingAndWait:` block. It is therefore safe to call any method inside your override — including those
/// that have or require write semantics. Calling this method from within a `performBlockForReading:` block **is unsafe and
/// will likely deadlock!**
- (nullable NSArray<PSPDFAnnotation *> *)parseAnnotationsForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Saving code.
- (BOOL)saveAnnotationsWithOptions:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)error;

/// Loads annotations from an external file, returning `nil` and an error if that fails.
- (nullable NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *)loadAnnotationsWithError:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
