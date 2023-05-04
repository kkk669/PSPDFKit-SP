//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDigitalSignatureCoordinator.h>
#import <PSPDFKit/PSPDFSignatureBiometricProperties.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFPageView;

/// Empty view controller that is used for presenting the password input dialog after drawing a signature rect for digitally signing a document.
@interface PSPDFSignaturePasswordPlaceholderViewController : UIViewController
@end

@interface PSPDFDigitalSignatureCoordinator ()

/// Instantiate a new digital signature coordinator.
///
/// @param signatureBiometricPropertiesOption Defines which biometric properties, `PSPDFSignatureBiometricProperties`, should be stored in a digital signature, if one is created. Usually set via `PSPDFConfiguration.signatureBiometricPropertiesOptions`.
- (instancetype)initWithSignatureBiometricPropertiesOptions:(PSPDFSignatureBiometricPropertiesOption)signatureBiometricPropertiesOption;

/// Entry point for digitally signing a document. Prepares the document for digitally signing. Requests a signing certificate of the signature's signer. Creates the appropriate signature appearance if an ink annotation was provided, and allows customization via a subclassing hook. And digitally signs the document.
/// Signs the document to `pathForDigitallySignedDocumentFromOriginalDocument:`. And presents it via `presentSignedDocument:showingPageIndex:`.
///
/// @param signature The signature that is used to digitally sign the document. Needs to have a `signer`, used for digitally signing.
/// @param formElement The signature form element that should be signed. This form elements needs to be on the document already.
/// @param viewController The view controller where potential error messages and the password entry view controller should be pushed at. Needs to have a `navigationController`.
/// @param presentationContext Used for refreshing the page views when signed.
/// @param completionBlock Called when signing succeeded or when an error occurred.
- (void)signDocument:(PSPDFDocument *)document withSignature:(PSPDFSignatureContainer *)signature formElement:(PSPDFSignatureFormElement *)formElement viewController:(UIViewController *)viewController presentationContext:(nullable id<PSPDFPresentationContext>)presentationContext completionBlock:(nullable void (^)(BOOL success))completionBlock;

/// Used if a document is signed without a signature form element and a signature area has been drawn by the user.
/// This method will create a signature form element on `rect` on the correct page index of `pageView`.
/// And will initiate the digital signing process.
- (void)selectedSignatureAreaRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

/// The associated signature used for signing the document.
@property (nonatomic, nullable) PSPDFSignatureContainer *signature;

/// Defines which biometric properties, `PSPDFSignatureBiometricProperties`, should be stored in a digital signature, if one is created.
/// Set in the initializer.
@property (nonatomic, readonly) PSPDFSignatureBiometricPropertiesOption signatureBiometricPropertiesOptions;

@end

NS_ASSUME_NONNULL_END
