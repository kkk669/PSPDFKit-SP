//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif
// Swift can't deal with an import of sqlite3 in framework headers, so we use void * to mask the sqlite struct.

NS_ASSUME_NONNULL_BEGIN

/**
 Support for database encryption. If you intend to use database encryption features, you must provide
 an implementation of `PSPDFDatabaseEncryptionProvider` by setting `-[PSPDFKitGlobal setDatabaseEncryptionProvider:]`.
 */
PSPDF_PROTOCOL_SWIFT(DatabaseEncryptionProvider)
@protocol PSPDFDatabaseEncryptionProvider <NSObject>

/**
 The encryption provider must perform the necessary steps to encrypt the given `db` with the given
 `keyData`. Most implementations will call `sqlite3_key(db, keyData.bytes, keyData.length)`.
 Return `true` if no errors occurred, and `false` otherwise.
 */
- (BOOL)encryptDatabase:(void *)db withKey:(NSData *)keyData; // db is of type sqlite3

/**
 The encryption provider must perform the necessary steps to re-encrypt the given `db` with the
 given `keyData`. Most implementations will call `sqlite3_rekey(db, keyData.bytes, keyData.length)`.
 Return `true` if no errors occurred, and `false` otherwise.
 */
- (BOOL)reEncryptDatabase:(void *)db withKey:(NSData *)keyData; // db is of type sqlite3

@end

NS_ASSUME_NONNULL_END
