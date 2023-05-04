//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// A cell that displays PSPDFToolbar as the accessory view.
///
/// Can use the textLabel and detailText label too.
///
/// An implementation detail is that the toolbar size needs updating after
/// changing the buttons, so the toolbar is private so we don’t forget to do this.
PSPDF_APP_CLASS_SWIFT(ToolbarCell)
@interface PSPDFToolbarCell : PSPDFTableViewCell

@property (nonatomic, copy) NSArray<UIButton *> *buttons;

@property (nonatomic, getter=isToolbarUserInteractionEnabled) BOOL toolbarUserInteractionEnabled;

@end

NS_ASSUME_NONNULL_END
