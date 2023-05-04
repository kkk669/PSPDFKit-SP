//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/// Mutable builder for configuration options for `PSPDFSignatureCreationViewController`.
PSPDF_CLASS_AVAILABLE PSPDF_SUBCLASSING_RESTRICTED NS_REFINED_FOR_SWIFT
@interface PSPDFSignatureCreationConfigurationBuilder : PSPDFBaseConfigurationBuilder

/// The ways in which the user can choose to add their signature.
///
/// This array should contain `PSPDFSignatureCreationMode` values boxed in `NSNumber` objects.
///
/// These are shown in the order specified as tabs across the top of the signatures UI. The first entry will be selected initially.
/// If this array contains a single entry then the tabs will be hidden. This array must not be empty and must not contain duplicates.
///
/// Defaults to `@[@(PSPDFSignatureCreationModeDraw), @(PSPDFSignatureCreationModeImage), @(PSPDFSignatureCreationModeType)]`.
@property (nonatomic, copy) NSArray<NSNumber /* PSPDFSignatureCreationMode */ *> *availableModes;

/// The available colors that the user can pick for their signature when drawing or typing.
///
/// The first entry will be selected initially. If this array contains a single entry then the
/// color options will be hidden. This array must not be empty and must not contain duplicates.
///
/// Limiting this to no more than around three colors is recommended.
///
/// Defaults to black, purple, and blue.
@property (nonatomic, copy) NSArray<UIColor *> *colors;

/// Whether natural drawing is enabled, which applies thickness adjustments based on the speed of strokes.
/// Only relevant with the Draw mode.
/// Defaults to true.
@property (nonatomic) BOOL isNaturalDrawingEnabled;

/// Font options presented to the user for the Type mode to set their signature style.
/// Defaults to 4 custom fonts that are bundled by PSPDFKit.
/// The size of the provided `UIFont` instances is ignored.
/// This array must not be empty.
@property (nonatomic, copy) NSArray<UIFont *> *fonts;

@end

/// Configuration options for `PSPDFSignatureCreationViewController`.
///
/// See example usage at https://pspdfkit.com/guides/ios/signatures/customizing-the-signature-user-interface/
PSPDF_CLASS_AVAILABLE PSPDF_SUBCLASSING_RESTRICTED NS_REFINED_FOR_SWIFT
@interface PSPDFSignatureCreationConfiguration : PSPDFBaseConfiguration<PSPDFSignatureCreationConfigurationBuilder *>

/// The ways in which the user can choose to add their signature.
///
/// This array should contain `PSPDFSignatureCreationMode` values boxed in `NSNumber` objects.
///
/// These are shown in the order specified as tabs across the top of the signatures UI. The first entry will be selected initially.
/// If this array contains a single entry then the tabs will be hidden. This array must not be empty and must not contain duplicates.
///
/// Defaults to `@[@(PSPDFSignatureCreationModeDraw), @(PSPDFSignatureCreationModeImage), @(PSPDFSignatureCreationModeType)]`.
@property (nonatomic, copy, readonly) NSArray<NSNumber /* PSPDFSignatureCreationMode */ *> *availableModes;

/// The available colors that the user can pick for their signature when drawing or typing.
///
/// The first entry will be selected initially. If this array contains a single entry then the
/// color options will be hidden. This array must not be empty and must not contain duplicates.
///
/// Limiting this to no more than around three colors is recommended.
///
/// Defaults to black, purple, and blue.
@property (nonatomic, copy, readonly) NSArray<UIColor *> *colors;

/// Whether natural drawing is enabled, which applies thickness adjustments based on the speed of strokes.
/// Only relevant with the Draw mode.
/// Defaults to true.
@property (nonatomic, readonly) BOOL isNaturalDrawingEnabled;

/// Font options presented to the user for the Type mode to set their signature style.
/// Defaults to 4 custom fonts that are bundled by PSPDFKit.
/// The size of the provided `UIFont` instances is ignored.
/// This array must not be empty.
@property (nonatomic, copy, readonly) NSArray<UIFont *> *fonts;

@end

NS_ASSUME_NONNULL_END
