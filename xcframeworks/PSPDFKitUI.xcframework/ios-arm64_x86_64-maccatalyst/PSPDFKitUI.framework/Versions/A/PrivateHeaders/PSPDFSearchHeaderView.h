//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSearchViewController.h>
#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_APP_EXPORT @interface PSPDFSearchHeaderView : UITableViewHeaderFooterView <PSPDFSearchScopeViewable>

@property (nonatomic, readonly) UILabel *scopeLabel;
@property (nonatomic, readonly) UILabel *matchLabel;

@property (nonatomic, readonly, nullable) UILabel *textLabel NS_UNAVAILABLE;
@property (nonatomic, readonly, nullable) UILabel *detailTextLabel NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
