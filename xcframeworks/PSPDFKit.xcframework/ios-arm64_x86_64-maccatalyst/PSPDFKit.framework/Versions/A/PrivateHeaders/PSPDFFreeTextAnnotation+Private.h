//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFreeTextAnnotation.h>
#import <PSPDFKit/PSPDFRotatableInternal.h>

NS_ASSUME_NONNULL_BEGIN

/// The default font name for free text annotations.
PSPDF_SDK_EXPORT NSString *const PSPDFDefaultFreeTextFontName;

/// The default font size for free text annotations.
PSPDF_SDK_EXPORT const CGFloat PSPDFDefaultFreeTextFontSize;

/// The default lower font size.
PSPDF_SDK_EXPORT const CGFloat PSPDFTextSizeMinimum;

/// The default upper font size.
PSPDF_SDK_EXPORT const CGFloat PSPDFTextSizeMaximum;

@interface PSPDFFreeTextAnnotation () <PSPDFRotatableInternal>

/// The line height is dynamically calculated based on the font type and size.
- (CGFloat)lineHeight;

/// Clears the “text should fit” flag for the receiver.
///
/// Should be called whenever we regenerate the AP stream and the text does not fit the bounding box.
- (void)instant_clearTextShouldFitMarker;

@end

@interface PSPDFFreeTextAnnotation (Tests)

/// When non-nil this reflects the font size that is used during rendering
/// to ensure text fits in the annotation bounding box without clipping.
@property (nonatomic, nullable, readonly) NSNumber *fittingFontSize;

/// This calculates the largest font size which allows text to completely fit
/// inside the current text bounding box. We use it when resizing the free text
/// annotation using the bottom right knob - which grows or shrinks the font
/// along with the bounding box.
@property (nonatomic, readonly) CGFloat optimalFontSize;

@end

NS_ASSUME_NONNULL_END
