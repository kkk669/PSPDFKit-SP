//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFSignatureContainer, PSPDFSignatureFormElement, PSPDFSignatureAppearanceBuilder;

/// The digital signature coordinator handles signing and presenting a digitally signed document.
/// Signing a document with a certificate creates a readonly copy, as the file has to be completely re-written.
///
/// @note Depending on your application logic you will want to choose where to store this new file.
/// PSPDFKit suggests a randomized temporary folder + file name as default location.
///
/// Register your subclass via overrideClass:withClass: on the configuration object. Don't instantiate an object of this class yourself.
PSPDF_CLASS_SWIFT(DigitalSignatureCoordinator)
@interface PSPDFDigitalSignatureCoordinator : NSObject<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFDigitalSignatureCoordinator (SubclassingHooks)

/// Path that is used for storing the newly created document, which will be digitally signed.
///
/// @note `fileName` is a suggestion based on the title of the original document, which can be used in the path.
/// The path will be sanitized, and it will me made sure that the suffix is .pdf.
- (NSString *)pathForDigitallySignedDocumentFromOriginalDocument:(PSPDFDocument *)document suggestedFileName:(NSString *)fileName;

/// Present the digitally signed document, containing the signature on `pageIndex`.
///
/// @param signedDocument The newly created document containing the digital signature.
/// @param pageIndex The page index the digital signature is on. You can use this to scroll to this page when presenting the new document.
/// @param presentationContext A presentation context that can be used to present the new document to. Usually the `PDFViewController` that initiated the digital signing process.
- (void)presentSignedDocument:(PSPDFDocument *)signedDocument showingPageIndex:(PSPDFPageIndex)pageIndex withPresentationContext:(id<PSPDFPresentationContext>)presentationContext;

/// Subclassing hook that can be used to configure the signature appearance.
///
/// @note If an ink signature has lines set, the `signatureGraphic` will be preconfigured.
- (void)configureSignatureAppearanceWithBuilder:(PSPDFSignatureAppearanceBuilder *)builder document:(PSPDFDocument *)document signature:(PSPDFSignatureContainer *)signature;

@end

NS_ASSUME_NONNULL_END
