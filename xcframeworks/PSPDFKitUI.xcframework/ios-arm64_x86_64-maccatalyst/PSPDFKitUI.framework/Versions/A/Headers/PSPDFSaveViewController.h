//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDirectory, PSPDFSaveViewController;

PSPDF_PROTOCOL_SWIFT(SaveViewControllerDelegate)
@protocol PSPDFSaveViewControllerDelegate<NSObject>

/// Called when the done button is pressed, and the file should be saved to the selected location.
/// The delegate needs to handle the actual saving process.
///
/// @note This will be called with a temporary URL if `PSPDFDirectory.documentPickerDirectory` has been selected,
/// to allow the document picker to move the file to the final location. You should not rely on that file to persist at the temporary location.
///
/// @param controller The current save view controller.
/// @param url The URL the file should be saved to, considering the current `selectedSaveDirectory`.
/// @param completionHandler Call the completion handler once saving finished with the final URL the file was saved to,
/// or if an error occurred before or during saving.
/// If an error is provided, an alert is shown with the error's `localizedDescription` as content.
- (void)saveViewController:(PSPDFSaveViewController *)controller saveFileToURL:(NSURL *)url completionHandler:(void (^)(NSURL *_Nullable url, NSError *_Nullable error))completionHandler;

/// Called when the save view controller finished with a selected URL.
/// This will only ever be called after the completion handler of
/// `-saveViewController:saveFileToURL:completionHandler:` has been called.
///
/// You should dismiss the save controller in this delegate.
- (void)saveViewController:(PSPDFSaveViewController *)controller didFinishWithURL:(NSURL *)url;

/// Called when the directory save view controller cancelled.
/// You should dismiss the save controller in this delegate.
- (void)saveViewControllerDidCancel:(PSPDFSaveViewController *)controller;

@end

/// The directory save view controller enables users to enter a custom file name and
/// chose a directory to save a file to.
///
/// Internal callers might show a `UIDocumentPickerViewController` if `saveDirectories` contains
/// only `Directory.documentPickerDirectory`, and it is selected when the done button is pressed.
PSPDF_CLASS_SWIFT(SaveViewController)
@interface PSPDFSaveViewController: PSPDFStaticTableViewController<PSPDFOverridable>

PSPDF_DEFAULT_TABLEVIEWCONTROLLER_INIT_UNAVAILABLE

/// Create a new directory save view controller instance with predefined save directories.
///
/// @param saveDirectories Predefined save directories. Needs to have at least one item.
- (instancetype)initWithSaveDirectories:(NSArray<PSPDFDirectory *> *)saveDirectories NS_DESIGNATED_INITIALIZER;

/// Set save directories.
@property (nonatomic, readonly) NSArray<PSPDFDirectory *> *saveDirectories;

/// The currently selected save directory.
/// Will be set to the first entry of `saveDirectories` by default.
@property (nonatomic) PSPDFDirectory *selectedSaveDirectory;

/// The delegate to react to changes and to handle saving the file.
@property (nonatomic, weak) id<PSPDFSaveViewControllerDelegate> delegate;

/// Shows a directory picker based on the set save directories.
/// Defaults to YES.
@property (nonatomic) BOOL showDirectoryPicker;

/// The desired file name. Might not always be a valid file name (may have illegal characters).
@property (nonatomic, copy, nullable) NSString *fileName;

/// The resulting full path with the PDF extension. Considers the filename and selected directory.
/// Will be `nil`, if `fileName` is not a valid.
@property (nonatomic, nullable, readonly) NSString *fullFilePath;

@end

NS_ASSUME_NONNULL_END
