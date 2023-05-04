//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <TargetConditionals.h>

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIBezierPath (PSPDFMacOSCompatibility)

/// Same as applyTransform. We add a method of the same name on NSBezierPath, so this gives us source compatibility
/// without defining a macro for applyTransform which would break stuff because other functions use the same name.
///
/// @param transform The transform to apply.
- (void)pspdf_applyTransform:(CGAffineTransform)transform;

@end

NS_ASSUME_NONNULL_END

#endif
