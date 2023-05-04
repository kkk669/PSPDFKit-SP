//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFFlexibleToolbarController.h>
#import <PSPDFKitUI/PSPDFConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFFlexibleToolbarController ()

/// Writeable version (can be used to override the setter).
@property (nonatomic, readwrite, nullable) PSPDFFlexibleToolbarContainer *flexibleToolbarContainer;

/// Allows modification of the `toolbarVisible` property.
///
/// @param animated Can be passed into resulting notifications.
- (void)setIsToolbarVisible:(BOOL)visible willChangeWithAnimation:(BOOL)animated;

/// Defines edge screen deferring gesture rules for viewController.
- (UIRectEdge)preferredScreenEdgesDeferringSystemGesturesForViewController:(UIViewController *)viewController;

/// Validate that the supported toolbar positions do not conflict with passed configuration.
///
/// @note When `PSPDFFlexibleToolbarPositionTop` is used `documentLabelEnabled` must be `PSPDFAdaptiveConditionalNO`.
/// @param configuration The configuration to validate.
- (BOOL)validateSupportedToolbarPositionsWithConfiguration:(PSPDFConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
