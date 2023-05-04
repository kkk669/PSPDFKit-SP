//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFDataProviding.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFDataProviding;
@class PSPDFAnnotation;

typedef NSString *PSPDFAppearanceStreamGenerationOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(AppearanceStreamGenerationOption);

/// Option for `dataProviderForAnnotation:options:`. If set, the resulting appearance stream is to be used for a flattened document.
PSPDF_EXPORT PSPDFAppearanceStreamGenerationOption const PSPDFAppearanceGenerationFlatten;

/// Option for `dataProviderForAnnotation:options:`. If set, the resulting appearance stream is to be used for printing.
PSPDF_EXPORT PSPDFAppearanceStreamGenerationOption const PSPDFAppearanceGenerationPrint;

/// A instance of this protocol can be set on any `PSPDFAnnotation` and instead of using the PSPDFKit provided
/// appearance stream generation methods, any PDF can be returned.
///
/// The annotation will use the first page of the returned PDF as its appearance and this content will be embedded into the PDF.
PSPDF_PROTOCOL_SWIFT(AppearanceStreamGenerating)
@protocol PSPDFAppearanceStreamGenerating <NSObject>

/// Called when the appearance stream data for the given annotation is needed.
///
/// The data represented by the `DataProviding` class must be a valid formed PDF. The contents of the first page
/// of that PDF file will be embedded in the `annotation` as its appearance stream.
///
/// @note This method can be called on any thread at any time and is also time sensitive.
- (nullable id<PSPDFDataProviding>)dataProviderForAnnotation:(PSPDFAnnotation *)annotation options:(nullable NSDictionary<PSPDFAppearanceStreamGenerationOption, id> *)options;

@end

NS_ASSUME_NONNULL_END
