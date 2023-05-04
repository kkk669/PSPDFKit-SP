//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

/// An operation that reflows the content of a PDF document according to a
/// set of parameters.
///
/// Reflowing a PDF document means that the content will be more readable
/// on small screens, without needing zooming in and horizontal scrolling.
///
/// Use the `reflowCompletionBlock` to get the reflowed content.
PSPDF_SDK_CLASS_SWIFT(ReflowOperation)
@interface PSPDFReflowOperation : NSOperation <NSProgressReporting>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new reflow operation with a document to be reflowed.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// The document to be reflowed.
@property (nonatomic, readonly) PSPDFDocument *document;

/// Does not support pausing.
/// It does support cancellation, although you can also cancel the operation directly.
/// The `fractionCompleted` will be updated on a background queue.
@property (nonatomic, readonly) NSProgress *progress;

/// A block called when reflow finishes.
///
/// The block is passed either HTML or an error.
///
/// This will be typically called with an error if the reflow operation is cancelled although this is done as
/// a best effort so is not a guarantee. It’s possible this will be called with HTML even after cancellation.
///
/// This content is self-contained HTML that can can be rendered “as is” although it does not contain any styling.
@property (nonatomic, copy, nullable) void (^reflowCompletionBlock)(NSString *_Nullable htmlContent, NSError * _Nullable operationError);

@end

NS_ASSUME_NONNULL_END
