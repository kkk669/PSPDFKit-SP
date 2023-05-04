//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// A container view cannot draw content in itself.
///
/// It uses a `CATransformLayer` as backing.
/// This allows blend mode pass-through, and is more lightweight than a regular view.
///
/// @note `UIStackView` uses the same trick for being a purely managing container.
PSPDF_CLASS_SWIFT(PDFContainerView)
@interface PSPDFContainerView : UIView
@end
