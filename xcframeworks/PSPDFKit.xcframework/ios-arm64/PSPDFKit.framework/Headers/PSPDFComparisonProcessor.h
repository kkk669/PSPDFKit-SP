//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocument;
@class PSPDFComparisonConfiguration;

NS_ASSUME_NONNULL_BEGIN

/// An object that can be used to generate a comparison document between two
/// versions of a document.
///
/// # Customizing the Comparison Document
///
/// You may use the `ComparisonConfiguration` to customize the contents and the
/// look of the generated comparison document. See its documentation for more
/// information.
///
/// # Aligning the Documents
///
/// In case the two versions of a document are not perfectly aligned, the
/// comparison processor accepts an optional transformation matrix that
/// describes how the page in the new version of a document is aligned in
/// relation to the page in the old version of a document.
///
/// You may either provide an already computed transformation matrix or two sets
/// of equivalent points from both versions of a document and let the
/// comparison processor automatically compute the transformation matrix.
///
/// You may also use the `DocumentAlignmentViewController` from the PSPDFKitUI
/// framework to initiate a process where users can visually select the two sets
/// of points themselves. See its documentation for more information.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ComparisonProcessor)
@interface PSPDFComparisonProcessor : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initialize the comparison processor with the given configuration.
///
/// @note Initializing the comparison processor requires the Comparison
///       component to be enabled for your license.
///
/// @param configuration The configuration that will be used to generate a
///        comparison document.
- (instancetype)initWithConfiguration:(PSPDFComparisonConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

/// Generate a comparison document by overlaying a new version of a page onto an
/// old version of the same page.
///
/// The generated comparison document will contain all other pages from the old
/// version of a document at their original indices, and it will have the same
/// security options as the old version of a document.
///
/// @param oldDocument The old version of a document.
/// @param oldDocumentPageIndex The index of the page in the old version of a
///        document.
/// @param newDocument The new version of a document.
/// @param newDocumentPageIndex The index of the page in the new version of a
///        document. This page will be auto-rotated to match the rotation of the
///        equivalent page in the old version of a document.
/// @param transform The transformation matrix that describes how the page in
///        the new version of a document is aligned in relation to the page in
///        the old version of a document. Use `.identity` if the pages are
///        perfectly aligned.
/// @param error If generating a comparison document fails, upon return contains
///        an error object that describes the problem.
///
/// @returns A comparison document created with the given parameters and the
///          configuration given at initialization, or `nil` if an error occurs.
- (nullable PSPDFDocument *)comparisonDocumentWithOldDocument:(PSPDFDocument *)oldDocument pageIndex:(PSPDFPageIndex)oldDocumentPageIndex newDocument:(PSPDFDocument *)newDocument pageIndex:(PSPDFPageIndex)newDocumentPageIndex transform:(CGAffineTransform)transform error:(NSError * __autoreleasing *)error NS_REFINED_FOR_SWIFT;

/// Generate a comparison document by overlaying a new version of a page onto an
/// old version of the same page.
///
/// The generated comparison document will contain all other pages from the old
/// version of a document at their original indices, and it will have the same
/// security options as the old version of a document.
///
/// @param oldDocument The old version of a document.
/// @param oldDocumentPageIndex The index of the page in the old version of a
///        document.
/// @param oldDocumentPoints The array of three reference points in the PDF
///        coordinate space of the page in the old version of a document.
/// @param newDocument The new version of a document.
/// @param newDocumentPageIndex The index of the page in the new version of a
///        document. This page will be auto-rotated to match the rotation of the
///        equivalent page in the old version of a document.
/// @param newDocumentPoints The array of three reference points in the PDF
///        coordinate space of the page in the new version of a document,
///        equivalent to the points in the old version of a document.
/// @param error If generating a comparison document fails, upon return contains
///        an error object that describes the problem.
///
/// @returns A comparison document created with the given parameters and the
///          configuration given at initialization, or `nil` if an error occurs.
- (nullable PSPDFDocument *)comparisonDocumentWithOldDocument:(PSPDFDocument *)oldDocument pageIndex:(PSPDFPageIndex)oldDocumentPageIndex points:(NSArray<NSValue /* CGPoint */ *> *)oldDocumentPoints newDocument:(PSPDFDocument *)newDocument pageIndex:(PSPDFPageIndex)newDocumentPageIndex points:(NSArray<NSValue /* CGPoint */ *> *)newDocumentPoints error:(NSError * __autoreleasing *)error NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
