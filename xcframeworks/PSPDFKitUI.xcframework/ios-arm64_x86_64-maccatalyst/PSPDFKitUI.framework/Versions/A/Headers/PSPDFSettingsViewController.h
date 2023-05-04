//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFStaticTableViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// The possible UX settings that can be set by a `PDFSettingsViewController`.
typedef NS_OPTIONS(NSUInteger, PSPDFSettingsOptions) {
    /// Shows UI to change `ScrollDirection`.
    PSPDFSettingsOptionScrollDirection = 1 << 0,
    /// Shows UI to change `PageTransition` (continuous or per-spread scrolling).
    PSPDFSettingsOptionPageTransition = 1 << 1,
    /// Shows UI to change `AppearanceMode` (sepia and dark rendering).
    PSPDFSettingsOptionAppearance = 1 << 2,
    /// Shows UI to adjust screen brightness.
    PSPDFSettingsOptionBrightness = 1 << 3,
    /// Shows UI to change `PageMode` (single or double page mode).
    PSPDFSettingsOptionPageMode = 1 << 4,
    /// Shows UI to change `ConfigurationSpreadFitting`.
    PSPDFSettingsOptionSpreadFitting = 1 << 5,
    /// The default set of settings the user can adjust with `PDFSettingsViewController`.
    PSPDFSettingsOptionDefault = PSPDFSettingsOptionScrollDirection | PSPDFSettingsOptionPageTransition | PSPDFSettingsOptionSpreadFitting | PSPDFSettingsOptionAppearance | PSPDFSettingsOptionBrightness,
    /// All the settings that can be set by a `PDFSettingsViewController`.
    PSPDFSettingsOptionAll = NSUIntegerMax,
} PSPDF_ENUM_SWIFT(PDFSettingsViewController.Options);

@class PSPDFViewController;

/// Controller to change some key UX settings.
///
/// Configurable via `PDFConfiguration.settingsOptions` property. Use `PDFViewController.settingsButtonItem` to add it to controller's navigation item.
///
/// To be notified about configuration changes, use KVO on the `configuration` property of the `PDFViewController`.
PSPDF_CLASS_SWIFT(PDFSettingsViewController)
@interface PSPDFSettingsViewController : PSPDFStaticTableViewController<PSPDFOverridable>

/// Reference to the controller which will be configured with `PDFSettingsViewController`.
@property (nonatomic, weak) PSPDFViewController *pdfViewController;

@end

NS_ASSUME_NONNULL_END
