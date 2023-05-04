//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>

#import <PSPDFKit/PSPDFCoordinatedFileDataProviding.h>
#import <PSPDFKit/PSPDFFileConflictResolution.h>

@class PSPDFConflictResolutionManager, PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

PSPDF_PROTOCOL_SWIFT(ConflictResolutionManagerDelegate)
@protocol PSPDFConflictResolutionManagerDelegate <NSObject>

/// Invoked when the conflict resolution selection completes.
///
/// The implementing object should resolve the file conflict (externally removed or modified file) using the
/// selected conflict resolution option.
///
/// Designed to be invoked from: `controllerForFileDeletionResolutionOnDocument:dataProvider:dataProvider:` and
/// `controllerForExternalFileChangeResolutionOnDocument:dataProvider:dataProvider:`.
///
/// @param manager A reference to the resolution manager that invoked this call.
/// @param document The current document.
/// @param dataProvider The document's data provider that detected the file change.
/// @param resolution The conflict resolution option that should be performed.
/// @param error An optional error describing the failure.
/// @return YES, if the resolution was successful and no otherwise.
- (BOOL)resolutionManager:(PSPDFConflictResolutionManager *)manager requestingFileConflictResolutionForDocument:(PSPDFDocument *)document dataProvider:(id<PSPDFCoordinatedFileDataProviding>)dataProvider withResolution:(PSPDFFileConflictResolution)resolution error:(NSError **)error;

@optional

/// Invoked just before the conflict resolution UI is displayed.
///
/// This callback can be used to suppress UI presentation and instead perform a conflict resolution
/// action immediately.
///
/// @param manager A reference to the resolution manager that invoked this call.
/// @param document The current document.
/// @param dataProvider The document's data provider that detected the file change.
/// @param type The type of conflict that is being resolved.
/// @param resolution The conflict resolution option that should be performed. A default value is passed based on the conflict type. This can be modified by assigning a new value to `*resolution`.
- (BOOL)resolutionManager:(PSPDFConflictResolutionManager *)manager shouldPerformAutomaticResolutionForForDocument:(PSPDFDocument *)document dataProvider:(id<PSPDFCoordinatedFileDataProviding>)dataProvider conflictType:(PSPDFFileConflictType)type resolution:(inout PSPDFFileConflictResolution *)resolution;

/// Specifies the view controller that should be used for UI presentation.
///
/// If not implemented or if the specified view controller is not currently being displayed,
/// the topmost view controller reachable from last known window will be used to display UI during a conflict.
///
/// @note Called on the main thread.
///
/// @param manager A reference to the resolution manager that invoked this call.
/// @return A view controller suitable for modal UI presentation.
- (UIViewController *)viewControllerForPresentationForResolutionManager:(PSPDFConflictResolutionManager *)manager;

@end

/// Handles conflict resolution UI presentation in response to a `PSPDFDocumentUnderlyingFileChangedNotification`.
/// Invokes the delegate to perform the selected conflict resolution option when done.
///
/// @warning This class manages UI and it's methods should only be used on the main thread.
PSPDF_CLASS_SWIFT(ConflictResolutionManager)
@interface PSPDFConflictResolutionManager : NSObject<PSPDFOverridable>

/// An object performing the selected conflict resolution actions.
@property (nonatomic, weak) id<PSPDFConflictResolutionManagerDelegate> delegate;

/// Parses the change notification and presents an appropriate UI for conflict resolution.
///
/// @param notification A forwarded `PSPDFDocumentUnderlyingFileChangedNotification` notification object.
- (void)handleUnderlyingFileChangedNotification:(NSNotification *)notification;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFConflictResolutionManager (SubclassingHooks)

/// Presents UI for file conflict resolution for a deleted source file.
///
/// The presented actions should invoke the
/// `resolutionManager:requestingFileConflictResolutionForDocument:dataProvider:withResolution:`, delegate
/// passing the `document`, `dataProvider` and the selected conflict resolution option.
///
/// @param document The document who's file was deleted.
/// @param dataProvider The data provider that detected the change and can be used for conflict resolution.
/// @return A view controller with conflict resolution options. By default a `UIAlertController` instance. If `nil` is returned, no UI will be presented an a default resolution applied (removing the document from the view controller).
- (nullable UIViewController *)controllerForFileDeletionResolutionOnDocument:(PSPDFDocument *)document dataProvider:(id<PSPDFCoordinatedFileDataProviding>)dataProvider;

/// Presents UI for file conflict resolution for an externally modified source file.
///
/// The presented actions should invoke the
/// `resolutionManager:requestingFileConflictResolutionForDocument:dataProvider:withResolution:`, delegate
/// passing the `document`, `dataProvider` and the selected conflict resolution option.
///
/// @param document The document who's file was externally modified.
/// @param dataProvider The data provider that detected the change and can be used for conflict resolution
/// @return A view controller with conflict resolution options. By default a `UIAlertController` instance. If `nil` is returned, no UI will be presented an a default resolution applied (reloading the document to reflect the external change).
- (nullable UIViewController *)controllerForExternalFileChangeResolutionOnDocument:(PSPDFDocument *)document dataProvider:(id<PSPDFCoordinatedFileDataProviding>)dataProvider;

@end

NS_ASSUME_NONNULL_END
