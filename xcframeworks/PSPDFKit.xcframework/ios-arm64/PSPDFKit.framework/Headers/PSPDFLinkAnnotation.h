//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(UInt8, PSPDFLinkAnnotationType) {
    PSPDFLinkAnnotationPage = 0,
    PSPDFLinkAnnotationWebURL,
    PSPDFLinkAnnotationDocument,
    PSPDFLinkAnnotationVideo,
    /// Deprecated. This is for both YouTube and Vimeo.
    PSPDFLinkAnnotationYouTube PSPDF_DEPRECATED(11.4, "Please load videos with direct sources or embed your own player view instead."),
    PSPDFLinkAnnotationAudio,
    PSPDFLinkAnnotationImage,
    PSPDFLinkAnnotationBrowser,
    /// Any annotation format that is not recognized is custom. (e.g. tel://)
    PSPDFLinkAnnotationCustom,
} PSPDF_ENUM_SWIFT(LinkAnnotation.Kind);

@class PSPDFAction, PSPDFURLAction, PSPDFGoToAction;

/// The `PSPDFLinkAnnotation` represents both classic PDF page/document/web links, and more types not supported by other PDF readers (video, audio, image, etc)
///
/// PSPDFKit will automatically figure out the type for PDF link annotations loaded from a document, based on the file type. ("mp4" belongs to `.video`; a YouTube-URL to `.youTube`, etc)
///
/// If you create a `LinkAnnotation` at runtime, be sure to set the correct type and use the URL parameter for your link.
/// `boundingBox` defines the frame, in PDF space coordinates.
///
/// If you want to customize how links look in the PDF, customize `LinkAnnotationView`’s properties. There's currently no mapping between `color`/`lineWidth`/etc and the properties of the view. This might change in a future release.
PSPDF_CLASS_SWIFT(LinkAnnotation)
@interface PSPDFLinkAnnotation : PSPDFAnnotation<PSPDFOverridable>

/// Designated initializer for custom, at runtime created `PSPDFLinkAnnotations`.
- (instancetype)initWithLinkAnnotationType:(PSPDFLinkAnnotationType)linkAnnotationType;

/// Initialize with an action.
- (instancetype)initWithAction:(PSPDFAction *)action;

/// Initialize link annotation with target URL.
- (instancetype)initWithURL:(NSURL *)url;

/// PSPDFKit addition - will be updated if the `pspdfkit://` protocol is detected.
@property (atomic) PSPDFLinkAnnotationType linkType;

/// The associated PDF action that will be executed on tap.
///
/// @note Will update the `linkType` and potential other properties like `autoplayEnabled`,
/// `controlsEnabled`, `loopEnabled`, `fullscreenEnabled` to match the action when set.
@property (atomic, nullable) PSPDFAction *action;

/// Convenience cast. Will return the URL action if action is of type `PSPDFActionTypeURL`, else nil.
@property (atomic, readonly, nullable) PSPDFURLAction *URLAction;

/// Convenience method, gets the URL if `action` is a `PSPDFURLAction`.
@property (atomic, copy, readonly, nullable) NSURL *URL;

/// Will be YES if this is a regular link or a multimedia link annotation that should be displayed as link. (e.g. if `isPopover/isModal` is set to yes)
@property (atomic, readonly) BOOL showAsLinkView;

/// Returns YES if this link is specially handled by PSPDFKit.
/// Returns true for any linkType >= `PSPDFLinkAnnotationVideo` && linkType <= `PSPDFLinkAnnotationBrowser`.
@property (atomic, readonly, getter=isMultimediaExtension) BOOL multimediaExtension;

/// Show or hide controls. Valid for `PSPDFLinkAnnotationVideo`, `PSPDFLinkAnnotationAudio`
/// and `PSPDFLinkAnnotationBrowser`. Defaults to YES.
/// Some controls will add alternative ways to control if this is disabled.
/// e.g. Videos can be paused via touch on the view if this is set to NO.
/// Websites will not receive touches if controlsEnabled is set to NO.
@property (atomic) BOOL controlsEnabled;

/// Autoplay video/audio. Only valid for `PSPDFLinkAnnotationVideo` and `PSPDFLinkAnnotationAudio`. Defaults to NO.
@property (atomic, getter=isAutoplayEnabled) BOOL autoplayEnabled;

/// Loop media. Only valid for `PSPDFLinkAnnotationVideo` and `PSPDFLinkAnnotationAudio`. Defaults to NO.
@property (atomic, getter=isLoopEnabled) BOOL loopEnabled;

/// Allow fullscreen presentation of the media item. Defaults to YES.
@property (atomic, getter=isFullscreenEnabled) BOOL fullscreenEnabled;

/// Used for the preview string when the user long-presses on a link annotation.
/// Forwards to `action.localizedDescription`.
@property (atomic, readonly, nullable) NSString *targetString;

@end

NS_ASSUME_NONNULL_END
