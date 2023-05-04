//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFPrivateKey.h>
#import <PSPDFKit/PSPDFX509.h>

NS_ASSUME_NONNULL_BEGIN

/// A PKCS12 container holding a private key and certificate.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PKCS12)
@interface PSPDFPKCS12 : NSObject<NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a container with data from a PKCS12 blob.
- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

/// The data this container was initialized with.
@property (nonatomic, readonly) NSData *data;

/// Unlocks the PKCS12 archive and retrieves the certificate and public key.
- (void)unlockWithPassword:(NSString *)password done:(nullable void (^)(PSPDFX509 *_Nullable x509, PSPDFPrivateKey *_Nullable pk, NSError *_Nullable error))done;

@end

NS_ASSUME_NONNULL_END
