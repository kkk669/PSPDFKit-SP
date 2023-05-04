//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbar.h>

@class PSPDFToolbarButton;

NS_ASSUME_NONNULL_BEGIN

/// A flexible toolbar with various document editing functions.
///
/// @note This class requires the Document Editor component to be enabled for your license.
PSPDF_CLASS_SWIFT(PDFDocumentEditorToolbar)
@interface PSPDFDocumentEditorToolbar : PSPDFFlexibleToolbar<PSPDFOverridable>

/// Preset button for showing the new page UI.
@property (nonatomic, readonly) PSPDFToolbarButton *addPageButton;

/// Preset button for deleting selected pages.
@property (nonatomic, readonly) PSPDFToolbarButton *deletePagesButton;

/// Preset button for duplicating selected pages.
@property (nonatomic, readonly) PSPDFToolbarButton *duplicatePagesButton;

/// Preset button for rotating selected pages 90 clockwise.
@property (nonatomic, readonly) PSPDFToolbarButton *rotatePagesButton;

/// Preset button for exporting selected pages into a new PDF file.
@property (nonatomic, readonly) PSPDFToolbarButton *exportPagesButton;

/// Preset button for selecting or deselecting all pages.
///
/// @see `allPagesSelected`.
@property (nonatomic, readonly) PSPDFToolbarButton *selectAllPagesButton;

/// Copies the selected pages to the pasteboard.
@property (nonatomic, readonly) PSPDFToolbarButton *copyPagesButton;

/// Copies the selected pages to the pasteboard, and then removes them from the document. (Cut)
@property (nonatomic, readonly) PSPDFToolbarButton *cutPagesButton;

/// Pastes the selected pages from the pasteboard.
@property (nonatomic, readonly) PSPDFToolbarButton *pastePagesButton;

/// Preset button for undoing the last change.
@property (nonatomic, readonly) PSPDFToolbarButton *undoButton;

/// Preset button for redoing the last undo action.
@property (nonatomic, readonly) PSPDFToolbarButton *redoButton;

/// Preset button for dismissing or showing the save UI if changes were made.
@property (nonatomic, readonly) PSPDFToolbarButton *doneButton;

/// Toggles between the select all and select none state for `selectAllPagesButton`.
@property (nonatomic) BOOL allPagesSelected;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFDocumentEditorToolbar (SubclassingHooks)

/// Subclassing hook that allows customization of the visible buttons for the given toolbar length.
///
/// Call `super` and modify the returned array or construct your own toolbar using the preset buttons.
///
/// @note This will get called a lot (to size the toolbar, anchor views, etc.). You should cache the returned buttons or use preset buttons defined on PSPDFDocumentEditorToolbar.
///
/// @property width The maximum available length (in either vertical or horizontal direction) for buttons given the container size. This excludes any button spacing.
/// @return The buttons that should be displayed.
- (NSArray<__kindof PSPDFToolbarButton *> *)buttonsForWidth:(CGFloat)width;

@end

NS_ASSUME_NONNULL_END
