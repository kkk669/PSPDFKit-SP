//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKitUI/PSPDFDocumentInfoViewController.h>

@class PSPDFSectionModel;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDocumentInfoViewController ()

/// Called to update the toolbar items.
- (void)updateToolbarItems;

/// Allow to customize the section models
- (NSArray<PSPDFSectionModel *> *)sectionModels;

/// The delegate that can be used to override classes.
@property (nonatomic, weak) id<PSPDFOverrideProvider> overrideDelegate;

@end

NS_ASSUME_NONNULL_END
