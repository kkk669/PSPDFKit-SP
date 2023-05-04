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

/// Implement in your `UIViewController` subclass provide navigation image for `PSPDFDocumentInfoController` container.
PSPDF_PROTOCOL_SWIFT(SegmentImageProviding)
@protocol PSPDFSegmentImageProviding <NSObject>

/// An image object to use as the content of the segment.
///
/// If this returns nil or this protocol is not implemented by a view controller then the view controller’s title will be displayed instead.
///
/// @note Set `accessibilityLabel` property on image to ensure that the segments are properly accessible.
@property (nonatomic, readonly, nullable) UIImage *segmentImage;

@end

NS_ASSUME_NONNULL_END
