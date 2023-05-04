//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFStatefulTableViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// An abstract class for a controller that manages a table view with search functionality.
PSPDF_CLASS_SWIFT(SearchableTableViewController)
@interface PSPDFSearchableTableViewController : PSPDFStatefulTableViewController

/// Allows search. Defaults to YES.
///
/// @note The UISearchBar is updated internally during reloading.
/// To customize, use UIAppearance: `[[UISearchBar appearanceWhenContainedIn:PSPDFOutlineViewController.class, nil] setBarStyle:UIBarStyleBlack];`
@property (nonatomic) BOOL searchEnabled;

@end

NS_ASSUME_NONNULL_END

