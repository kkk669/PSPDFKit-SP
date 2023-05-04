//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

#import <PSPDFKit/PSPDFFeatureMask.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_EXPORT void PSPDFInfo(void);

/// Checks if all of the specified features are enabled.
///
/// @param feature A bitmask of features, which may be combined with the bitwise or operator (|).
/// @param warn If YES, log a warning if any of the features are not available. If NO the call is always silent.
/// @return YES if all of the features in the passed in bitmask are enabled. NO if any of the features are not enabled.
PSPDF_TEST_EXPORT BOOL PSPDFIsFeatureEnabled(PSPDFFeatureMask feature, BOOL warn) NS_REFINED_FOR_SWIFT;

/// Checks if any of the specified features are enabled.
///
/// @param features A bitmask of features, which should be combined with the bitwise or operator (|).
/// @param warn If YES, log a warning if the features are not all available. If NO the call is always silent.
/// @return YES if any of the features in the passed in bitmask are enabled. NO if all of the features are not enabled.
PSPDF_TEST_EXPORT BOOL PSPDFIsAnyFeatureEnabled(PSPDFFeatureMask features, BOOL warn) NS_REFINED_FOR_SWIFT;

typedef NS_CLOSED_ENUM(NSInteger, PSPDFSignatureFeatureAvailability) {
    /// The newer ElectronicSignatures component is unlocked, which allows signing by drawing, typing, or choose an image. There is an explicit license feature for this case.
    PSPDFSignatureFeatureAvailabilityElectronicSignatures,
    /// The older signing functionality as part of AnnotationEditing is unlocked. This is the case if a customer bought AnnotationEditing before we added the ElectronicSignatures component. Customers who first purchased after we added ElectronicSignatures will never have this legacy functionality.
    PSPDFSignatureFeatureAvailabilityLegacySignatures,
    /// Neither of the above two are unlocked. This is the case if neither of the conditions for the other options are satisfied. Note that Digital Signatures might still be unlocked.
    PSPDFSignatureFeatureAvailabilityNone,
} PSPDF_ENUM_SWIFT(SignatureFeatureAvailability);

/// What type of signature features are available. This is unrelated to Digital Signatures.
///
/// @param warn If true then log a warning if no signature features are available.
PSPDF_TEST_EXPORT PSPDFSignatureFeatureAvailability PSPDFGetSignatureFeatureAvailability(BOOL warn) NS_REFINED_FOR_SWIFT;

/// Creates an error if any of the specified features are disabled. An additional
/// optional error message will be combined with the default `Your license does not
/// include...` message.
///
/// @param feature A bitmask of features, which may be combined with the bitwise or operator (|).
/// @param errorMessage The error message format, followed by arguments.
/// @return An error if any of the features are not enabled. `nil` if all specified features are enabled.
PSPDF_EXPORT NSError * _Nullable PSPDFCreateErrorIfFeatureIsNotEnabled(PSPDFFeatureMask feature, NSString * _Nullable errorMessage, ...) NS_FORMAT_FUNCTION(2, 3);

/// String representation for `PSPDFFeatureMaskInteger`.
PSPDF_EXPORT NSString *PSPDFFeatureMaskToString(PSPDFFeatureMask features) NS_REFINED_FOR_SWIFT;

/// Returns the original purchase date (`op`) from the license JSON or returns nil if that property is not set.
PSPDF_EXPORT NSDate *_Nullable PSPDFGetLicenseOriginalPurchaseDate(void) NS_REFINED_FOR_SWIFT;

/// Is in demo mode.
PSPDF_TEST_EXPORT BOOL PSPDFIsDemo(void) NS_REFINED_FOR_SWIFT;

/// Shows an alert from the model layer. Use sparingly!
PSPDF_EXTERN void PSPDFPresentAlert(NSString *_Nullable title, NSString *_Nullable message, BOOL dismissible);

/// C method to set the license key.
PSPDF_EXTERN PSPDFFeatureMask _PSPDFSetLicenseKey(const char *licenseKey, NSDictionary<NSString *, id> *_Nullable options);

/// Sets the features (`f`) and original purchase date (`op`) of the active license while preserving other
/// properties of the license. This has the power to add capabilities, so it is not for public release!
/// This will clear the render cache after setting the license since license features affect rendering.
PSPDF_EXPORT void PSPDFSetLicenseOverride(PSPDFFeatureMask features, NSDate *_Nullable originalPurchaseDate);

NS_ASSUME_NONNULL_END
