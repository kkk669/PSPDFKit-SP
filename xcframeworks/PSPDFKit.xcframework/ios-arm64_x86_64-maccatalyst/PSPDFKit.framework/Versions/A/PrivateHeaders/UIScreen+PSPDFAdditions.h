//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#if TARGET_OS_IOS

NS_ASSUME_NONNULL_BEGIN

@interface UIScreen (PSPDFAdditions)

/// Searches a file path for an @%tux scale marker and returns the scale. Returns 1.f if no scale found.
+ (CGFloat)pspdf_scaleForPath:(NSString *)path;

/// Returns either `@""` or `@%tux` depending on the screen resolution.
@property (nonatomic, readonly) NSString *pspdf_scaleString;

/// Returns a cached version of the UIScreen.mainScreen.scale on iOS,
/// and always 1.0 on macOS.
PSPDF_EXPORT CGFloat PSPDFDefaultScale(void);

@end

NS_ASSUME_NONNULL_END

#endif
