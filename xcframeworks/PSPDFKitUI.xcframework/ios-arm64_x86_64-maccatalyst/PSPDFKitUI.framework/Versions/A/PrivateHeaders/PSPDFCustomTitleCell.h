//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// When a `UITableViewCell` conforms to this protocol and is used with
/// `PSPDFStaticTableViewController`, the cell model’s title will be applied via the titleText accessor.
///
/// @note This is helpful for custom cell layouts.
PSPDF_PROTOCOL_SWIFT(CustomTitleCell)
@protocol PSPDFCustomTitleCell <NSObject>

/// Custom accessor for the title.
@property (nonatomic, copy) NSString *titleText;

@end

NS_ASSUME_NONNULL_END
