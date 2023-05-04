//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFAnnotationCreator.h>
#import <PSPDFKitUI/PSPDFPresentationContext.h>

@class PSPDFConfiguration, PSPDFDigitalSignatureCoordinator, PSPDFDrawView, PSPDFSignatureFormElement;

NS_ASSUME_NONNULL_BEGIN

/// Handles state and actions required to create a signature annotation.
/// The signature will be added inside the `targetPDFRect`.
PSPDF_SDK_CLASS_SWIFT(SignatureAnnotationCreator)
@interface PSPDFSignatureAnnotationCreator : PSPDFAnnotationCreator

/// Creates an instance of `PSPDFSignatureAnnotationCreator`.
///
/// @param pageView The page view on which the annotation is to be created. This reference is not stored.
/// @param signatureFormElement The signature form element that should be signed. This form elements needs to be on the document already. If `nil` is passed, the user is asked to draw a rectangle on the page, that is used to create a signature form element, with which the document is signed.
/// @param presentationContext The presentation context for the signature. The configuration and signature coordinator are extracted from this context.
- (instancetype)initWithPageView:(PSPDFPageView *)pageView signatureFormElement:(nullable PSPDFSignatureFormElement *)signatureFormElement presentationContext:(id<PSPDFPresentationContext>)presentationContext NS_DESIGNATED_INITIALIZER;

/// The presentation context in which this signature is to be added.
@property (nonatomic, readonly, weak) id<PSPDFPresentationContext> presentationContext;

/// The signature form element that should be signed, passed at init time. This form elements needs to be on the document already. If `nil` is passed, the user is asked to draw a rectangle on the page, that is used to create a signature form element, with which the document is signed.
@property (nonatomic, readonly, weak) PSPDFSignatureFormElement *signatureFormElement;

/// Displays a `PSPDFSignatureViewController` or `PSPDFSignatureSelectorViewController`, based on the signature saving strategy in `configuration`.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See `PSPDFPresentationActions.h` for possible values.
///
/// @return The view controller that will be presented.
- (nullable UIViewController *)presentAppropriateSignatureController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

/// Presents a `PSPDFSignatureViewController` to create a new signature. The signature is saved based on the `configuration`'s `savingStrategy`.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See `PSPDFPresentationActions.h` for possible values.
///
/// @return The view controller that will be presented.
- (nullable UIViewController *)presentSignatureCreationController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options;

/// Creates an ink annotation signature from the draw view for the given page size.
/// 
/// @param drawView View containing the drawn ink lines.
/// @param pageSize Size of the page to which the ink signature will be added.
/// @param targetPDFRect Target location of the ink signature in the PDF coordinate space.
/// @param overrideProvider Delegate that provides the override class for the ink signature if available.
PSPDF_SDK_EXPORT PSPDFAnnotation *_Nullable PSPDFCreateSignatureFromDrawView(PSPDFDrawView *drawView, CGSize pageSize, CGRect targetPDFRect, id<PSPDFOverrideProvider> _Nullable overrideProvider) NS_SWIFT_NAME(createSignatureFromDrawView(_:pageSize:targetPDFRect:overrideProvider:));

/// Creates a signature annotation from an image. Used if the user picks an existing image or when adding a previously saved typed signature.
///
/// @param image The bitmap image to use for the signature.
/// @param pageSize Size of the page to which the ink signature will be added.
/// @param targetPDFRect Target location of the ink signature in the PDF coordinate space.
/// @param overrideProvider Delegate that provides the override class for the ink signature if available.
PSPDF_SDK_EXPORT PSPDFAnnotation *PSPDFCreateSignatureFromImage(UIImage *image, CGSize pageSize, CGRect targetPDFRect, id<PSPDFOverrideProvider> _Nullable overrideProvider) NS_SWIFT_NAME(createSignatureFromImage(_:pageSize:targetPDFRect:overrideProvider:));

/// Creates a signature annotation from text that the user typed and a font the user chose.
///
/// @param text The text to be displayed.
/// @param font The font to use to show the text.
/// @param color The color to render the text.
/// @param pageSize Size of the page to which the ink signature will be added.
/// @param targetPDFRect Target location of the ink signature in the PDF coordinate space.
/// @param overrideProvider Delegate that provides the override class for the ink signature if available.
PSPDF_SDK_EXPORT PSPDFAnnotation *PSPDFCreateSignatureFromText(NSString *text, UIFont *font, UIColor *color, CGSize pageSize, CGRect targetPDFRect, id<PSPDFOverrideProvider> _Nullable overrideProvider) NS_SWIFT_NAME(createSignatureFromText(_:font:color:pageSize:targetPDFRect:overrideProvider:));

@end

NS_ASSUME_NONNULL_END
