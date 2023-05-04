//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTabbedViewController.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFTabbedViewController ()

@property (nonatomic, readonly, getter=isTabbedBarHidden) BOOL tabbedBarHidden;

/// Asks the delegate whether to allow the change, and notifies the delegate after changing.
- (void)userRequestedChangingToVisibleDocumentAtIndex:(NSUInteger)newVisibleDocumentIndex scrollToVisible:(BOOL)shouldScrollTabToVisible completionHandler:(nullable void (^)(BOOL success))completionHandler;

/// Asks the delegate whether to allow the change, and notifies the delegate after changing.
- (void)userRequestedClosingDocumentAtIndex:(NSUInteger)indexOfDocumentToClose completionHandler:(nullable void (^)(BOOL success))completionHandler;

/// Same as - userRequestedClosingDocumentAtIndex:, but acts on the currently visible document.
- (void)userRequestedClosingVisibleDocument;

/// Attempts to close all documents except for the currently visible one.
- (void)userRequestedClosingAllOtherDocuments:(NSUInteger)closeOtherIndex;

/// Attempts to close all documents on the tabbed view controller
- (void)userRequestedClosingAllDocuments;

/// The index of the currently visible document.
@property (nonatomic, readonly) NSUInteger currentIndex;

// MARK: - Private Subclassing Hooks

/// Called to check if the visible document should be changed.
///
/// @param newVisibleDocument The document to change to, or nil if there is no new document.
/// @return `true` if the visible document should be changed, else `false`.
- (BOOL)shouldChangeVisibleDocument:(nullable PSPDFDocument *)newVisibleDocument;

/// Called when the visible document changes. Subclasses must call super.
- (void)didChangeVisibleDocumentFromOldVisibleDocument:(nullable PSPDFDocument *)oldVisibleDocument NS_SWIFT_NAME(didChangeVisibleDocument(from:)) NS_REQUIRES_SUPER;

/// Called when the document is closed. Subclasses must call super.
- (void)didCloseDocument:(PSPDFDocument *)document NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
