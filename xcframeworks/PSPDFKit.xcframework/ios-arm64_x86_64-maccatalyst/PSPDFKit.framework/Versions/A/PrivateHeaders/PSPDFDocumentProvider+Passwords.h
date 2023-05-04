//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentProvider.h>
#import <PSPDFKit/PSPDFDocument+Passwords.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDocumentProvider (Passwords)

/// Returns if the given password is a valid user or owner password
/// for this document provider (depending on the `passwordType` parameter).
- (BOOL)checkPassword:(NSString *)password passwordType:(PSPDFPasswordType)passwordType;

/// Returns the user password, if any, of this document provider, given a valid owner password.
- (nullable NSString *)userPassword:(NSString *)ownerPassword;

@end

NS_ASSUME_NONNULL_END
