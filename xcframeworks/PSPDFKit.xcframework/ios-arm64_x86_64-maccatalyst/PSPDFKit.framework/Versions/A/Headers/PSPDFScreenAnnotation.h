//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAssetAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFMediaScreenWindowType) {
    PSPDFMediaScreenWindowTypeFloating,
    PSPDFMediaScreenWindowTypeFullscreen,
    PSPDFMediaScreenWindowTypeHidden,
    /// Default value
    PSPDFMediaScreenWindowTypeUseAnnotationRectangle,
} PSPDF_ENUM_SWIFT(ScreenAnnotation.MediaScreenWindowType);

/// A screen annotation (PDF 1.5) specifies a region of a page upon which media clips may be played. It also serves as an object from which actions can be triggered. PSPDFKit also supports the matching Rendition Actions to control the video play state.
///
/// @note iOS cannot play all video/audio formats that can be used for PDF.
PSPDF_CLASS_SWIFT(ScreenAnnotation)
@interface PSPDFScreenAnnotation : PSPDFAssetAnnotation<PSPDFOverridable>

/// Defaults the window type the media should play in.
///
/// @note only `.UseAnnotationRectangle` and `.Hidden` is currently supported.
@property (atomic, readonly) PSPDFMediaScreenWindowType mediaScreenWindowType;

@end
