//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFHostingAnnotationView.h>

#import <PSPDFKitUI/PSPDFFormInputAccessoryView.h>

/// Generic view for form elements. Adds the form accessory view and additional keyboard support.
/// Form views are not synced with the page to allow snappier editing.
PSPDF_CLASS_SWIFT(PDFFormElementView)
@interface PSPDFFormElementView : PSPDFHostingAnnotationView<PSPDFFormInputAccessoryViewDelegate>

@end
