//
//  PSPDFDatabaseQueue.h
//  PSPDFKit
//
//  This is modified 3rd-party code licensed under MIT.
//
//  Copyright © 2008 Flying Meat Inc.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

@class PSPDFDatabase;
@protocol PSPDFDatabaseEncryptionProvider;

NS_ASSUME_NONNULL_BEGIN

/// Allows coordinated access to the database.
@interface PSPDFDatabaseQueue : NSObject

/// Initializer.
- (instancetype)initWithPath:(NSString *)path encryptionKey:(nullable NSData *)encryptionKey databaseEncryptionProvider:(nullable id<PSPDFDatabaseEncryptionProvider>)databaseEncryptionProvider;

/// Close
- (void)close;

/// The active database path.
@property (atomic, copy) NSString *path;

/// Transaction helper
- (void)inDatabase:(void (^)(PSPDFDatabase *db))block;
- (void)inDatabaseAsync:(void (^)(PSPDFDatabase *db))block;
- (void)inTransaction:(void (^)(PSPDFDatabase *db, BOOL *rollback))block;
- (void)inTransaction:(void (^)(PSPDFDatabase *db, BOOL *rollback))block afterCommit:(void (^)(void))afterCommit;
- (void)inDeferredTransaction:(void (^)(PSPDFDatabase *db, BOOL *rollback))block;
- (void)inDeferredTransactionAsync:(void (^)(PSPDFDatabase *db, BOOL *rollback))block;
- (void)inDeferredTransactionAsync:(void (^)(PSPDFDatabase *db, BOOL *rollback))block afterCommit:(void (^)(void))afterCommit;

/// NOTE: you can not nest these, since calling it will pull another database out of the pool and you'll get a deadlock.
/// If you need to nest, use PSPDFDatabase's `startSavePointWithName:error:` instead.
- (nullable NSError *)inSavePoint:(void (^)(PSPDFDatabase *db, BOOL *rollback))block;

@end

NS_ASSUME_NONNULL_END
