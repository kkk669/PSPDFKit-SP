//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN
@protocol PSPDFFontDownloaderDelegate;

/// A simplified Objective-C wrapper for `CTFontDescriptorMatchFontDescriptorsWithProgressHandler`.
///
/// In addition to just loading fonts, this class also keeps track of previously loaded ones, and
/// conveniently makes those fonts available later.
PSPDF_SDK_CLASS_SWIFT(FontDownloader)
@interface PSPDFFontDownloader : NSObject

/// Resolves saved fonts, and asynchronously loads them if necessary.
///
/// Once a font download completes successfully, this class keeps track of the font across app starts.
/// Because these fonts may not immediately be resolved by the system, we may want to resolve all of
/// them at once, later.
+ (void)loadPreviouslyDownloadedFonts;

/// Schedules a download of the font(s) matching the given descriptor, informing the delegate of
/// relevant events in the process.
///
/// The object returned by this method is kept alive for the duration of the download.
///
/// @note **Important:** The delegate may begin receiving messages before this method even returns.
/// @param fontDescriptor An object specifying the search criteria for one or more downloadable fonts.
/// @param delegate An object to be informed of relevant events during download.
+ (instancetype)downloadFontWithDescriptor:(UIFontDescriptor *)fontDescriptor delegate:(nullable id<PSPDFFontDownloaderDelegate>)delegate;

/// The object to be informed of download events.
///
/// @note The downloader will continue loading even when the delegate has been deallocated.
@property (nonatomic, readonly, weak) id<PSPDFFontDownloaderDelegate> delegate;

PSPDF_EMPTY_INIT_UNAVAILABLE

@end

// MARK: -

/// User info key for the `UIFontDescriptor` for which no font could be loaded after downloading.
///
/// Will be present in the `userInfo` dictionary of a `PSPDFErrorCodeFailedToLoadAnnotationFont`.
PSPDF_EXTERN NSString *const PSPDFFontLoadErrorFontDescriptorKey;

/// Delegate to receive download events.
///
/// @note **Important:** The methods in this protocol will be called on an arbitrary thread/queue!
@protocol PSPDFFontDownloaderDelegate <NSObject>

/// Informs the receiver that the downloader successfully finished operation, and that fonts matching
/// the descriptor are now available for use.
///
/// @param fontDownloader The sender of the message.
/// @param font The font that the sender resolved to.
/// @param fontDescriptor The resolved font descriptor.
- (void)fontDownloader:(PSPDFFontDownloader *)fontDownloader didResolveFont:(UIFont *)font forFontDescriptor:(UIFontDescriptor *)fontDescriptor;

@optional

/// Informs the receiver that the font downloader has started operation.
///
/// @note This method may be sent before `+[PSPDFFontDownloader downloadFontWithDescriptor:delegate:]`
/// even returns.
/// @param fontDownloader The sender of the message
/// @param fontDescriptor The font descriptor that should be downloaded and matched.
- (void)fontDownloader:(PSPDFFontDownloader *)fontDownloader didBeginResolvingFontDescriptor:(UIFontDescriptor *)fontDescriptor;

/// Informs the receiver that the font downloader received data, downloading the font(s) mathiching the
/// descriptor.
///
/// @param fontDownloader The sender of the message
/// @param progress A value 0.0-1.0 describing how much of the operation has completed.
/// @param fontDescriptor The font descriptor that is downloaded and matched.
- (void)fontDownloader:(PSPDFFontDownloader *)fontDownloader didUpdateProgress:(CGFloat)progress forFontDescriptor:(UIFontDescriptor *)fontDescriptor;

/// Informs the receiver that the font downloader failed loading or matching the descriptor.
///
/// @param fontDownloader The sender of the message
/// @param fontDescriptor The font descriptor that failed to be downloaded or matched.
/// @param error An object detailing what went wrong.
- (void)fontDownloader:(PSPDFFontDownloader *)fontDownloader didFailResolvingFontDescriptor:(UIFontDescriptor *)fontDescriptor withError:(NSError *)error;

@end
NS_ASSUME_NONNULL_END
