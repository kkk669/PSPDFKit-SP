//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFRedactionViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// Posted when the view controller has finished applying the redactions.
PSPDF_EXTERN NSNotificationName const PSPDFRedactionViewControllerDidApplyRedactions;

@interface PSPDFRedactionViewController ()

/// Apply button used to commit redactions in the current document.
@property (nonatomic, readonly) UIButton *applyButton;

/// Apply button used to commit redactions in a new file.
@property (nonatomic, readonly) UIButton *applyAsButton;

/// Target action of the `applyButton`.
- (void)applyButtonPressed:(id)sender;

/// Target action of the `applyAsButton`.
- (void)applyAsButtonPressed:(id)sender;

@end

NS_ASSUME_NONNULL_END
