//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFScrollTouchMode) {
    /// The default UIScrollView behavior, where scrolling is possible with one direct or stylus touch.
    PSPDFScrollTouchModeSingle,
    /// Require two direct touches for scrolling, so single finger touches may be used for annotating.
    PSPDFScrollTouchModeTwoFingers,
    /// Scroll with one finger, but not with Apple Pencil touches so they may be used for annotating.
    PSPDFScrollTouchModeNoStylus,
} NS_SWIFT_NAME(ScrollTouchMode);

NS_ASSUME_NONNULL_END
