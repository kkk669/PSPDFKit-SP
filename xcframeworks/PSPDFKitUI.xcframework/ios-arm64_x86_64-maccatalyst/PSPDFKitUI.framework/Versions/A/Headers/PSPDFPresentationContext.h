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
#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKitUI/PSPDFControlDelegate.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>
#import <PSPDFKitUI/PSPDFVisiblePagesDataSource.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFKitGlobal, PSPDFConfiguration, PSPDFPageView, PSPDFDocument, PSPDFViewController, PSPDFDocumentViewController, PSPDFAnnotationStateManager, PSPDFAnnotation, PSPDFAnnotationToolbarController;

/// The presentation context is used to provide several parts of the framework with
/// information about what is currently presented in the corresponding `PDFViewController`.
///
/// @note You should never implement `PSPDFPresentationContext` yourself, instead it
/// is created by the framework and handed to you in several places when needed.
PSPDF_PROTOCOL_SWIFT(PresentationContext)
@protocol PSPDFPresentationContext<PSPDFOverridable, PSPDFVisiblePagesDataSource, PSPDFErrorHandler>

/// Accesses the configuration object.
@property (nonatomic, copy, readonly) PSPDFConfiguration *configuration;

/// Access the PSPDFKit singleton store.
@property (nonatomic, readonly) PSPDFKitGlobal *pspdfkit;

/// The displaying view controller and popover/half modal controllers.
@property (nonatomic, readonly) UIViewController<PSPDFPresentationActions> *displayingViewController;

@property (nonatomic, readonly) PSPDFDocumentViewController *documentViewController;

// MARK: General State

/// The associated document.
@property (nonatomic, readonly, nullable) PSPDFDocument *document;

/// Current view mode;
@property (nonatomic, readonly) PSPDFViewMode viewMode;

/// Frame for the visible content, without navigation bar, status bar, side bar.
@property (nonatomic, readonly) CGRect contentRect;

// MARK: varying State

/// Defines if a rotation is currently happening.
@property (nonatomic, getter=isRotationActive, readonly) BOOL rotationActive;

/// Defines if the user interface is visible.
@property (nonatomic, getter=isUserInterfaceVisible, readonly) BOOL userInterfaceVisible;

/// Defines if `viewWillAppear` is currently being called.
@property (nonatomic, getter=isViewWillAppearing, readonly) BOOL viewWillAppearing;

/// Defines if the view is currently reloading.
@property (nonatomic, getter=isReloading, readonly) BOOL reloading;

/// Defines if the view is loaded.
@property (nonatomic, getter=isViewLoaded, readonly) BOOL viewLoaded;

// MARK: Page Views

/// Currently visible page views.
@property (nonatomic, readonly) NSArray<PSPDFPageView *> *visiblePageViews;

/// Returns the page view for the given page index. Will return `nil` if the page view is not loaded.
- (nullable PSPDFPageView *)pageViewForPageAtIndex:(PSPDFPageIndex)pageIndex;

// MARK: Page Numbers

/// Accesses the global annotation state manager.
@property (nonatomic, readonly) PSPDFAnnotationStateManager *annotationStateManager;

/// Annotation toolbar controller used for handling the annotation toolbar.
@property (nonatomic, readonly) PSPDFAnnotationToolbarController *annotationToolbarController;

/// Delegate for control handling.
@property (nonatomic, readonly) id<PSPDFControlDelegate> actionDelegate;

/// Direct access to the `PDFViewController` if required.
@property (nonatomic, readonly) PSPDFViewController *pdfController;

@end

NS_ASSUME_NONNULL_END
