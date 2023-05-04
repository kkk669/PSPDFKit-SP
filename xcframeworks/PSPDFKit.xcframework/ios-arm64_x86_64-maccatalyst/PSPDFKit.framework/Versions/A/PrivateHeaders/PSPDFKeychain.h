//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif
#import <Security/Security.h>

NS_ASSUME_NONNULL_BEGIN

/// Very simple, internal wrapper for the keychain.
PSPDF_SDK_CLASS_SWIFT(Keychain)
@interface PSPDFKeychain : NSObject

/// Return all accounts for `serviceName`. If `serviceName` is nil, all accounts are returned.
+ (nullable NSArray<NSDictionary *> *)accountsForService:(NSString *)serviceName error:(NSError **)error;

/// Get the password data for `serviceName`.
+ (nullable NSData *)passwordDataForService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;

/// Store password data.
/// Use `[password dataUsingEncoding:NSUTF8StringEncoding]` to store a string.
+ (BOOL)setPasswordData:(NSData *)password forService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;

/// Deletes a password entry.
+ (BOOL)deletePasswordForService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
