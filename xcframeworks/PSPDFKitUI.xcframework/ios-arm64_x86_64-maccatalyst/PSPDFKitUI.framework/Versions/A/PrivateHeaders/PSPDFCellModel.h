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

@class PSPDFStaticTableViewController, PSPDFSectionModel;

/// Defines the content for a `UITableViewCell`.
/// Used in `PSPDFStaticTableViewController`.
PSPDF_SDK_CLASS_SWIFT(CellModel)
@interface PSPDFCellModel : NSObject

/// Convenience initializer. Sets `title` during initialization.
+ (instancetype)cellWithTitle:(nullable NSString *)title;

/// Back pointer to the parent section model.
@property (nonatomic, weak) PSPDFSectionModel *section;

/// Container for optional custom data.
@property (nonatomic, copy, nullable) NSDictionary *userInfo;

/// @section Configuration

/// The created cell class for this model. Defaults to `PSPDFTableViewCell`.
@property (nonatomic) Class cellClass;

/// The contents of the `textLabel` or the `titleLabel` if the cell conforms to `PSPDFCustomTitleLabelCell`.
@property (nonatomic, copy, nullable) NSString *title;

/// The contents of the `detailTextLabel`.
@property (nonatomic, copy, nullable) NSString *subtitle;

/// Table cell accessory view.
@property (nonatomic, nullable) UIView *accessoryView;

/// Image used on the leading side of the cell. Sets `imageView` on the cell.
@property (nonatomic, nullable) UIImage *image;

/// Defaults to `UITableViewCellSelectionStyleBlue`.
@property (nonatomic) UITableViewCellSelectionStyle selectionStyle;

/// Defaults to `UITableViewCellAccessoryNone`.
@property (nonatomic) UITableViewCellAccessoryType accessoryType;

/// A cell might be not selectable, in that case the action block does not fire when the user taps on it.
/// Defaults to YES.
@property (nonatomic) BOOL selectable;

/// @section Selection

/// Returns YES if cell is currently checked (checkmark added).
@property (nonatomic, getter=isChecked) BOOL checked;

/// @section Editing

/// Edit cells. If set, a tap will show/hide these additional cells.
///
/// Editing cells will not show a separator when expanded.
@property (nonatomic, copy) NSArray<PSPDFCellModel *> *editingCellModels;

/// Show / hide editing cells.
@property (nonatomic, getter=isEditing) BOOL editing;

/// @section Blocks

/// Called during initialization, updates and before it is displayed.
@property (nonatomic, copy, nullable) void (^updateBlock)(__kindof PSPDFStaticTableViewController *viewController, __kindof UITableViewCell *cell, NSIndexPath *indexPath);

/// Called when the editing state is triggered.
@property (nonatomic, copy, nullable) void (^editingBlock)(__kindof PSPDFStaticTableViewController *viewController, __kindof UITableViewCell *cell, NSIndexPath *indexPath);

/// Called after the cell is first created. Cells will not be reused, so no cleanup is needed.
@property (nonatomic, copy, nullable) void (^createBlock)(__kindof PSPDFStaticTableViewController *viewController, __kindof UITableViewCell *cell);

/// Called when the cell is selected, if selection is enabled.
@property (nonatomic, copy, nullable) void (^actionBlock)(__kindof PSPDFStaticTableViewController *viewController, __kindof UITableViewCell *cell);

/// Called before displaying cell. Can be used to start observing model changes.
@property (nonatomic, copy, nullable) void (^willDisplayBlock)(__kindof PSPDFStaticTableViewController *viewController, __kindof UITableViewCell *cell, NSIndexPath *indexPath);

/// Called after cell has been removed from the table. Can be used to stop observing model changes.
@property (nonatomic, copy, nullable) void (^didEndDisplayBlock)(__kindof PSPDFStaticTableViewController *viewController, __kindof UITableViewCell *cell, NSIndexPath *indexPath);

@end

NS_ASSUME_NONNULL_END
