//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFProcessor;

/// The type implementing this protocol can receive updates from a `PSPDFProcessor`.
PSPDF_PROTOCOL_SWIFT(ProcessorDelegate)
@protocol PSPDFProcessorDelegate<NSObject>

@optional

/// Notifies the delegate that a page has completed processing.
///
/// @param processor   The `PSPDFProcessor` instance that's notifying the delegate.
/// @param currentPage An unsigned integer representing the page that just completed processing.
/// @param totalPages  The total number of pages that the `PSPDFProcessor` needs to process.
- (void)processor:(PSPDFProcessor *)processor didProcessPage:(NSUInteger)currentPage totalPages:(NSUInteger)totalPages;

/// Notifies the delegate that a request to cancel documents currently being processed has been received.
///
/// @note This method being called does not necessarily mean that the processing itself has stopped altogether, but that the cancellation has been requested and will happen sometime in the future.
///
/// @param processor   The `PSPDFProcessor` instance.
- (void)processorCancelled:(PSPDFProcessor *)processor;

@end

NS_ASSUME_NONNULL_END
