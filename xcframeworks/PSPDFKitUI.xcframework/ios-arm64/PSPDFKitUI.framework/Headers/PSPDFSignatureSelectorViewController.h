//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFStatefulTableViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>
#import <PSPDFKitUI/PSPDFSignatureStore.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSignatureSelectorViewController, PSPDFSignatureContainer;

/// Delegate to be notified when the `PSPDFSignatureSelectorViewController` has a valid selection.
PSPDF_PROTOCOL_SWIFT(SignatureSelectorViewControllerDelegate)
@protocol PSPDFSignatureSelectorViewControllerDelegate<NSObject>

/// A signature has been selected.
- (void)signatureSelectorViewController:(PSPDFSignatureSelectorViewController *)signatureSelectorController didSelectSignature:(PSPDFSignatureContainer *)signature;

/// The 'add' button has been pressed.
- (void)signatureSelectorViewControllerWillCreateNewSignature:(PSPDFSignatureSelectorViewController *)signatureSelectorController;

@end

/// Shows a list of signatures from the set `signatureStore`.
PSPDF_CLASS_SWIFT(SignatureSelectorViewController)
@interface PSPDFSignatureSelectorViewController : PSPDFStatefulTableViewController<PSPDFStyleable, PSPDFOverridable>

/// Signature store with signatures that are being displayed.
@property (nonatomic, nullable) id<PSPDFSignatureStore> signatureStore;

/// Signature selector delegate.
///
/// @note The delegate is responsible for handling presenting the UI when creating a new signature,
/// handling insertion of a selected signature, and dismissing the signature selector in these cases.
/// When presenting via built-in UI, the delegate will be set to an internal PSPDFKit object which manages this flow. If you are setting a custom delegate you need to do this yourself.
@property (nonatomic, weak) IBOutlet id<PSPDFSignatureSelectorViewControllerDelegate> delegate;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFSignatureSelectorViewController (SubclassingHooks)

/// Button that will allow adding a new signature.
///
/// @note The toolbar will be set up in `viewWillAppear:`.
@property (nonatomic, readonly) UIBarButtonItem *addSignatureButtonItem;

/// A button that will dismiss the view controller,
/// shown in the navigation bar except when in a popover.
@property (nonatomic, readonly) UIBarButtonItem *doneButtonItem;

// MARK: Actions
- (void)doneAction:(nullable id)sender;
- (void)addSignatureAction:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
