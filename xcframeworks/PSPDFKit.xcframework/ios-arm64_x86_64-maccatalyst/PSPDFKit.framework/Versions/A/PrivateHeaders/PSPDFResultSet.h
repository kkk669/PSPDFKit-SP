//
//  PSPDFResultSet.h
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
@class PSPDFStatement;

NS_ASSUME_NONNULL_BEGIN
// The result set for a DB fetch.
@interface PSPDFResultSet : NSObject

@property (atomic, copy, nullable) NSString *query;
@property (atomic, readonly, nullable) NSMutableDictionary<NSString *, NSNumber *> *columnNameToIndexMap;
@property (atomic, nullable) PSPDFStatement *statement;

+ (instancetype)resultSetWithStatement:(PSPDFStatement *)statement usingParentDatabase:(PSPDFDatabase *)aDB;

- (void)close;

- (void)setParentDB:(nullable PSPDFDatabase *)newDb;

- (BOOL)next;
- (BOOL)nextWithErrorLogEnabled:(BOOL)logEnabled;
- (BOOL)hasAnotherRow;

- (int)columnCount;

- (int)columnIndexForName:(NSString *)columnName;
- (nullable NSString *)columnNameForIndex:(int)columnIdx;

- (int)intForColumn:(NSString *)columnName;
- (int)intForColumnIndex:(int)columnIdx;

- (long)longForColumn:(NSString *)columnName;
- (long)longForColumnIndex:(int)columnIdx;

- (long long int)longLongIntForColumn:(NSString *)columnName;
- (long long int)longLongIntForColumnIndex:(int)columnIdx;

- (unsigned long long int)unsignedLongLongIntForColumn:(NSString *)columnName;
- (unsigned long long int)unsignedLongLongIntForColumnIndex:(int)columnIdx;

- (BOOL)boolForColumn:(NSString *)columnName;
- (BOOL)boolForColumnIndex:(int)columnIdx;

- (double)doubleForColumn:(NSString *)columnName;
- (double)doubleForColumnIndex:(int)columnIdx;

- (nullable NSString *)stringForColumn:(NSString *)columnName;
- (nullable NSString *)stringForColumnIndex:(int)columnIdx;

- (nullable NSDate *)dateForColumn:(NSString *)columnName;
- (nullable NSDate *)dateForColumnIndex:(int)columnIdx;

- (nullable NSData *)dataForColumn:(NSString *)columnName;
- (nullable NSData *)dataForColumnIndex:(int)columnIdx;

- (nullable const unsigned char *)UTF8StringForColumnIndex:(int)columnIdx NS_RETURNS_INNER_POINTER;
- (nullable const unsigned char *)UTF8StringForColumnName:(NSString *)columnName NS_RETURNS_INNER_POINTER;

// returns one of NSNumber, NSString, NSData, or NSNull
- (nullable id)objectForColumnName:(NSString *)columnName;
- (nullable id)objectForColumnIndex:(int)columnIdx;

- (nullable id)objectForKeyedSubscript:(NSString *)columnName;
- (nullable id)objectAtIndexedSubscript:(int)columnIdx;

/*
If you are going to use this data after you iterate over the next row, or after you close the
result set, make sure to make a copy of the data first (or just use dataForColumn:/dataForColumnIndex:)
If you don't, you're going to be in a world of hurt when you try and use the data.
*/
- (nullable NSData *)dataNoCopyForColumn:(NSString *)columnName NS_RETURNS_NOT_RETAINED;
- (nullable NSData *)dataNoCopyForColumnIndex:(int)columnIdx NS_RETURNS_NOT_RETAINED;

- (BOOL)columnIndexIsNull:(int)columnIdx;
- (BOOL)columnIsNull:(NSString *)columnName;


// Returns a dictionary of the row results mapped to case sensitive keys of the column names.
- (nullable NSDictionary<NSString *, id> *)resultDictionary;

- (void)kvcMagic:(id)object;

@end
NS_ASSUME_NONNULL_END
