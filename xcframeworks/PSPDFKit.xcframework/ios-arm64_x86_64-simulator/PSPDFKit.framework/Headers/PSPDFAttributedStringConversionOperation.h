//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFConversionOperation.h>

NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IOS

/// Operation that converts an attributed string to PDF. Needs to be executed from background thread.
///
/// @note Requires the `Features.webKitHtmlConversion` feature flag.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AttributedStringConversionOperation)
@interface PSPDFAttributedStringConversionOperation : PSPDFConversionOperation

/// Input attributed string.
@property (nonatomic, readonly, copy) NSAttributedString *attributedString;

@end

#endif

NS_ASSUME_NONNULL_END
