//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFConflictResolutionManager.h>

#import <PSPDFKit/PSPDFDocument.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFMultiDocumentViewController;

/// Delegate for the `PSPDFMultiDocumentViewController`.
PSPDF_PROTOCOL_SWIFT(MultiDocumentViewControllerDelegate)
@protocol PSPDFMultiDocumentViewControllerDelegate<NSObject>

@optional

/// Informs the delegate that the `documents` array is about to change.
- (void)multiPDFController:(PSPDFMultiDocumentViewController *)multiPDFController willChangeDocuments:(NSArray<PSPDFDocument *> *)newDocuments;

/// Informs the delegate that the `documents` array has changed.
- (void)multiPDFController:(PSPDFMultiDocumentViewController *)multiPDFController didChangeDocuments:(NSArray<PSPDFDocument *> *)oldDocuments;

/// Informs the delegate that `visibleDocument` is about to change.
- (void)multiPDFController:(PSPDFMultiDocumentViewController *)multiPDFController willChangeVisibleDocument:(nullable PSPDFDocument *)newDocument;

/// Informs the delegate that `visibleDocument` has changed.
- (void)multiPDFController:(PSPDFMultiDocumentViewController *)multiPDFController didChangeVisibleDocument:(nullable PSPDFDocument *)oldDocument;

@end

/// Allows displaying multiple `PSPDFDocuments`.
PSPDF_CLASS_SWIFT(MultiDocumentViewController)
@interface PSPDFMultiDocumentViewController : PSPDFBaseViewController <PSPDFConflictResolutionManagerDelegate>

/// Initialize the controller.
///
/// @param pdfController Set a custom `pdfController` to use a subclass. If nil, a default instance will be created.
/// The passed-in controller will be modified internally and should no longer be used on its own.
/// You probably don’t want to pass a `PDFViewController` that already has a `document` set since the multi-document
/// view controller won’t include that document in its `documents` array. Instead, set the `documents` array after
/// creating the multi-document view controller.
- (instancetype)initWithPDFViewController:(nullable PSPDFViewController *)pdfController NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

/// Currently visible document.
@property (nonatomic, nullable) PSPDFDocument *visibleDocument;

/// Documents that are currently loaded.
@property (nonatomic, copy) NSArray<PSPDFDocument *> *documents;

/// Delegate to capture events.
@property (nonatomic, weak) IBOutlet id<PSPDFMultiDocumentViewControllerDelegate> delegate;

/// Set to YES to enable automatic state persisting. Will be saved to NSUserDefaults. Defaults to NO.
@property (nonatomic) BOOL enableAutomaticStatePersistence;

/// Persists the state to `NSUserDefaults`.
///
/// @warning Will only persist file-based documents, not documents based on NSData or CGDataProviders.
- (void)persistState;

/// Restores state from `NSUserDefaults`. Returns YES on success.
/// Will set the visibleDocument that is saved in the state.
///
/// @warning Despite being marked as a property, this has the behavior of a method.  
@property (nonatomic, readonly) BOOL restoreState;

/// Restores the state and merges with new documents. First document in the array will be visibleDocument.
- (BOOL)restoreStateAndMergeWithDocuments:(NSArray<PSPDFDocument *> *)documents;

/// Defaults to `PSPDFMultiDocumentsPersistKey`.
/// Change if you use multiple instances of `PSPDFMultiDocumentViewController`.
@property (nonatomic, copy) NSString *statePersistenceKey;

/// The embedded `PDFViewController`. Access to customize the properties.
@property (nonatomic, readonly) PSPDFViewController *pdfController;

/// A Boolean value specifying whether thumbnail view mode shows pages from all loaded documents.
/// If `true`, pages are shown from all loaded documents.
/// If `false`, only pages from the current visible document are shown.
/// Defaults to `false`.
@property (nonatomic) BOOL thumbnailViewIncludesAllDocuments;

/// A Boolean value specifying whether `title` should be the title of the current visible document, and therefore shown in the navigation bar or in the overlay.
/// When this is set to `true` and there is enough space available in the navigation bar, the title will be displayed there, if not, the title will be displayed in the overlay.
/// Defaults to `false`, so no title is shown in the navigation bar or in the overlay.
@property (nonatomic) BOOL showTitle;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFMultiDocumentViewController (SubclassingHooks)

/// Override this initializer to allow all use cases (storyboard loading, etc)
///
/// @note The `pdfController` argument might be `nil`, but the property of the same name will be non-nil after calling the superclass’s implementation.
- (void)commonInitWithPDFController:(nullable PSPDFViewController *)pdfController NS_REQUIRES_SUPER;

/// Returns the title of the loaded document at a specified index.
/// Can be subclassed to customize what title should be set.
- (NSString *)titleForDocumentAtIndex:(NSUInteger)idx;

/// Called when the title of the document at `idx` changes.
/// Override this to update views.
- (void)titleDidChangeForDocumentAtIndex:(NSUInteger)idx;

/// Persists the current view state. This method by default persists in an internal dictionary.
/// Called any time the visible document changes at an optimal time to persist the view state.
///
/// @note Can be overridden to disable automatic view state restoration.
- (void)persistViewStateForCurrentVisibleDocument;

/// Restores the current view state from an internal dictionary, if found.
/// Called any time the visible document changes at an optimal time to restore the view state.
///
/// @note Can be overridden to disable automatic view state restoration.
- (void)restoreViewStateForCurrentVisibleDocument;

@end

NS_ASSUME_NONNULL_END
