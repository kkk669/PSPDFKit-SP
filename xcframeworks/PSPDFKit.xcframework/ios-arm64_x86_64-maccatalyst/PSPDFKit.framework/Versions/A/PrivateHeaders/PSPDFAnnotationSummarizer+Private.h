//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationSummarizer.h>

NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IOS
@interface PSPDFAnnotationSummarizer (Private)

/// Generates a PDF file with the annotation summary for the document at the provided pages, and sets a custom filename.
///
/// @param pages               The pages to scan for annotations to generate the summary.
/// @param suggestedFilename   Custom filename to use.
/// @param progressBlock       Reports the progress of generating the annotation summary.
/// @param completionBlock     Called when the temporary file creation has either completed or failed.
- (void)temporaryPDFFileURLForPages:(NSIndexSet *)pages suggestedFilename:(nullable NSString *)suggestedFilename progress:(void (^ _Nullable)(NSUInteger currentIndex, CGFloat progress))progressBlock completionBlock:(void (^)(NSURL *_Nullable fileURL, NSError *_Nullable error))completionBlock;

@end
#endif

NS_ASSUME_NONNULL_END
