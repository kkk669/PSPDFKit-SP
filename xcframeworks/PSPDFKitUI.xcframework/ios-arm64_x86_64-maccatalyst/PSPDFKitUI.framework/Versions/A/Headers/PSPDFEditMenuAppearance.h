//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// An enum that describes the appearance of an edit menu.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFEditMenuAppearance) {

    /// The edit menu appears as a horizontal bar.
    PSPDFEditMenuAppearanceHorizontalBar,

    /// The edit menu appears as a context menu.
    PSPDFEditMenuAppearanceContextMenu,

} PSPDF_ENUM_SWIFT(EditMenuAppearance) NS_SWIFT_SENDABLE;
