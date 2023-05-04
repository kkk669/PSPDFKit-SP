//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Abstract class for a controller that manages a table view. Adds support for hardware keyboard navigation,
/// and automatically sizing popovers to fit the table view contents.
PSPDF_CLASS_SWIFT(BaseTableViewController)
@interface PSPDFBaseTableViewController : UITableViewController

// PSPDFKit overrides all kind of event hooks for UIViewController.
// You should always call super in your own view controllers, even if you're just subclassing `UIViewController`.

- (void)viewWillAppear:(BOOL)animated NS_REQUIRES_SUPER;
- (void)viewDidAppear:(BOOL)animated NS_REQUIRES_SUPER;
- (void)viewWillDisappear:(BOOL)animated NS_REQUIRES_SUPER;
- (void)viewDidLayoutSubviews NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
