//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentEditor.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFFlexibleToolbarContainer.h>
#import <PSPDFKitUI/PSPDFViewModePresenter.h>
#import <UIKit/UIKit.h>

/// The interactive capabilities of the document editor.
typedef NS_OPTIONS(NSUInteger, PSPDFDocumentEditorInteractiveCapabilities) {
    PSPDFDocumentEditorInteractiveCapabilityNone = 0,

    /// The editor accepts dropped PDFs from other applications.
    PSPDFDocumentEditorInteractiveCapabilityImportPDFs = 1 << 0,

    /// The editor accepts dropped images from other applications.
    PSPDFDocumentEditorInteractiveCapabilityImportImages = 1 << 1,

    /// The editor can export pages to other applications
    PSPDFDocumentEditorInteractiveCapabilityExportPages = 1 << 2,

    /// The editor can accept PDF and images, and export pages to other applications.
    PSPDFDocumentEditorInteractiveCapabilityAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(PDFDocumentEditorViewController.InteractiveCapabilities);

@class PSPDFDocumentEditorToolbarController;

NS_ASSUME_NONNULL_BEGIN

/// The main view controller for document editing. Shows a collection view with page thumbnails that
/// reflect the document editor changes. Selection is performed on this object and the selection state
/// is then forwarded to `toolbarController`.
///
/// @note This class requires the Document Editor component to be enabled for your license.
PSPDF_CLASS_SWIFT(PDFDocumentEditorViewController)
@interface PSPDFDocumentEditorViewController : UICollectionViewController <PSPDFViewModePresenter, PSPDFDocumentEditorDelegate, PSPDFFlexibleToolbarContainerDelegate, PSPDFOverridable>

/// Class used for thumbnails. Defaults to `PSPDFDocumentEditorCell` and customizations should be a subclass of thereof.
///
/// @see `-[PSPDFViewModePresenter cellClass]`
@property (nonatomic) Class cellClass;

/// The associated document editor. The document editor is automatically generated when a document is assigned.
/// Alternatively one can be assigned manually via this property.
///
/// @note Will be nil, if the document is `nil` or document editing is not supported for that document.
@property (nonatomic, nullable) PSPDFDocumentEditor *documentEditor;

/// Manages the document editor toolbar.
///
/// @note The toolbar is not automatically displayed.
@property (nonatomic, readonly) PSPDFDocumentEditorToolbarController *toolbarController;

/// Defines the interactive capabilities of the document editor.
///
/// If `PSPDFDocumentEditorInteractiveCapabilityNone` is set, the document editor won't be able to import images
/// and PDFs, nor export pages to other applications, via drag & drop.
///
/// @see PSPDFDocumentEditorInteractiveCapabilities.
///
/// @note Defaults to `PSPDFDocumentEditorInteractiveCapabilityAll`. When running on iPhone, setting values on this property has no effect.
@property (nonatomic, assign) PSPDFDocumentEditorInteractiveCapabilities editorInteractiveCapabilities;

@end

NS_ASSUME_NONNULL_END
