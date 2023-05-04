//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFStaticTableViewController, PSPDFCellModel;

/// Defines the content for a section in `UITableView`.
PSPDF_APP_CLASS_SWIFT(SectionModel)
@interface PSPDFSectionModel : NSObject

+ (instancetype)sectionWithTitle:(nullable NSString *)headerTitle cells:(nullable NSArray<__kindof PSPDFCellModel *> *)cells;

@property (nonatomic, copy, nullable) NSString *headerTitle;
@property (nonatomic, copy, nullable) NSString *footerTitle;
@property (nonatomic, nullable) UIView *headerView;
@property (nonatomic, nullable) UIView *footerView;

/// Reading this will include `editingCellModels`.
@property (nonatomic, copy, nullable) NSArray<__kindof PSPDFCellModel *> *cells;

/// Invoke to update the section model.
@property (nonatomic, copy, nullable) void (^updateBlock)(__kindof PSPDFStaticTableViewController *viewController, __kindof PSPDFSectionModel *sectionModel);

/// Calls `updateBlock` if it exists.
- (void)updateWithViewController:(PSPDFStaticTableViewController *)viewController;

@end

NS_ASSUME_NONNULL_END
