//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that can be used to build comparison processor configuration
/// objects.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ComparisonConfiguration.Builder)
@interface PSPDFComparisonConfigurationBuilder: PSPDFBaseConfigurationBuilder

/// @see PSPDFComparisonConfiguration.oldDocumentStrokeColor
@property (nonatomic, nullable) UIColor *oldDocumentStrokeColor;

/// @see PSPDFComparisonConfiguration.newDocumentStrokeColor
@property (nonatomic, nullable) UIColor *newDocumentStrokeColor;

/// @see PSPDFComparisonConfiguration.blendMode
@property (nonatomic) CGBlendMode blendMode;

/// @see PSPDFComparisonConfiguration.workingDirectory
@property (nonatomic, nullable) NSURL *workingDirectory;

@end

// MARK: -

/// An object that encapsulates the configuration of the comparison processor.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ComparisonConfiguration)
@interface PSPDFComparisonConfiguration : PSPDFBaseConfiguration<PSPDFComparisonConfigurationBuilder *>

/// The color that will be used to replace all strokes in the old version of a
/// document. If `nil`, the stroke color won't be replaced.
///
/// Default: `.red`.
@property (nonatomic, readonly, nullable) UIColor *oldDocumentStrokeColor;

/// The color that will be used to replace all strokes in the new version of a
/// document. If `nil`, the stroke color won't be replaced.
///
/// Default: `.green`.
@property (nonatomic, readonly, nullable) UIColor *newDocumentStrokeColor;

/// The blend mode that will be used when overlaying the new version of a
/// document onto the old version.
///
/// Default: `.darken`.
@property (nonatomic, readonly) CGBlendMode blendMode;

/// The URL of a directory that will be used to write temporary files when
/// generating the comparison document. If `nil`, processing will be done in
/// memory, which might be inefficient with larger documents.
///
/// Default: `NSTemporaryDirectory()`.
@property (nonatomic, readonly, nullable) NSURL *workingDirectory;

@end

NS_ASSUME_NONNULL_END
