//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAnnotation, PSPDFDocumentProvider;
@protocol PSPDFAnnotationProviderChangeNotifier, PSPDFAnnotationProviderDelegate;

NS_ASSUME_NONNULL_BEGIN

/// Notification posted on the main thread when new annotations are added to the default `PSPDFContainerAnnotationProvider`.
/// The notification object is an `NSArray` containing the new `PSPDFAnnotation`s.
PSPDF_EXPORT NSNotificationName const PSPDFAnnotationsAddedNotification;

/// Notification posted on the main thread when annotations are removed from the default `PSPDFContainerAnnotationProvider`.
/// The notification object is an `NSArray` containing the removed `PSPDFAnnotation`s.
PSPDF_EXPORT NSNotificationName const PSPDFAnnotationsRemovedNotification;

/// A notification that should be posted after an annotation’s properties have been changed
/// so that PSPDFKit can re-render the annotation and update the UI.
///
/// If you change multiple properties on a single annotation at once then you can post this notification just once after all changes have been made.
///
/// PSPDFKit also posts this when it internally makes changes to an annotation.
///
/// @warning Only post this from the main thread!
///
/// @warning Don’t save the document during an observation callback for this notification.
///
/// The notification’s object property should be the `Annotation` instance that changed.
///
/// The notification’s `userInfo` may optionally contain the properties that were changed under the key `PSPDFAnnotationChangedNotificationKeyPathKey`.
PSPDF_EXPORT NSNotificationName const PSPDFAnnotationChangedNotification;

/// Set to YES to disable handling by views.
PSPDF_EXPORT NSString *const PSPDFAnnotationChangedNotificationIgnoreUpdateKey;

/// Key into the `userInfo` of a `.PSPDFAnnotationChanged` notification. Used to store the changed properties.
///
/// There should be an array of property names as strings stored under this key, which represent the properties that were changed.
/// The order of the elements in the array has no significance.
/// If no entry is stored under this key then please assume that any properties might have changed.
///
/// For example, if the `points` and `boundingBox` properties were both changed, then the `userInfo` might be like this:
///
/// ```
/// [PSPDFAnnotationChangedNotificationKeyPathKey: ["boundingBox", "points"]]
/// ```
///
/// @note Boolean properties will be prefixed with ‘is’. For example, the `deleted` property becomes `isDeleted`.
PSPDF_EXPORT NSString *const PSPDFAnnotationChangedNotificationKeyPathKey;

/// With the annotation provider, you can mix in PDF annotations from any source (custom database, web, etc)
/// Implement your custom provider class and register it in the `PSPDFAnnotationManager`.
///
/// (Make sure to register the provider in the PSPDFDocument's `didCreateDocumentProvider:` method, since a `Document` can have multiple `PSPDFDocumentProviders` and thus multiple `PSPDFAnnotationProviders` - and they can also be discarded on low memory situations.)
///
/// Ensure everything is thread safe here - methods will be called from any threads and sometimes even concurrently at the same time.
/// (If you're doing parsing, block and then in the queue re-check so you're not parsing multiple times for the same page)
///
/// @note You should always use `PSPDFContainerAnnotationProvider` as the base class for your custom annotation provider.
PSPDF_PROTOCOL_SWIFT(AnnotationProvider)
@protocol PSPDFAnnotationProvider<NSObject>

/// Return any annotations that should be displayed on that page.
///
/// @note This method needs to be accessible FROM ANY THREAD.
/// You can block here and do your processing but try to cache the result, this method is called often. (e.g. on every zoom change/re-rendering)
/// You're only getting the zero-based page index here. If needed, add a reference to `PSPDFDocumentProvider` during init or query the change notifier delegate.
- (nullable NSArray<__kindof PSPDFAnnotation *> *)annotationsForPageAtIndex:(PSPDFPageIndex)pageIndex;

@optional

/// Return YES if `annotationsForPageAtIndex:` is done preparing the cache, else NO.
/// PSPDFKit will preload/access `annotationsForPageAtIndex:` in a background thread and then re-access it on the main thread.
/// Defaults to YES if not implemented.
///
/// @warning You NEED to return YES on this after `annotationsForPageAtIndex:` has been accessed.
- (BOOL)hasLoadedAnnotationsForPageAtIndex:(PSPDFPageIndex)pageIndex;

/// Any annotation that returns YES on `isOverlay` needs a view class to be displayed.
/// Will be called on all `annotationProviders` until someone doesn't return nil.
///
/// @note If no class is found, the view will be ignored.
- (nullable Class)annotationViewClassForAnnotation:(PSPDFAnnotation *)annotation;

/// Additional behaviors when creating, changing, or deleting annotations.
///
/// These constants will primarily be used as keys in the `userInfo` dictionary of annotation specific notifications.
typedef NSString *PSPDFAnnotationOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(AnnotationManager.ChangeBehaviorKey);

/// Controls if overlay annotations should be animated. Only applies to overlay.
/// Defaults to YES if not explicitly set to NO.
///
/// @note This is defined on the model layer to allow passing through animated: parameters.
PSPDF_EXPORT PSPDFAnnotationOption const PSPDFAnnotationOptionAnimateView;

/// Prevents the insertion or removal notifications from being sent (use a BOOL NSNumber value).
///
/// @warning Disabling this option will lead to PSPDFKit not updating its state and views when adding new annotations, which can lead to issues presenting those annotations. Therefore, we don't recommend using this unless for cases where a `PSPDFAnnotationsAdded` notification is sent manually for timing reasons.
PSPDF_EXPORT PSPDFAnnotationOption const PSPDFAnnotationOptionSuppressNotifications;

/// Handle adding annotations. A provider can decide that it doesn't want to add this annotation, in that case either don't implement `addAnnotations:` at all or return nil.
/// Return all annotations that are handled by this annotation provider. `PSPDFAnnotationManager` will call all annotation providers in the list until all annotations have been processed.
///
/// @param annotations An array of PSPDFAnnotation objects to be added.
/// @param options Insertion options (see `PSPDFAnnotationOption` constants in `PSPDFAnnotationManager.h`).
/// @note The annotation provider is responsible for emitting the `PSPDFAnnotationsAddedNotification`.
- (nullable NSArray<__kindof PSPDFAnnotation *> *)addAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options;

/// Handle inserting an annotation. A provider can decide that it doesn't want to add this annotation, in that case either don't implement `insertAnnotation:` at all or return NO.
/// Return YES if inserting the annotation was successful, NO otherwise. `PSPDFAnnotationManager` will call all annotation providers in the list until the annotation has been successfully added.
///
/// @param annotation An `PSPDFAnnotation` object to be inserted.
/// @param destinationIndex The z-index the annotation should be inserted at.
/// @param options Insertion options (see `PSPDFAnnotationOption` constants in `PSPDFAnnotationManager.h`).
/// @note The annotation provider is responsible for emitting the `PSPDFAnnotationsAddedNotification`.
- (BOOL)insertAnnotation:(PSPDFAnnotation *)annotation atZIndex:(NSUInteger)destinationIndex options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options error:(NSError **)error;

/// Defines if this annotation provider supports z-index moving of annotations.
/// If this is not implemented, NO is assumed.
@property (nonatomic, readonly) BOOL allowAnnotationZIndexMoves;

/// Handle removing annotations. A provider can decide that it doesn’t want to remove some annotations. In that case, omit those annotations from the returned array.
///
/// @param annotations An array of PSPDFAnnotation objects to be removed.
/// @param options Deletion options (see `PSPDFAnnotationOption` constants in `PSPDFAnnotationManager.h`).
/// @note The annotation provider is responsible for emitting the `PSPDFAnnotationsRemovedNotification`.
- (nullable NSArray<__kindof PSPDFAnnotation *> *)removeAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options;

/// PSPDFKit requests a save. Can be ignored if you're instantly persisting.
/// Event is e.g. fired before the app goes into background, or when `PDFViewController` is dismissed.
/// Return NO + error if saving failed.
- (BOOL)saveAnnotationsWithOptions:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)error;

/// Return YES if the provider requires saving.
@property (nonatomic, readonly) BOOL shouldSaveAnnotations;

/// Return all "dirty" = unsaved annotations.
@property (nonatomic, readonly, nullable) NSDictionary<NSNumber *, NSArray<__kindof PSPDFAnnotation *> *> *dirtyAnnotations;

/// Callback if an annotation has been changed by PSPDFKit.
/// This method will be called on ALL annotations, not just the ones that you provided.
- (void)didChangeAnnotation:(PSPDFAnnotation *)annotation keyPaths:(NSArray<NSString *> *)keyPaths options:(nullable NSDictionary<NSString *, id> *)options;

/// Provides a back-channel to PSPDFKit if you need to change annotations on the fly. (e.g. new changes from your server are coming in)
@property (atomic, weak) id<PSPDFAnnotationProviderChangeNotifier> providerDelegate;

/// Set this delegate to be notified of annotation saving related events. Automatically synthesized on `PSPDFContainerAnnotationProvider`.
@property (nonatomic, weak) id<PSPDFAnnotationProviderDelegate> delegate;

@end

/// To be notified on any changes PSPDFKit does on your annotations, implement this notifier.
/// It will be set as soon as your class is added to the `annotationManager`.
PSPDF_PROTOCOL_SWIFT(AnnotationProviderChangeNotifier)
@protocol PSPDFAnnotationProviderChangeNotifier<NSObject>

/// Call this from your code as soon as annotations change.
/// This method can be called from any thread. (try to avoid the main thread)
///
/// @warning Don't dynamically change the value that `isOverlay` returns, else you'll confuse the updater.
- (void)updateAnnotations:(NSArray<PSPDFAnnotation *> *)annotations animated:(BOOL)animated;

/// Query to get the document provider if this annotation provider is attached to the `PSPDFAnnotationManager`.
@property (nonatomic, readonly, nullable) PSPDFDocumentProvider *parentDocumentProvider;

@end

/// Delegate for callbacks related to annotation saving.
PSPDF_PROTOCOL_SWIFT(AnnotationProviderDelegate)
@protocol PSPDFAnnotationProviderDelegate<NSObject>

@optional

/// Called after saving was successful.
/// If there are no dirty annotations, delegates will not be called.
///
/// @note `annotations` might not include all changes, especially if annotations have been deleted or an annotation provider didn't implement dirtyAnnotations.
///
/// @warning This is called after document providers finish saving annotations, but before the document is saved to disk. Use `pdfDocumentDidSave:` callback if you want to perform any actions after all changes have beed saved to disk.
///
/// @warning Might be called from a background thread.
- (void)annotationProvider:(id<PSPDFAnnotationProvider>)annotationProvider didSaveAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations;

/// Called after saving annotations failed. When an error occurs, annotations will not be the complete set in multi-file documents.
///
/// @note `annotations` might not include all changes, especially if annotations have been deleted or an annotation provider didn't implement `dirtyAnnotations`.
///
/// @warning Might be called from a background thread.
- (void)annotationProvider:(id<PSPDFAnnotationProvider>)annotationProvider failedToSaveAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations error:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
