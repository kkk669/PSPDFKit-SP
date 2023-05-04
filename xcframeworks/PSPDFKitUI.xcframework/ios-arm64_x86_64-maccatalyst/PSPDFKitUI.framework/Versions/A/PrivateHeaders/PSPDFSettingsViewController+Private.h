//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSettingsViewController.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSectionModel, PSPDFCellModel, PSPDFViewController;

/// Private subclassing hooks for PDF Viewer.
@interface PSPDFSettingsViewController ()

/// Creates cell models for setting actions.
- (NSArray<PSPDFSectionModel *> *)sectionsForPDFViewController:(PSPDFViewController *)pdfViewController;

/// Returns the available setting options for the PDFViewController.
- (PSPDFSettingsOptions)settingsOptionsForPDFViewController:(PSPDFViewController *)pdfViewController;

@end

PSPDF_APP_CLASS_SWIFT(SettingsSeparatorView)
@interface PSPDFSettingsSeparatorView: UIView @end

NS_ASSUME_NONNULL_END

