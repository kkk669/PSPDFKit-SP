//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
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

/// Replace first occurrence of string with replacement string. Not case sensitive.
/// Does not use regular expressions.
PSPDF_EXTERN BOOL PSPDFReplaceFirstOccurrenceOfStringWithString(NSMutableString *mutableString, NSString *target, NSString *replacement);

/// Returns the n'th capture group from `regexString` in `string`.
PSPDF_SDK_EXPORT NSString *PSPDFMatchInRegexString(NSString *regexString, NSString *string, NSUInteger captureGroupNumber);

/// Returns all matches as array of NSTextCheckingResult.
PSPDF_EXTERN NSArray<NSTextCheckingResult *> *PSPDFRangeOfMatchesInRegexString(NSString *regexString, NSString *string, NSMatchingOptions options);

/// Get range for regex match.
PSPDF_EXTERN NSRange PSPDFRangeOfMatchInRegexString(NSString *regexString, NSString *string, NSMatchingOptions options, NSUInteger captureGroupNumber);

/// Returns all matches with their capturing groups (NSArray)
PSPDF_EXTERN NSArray<NSArray<NSString *> *> *PSPDFMatchesInRegexStringAsGroups(NSString *regexString, NSString *string, NSMatchingOptions options);

/// Converts a NSTextCheckingResult to a group (NSArray)
PSPDF_EXTERN NSArray<NSString *> *PSPDFGroupsFromResultMatch(NSTextCheckingResult *result, NSString *original);
