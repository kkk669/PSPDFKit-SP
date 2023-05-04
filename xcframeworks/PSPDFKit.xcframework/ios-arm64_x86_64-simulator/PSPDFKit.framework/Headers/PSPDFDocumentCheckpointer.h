//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

/// The strategy used by the `PSPDFDocumentCheckpointer` to save checkpoints.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFDocumentCheckpointingStrategy) {
    /// A checkpoint is never created automatically.
    PSPDFDocumentCheckpointingStrategyManual,
    /// A checkpoint is created periodically, if the document has unsaved changes.
    PSPDFDocumentCheckpointingStrategyTimed,
    /// A checkpoint is created as soon as the annotations in the document are modified, added, or removed.
    PSPDFDocumentCheckpointingStrategyImmediate
} NS_SWIFT_NAME(DocumentCheckpointingStrategy);

/// The notification posted when a checkpoint is saved. The object sending this is the document's checkpointer.
PSPDF_EXPORT NSNotificationName const PSPDFDocumentCheckpointSavedNotification;

/// The key set in `PSPDFDocumentCheckpointSavedNotification`'s userInfo that indicates (using a `BOOL` wrapped in a `NSNumber`) whether the checkpoint saved successfully or not.
PSPDF_EXPORT NSString *const PSPDFDocumentCheckpointSavedNotificationSuccessKey;

/// A checkpointer handles autosaving of annotations for recovery in case of a crash that occurs without saving.
/// A checkpoint is a small file that contains all the changes made to the document that haven't been saved.
/// The checkpoint is created according to the `strategy`. On a save of the document, it is automatically deleted.
///
/// @note Checkpoints are not supported for multi-provider `Document`s, or documents that are encrypted.
/// @note This class is thread safe.
/// @note You must not create instances of this class yourself, and instead use the `checkpointer` property on
/// `Document`.
PSPDF_CLASS_SWIFT(DocumentCheckpointer)
@interface PSPDFDocumentCheckpointer : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The mode in which checkpointing should be performed. Defaults to `PSPDFDocumentCheckpointingStrategyManual`.
@property (nonatomic) PSPDFDocumentCheckpointingStrategy strategy;

/// The document for which the receiver is created.
@property (nonatomic, weak, readonly) PSPDFDocument *document;

/// `true` if a checkpoint file is available at `checkpointLocation`, else `false`.
///
/// @warning This property performs disk I/O every time it is called.
@property (nonatomic, readonly) BOOL checkpointExists;

/// Call this method to save a checkpoint of the document's dirty objects. Any previous checkpoint will be deleted.
///
/// @param completionHandler The block to call after the checkpoint is saved. It is passed in `true` if the save completed
/// successfully, or there was nothing to save, else `false` is passed in.
/// If additional info about the failure is available, `error`, is passed in with that information.
/// Always called on the main queue.
- (void)saveCheckpointWithCompletionHandler:(void(^ _Nullable)(BOOL saved, NSError *_Nullable error))completionHandler;


/// Deletes the checkpoint file, if it exists.
///
/// @param completionHandler The block to call after the checkpoint is deleted. `true` if the checkpoint was successfully
/// deleted or one doesn't exist, else `false`.
/// If additional info about the failure is available, `error`, is passed in with that information.
/// Always called on the main queue.
- (void)deleteCheckpointWithCompletionHandler:(void(^ _Nullable)(BOOL deleted, NSError *_Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
