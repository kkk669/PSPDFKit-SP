//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

///Produces a summary of the annotations in a document.
PSPDF_CLASS_SWIFT(AnnotationSummarizer)
@interface PSPDFAnnotationSummarizer : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initialize the annotation summarizer with a document.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// The document to generate the annotation summary out of.
@property (nonatomic, readonly) PSPDFDocument *document;

/// Returns the annotation summary as a formatted string for the indexes in `pages`.
///
/// @note If the summary generation is cancelled while this method is executing, it will return `nil`.
///
/// @param pages   The pages to scan for annotations to generate the summary.
- (nullable NSAttributedString *)annotationSummaryForPages:(NSIndexSet *)pages;

/// Returns the annotation summary as a formatted string for the indexes in `pages`, and reports progress.
///
/// @note If the summary generation is cancelled while this method is executing, it will return `nil`.
///
/// @param pages       The pages to scan for annotations to generate the summary.
/// @param progressBlock     Block to observe the progress of summarizing the annotations.
- (nullable NSAttributedString *)annotationSummaryForPages:(NSIndexSet *)pages progress:(void (^ _Nullable)(NSUInteger currentIndex, CGFloat percentage))progressBlock;

/// Cancels the annotation summary generation, if currently in progress.
- (void)cancelSummaryGeneration;

@end

#if TARGET_OS_IOS
@interface PSPDFAnnotationSummarizer (FileSupport)
/// Generates a PDF file with the annotation summary for the document at the provided pages.
///
/// @param pages               The pages to scan for annotations to generate the summary.
/// @param completionBlock     Called when the temporary file creation has either completed or failed.
- (void)temporaryPDFFileURLForPages:(NSIndexSet *)pages completionBlock:(void (^)(NSURL * _Nullable fileURL, NSError * _Nullable error))completionBlock;

/// Generates a PDF file with the annotation summary for the document at the provided pages.
///
/// @param pages               The pages to scan for annotations to generate the summary.
/// @param progressBlock       Reports the progress of generating the annotation summary.
/// @param completionBlock     Called when the temporary file creation has either completed or failed.
- (void)temporaryPDFFileURLForPages:(NSIndexSet *)pages progress:(void (^ _Nullable)(NSUInteger currentIndex, CGFloat progress))progressBlock completionBlock:(void (^)(NSURL *_Nullable fileURL, NSError *_Nullable error))completionBlock;
@end
#endif

NS_ASSUME_NONNULL_END
