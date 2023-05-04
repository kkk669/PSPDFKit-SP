//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFAnnotation.h>

@class PSPDFAnnotationMapper;
@class PSPDFCoreAnnotation;
@class PSPDFDispatchQueue;
@class PSPDFDocumentProvider;
@class PDFIAssetManager;
@protocol PSPDFCustomConcurrentQueue;
@protocol PSPDFInstantAnnotationAttachmentResolver;

NS_ASSUME_NONNULL_BEGIN
/// We deliberately do **not** inherit `PSPDFContainerAnnotationProvider`:
/// Its locking mechanism does not allow recursion — which we need!
PSPDF_CLASS_SWIFT(InstantAnnotationProvider)
@interface PSPDFInstantAnnotationProvider : NSObject <PSPDFAnnotationProvider>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Sets up a new instance.
///
/// @note **Important:** This method’s signature **must not** be different from that of `PSPDFFileAnnotationProvider`!
/// Otherwise we cannot easily replace `PSPDFAnnotationManager`’s annotation provider.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// The document provider that’s associated with all annotations managed by this object.
@property (nonatomic, readonly, weak) PSPDFDocumentProvider *documentProvider;

/// The object used to resolve attachments for annotations that have them.
///
/// @note **Important:** This property needs to be set as early as possible — ideally, directly after
/// instantiation — and should not be tampered with afterwards.
@property (nonatomic, readonly, weak) id<PSPDFInstantAnnotationAttachmentResolver> attachmentResolver;

/// The annotation mapper to use.
///
/// Instant introduces additional annotation types, and it can be used alongside a traditional PSPDFKit integration.
/// Therefore, we cannot blindly replace the default class mapper when Instant gets loaded. Instead, we have to inject a
/// custom annotation mapper when the actual instant annotation provider is configured. This gives us an opportunity to
/// selectively replace certain annotation types, depending on a per instance basis.
/// This mechanism might be ported to other annotation providers if it turns out well.
///
@property (nonatomic, readonly) PSPDFAnnotationMapper *customAnnotationMapper;

/// Injects the required dependencies that cannot be passed at init time.
///
/// @param attachmentResolver   The object responsible to turn attachment identifiers into useful data.
/// @param annotationMapper     The object that maps annotation strings to annotation classes.
/// @param accessQueue          The dispatch queue to use for synchronization of the annotation properties with core.
- (void)finishSetupWithAttachmentResolver:(id<PSPDFInstantAnnotationAttachmentResolver>)attachmentResolver annotationMapper:(PSPDFAnnotationMapper *)annotationMapper propertyAccessQueue:(PSPDFDispatchQueue<PSPDFCustomConcurrentQueue> *)accessQueue;

/// Prevents other threads from accessing the receiver’s data, allowing for atomic modifications.
///
/// Can be called recursively. Each call, however, **must** be balanced by `unlockFromWriting` **on the same thread**.
/// Failing to do so can result in livelock, deadlock, or even crashes.
- (void)lockForWriting;

/// Balances a previous call to `lockForWriting` on the current thread.
///
/// Calling this method when the current thread does not own the write lock will lead to a crash.
- (void)unlockFromWriting;

/// Flushes all pending changes to core.
- (BOOL)needsLocking_flushPendingChangesToCore;

/// Replaces the cached annotations for the specified pages, and accumulates the changes using the block in order to
/// generate change messages.
///
/// @note This does not use `NSIndexSet` to avoid converting types coming from Djinni.
- (void)needsLocking_refreshCachedAnnotationsForPagesAtIndices:(NSSet<NSNumber *> *)pageIndices;

/// Returns the annotation with the given Instant identifier — if any.
- (nullable __kindof PSPDFAnnotation *)annotationWithIdentifier:(NSString *)identifier;

/// Returns the Instant identifier for the given annotation — if any.
+ (nullable NSString *)identifierForAnnotation:(PSPDFAnnotation *)annotation;

@end

// MARK: - PSPDFAnnotation Additions

/// Groups additional API on annotations, required by `PSPDFInstantAnnotationProvider`.
///
/// In order to customize annotations for the needs of Instant, without littering the general framework
/// with it, we need additional functionality on `PSPDFAnnotation`. The default implementation of this
/// API does nothing, but can be overridden for specific annotation type inside the Instant framework.
@interface PSPDFAnnotation (InstantAnnotationProvider)

/// Block that is called before attaching a core annotation to its respective backend.
///
/// The core annotation passed into the block is guaranteed to be associated with the `PSPDFAnnotation`
/// that returned it from `instant_preAttachActionWithAssetManager:error:`.
///
/// @param coreAnnotation The core annotation that has been created to back the `PSPDFAnnotation` that
/// is about to be added to the annotation provider’s backing store.
/// @see instant_preAttachActionWithAssetManager:error:
typedef void (^PSPDFInstantPreAttachAction)(PSPDFCoreAnnotation *coreAnnotation);

/// Returns a block that is called before finalizing the connection between the receiver and core.
///
/// The default implementation unconditionally returns a block that does nothing. Annotation classes
/// that require attachments need to override this method to import the data, and (on success) return a
/// block that associates the asset ID for that attachment with the core annotation.
///
/// Should importing the data, or any other possible preflight check fail, custom implementations
/// should fail by returning `nil`, and providing an appropriate error.
///
/// The block is called exactly once.
///
/// @param attachmentResolver The object to be used to import or retrieve any attached data.
/// @param error A pointer to be populated when this method returns `nil`.
/// @return A block that is called after the core annotation corresponding to the receiver has been
/// created, but just before establishing the connection between the two, or `nil` in case of an error.
- (nullable PSPDFInstantPreAttachAction)instant_preAttachActionWithAttachmentResolver:(id<PSPDFInstantAnnotationAttachmentResolver>)attachmentResolver error:(NSError **)error;

/// Called after the annotation has been created by the instant annotation provider, and the connection
/// to core has been established.
///
/// This override point gives the annotation an opportunity to load attachment data — such as images —
/// after its geometry and other basic properties have been restored.
///
/// @param attachmentResolver The object to use for retrieving attachment data.
- (void)instant_awakeAfterDeserialization:(id<PSPDFInstantAnnotationAttachmentResolver>)attachmentResolver;

@end

// MARK: -

@protocol PSPDFInstantAnnotationAttachmentResolver

/// Import the given data and return an opaque identifier that allows retrieving it later.
///
/// @param annotation The annotation that needs to import data.
/// @param data The data that should be important and attached to the annotation.
/// @param MIMEType The MIME type for the data that should be imported.
/// @param error A pointer to be populated with an error when the import fails.
/// @return An opaque identifier for the imported data that allows retrieving the data later.
/// @see annotation:localAssetForID:error:
- (nullable NSString *)annotation:(PSPDFAnnotation *)annotation importData:(NSData *)data withMIMEType:(NSString *)MIMEType error:(NSError **)error;

/// Returns the data of the given asset ID when locally available.
///
/// If the asset is known, but isn’t locally available, this method needs to fail with
/// `PSPDFInstantErrorAttachmentNotLoaded`. When the asset is unknown, it needs to fail with a
/// `PSPDFInstantErrorNoSuchAttachment`. Other errors, such as database errors, are possible as well.
///
/// @param annotation The annotation that needs to retrieve data.
/// @param assetID The opaque identifier as returned from `annotation:importData:withMIMEType:error`.
/// @param error A pointer to be populated when the data cannot be loaded.
/// @return The locally available data for the specified asset, or `nil`.
- (nullable NSData *)annotation:(PSPDFAnnotation *)annotation localAssetForID:(NSString *)assetID error:(NSError **)error;

/// Block that is called when an attachment download completes or fails.
///
/// @param data In the case of a successful download, the loaded data — otherwise nil.
/// @param error In the case of a failed download, an error describing what happened — otherwise nil.
typedef void (^PSPDFInstantAnnotationAttachmentResolution)(NSData *_Nullable data, NSError *_Nullable error);

/// Schedules a download for the asset with the given identifier.
///
/// When the download completes or fails, the attachment resolution is called with either the data
/// backing the asset or an error detailing why the download failed.
///
/// @param annotation The annotation in need of the asset data.
/// @param assetID The identifier for the asset data backing the annotation.
/// @param error Pointer to be populated when the download could not be scheduled.
/// @param attachmentResolution The block to be called when the download completes or fails.
- (nullable NSProgress *)annotation:(PSPDFAnnotation *)annotation scheduleDownloadForAssetID:(NSString *)assetID error:(NSError **)error resolution:(PSPDFInstantAnnotationAttachmentResolution)attachmentResolution;

@end

NS_ASSUME_NONNULL_END
