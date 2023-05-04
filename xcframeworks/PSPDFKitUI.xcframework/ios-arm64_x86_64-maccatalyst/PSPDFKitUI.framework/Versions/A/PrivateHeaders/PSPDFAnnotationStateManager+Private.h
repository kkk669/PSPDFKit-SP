//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationStateManager.h>

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKit/PSPDFRenderRequest.h>

@class PSPDFAnnotationCreator, PSPDFImageAnnotationCreator, PSPDFDrawViewManager;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAnnotationStateManager () <PSPDFOverrideProvider>

/// Sent when we change the state.
PSPDF_EXTERN NSNotificationName const PSPDFAnnotationStateManagerChangedStateNotification;

/// Designated initializer.
/// Returns nil if annotations are not licensed.
- (nullable instancetype)initWithPDFController:(PSPDFViewController *)pdfController;

/// Annotation state helpers.
@property (nonatomic, getter=isInDrawingState, readonly) BOOL inDrawingState;
@property (nonatomic, readonly) NSSet<PSPDFAnnotationString> *markupAnnotationStates;

/// This mask specifies the types of annotations to be selected by the multi select tool.
@property (class, nonatomic, readonly) PSPDFAnnotationType annotationTypesForMultiSelect;

/// Sets the specified state, tied to the passed in creator. The annotation state manager begins observing the creator's `status`.
/// When the creator transitions to `PSPDFAnnotationCreatorStatusFinished`, the state manager automatically clears its own `state`.
///
/// @param state The state that the receiver should switch to.
/// @param creator The creator to which the given state is tied.
- (void)setState:(PSPDFAnnotationString)state andObserveCreator:(PSPDFAnnotationCreator *)creator;

/// Selects a location on the pageView and triggers the corresponding selection action at that point.
/// Only relevant for states that use selection view (PSPDFAnnotationStringFreeText, PSPDFAnnotationStringNote,
/// PSPDFAnnotationStringSignature, PSPDFAnnotationStringImage, PSPDFAnnotationStringSound,
/// PSPDFAnnotationStringSelectionTool).
///
/// @param pageView The page view on which the selection should be performed.
/// @param point A location in the pageView coordinate system.
- (void)performSelectionOnPageView:(PSPDFPageView *)pageView atPoint:(CGPoint)point;

/// Set this property to allow drawing a signature area via the selection view.
/// This property is only honored if the `state` is `Annotation.Tool.signature`.
@property (nonatomic) BOOL shouldDrawSignatureArea;


/// Specifies if touch handling should be limited to certain touch types in the provided state.
///
/// @param state The annotation state for which touch types should be provided.
/// @return An array of `UITouchType` values wrapped in `NSNumber` objects.
- (NSArray<NSNumber *> *)allowedTouchTypesForDrawAndSelectionViewsForState:(nullable PSPDFAnnotationString)state;

/// The document render options for PSPDFRenderTypePage.
@property (nonatomic, readonly) PSPDFRenderOptions *renderOptions;

/// Displays a `PSPDFImagePickerController` and toggles the state to `PSPDFAnnotationStringImage`. This will display an alert if the user selects UIImagePickerControllerSourceTypeCamera but does not grant permission.
///
/// @param sender A `UIView` or `UIBarButtonItem` used as the anchor view for the popover controller.
/// @param options A dictionary of presentation options. See PSPDFPresentationActions.h for possible values.
/// @param annotationCreator An instance of a `PSPDFImageAnnotationCreator` that will control how and if an image annotation will be created.
- (nullable UIViewController *)toggleImagePickerController:(nullable id)sender presentationOptions:(nullable NSDictionary<PSPDFPresentationOption, id> *)options annotationCreator:(nullable PSPDFImageAnnotationCreator *)annotationCreator;

@end

NS_ASSUME_NONNULL_END
