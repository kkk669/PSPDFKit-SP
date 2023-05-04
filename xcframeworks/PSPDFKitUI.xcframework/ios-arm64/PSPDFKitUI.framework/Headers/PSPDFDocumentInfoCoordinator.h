//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFContainerViewController, PSPDFDocumentInfoViewController, PSPDFDocumentInfoCoordinator;

typedef NSString *PSPDFDocumentInfoOption NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(DocumentInfoOption);

/// The outline (Table of Contents) controller.
PSPDF_EXPORT PSPDFDocumentInfoOption const PSPDFDocumentInfoOptionOutline;

/// Bookmark list controller.
PSPDF_EXPORT PSPDFDocumentInfoOption const PSPDFDocumentInfoOptionBookmarks;

/// Annotation list controller. Requires `Features.annotationEditing`.
PSPDF_EXPORT PSPDFDocumentInfoOption const PSPDFDocumentInfoOptionAnnotations;

/// Embedded Files. Requires `Features.annotationEditing`.
PSPDF_EXPORT PSPDFDocumentInfoOption const PSPDFDocumentInfoOptionEmbeddedFiles;

/// Document Metadata.
PSPDF_EXPORT PSPDFDocumentInfoOption const PSPDFDocumentInfoOptionDocumentInfo;

/// Document security options (permissions).
PSPDF_EXPORT PSPDFDocumentInfoOption const PSPDFDocumentInfoOptionSecurity;

@protocol PSPDFDocumentInfoCoordinatorDelegate<NSObject>

@optional

/// Notifies the delegate that the `PSPDFDocumentInfoViewController` has discarded the pending changes
/// and the controller is no longer in edit mode.
///
/// @param infoCoordinator     The coordinator.
/// @param infoViewController  The `PSPDFDocumentInfoViewController` that cancelled the update.
- (void)documentInfoCoordinator:(PSPDFDocumentInfoCoordinator *)infoCoordinator infoViewControllerDidCancelDocumentInfoUpdate:(PSPDFDocumentInfoViewController *)infoViewController;

/// Notifies the delegate that the info view controller has applied the specified updates to the underlying document. Use this method to update the UI if required.
///
/// @param infoCoordinator     The coordinator.
/// @param infoViewController  The controller that applied the updates.
- (void)documentInfoCoordinator:(PSPDFDocumentInfoCoordinator *)infoCoordinator infoViewControllerDidCommitUpdates:(PSPDFDocumentInfoViewController *)infoViewController;

@end

/// Coordinates a common view controller for document metadata, such as outline, bookmarks or annotations.
PSPDF_CLASS_SWIFT(DocumentInfoCoordinator)
@interface PSPDFDocumentInfoCoordinator : NSObject<PSPDFOverridable>

/// Builds and returns the document info view controller.
- (nullable UIViewController *)documentInfoViewController;

/// Present view controller on `targetController`.
///
/// @note The `completion` block will not be called if there's another view
/// controller presented on `targetController`.
- (nullable UIViewController *)presentToViewController:(UIViewController<PSPDFPresentationActions> *)targetController options:(nullable NSDictionary<NSString *, id> *)options sender:(nullable id)sender animated:(BOOL)animated completion:(nullable void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

/// Checks if there's data to present.
@property (nonatomic, getter=isAvailable, readonly) BOOL available;

/// The document attached to the document info coordinator.
@property (nonatomic, nullable) PSPDFDocument *document;

/// This protocol inherits from `PSPDFOverridable` since it's also used to fetch subclasses.
@property (nonatomic, weak) id<PSPDFDocumentInfoCoordinatorDelegate> delegate;

/// Choose the controller type.
/// Defaults to `PSPDFDocumentInfoOptionOutline, PSPDFDocumentInfoOptionAnnotations, PSPDFDocumentInfoOptionBookmarks, PSPDFDocumentInfoOptionEmbeddedFiles, PSPDFDocumentInfoOptionDocumentInfo`, `PSPDFDocumentInfoOptionSecurity`.
///
/// @note Change this before the controller is being displayed.
@property (nonatomic, copy) NSArray<PSPDFDocumentInfoOption> *availableControllerOptions;

/// Called after a controller has been created. Set a block to allow custom modifications.
/// This sets the delegate of the controllers by default. If you set a custom block, ensure to call the previous implementation.
@property (nonatomic, copy, nullable) void (^didCreateControllerBlock)(UIViewController *controller, PSPDFDocumentInfoOption option);

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFDocumentInfoCoordinator (SubclassingHooks)

/// Subclass to allow early controller customization.
- (nullable UIViewController *)controllerForOption:(PSPDFDocumentInfoOption)option;

/// Is used internally to filter unavailable options.
- (BOOL)isOptionAvailable:(PSPDFDocumentInfoOption)option;

@end

NS_ASSUME_NONNULL_END
