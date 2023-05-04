//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Models the different kinds of passwords that can be set on a PDF document.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFPasswordType) {
    /// A user password, also known as open password. Used to prevent opening the document.
    PSPDFPasswordTypeUser,
    /// An owner password, also known as permissions password. Used to set permissions and change passwords.
    PSPDFPasswordTypeOwner,
};

@interface PSPDFDocument (Passwords)

/// Returns if the given password is a valid user or owner password
/// for this document (depending on the `passwordType` parameter).
- (BOOL)checkPassword:(NSString *)password passwordType:(PSPDFPasswordType)passwordType;

/// Returns the user password, if any, of this document, given a valid owner password.
- (nullable NSString *)userPassword:(NSString *)ownerPassword;

@end

NS_ASSUME_NONNULL_END
