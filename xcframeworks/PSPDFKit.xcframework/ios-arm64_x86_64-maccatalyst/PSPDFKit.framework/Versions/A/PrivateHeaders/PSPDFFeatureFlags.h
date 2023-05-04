//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Responsible for handling features flags.
/// This is used to check if certain features are enabled.
/// Mostly used for disabling features that are being developed for an upcoming release,
/// before the feature is ready.

/// States if the Electronic Signatures feature is enabled.
PSPDF_SDK_EXPORT BOOL PSPDFFeatureFlagsIsElectronicSignaturesEnabled(void) NS_SWIFT_NAME(FeatureFlagsIsElectronicSignaturesEnabled());

/// Changes whether the Electronic Signatures feature is enabled. For tests.
PSPDF_SDK_EXPORT void PSPDFFeatureFlagsSetElectronicSignaturesEnabled(BOOL) NS_SWIFT_NAME(FeatureFlagsSetElectronicSignaturesEnabled(_:));

NS_ASSUME_NONNULL_END
