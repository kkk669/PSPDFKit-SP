//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFTableViewCell.h>
#import <PSPDFKitUI/PSPDFCustomTitleCell.h>

NS_ASSUME_NONNULL_BEGIN

/// A cell that sets the `textLabel` color to the `tintColor` or adds a real button when running optimized for Mac. This class should usually be used with `PSPDFButtonCellModel`.
PSPDF_APP_CLASS_SWIFT(ButtonCell)
@interface PSPDFButtonCell : UITableViewCell <PSPDFCustomTitleCell>

/// Whether the cell adds a real button as a subview. If NO, the cell itself is the ‘button’. This is currently only returns YES when optimized for Mac.
@property(class, nonatomic, readonly) BOOL useButtonView;

/// The action block that is triggered whenever the button is tapped
@property (nonatomic, copy, nullable) void (^actionBlock)(PSPDFButtonCell *buttonCell);

@end

NS_ASSUME_NONNULL_END
