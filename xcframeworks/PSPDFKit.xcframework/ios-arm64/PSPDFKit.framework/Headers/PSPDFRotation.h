//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

/// An angle a PDF page is displayed at in clockwise degrees.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFRotation) {
    /// The page is displayed without rotation.
    PSPDFRotation0 = 0,
    /// The page is displayed 90 degrees clockwise.
    PSPDFRotation90 = 90,
    /// The page is displayed upside-down.
    PSPDFRotation180 = 180,
    /// The page is displayed 90 degrees counterclockwise.
    PSPDFRotation270 = 270
} PSPDF_ENUM_SWIFT(Rotation);
