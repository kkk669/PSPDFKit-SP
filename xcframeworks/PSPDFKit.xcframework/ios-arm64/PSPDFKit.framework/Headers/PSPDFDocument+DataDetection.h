//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>

NS_ASSUME_NONNULL_BEGIN

// MARK: Options for the Object Finder.

typedef NSString *PSPDFObjectFinderOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(Document.ObjectFinderOption);

/// Option indicating if glyphs should be extracted. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionExtractGlyphs;

/// Option indicating if full `PSPDFWord`s should be extracted. Implies `PSPDFObjectFinderOptionExtractText`. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionExtractWords;

/// Option indicating if text should be extracted. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionExtractText;

/// Option indicating if text blocks should be extracted. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionExtractTextBlocks;

/// Option indicating if image info should be extracted. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionExtractImages;

/// Option indicating if annotations should be extracted. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionExtractAnnotations;

/// Ignore large text blocks that are > 90% of a page. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionIgnoreLargeTextBlocks;

/// Include annotations of attached type. (Type: `PSPDFAnnotationType` wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionAnnotationTypes;

/// Special case; used for `PSPDFAnnotationTypeNote` hit testing. (Type: `CGRect` wrapped in `NSValue`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionAnnotationPageBounds;

/// Special case; Used to correctly hit test zoom-invariant annotations. (Type: `CGFloat` wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionPageZoomLevel;

/// Option indicating if annotations that are part of a group should be included. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionAnnotationIncludedGrouped;

/// Will sort words/annotations (smaller words/annotations first).
/// Also reverses z-order so annotations on top are returned first.
/// Use for touch detection. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionSmartSort;

/// Will use path-based hit-testing based on the center point if set.
/// All annotations that support path based hit-testing but fail the test will be excluded from the results.
/// (Type: `CGFloat` wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionMinDiameter;

/// Will look at the text flow and select full sentences, not just what's within the rect. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionTextFlow;

/// Will stop after finding the first matching object. (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionFindFirstOnly;

/// Only relevant for rect. Will test for intersection instead of objects that are fully included in the pdfRect.
/// Defaults to YES if not set.
/// (Type: Boolean wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionTestIntersection;

/// Only relevant if `PSPDFObjectFinderOptionTestIntersection` is set to YES.
/// Test succeeds if the fraction of the overlapping area between the object and pdfRect is greater than the fraction set here.
/// Defaults to 0 if not set, which means the test succeeds if there is any intersection at all. Valid values: 0 - 1.
///
/// @note: The overlap is calculated w.r.t the total area. So, if `ao` is the area of the object, `ap` is the area of pdfRect
/// and `ai` is the intersecting area, then the overlap proportion would be ai / (ao + ap - ai).
/// (Type: double wrapped in `NSNumber`)
PSPDF_EXPORT PSPDFObjectFinderOption const PSPDFObjectFinderOptionTestIntersectionFraction;


// MARK: Object Finder Output Types.

typedef NSString *PSPDFObjectFinderType NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(Document.ObjectFinderType);

/// Returns matching glyphs. Return type is NSArray <PSPDFGlyph *> *
PSPDF_EXPORT PSPDFObjectFinderType const PSPDFObjectFinderTypeGlyphs;

/// Returns matching words. Return type is NSArray <PSPDFWord *> *
PSPDF_EXPORT PSPDFObjectFinderType const PSPDFObjectFinderTypeWords;

/// Returns matching text. Return type is NSString *
PSPDF_EXPORT PSPDFObjectFinderType const PSPDFObjectFinderTypeText;

/// Returns matching text blocks. Return type is NSArray <PSPDFTextBlock *> *
PSPDF_EXPORT PSPDFObjectFinderType const PSPDFObjectFinderTypeTextBlocks;

/// Returns matching image info. Return type is NSArray <PSPDFImageInfo *> *
PSPDF_EXPORT PSPDFObjectFinderType const PSPDFObjectFinderTypeImages;

/// Returns matching annotations. Return type is NSArray <PSPDFAnnotation *> *
PSPDF_EXPORT PSPDFObjectFinderType const PSPDFObjectFinderTypeAnnotations;

@interface PSPDFDocument (DataDetection)

/// Set this property to allow automatic link detection.
/// Will only add links where no link annotations already exist.
/// Defaults to `PSPDFTextCheckingTypeNone` for performance reasons.
///
/// Set to `PSPDFTextCheckingTypeLink` if you are see URLs in your document that are not clickable.
/// `PSPDFTextCheckingTypeLink` is the default behavior for desktop apps like Adobe Acrobat or Apple Preview.
///
/// @note This requires that you keep the `PSPDFFileAnnotationProvider` in the `annotationManager`.
/// (Default). Needs to be set before the document is being displayed or annotations are accessed!
/// The exact details how detection works are an implementation detail.
/// Apple's Data Detectors are currently used internally.
///
/// @warning Auto-detecting links is useful but might slow down annotation display.
@property (nonatomic) PSPDFTextCheckingType autodetectTextLinkTypes;

/// Iterates over all pages at `indexes` and creates new annotations for `linkTypes`.
/// Will ignore any text that is intersecting with an already existing link annotation.
/// It is your responsibility to add the annotations to the document.
///
/// If an error occurs, this method returns `nil` while setting the out `error`
/// parameter to the encountered error.
///
/// @note To analyze the whole document, use
/// `[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, document.pageCount)]`
///
/// `options` can take a PSPDFObjectFinderTypeAnnotations of type NSDictionary -> page to prevent auto-fetching for comparison.
///
/// @warning Performs text and annotation extraction and analysis. Might be slow.
/// `progressBlock` might be called from different threads.
/// Ensure you dispatch to the main queue for progress updates.
- (nullable NSDictionary<NSNumber *, NSArray<__kindof PSPDFAnnotation *> *> *)annotationsByDetectingLinkTypes:(PSPDFTextCheckingType)linkTypes forPagesAtIndexes:(NSIndexSet *)indexes options:(nullable NSDictionary<PSPDFObjectFinderType, NSDictionary<NSNumber *, NSArray<PSPDFAnnotation *> *> *> *)options progress:(nullable void (^)(NSArray<__kindof PSPDFAnnotation *> *annotations, NSUInteger page, BOOL *stop))progressBlock error:(NSError **)error;

@end

@interface PSPDFDocument (TextParser)

/// Filters out watermarks from text selection and extraction. Defaults to YES.
///
/// @note Toggling this will invalidate all current text parsers.
/// @note Not all watermarks are properly identified by the PDF file. Due to this, PSPDFKit has to try to identify possible
/// watermarks. This might accidentally filter out wanted text. If this is the case, please set `isWatermarkFilterEnabled`
/// to `false` and send a support request (https://pspdfkit.com/support/request) with the misbehaving PDF file.
@property (nonatomic, getter=isWatermarkFilterEnabled) BOOL watermarkFilterEnabled;

/// Fetches the text parser for the requested page index.
///
/// @param pageIndex The page index for which the text parser is required.
/// @return An instance of `PSPDFTextParser`, if one could be created, else `nil`.
- (nullable PSPDFTextParser *)textParserForPageAtIndex:(PSPDFPageIndex)pageIndex;

@end

@interface PSPDFDocument (ObjectFinder)

// MARK: Object Finder Methods

/// Find objects (glyphs, words, images, annotations) at the specified `pdfPoint`.
///
/// @note Unless set otherwise, for points `PSPDFObjectFinderOptionTestIntersection` is YES automatically.
/// If `options` is nil, we assume `PSPDFObjectFinderOptionExtractText` and `PSPDFObjectFinderOptionExtractWords`.
/// Annotations with the `Hidden` or `NoView` flag are ignored. This method is thread safe.
///
/// @param pdfPoint The point in PDF coordinates where we want to find the objects.
/// @param pageIndex The page index where we want to find the objects.
/// @param options Options dictionary. The PSPDFObjectFinderOption enum lists all the available options.
///
/// @return A dictionary containing the matched objects. The exact return type for each PSPDFObjectFinderType is given below:
/// PSPDFObjectFinderTypeGlyphs -> NSArray <PSPDFGlyph *> *
/// PSPDFObjectFinderTypeText -> NSString *
/// PSPDFObjectFinderTypeWords -> NSArray <PSPDFWord *> *
/// PSPDFObjectFinderTypeTextBlocks -> NSArray <PSPDFTextBlock *> *
/// PSPDFObjectFinderTypeImages -> NSArray <PSPDFImageInfo *> *
/// PSPDFObjectFinderTypeAnnotations -> NSArray <PSPDFAnnotation *> *
- (NSDictionary<PSPDFObjectFinderType, id> *)objectsAtPDFPoint:(CGPoint)pdfPoint pageIndex:(PSPDFPageIndex)pageIndex options:(nullable NSDictionary<PSPDFObjectFinderOption, NSValue *> *)options;

/// Find objects (glyphs, words, images, annotations) at the specified `pdfRect`.
///
/// @note Unless set otherwise, for points `PSPDFObjectFinderOptionTestIntersection` is YES automatically.
/// If `options` is nil, we assume `PSPDFObjectFinderTypeExtractGlyphs` only.
/// Annotations with the `Hidden` or `NoView` flag are ignored. This method is thread safe.
///
/// @param pdfRect The rect in PDF coordinates where we want to find the objects.
/// @param pageIndex The page index where we want to find the objects.
/// @param options Options dictionary. The PSPDFObjectFinderOption enum lists all the available options.
///
/// @return A dictionary containing the matched objects. The exact return type for each PSPDFObjectFinderType is given below:
/// PSPDFObjectFinderTypeGlyphs -> NSArray <PSPDFGlyph *> *
/// PSPDFObjectFinderTypeText -> NSString *
/// PSPDFObjectFinderTypeWords -> NSArray <PSPDFWord *> *
/// PSPDFObjectFinderTypeTextBlocks -> NSArray <PSPDFTextBlock *> *
/// PSPDFObjectFinderTypeImages -> NSArray <PSPDFImageInfo *> *
/// PSPDFObjectFinderTypeAnnotations -> NSArray <PSPDFAnnotation *> *
- (NSDictionary<PSPDFObjectFinderType, id> *)objectsAtPDFRect:(CGRect)pdfRect pageIndex:(PSPDFPageIndex)pageIndex options:(nullable NSDictionary<PSPDFObjectFinderOption, NSValue *> *)options;

@end

NS_ASSUME_NONNULL_END
