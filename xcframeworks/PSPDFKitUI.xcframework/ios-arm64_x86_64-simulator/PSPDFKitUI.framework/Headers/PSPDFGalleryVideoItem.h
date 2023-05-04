//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFGalleryItem.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFGalleryVideoItemQuality) {
    PSPDFGalleryVideoItemQualityUnknown,
    PSPDFGalleryVideoItemQuality240p,
    PSPDFGalleryVideoItemQuality360p,
    PSPDFGalleryVideoItemQuality720p,
    PSPDFGalleryVideoItemQuality1080p,
} PSPDF_ENUM_SWIFT(GalleryVideoItem.Quality);

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFGalleryVideoItemCoverMode) {
    /// The cover is not visible. Correspondents to `none`.
    PSPDFGalleryVideoItemCoverModeNone,

    /// The cover is visible and a video preview is displayed. Correspondents to `preview`.
    PSPDFGalleryVideoItemCoverModePreview,

    /// The cover is visible and an image is displayed. Correspondents to `image`.
    PSPDFGalleryVideoItemCoverModeImage,

    /// The cover is visible and the underlying PDF shines through. Correspondents to `clear`.
    PSPDFGalleryVideoItemCoverModeClear
} PSPDF_ENUM_SWIFT(GalleryVideoItem.CoverMode);

/// Converts an `NSString` into `PSPDFGalleryVideoItemQuality`.
PSPDF_EXPORT PSPDFGalleryVideoItemQuality PSPDFGalleryVideoItemQualityFromString(NSString *string);

/// Converts an `NSString` into `PSPDFGalleryVideoItemCoverMode`.
PSPDF_EXPORT PSPDFGalleryVideoItemCoverMode PSPDFGalleryVideoItemCoverModeFromString(NSString *string);

/// A video item in a gallery. This class uses the class cluster design pattern.
PSPDF_CLASS_SWIFT(GalleryVideoItem)
@interface PSPDFGalleryVideoItem : PSPDFGalleryItem

// MARK: Options

/// Indicates if the item should start playing automatically. Defaults to `false`.
@property (nonatomic) BOOL autoplayEnabled;

/// Indicates if the playback should loop. Defaults to `false`.
@property (nonatomic) BOOL loopEnabled;

/// Contains the order of the preferred video qualities. This only works for videos where
/// the source is capable of providing different qualities.
@property (nonatomic, copy) NSArray<NSNumber *> *preferredVideoQualities;

/// The initial seek time. Defaults to `0.0`.
@property (nonatomic) NSTimeInterval seekTime;

/// The start of the video in seconds. Defaults to `nil`.
@property (nonatomic, nullable) NSNumber *startTime;

/// The end time of the video in seconds. Defaults to `nil`.
@property (nonatomic, nullable) NSNumber *endTime;

/// Calculates the playable range from `startTime` and `endTime`.
@property (nonatomic, readonly) CMTimeRange playableRange;

/// The cover mode used. Defaults to `PSPDFGalleryVideoItemCoverModePreview`.
@property (nonatomic) PSPDFGalleryVideoItemCoverMode coverMode;

/// The cover image URL. Defaults to `nil`.
///
/// @note The `coverMode` must be set to `PSPDFGalleryVideoItemCoverModeImage` for this
/// property to have an effect.
@property (nonatomic, copy, nullable) NSURL *coverImageURL;

/// The time in seconds at which the cover view should be captured. Only applicable if
/// `coverMode` is set to `PSPDFGalleryVideoItemCoverModePreview`.
@property (nonatomic, nullable) NSNumber *coverPreviewCaptureTime;

// MARK: Content

/// An `PSPDFGalleryVideoItem` has an URL to a video as its content.
@property (nonatomic, readonly, nullable) NSURL *content;

@end

@interface PSPDFGalleryVideoItem (Protected)

/// This method is the designated initializer for all internal classes of the class cluster.
- (instancetype)initInternallyWithDictionary:(NSDictionary<PSPDFGalleryItemProperty, id> *)dictionary;

@end

// MARK: Video Options

/// NSString. Indicates the cover mode.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionCoverMode;

/// NSURL. Indicates which image should be presented as a cover view.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionCoverImage;

/// NSNumber. The time in the video where the preview should be captured.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionCoverPreviewCaptureTime;

/// NSArray. The preferred video qualities.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionPreferredVideoQualities;

/// NSNumber. The start time of the video.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionStartTime;

/// NSNumber. The end time of the video.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionEndTime;

// MARK: Deprecated Video Options

/// Mixed value. This is a mixture of boolean values and an URL to a cover image.
/// Use `PSPDFGalleryOptionCoverImage` and `PSPDFGalleryOptionCoverMode` instead.
PSPDF_EXPORT NSString *const PSPDFGalleryOptionCover;

NS_ASSUME_NONNULL_END
