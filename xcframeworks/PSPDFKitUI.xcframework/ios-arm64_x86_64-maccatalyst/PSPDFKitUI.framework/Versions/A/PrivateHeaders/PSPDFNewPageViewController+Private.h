//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFNewPageViewController.h>

@class PSPDFCellModel;

NS_ASSUME_NONNULL_BEGIN

// MARK: Private Subclassing Hooks
@interface PSPDFNewPageViewController ()

/// Cell model used to add a way to allow merging documents.
- (PSPDFCellModel *)selectFileCellModel;

/// Recreates and reloads the table view sections.
- (void)updateSections;

@end

NS_ASSUME_NONNULL_END
