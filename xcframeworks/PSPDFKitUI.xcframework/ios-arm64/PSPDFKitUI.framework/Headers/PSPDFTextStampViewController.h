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
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFStampAnnotation, PSPDFTextStampViewController;

/// Delegate to be notified on actions.
PSPDF_PROTOCOL_SWIFT(TextStampViewControllerDelegate)
@protocol PSPDFTextStampViewControllerDelegate<NSObject>

/// The 'Add' button has been pressed.
- (void)textStampViewController:(PSPDFTextStampViewController *)stampController didCreateAnnotation:(PSPDFStampAnnotation *)stampAnnotation;

@end

/// A view controller that lets users create or edit a custom text annotation stamp.
PSPDF_CLASS_SWIFT(TextStampViewController)
@interface PSPDFTextStampViewController : PSPDFStaticTableViewController<PSPDFOverridable>

/// Initialize controller, optionally with a preexisting stamp, otherwise a new one will be created.
- (instancetype)initWithStampAnnotation:(nullable PSPDFStampAnnotation *)stampAnnotation NS_DESIGNATED_INITIALIZER;

/// Text Stamp controller delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFTextStampViewControllerDelegate> delegate;

/// The custom stamp annotation.
/// If this controller isn't initialized with a stamp, a new one will be created.
/// Will be modified according to the user input.
@property (nonatomic, readonly) PSPDFStampAnnotation *stampAnnotation;

/// The default stamp text if stamp is created. Defaults to nil.
@property (nonatomic, copy, nullable) NSString *defaultStampText;

@end

NS_ASSUME_NONNULL_END
