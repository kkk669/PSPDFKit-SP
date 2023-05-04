//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

// MARK: App specific
#import <PSPDFKitUI/PSPDFBaseTableViewController+Private.h>
#import <PSPDFKitUI/PSPDFCellSelectionView.h>
#import <PSPDFKitUI/PSPDFCircularProgressView.h>
#import <PSPDFKitUI/PSPDFComment.h>
#import <PSPDFKitUI/PSPDFConfiguration+Private.h>
#import <PSPDFKitUI/PSPDFFeedbackGenerator.h>
#import <PSPDFKitUI/PSPDFKeyboardHandlingView.h>
#import <PSPDFKitUI/PSPDFTouchForwardingView.h>
#import <PSPDFKitUI/PSPDFKitGlobal+PSPDFUIPrivate.h>
#import <PSPDFKitUI/PSPDFNewPageViewController+Private.h>
#import <PSPDFKitUI/PSPDFPresentationManager.h>
#import <PSPDFKitUI/PSPDFScrollTouchMode.h>
#import <PSPDFKitUI/PSPDFSearchResultCell.h>
#import <PSPDFKitUI/PSPDFSearchViewController+Private.h>
#import <PSPDFKitUI/PSPDFSearchHeaderView.h>
#import <PSPDFKitUI/PSPDFViewController+Private.h>
#import <PSPDFKitUI/PSPDFTabbedViewController+Private.h>
#import <PSPDFKitUI/PSPDFSettingsViewController+Private.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationPlayback.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationPlaybackController.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationPlaybackBarView.h>
#import <PSPDFKitUI/PSPDFAppearanceModeManager+Private.h>
#import <PSPDFKitUI/PSPDFFilePreviewController.h>
#import <PSPDFKitUI/PSPDFNoteAnnotationViewController+Private.h>
#import <PSPDFKitUI/PSPDFCommentCell.h>
#import <PSPDFKitUI/PSPDFDocumentEditorToolbarController+Private.h>
#import <PSPDFKitUI/PSPDFDocumentEditorCutCopyCoordinator.h>
#import <PSPDFKitUI/PSPDFDocumentSharingViewController+Private.h>
#import <PSPDFKitUI/PSPDFDocumentSharingViewController+Activity.h>
#import <PSPDFKitUI/PSPDFDocumentSharingConfiguration+Private.h>
#import <PSPDFKitUI/PSPDFDocumentSharingContext.h>
#import <PSPDFKitUI/PSPDFDocumentSecurityViewController+Private.h>
#import <PSPDFKitUI/PSPDFDocumentInfoViewController+Private.h>
#import <PSPDFKitUI/PSPDFDocumentEditorViewControllerDragAndDropManager.h>
#import <PSPDFKitUI/PSPDFChoiceFormEditorViewController.h>
#import <PSPDFKitUI/PSPDFRedactionViewController+Private.h>
#import <PSPDFKitUI/PSPDFAnnotationToolbar+Private.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationView.h>
#import <PSPDFKitUI/PSPDFDrawView+Private.h>
#import <PSPDFKitUI/PSPDFAnimatableShapeUpdates.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController+Private.h>
#import <PSPDFKitUI/PSPDFSectionModel.h>
#import <PSPDFKitUI/PSPDFCheckBoxCellModel.h>
#import <PSPDFKitUI/PSPDFContainerViewController+Private.h>
#import <PSPDFKitUI/PSPDFPageCurlViewController.h>
#import <PSPDFKitUI/PSPDFDocumentViewPageViewController.h>

// MARK: Categories
#import <PSPDFKitUI/UIColor+PSPDFCompatible.h>
#import <PSPDFKitUI/UIView+PSPDFAdditions.h>
#import <PSPDFKitUI/UIResponder+PSPDFAdditions.h>
#import <PSPDFKitUI/UIViewController+PSPDFAdditions.h>
#import <PSPDFKitUI/UICollectionView+PSPDFAdditions.h>
#import <PSPDFKitUI/UIWindow+PSPDFAdditions.h>
#import <PSPDFKitUI/PSPDFAnnotationToolbarConfiguration+PSPDFPresets.h>
#import <PSPDFKitUI/UIKeyCommand+PSPDFAdditions.h>
#import <PSPDFKitUI/UIGestureRecognizer+PSPDFAdditions.h>

#import <PSPDFKitUI/PSPDFTextField.h>
#import <PSPDFKitUI/PSPDFTextFieldCell.h>
#import <PSPDFKitUI/PSPDFTextView.h>
#import <PSPDFKitUI/PSPDFWindow.h>
#import <PSPDFKitUI/PSPDFSymbolView.h>
#import <PSPDFKitUI/PSPDFSwitchCell.h>
#import <PSPDFKitUI/PSPDFButtonCell.h>
#import <PSPDFKitUI/PSPDFValue1TableViewCell.h>
#import <PSPDFKitUI/PSPDFCustomTitleCell.h>
#import <PSPDFKitUI/PSPDFToolbarCell.h>
#import <PSPDFKitUI/PSPDFLabel.h>
#import <PSPDFKitUI/PSPDFViewState+Private.h>
#import <PSPDFKitUI/PSPDFBarButtonItem.h>
#import <PSPDFKitUI/PSPDFNavigationItem+Private.h>
#import <PSPDFKitUI/PSPDFPointerHoverEffect.h>
#import <PSPDFKitUI/UIButton+PSPDFAdditions.h>
#import <PSPDFKitUI/PSPDFCheckbox.h>
#import <PSPDFKitUI/PSPDFLabeledCheckbox.h>

// MARK: Tests
#import <PSPDFKitUI/PSPDFURLExecutor.h>
#import <PSPDFKitUI/PSPDFActionExecutor.h>
#import <PSPDFKitUI/PSPDFAnnotationsRenderView.h>
#import <PSPDFKitUI/PSPDFAnnotationViewRendering.h>
#import <PSPDFKitUI/PSPDFAnnotationStateManager+Private.h>
#import <PSPDFKitUI/PSPDFAvoidingScrollView+Private.h>
#import <PSPDFKitUI/PSPDFColorPickerView.h>
#import <PSPDFKitUI/PSPDFDefaultAnnotationViewMapper.h>
#import <PSPDFKitUI/PSPDFDigitalSignatureCoordinator+Private.h>
#import <PSPDFKitUI/PSPDFDocumentViewController+Private.h>
#import <PSPDFKitUI/PSPDFDocumentSharingPageSelectionViewController.h>
#import <PSPDFKitUI/PSPDFDocumentSharingProcessingManager.h>
#import <PSPDFKitUI/PSPDFDocumentView.h>
#import <PSPDFKitUI/PSPDFDocumentView+Private.h>
#import <PSPDFKitUI/PSPDFDocumentViewScrollView.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbar+Private.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarController+Private.h>
#import <PSPDFKitUI/PSPDFFormSubmissionController+Private.h>
#import <PSPDFKitUI/PSPDFGalleryViewController+Private.h>
#import <PSPDFKitUI/PSPDFGalleryItemConfiguration.h>
#import <PSPDFKitUI/PSPDFGalleryItem+Private.h>
#import <PSPDFKitUI/PSPDFGalleryItemResolver.h>
#import <PSPDFKitUI/PSPDFGoToPageActivity.h>
#import <PSPDFKitUI/PSPDFHostingAnnotationView+Private.h>
#import <PSPDFKitUI/PSPDFImageAnnotationCreator.h>
#import <PSPDFKitUI/PSPDFImageEditViewController.h>
#import <PSPDFKitUI/PSPDFKeyboardTracker.h>
#import <PSPDFKitUI/PSPDFMediaPlayerController+Private.h>
#import <PSPDFKitUI/PSPDFMediaPlayerView.h>
#import <PSPDFKitUI/PSPDFMenuItem+Private.h>
#import <PSPDFKitUI/PSPDFNoteAnnotationViewControllerDataProvider.h>
#import <PSPDFKitUI/PSPDFPageView+Private.h>
#import <PSPDFKitUI/PSPDFScrubberBin.h>
#import <PSPDFKitUI/PSPDFScrubberBar+Private.h>
#import <PSPDFKitUI/PSPDFScrubberBarContentView.h>
#import <PSPDFKitUI/PSPDFScrubberBarContentView+Private.h>
#import <PSPDFKitUI/PSPDFScrubberThumbView.h>
#import <PSPDFKitUI/PSPDFAdornmentContainerView.h>
#import <PSPDFKitUI/PSPDFSelectionState+Private.h>
#import <PSPDFKitUI/PSPDFSpeechController+Private.h>
#import <PSPDFKitUI/PSPDFTextMarkupAnnotationCreator.h>
#import <PSPDFKitUI/PSPDFTextSelectionView+Private.h>
#import <PSPDFKitUI/PSPDFViewController+CoreJSExport.h>
#import <PSPDFKitUI/PSPDFReaderViewController+Private.h>
#import <PSPDFKitUI/PSPDFSimplePageViewController.h>
#import <PSPDFKitUI/PSPDFPickerTableViewController+Private.h>
#import <PSPDFKitUI/PSPDFColorPresetsView.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbar+Private.h>
#import <PSPDFKitUI/PSPDFSaveViewController+Private.h>
#import <PSPDFKitUI/PSPDFShapeTemplateTransformer.h>
#import <PSPDFKitUI/PSPDFBasicShapeTemplateTransformer.h>
#import <PSPDFKitUI/PSPDFLineShapeTemplateTransformer.h>
#import <PSPDFKitUI/PSPDFShapeTemplateTransformerRegistry.h>
#import <PSPDFKitUI/PSPDFDocumentViewSpreadCell.h>

// MARK: Instant
#import <PSPDFKitUI/PSPDFAnalyticsEvents+Private.h>
#import <PSPDFKitUI/PSPDFAnnotationPlaceholder+Private.h>
#import <PSPDFKitUI/PSPDFAnnotationPlaceholderView.h>
#import <PSPDFKitUI/PSPDFViewController+Delegates.h>

// MARK: Catalyst
#import <PSPDFKitUI/PSPDFAppKitUIHelper.h>

// MARK: Interactions
#import <PSPDFKitUI/PSPDFInteractionComponent+Private.h>
#import <PSPDFKitUI/PSPDFInteractionComponentCore.h>
#import <PSPDFKitUI/PSPDFInteractionComponentSimpleCore.h>
#import <PSPDFKitUI/PSPDFInteractionComponentCompositeCore.h>
#import <PSPDFKitUI/PSPDFInteractionComponentTransformedCore.h>
#import <PSPDFKitUI/PSPDFGestureRecognizerGroup.h>
#import <PSPDFKitUI/PSPDFComposeMenuInteractionSupport.h>
#import <PSPDFKitUI/PSPDFVisibleAnnotation.h>

// MARK: Swift
#import <PSPDFKitUI/PSPDFImagePicker.h>
#import <PSPDFKitUI/PSPDFImagePickerController+Private.h>
#import <PSPDFKitUI/PSPDFSpreadView+Private.h>
#import <PSPDFKitUI/PSPDFSignatureAnnotationCreator.h>
#import <PSPDFKitUI/PSPDFSoundAnnotationPlaybackCoordinator.h>
#import <PSPDFKitUI/PSPDFColorPicker.h>
#import <PSPDFKitUI/PSPDFAnnotationInsertingCreator.h>
#import <PSPDFKitUI/PSPDFFontSizePickerController.h>
#import <PSPDFKitUI/PSPDFPresentationActions+Private.h>
#import <PSPDFKitUI/PSPDFColorPickerPageViewController.h>
