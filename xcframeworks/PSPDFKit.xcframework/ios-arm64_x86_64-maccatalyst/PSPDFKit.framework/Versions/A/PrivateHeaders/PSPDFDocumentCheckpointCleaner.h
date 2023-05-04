//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// A simple class that handles the cleaning of stale checkpoints.
NS_SWIFT_NAME(DocumentCheckpointCleaner)
PSPDF_TEST_EXPORT @interface PSPDFDocumentCheckpointCleaner : NSObject

/// The shared checkpoint cleaner object.
@property (class, nonatomic, readonly) PSPDFDocumentCheckpointCleaner *sharedInstance NS_SWIFT_NAME(shared);

/// Specifies whether a cleaning has occurred.
/// Set this to `false` if you want to force `-cleanCheckpointsInDirectory:` to clean up.
@property (nonatomic, getter=hasCleaned) BOOL cleaned;

/// Synchronously cleans the stale checkpoints in the directory. This method does nothing if `cleaned` is `true`.
///
/// @param checkpointsDirectory The URL for the directory in which the checkpoint files are stored. No other files should be stored here.
///
/// @warning This method should not be called on the main thread, as it blocks until I/O is complete.
- (void)cleanCheckpointsInDirectory:(NSURL *)checkpointsDirectory;

@end

NS_ASSUME_NONNULL_END
