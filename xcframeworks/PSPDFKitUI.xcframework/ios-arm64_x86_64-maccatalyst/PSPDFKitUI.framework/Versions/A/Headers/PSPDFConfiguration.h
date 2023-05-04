//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>

#import <CoreGraphics/CoreGraphics.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFBookmarkManager.h>
#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFSignatureBiometricProperties.h>
#import <PSPDFKitUI/PSPDFAppearanceModeManager.h>
#import <PSPDFKitUI/PSPDFDocumentSharingViewController.h>
#import <PSPDFKitUI/PSPDFDragAndDropConfiguration.h>
#import <PSPDFKitUI/PSPDFPrintConfiguration.h>
#import <PSPDFKitUI/PSPDFSettingsViewController.h>
#import <PSPDFKitUI/PSPDFSignatureCreationConfiguration.h>
#import <PSPDFKitUI/PSPDFSignatureStore.h>

@class PSPDFAnnotationGroup;
@class PSPDFAnnotationMenuConfiguration;
@class PSPDFDocumentEditorConfiguration;
@class PSPDFGalleryConfiguration;

/// Page Transition. Can be scrolling or something more fancy.
/// See https://pspdfkit.com/guides/ios/customizing-the-interface/document-presentation-options/ for further documentation.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPageTransition) {
    /// Transitions from one spread to another and does not stop scrolling in between two spreads (paginated).
    PSPDFPageTransitionScrollPerSpread,
    /// Scrolls continuously. Ignores `PageMode.double` when scrolling horizontally.
    PSPDFPageTransitionScrollContinuous,
    /// Page curl mode, similar to Apple Books. Not supported with variable sized PDFs.
    PSPDFPageTransitionCurl
} PSPDF_ENUM_SWIFT(PageTransition);

/// Active page mode.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPageMode) {
    /// Always show a single page.
    PSPDFPageModeSingle,
    /// Always show two pages side-by-side.
    PSPDFPageModeDouble,
    /// Show two pages only when the view is sufficiently large and two pages can be shown without too much shrinking.
    PSPDFPageModeAutomatic
} PSPDF_ENUM_SWIFT(PageMode);

/// Active scrolling direction. Only relevant for scrolling page transitions.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFScrollDirection) {
    /// Default horizontal scrolling.
    PSPDFScrollDirectionHorizontal,
    /// Vertical scrolling.
    PSPDFScrollDirectionVertical
} PSPDF_ENUM_SWIFT(ScrollDirection);

/// Current active view mode.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFViewMode) {
    /// Document is visible.
    PSPDFViewModeDocument,
    /// Thumbnails are visible.
    PSPDFViewModeThumbnails,
    /// Shows thumbnails and page editing options.
    PSPDFViewModeDocumentEditor,
    /// Document is visible in content editing mode.
    ///
    /// > Important: Entering this view mode requires the _Content Editing_
    /// > feature to be included in your license.
    PSPDFViewModeContentEditing,
} PSPDF_ENUM_SWIFT(ViewMode);

/// Default action for PDF link annotations.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFLinkAction) {
    /// Link actions are ignored.
    PSPDFLinkActionNone,
    /// Link actions open an `UIAlertView`.
    PSPDFLinkActionAlertView,
    /// Link actions directly open Safari or whichever app is set as the default browser.
    PSPDFLinkActionOpenSafari,
    /// Link actions open in an `SFSafariViewController`, falling back on `PDFWebViewController` for local file URLs.
    PSPDFLinkActionInlineBrowser,
    /// Always uses `PDFWebViewController`.
    /// Not generally recommended but might be required in certain settings for more control.
    PSPDFLinkActionInlineWebViewController
} PSPDF_ENUM_SWIFT(LinkAction);

/// Defines the text selection mode in `TextSelectionView`.
/// Requires `Features.textSelection` to be enabled and `textSelectionEnabled` set to `true`.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFTextSelectionMode) {
    /// Selecting text in regular mode starts after a long-press and results in a
    /// selection with dragging handles.
    PSPDFTextSelectionModeRegular,
    /// Selecting text in simple mode starts almost immediately on touch down and
    /// results in a selection with dragging handles.
    ///
    /// This mode is similar to selecting text in Apple Books and is useful for
    /// applications where highlighting is a main feature.
    PSPDFTextSelectionModeSimple,
    /// Selection mode will be chosen based on input device: selecting text with
    /// finger or Apple Pencil will use regular mode, while selecting text with
    /// trackpad or mouse will use simple mode.
    ///
    /// This mode is recommended for most use cases, as it resembles the standard
    /// system text selection behavior most closely.
    PSPDFTextSelectionModeAutomatic
} PSPDF_ENUM_SWIFT(TextSelectionMode);

/// Defines how annotations, which are drawn, are created.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFDrawCreateMode) {
    /// Every stroke will result in a separate ink annotation.
    /// This creates the maximum number of annotations.
    PSPDFDrawCreateModeSeparate,

    /// Strokes that have the same color/width are merged.
    /// This creates the minimum number of annotations.
    PSPDFDrawCreateModeMergeIfPossible,

    /// Stokes that are drawn close together without too much delay are merged.
    /// This is the default.
    PSPDFDrawCreateModeAutomatic,
} PSPDF_ENUM_SWIFT(DrawCreateMode);

/// Menu options when text is selected on this document.
typedef NS_OPTIONS(NSUInteger, PSPDFTextSelectionMenuAction) {
    /// No text selection actions.
    PSPDFTextSelectionMenuActionNone = 0,
    /// Allow search from selected text.
    PSPDFTextSelectionMenuActionSearch = 1 << 0,
    /// Offers to show "Define" on selected text. Not available for Mac Catalyst (FB6823989 Offer UIReferenceLibraryViewController)
    PSPDFTextSelectionMenuActionDefine = 1 << 1,
    /// Offers a toggle for Wikipedia.
    PSPDFTextSelectionMenuActionWikipedia = 1 << 2,
    /// Allows text-to-speech. To avoid adding duplicate commands, this menu item is always omitted if the Speak Selection accessibility setting is enabled.
    PSPDFTextSelectionMenuActionSpeak = 1 << 3,
    /// Allows sharing content. Also used for image selection.
    PSPDFTextSelectionMenuActionShare = 1 << 4,
    /// Allows copying the selected text.
    PSPDFTextSelectionMenuActionCopy = 1 << 5,
    /// Allows marking up the selected text (highlight/underline/strikeout).
    PSPDFTextSelectionMenuActionMarkup = 1 << 6,
    /// Allows redacting the selected text.
    PSPDFTextSelectionMenuActionRedact = 1 << 7,
    /// Allows creating a link from the selected text.
    PSPDFTextSelectionMenuActionCreateLink = 1 << 8,
    /// Helper that encapsulates all text selection menu actions that create annotations: Text Highlight, Underline, Squiggle, Strikethrough, Redaction, Link.
    /// Removing this from `allowedMenuActions` does not have any effect on whether the annotation creation menu is shown
    /// when long pressing on an empty area of a page.
    /// To remove certain items from the annotation creation menu, use `editableAnnotationTypes` or `createAnnotationMenuGroups` or
    /// disable that menu completely by setting `isCreateAnnotationMenuEnabled` to `false`.
    PSPDFTextSelectionMenuActionAnnotationCreation = (PSPDFTextSelectionMenuActionMarkup | PSPDFTextSelectionMenuActionRedact | PSPDFTextSelectionMenuActionCreateLink),
    /// All text selection entries
    PSPDFTextSelectionMenuActionAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(TextSelectionMenuAction);

/// The thumbnail bar mode controls how the `PDFViewController` displays thumbnails
/// of pages when viewing a document.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFThumbnailBarMode) {
    /// Don't show any thumbnails.
    PSPDFThumbnailBarModeNone,
    /// Show scrubber bar (like Apple Books, `ScrubberBar`)
    PSPDFThumbnailBarModeScrubberBar,
    /// Show scrollable thumbnail bar (`ThumbnailBar`)
    PSPDFThumbnailBarModeScrollable,
    /// Show a floating scrubber bar (`ScrubberBar`)
    PSPDFThumbnailBarModeFloatingScrubberBar
} PSPDF_ENUM_SWIFT(ThumbnailBarMode);

/// Defines where the scrubber but should be shown.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFScrubberBarType) {
    /// The default style: A scrubber bar that lays out its thumbnails along its width.
    PSPDFScrubberBarTypeHorizontal,
    /// Style for a scrubber bar that lays out its thumbnails along its height and sits along the left edge of its container.
    /// (I.e. it draws a border on its _right–hand_ side.)
    PSPDFScrubberBarTypeVerticalLeft,
    /// Style for a scrubber bar that lays out its thumbnails along its height and sits along the right edge of its container view.
    /// (I.e. it draws a border on its _left–hand_ side.)
    PSPDFScrubberBarTypeVerticalRight,
} PSPDF_ENUM_SWIFT(ScrubberBarType);

/// Thumbnail grouping setting for `ThumbnailBarMode.scrollable` and the `ThumbnailViewController`.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFThumbnailGrouping) {
    /// Group double pages when `PageMode.double` is enabled.
    PSPDFThumbnailGroupingAutomatic,
    /// Never group double pages for thumbnails.
    PSPDFThumbnailGroupingNever,
    /// Always group double pages for thumbnails.
    PSPDFThumbnailGroupingAlways
} PSPDF_ENUM_SWIFT(ThumbnailGrouping);

/// Defines when the user interface view should be shown.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFUserInterfaceViewMode) {
    /// Always show the user interface view.
    PSPDFUserInterfaceViewModeAlways,
    /// Show user interface view on touch and first/last page.
    PSPDFUserInterfaceViewModeAutomatic,
    /// Show user interface view on touch.
    PSPDFUserInterfaceViewModeAutomaticNoFirstLastPage,
    /// Never show the user interface view.
    PSPDFUserInterfaceViewModeNever
} PSPDF_ENUM_SWIFT(UserInterfaceViewMode);

/// Defines how the user interface view should animate.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFUserInterfaceViewAnimation) {
    /// Don't animate user interface view appearance.
    PSPDFUserInterfaceViewAnimationNone,
    /// Fade user interface view in/out.
    PSPDFUserInterfaceViewAnimationFade,
    /// Slide user interface view.
    PSPDFUserInterfaceViewAnimationSlide
} PSPDF_ENUM_SWIFT(UserInterfaceViewAnimation);

/// Defines how the search is displayed.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSearchMode) {
    /// Display search results in a modal view.
    PSPDFSearchModeModal,
    /// Display search results inline.
    PSPDFSearchModeInline
} PSPDF_ENUM_SWIFT(SearchMode);

/// Defines where the render status should be displayed.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFRenderStatusViewPosition) {
    /// Display render status view at the top.
    PSPDFRenderStatusViewPositionTop,
    /// Display render status view at the center.
    PSPDFRenderStatusViewPositionCentered
} PSPDF_ENUM_SWIFT(RenderStatusViewPosition);

// Defines what happens when tapping.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFTapAction) {
    /// Nothing happens.
    PSPDFTapActionNone,
    /// Zoom to the center of the user's tap.
    PSPDFTapActionZoom,
    /// Detect text blocks and zoom to the tapped text block.
    PSPDFTapActionSmartZoom,
} PSPDF_ENUM_SWIFT(TapAction);

/// Defines an adaptive value.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAdaptiveConditional) {
    /// The behavior is always disabled.
    PSPDFAdaptiveConditionalNO,
    /// The behavior is always enabled.
    PSPDFAdaptiveConditionalYES,
    /// The behavior is determined adaptively based on the current app state (e.g., current size classes).
    PSPDFAdaptiveConditionalAdaptive
} PSPDF_ENUM_SWIFT(AdaptiveConditional);

/// Defines how the scroll view inset should be set.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFScrollInsetAdjustment) {
    /// Never adjust scroll view insets.
    PSPDFScrollInsetAdjustmentNone,
    /// Adjust scroll view insets if the user interface view elements are always visible
    /// (e.g., `UserInterfaceViewMode.always`, or disabled `shouldHideNavigationBarWithUserInterface`).
    PSPDFScrollInsetAdjustmentFixedElements,
    /// Adjust scroll view insets whenever user interface view elements are visible.
    PSPDFScrollInsetAdjustmentAllElements
} PSPDF_ENUM_SWIFT(ScrollInsetAdjustment) PSPDF_DEPRECATED(11.5, "Using the `scrollViewInsetAdjustment` property has no effect.");

/// Defines when the bookmark indicator should be shown on a page.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPageBookmarkIndicatorMode) {
    /// Never show the bookmark indicator on page views.
    PSPDFPageBookmarkIndicatorModeOff,
    /// Always shows the bookmark indicator on page views.
    PSPDFPageBookmarkIndicatorModeAlwaysOn,
    /// Only display the bookmark indicator when the page is bookmarked.
    PSPDFPageBookmarkIndicatorModeOnWhenBookmarked
} PSPDF_ENUM_SWIFT(PageBookmarkIndicatorMode);

/// Defines the sound player style used for playing back sound annotations.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSoundAnnotationPlayerStyle) {
    /// Sound annotation player that is shown directly on the page, above the sound annotation view.
    PSPDFSoundAnnotationPlayerStyleInline,
    /// Sound annotation player that is shown on the bottom of the view, staying even when changing pages.
    PSPDFSoundAnnotationPlayerStyleBottom
} PSPDF_ENUM_SWIFT(SoundAnnotationPlayerStyle);

/// Possible options for whether signature annotations should be saved.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSignatureSavingStrategy) {
    /// Signature should be always saved, without giving the user a choice.
    /// This setting is ignored if no `signatureStore` is provided.
    PSPDFSignatureSavingStrategyAlwaysSave,
    /// Signature should be never saved, without giving the user a choice. Always showing the new signature creation UI.
    PSPDFSignatureSavingStrategyNeverSave,
    /// Signature should only be saved if selected in the UI. A toggle will be added to the signature creation UI.
    /// This setting is ignored if no `signatureStore` is provided.
    PSPDFSignatureSavingStrategySaveIfSelected
} PSPDF_ENUM_SWIFT(SignatureSavingStrategy);

/// Defines if certificate management/selection should be allowed for digitally signing a document.
///
/// This is only used if your license contains the Digital Signatures component and was originally purchased before the introduction of the Electronic Signatures component in March 2021.
/// If you originally purchased after this date, Digital Signatures does not provide any UI for adding signatures.
/// The Electronic Signatures component does not support selecting certificates.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFSignatureCertificateSelectionMode) {
    /// Certificates should always be selectable.
    PSPDFSignatureCertificateSelectionModeAlways,
    /// Certificates should never be selectable.
    PSPDFSignatureCertificateSelectionModeNever,
    /// Certificates should only be selectable if there are available certificates.
    PSPDFSignatureCertificateSelectionModeIfAvailable
} PSPDF_ENUM_SWIFT(SignatureCertificateSelectionMode);

/// Controls whether spreads can grow larger than the actual view.
/// This can be helpful on smaller screens to make the content more readable.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFConfigurationSpreadFitting) {
    /// Aspect fit results in a spread view having all its pages always visible on
    /// screen. Pages are shown in a size so that everything fits the view.
    PSPDFConfigurationSpreadFittingFit,
    /// Aspect fills the content so that it completely covers the width of the view
    /// for scroll-per-spread layouts and the transverse axis on a continuous scrolling
    /// layout.
    PSPDFConfigurationSpreadFittingFill,
    /// Automatically switches between `.fittingFit` and `fittingFill`,
    /// depending on the vertical size class in use.
    /// If the vertical size class is compact, it uses the fill width mode, otherwise the fit mode.
    PSPDFConfigurationSpreadFittingAdaptive
} PSPDF_ENUM_SWIFT(PDFConfiguration.SpreadFitting);

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFMarkupAnnotationMergeBehavior) {
    /// Never merge markup annotations.
    PSPDFMarkupAnnotationMergeNever = 0,

    /// Attempt to merge markup annotations if the color matches.
    PSPDFMarkupAnnotationMergeIfColorMatches,
} NS_SWIFT_NAME(MarkupAnnotationMergeBehavior);

/// The configuration builder object offers all properties of `PDFConfiguration`
/// in a writable version, in order to build an immutable `PDFConfiguration` object.

/// @see `PDFConfiguration`
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFConfigurationBuilder)
@interface PSPDFConfigurationBuilder : PSPDFBaseConfigurationBuilder
@end

NS_ASSUME_NONNULL_BEGIN

/// A `PDFConfiguration` defines the behavior of a `PDFViewController`.
/// It uses the builder pattern via `PDFConfigurationBuilder` to create an immutable copy via a block.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFConfiguration)
@interface PSPDFConfiguration : PSPDFBaseConfiguration<PSPDFConfigurationBuilder *> <PSPDFOverridable>

// MARK: Appearance Properties

/// Set a page mode defined in the enum. Defaults to `.automatic`.
/// Reloads the view, unless it is set while rotation is active. Thus, one can customize the size change behavior by setting this within a size transition animation block.
/// Ignored when `pageTransition` is set to `.scrollContinuous`.
@property(nonatomic, readonly) PSPDFPageMode pageMode;

/// Defines the page transition. Defaults to `.scrollPerSpread`.
///
/// @warning If you change the property dynamically in `viewWillTransitionToSize:withTransitionCoordinator:`, wait for the transition to finish using the coordinator’s completion block, otherwise the controller will get in an invalid state. Child view controllers get rotation events AFTER the parent view controller, so if you're changing this from a parent viewController, for PSPDFKit the rotation hasn't been completed yet, and your app will eventually crash. In that case, dispatch the work async on the main queue.
/// You might just want to set `updateSettingsForBoundsChangeBlock` and set your properties there.
///
/// @note We enable the `automaticallyAdjustsScrollViewInsets` by default. If you don't want this behavior, subclass `reloadData` and set this property to `false`.
@property (nonatomic, readonly) PSPDFPageTransition pageTransition;

/// Shows first document page alone as "cover mode". Defaults to `true`.
@property (nonatomic, getter=isFirstPageAlwaysSingle, readonly) BOOL firstPageAlwaysSingle;

/// Controls whether spreads can grow larger than the actual view. Defaults to `.adaptive`.
/// This can be helpful on smaller screens to make the content more readable.
///
/// @note This property has no effect if the page transition is anything but `PageTransition.scrollPerSpread` or `PageTransition.scrollContinuous`.
@property (nonatomic, readonly) PSPDFConfigurationSpreadFitting spreadFitting;

/// Only useful for `PageTransition.curl`. Clips the page to its boundaries, not showing a pageCurl on empty background. Defaults to `true`. Set to `false` if your document is variably sized.
@property (nonatomic, readonly) BOOL clipToPageBoundaries;

/// Additional insets to apply to the document scroll view's frame.
///
/// @see `-[PSPDFDocumentViewLayout additionalScrollViewFrameInsets]`
@property (nonatomic, readonly) UIEdgeInsets additionalScrollViewFrameInsets;

/// Additional insets to apply to the layout's content.
///
/// @note This only has an effect if the page transition is either `.scrollPerSpread`
/// or `.scrollContinuous`.
///
/// @see `StackViewLayout.additionalContentInsets`
@property (nonatomic, readonly) UIEdgeInsets additionalContentInsets;

/// Enable/disable page shadow. Defaults to `false`.
@property (nonatomic, getter=isShadowEnabled, readonly) BOOL shadowEnabled;

/// Set default shadowOpacity. Defaults to 0.7.
@property (nonatomic, readonly) CGFloat shadowOpacity;

/// Background color behind the page view.
/// Defaults to a dynamic color which matches the current `UIUserInterfaceStyle`.
@property (nonatomic, readonly) UIColor *backgroundColor;

/// Allowed appearance modes for `BrightnessViewController`. Defaults to `.all`.
/// `.default` is always assumed to be available. Set to only `.default` to disable appearance mode picker UI.
/// This needs to be set before `BrightnessViewController` is presented.
@property (nonatomic, readonly) PSPDFAppearanceMode allowedAppearanceModes;

// MARK: Scroll View Configuration

/// Page scrolling direction. Defaults to `.horizontal`. Only relevant for scrolling page transitions.
@property (nonatomic, readonly) PSPDFScrollDirection scrollDirection;

/// Sets the scroll view inset adjustment mode. Defaults to `ScrollInsetAdjustment.fixedElements`.
/// This is only evaluated for `PageTransition.scrollContinuous` & `ScrollDirection.vertical`.
///
/// @note This is similar to `automaticallyAdjustsScrollViewInsets` but more tailored to PSPDFKit's use case.
/// @warning `UIViewController`’s `automaticallyAdjustsScrollViewInsets` will always be disabled. Don't enable this property.
@property (nonatomic, readonly) PSPDFScrollInsetAdjustment scrollViewInsetAdjustment PSPDF_DEPRECATED(11.5, "Using this property has no effect.");

/// Minimum zoom scale. Defaults to 1.
@property (nonatomic, readonly) float minimumZoomScale;

/// Maximum zoom scale for the scrollview. Defaults to 20.
@property (nonatomic, readonly) float maximumZoomScale;

/// Determines whether the scrolling is locked in a certain direction when interacting with the document's pages.
///
/// The default value of this property is `.adaptive`, which means the directional lock on the underlying scroll view will be enabled
/// or disabled depending on the context in which the document is being presented. Setting explicit `true` or `false` values will directly affect how the scroll view behaves,
/// regardless of presentation context.
@property (nonatomic, readonly) PSPDFAdaptiveConditional documentViewLayoutDirectionalLock;

// MARK: Page Border and Rendering

/// If `true`, shows an `UIActivityIndicatorView` on the top right while page is rendering. Defaults to `true`.
@property (nonatomic, getter=isRenderAnimationEnabled, readonly) BOOL renderAnimationEnabled;

/// Position of render status view. Defaults to `.top`.
@property (nonatomic, readonly) PSPDFRenderStatusViewPosition renderStatusViewPosition;

// MARK: Page Behavior

/// The action that happens when the user double taps somewhere in the document. Defaults to `.smartZoom`.
@property (nonatomic, readonly) PSPDFTapAction doubleTapAction;

/// If set to `true`, automatically focuses on selected form elements. Defaults to `false`.
@property (nonatomic, getter=isFormElementZoomEnabled, readonly) BOOL formElementZoomEnabled;

/// Whether tapping on leading/trailing edges of the document view should trigger changing to the previous/next page.
/// Defaults to `true`.
///
/// Taps detected near the edge cancel the double-tap to zoom gesture so the default margin is quite narrow.
/// This gesture allows fast tapping to quickly browse through a document.
///
/// @see `animateScrollOnEdgeTaps` and `scrollOnEdgeTapMargin` for related properties.
@property (nonatomic, getter=isScrollOnEdgeTapEnabled, readonly) BOOL scrollOnEdgeTapEnabled;

/// Whether to animate scrolling to the previous or next page when tapping the edges of the view.
/// Defaults to `false` to enable very fast browsing through a document.
///
/// This is only effective if `scrollOnEdgeTapEnabled` is set to `true`.
///
/// @note This property has no effect if you are using  `PageTransition.curl`.
@property (nonatomic, getter=animateScrollOnEdgeTaps, readonly) BOOL animateScrollOnEdgeTaps;

/// The margin in points from the view’s sides in which tapping should trigger scrolling to the previous/next page.
/// Defaults to 44.
///
/// This is only effective if `scrollOnEdgeTapEnabled` is set to `true`.
///
/// @note This property has no effect if you are using  `PageTransition.curl`.
@property (nonatomic, readonly) CGFloat scrollOnEdgeTapMargin;

// MARK: Page Actions

/// Set the default link action for pressing on `LinkAnnotation`s. Default is `.openSafari`.
///
/// @note If modal is set in the link, this property has no effect.
@property (nonatomic, readonly) PSPDFLinkAction linkAction;

/// May be used to customize other displayed menu actions when text is selected.
/// Defaults to `[.search, .define, .speak, .share, .copy, .annotationCreation]`.
@property (nonatomic, readonly) PSPDFTextSelectionMenuAction allowedMenuActions;

// MARK: Features

/// Allows text selection. Defaults to `true`.
///
/// @note This implies that the PDF file actually contains text glyphs.
/// Sometimes text is represented via embedded images or vectors, in that case PSPDFKit can't select it.
@property (nonatomic, getter=isTextSelectionEnabled, readonly) BOOL textSelectionEnabled;

/// Allows image selection. Defaults to `true`.
///
/// @note This implies that the image is not in vector format. Only supports a subset of all possible image types in PDF.
/// @warning Will only work if `textSelectionEnabled` is also set to `true`.
@property (nonatomic, getter=isImageSelectionEnabled, readonly) BOOL imageSelectionEnabled;

/// Defines how the text is selected. Defaults to `.automatic`.
@property (nonatomic, readonly) PSPDFTextSelectionMode textSelectionMode;

/// Specifies whether the selection view snaps to word boundaries when selecting text.
///
/// Setting this to `true` will:
/// - adjust the text selection to word boundaries when resize handles are released,
/// - ensure selection starts on a word boundary in `.simple` on Mac Catalyst.
///
/// A new selection always first selects a full word in `.regular`.
/// That's also the case on iOS, regardless of the set selection mode.
///
/// Defaults  `false`.
@property (nonatomic, readonly) BOOL textSelectionShouldSnapToWord;

/// Modify what annotations are editable and can be created. Set to nil to completely disable annotation editing/creation.
/// Defaults to all available annotation strings.
///
/// In the case of `.widget`, whether that type is included in `editableAnnotationTypes`
/// determines whether users can interact with PDF forms to edit form field *values* rather than editing the form elements themselves.
/// In other words, editing the properties like background color or the position of form elements on the page is not supported.
///
/// @warning Some annotation types are only behaviorally different in PSPDFKit but are mapped to basic annotation types,
/// so adding those will only change the creation of those types, not editing.
/// Example: If you add `.ink` but not `.signature`, signatures added in previous session will still be editable (since they are ink annotations).
/// On the other hand, if you set `.signature` but not `.ink`, then your newly created signatures will not be movable.
///
/// @see `PSPDFAnnotation.h` for additional comments.
@property (nonatomic, readonly) NSSet<PSPDFAnnotationString> *editableAnnotationTypes;

/// Shows a custom cell with configurable color presets for the provided annotation types.
/// Defaults to `PSPDFAnnotationTypeAll`. Set to `PSPDFAnnotationTypeNone` to completely disable color presets.
///
/// @note The presets are only displayed if the PSPDFStyleManager returns supported annotation types only.
@property (nonatomic, readonly) PSPDFAnnotationType typesShowingColorPresets;

/// Customize the inspector items globally.
///
/// This currently affects `AnnotationStyleViewController` and `FreeTextAccessoryView`.
///
/// The dictionary is keyed by annotation type (`PSPDFAnnotationString`).
/// The values are either:
/// - an array of arrays of property name strings (see `PSPDFAnnotationStyleKeyGroupedList`)
/// - a block taking an annotation and returning `PSPDFAnnotationStyleKeyGroupedList` for it (see `PSPDFAnnotationStyleBlock`)
///
/// See `AnnotationStyle.Key` for a list of supported keys.
///
/// The block option is especially useful to customize the available inspector properties based on some annotation attributes.
/// (e.g., show callout options based on the free text annotation intentType).
///
/// @note If you want to disable all color editing, be sure to also remove the relevant type from `typesShowingColorPresets` (also available in `PDFConfiguration`).
@property (nonatomic, readonly) NSDictionary<PSPDFAnnotationString, id> *propertiesForAnnotations;

/// Shows a toolbar with text editing options (`FreeTextAccessoryView`) above the keyboard, while editing
/// free text annotations. Defaults to `true`.
/// You need to set this property before the text annotation is edited.
@property (nonatomic, getter=isFreeTextAccessoryViewEnabled, readonly) BOOL freeTextAccessoryViewEnabled;

/// Controls how bookmarks are displayed and managed.
/// While bookmarks have a custom order, the default is set to `BookmarkManager.sortOrderPageBased`.
@property (nonatomic, readonly) PSPDFBookmarkManagerSortOrder bookmarkSortOrder;

/// Sets the page's bookmark indicator mode. Defaults to `.off`.
/// Depending on this mode, a button indicating the current bookmark status of the page will be displayed on the page itself.
/// Tapping the button will toggle the bookmark mode. For customizing the bookmark indicator, see PSPDFBookMarkIndicatorButton.h
///
/// @see bookmarkIndicatorInteractionEnabled
@property (nonatomic, readonly) PSPDFPageBookmarkIndicatorMode bookmarkIndicatorMode;

/// Enables/disables the bookmark indicator's interaction. Defaults to `true`.
/// If this is enabled, tapping the indicator will bookmark on un-bookmark the page it is displayed on.
/// Use this in conjunction with `bookmarkIndicatorMode` to get the desired behavior
///
/// @see bookmarkIndicatorMode
@property (nonatomic, readonly) BOOL bookmarkIndicatorInteractionEnabled;

/// Defines whether it is possible to add multiple bookmarks on the same page via the UI.
/// If this is enabled:
/// - the bookmark list's add button is always enabled.
/// - the bookmark button item removes all bookmarks on a page, if there are any, if tapped.
///
/// This property does not affect adding bookmarks via the bookmark manager,
/// where adding multiple ones for a single page is always supported.
///
/// Defaults to `false`.
@property (nonatomic, readonly) BOOL allowMultipleBookmarksPerPage;

// MARK: User Interface Settings

/// Controls the behavior of the user interface view, defaults to `.automaticNoFirstLastPage`.
///
/// `PDFViewController` can display additional information and interactive elements for the visible
/// document as an overlay called the user interface view. While the elements in the user interface
/// view are controlled by various other configuration properties, `userInterfaceViewMode` controls
/// the initial visibility of the user interface view and whether the visibility is updated on user
/// interaction.
///
/// For immersive reading, the visibility of the navigation bar of the parent navigation controller
/// can be tied to the user interface view by setting `shouldHideNavigationBarWithUserInterface` to
/// `true`, except in `UserInterfaceViewMode.never`. In this mode, the visibility of the navigation
/// bar is left untouched to prevent getting “trapped” inside a `PDFViewController` due to the lack
/// of the back- or close button typically present in the navigation bar.
///
/// @note Explicit, manual calls to `setUserInterfaceVisible(_:animated:)` on a `PDFViewController`
/// always take precedence over the value of this property.
///
/// @warning The visibility of the user interface view is not updated when changing this mode once
/// a `PDFViewController` is on screen! To programmatically show/hide the user interface view, use
/// `setUserInterfaceVisible(_:animated:)` instead.
@property (nonatomic, readonly) PSPDFUserInterfaceViewMode userInterfaceViewMode;

/// Sets the way the user interface view will be animated. Defaults to `.fade`.
@property (nonatomic, readonly) PSPDFUserInterfaceViewAnimation userInterfaceViewAnimation;

/// Changes the user interface style for the contents when displayed inside a half-modal or a popover. Defaults to `.card`.
@property (nonatomic, readonly) PSPDFPresentationHalfModalStyle halfModalStyle;

/// Enables/Disables the bottom document site position overlay.
/// Defaults to `true`. Animatable. Will be added to the userInterfaceView.

/// @note Requires a `setNeedsLayout` on `PSPDFUserInterfaceView` to update if there's no full reload.
@property (nonatomic, getter=isPageLabelEnabled, readonly) BOOL pageLabelEnabled;

/// Enable/disable the top document label overlay.
/// Defaults to `.adaptive`: The document label is shown if there's not enough space to set the navigation bar title instead.
///
/// @note Requires a `setNeedsLayout` on the `PDFViewController` view to update if there's no full reload.
@property (nonatomic, readonly) PSPDFAdaptiveConditional documentLabelEnabled;

/// Automatically hides the user interface when the user starts scrolling to different pages in the document. Defaults to `true`.
@property (nonatomic, readonly) BOOL shouldHideUserInterfaceOnPageChange;

/// Should show the user interface view on `viewWillAppear:`, unless the user interface is disabled. Defaults to `true`.
@property (nonatomic, readonly) BOOL shouldShowUserInterfaceOnViewWillAppear;

/// If the home indicator height should be included when calculating the insets for the document view. Defaults to `false`.
@property (nonatomic, readonly) BOOL shouldAdjustDocumentInsetsByIncludingHomeIndicatorSafeAreaInsets;

/// Allow PSPDFKit to change the title of this view controller.
/// If `true`, the controller title will be set to the document title or `nil`, depending on whether the
/// document label is visible or not. Set to `false`, to manage the viewController title manually.
///
/// Defaults to `true`.
///
/// On Mac Catalyst, we suggest to not show a toolbar and set `allowWindowTitleChange` instead.
@property (nonatomic, readonly) BOOL allowToolbarTitleChange;

/// Mac Catalyst specific: Sets the documentURL and title of the current window.
/// This uses NSDocumentController internally to set the toolbar and set the dirty state.
///
/// This method has no effect on iOS.
/// Defaults to `false`.
@property (nonatomic, readonly) BOOL allowWindowTitleChange;

/// If `true`, the navigation bar will be hidden when the user interface is hidden. If `false`, the navigation will stay
/// shown or hidden depending on the value of `[UINavigationController navigationBarHidden]`. Defaults to `true`.
@property (nonatomic, readonly) BOOL shouldHideNavigationBarWithUserInterface;

/// If `true`, the status bar will always remain hidden (regardless of the `shouldHideStatusBarWithUserInterface` setting).
/// The setting is also passed on to internally created sub-controllers. Defaults to `false`.
@property (nonatomic, readonly) BOOL shouldHideStatusBar;

/// If `true`, the status bar will be hidden when the user interface is hidden. Defaults to `true`.
///
/// @note This setting is ignored when the navigation bar is always visible (`shouldHideNavigationBarWithUserInterface`
/// and `UINavigationController.isNavigationBarHidden` both set to `false`).
@property (nonatomic, readonly) BOOL shouldHideStatusBarWithUserInterface;

/// Defines if the floating redaction info button,
/// that is shown when there are uncommitted redactions in the document,
/// should be shown in the user interface view.
///
/// Defaults to `true`, if the Redaction component is included in the license.
///
/// @note Setting this property will have no effect if the Redaction component is not included in the license.
/// @note When disabling this and you support redaction annotations, applying redactions will need to be handled manually.
@property (nonatomic, readonly) BOOL shouldShowRedactionInfoButton;

/// Whether the usage hint alert should be shown the first time the user selects the redaction tool.
/// Defaults to `true`, if the Redaction component is included in the license.
///
/// @note Setting this property will have no effect if the Redaction component is not included in the license.
@property (nonatomic, readonly) BOOL redactionUsageHintEnabled;

// MARK: Action navigation

/// Shows a floating back button in the lower part of the screen.
/// Used to navigate back to the origin page when navigating via PDF actions.
/// Defaults to `true`.
@property (nonatomic, readonly) BOOL showBackActionButton;

/// Shows a floating forward button in the lower part of the screen.
/// Used to revert the back button navigation action.
/// Defaults to `true`.
@property (nonatomic, readonly) BOOL showForwardActionButton;

/// Adds text labels representing the destination name to the back and forward buttons.
/// Defaults to `true` on iPad and `false` otherwise.
@property (nonatomic, readonly) BOOL showBackForwardActionButtonLabels;

// MARK: Thumbnail Settings

/// Sets the thumbnail bar mode. Defaults to `.floatingScrubberBar`.
@property (nonatomic, readonly) PSPDFThumbnailBarMode thumbnailBarMode;

/// Controls the placement of the scrubber bar. Defaults to `.horizontal`.
///
/// @note Customizing `scrubberBarType` is supported only when `thumbnailBarMode` is `.scrubberBar`.
/// Otherwise, setting this property to any value other than `.horizontal` won't have any effect.
@property (nonatomic, readonly) PSPDFScrubberBarType scrubberBarType;

/// If `true`, the thumbnail bar will not be shown for single page documents. Defaults to `true`.
@property (nonatomic, readonly) BOOL hideThumbnailBarForSinglePageDocuments;

/// Controls the thumbnail grouping. Defaults to `.automatic`.
@property (nonatomic, readonly) PSPDFThumbnailGrouping thumbnailGrouping;

/// The thumbnail size for `ThumbnailViewController` and `PDFDocumentEditorViewController`. Defaults to `CGSizeZero`.
/// If one of the width or height is zero, this dimension will be determined from the page aspect ratio.
/// If both the width and height are zero, the size is automatic and adaptive, based on the page sizes and view size.
@property (nonatomic, readonly) CGSize thumbnailSize;

/// The minimum internal horizontal space between thumbnails in `ThumbnailViewController`.
/// The default depends on the screen size, and is the same as `thumbnailLineSpacing` and each element in `thumbnailMargin`.
@property (nonatomic, readonly) CGFloat thumbnailInteritemSpacing;

/// The minimum internal vertical space between thumbnails in `ThumbnailViewController`.
/// The default depends on the screen size, and is the same as `thumbnailInteritemSpacing` and each element in `thumbnailMargin`.
@property (nonatomic, readonly) CGFloat thumbnailLineSpacing;

/// The external margin around the grid of thumbnails in thumbnail view mode.
/// The default depends on the screen size, with all elements the same as `thumbnailInteritemSpacing` and `thumbnailLineSpacing`.
@property (nonatomic, readonly) UIEdgeInsets thumbnailMargin;

// MARK: Annotation Settings

/// Overlay annotations are faded in. Set global duration for this fade here. Defaults to 0.25.
@property (nonatomic, readonly) CGFloat annotationAnimationDuration;

/// If set to `true`, you can group/ungroup annotations with the multi-select tool.
/// Defaults to `true`.
///
/// @note This is a UI setting that defines if `group` on `PSPDFAnnotation` is evaluated or not.
/// The `group` property is always set for group operations.
@property (nonatomic, readonly) BOOL annotationGroupingEnabled;

/// Controls if markup annotations should be merged. Defaults to `.ifColorMatches`.
@property (nonatomic, readonly) PSPDFMarkupAnnotationMergeBehavior markupAnnotationMergeBehavior;

/// If `true`, a long press or secondary click on an empty space of a page view
/// will present a menu to create new annotations. If `false`, this behavior is
/// disabled.
///
/// If enabled, the annotation creation menu can be customized using the
/// ``createAnnotationMenuGroups`` configuration property or using the
/// ``PSPDFViewControllerDelegate/pdfViewController:menuForCreatingAnnotationAtPoint:onPageView:appearance:suggestedMenu:``
/// delegate method.
///
/// - Note: Presenting the annotation creation menu requires the Annotation
///   Editing component to be enabled for your license.
@property (nonatomic, getter=isCreateAnnotationMenuEnabled, readonly) BOOL createAnnotationMenuEnabled;

/// The array of annotation type groups shown in the annotation creation menu.
/// Annotation types that are not listed in ``editableAnnotationTypes`` will be
/// ignored.
///
/// On iOS 16 and newer, annotation type groups will be separated from each
/// other when the annotation creation menu is presented using secondary click
/// interaction. Otherwise, there's no visual separation between the groups.
///
/// Setting this property to an empty array doesn't prevent the annotation
/// creation menu from being presented, as it may also contain other actions,
/// such as Paste. To disable the annotation creation menu completely, set the
/// ``createAnnotationMenuEnabled`` configuration property to `false`.
///
/// - Note: Presenting the annotation creation menu requires the Annotation
///   Editing component to be enabled for your license.
@property (nonatomic, copy, readonly) NSArray<PSPDFAnnotationGroup *> *createAnnotationMenuGroups;

/// Enables natural drawing for ink annotations. Defaults to `false`.
@property (nonatomic, readonly) BOOL naturalDrawingAnnotationEnabled;

/// The confidence threshold at which the Magic Ink tool should replace the drawn ink with a corresponding
/// shape annotation. This should always be in the range [0, 100], with 100 representing a perfect match.
///
/// Magic Ink uses the tool `.ink` with the variant `.inkMagic`.
///
/// Defaults to 70.
@property (nonatomic, readonly) NSUInteger magicInkReplacementThreshold;

/// Determines whether new annotations are created when strokes end.  Defaults to `.automatic`.
///
/// The PDF spec allows an unlimited number of separate paths per ink annotation object.
/// They all need to have the same color and width.
///
/// @note This does not affect undo - undo is smart and tracks paths individually.
@property (nonatomic, readonly) PSPDFDrawCreateMode drawCreateMode;

/// If `true`, asks the user to specify a custom annotation username ("author")
/// when first creating a new annotation
///
/// This is triggered by the `AnnotationStateManager` changing its state.
///
/// A default name will already be suggested based on the device name.
/// You can change the default username by setting `-[PSPDFDocument defaultAnnotationUsername]`.
/// Defaults to `true`.
@property (nonatomic, readonly) BOOL shouldAskForAnnotationUsername;

/// Controls if a second tap to an annotation that allows inline editing enters edit mode. Defaults to `true`.
/// (The most probable candidate for this is `FreeTextAnnotation`)
@property (nonatomic, readonly) BOOL annotationEntersEditModeAfterSecondTapEnabled;

/// Scrolls to affected page during an undo/redo operation. Defaults to `true`.
@property (nonatomic, readonly) BOOL shouldScrollToChangedPage;

/// Controls the sound annotation player style. Defaults to `.bottom`.
///
/// This must be set in the configuration when the `PDFViewController` is initialized.
/// Applying a configuration that changes this property after loading is not supported.
@property (nonatomic, readonly) PSPDFSoundAnnotationPlayerStyle soundAnnotationPlayerStyle;

// MARK: Annotation Saving

/// Whether PSPDFKit should save automatically in response to certain UI triggers, such as
/// the app entering the background or the view disappearing.
///
/// Defaults to `true` because users generally expect saving to be automatic on iOS.
/// The exact save triggers may change between PSPDFKit versions.
/// See https://pspdfkit.com/guides/ios/annotations/annotation-and-bookmark-saving-triggers/ for details.
///
/// Set this property to `false` if you want to save with different triggers, such as when
/// the user manually requests this. You can save using the `Document` method
/// `save(options:)` or `save(options:completion:)`.
///
/// To fully disable a `Document` from saving, set its `annotationSaveMode` to `.disabled`.
/// See https://pspdfkit.com/guides/ios/annotations/annotation-saving-mechanism/ for details.
///
/// Implement `PDFDocumentDelegate` to be notified when automatic saving succeeds or fails.
@property (nonatomic, getter=isAutosaveEnabled, readonly) BOOL autosaveEnabled;

/// Whether automatic saving should happen on a background thread.
///
/// Defaults to `false`, which means automatic saving will run on the main thread.
///
/// If saving on the main thread is a performance issue due to saving large documents then
/// this property can be set `true` to tell PSPDFKit to auto-save on a background thread.
///
/// @note Make sure that you don't re-create the `Document` object if you enable background saving, otherwise you might
/// run into race conditions where the old object is still saving and the new one might load outdated or corrupted data.
///
/// This property has no effect if automatic saving is disabling by setting `isAutosaveEnabled` to `false`.
/// See `isAutosaveEnabled` for details about automatic saving.
@property (nonatomic, readonly) BOOL allowBackgroundSaving;

/// Describes the time limit for recording sound annotations in seconds. After
/// this time has been reached, the recording will stop.
///
/// Defaults to 300 (= 5 minutes).
@property (nonatomic, readonly) NSTimeInterval soundAnnotationTimeLimit;

/// Defines the default options when a sound annotation is created for recording.
///
/// Defaults to an empty dictionary in which case following set is used:
///
/// AVFormatIDKey: @(kAudioFormatLinearPCM)
/// AVSampleRateKey: @(annotation.rate)           // 22050
/// AVNumberOfChannelsKey: @(annotation.channels) // 1
/// AVLinearPCMBitDepthKey: @(annotation.bits)    // 16
///
/// Make sure to set a combination that are supported in
/// - AVAudioRecorder
/// - AVPlayer
/// - The PDF Specification
///
/// @see PDF Reference 1.7, Chapter 13.3 Sounds and `PSPDFSoundAnnotation` for details.
@property (nonatomic, readonly) NSDictionary<NSString *, id> *soundAnnotationRecordingOptions;

// MARK: Search

/// Controls whether to display search results directly in a PDF, or as a list in a modal.
/// Defaults to `.modal`.
@property (nonatomic, readonly) PSPDFSearchMode searchMode;

/// Use on `searchResultZoomScale` for an automatic scale mode that makes text readable in most cases.
PSPDF_EXPORT const CGFloat PSPDFAutomaticSearchResultZoomScale;

/// If a search result is selected, we scroll to the page to make it visible.
/// Defaults to `PSPDFAutomaticSearchResultZoomScale` to indicate automatic scale based on the
/// result we're zooming into.
///
/// If this is set to 1, no zooming is performed.
/// Increase this to zoom to the search result.
/// This value will be clamped by `maximumZoomScale` and should be set below.
/// Values smaller than 1 and other than `PSPDFAutomaticSearchResultZoomScale` will be clamped to 1 as well.
///
/// @note This value will be used as a guidance. In case the zoom would be too large,
/// we reduce the scale to ensure the object fits the screen.
@property (nonatomic, readonly) CGFloat searchResultZoomScale;

// MARK: Signatures

/// Whether signatures should be saved after creation.
///
/// This will be ignored (and signatures will not be saved) if `signatureStore` is nil.
///
/// Defaults to `.saveIfSelected`, which means the user is given the choice whether to save signatures or not.
///
/// To always save signatures without giving the user the choice, set a `signatureStore` and set `signatureSavingStrategy` to `.alwaysSave`.
@property (nonatomic, readonly) PSPDFSignatureSavingStrategy signatureSavingStrategy;

/// Defines if the user should be able to select certificates for digitally signing a document, when creating a new signature. Defaults to `.ifAvailable`.
///
/// Will always show the certificate button on the signature creation UI, when set to `.always`.
/// Will never show the certificate button on the signature creation UI, when set to `.never`.
/// Will only show the certificate button on the signature creation UI, when there are `registeredSigners`
/// on the shared `PDFSignatureManager`, when set to `.ifAvailable`. This is the default mode.
///
/// This is only used if your license contains the Digital Signatures component and was originally purchased before the introduction of the Electronic Signatures component in March 2021.
/// If you originally purchased after this date, Digital Signatures does not provide any UI for adding signatures.
/// The Electronic Signatures component does not support selecting certificates.
@property (nonatomic, readonly) PSPDFSignatureCertificateSelectionMode signatureCertificateSelectionMode;

/// Defines which biometric properties, `PSPDFSignatureBiometricProperties`, should be stored in a digital signature, if one is created.
/// Defaults to `PSPDFSignatureBiometricPropertiesOptionAll`.
///
/// @note Needs to have Digital Signatures licensed, will be ignored otherwise.
@property (nonatomic, readonly) PSPDFSignatureBiometricPropertiesOption signatureBiometricPropertiesOptions;

/// Enables natural drawing for signatures. Defaults to `true`.
/// This is only used when Electronic Signatures is not enabled and Annotations is enabled in your license from before the introduction of Electronic Signatures.
/// For Electronic Signatures, use `signatureCreationConfiguration` instead.
@property (nonatomic, readonly) BOOL naturalSignatureDrawingEnabled;

/// Configuration for the Electronic Signatures creation UI.
/// Defaults to the default signature creation configuration.
@property (nonatomic, readonly) PSPDFSignatureCreationConfiguration *signatureCreationConfiguration NS_REFINED_FOR_SWIFT;

/// The object that loads and saves signature annotations. You can implement a signature store to use your own backend.
///
/// If Electronic Signatures is enabled in your license then this defaults to nil, which means signatures can’t be saved.
/// To enable simple on-device signature storage, set this to an instance of `KeychainSignatureStore`.
///
/// If Annotations is enabled in your license from before the introduction of Electronic Signatures (and
/// Electronic Signatures is not enabled) then this defaults to an instance of `KeychainSignatureStore`.
///
/// To remove the UI option to choose whether to save signatures and force them to be saved, change the `signatureSavingStrategy` property or set this store to nil.
///
/// Read more about signature storage options at https://pspdfkit.com/guides/ios/signatures/signature-storage/
@property (nonatomic, readonly, nullable) id<PSPDFSignatureStore> signatureStore;

// MARK: Sharing

/// This has been unused since PSPDFKit 9.3 for iOS because `UIActivityViewController` now includes “open in” functionality directly.
PSPDF_EXPORT UIActivityType const PSPDFActivityTypeOpenIn PSPDF_DEPRECATED(11.5, "This has been unused since PSPDFKit 9.3 for iOS because `UIActivityViewController` now includes “open in” functionality directly.");

/// A list of configurations to use when sharing documents.
///
/// Includes a configuration for sharing to `UIActivityViewController` by default.
@property (nonatomic, readonly) NSArray<PSPDFDocumentSharingConfiguration *> *sharingConfigurations;

/// The default sharing destination to be selected when presenting the sharing UI. If not set, the first configuration is chosen.
@property (nonatomic, readonly, nullable) PSPDFDocumentSharingDestination selectedSharingDestination;

/// Options that will be presented by `PDFSettingsViewController`. Defaults to `.default`.
@property (nonatomic, readonly) PSPDFSettingsOptions settingsOptions;

// MARK: Advanced Properties

/// Enable/Disable all internal gesture recognizers. Defaults to `true`.
/// Can be useful if you're doing custom drawing on the `PDFPageView`.
@property (nonatomic, readonly) BOOL internalTapGesturesEnabled;

/// Set this to true to allow this controller to access the parent `navigationBar`/`navigationController` to add custom buttons.
/// Has no effect if there's no `parentViewController`. Defaults to `false`.
///
/// @note When using this feature, you should also implement both `childViewControllerForStatusBarHidden`
/// and `childViewControllerForStatusBarStyle` to return the `PDFViewController` instance that is embedded.
@property (nonatomic, readonly) BOOL useParentNavigationBar;

/// If enabled, will request that all thumbnails are pre-cached in `PDFViewController’s` `viewDidAppear:`. Defaults to `false`.
/// It will also result in `ThumbnailViewController` pre-caching thumbnails in the alternative device orientation.
/// This property being `false` will not prevent `ThumbnailViewController` from pre-caching for the current view size when it appears.
/// Set this to `true` if you want to pre-cache thumbnails if you use the thumbnail view mode a lot.
///
/// @warning Does not delete any cache and doesn't change if set after the controller has been presented.
@property (nonatomic, readonly) BOOL shouldCacheThumbnails;

/// Determines if it should be supported to change the z-index of annotations in the UI.
///
/// If enabled, this will show a section in the annotation inspector to move an annotation. Also shows reorder controls in `AnnotationTableViewController` if changing the z-index is allowed.
///
/// There are more factors, in addition to this property, that are considered, when determining if an annotation can be moved.
///
/// Defaults to `true`.
@property (nonatomic, readonly) BOOL allowAnnotationZIndexMoves;


/// Configure whether the user should be presented with the option to remove digital signatures from PDF documents.
///
/// @note This property will be `true` only if `Annotation.Tool.signature` is included in `PDFConfiguration.editableAnnotationTypes`.
@property (nonatomic, readonly) BOOL allowRemovingDigitalSignatures;

// MARK: Gallery Configuration

/// The configuration used for the gallery system. Defaults to `GalleryConfiguration.default()`.
@property (nonatomic, readonly) PSPDFGalleryConfiguration *galleryConfiguration;

// MARK: Drag and Drop

/// Configures how and where Drag and Drop should work. Defaults to `DragAndDropConfiguration.default())`.
@property (nonatomic, readonly) PSPDFDragAndDropConfiguration *dragAndDropConfiguration;

/// A configuration set up with appropriate settings for image display.
@property (nonatomic, readonly, class) PSPDFConfiguration *imageConfiguration;

/// Configuration options for various document editor controllers.
@property (nonatomic, readonly) PSPDFDocumentEditorConfiguration *documentEditorConfiguration;

// MARK: Menus

/// An object that configures the annotation menu.
@property (nonatomic, readonly) PSPDFAnnotationMenuConfiguration *annotationMenuConfiguration;

@end

@interface PSPDFConfigurationBuilder ()

/// Use this to use specific subclasses instead of the default PSPDF* classes.
/// This works across the whole framework and allows you to subclass all usages of a class.
/// For example add an entry of `PSPDFPageView.class` / `MyCustomPageView.class` to use
/// the custom subclass. (`MyCustomPageView` must be a subclass of `PDFPageView`)
///
/// @throws an exception if the overriding class is not a subclass of the overridden class.
/// @note Only set from the main thread, before you first use the object.
/// Model objects will use the overrideClass entries from the set document instead.
- (void)overrideClass:(Class<PSPDFOverridable>)builtinClass withClass:(nullable Class)subclass;

/// @see PSPDFConfiguration.documentViewLayoutDirectionalLock.
@property (nonatomic) PSPDFAdaptiveConditional documentViewLayoutDirectionalLock;
/// @see PSPDFConfiguration.doubleTapAction.
@property (nonatomic) PSPDFTapAction doubleTapAction;
/// @see PSPDFConfiguration.formElementZoomEnabled.
@property (nonatomic, getter=isFormElementZoomEnabled) BOOL formElementZoomEnabled;
/// @see PSPDFConfiguration.scrollOnEdgeTapEnabled.
@property (nonatomic, getter=isScrollOnEdgeTapEnabled) BOOL scrollOnEdgeTapEnabled;
/// @see PSPDFConfiguration.animateScrollOnEdgeTaps.
@property (nonatomic, getter=animateScrollOnEdgeTaps) BOOL animateScrollOnEdgeTaps;
/// @see PSPDFConfiguration.scrollOnEdgeTapMargin.
@property (nonatomic) CGFloat scrollOnEdgeTapMargin;
/// @see PSPDFConfiguration.textSelectionEnabled.
@property (nonatomic, getter=isTextSelectionEnabled) BOOL textSelectionEnabled;
/// @see PSPDFConfiguration.imageSelectionEnabled.
@property (nonatomic, getter=isImageSelectionEnabled) BOOL imageSelectionEnabled;
/// @see PSPDFConfiguration.textSelectionMode.
@property (nonatomic) PSPDFTextSelectionMode textSelectionMode;
/// @see PSPDFConfiguration.textSelectionShouldSnapToWord.
@property (nonatomic) BOOL textSelectionShouldSnapToWord;
/// @see PSPDFConfiguration.typesShowingColorPresets.
@property (nonatomic) PSPDFAnnotationType typesShowingColorPresets;
/// @see PSPDFConfiguration.propertiesForAnnotations.
@property (nonatomic, copy) NSDictionary<PSPDFAnnotationString, id> *propertiesForAnnotations;
/// @see PSPDFConfiguration.freeTextAccessoryViewEnabled.
@property (nonatomic) BOOL freeTextAccessoryViewEnabled;
/// @see PSPDFConfiguration.bookmarkSortOrder.
@property (nonatomic) PSPDFBookmarkManagerSortOrder bookmarkSortOrder;
/// @see PSPDFConfiguration.bookmarkIndicatorMode.
@property (nonatomic) PSPDFPageBookmarkIndicatorMode bookmarkIndicatorMode;
/// @see PSPDFConfiguration.bookmarkIndicatorInteractionEnabled.
@property (nonatomic) BOOL bookmarkIndicatorInteractionEnabled;
/// @see PSPDFConfiguration.allowMultipleBookmarksPerPage.
@property (nonatomic) BOOL allowMultipleBookmarksPerPage;
/// @see PSPDFConfiguration.internalTapGesturesEnabled.
@property (nonatomic) BOOL internalTapGesturesEnabled;
/// @see PSPDFConfiguration.useParentNavigationBar.
@property (nonatomic) BOOL useParentNavigationBar;
/// @see PSPDFConfiguration.linkAction.
@property (nonatomic) PSPDFLinkAction linkAction;
/// @see PSPDFConfiguration.allowedMenuActions.
@property (nonatomic) PSPDFTextSelectionMenuAction allowedMenuActions;
/// @see PSPDFConfiguration.userInterfaceViewMode.
@property (nonatomic) PSPDFUserInterfaceViewMode userInterfaceViewMode;
/// @see PSPDFConfiguration.userInterfaceViewAnimation.
@property (nonatomic) PSPDFUserInterfaceViewAnimation userInterfaceViewAnimation;
/// @see PSPDFConfiguration.halfModalStyle.
@property (nonatomic) PSPDFPresentationHalfModalStyle halfModalStyle;
/// @see PSPDFConfiguration.thumbnailBarMode.
@property (nonatomic) PSPDFThumbnailBarMode thumbnailBarMode;
/// @see PSPDFConfiguration.pageLabelEnabled.
@property (nonatomic, getter=isPageLabelEnabled) BOOL pageLabelEnabled;
/// @see PSPDFConfiguration.documentLabelEnabled.
@property (nonatomic) PSPDFAdaptiveConditional documentLabelEnabled;
/// @see PSPDFConfiguration.shouldHideUserInterfaceOnPageChange.
@property (nonatomic) BOOL shouldHideUserInterfaceOnPageChange;
/// @see PSPDFConfiguration.shouldShowUserInterfaceOnViewWillAppear.
@property (nonatomic) BOOL shouldShowUserInterfaceOnViewWillAppear;
/// @see PSPDFConfiguration.shouldAdjustDocumentInsetsByIncludingHomeIndicatorSafeAreaInsets.
@property (nonatomic) BOOL shouldAdjustDocumentInsetsByIncludingHomeIndicatorSafeAreaInsets;
/// @see PSPDFConfiguration.allowToolbarTitleChange.
@property (nonatomic) BOOL allowToolbarTitleChange;
/// @see PSPDFConfiguration.allowWindowTitleChange.
@property (nonatomic) BOOL allowWindowTitleChange;
/// @see PSPDFConfiguration.renderAnimationEnabled.
@property (nonatomic, getter=isRenderAnimationEnabled) BOOL renderAnimationEnabled;
/// @see PSPDFConfiguration.renderStatusViewPosition.
@property (nonatomic) PSPDFRenderStatusViewPosition renderStatusViewPosition;
/// @see PSPDFConfiguration.pageMode.
@property (nonatomic) PSPDFPageMode pageMode;
/// @see PSPDFConfiguration.scrubberBarType.
@property (nonatomic) PSPDFScrubberBarType scrubberBarType;
/// @see PSPDFConfiguration.hideThumbnailBarForSinglePageDocuments.
@property (nonatomic) BOOL hideThumbnailBarForSinglePageDocuments;
/// @see PSPDFConfiguration.thumbnailGrouping.
@property (nonatomic) PSPDFThumbnailGrouping thumbnailGrouping;
/// @see PSPDFConfiguration.pageTransition.
@property (nonatomic) PSPDFPageTransition pageTransition;
/// @see PSPDFConfiguration.scrollDirection.
@property (nonatomic) PSPDFScrollDirection scrollDirection;
/// @see PSPDFConfiguration.scrollViewInsetAdjustment.
@property (nonatomic) PSPDFScrollInsetAdjustment scrollViewInsetAdjustment PSPDF_DEPRECATED(11.5, "Setting this property has no effect.");
/// @see PSPDFConfiguration.firstPageAlwaysSingle.
@property (nonatomic, getter=isFirstPageAlwaysSingle) BOOL firstPageAlwaysSingle;
/// @see PSPDFConfiguration.spreadFitting.
@property (nonatomic) PSPDFConfigurationSpreadFitting spreadFitting;
/// @see PSPDFConfiguration.clipToPageBoundaries.
@property (nonatomic) BOOL clipToPageBoundaries;
/// @see PSPDFConfiguration.additionalScrollViewFrameInsets.
@property (nonatomic) UIEdgeInsets additionalScrollViewFrameInsets;
/// @see PSPDFConfiguration.additionalContentInsets.
@property (nonatomic) UIEdgeInsets additionalContentInsets;
/// @see PSPDFConfiguration.minimumZoomScale.
@property (nonatomic) float minimumZoomScale;
/// @see PSPDFConfiguration.maximumZoomScale.
@property (nonatomic) float maximumZoomScale;
/// @see PSPDFConfiguration.shadowEnabled.
@property (nonatomic, getter=isShadowEnabled) BOOL shadowEnabled;
/// @see PSPDFConfiguration.shadowOpacity.
@property (nonatomic) CGFloat shadowOpacity;
/// @see PSPDFConfiguration.shouldHideNavigationBarWithUserInterface.
@property (nonatomic) BOOL shouldHideNavigationBarWithUserInterface;
/// @see PSPDFConfiguration.shouldHideStatusBar.
@property (nonatomic) BOOL shouldHideStatusBar;
/// @see PSPDFConfiguration.shouldHideStatusBarWithUserInterface.
@property (nonatomic) BOOL shouldHideStatusBarWithUserInterface;
/// @see PSPDFConfiguration.backgroundColor.
@property (nonatomic) UIColor *backgroundColor;
/// @see PSPDFConfiguration.allowedAppearanceModes.
@property (nonatomic) PSPDFAppearanceMode allowedAppearanceModes;
/// @see PSPDFConfiguration.thumbnailSize.
@property (nonatomic) CGSize thumbnailSize;
/// @see PSPDFConfiguration.thumbnailInteritemSpacing.
@property (nonatomic) CGFloat thumbnailInteritemSpacing;
/// @see PSPDFConfiguration.thumbnailLineSpacing.
@property (nonatomic) CGFloat thumbnailLineSpacing;
/// @see PSPDFConfiguration.thumbnailMargin.
@property (nonatomic) UIEdgeInsets thumbnailMargin;
/// @see PSPDFConfiguration.annotationAnimationDuration.
@property (nonatomic) CGFloat annotationAnimationDuration;
/// @see PSPDFConfiguration.annotationGroupingEnabled.
@property (nonatomic) BOOL annotationGroupingEnabled;
/// @see PSPDFConfiguration.markupAnnotationMergeBehavior.
@property (nonatomic) PSPDFMarkupAnnotationMergeBehavior markupAnnotationMergeBehavior;
/// @see PSPDFConfiguration.createAnnotationMenuEnabled.
@property (nonatomic, getter=isCreateAnnotationMenuEnabled) BOOL createAnnotationMenuEnabled;
/// @see PSPDFConfiguration.createAnnotationMenuGroups.
@property (nonatomic, copy) NSArray<PSPDFAnnotationGroup *> *createAnnotationMenuGroups;
/// @see PSPDFConfiguration.naturalDrawingAnnotationEnabled.
@property (nonatomic) BOOL naturalDrawingAnnotationEnabled;
/// @see PSPDFConfiguration.magicInkReplacementThreshold.
@property (nonatomic) NSUInteger magicInkReplacementThreshold;
/// @see PSPDFConfiguration.drawCreateMode.
@property (nonatomic) PSPDFDrawCreateMode drawCreateMode;
/// @see PSPDFConfiguration.shouldAskForAnnotationUsername.
@property (nonatomic) BOOL shouldAskForAnnotationUsername;
/// @see PSPDFConfiguration.annotationEntersEditModeAfterSecondTapEnabled.
@property (nonatomic) BOOL annotationEntersEditModeAfterSecondTapEnabled;
/// @see PSPDFConfiguration.editableAnnotationTypes.
@property (nonatomic, copy, nullable) NSSet<PSPDFAnnotationString> *editableAnnotationTypes;
/// @see PSPDFConfiguration.autosaveEnabled.
@property (nonatomic, getter=isAutosaveEnabled) BOOL autosaveEnabled;
/// @see PSPDFConfiguration.allowBackgroundSaving.
@property (nonatomic) BOOL allowBackgroundSaving;
/// @see PSPDFConfiguration.soundAnnotationTimeLimit.
@property (nonatomic) NSTimeInterval soundAnnotationTimeLimit;
/// @see PSPDFConfiguration.soundAnnotationRecordingOptions.
@property (nonatomic) NSDictionary<NSString *, id> *soundAnnotationRecordingOptions;
/// @see PSPDFConfiguration.shouldCacheThumbnails.
@property (nonatomic) BOOL shouldCacheThumbnails;
/// @see PSPDFConfiguration.shouldScrollToChangedPage.
@property (nonatomic) BOOL shouldScrollToChangedPage;
/// @see PSPDFConfiguration.searchMode.
@property (nonatomic) PSPDFSearchMode searchMode;
/// @see PSPDFConfiguration.searchResultZoomScale.
@property (nonatomic) CGFloat searchResultZoomScale;
/// @see PSPDFConfiguration.signatureSavingStrategy.
@property (nonatomic) PSPDFSignatureSavingStrategy signatureSavingStrategy;
/// @see PSPDFConfiguration.signatureCertificateSelectionMode.
@property (nonatomic) PSPDFSignatureCertificateSelectionMode signatureCertificateSelectionMode;
/// @see PSPDFConfiguration.signatureBiometricPropertiesOptions.
@property (nonatomic) PSPDFSignatureBiometricPropertiesOption signatureBiometricPropertiesOptions;
/// @see PSPDFConfiguration.naturalSignatureDrawingEnabled.
@property (nonatomic) BOOL naturalSignatureDrawingEnabled;
/// @see PSPDFConfiguration.signatureCreationConfiguration.
@property (nonatomic) PSPDFSignatureCreationConfiguration *signatureCreationConfiguration NS_REFINED_FOR_SWIFT;
/// @see PSPDFConfiguration.signatureStore.
@property (nonatomic, nullable) id<PSPDFSignatureStore> signatureStore;
/// @see PSPDFConfiguration.galleryConfiguration.
@property (nonatomic) PSPDFGalleryConfiguration *galleryConfiguration;
/// @see PSPDFConfiguration.showBackActionButton.
@property (nonatomic) BOOL showBackActionButton;
/// @see PSPDFConfiguration.showForwardActionButton.
@property (nonatomic) BOOL showForwardActionButton;
/// @see PSPDFConfiguration.showBackForwardActionButtonLabels.
@property (nonatomic) BOOL showBackForwardActionButtonLabels;
/// @see PSPDFConfiguration.shouldShowRedactionInfoButton.
@property (nonatomic) BOOL shouldShowRedactionInfoButton;
/// @see PSPDFConfiguration.redactionUsageHintEnabled.
@property (nonatomic) BOOL redactionUsageHintEnabled;
/// @see PSPDFConfiguration.soundAnnotationPlayerStyle.
@property (nonatomic) PSPDFSoundAnnotationPlayerStyle soundAnnotationPlayerStyle;
/// @see PSPDFConfiguration.dragAndDropConfiguration.
@property (nonatomic) PSPDFDragAndDropConfiguration *dragAndDropConfiguration;
/// @see PSPDFConfiguration.documentEditorConfiguration.
@property (nonatomic) PSPDFDocumentEditorConfiguration *documentEditorConfiguration;
/// @see PSPDFConfiguration.settingsOptions.
@property (nonatomic) PSPDFSettingsOptions settingsOptions;
/// @see PSPDFConfiguration.sharingConfigurations.
@property (nonatomic) NSArray<PSPDFDocumentSharingConfiguration *> *sharingConfigurations;
/// @see PSPDFConfiguration.selectedSharingDestination.
@property (nonatomic, nullable) PSPDFDocumentSharingDestination selectedSharingDestination;
/// @see PSPDFConfiguration.allowAnnotationZIndexMoves.
@property (nonatomic) BOOL allowAnnotationZIndexMoves;
/// @see PSPDFConfiguration.allowRemovingDigitalSignatures.
@property (nonatomic) BOOL allowRemovingDigitalSignatures;
/// @see PSPDFConfiguration.annotationMenuConfiguration.
@property (nonatomic) PSPDFAnnotationMenuConfiguration *annotationMenuConfiguration;

@end

NS_ASSUME_NONNULL_END
