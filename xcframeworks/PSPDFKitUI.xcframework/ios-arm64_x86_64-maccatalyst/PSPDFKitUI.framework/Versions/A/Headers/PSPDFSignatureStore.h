//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFSignatureContainer.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that stores signature annotations.
///
/// You can implement this protocol and set the object as the `PDFConfiguration`’s `signatureStore` to use your own backend for saving and loading the user’s signatures.
/// Read more: https://pspdfkit.com/guides/ios/signatures/signature-storage/
///
/// The store must support `NSSecureCoding` because the store is part of the `PDFConfiguration` object. If your store requires any identifiers such as a store name or a username, ensure these are serialized and deserialized.
///
/// If you want a simple on-device store, PSPDFKit provides `KeychainSignatureStore`, which implements this protocol.
PSPDF_PROTOCOL_SWIFT(SignatureStore)
@protocol PSPDFSignatureStore<NSObject, NSSecureCoding>

/// Add a signature to the store.
///
/// The new signature should be included in any future calls to `signatures` but your implementation is free be insert the new signature in any position, such as at the start or end.
- (void)addSignature:(PSPDFSignatureContainer *)signature;

/// Remove a signature from the store.
///
/// The signature should not be included in any future calls to `signatures`.
- (BOOL)removeSignature:(PSPDFSignatureContainer *)signature;

/// Access the saved signatures (`SignatureContainer` objects).
///
/// This property may be set when the user reorders the signature list.
/// Reading this property must preserve the order that was set.
@property (nonatomic, copy, null_resettable) NSArray<PSPDFSignatureContainer *> *signatures;

@end

/// The default store name PSPDFKit uses for the `KeychainSignatureStore` when using the initializer with no parameters.
PSPDF_EXPORT NSString *PSPDFKeychainSignatureStoreDefaultStoreName NS_SWIFT_NAME(KeychainSignatureStore.DefaultStoreName);

/// A signature store implementation that securely loads from, and saves to, the system keychain.
PSPDF_CLASS_SWIFT(KeychainSignatureStore)
@interface PSPDFKeychainSignatureStore : NSObject<PSPDFSignatureStore>

/// Creates a `KeychainSignatureStore`.
///
/// @param storeName The keychain service name, which can be used to differentiate between different stores. Omit this parameter to use `DefaultStoreName`.
- (instancetype)initWithStoreName:(nullable NSString *)storeName NS_DESIGNATED_INITIALIZER;

/// The keychain service name, which can be used to differentiate between different stores.
///
/// This returns the `storeName` passed to the initializer, which may be `DefaultStoreName` if the object was initialzed with no parameters.
@property (nonatomic, copy, readonly) NSString *storeName;

@end

NS_ASSUME_NONNULL_END
