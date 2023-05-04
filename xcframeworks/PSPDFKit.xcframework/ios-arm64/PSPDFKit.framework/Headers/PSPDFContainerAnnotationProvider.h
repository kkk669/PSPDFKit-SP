//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationProvider.h>

NS_ASSUME_NONNULL_BEGIN

/// Default container for annotations. It's highly recommended that you use this class as your base class if you implement
/// a custom annotation provider in order to leverage built-in functionality that ensures annotation changes are correctly
/// propagated throughout the framework.
///
/// You must use this base class to support refreshing annotations in response to an external change, like from
/// `-[PSPDFDocumentProvider setRotationOffset:forPageAtIndex:]`. To put that in other words, an annotation provider *must* subclass
/// this class for temporary page rotations to work correctly.
PSPDF_CLASS_SWIFT(PDFContainerAnnotationProvider)
@interface PSPDFContainerAnnotationProvider : NSObject <PSPDFAnnotationProvider>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// Associated `documentProvider`.
@property (nonatomic, weak, readonly) PSPDFDocumentProvider *documentProvider;

/// The methods in this section provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
// MARK: - Subclassing Hooks

/// Whether this class tracks removed annotations as soft deletions — defaults to `true`.
///
/// When `true`, instances of this class track annotations that have been passed to `removeAnnotations:options:` in the
/// `dirtyAnnotations` until `clearNeedsSaveFlag` is called. When implementing your own annotation provider, you can opt
/// out of this behavior by overriding this class method to return `false`.
@property (nonatomic, class, readonly) BOOL shouldTrackDeletions;

/// Clears `shouldSaveAnnotations`, disposes of any soft deleted annotations, and clears the “dirty” flag of all the
/// receiver’s annotations.
///
/// Adding, removing, and updating annotations not only marks the annotation itself as “dirty”, but also triggers an
/// internal flag that the provider requires saving. This method clears those flags and disposes of any “soft deleted”
/// annotations. The receiver is left without `dirtyAnnotations` and `shouldSaveAnnotations` returns `false` until the next
/// annotation change.
///
/// @warning This method **must be called inside a write block!** Failing to do so will (at best) crash your program. At
/// worst it will silently corrupt user data.
- (void)clearNeedsSaveFlag;

/// Directly accesses the annotation cache used internally.
/// Be extremely careful when accessing this, and use the locking methods.
@property (nonatomic, readonly) NSMutableDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *annotationCache;

/// Called before new annotations are inserted. Subclass to perform custom actions.
///
/// This method is called inside of a writing block. You can therefore safely inspect and even modify the `annotationCache`
/// directly.
- (void)willInsertAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

/// Allows synchronization with the internal reader queue.
///
/// This method is safe to call inside of a write block. That is a block passed into `performBlockForWriting:` or
/// `performBlockForWritingAndWait:`. The reverse is not necessarily true. Specifically…
///
/// @warning Calling `performBlockForWritingAndWait:` inside of the read block is unsafe, and **will almost certainly cause
/// deadlock**! This includes making calls that have write semantics and are not documented to require to be called inside
/// a write block.
- (void)performBlockForReading:(NS_NOESCAPE void (^)(void))block NS_REFINED_FOR_SWIFT;

/// Allows synchronization with the internal writer queue.
///
/// This method is safe to call at any time — including inside a read block. The exact execution characteristics may be
/// surprising, though:
///
/// 1. When this method is called inside a write block, the block parameter is executed inline.
/// 2. When this method is called in any other context, the block parameter is executed _asynchronously_ on a background
/// queue.
/// 3. When executed, the block parameter will have writer status. It is therefore safe to call any instance method of this
/// class inside the block.
- (void)performBlockForWriting:(void (^)(void))block NS_REFINED_FOR_SWIFT;

/// Allows synchronization with the internal writer queue and blocks until the block is processed.
///
/// When executed, the block parameter will have writer status. It is therefore safe to call any instance method of this
/// class inside the block. This specifically includes calls to `performBlockForWritingAndWait:` and calls to
/// `performBlockForReading:`. The reverse, however, is not true. Specifically…
///
/// @warning Calling this method as part of a block passed to `performBlockForReading:` **will almost certainly cause
/// deadlock**!
- (void)performBlockForWritingAndWait:(NS_NOESCAPE void (^)(void))block NS_REFINED_FOR_SWIFT;

/// Modify the internal store. Optionally appends annotations instead of replacing them.
///
/// @note The page set in the `annotations` need to match the `page`.
/// @note **Subclassing Note:** If you override this method and modify additional internal state of your subclass, wrap the
/// modifications as well as the call to `super` in a write block. Otherwise you risk breaking atomicity of the operation.
- (void)setAnnotations:(NSArray<PSPDFAnnotation *> *)annotations forPageAtIndex:(PSPDFPageIndex)pageIndex append:(BOOL)append;

/// Set annotations, evaluate the page value of each annotation.
///
/// @note **Subclassing Note:** If you override this method and modify additional internal state of your subclass, wrap the
/// modifications as well as the call to `super` in a write block. Otherwise you risk breaking atomicity of the operation.
- (void)setAnnotations:(NSArray<PSPDFAnnotation *> *)annotations append:(BOOL)append;

/// @note **Subclassing Note:** If you override this method and modify additional internal state of your subclass, wrap the
/// modifications as well as the call to `super` in a `performLockForWritingAndWait:`. Otherwise you risk breaking
/// atomicity of the operation or deadlock.
- (nullable NSArray<__kindof PSPDFAnnotation *> *)addAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options NS_REQUIRES_SUPER;

/// As of PSPDFKit 7.4, `PSPDFContainerAnnotationProvider` tracks annotations passed into this method as deleted, unless
/// you override `+shouldTrackDeletions` to return `false`. So when you are inheriting from this class, you **must** call
/// `clearNeedsSaveFlag` when implementing `saveAnnotationsWithOptions:error:` to purge those deleted annotations.
///
/// @note **Subclassing Note:** If you override this method and modify additional internal state of your subclass, wrap the
/// modifications as well as the call to `super` in a `performLockForWritingAndWait:`. Otherwise you risk breaking
/// atomicity of the operation or deadlock.
///
/// @param annotations The annotations to delete.
/// @param options Options for the deletion. For the full set of options, see `PSPDFAnnotationOption` constants in PSPDFAnnotationManager.h.
- (nullable NSArray<__kindof PSPDFAnnotation *> *)removeAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations options:(nullable NSDictionary<PSPDFAnnotationOption, id> *)options NS_REQUIRES_SUPER;

/// Remove all annotations (effectively clears the cache).
///
/// @note **Subclassing Note:** If you override this method and modify additional internal state of your subclass, wrap the
/// modifications as well as the call to `super` in a write block. Otherwise you risk breaking atomicity of the operation.
/// @param options Deletion options (see the  (see `PSPDFAnnotationOption` constants in `PSPDFAnnotationManager.h`).
- (void)removeAllAnnotationsWithOptions:(NSDictionary<PSPDFAnnotationOption, id> *)options;

/// Returns the cached annotations of all pages in one array.
///
/// This will not force loading if the provider lazily loads annotations into the cache in `annotationsForPageAtIndex:`.
/// Both `PSPDFFileAnnotationProvider` and `PSPDFXFDFAnnotationProvider` do this lazy loading.
///
/// @note **Subclassing Note:** This is a reading operation. If you need to override this method to query mutable state,
/// wrap these queries as well as the call to `super` in a read block. Otherwise you risk breaking atomicity of the
/// operation.
@property (nonatomic, readonly) NSArray<PSPDFAnnotation *> *allAnnotations;

/// Returns cached annotations as a page->annotations per page dictionary.
///
/// This will not force loading if the provider lazily loads annotations into the cache in `annotationsForPageAtIndex:`.
/// Both `PSPDFFileAnnotationProvider` and `PSPDFXFDFAnnotationProvider` do this lazy loading.
///
/// @note **Subclassing Note:** This is a reading operation. If you need to override this method to query mutable state,
/// wrap these queries as well as the call to `super` in a read block. Otherwise you risk breaking atomicity of the
/// operation.
@property (nonatomic, readonly) NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *annotations;

/// May be used to override the annotation cache directly. Faster than using `setAnnotations:`.
///
/// @note **Subclassing Note:** If you override this method and modify additional internal state of your subclass, wrap the
/// modifications as well as the call to `super` in a write block. Otherwise you risk breaking atomicity of the operation.
- (void)setAnnotationCacheDirect:(NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *)annotationCache;

@end

NS_ASSUME_NONNULL_END
