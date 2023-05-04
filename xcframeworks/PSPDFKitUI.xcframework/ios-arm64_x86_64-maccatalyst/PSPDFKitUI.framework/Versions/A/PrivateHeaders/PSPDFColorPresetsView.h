//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFColorPreset, PSPDFDualColorButton;

/// Displays a list of `PSPDFColorPreset` as a grid of `PSPDFDualColorButton` views.
@interface PSPDFColorPresetsView : UIView

/// An array of `PSPDFColorPreset` objects.
@property (nonatomic, copy, nullable) NSArray<PSPDFColorPreset *> *presets;

/// Array of generated buttons, one for every preset in the `presets` array.
@property (nonatomic, readonly, nullable) NSMutableArray<PSPDFDualColorButton *> *colorButtons;

/// The currently selected preset. `NSNotFound` if no preset is selected (the default).
@property (nonatomic) NSUInteger selectedPresetIndex;

/// Selects the button corresponding to the preset at `selectedPresetIndex`, optionally animating the change.
/// Set to `NSNotFound` value for no selection. Asserts if the index extends presets.count.
- (void)setSelectedPresetIndex:(NSUInteger)selectedPresetIndex animated:(BOOL)animated;

/// Called whenever a preset gets selected.
/// Not called during programmatic selection.
@property (nonatomic, copy, nullable) void (^presetSelectionBlock)(PSPDFColorPresetsView *presetView, NSUInteger presetIndex);

/// Called whenever a preset might display the edit menu.
@property (nonatomic, copy, nullable) BOOL (^shouldShowEditMenuBlock)(PSPDFColorPresetsView *presetView, NSUInteger presetIndex);

/// Called to get menu items when a preset wants to display the edit menu.
@property (nonatomic, copy, nullable) NSArray<UIMenuElement *> * (^editMenuItemsBlock)(PSPDFColorPresetsView *presetView, NSUInteger presetIndex);

/// If set to `false`, the secondary color won't be drawn. Defaults to YES.
@property (nonatomic) BOOL renderSecondaryColor;

/// If set to `true`, the secondary color will be drawn first. Defaults to NO.
@property (nonatomic) BOOL invertColorOrder;

@end

NS_ASSUME_NONNULL_END
