//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Simple rounded label.
PSPDF_CLASS_SWIFT(RoundedLabel)
@interface PSPDFRoundedLabel : UILabel

/// Corner radius. Defaults to 5.
@property (nonatomic) CGFloat cornerRadius UI_APPEARANCE_SELECTOR;

/// Label background. Defaults to `[UIColor colorWithWhite:0. alpha:0.7]`.
@property (nonatomic, nullable) UIColor *rectColor UI_APPEARANCE_SELECTOR;

@end
