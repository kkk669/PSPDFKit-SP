//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFDrawView.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDrawView, PSPDFSignatureViewController, PSPDFColorButton, PSPDFSigner;

/// Delegate to be notified on signature actions.
PSPDF_PROTOCOL_SWIFT(SignatureViewControllerDelegate)
@protocol PSPDFSignatureViewControllerDelegate<NSObject>

@optional

/// Cancel button has been pressed.
- (void)signatureViewControllerDidCancel:(PSPDFSignatureViewController *)signatureController;

/// Save/Done button has been pressed.
- (void)signatureViewControllerDidFinish:(PSPDFSignatureViewController *)signatureController withSigner:(nullable PSPDFSigner *)signer shouldSaveSignature:(BOOL)shouldSaveSignature;

@end

/// The signature view controller can be used to create ink signatures to add to a document.
///
/// These signatures optionally can be used to create a digital signature with a certificate.
///
/// This class constitutes PSPDFKit’s older signatures functionality from before the introduction of
/// Electronic Signatures. As such, using this class requires that your license includes the Annotations
/// feature and was originally purchased in April 2021 or earlier. If you purchased your license after
/// this time, then you should use `SignatureCreationViewController` from Electronic Signatures instead.
///
/// This older signatures functionality will continue to be maintained and supported.
/// However, we recommend using Electronic Signatures for new PSPDFKit integrations.
/// If you’re interested in upgrading, please see our migration guide: https://pspdfkit.com/guides/ios/migration-guides/migrating-to-electronic-signatures/
PSPDF_CLASS_SWIFT(SignatureViewController)
@interface PSPDFSignatureViewController : PSPDFBaseViewController<PSPDFStyleable, PSPDFOverridable>

/// Enable natural drawing. Defaults to NO.
/// Usually set via `PSPDFConfiguration.naturalSignatureDrawingEnabled`.
@property (nonatomic) BOOL naturalDrawingEnabled;

/// Color options for the color picker (limit this to about 3 `UIColor` instances).
/// Defaults to black, blue and red.
@property (nonatomic, copy) NSArray<UIColor *> *menuColors;

/// Signature controller delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFSignatureViewControllerDelegate> delegate;

/// Defines if a signature should be saved. Defaults to `PSPDFSignatureSavingStrategySaveIfSelected`.
/// Usually set via `PSPDFConfiguration.signatureSavingStrategy`.
/// Shows a checkbox, when set to `PSPDFSignatureSavingStrategySaveIfSelected`.
@property (nonatomic) PSPDFSignatureSavingStrategy savingStrategy;

/// Defines if the certificate picker button should be shown. Defaults to `PSPDFSignatureCertificateSelectionModeIfAvailable`.
/// Usually set via `PSPDFConfiguration.signatureCertificateSelectionMode`.
@property (nonatomic) PSPDFSignatureCertificateSelectionMode certificateSelectionMode;

/// The view used internally for drawing the signature.
///
/// Use the draw view to access additional drawing data, including biometric values.
@property (nonatomic, readonly) PSPDFDrawView *drawView;

/// Signer used for digitally signing.
/// If this is set, a digital signature will be created instead of an ink signature.
@property (nonatomic, readonly, nullable) PSPDFSigner *signer;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFSignatureViewController (SubclassingHooks)

/// Customize the created color menu buttons.
- (PSPDFColorButton *)colorButtonForColor:(UIColor *)color;

// MARK: Actions for custom buttons.

/// Called when the cancel button has been tapped.
- (void)cancel:(nullable id)sender;

/// Called when the done button has been tapped.
- (void)done:(nullable id)sender;

/// Called when the clear button has been tapped.
- (void)clear:(nullable id)sender;

/// Called when a color has been tapped.
- (void)color:(PSPDFColorButton *)sender;

@end

NS_ASSUME_NONNULL_END
