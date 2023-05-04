//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBackForwardButton.h>
#import <PSPDFKitUI/PSPDFLabelView.h>
#import <PSPDFKitUI/PSPDFPageLabelView.h>
#import <PSPDFKitUI/PSPDFRelayTouchesView.h>
#import <PSPDFKitUI/PSPDFScrubberBar.h>
#import <PSPDFKitUI/PSPDFThumbnailBar.h>
#import <UIKit/UIKit.h>

@class PSPDFDocumentLabelView, PSPDFPageLabelView, PSPDFThumbnailBar, PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// Empty subclass for easier debugging.
PSPDF_CLASS_SWIFT(DocumentLabelView)
@interface PSPDFDocumentLabelView : PSPDFLabelView<PSPDFOverridable>
@end

/// The user interface view overlay for the `PDFViewController`. Contains the thumbnail and page/title label overlays.
PSPDF_CLASS_SWIFT(UserInterfaceView)
@interface PSPDFUserInterfaceView : PSPDFRelayTouchesView<PSPDFThumbnailBarDelegate, PSPDFScrubberBarDelegate, PSPDFPageLabelViewDelegate, PSPDFOverridable>

/// Convenience initializer.
- (instancetype)initWithFrame:(CGRect)frame dataSource:(id<PSPDFPresentationContext>)dataSource;

/// The data source.
@property (nonatomic, weak) id<PSPDFPresentationContext> dataSource;

/// Force subview updating.
- (void)layoutSubviewsAnimated:(BOOL)animated;

/// Fetches data again
- (void)reloadData;

/// Specifies the distance between the subviews shown at the bottom and the top of the scrubber bar or the
/// bottom of the screen, depending on whether the scrubber bar is enabled. Defaults to 0,5,10,5.
///
/// @note The subviews shown at the bottom include the page label along with the backward, forward and apply redaction buttons.
@property (nonatomic) UIEdgeInsets pageLabelInsets UI_APPEARANCE_SELECTOR;

/// Specifies the distance between the top document label. Defaults to 10,5,0,5.
@property (nonatomic) UIEdgeInsets documentLabelInsets UI_APPEARANCE_SELECTOR;

/// Insets from self.frame when positioning the scrubber bar. Defaults to 0,0,0,0.
///
/// If you use this to move the scrubber bar above its default position at the bottom of the screen then the bar may stay visible
/// when entering the thumbnails view mode. We recommend hiding the scrubber bar by changing the configuration’s `thumbnailBarMode`
/// in the delegate method `pdfViewController(_ pdfController: PDFViewController, didChange viewMode: ViewMode)`.
@property (nonatomic) UIEdgeInsets scrubberBarInsets UI_APPEARANCE_SELECTOR;

// MARK: Subviews

/// Document title label view.
@property (nonatomic, readonly) PSPDFDocumentLabelView *documentLabel;

/// Document page label view.
@property (nonatomic, readonly) PSPDFPageLabelView *pageLabel;

/// Scrubber bar. Created lazily. Available if `PSPDFThumbnailBarModeScrubberBar` is set.
@property (nonatomic, readonly) PSPDFScrubberBar *scrubberBar;

/// Thumbnail bar. Created lazily. Available if `PSPDFThumbnailBarModeScrollable` is set.
@property (nonatomic, readonly) PSPDFThumbnailBar *thumbnailBar;

/// Back navigation button (PSPDFAction history). Automatically shown / hidden.
@property (nonatomic, readonly) PSPDFBackForwardButton *backButton;

/// Forward navigation button (PSPDFAction history). Automatically shown / hidden.
@property (nonatomic, readonly) PSPDFBackForwardButton *forwardButton;

/// Redaction info button. Shown in the lower trailing corner.
/// Shows a popover to preview or apply uncommitted redaction annotations in the document, when tapped.
///
/// Will only be shown if
/// - the document contains redactions, and
/// - `PSPDFConfiguration.shouldShowRedactionInfoButton` is enabled, and
/// - the license contains the Redaction component.
@property (nonatomic, readonly) PSPDFStyleButton *redactionInfoButton;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFUserInterfaceView (SubclassingHooks)

/// Update these to manually set the frame.
///
/// `dataSource` will not be `nil` when these methods are called.
- (void)updateDocumentLabelFrameAnimated:(BOOL)animated;
- (void)updateThumbnailBarFrameAnimated:(BOOL)animated;
- (void)updateScrubberBarFrameAnimated:(BOOL)animated;

/// Use this method to customize the position of the page label.
///
/// @note The default implementation also sizes the label appropriately. Please call super and then change only the position of the label.
- (void)updatePageLabelFrameAnimated:(BOOL)animated NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
