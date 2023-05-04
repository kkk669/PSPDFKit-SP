//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

@class PSPDFSigner;

NS_ASSUME_NONNULL_BEGIN

/// Cell that is used for displaying a signature.
/// Displays a label and an image beneath each other.
PSPDF_CLASS_SWIFT(SignatureCell)
@interface PSPDFSignatureCell : UITableViewCell<PSPDFOverridable>

/// Label with a green tint color that is shown on top of the cell.
/// Will be hidden if no certificate/signer is selected.
@property (nonatomic, readonly) UIControl *certificateLabel;

/// Image view that will show its image centered.
/// Used for the signature annotation image.
@property (nonatomic, readonly) UIImageView *signatureImageView;

/// Updates the cell for a signer.
/// Will show the signer's display name in the certificate label if available.
/// Will hide the certificate label when `signer` is `nil`.
///
/// @note If you provide your own `certificateLabel`, executing this method won't do anything. You need to override this method in that case.
- (void)updateCellForSigner:(nullable PSPDFSigner *)signer;

@end

NS_ASSUME_NONNULL_END
