//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(RSAKey)
@interface PSPDFRSAKey : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The underlying public key scheme.
@property (nonatomic, readonly) NSString *publicKeyScheme;

/// Returns the approximate length of the security parameter. For example, for RSA this is the size of the modulus.
@property (nonatomic, readonly) NSInteger keyLength;

@end

NS_ASSUME_NONNULL_END
