//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// Draws a checkmark selection indicator with two states.
PSPDF_APP_EXPORT @interface PSPDFCellSelectionView : UIView

// MARK: Selection

/// The current appearance.
@property (nonatomic, getter=isSelected) BOOL selected;

/// Switch between the selected and deselected appearance.
/// Optionally animating the change.
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

// MARK: Appearance

/// Background color for the circular background.
@property (nonatomic) UIColor *fillColor UI_APPEARANCE_SELECTOR;

/// Background color for the circular background during selection.
/// Uses the `tintColor` if `nil` (the default).
@property (nonatomic, nullable) UIColor *selectedFillColor UI_APPEARANCE_SELECTOR;

/// Stroke color for the border.
@property (nonatomic) UIColor *strokeColor UI_APPEARANCE_SELECTOR;

/// Stroke color for the border and checkmark during selection.
@property (nonatomic) UIColor *selectedStrokeColor UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END
