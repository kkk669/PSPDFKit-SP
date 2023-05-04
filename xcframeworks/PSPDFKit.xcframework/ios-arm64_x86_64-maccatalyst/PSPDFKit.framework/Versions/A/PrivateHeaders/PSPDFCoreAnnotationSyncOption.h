//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Defines how changes should be synced down to core.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFCoreAnnotationSyncOption) {
    /// The previous behavior: Changes are synced to the base annotation but not flushed down to the
    /// PDFium and related structures.
    ///
    /// If a (new) appearance stream (AP stream) is needed, it is not generated before the next sync of
    /// the annotation provider. This can have unwanted side-effects — particularly for free text
    /// annotations!
    PSPDFCoreAnnotationSyncOptionDeferGeneratingAPStream,

    /// When syncing the annotation, propagate changes all the way down to the PDFium structures.
    ///
    /// When no AP stream exists, a new one will be generated (if possible, that is).
    PSPDFCoreAnnotationSyncOptionGenerateAPStreamWhenNoneExists,

    /// Same as PSPDFCoreAnnotationSyncOptionGenerateAPStreamWhenNoneExists — except we try generating
    /// an AP stream even when a prior one exists.
    PSPDFCoreAnnotationSyncOptionForceGenerateAPStream,
} NS_SWIFT_NAME(CoreAnnotationSyncOption);
