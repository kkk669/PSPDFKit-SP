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
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFStringTruncation) {
    PSPDFStringTruncationHead,
    PSPDFStringTruncationMiddle,
    PSPDFStringTruncationTail,
} NS_SWIFT_NAME(StringTruncation);

/// Represents the string direction. 1-1 mapping to the return values of http://icu-project.org/apiref/icu4c/ubidi_8h.html#aeb1fd15743833278cc11906cd5a48aef
///
/// - PSPDFTextDirectionNeutral: The direction is neutral i.e. no control characters.
/// - PSPDFTextDirectionLTR: The base direction of the string is left to right.
/// - PSPDFTextDirectionRTL: The base direction of the string is right to left.
/// - PSPDFTextDirectionUnknown: Used to represent an unchecked direction state.
typedef NS_CLOSED_ENUM(uint8_t, PSPDFTextDirection) {
    PSPDFTextDirectionNeutral,
    PSPDFTextDirectionLTR,
    PSPDFTextDirectionRTL,
    PSPDFTextDirectionUnknown = UINT8_MAX
} NS_SWIFT_NAME(TextDirection);

/// Convert BOOL into a string (YES or NO)
PSPDF_EXPORT NSString *PSPDFBoolString(BOOL value);

@interface NSString (PSPDFFoundation)

/// Returns a reversed string in a performant way, taking composed character sequences into account.
@property (nonatomic, readonly) NSString *pspdf_reversedString NS_SWIFT_NAME(reversed);

/// Transforms a camel case string like "someThing" to "Some Thing".
+ (NSString *)pspdf_humanReadableStringFromCamelCaseString:(NSString *)camelCaseString NS_SWIFT_NAME(humanReadableString(camelCaseString:));

/// Returns " sign here" from "  sign \n here". Removes newlines and replaces them
/// with whitespaces, and replaces multiple whitespaces with a single one.
@property (nonatomic, readonly) NSString *pspdf_newlineCleanedString NS_SWIFT_NAME(newlineCleaned);

/// Replaces new lines with `replacementString`.
/// Trims whitespaces at the start and end at each location where `replacementString` is added.
///
/// @note `replacementString` is not repeated in case there are multiple new lines next to each other.
- (NSString *)pspdf_replaceNewlinesWithString:(NSString *)replacementString NS_SWIFT_NAME(replaceNewlines(with:));

/// Returns "signhere" from " sign here". Removes all whitespace.
@property (nonatomic, readonly) NSString *pspdf_whitespaceCleanedString NS_SWIFT_NAME(whitespaceCleaned);

/// Trims leading and trailing whitespace.
@property (nonatomic, readonly) NSString *pspdf_trimmedString NS_SWIFT_NAME(trimmed);

/// Converts's e.g. "Josh's" into "Josh" and also removes spaces, punctuation characters and newlines.
@property (nonatomic, readonly) NSString *pspdf_searchOptimizedString NS_SWIFT_NAME(searchOptimized);

/// A string with only ASCII letters and numbers.
@property (nonatomic, readonly) NSString *pspdf_stringByDeletingNonASCIILettersAndNumbers NS_SWIFT_NAME(deletingNonASCIILettersAndNumbers);


/// Returns the direction of the first character in the receiver that has a strong direction. Worst case time complexity: O(n).
@property (nonatomic, readonly) PSPDFTextDirection pspdf_textDirection NS_SWIFT_NAME(textDirection);

/// Ensures the string is no longer than `maxLength` characters.
///
/// @param addEllipsis Adds an ellipsis when string is trimmed.
/// @param maxLength Must be be greater than 0.
- (NSString *)pspdf_stringClippedToLength:(NSUInteger)maxLength addEllipsis:(BOOL)addEllipsis NS_SWIFT_NAME(clipped(toLength:addEllipsis:));

/// Filters a string by removing all characters that are part of `characterSet`.
- (NSString *)pspdf_filteredByCharacterSet:(NSCharacterSet *)characterSet NS_SWIFT_NAME(filteredBy(_:));

/// If a string is longer than `length` this truncates the string to a length that is
/// shorter than or equal to length.
///
/// If the string already is smaller than or equal to length, no truncation is done.
///
/// @note This might not work well for very small values for length.
///
/// @param truncation The kind of truncation to do.
/// @param length     The max. length the string should have.
///
/// @return A new string having the desired length.
- (NSString *)pspdf_truncating:(PSPDFStringTruncation)truncation toLength:(NSInteger)length NS_SWIFT_NAME(truncating(_:to:));

/// Checks if the string starts with `prefix` and removes it.
///
/// @param prefix The string prefix to be removed.
/// @return A new string with `prefix` removed or `self` if the string is not prefixed by `prefix`.
- (NSString *)pspdf_stringByDeletingPrefix:(NSString *)prefix NS_SWIFT_NAME(deletingPrefix(_:));

/// This will create a @%tux version (@2x, @3x) of the path on retina devices.
/// If the version does not exist and `check` is enabled, this will return a copy of the original string.
- (NSString *)pspdf_resolutionDependentPathFallingBackToOriginal:(BOOL)check NS_SWIFT_NAME(resolutionDependentPath(fallingBackToOriginal:));

@end

@interface NSString (PSPDFFileNameType)

/// Returns any matching UTI for the extension of the given filename.
/// Returns nil if the filename has no extension or if no type is found for the filename extension.
///
/// @warning This is susceptible to UTI overloading. Another app installed on the system could declare a new UTI associated with a filename extension,
/// and which UTI gets picked as ‘preferred’ is undefined. Correct code should consider the fact that a filename extension might map to multiple UTIs.
/// Use the method below to get all possible types.
+ (nullable UTType *)pspdf_anyUTITypeFromFilename:(NSString *)fileName NS_SWIFT_NAME(anyUTIType(from:));

/// Returns all possible types for the extension of the given filename.
+ (NSArray<UTType *> *)pspdf_allUTITypesFromFilename:(NSString *)fileName NS_SWIFT_NAME(allUTITypes(from:));

/// Ensures that the filename conforms to the type provided.
///
/// @note The receiver needs to be a filename with a valid extension.
- (BOOL)pspdf_conformsToUTIType:(UTType *)utiType NS_SWIFT_NAME(conforms(toUTIType:));

/// Ensures that the UTI is of type PDF.
///
/// @note The receiver needs to be a filename with a valid extension.
@property (nonatomic, readonly) BOOL pspdf_typeIsPDF NS_SWIFT_NAME(typeIsPDF);

/// Ensures that the UTI is of type JPEG.
///
/// @note The receiver needs to be a filename with a valid extension.
@property (nonatomic, readonly) BOOL pspdf_typeIsJPEG NS_SWIFT_NAME(typeIsJPEG);

/// Ensures that the UTI is of type PNG.
///
/// @note The receiver needs to be a filename with a valid extension.
@property (nonatomic, readonly) BOOL pspdf_typeIsPNG;

/// Ensures that the UTI is of type GIF.
///
/// @note The receiver needs to be a filename with a valid extension.
@property (nonatomic, readonly) BOOL pspdf_typeIsGIF NS_SWIFT_NAME(typeIsGIF);

/// Interpets a string true/yes/1 or false/no/0, else returns nil.
@property (nonatomic, readonly, nullable) NSNumber *pspdf_booleanFromString NS_SWIFT_NAME(booleanValue);

/// Returns YES, if the string can be used as a name of a regular file on iOS and Mac OS.
@property (nonatomic, readonly) BOOL pspdf_isValidFilename NS_SWIFT_NAME(isValidFilename);

/// Returns a version of the string that is suitable to use as a filename for a regular (non-hidden) file.
///
/// @see `pspdf_isValidFilename`
/// @param isCrossPlatformCompatible When true, creates a title which is cross platform compatible, applying stricter rules.
- (NSString *)pspdf_sanitizedFilenameForCrossPlatforms:(BOOL)isCrossPlatformCompatible NS_SWIFT_NAME(sanitizedFilename(crossPlatformCompatible:));

/// Converts a C string to NSString. Tries very hard.
+ (instancetype)pspdf_stringWithCString:(const char *)cString;

@end

/// Always returns a string, will be empty if `string` is nil.
/// This is there since `[NSString stringWithString:nil]` throws an exception.
PSPDF_INLINE NSString *PSPDFEnsureString(NSString *_Nullable string) {
    PSPDFCAssertClassOptional(string, NSString);
    return (NSString *)string ?: @"";
}

NS_ASSUME_NONNULL_END

#ifdef __cplusplus
#include <optional>
#include <string>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (PSPDFFoundationCpp)

/// Converts an unicode std::string to NSString.
+ (instancetype)pspdf_stringWithStdString:(const std::string &)string;

+ (nullable instancetype)pspdf_stringWithOptionalStdString:(const std::optional<std::string> &)optionalString;

/// Convert string to a C++ std::string.
@property (nonatomic, readonly) std::string pspdf_stdString;

@end

NS_ASSUME_NONNULL_END
#endif
