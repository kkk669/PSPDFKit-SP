//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

@class PSPDFAppearanceModeManager, PSPDFConfigurationBuilder, PSPDFRenderOptions;

typedef NS_OPTIONS(NSUInteger, PSPDFAppearanceMode) {
    /// Normal application appearance and page rendering, as configured by the host app.
    PSPDFAppearanceModeDefault = 0,
    /// Renders the PDF content with a sepia tone.
    PSPDFAppearanceModeSepia = 1 << 0,
    /// Inverts the PDF page content and applies color correction.
    PSPDFAppearanceModeNight = 1 << 1,
    /// All options.
    PSPDFAppearanceModeAll = PSPDFAppearanceModeDefault | PSPDFAppearanceModeSepia | PSPDFAppearanceModeNight
} NS_SWIFT_NAME(PDFAppearanceMode);

NS_ASSUME_NONNULL_BEGIN

/// Notification sent out after `appearanceMode` is changed.
PSPDF_EXPORT NSNotificationName const PSPDFAppearanceModeChangedNotification;

PSPDF_PROTOCOL_SWIFT(AppearanceModeManagerDelegate)
@protocol PSPDFAppearanceModeManagerDelegate<NSObject>

@optional

/// Provides the document render options for the specified mode.
///
/// @param manager A reference to the invoking appearance mode manager.
/// @param mode The mode that is about to be applied.
///
/// @note Overrides the default behavior, if implemented.
- (PSPDFRenderOptions *)appearanceManager:(PSPDFAppearanceModeManager *)manager renderOptionsForMode:(PSPDFAppearanceMode)mode;

@end

/// Coordinates appearance mode changes.
///
/// This class will only update the PDF page rendering style.
PSPDF_CLASS_SWIFT(PDFAppearanceModeManager)
@interface PSPDFAppearanceModeManager : NSObject<PSPDFOverridable>

/// The currently selected appearance mode. Defaults to `PSPDFAppearanceModeDefault`.
@property (nonatomic) PSPDFAppearanceMode appearanceMode;

/// The appearance delegate. Can be used to customize the default behaviors for each mode.
@property (nonatomic, weak) id<PSPDFAppearanceModeManagerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
