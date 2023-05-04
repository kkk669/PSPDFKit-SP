//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFFormInputAccessoryViewDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/// Notification when someone pressed "Clear Field".
PSPDF_EXPORT NSNotificationName const PSPDFFormInputAccessoryViewDidPressClearButtonNotification;

/// Toolbar for Next|Previous controls for Form Elements.
PSPDF_CLASS_SWIFT(PDFFormInputAccessoryView)
@interface PSPDFFormInputAccessoryView : UIView<PSPDFOverridable>

/// Display Done button. Defaults to YES.
@property (nonatomic) BOOL displayDoneButton;

/// Display Clear button. Defaults to YES.
@property (nonatomic) BOOL displayClearButton;

/// The input accessory delegate.
@property (nonatomic, weak) id<PSPDFFormInputAccessoryViewDelegate> delegate;

/// Trigger toolbar update.
- (void)updateToolbar;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFFormInputAccessoryView (SubclassingHooks)

/// Allow button customizations. Never return nil for these!
@property (nonatomic, readonly) UIBarButtonItem *nextButton;
@property (nonatomic, readonly) UIBarButtonItem *prevButton;
@property (nonatomic, readonly) UIBarButtonItem *doneButton;
@property (nonatomic, readonly) UIBarButtonItem *clearButton;

- (IBAction)nextButtonPressed:(nullable id)sender;
- (IBAction)prevButtonPressed:(nullable id)sender;
- (IBAction)doneButtonPressed:(nullable id)sender;
- (IBAction)clearButtonPressed:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
