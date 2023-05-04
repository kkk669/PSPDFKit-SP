//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKit/PSPDFLinkAnnotation.h>

@class PSPDFAction, PSPDFDocument;
@protocol PSPDFLinkAnnotationEditingViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

/// Abstract class for view controllers that support link annotation creation
/// and editing.
PSPDF_CLASS_SWIFT(LinkAnnotationEditingViewController)
@interface PSPDFLinkAnnotationEditingViewController: PSPDFBaseViewController

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// Designated initializer to create a new link annotation editing view controller.
///
/// @param document Document where the new or the edited link annotation should be or is part of.
/// @param action If editing an existing link annotation, this should be the existing action of the link.
- (instancetype)initWithDocument:(PSPDFDocument *)document existingAction:(nullable PSPDFAction *)action NS_DESIGNATED_INITIALIZER;

/// Document where the new or the edited link annotation should be or is part of.
@property (nonatomic, readonly) PSPDFDocument *document;

/// If editing an existing link annotation, this should be the existing action of the link.
@property (nonatomic, readonly, nullable) PSPDFAction *existingAction;

/// The final link action. Usually be called from the presenter once creation or editing
/// has been finished, when the Done button was tapped.
@property (nonatomic, nullable, readonly) PSPDFAction *linkAction;

/// Delegate to be notified of potential changes.
@property (nonatomic, weak) id<PSPDFLinkAnnotationEditingViewControllerDelegate> delegate;

/// The link type the created/edited link should have.
@property (nonatomic, readonly) PSPDFLinkAnnotationType linkType;

@end

/// Protocol for delegate actions of the link annotation editing view controller.
PSPDF_PROTOCOL_SWIFT(LinkAnnotationEditingViewControllerDelegate)
@protocol PSPDFLinkAnnotationEditingViewControllerDelegate<NSObject>

/// Can be used to control if the done button of the presenter should be enabled or disabled.
- (void)linkAnnotationEditingViewController:(PSPDFLinkAnnotationEditingViewController *)linkAnnotationEditingViewController shouldEnableDoneButton:(BOOL)doneButtonEnabled;

@end

NS_ASSUME_NONNULL_END
