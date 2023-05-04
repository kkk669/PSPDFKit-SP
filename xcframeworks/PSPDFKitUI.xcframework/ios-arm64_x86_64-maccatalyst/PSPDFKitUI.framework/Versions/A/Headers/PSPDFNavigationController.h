//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// A navigation controller that is optimized for use with `PDFViewController`.
/// We recommend using this subclass if possible.
///
/// This subclass forwards the following rotation methods to the top view controller:
/// `shouldAutorotate`, `supportedInterfaceOrientations`, `preferredInterfaceOrientationForPresentation:`.
///
/// To improve legibility with the widest range of documents, this subclass changes the default bar background
/// to use a system thick material effect for the navigation bar’s `standardAppearance` and `compactAppearance`.
/// The `scrollEdgeAppearance` and `compactScrollEdgeAppearance` are not changed.
PSPDF_CLASS_SWIFT(PDFNavigationController)
@interface PSPDFNavigationController : UINavigationController<UINavigationControllerDelegate>

- (void)setDelegate:(nullable id<UINavigationControllerDelegate>)delegate PSPDF_UNAVAILABLE("Not available.");

/// Forward the modern rotation method to the visible view controller. Defaults to YES.
@property (nonatomic, getter=isRotationForwardingEnabled) BOOL rotationForwardingEnabled;

@end

NS_ASSUME_NONNULL_END
