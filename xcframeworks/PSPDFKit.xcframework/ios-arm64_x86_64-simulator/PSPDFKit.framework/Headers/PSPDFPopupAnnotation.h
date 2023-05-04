//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

PSPDF_CLASS_SWIFT(PopupAnnotation)
@interface PSPDFPopupAnnotation : PSPDFAnnotation<PSPDFOverridable>

/// Specifies whether the popup is initially open or closed.
@property (atomic, getter=isOpen) BOOL open;

@end
