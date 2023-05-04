//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFContainerViewController.h>
#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocument, PSPDFLinkAnnotation, PSPDFLinkAnnotationEditingContainerViewController;

NS_ASSUME_NONNULL_BEGIN

/// Delegate for callbacks on the state of the link annotation editing container view controller.
PSPDF_PROTOCOL_SWIFT(LinkAnnotationEditingContainerViewControllerDelegate)
@protocol PSPDFLinkAnnotationEditingContainerViewControllerDelegate<NSObject>

@optional

/// Called when creating a new link annotation has finished.
///
/// @note The annotation has not yet been added to the document.
/// This is the responsibility of the delegate.
- (void)linkAnnotationEditingContainerViewController:(PSPDFLinkAnnotationEditingContainerViewController *)linkAnnotationEditingContainerViewController didFinishCreatingLinkAnnotation:(PSPDFLinkAnnotation *)linkAnnotation;

/// Called when editing an existing link annotation has finished.
- (void)linkAnnotationEditingContainerViewController:(PSPDFLinkAnnotationEditingContainerViewController *)linkAnnotationEditingContainerViewController didFinishEditingLinkAnnotation:(PSPDFLinkAnnotation *)linkAnnotation;

@end

/// Custom container view controller that displays all the supported controllers (one at a time) to
/// create a new or edit an existing link annotation. The controllers can be switched between using a segmented control.
PSPDF_CLASS_SWIFT(LinkAnnotationEditingContainerViewController)
@interface PSPDFLinkAnnotationEditingContainerViewController : PSPDFContainerViewController

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// Create a link annotation editing container view controller to create a new link annotation on a specified page on a specified area.
///
/// @param document The document that should contain the new link annotation.
/// @param pageIndex The page index for the page that should contain the new link annotation.
/// @param selectedRects Rects in PDF coordinates space that are passed to the newly created link annotation.
- (instancetype)initWithDocument:(PSPDFDocument *)document pageIndex:(PSPDFPageIndex)pageIndex selectedRects:(NSArray<NSValue /* CGRect */ *> *)selectedRects NS_DESIGNATED_INITIALIZER;

/// Create a link annotation editing container view controller to edit an existing link annotation.
///
/// @note The existing link annotation needs to be associated with a document.
///
/// @param linkAnnotation The annotation that should be edited.
- (instancetype)initWithExistingLinkAnnotation:(PSPDFLinkAnnotation *)linkAnnotation NS_DESIGNATED_INITIALIZER;

/// Delegate about changes in the link annotation editing container.
@property (nonatomic, weak) id<PSPDFLinkAnnotationEditingContainerViewControllerDelegate> linkDelegate;

@end

NS_ASSUME_NONNULL_END
