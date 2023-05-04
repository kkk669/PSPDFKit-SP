//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentEditor.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDocumentEditor ()

/// Representative size for the document. Currently just the initial page size of page 0.
/// Remains constant. Even if we reorder pages and/or change the page size of the page at index 0.
@property (nonatomic, readonly) CGSize referenceSize;

/// Start an editing group. Every call to `- beginUpdates` needs to have a corresponding
/// call to `-commitUpdates` or `-commitUpdatesAndNotifyDelegates`.
- (void)beginUpdates;

/// Commits all the changes made to the document since the `-beginUpdates` call.
///
/// @warning Calling this method without a prior call to `-beginUpdates` will assert.
///
/// @return List of `PSPDFEditingChange`.
- (NSArray<PSPDFEditingChange *> *)commitUpdates;

/// Commits all the changes made to the document since the `-beginUpdates` call and notifies the document editor's delegates.
///
/// @warning Calling this method without a prior call to `-beginUpdates` will assert.
///
/// @return List of `PSPDFEditingChange`.
- (NSArray<PSPDFEditingChange *> *)commitUpdatesAndNotifyDelegates;

/// If changes were obtained via a completion block, and there's a need to notify the delegates about them also,
/// call this method.
///
/// @param changes     The changes to notify the delegates about.
- (void)notifyDelegatesAboutChanges:(NSArray<PSPDFEditingChange *> *)changes;

/// Discards all the changes made to the document since the `-beginUpdates` call.
///
/// @warning Calling this method without a prior call to `-beginUpdates` will assert.
///
/// @return List of the discarded `PSPDFEditingChange` objects.
- (NSArray<PSPDFEditingChange *> *)discardUpdates;

/// Performs the given block blocking actions on the editor.
- (void)performLocked:(void (^)(void))lockedScope;

/// The image loading queue for the current instance.
@property (nonatomic, readonly) NSOperationQueue *imageLoadingQueue;

@end

NS_ASSUME_NONNULL_END
