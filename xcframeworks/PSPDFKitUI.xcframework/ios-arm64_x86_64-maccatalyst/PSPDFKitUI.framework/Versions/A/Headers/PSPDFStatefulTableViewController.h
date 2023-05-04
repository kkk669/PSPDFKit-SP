//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseTableViewController.h>
#import <PSPDFKitUI/PSPDFStatefulViewControlling.h>

NS_ASSUME_NONNULL_BEGIN

/// An abstract class for a controller that manages a table view or shows a label when there is no content for the table view.
PSPDF_CLASS_SWIFT(StatefulTableViewController)
@interface PSPDFStatefulTableViewController : PSPDFBaseTableViewController<PSPDFStatefulViewControlling>

/// Empty view.
@property (nonatomic, nullable) UIView *emptyView;

/// Loading view.
@property (nonatomic, nullable) UIView *loadingView;

/// Receives the current controller state.
///
/// @note This is KVO observable.
@property (nonatomic) PSPDFStatefulViewState controllerState;

/// Sets the controller state and shows/hides the `emptyView`/`loadingView` depending on the state.
- (void)setControllerState:(PSPDFStatefulViewState)controllerState animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
