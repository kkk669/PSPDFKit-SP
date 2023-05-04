//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFormOption.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFBaseTableViewController.h>
#import <PSPDFKitUI/PSPDFChoiceFormElementView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFChoiceFormEditorViewController;

/// Data source for `PSPDFChoiceFormEditorViewController`.
NS_SWIFT_NAME(ChoiceFormEditorViewControllerDataSource)
@protocol PSPDFChoiceFormEditorViewControllerDataSource <NSObject>

/// Number of predefined choices excluding editable choice.
@property (nonatomic, readonly) NSUInteger numberOfOptions;

/// Number of selected choices.
@property (nonatomic, readonly) NSUInteger numberOfOptionsSelected;

/// Defines if multiple options can be selected.
@property (nonatomic, getter=isMultiSelect, readonly) BOOL multiSelect;

/// Returns the user-facing text of a single choice form option.
///
/// @param index Index of the choice form option.
/// @return The user-facing string.
- (nullable NSString *)optionTextAtIndex:(NSUInteger)index;

/// Returns if a single choice form option is selection.
///
/// @param index Index of the choice form option.
/// @return Returns the selected state of an option.
- (BOOL)isSelectedAtIndex:(NSUInteger)index;

/// All the selected indices of the choice form element.
@property (nonatomic, readonly, nullable) NSIndexSet *selectedIndices;

/// Defines if the user can enter his own choice.
@property (nonatomic, getter=isEdit, readonly) BOOL edit;

/// The user-generated custom choice form option value.
@property (nonatomic, readonly, nullable) NSString *customText;

/// All available options of the choice form element.
@property (nonatomic, readonly, nullable) NSArray<PSPDFFormOption *> *allOptions;

@end

/// Delegate notifying about changes in the choice form list.
NS_SWIFT_NAME(ChoiceFormEditorViewControllerDelegate)
@protocol PSPDFChoiceFormEditorViewControllerDelegate <NSObject>

/// Called when an option has been selected at the given index.
///
/// @param choiceEditorController Corresponding `PSPDFChoiceFormEditorViewController` object.
/// @param index Option at this index has been selected.
/// @param shouldDismissController Defines if the presented `PSPDFChoiceFormEditorViewController` should be dismissed.
- (void)choiceEditorController:(PSPDFChoiceFormEditorViewController *)choiceEditorController didSelectIndex:(NSUInteger)index shouldDismissController:(BOOL)shouldDismissController;

/// Called when the user changed the text in the custom editable text option.
///
/// @param choiceEditorController Corresponding `PSPDFChoiceFormEditorViewController` object.
/// @param text Changed text value.
- (void)choiceEditorController:(PSPDFChoiceFormEditorViewController *)choiceEditorController didUpdateCustomText:(NSString *)text;

/// Called when the user selected the custom text option.
///
/// @param choiceEditorController Corresponding `PSPDFChoiceFormEditorViewController` object.
- (void)choiceEditorControllerDidSelectCustomText:(PSPDFChoiceFormEditorViewController *)choiceEditorController;

/// Called when the user starts entering text in the custom text option.
///
/// @param choiceEditorController Corresponding `PSPDFChoiceFormEditorViewController` object.
- (void)choiceEditorControllerDidBeginEditingCustomText:(PSPDFChoiceFormEditorViewController *)choiceEditorController;

/// Called when the user finished entering text in the custom text option.
///
/// @param choiceEditorController Corresponding `PSPDFChoiceFormEditorViewController` object.
- (void)choiceEditorControllerDidEndEditingCustomText:(PSPDFChoiceFormEditorViewController *)choiceEditorController;

@end

/// Shows a list of choice form options for a choice form element.
PSPDF_APP_CLASS_SWIFT(ChoiceFormEditorViewController)
@interface PSPDFChoiceFormEditorViewController : PSPDFBaseTableViewController<PSPDFOverridable>

/// Initialize with a data source and a delegate.
- (instancetype)initWithDataSource:(id<PSPDFChoiceFormEditorViewControllerDataSource>)datasource delegate:(id<PSPDFChoiceFormEditorViewControllerDelegate>)delegate;

/// The choice editor data source.
@property (nonatomic, weak) IBOutlet id<PSPDFChoiceFormEditorViewControllerDataSource> dataSource;

/// The choice editor delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFChoiceFormEditorViewControllerDelegate> delegate;

/// The view where the form is currently rendered into.
@property (nonatomic, weak) PSPDFChoiceFormElementView *formElementView;

/// Search controller used for searching.
@property (nonatomic, nullable) UISearchController *searchController;

/// Defines if searching the options should be enabled.
/// Shows a search bar on top of the list if this is enabled.
@property (nonatomic) BOOL searchEnabled;

/// Reload the table.
- (void)reloadData;

/// Select the next visible cell.
/// Doesn't do anything when `multiSelect` is enabled in the data source or while searching.
- (void)selectNextValueAnimated:(BOOL)animated;

/// Select the previous visible cell.
/// Doesn't do anything when `multiSelect` is enabled in the data source or while searching.
- (void)selectPreviousValueAnimated:(BOOL)animated;

/// If the choice controller allows custom editing, make the edit cell active and scroll to it.
- (BOOL)enableEditModeAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
