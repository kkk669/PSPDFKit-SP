//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDataSink.h>
#import <PSPDFKit/PSPDFDocumentSecurityOptions.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFProcessorConfiguration.h>
#import <PSPDFKit/PSPDFProcessorDelegate.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFAttributedStringConversionOperation, PSPDFHTMLConversionOperation, PSPDFOfficeConversionOperation, PSPDFURLConversionOperation;

/// Available keys for options. `PSPDFProcessorAnnotationDictKey` in form of pageIndex -> annotations.
/// Annotations will be flattened when type is set, unless `PSPDFProcessorAnnotationAsDictionaryKey` is also set.
/// Don't forget to also define the types of annotations that should be processed:
/// `PSPDFProcessorAnnotationTypesKey: @(PSPDFAnnotationTypeAll)`.
PSPDF_EXPORT NSString *const PSPDFProcessorAnnotationTypesKey;
PSPDF_EXPORT NSString *const PSPDFProcessorAnnotationDictKey;

/// Set to `@YES` to add annotations as dictionary and don't flatten them. Dictionary keys are the *original* page indexes.
PSPDF_EXPORT NSString *const PSPDFProcessorAnnotationAsDictionaryKey;

/// Specifies the user password that should be set on the generated PDF.
PSPDF_EXPORT NSString *const PSPDFProcessorUserPasswordKey;

/// Specifies the owner password that should be set on the generated PDF.
PSPDF_EXPORT NSString *const PSPDFProcessorOwnerPasswordKey;

/// Specifies the key length that should be used to encrypt the PDF. Value must be
/// divisible by 8 and in the range of 40 to 128.
PSPDF_EXPORT NSString *const PSPDFProcessorKeyLengthKey;

/// Settings for the string/URL -> PDF generators.

/// Defaults to `PSPDFPaperSizeA4`
PSPDF_EXPORT NSString *const PSPDFProcessorPageRectKey;

/// Defaults to 10. Set lower to optimize, higher if you have a lot of content.
PSPDF_EXPORT NSString *const PSPDFProcessorNumberOfPagesKey;

/// Defines the page margin. Defaults to `UIEdgeInsetsMake(5, 5, 5, 5)`.
PSPDF_EXPORT NSString *const PSPDFProcessorPageBorderMarginKey;

/// If you print web pages, they might load async content which can't be reliably detected.
/// Defaults to 0.05 seconds. Set higher if you get blank pages.
PSPDF_EXPORT NSString *const PSPDFProcessorAdditionalDelayKey;

/// Defaults to NO. Adds an additional step to strip white pages if you're getting any at the end.
PSPDF_EXPORT NSString *const PSPDFProcessorStripEmptyPagesKey;

/// Common page sizes. Use for `PSPDFProcessorPageRectKey`.
PSPDF_EXPORT const CGRect PSPDFPaperSizeA4;
PSPDF_EXPORT const CGRect PSPDFPaperSizeLetter;

/// common options
/// Will override any defaults if set.
PSPDF_EXPORT NSString *const PSPDFProcessorDocumentTitleKey;

/// 1st argument: current page, 2nd argument: total pages
typedef void (^PSPDFProgressBlock)(NSUInteger currentPage, NSUInteger totalPages);

/// Create, merge or modify PDF documents. Can also flatten annotation data.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(Processor)
@interface PSPDFProcessor : NSObject

@property (nonatomic, weak) id<PSPDFProcessorDelegate> delegate;

/// Instantiates a `PSPDFProcessor` with the given configuration and security options.
///
/// @see `-initWithOptions:` if you want to generate a PDF from an HTML string or URL.
///
/// @param configuration The configuration you want to use for the processing.
/// @param securityOptions The save options to use or `nil` if you want to keep the ones from the original document.
- (instancetype)initWithConfiguration:(PSPDFProcessorConfiguration *)configuration securityOptions:(nullable PSPDFDocumentSecurityOptions *)securityOptions;

/// Generates a new document based on the configuration and security options set on the receiver, and stores it
/// to `fileURL`.
///
/// @param fileURL The URL to save the generated document to. Needs to be a file URL. There should be no file at this URL prior to calling this method. This method will throw an error in the case a file already exists.
/// @param error On return, contains an error if one occurred while generating the document.
///
/// @return `true` if generation was successful, `false` otherwise.
- (BOOL)writeToFileURL:(NSURL *)fileURL error:(NSError **)error;

/// Generates a new document based on the configuration and security options set on the receiver.
///
/// @note The data object will be memory-mapped if possible, however we encourage you to use the file url based variant instead.
///
/// @param error On return, contains an error if one occurred while generating the document.
///
/// @return A `Data` object containing the generated document. If possible, this object is memory-mapped.
- (nullable NSData *)dataWithError:(NSError **)error;

/// Generates a new document based on the configuration and security options set on the receiver, and
/// writes it to the PSPDFDataSink provided.
///
/// @param outputDataSink The generated document will be written into `outputDataSink`.
/// @param error On return, contains an error if one occurred while generating the document.
///
/// @return `true` if generation was successful, `false` otherwise.
- (BOOL)outputToDataSink:(id<PSPDFDataSink>)outputDataSink error:(NSError **)error;

/// Cancels the current PDF generation process associated with the receiver.
///
/// The cancellation is asynchronous, and only happens until the current page that's being processes is completed.
- (void)cancel;

// MARK: Conversion

#if TARGET_OS_IOS

/// Renders a PDF from a website or file, and keeps it in memory (the generated PDF won't be saved to disk).
/// Upon completion, the `completionBlock` will be called.
///
/// Loading the URL is non-blocking, however the conversion uses the iOS printing infrastructure and only works
/// on the main thread. Larger documents might stall your application for a while. Download the document to a temporary
/// folder and show a blocking progress HUD while the conversion is running to mitigate the blocking.
///
/// Supported types are those that can be rendered by `WKWebView`. This includes web pages, Pages, Keynote, Numbers,
/// Word, PowerPoint, Excel, RTF, JPEG, PNG.
///
/// @note File / office conversion will generally not yield good results with this approach. For a 1:1 office conversion,
/// you need to convert those files on a server with a product that is specialized for this task.
/// See `Processor.generatePDF(from:, serverURL:, jwt:, completionBlock:)` for more information.
///
/// Certain documents might not have the correct pagination (try to manually define `PSPDFProcessorPageRectKey` to fine-tune this).
///
/// When a password is set, only link annotations can be added as dictionary (this does not affect flattening).
///
/// @warning Don't manually override the returned operation's `completionBlock`.
/// @warning Don't use this for PDF files.
///
/// @param inputURL The URL to generate the PDF from.
/// @param options Options to be considered when generating a PDF from a website or file.
/// @param completionBlock Called when the PDF generation is complete. First parameter is the data of the rendered PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting URL to PDF that will be automatically enqueued.
///
/// @note Requires the `Features.webKitHtmlConversion` feature flag. Calls `completionBlock` with an error if the feature is not available in your license.
+ (PSPDFURLConversionOperation *)generatePDFFromURL:(NSURL *)inputURL options:(nullable NSDictionary<NSString *, id> *)options completionBlock:(nullable void (^)(NSData * _Nullable outputData, NSError * _Nullable error))completionBlock;

/// This method performs the same task as `+generatePDFFromURL:options:completionBlock`, but the generated PDF is saved to disk.
///
/// @param inputURL The URL to generate the PDF from.
/// @param outputFileURL The URL the generated PDF is going to be saved to. Needs to be a file URL. Note that the actual output file URL might be different at the end.
/// @param options Options to be considered when generating a PDF from a website or file.
/// @param completionBlock Called when the PDF generation is complete. First parameter is the actual output file URL of the rendered PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting URL to PDF that will be automatically enqueued.
///
/// @note Requires the `Features.webKitHtmlConversion` feature flag. Calls `completionBlock` with an error if the feature is not available in your license.
+ (PSPDFURLConversionOperation *)generatePDFFromURL:(NSURL *)inputURL outputFileURL:(NSURL *)outputFileURL options:(nullable NSDictionary<NSString *, id> *)options completionBlock:(nullable void (^)(NSURL * _Nullable actualOutputFileURL, NSError * _Nullable error))completionBlock;

#if !TARGET_OS_MACCATALYST

/// Renders a PDF from a HTML string, and keeps it in memory.
///
/// @note This allows for simple HTML tags but will not work with complex HTML pages.
/// E.g. `This is a <b>test</b>` in `<span style='color:red'>color.</span>`
///
/// @warning Don't manually override the returned operation's `completionBlock`.
///
/// @param HTMLString The HTML string that's going to be converted to PDF.
/// @param options Options to be considered when generating a PDF from a HTML string.
/// @param completionBlock Block that's called on completion of the PDF generation. First parameter is the data of the rendered PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting HTML string to PDF that will be automatically enqueued.
///
/// @note Requires the `Features.webKitHtmlConversion` feature flag. Calls `completionBlock` with an error if the feature is not available in your license.
/// This feature uses `UIMarkupTextPrintFormatter`, which is (in contrast to the documentation) not available on Mac Catalyst: FB6823732
+ (PSPDFHTMLConversionOperation *)generatePDFFromHTMLString:(NSString *)HTMLString options:(nullable NSDictionary<NSString *, id> *)options completionBlock:(nullable void (^)(NSData * _Nullable outputData, NSError * _Nullable error))completionBlock;

/// This method performs the same task as `+generatePDFFromHTMLString:options:completionBlock`, but the generated PDF is saved to disk.
///
/// @param HTMLString The HTML string that's going to be converted to PDF.
/// @param outputFileURL The URL the generated PDF is going to be saved to. Needs to be a file URL. Note that the actual output file URL might be different at the end.
/// @param options Options to be considered when generating a PDF from a HTML string.
/// @param completionBlock Block that's called on completion of the PDF generation. First parameter is the actual output file URL of the rendered PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting HTML string to PDF that will be automatically enqueued.
///
/// @note Requires the `Features.webKitHtmlConversion` feature flag. Calls `completionBlock` with an error if the feature is not available in your license.
+ (PSPDFHTMLConversionOperation *)generatePDFFromHTMLString:(NSString *)HTMLString outputFileURL:(NSURL *)outputFileURL options:(nullable NSDictionary<NSString *, id> *)options completionBlock:(nullable void (^)(NSURL * _Nullable actualOutputFileURL, NSError * _Nullable error))completionBlock;

#endif

#endif

#if TARGET_OS_IOS

/// Renders a PDF from an attributed string, and keeps it in memory.
///
/// @warning Don't manually override the returned operation's `completionBlock`.
///
/// @param attributedString The attributed string that's going to be converted to PDF.
/// @param options Options to be considered when generating a PDF from an attributed string.
/// @param completionBlock Block that's called on completion of the PDF generation. First parameter is the data of the rendered PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting attributed string to PDF that will be automatically enqueued.
///
/// @note Requires the `Features.webKitHtmlConversion` feature flag. Calls `completionBlock` with an error if the feature is not available in your license.
+ (PSPDFAttributedStringConversionOperation *)generatePDFFromAttributedString:(NSAttributedString *)attributedString options:(nullable NSDictionary<NSString *, id> *)options completionBlock:(nullable void (^)(NSData * _Nullable outputData, NSError * _Nullable error))completionBlock;

/// This method performs the same task as `+generatePDFFromAttributedString:options:completionBlock`, but the generated PDF is saved to disk.
///
/// @param attributedString The attributed string that's going to be converted to PDF.
/// @param outputFileURL The URL the generated PDF is going to be saved to. Needs to be a file URL. Note that the actual output file URL might be different at the end.
/// @param options Options to be considered when generating a PDF from an attributed string.
/// @param completionBlock Block that's called on completion of the PDF generation. First parameter is the actual output file URL of the rendered PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting attributed string to PDF that will be automatically enqueued.
///
/// @note Requires the `Features.webKitHtmlConversion` feature flag. Calls `completionBlock` with an error if the feature is not available in your license.
+ (PSPDFAttributedStringConversionOperation *)generatePDFFromAttributedString:(NSAttributedString *)attributedString outputFileURL:(NSURL *)outputFileURL options:(nullable NSDictionary<NSString *, id> *)options completionBlock:(nullable void (^)(NSURL * _Nullable actualOutputFileURL, NSError * _Nullable error))completionBlock;

#endif

/// Converts an Office file to a PDF by uploading it to a server that performs the actual conversion.
/// Once the server completes the conversion, the resulting PDF file is downloaded and kept in memory.
///
/// Supported document types: Word, Excel and Powerpoint.
///
/// @param inputURL The URL of the file to generate the PDF from.
/// @param serverURL The URL of the server that will perform the document conversion.
/// @param JWT The JSON Web token used to authenticate access to the server.
/// @param completionBlock Called when the converted PDF has finished downloading. First parameter is the data of the rendered PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting the Office file to PDF that will be automatically enqueued.
///
/// @note WARNING: This API downloads and loads the entire converted PDF file into memory.
+ (nullable PSPDFOfficeConversionOperation *)generatePDFFromURL:(NSURL *)inputURL serverURL:(NSURL *)serverURL JWT:(NSString *)JWT completionBlock:(nullable void (^)(NSData * _Nullable outputData, NSError * _Nullable error))completionBlock;

/// This method performs the same task as `+generatePDFFromURL:serverURL:jwt:completionBlock`, but the generated PDF is saved to disk.
///
/// Supported document types: Word, Excel and Powerpoint.
///
/// @param inputURL The URL of the file to generate the PDF from.
/// @param serverURL The URL of the server that will perform the document conversion.
/// @param JWT The JSON Web token used to authenticate access to the server.
/// @param outputFileURL The URL the generated PDF is going to be saved to. Needs to be a file URL. Note that the actual output file URL might be different at the end.
/// @param completionBlock Called when the converted PDF has finished downloading and has been saved to disk. First parameter is the actual output file URL of the converted PDF, second parameter is the resulting error, if any.
///
/// @return Operation of converting the Office file to PDF that will be automatically enqueued.
///
/// @note This API streams the converted PDF file and writes it to disk without loading it entirely into memory.

+ (nullable PSPDFOfficeConversionOperation *)generatePDFFromURL:(NSURL *)inputURL serverURL:(NSURL *)serverURL JWT:(NSString *)JWT outputFileURL:(NSURL *)outputFileURL completionBlock:(nullable void (^)(NSURL * _Nullable actualOutputFileURL, NSError * _Nullable error))completionBlock;

/// Cancel all ongoing conversion operations.
+ (void)cancelAllConversionOperations;

@end

NS_ASSUME_NONNULL_END
