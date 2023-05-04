//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// The different kinds of input methods we support for creating a handwritten signature.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFDrawInputMethod) {
    /// The signature input mode is not stored.
    PSPDFDrawInputMethodNone,
    /// The signature was created using the finger.
    PSPDFDrawInputMethodFinger,
    /// The signature was created using an Apple Pencil.
    PSPDFDrawInputMethodApplePencil,
    /// The signature was created using a third-party stylus.
    PSPDFDrawInputMethodThirdPartyStylus,
    /// The signature was created using a mouse. Although not used by PSPDFKit for now, other platforms might create biometric data with this input method.
    PSPDFDrawInputMethodMouse
} PSPDF_ENUM_SWIFT(DrawInputMethod);

// Deprecated Backwards Compatibility
#define PSPDFSignatureInputMethod PSPDFDrawInputMethod

/// Defines the possible biometric properties to store in a digital signature.
typedef NS_OPTIONS(NSUInteger, PSPDFSignatureBiometricPropertiesOption) {
    /// Don't store any biometric properties.
    PSPDFSignatureBiometricPropertiesOptionNone = 0,
    /// Store the pressure of the created ink signature.
    PSPDFSignatureBiometricPropertiesOptionPressure = 1 << 0,
    /// Store the time points of the created ink signature.
    PSPDFSignatureBiometricPropertiesOptionTimePoints = 1 << 1,
    /// Store the average touch radius of the created ink signature.
    PSPDFSignatureBiometricPropertiesOptionTouchRadius = 1 << 2,
    /// Store the input method of the created ink signature.
    PSPDFSignatureBiometricPropertiesOptionInputMethod = 1 << 3,
    /// Store all biometric properties.
    PSPDFSignatureBiometricPropertiesOptionAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(PDFSignatureBiometricProperties.Option);

/// An instance of `PSPDFSignatureBiometricProperties` represents properties which add biometric
/// information to a digital signature, for enhanced security. Biometric information includes the
/// input method pressure values, time intervals when the signature was being created, or average touch radius.
///
/// This information is encrypted and stored inside the PDF document using the signer's
/// public key, and can be decrypted with the appropriate private key.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFSignatureBiometricProperties)
@interface PSPDFSignatureBiometricProperties : NSObject<NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new `PSPDFSignatureBiometricProperties`.
///
/// @param pressureList      A list of physical pressures obtained when the user signed the document.
/// @param timePointsList    A list of time intervals obtained from specific points in a handwritten signature.
/// @param touchRadius       The average touch radius used to create this signature.
/// @param inputMethod       The input method used to create the signature (ie. finger, Apple Pencil, etc.)
///
/// @note There can only be a maximum of 6 values in the `pressureList` and `timePointsList` arrays combined.
- (nullable instancetype)initWithPressureList:(nullable NSArray<NSNumber *> *)pressureList
                      timePointsList:(nullable NSArray<NSNumber *> *)timePointsList
                         touchRadius:(nullable NSNumber *)touchRadius
                         inputMethod:(PSPDFDrawInputMethod)inputMethod;

/// The list of pressure values that were recorded when the signature was created.
///
/// When signing a document with the default UI, this is set to the first, the middle and the last floating point intensity values of the created ink signature.
/// If `inputMethod` is set to `PSPDFDrawInputMethodFinger`, this is calculated based on the velocity of the drawing.
/// If `inputMethod` is set to `PSPDFDrawInputMethodApplePencil`, this is calculated based on the Apple Pencil's azimuth and altitude towards the display.
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *pressureList;

/// The list of time point values that were recorded when the signature was created.
///
/// When signing a document with the default UI, this is set to an array of the first, the middle and the last time stamps during the creation of the ink signature.
/// The time stamps are corresponding to the values in `pressureList` and have been taken at the same point in time.
///
/// @note Includes boxed `NSTimeInterval` values, set to `-[NSDate timeIntervalSince1970]` at the time of the drawing.
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *timePointsList;

/// The average touch radius that was recorded when the signature was created.
///
/// When signing a document with the default UI, and `inputMethod` is set to `PSPDFDrawInputMethodFinger` this is set to the average radius of all touches of the created ink annotation.
/// If `inputMethod` is set to `PSPDFDrawInputMethodApplePencil`, the altitude angle of the Apple Pencil is used instead.
@property (nonatomic, readonly, nullable) NSNumber *touchRadius;

/// The device that was used to create the signature.
///
/// When signing a document with the default UI, this is set to the last used input method of the created ink signature.
@property (nonatomic, readonly) PSPDFDrawInputMethod inputMethod;

@end

NS_ASSUME_NONNULL_END
