//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPointerHoverEffect) {
    /// Only an overlay tint. Use this for opaque views that are directly next to other elements.
    PSPDFPointerHoverEffectTint,
    /// Only scale. Use this for views with transparent backgrounds.
    PSPDFPointerHoverEffectScale,
    /// Scale with shadow. Use this for opaque views with some space around them, and `tintScaleShadow` seems too strong.
    PSPDFPointerHoverEffectScaleShadow,
    /// All components of a hover effect. Use this for opaque views with some space around them.
    PSPDFPointerHoverEffectTintScaleShadow,
} PSPDF_ENUM_SWIFT(PointerHoverEffect);
