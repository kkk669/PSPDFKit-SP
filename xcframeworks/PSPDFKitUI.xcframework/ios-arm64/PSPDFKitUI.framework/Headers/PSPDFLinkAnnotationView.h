//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFLinkAnnotationBaseView.h>

NS_ASSUME_NONNULL_BEGIN

/// Displays an annotation link.
PSPDF_CLASS_SWIFT(LinkAnnotationView)
@interface PSPDFLinkAnnotationView : PSPDFLinkAnnotationBaseView<PSPDFOverridable>

/// The border color. This is passed onto a `CALayer`. A nil border color means the border is black.
///
/// @note This property will be set to match the link annotation `borderColor`.
///
/// @note If the dash array is invalid, the border will not be rendered. See PDF Reference §8.4.3.6 (Table 55).
///
/// To use a fixed value override this property setter and call super with a custom value.
@property (nonatomic, nullable) UIColor *borderColor;

/// Roundness of the border. Defaults to 0.
@property (nonatomic) CGFloat cornerRadius;

/// Stroke width. Defaults to 0.
///
/// @note This property will be set to match the link annotation `lineWidth`.
/// To use a fixed value override this property setter and call super with a custom value.
@property (nonatomic) CGFloat strokeWidth;

@end

NS_ASSUME_NONNULL_END
