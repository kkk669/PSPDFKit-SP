//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
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

NS_ASSUME_NONNULL_BEGIN


/// Methods that formalize the approach from the `NSFileCoordinator` documentation for failable file access.
@interface NSFileCoordinator (PSPDFKit)


/// Attempts to perform a coordinated read, propagating any error from the (failable) accessor.
///
/// @param url The URL to perform a coordinated read on.
/// @param options Any options for that coordinated read.
/// @param outError A pointer to populate in case of an error — both, accessing the file, as well as the accessor itself.
/// @param reader A block that signals failure by returning `NO` and populating its error pointer.
- (BOOL)pspdf_boolForCoordinateReadingItemAtURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options error:(NSError **)outError byAccessor:(BOOL (^)(NSURL *readURL, NSError **errorToPropagate))reader NS_SWIFT_UNAVAILABLE("Please use the generic function instead");

/// Attempts to perform a coordinated write, propagating any error from the (failable) accessor.
///
/// @param url The URL to perform a coordinated write on.
/// @param options Any options for that coordinated write.
/// @param outError A pointer to populate in case of an error — both, accessing the file, as well as the accessor itself.
/// @param writer A block that signals failure by returning `NO` and populating its error pointer.
- (BOOL)pspdf_boolForCoordinateWritingItemAtURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options error:(NSError **)outError byAccessor:(BOOL (^)(NSURL *, NSError **errorToPropagate))writer NS_SWIFT_UNAVAILABLE("Please use the generic function instead");

/// Attempts to perform a coordinated read on one file and a write at another, propagating any error from the (failable) accessor.
///
/// @param readingURL The URL to perform a coordinated read on.
/// @param readingOptions Any options for that coordinated read.
/// @param writingURL The URL to perform the coordinated write on.
/// @param writingOptions Any options for that coordinated write.
/// @param outError A pointer to populate in case of an error — both, accessing the file, as well as the accessor itself.
/// @param readerWriter A block that signals failure by returning `NO` and populating its error pointer.
- (BOOL)pspdf_boolForCoordinateReadingItemAtURL:(NSURL *)readingURL options:(NSFileCoordinatorReadingOptions)readingOptions writingItemAtURL:(NSURL *)writingURL options:(NSFileCoordinatorWritingOptions)writingOptions error:(NSError **)outError byAccessor:(BOOL (^)(NSURL *newReadingURL, NSURL *newWritingURL, NSError **errorToPropagate))readerWriter NS_SWIFT_UNAVAILABLE("Please use the generic function instead");

/// Attempts to perform a coordinated write on two files, propagating any error from the (failable) accessor.
///
/// @param url1 The first URL to perform a coordinated write on.
/// @param options1 Any options for that coordinated write on url1.
/// @param url2 The second URL to perform a coordinated write on.
/// @param options2 Any options for that coordinated write on url2.
/// @param outError A pointer to populate in case of an error — both, accessing the file, as well as the accessor itself.
/// @param writer A block that signals failure by returning `NO` and populating its error pointer.
- (BOOL)pspdf_boolForCoordinateWritingItemAtURL:(NSURL *)url1 options:(NSFileCoordinatorWritingOptions)options1 writingItemAtURL:(NSURL *)url2 options:(NSFileCoordinatorWritingOptions)options2 error:(NSError **)outError byAccessor:(BOOL (^)(NSURL *newURL1, NSURL *newURL2, NSError **errorToPropagate))writer NS_SWIFT_UNAVAILABLE("Please use the generic function instead");

/// Attempts to perform a coordinated read, propagating any error from the (failable) accessor.
///
/// @param url The URL to perform a coordinated read on.
/// @param options Any options for that coordinated read.
/// @param outError A pointer to populate in case of an error — both, accessing the file, as well as the accessor itself.
/// @param reader A block that signals failure by returning `nil` and populating its error pointer.
- (nullable id)pspdf_objectForCoordinateReadingItemAtURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options error:(NSError **)outError byAccessor:(id (^)(NSURL *newURL, NSError **errorToPropagate))reader NS_SWIFT_UNAVAILABLE("Please use the generic function instead");

/// Attempts to perform a coordinated write, propagating any error from the (failable) accessor.
///
/// @param url The URL to perform a coordinated write on.
/// @param options Any options for that coordinated write.
/// @param outError A pointer to populate in case of an error — both, accessing the file, as well as the accessor itself.
/// @param writer A block that signals failure by returning `nil` and populating its error pointer.
- (nullable id)pspdf_objectForCoordinateWritingItemAtURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options error:(NSError **)outError byAccessor:(id (^)(NSURL *newURL, NSError **errorToPropagate))writer NS_SWIFT_UNAVAILABLE("Please use the generic function instead");

@end

NS_ASSUME_NONNULL_END
