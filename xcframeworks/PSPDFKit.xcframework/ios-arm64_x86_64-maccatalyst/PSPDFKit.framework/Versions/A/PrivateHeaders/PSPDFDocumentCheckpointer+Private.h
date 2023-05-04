//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentCheckpointer.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDocumentCheckpointer ()

/// Initializes an instance of the receiver.
///
/// @param document The document for which the receiver is being created.
- (instancetype)initWithDocument:(PSPDFDocument *)document;

/// The location of the checkpoint file. Use when instantiating the document provider.
///
/// @note This is nullable because it depends on the weak document reference.
@property (nonatomic, readonly, nullable) NSURL *checkpointLocation;

/// The interval to use between capturing checkpoints when using the timed strategy.
@property (nonatomic) NSTimeInterval timedCheckpointInterval;

/// Deletes all checkpoints stored on-disk.
+ (void)deleteAllCheckpoints;

/// The directory in which all checkpoints are stored.
@property (class, nonatomic, readonly) NSURL *checkpointsDirectory;

@end

// MARK: - Tests

/// The notification posted when a checkpoint is deleted. The object sending this is the document's checkpointer.
PSPDF_SDK_EXPORT NSNotificationName const PSPDFDocumentCheckpointerDeletedNotification;

NS_ASSUME_NONNULL_END
