//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentEditor.h>

NS_ASSUME_NONNULL_BEGIN

/// The PSPDFDocumentEditorCutCopyCoordinator helps the document editor coordinate cuts, copies, and pastes
/// of pages within the current editing session.
///
/// When copying/cutting and pasting pages within the same document, the PSPDFDocumentEditorCutCopyCoordinator
/// makes sure the internal references for those pages in the document are preserved, so that PDF actions still work
/// even after altering the order of the pages.
@interface PSPDFDocumentEditorCutCopyCoordinator : NSObject

/// The current document editor.
@property (nonatomic, nullable) PSPDFDocumentEditor *documentEditor;

/// Whether the coordinator has pages to paste.
@property (nonatomic, readonly) BOOL canPaste;

/// Copies the specified pages.
- (void)copyPages:(NSIndexSet *)pages;

/// Cuts the specified pages.
- (void)cutPages:(NSIndexSet *)pages;

/// Pastes the currently copied or cut pages into the specified index.
- (void)pastePagesAtIndex:(PSPDFPageIndex)pageIndex completion:(void(^)(NSArray<PSPDFEditingChange *> * _Nullable editorChanges, NSError * _Nullable editorError))completion;

@end

NS_ASSUME_NONNULL_END
