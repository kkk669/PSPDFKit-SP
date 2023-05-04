//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFStampAnnotation.h>

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFRotatableInternal.h>

NS_ASSUME_NONNULL_BEGIN

PSPDF_SDK_EXPORT const CGSize PSPDFStampDefaultSize;

/// A stamp can be many things. This enum isn’t used in many places yet but could be a good way to make the branching code paths clearer.
/// We use the Stamp details to determine its category
///  - Standard: If the title of the stamp matches any of the default titles for stamps from Acrobat.
///  - Custom Text: If the `subtitle` and the `title` are non nil.
///  - Image: There's a backing image present.
///  - Vector: When none of the above cases are true.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFStampCategory) {
    /// A standard stamp from Acrobat or the spec. These display text except for the accepted and rejected stamps.
    PSPDFStampCategoryStandard,
    /// A stamp that displays a title and possibly a subtitle set by the user. They look similar to standard text stamps. This is a PSPDFKit addition.
    PSPDFStampCategoryCustomText,
    /// A stamp where the AP stream contains only an image resource. We extract the image.
    PSPDFStampCategoryImage,
    /// A stamp that is not in one of the other categories. We just render its appearance stream.
    PSPDFStampCategoryVector,
} PSPDF_ENUM_SWIFT(StampCategory);

@interface PSPDFStampAnnotation () <PSPDFRotatableInternal>

/// Returns the stamp types for default stamps.
+ (NSArray<PSPDFStampType> *)defaultStampTypes;

/// A boxed `PDFCStampType` from the stamp’s `stampType` string or nil if it’s not a standard stamp.
@property (atomic, readonly, nullable) NSNumber *boxedStampType;

/// Loads the image from core. Images are not loaded from core by default, only when required.
- (BOOL)loadAndSetImageWithError:(NSError **)error;

// MARK: - Tests

/// Be aware this might return bad results during initialization when the properties are not all set up.
@property (atomic, readonly) PSPDFStampCategory category;

@end

// MARK: - PSPDFStampAnnotationMarker

@interface UIImage (PSPDFStampAnnotationMarker)

/// Can be set when an image, associated with a stamp annotation, doesn't have an alpha value or should not respect its alpha value.
@property (atomic, assign) BOOL pspdf_forceIgnoreAlpha;

@end

NS_ASSUME_NONNULL_END
