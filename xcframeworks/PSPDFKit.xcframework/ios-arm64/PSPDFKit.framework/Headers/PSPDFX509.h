//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFRSAKey.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// This class represents a X.509 certificate.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(X509)
@interface PSPDFX509 : NSObject

/// Returns a `PSPDFX509` instance of the Adobe certification authority.
+ (instancetype)adobeCA;

/*
   Initializes the certificate from certificate data. If the input format is not supported, returns `nil` and
   the `error` argument will have detailed information about the problem.

   The certificate data must be in one of the following formats:
     - DER or PEM-encoded PKCS#7.
     - DER or PEM-encoded X509.

   The most reliable way to check the format is by using OpenSSL to show information about the certificate.

   For PEM-encoded certificates execute the following command in your shell:

     openssl pkcs7 -noout -text -print_certs -in example.p7b

   For DER-encoded certificates execute the following command in your shell:

     openssl pkcs7 -inform der -noout -text -print_certs -in example.p7b
*/
+ (nullable NSArray<PSPDFX509 *> *)certificatesFromPKCS7Data:(NSData *)data error:(NSError **)error;

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The public key.
@property (nonatomic, readonly) PSPDFRSAKey *publicKey;

/// The CN entry of this certificate.
@property (nonatomic, copy, readonly, nullable) NSString *commonName;

@end

NS_ASSUME_NONNULL_END
