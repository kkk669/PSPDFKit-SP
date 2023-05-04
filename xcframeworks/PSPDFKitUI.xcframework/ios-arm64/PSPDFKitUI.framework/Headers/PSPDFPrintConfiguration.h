//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFPrintMode) {
    /// The interactive mode presents the `UIPrintInteractionController`.
    PSPDFPrintModeInteractive,

    /// This mode will not show a document preview or any other options (such as print count).
    PSPDFPrintModeChoosePrinterOnly,

    /// This mode will use the set `UIPrinter` object on `defaultPrinter` to invoke printing without further UI.
    PSPDFPrintModePrintDirect
} PSPDF_ENUM_SWIFT(PrintConfiguration.Mode);

PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PrintConfigurationBuilder)
@interface PSPDFPrintConfigurationBuilder : PSPDFBaseConfigurationBuilder
@end

/// Common settings that define how printing should be handled.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PrintConfiguration)
@interface PSPDFPrintConfiguration : PSPDFBaseConfiguration<PSPDFPrintConfigurationBuilder *>

/// Defines the printer mode. See `PSPDFPrintMode` for available options.
/// Defaults to `PSPDFPrintModeInteractive`.
@property (nonatomic, readonly) PSPDFPrintMode printMode;

/// Defines the default printer that should be pre-selected.
/// Ignored when printMode is set to `PSPDFPrintModeInteractive`.
@property (nonatomic, nullable, readonly) UIPrinter *defaultPrinter;

@end

@interface PSPDFPrintConfigurationBuilder ()

/// @see PSPDFPrintConfiguration.printMode.
@property (nonatomic) PSPDFPrintMode printMode;
/// @see PSPDFPrintConfiguration.defaultPrinter.
@property (nonatomic, nullable) UIPrinter *defaultPrinter;

@end

NS_ASSUME_NONNULL_END
