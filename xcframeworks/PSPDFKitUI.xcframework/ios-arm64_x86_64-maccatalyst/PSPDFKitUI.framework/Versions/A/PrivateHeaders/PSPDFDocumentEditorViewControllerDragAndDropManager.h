//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentEditorViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// Class that manages the Drag and Drop capabilities for a given `PSPDFDocumentEditorViewController` instance.
///
/// This class is also responsible for performing the correct import and export operations for pages
/// in the document editor.
@interface PSPDFDocumentEditorViewControllerDragAndDropManager : NSObject

/// Instantiates a drag and drop manager for the given editor.
- (instancetype)initWithDocumentEditorViewController:(PSPDFDocumentEditorViewController *)editorViewController;

/// Reference to the editor view controller that this manager is associated with.
@property (nonatomic, weak, readonly) PSPDFDocumentEditorViewController *editorViewController;

/// Defines the interactive capabilities of the document editor.
///
/// If `PSPDFDocumentEditorInteractiveCapabilityNone` is set, the document editor won't be able to import images
/// and PDFs, nor export pages to other applications, via drag & drop.
///
/// @see PSPDFDocumentEditorInteractiveCapabilities.
///
/// @note Defaults to `PSPDFDocumentEditorInteractiveCapabilityAll`. When running on iPhone, setting values on this property has no effect.
/// @note This property is forwarded by `PSPDFDocumentEditorViewController`.
@property (nonatomic, assign) PSPDFDocumentEditorInteractiveCapabilities editorInteractiveCapabilities;

/// YES if there's a Drag and Drop session active.
@property (nonatomic, readonly) BOOL isWithinDragAndDropSession;

/// Configures the Drag and Drop capabilities of the editor based on the options provided
/// in the `editorInteractiveCapabilities` property.
- (void)configureInteractiveMovement;

@end

NS_ASSUME_NONNULL_END
