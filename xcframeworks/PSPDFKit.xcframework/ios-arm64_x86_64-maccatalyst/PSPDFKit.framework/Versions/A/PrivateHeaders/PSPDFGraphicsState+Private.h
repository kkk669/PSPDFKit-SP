//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFGraphicsState.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFGraphicsState ()

@end

/// Converts the CGBlendMode into a string that can be used as a compositing filter on CGLayer.
///
/// This is a UI helper for CGLayer on iOS and macOS.
PSPDF_SDK_EXPORT NSString *PSPDFComposingFilterStringFromCGBlendMode(CGBlendMode blendMode);

/// Returns the string from blend mode as it is used in the PDF serialization.
/// This string can be used for localization purposes.
PSPDF_SDK_EXPORT NSString *PSPDFStringFromCGBlendMode(CGBlendMode blendMode);

NS_ASSUME_NONNULL_END
