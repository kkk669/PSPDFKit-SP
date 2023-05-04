//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Spread position in the viewport.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFSpreadScrollPosition) {
    /// The spread is positioned at the beginning of the viewport in the scroll direction.
    PSPDFSpreadScrollPositionStart,
    /// The spread is positioned in the middle of the viewport.
    PSPDFSpreadScrollPositionMiddle,
    /// The spread is positioned at the end of the viewport in the scroll direction.
    PSPDFSpreadScrollPositionEnd
};
