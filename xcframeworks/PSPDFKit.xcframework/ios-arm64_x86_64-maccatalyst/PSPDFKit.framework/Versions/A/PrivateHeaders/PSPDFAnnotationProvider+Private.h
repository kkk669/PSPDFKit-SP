//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Checks if all annotations are on the same page. Does not compare documents.
PSPDF_EXPORT BOOL PSPDFAnnotationsAreOnSamePage(NSArray<PSPDFAnnotation *> *annotations);

/// Returns annotation from either an array or a single object.
PSPDF_EXPORT PSPDFAnnotation *_Nullable PSPDFFirstAnnotationFromChangeNotification(NSNotification *notification);

/// Sent when a set of annotation updates are expected to be performed in quick succession,
/// e.g., due to adjustments being performed by dragging a slider in the UI.
/// Contains the affected property keys in the `userInfo` dictionary under
/// `PSPDFAnnotationChangedNotificationKeyPathKey`, if relevant.
PSPDF_APP_EXPORT NSNotificationName const PSPDFAnnotationBatchUpdatesWillBeginNotification;

/// Counterpart to `PSPDFAnnotationBatchUpdatesWillBeginNotification`. It is possible that no
/// actual update events are emitted between `PSPDFAnnotationBatchUpdatesWillBeginNotification`
/// and `PSPDFAnnotationBatchUpdatesDidEndNotification`.
/// Contains the affected property keys in the `userInfo` dictionary under
/// `PSPDFAnnotationChangedNotificationKeyPathKey`, if relevant.
PSPDF_APP_EXPORT NSNotificationName const PSPDFAnnotationBatchUpdatesDidEndNotification;

/// Sent when the `hasReplies` property of an annotation changed.
/// Contains the affected annotation as `object`.
/// `userInfo` is `nil`.
/// Will always be posted on the main thread.
PSPDF_APP_EXPORT NSNotificationName const PSPDFAnnotationChangedHasRepliesNotification;

/// User info key to use with `PSPDFAnnotationsAddedNotification`,
/// `PSPDFAnnotationsRemovedNotification` and `PSPDFAnnotationChangedNotification`.
/// If an `NSNumber` wrapping a true value is under this key in the user info then
/// the page will not be re-rendered. Use in internal code that manually calls
/// `notifyAboutRenderResultChanged:` to avoid that being called twice.
PSPDF_EXTERN PSPDFAnnotationOption const PSPDFAnnotationOptionDoNotInvalidateRender;

/// User info key for a `BOOL` to use with the added, changed, or removed annotations.
///
/// Set to `true` (wrapped in an `NSNumber`) if the source of the change is not user-interaction,
/// but a data-import from an external/synced datasource — such as Instant.
/// In these cases, the notification **must not** trigger a new sync. Otherwise, you would cause
/// a sync-feedback-loop.
PSPDF_APP_EXPORT PSPDFAnnotationOption const PSPDFAnnotationOptionIgnoreAsTriggerForSyncing;

NS_ASSUME_NONNULL_END
