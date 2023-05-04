//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_APP_CLASS_SWIFT(PDFWindow)
@interface PSPDFWindow : UIWindow

/// Due to a bug in UIWindow we need to un-set the rootViewController when the window is hidden.
/// This property exposes the internally managed rootViewController that is not nil (once set)
@property (nonatomic, readonly, nullable) UIViewController *realRootViewController;

@end

PSPDF_APP_CLASS_SWIFT(StatusBarIgnoringWindow)
@interface PSPDFStatusBarIgnoringWindow : PSPDFWindow

@end

NS_ASSUME_NONNULL_END
