//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

/// The types of conflicts that PSPDFKit can detect.
typedef NS_ENUM(NSUInteger, PSPDFFileConflictType) {
    /// The document file was deleted while the document is loaded.
    PSPDFFileConflictTypeDeletion = 0,

    /// The document file was modified while the document is loaded has unsaved changes.
    PSPDFFileConflictTypeModification
} PSPDF_ENUM_SWIFT(FileConflictType);

/// Resolution options for conflicts due to out of process file changes or deletion.
typedef NS_ENUM(NSUInteger, PSPDFFileConflictResolution) {
    /// Resolve the conflict by closing the document.
    PSPDFFileConflictResolutionClose = 0,

    /// Resolve the conflict by saving the open document and overriding any file changes.
    /// If the file was deleted it will be restored.
    PSPDFFileConflictResolutionSave,

    /// Discard local changes and reload from file.
    PSPDFFileConflictResolutionReload
} PSPDF_ENUM_SWIFT(FileConflictResolution);
