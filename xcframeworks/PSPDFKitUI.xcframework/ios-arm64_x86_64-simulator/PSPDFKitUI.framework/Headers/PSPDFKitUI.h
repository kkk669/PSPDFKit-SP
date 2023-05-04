//
//  Copyright © 2010-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !__has_feature(objc_arc)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#endif

#if __has_feature(modules)
// Required to avoid 'non-modular import in framework header' errors when compiling Swift
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
@import PSPDFKit;
#pragma clang diagnostic pop
#else
#import <PSPDFKit/PSPDFKit.h>
#endif

// MARK: Common
#import <PSPDFKitUI/PSPDFApplication.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>
#import <PSPDFKitUI/PSPDFControlDelegate.h>
#import <PSPDFKitUI/PSPDFErrorHandler.h>
#import <PSPDFKitUI/PSPDFExternalURLHandler.h>
#import <PSPDFKitUI/PSPDFKitGlobal+PSPDFUI.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>
#import <PSPDFKitUI/PSPDFSelectionState.h>
#import <PSPDFKitUI/PSPDFViewState.h>

// MARK: Controllers
#import <PSPDFKitUI/PSPDFActivityViewController.h>
#import <PSPDFKitUI/PSPDFAnnotationGridViewController.h>
#import <PSPDFKitUI/PSPDFAnnotationStyleViewController.h>
#import <PSPDFKitUI/PSPDFAnnotationTableViewController.h>
#import <PSPDFKitUI/PSPDFBaseTableViewController.h>
#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFBrightnessViewController.h>
#import <PSPDFKitUI/PSPDFContainerViewController.h>
#import <PSPDFKitUI/PSPDFDocumentSharingViewController.h>
#import <PSPDFKitUI/PSPDFDocumentSharingConfiguration.h>
#import <PSPDFKitUI/PSPDFFontPickerViewController.h>
#import <PSPDFKitUI/PSPDFImagePickerController.h>
#import <PSPDFKitUI/PSPDFDocumentInfoViewController.h>
#import <PSPDFKitUI/PSPDFDocumentSecurityViewController.h>
#import <PSPDFKitUI/PSPDFMultiDocumentViewController.h>
#import <PSPDFKitUI/PSPDFNavigationController.h>
#import <PSPDFKitUI/PSPDFNoteAnnotationViewController.h>
#import <PSPDFKitUI/PSPDFPickerTableViewController.h>
#import <PSPDFKitUI/PSPDFReaderViewController.h>
#import <PSPDFKitUI/PSPDFSavedAnnotationsViewController.h>
#import <PSPDFKitUI/PSPDFScreenController.h>
#import <PSPDFKitUI/PSPDFSettingsViewController.h>
#import <PSPDFKitUI/PSPDFSignatureSelectorViewController.h>
#import <PSPDFKitUI/PSPDFSignatureViewController.h>
#import <PSPDFKitUI/PSPDFStampViewController.h>
#import <PSPDFKitUI/PSPDFStatefulTableViewController.h>
#import <PSPDFKitUI/PSPDFStatefulViewControlling.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>
#import <PSPDFKitUI/PSPDFTextStampViewController.h>
#import <PSPDFKitUI/PSPDFViewController.h>
#import <PSPDFKitUI/PSPDFViewControllerDelegate.h>
#import <PSPDFKitUI/PSPDFViewController+ScreenshotService.h>
#import <PSPDFKitUI/PSPDFWebViewController.h>

// MARK: Main Views
#import <PSPDFKitUI/PSPDFBackForwardButton.h>
#import <PSPDFKitUI/PSPDFUserInterfaceView.h>
#import <PSPDFKitUI/PSPDFMediaPlayerCoverView.h>
#import <PSPDFKitUI/PSPDFPageLabelView.h>
#import <PSPDFKitUI/PSPDFPageView+AnnotationMenu.h>
#import <PSPDFKitUI/PSPDFPageView.h>
#import <PSPDFKitUI/PSPDFRelayTouchesView.h>
#import <PSPDFKitUI/PSPDFContainerView.h>
#import <PSPDFKitUI/PSPDFTextSelectionView.h>
#import <PSPDFKitUI/PSPDFStyleButton.h>

// MARK: Document View
#import <PSPDFKitUI/PSPDFDocumentViewController.h>
#import <PSPDFKitUI/PSPDFDocumentViewLayout.h>
#import <PSPDFKitUI/PSPDFStackViewLayout.h>
#import <PSPDFKitUI/PSPDFScrollPerSpreadLayout.h>
#import <PSPDFKitUI/PSPDFContinuousScrollingLayout.h>
#import <PSPDFKitUI/PSPDFSpreadView.h>
#import <PSPDFKitUI/PSPDFSpreadScrollPosition.h>
#import <PSPDFKitUI/PSPDFDocumentViewSpreadMode.h>

// MARK: Annotations
#import <PSPDFKitUI/PSPDFAnnotationCell.h>
#import <PSPDFKitUI/PSPDFAnnotationPlaceholder.h>
#import <PSPDFKitUI/PSPDFAnnotationSetCell.h>
#import <PSPDFKitUI/PSPDFAnnotationSetsCell.h>
#import <PSPDFKitUI/PSPDFAnnotationStateManager.h>
#import <PSPDFKitUI/PSPDFAnnotationView.h>
#import <PSPDFKitUI/PSPDFAnnotationPresenting.h>
#import <PSPDFKitUI/PSPDFColorButton.h>
#import <PSPDFKitUI/PSPDFDrawView.h>
#import <PSPDFKitUI/PSPDFEraseOverlay.h>
#import <PSPDFKitUI/PSPDFFormElementView.h>
#import <PSPDFKitUI/PSPDFFormInputAccessoryView.h>
#import <PSPDFKitUI/PSPDFFormInputAccessoryViewDelegate.h>
#import <PSPDFKitUI/PSPDFFreeTextAccessoryView.h>
#import <PSPDFKitUI/PSPDFFreeTextAnnotationView.h>
#import <PSPDFKitUI/PSPDFHostingAnnotationView.h>
#import <PSPDFKitUI/PSPDFLinkAnnotationBaseView.h>
#import <PSPDFKitUI/PSPDFLinkAnnotationView.h>
#import <PSPDFKitUI/PSPDFNoteAnnotationView.h>
#import <PSPDFKitUI/PSPDFSelectionView.h>
#import <PSPDFKitUI/PSPDFSignatureCell.h>
#import <PSPDFKitUI/PSPDFSignatureStore.h>

// MARK: Forms
#import <PSPDFKitUI/PSPDFButtonFormElementView.h>
#import <PSPDFKitUI/PSPDFChoiceFormElementView.h>
#import <PSPDFKitUI/PSPDFFormRequest.h>
#import <PSPDFKitUI/PSPDFFormSubmissionDelegate.h>
#import <PSPDFKitUI/PSPDFFormSubmissionController.h>
#import <PSPDFKitUI/PSPDFTextFieldFormElementView.h>

// MARK: Search
#import <PSPDFKitUI/PSPDFInlineSearchManager.h>
#import <PSPDFKitUI/PSPDFSearchHighlightView.h>
#import <PSPDFKitUI/PSPDFSearchHighlightViewManager.h>
#import <PSPDFKitUI/PSPDFSearchViewController.h>
#import <PSPDFKitUI/UISearchController+PSPDFAdditions.h>

// MARK: Full-Text Search
#import <PSPDFKitUI/PSPDFDocumentPickerCell.h>
#import <PSPDFKitUI/PSPDFDocumentPickerController.h>
#import <PSPDFKitUI/PSPDFDocumentPickerIndexStatusCell.h>

// MARK: View Modes
#import <PSPDFKitUI/PSPDFControllerState.h>
#import <PSPDFKitUI/PSPDFViewModePresenter.h>

// MARK: Thumbnails
#import <PSPDFKitUI/PSPDFCollectionReusableFilterView.h>
#import <PSPDFKitUI/PSPDFPageCell.h>
#import <PSPDFKitUI/PSPDFScrubberBar.h>
#import <PSPDFKitUI/PSPDFThumbnailBar.h>
#import <PSPDFKitUI/PSPDFThumbnailGridViewCell.h>
#import <PSPDFKitUI/PSPDFThumbnailViewController.h>

// MARK: Document Editor
#import <PSPDFKitUI/PSPDFDocumentEditorCell.h>
#import <PSPDFKitUI/PSPDFDocumentEditorToolbar.h>
#import <PSPDFKitUI/PSPDFDocumentEditorToolbarController.h>
#import <PSPDFKitUI/PSPDFDocumentEditorViewController.h>
#import <PSPDFKitUI/PSPDFNewPageViewController.h>
#import <PSPDFKitUI/PSPDFSaveViewController.h>

// MARK: Outline
#import <PSPDFKitUI/PSPDFOutlineCell.h>
#import <PSPDFKitUI/PSPDFOutlineViewController.h>

// MARK: Tabbed Bar
#import <PSPDFKitUI/PSPDFMultiDocumentListController.h>
#import <PSPDFKitUI/PSPDFTabbedBar.h>
#import <PSPDFKitUI/PSPDFTabbedViewController.h>

// MARK: Embedded Files
#import <PSPDFKitUI/PSPDFEmbeddedFileCell.h>
#import <PSPDFKitUI/PSPDFEmbeddedFilesViewController.h>
#import <PSPDFKitUI/PSPDFViewController+EmbeddedFileSupport.h>

// MARK: Bookmarks
#import <PSPDFKitUI/PSPDFBookmarkCell.h>
#import <PSPDFKitUI/PSPDFBookmarkIndicatorButton.h>
#import <PSPDFKitUI/PSPDFBookmarkViewController.h>
#import <PSPDFKitUI/PSPDFThumbnailTextCell.h>

// MARK: Toolbar
#import <PSPDFKitUI/PSPDFAnnotationGroupItem+PSPDFPresets.h>
#import <PSPDFKitUI/PSPDFAnnotationToolbar.h>
#import <PSPDFKitUI/PSPDFAnnotationToolbarController.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbar.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarContainer.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarController.h>
#import <PSPDFKitUI/PSPDFToolbar.h>
#import <PSPDFKitUI/PSPDFToolbarButton.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarDragView.h>

// MARK: Action Coordinators
#import <PSPDFKitUI/PSPDFDocumentInfoCoordinator.h>
#import <PSPDFKitUI/PSPDFPrintConfiguration.h>

// MARK: Helpers
#import <PSPDFKitUI/PSPDFAppearanceModeManager.h>
#import <PSPDFKitUI/PSPDFBrightnessManager.h>
#import <PSPDFKitUI/PSPDFMenuItem.h>
#import <PSPDFKitUI/PSPDFNavigationItem.h>
#import <PSPDFKitUI/PSPDFNetworkActivityIndicatorManager.h>
#import <PSPDFKitUI/PSPDFSpeechController.h>
#import <PSPDFKitUI/PSPDFStatusHUD.h>
#import <PSPDFKitUI/PSPDFStyleable.h>
#import <PSPDFKitUI/PSPDFThumbnailFlowLayout.h>
#import <PSPDFKitUI/PSPDFUsernameHelper.h>
#import <PSPDFKitUI/PSPDFVisiblePagesDataSource.h>
#import <PSPDFKitUI/PSPDFSegmentImageProviding.h>
#import <PSPDFKitUI/PSPDFConflictResolutionManager.h>
#import <PSPDFKitUI/PSPDFInitialStartingPointGesture.h>

// MARK: Electronic Signatures
#import <PSPDFKitUI/PSPDFSignatureCreationConfiguration.h>

// MARK: Digital Signatures
#import <PSPDFKitUI/PSPDFSignedFormElementViewController.h>
#import <PSPDFKitUI/PSPDFCertificatePickerViewController.h>
#import <PSPDFKitUI/PSPDFDigitalSignatureCoordinator.h>

// MARK: Gallery
#import <PSPDFKitUI/PSPDFGalleryConfiguration.h>
#import <PSPDFKitUI/PSPDFGalleryContainerView.h>
#import <PSPDFKitUI/PSPDFGalleryContentCaptionView.h>
#import <PSPDFKitUI/PSPDFGalleryContentView.h>
#import <PSPDFKitUI/PSPDFGalleryContentViewProtocols.h>
#import <PSPDFKitUI/PSPDFGalleryImageContentView.h>
#import <PSPDFKitUI/PSPDFGalleryImageItem.h>
#import <PSPDFKitUI/PSPDFGalleryItem.h>
#import <PSPDFKitUI/PSPDFGalleryItem+Subclassing.h>
#import <PSPDFKitUI/PSPDFGalleryManifest.h>
#import <PSPDFKitUI/PSPDFGalleryUnknownItem.h>
#import <PSPDFKitUI/PSPDFGalleryVideoContentView.h>
#import <PSPDFKitUI/PSPDFGalleryVideoItem.h>
#import <PSPDFKitUI/PSPDFGalleryView.h>
#import <PSPDFKitUI/PSPDFGalleryViewController.h>
#import <PSPDFKitUI/PSPDFGalleryWebContentView.h>
#import <PSPDFKitUI/PSPDFGalleryWebItem.h>
#import <PSPDFKitUI/PSPDFMediaPlayerController.h>
#import <PSPDFKitUI/PSPDFMultimediaAnnotationView.h>
#import <PSPDFKitUI/PSPDFMultimediaViewController.h>
#import <PSPDFKitUI/PSPDFPresentationActions.h>

// MARK: Apple Pencil Support
#import <PSPDFKitUI/PSPDFApplePencilManager.h>
#import <PSPDFKitUI/PSPDFApplePencilController.h>

// MARK: Assisting Views
#import <PSPDFKitUI/PSPDFAvoidingScrollView.h>
#import <PSPDFKitUI/PSPDFButton.h>
#import <PSPDFKitUI/PSPDFLabelView.h>
#import <PSPDFKitUI/PSPDFResizableView.h>
#import <PSPDFKitUI/PSPDFRoundedLabel.h>
#import <PSPDFKitUI/PSPDFSelectableCollectionViewCell.h>
#import <PSPDFKitUI/PSPDFSpinnerCell.h>
#import <PSPDFKitUI/PSPDFTableViewCell.h>
#import <PSPDFKitUI/PSPDFProgressLabelView.h>

// MARK: Analytics
#import <PSPDFKitUI/PSPDFAnalytics.h>
#import <PSPDFKitUI/PSPDFAnalyticsEvents.h>
#import <PSPDFKitUI/PSPDFKitGlobal+Analytics.h>

// MARK: Link Editing
#import <PSPDFKitUI/PSPDFLinkAnnotationEditingContainerViewController.h>
#import <PSPDFKitUI/PSPDFLinkAnnotationEditingViewController.h>
#import <PSPDFKitUI/PSPDFPageLinkAnnotationEditingViewController.h>
#import <PSPDFKitUI/PSPDFWebsiteLinkAnnotationEditingViewController.h>

// MARK: Interactions
#import <PSPDFKitUI/PSPDFInteractionComponent.h>
#import <PSPDFKitUI/PSPDFAnnotationSelectionContext.h>
#import <PSPDFKitUI/PSPDFAnnotationTransformationContext.h>
#import <PSPDFKitUI/PSPDFDocumentViewInteractions.h>
#import <PSPDFKitUI/PSPDFFastScrollContext.h>
#import <PSPDFKitUI/PSPDFSmartZoomContext.h>
#import <PSPDFKitUI/PSPDFAnnotationMenuConfiguration.h>
#import <PSPDFKitUI/PSPDFEditMenuAppearance.h>

// MARK: Swift API
#import <PSPDFKitUI/PSPDFKitUI-Swift.h>

#if !__has_feature(objc_arc)
#pragma clang diagnostic pop
#endif
