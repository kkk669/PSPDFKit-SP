//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// An object used as an activation context in `PSPDFSmartZoomInteraction` that
/// provides information about a scroll view being zoomed and a target zoom rectangle.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(SmartZoomContext)
@interface PSPDFSmartZoomContext : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Target zoom rectangle in the coordinate space of `scrollView`. In case of zoom
/// out, this property will be `CGRectNull`.
@property (nonatomic, readonly) CGRect targetRect;

/// Scroll view which is being zoomed in or out.
@property (nonatomic, readonly) UIScrollView *scrollView;

@end

NS_ASSUME_NONNULL_END
