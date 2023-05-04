//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFStatefulTableViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSigner;
@protocol PSPDFCertificatePickerViewControllerDelegate;

/// Displays a view controller to offer selecting a signer for digitally signing a document.
PSPDF_CLASS_SWIFT(CertificatePickerViewController)
@interface PSPDFCertificatePickerViewController : PSPDFStatefulTableViewController<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

///  Initializes the view controller with registered signers.
///  
///  @param registeredSigners Optional. Will use the default shared singleton state if nil.
- (instancetype)initWithRegisteredSigners:(nullable NSArray<PSPDFSigner *> *)registeredSigners NS_DESIGNATED_INITIALIZER;

/// The unsigned form element view controller delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFCertificatePickerViewControllerDelegate> delegate;

@end

/// Delegate for signature status.
PSPDF_PROTOCOL_SWIFT(CertificatePickerViewControllerDelegate)
@protocol PSPDFCertificatePickerViewControllerDelegate<NSObject>

@optional

/// Called when the form element signing process has finished.
- (void)certificatePickerViewController:(PSPDFCertificatePickerViewController *)controller didPickSigner:(nullable PSPDFSigner *)signer;

@end

NS_ASSUME_NONNULL_END
