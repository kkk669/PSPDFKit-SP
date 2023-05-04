//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFLibrary+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFCDocumentLibraryQuery;

@interface PSPDFLibrary (Testing)

/// Generates a query for the Core document library for the given search string and options.
///
/// @param searchString The string for which the query is to be made.
/// @param generateTextPreviews Specifies if text previews of query results should be generated.
/// @param options The options dictionary.
/// @return A document library query instance.
+ (PDFCDocumentLibraryQuery *)queryWithSearchString:(NSString *)searchString generateTextPreviews:(BOOL)generateTextPreviews options:(nullable NSDictionary<PSPDFLibraryOption, id> *)options;

@end

NS_ASSUME_NONNULL_END
