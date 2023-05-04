//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFSignatureStatus.h>
#import <PSPDFKitUI/PSPDFBaseTableViewController.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFSignatureFormElement, PSPDFX509;

@protocol PSPDFSignedFormElementViewControllerDelegate;

///  Shows the current signature state of a PSPDFSignatureFormElement.
PSPDF_CLASS_SWIFT(SignedFormElementViewController)
@interface PSPDFSignedFormElementViewController : PSPDFBaseTableViewController<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Inits the signed view controller with a signature form element.
/// Using this initializer will the allow removal of signatures.
/// Use `-initWithSignatureFormElement:allowRemovingSignature:` initializer
/// to control the removal of digital signatures if needed.
///
/// @param element Element which contains the signature. Should not be nil.
- (instancetype)initWithSignatureFormElement:(PSPDFSignatureFormElement *)element;

/// Initializes the signed view controller with the signature form element and
/// whether the digital signature can be removed from the element.
///
/// @param element Element which contains the signature. Should not be nil.
/// @param allowRemovingSignature Removing digital signatures is allowed or not.
- (instancetype)initWithSignatureFormElement:(PSPDFSignatureFormElement *)element allowRemovingSignature:(BOOL)allowRemovingSignature NS_DESIGNATED_INITIALIZER;

/// The signature form element the controller was initialized with.
@property (nonatomic, strong, readonly) PSPDFSignatureFormElement *formElement;

///  Verifies the signature of the `formElement` set.
///  
///  @param trustedCertificates Optional. Uses the default shared state if not set.
- (nullable PSPDFSignatureStatus *)verifySignatureWithTrustedCertificates:(nullable NSArray<PSPDFX509 *> *)trustedCertificates error:(NSError **)error;

/// The signed form element view controller delegate
@property (nonatomic, weak) IBOutlet id<PSPDFSignedFormElementViewControllerDelegate> delegate;

@end

PSPDF_PROTOCOL_SWIFT(SignedFormElementViewControllerDelegate)
@protocol PSPDFSignedFormElementViewControllerDelegate<NSObject>

@optional

/// Called when a signature was successfully removed from the document.
- (void)signedFormElementViewController:(PSPDFSignedFormElementViewController *)controller removedSignatureFromDocument:(PSPDFDocument *)document;

@end

NS_ASSUME_NONNULL_END
