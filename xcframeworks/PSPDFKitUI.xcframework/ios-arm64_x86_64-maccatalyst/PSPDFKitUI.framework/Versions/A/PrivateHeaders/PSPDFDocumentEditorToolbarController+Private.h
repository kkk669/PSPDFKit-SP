//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentEditorToolbarController.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFDocumentEditorToolbarControllerEditorActionDelegate

/// Some editor actions should be disabled if there's an in-flight dragging session reordering pages in the document.
///
/// This method asks the editor if the user is currently reordering pages so that we can decide whether or not to process the editor action.
///
/// @return BOOL indicating if there's an active drag session in flight.
- (BOOL)isWithinDragAndDropSession;

@end

@interface PSPDFDocumentEditorToolbarController ()

/// Delegate to determine if the editor actions can be processed.
@property (nonatomic, weak) id<PSPDFDocumentEditorToolbarControllerEditorActionDelegate> editorActionDelegate;

/// Refreshes the toolbar buttons on the document editor view controller to reflect the current
/// state and capabilities of the editor.
///
/// @param animated    Whether the update should animate.
- (void)updateToolbarButtonsAnimated:(BOOL)animated;

/// Adds the target actions to all the document editor toolbar button items.
- (void)setUpActionsForToolbar;

@end

NS_ASSUME_NONNULL_END
