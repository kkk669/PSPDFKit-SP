//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFViewController.h>

#import <PSPDFKitUI/PSPDFEditMenuAppearance.h>
#import <PSPDFKitUI/PSPDFViewControllerDelegate.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation, PSPDFGlyph, PSPDFImageInfo, PSPDFMenuItem, PSPDFPageInfo, PSPDFPageView;
@protocol PSPDFAnnotationPresenting;

@interface PSPDFViewController (Delegates)

- (BOOL)delegateShouldChangeDocument:(nullable PSPDFDocument *)document;
- (void)delegateDidChangeDocument;

- (void)delegateWillScheduleRenderTaskForPageView:(PSPDFPageView *)pageView;
- (void)delegateDidFinishRenderTaskForPageView:(PSPDFPageView *)pageView;

- (void)delegateDidUpdateContentImageForPageView:(PSPDFPageView *)pageView isPlaceholder:(BOOL)placeholder;

- (void)delegateDidChangeViewMode:(PSPDFViewMode)viewMode;

- (void)delegateWillBeginDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;
- (void)delegateDidEndDisplayingPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

- (void)delegateDidConfigurePageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;
- (void)delegateDidCleanupPageView:(PSPDFPageView *)pageView forPageAtIndex:(NSInteger)pageIndex;

// MARK: Text selection

- (BOOL)delegateShouldSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

- (void)delegateDidSelectText:(NSString *)text withGlyphs:(NSArray<PSPDFGlyph *> *)glyphs atRect:(CGRect)rect onPageView:(PSPDFPageView *)pageView;

- (nullable NSArray<PSPDFMenuItem *> *)delegateShouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedText:(NSString *)selectedText inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

- (nullable NSArray<PSPDFMenuItem *> *)delegateShouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forSelectedImage:(PSPDFImageInfo *)selectedImage inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView;

// MARK: Annotations

- (BOOL)delegateDidTapOnAnnotation:(PSPDFAnnotation *)annotation annotationPoint:(CGPoint)annotationPoint annotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView pageView:(PSPDFPageView *)pageView viewPoint:(CGPoint)viewPoint;

- (NSArray<PSPDFAnnotation *> *)delegateShouldSelectAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;
- (void)delegateDidSelectAnnotations:(NSArray<__kindof PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;
- (void)delegateDidDeselectAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView;

/// Called when a custom annotation menu item was tapped that the page view does not know how to handle.
- (void)delegateHandleCreationOfCustomAnnotationType:(PSPDFAnnotationString)type variant:(nullable PSPDFAnnotationVariantString)variant atPoint:(CGPoint)point onPageView:(PSPDFPageView *)pageView;

// MARK: Customizing Annotation Display

/// Override point to customize the decision making process whether the given annotation should be
/// displayed.
///
/// If the receiver’s `delegate` implements `pdfViewController:shouldDisplayAnnotation:onPageView:`,
/// the parameters are forwarded to it, and the result of that call is returned. Otherwise, this method
/// returns `true`.
- (BOOL)pageView:(PSPDFPageView *)pageView shouldDisplayAnnotation:(PSPDFAnnotation *)annotation;

/// Override point to customize or replace the view used to display the given annotation.
///
/// If the receiver’s `delegate` implements `pdfViewController:annotationView:forAnnotation:onPageView:`,
/// the parameters are forwarded to it, and the result of that call is returned. If the delegate does
/// not implement this method, the `annotationView` is returned as is.
///
/// @param pageView The page view that will add the return value to its view hierarchy.
/// @param annotationView The view to be customized/replaced.
/// @param annotation The annotation that is displayed by the view.
- (nullable UIView<PSPDFAnnotationPresenting> *)pageView:(PSPDFPageView *)pageView customizeAnnotationView:(nullable UIView<PSPDFAnnotationPresenting> *)annotationView forAnnotation:(PSPDFAnnotation *)annotation;

// MARK: Annotation View Life-cycle

/// Override point to customize the behavior when an annotation view is about to be displayed.
///
/// If the receiver’s `delegate` implements `pdfViewController:willShowAnnotationView:onPageView:`, the
/// default implementation invokes that, forwarding the parameters as is. Otherwise, this method does
/// nothing.
///
/// @param pageView The page view about to add the given view to its hierarchy.
/// @param annotationView The view to be added.
- (void)pageView:(PSPDFPageView *)pageView willShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

/// Override point to customize the behavior when an annotation view has been added and made visible.
///
/// If the receiver’s `delegate` implements `pdfViewController:didShowAnnotationView:onPageView:`, the
/// default implementation invokes that, forwarding the parameters as is. Otherwise, this method does
/// nothing.
///
/// @param pageView The page view that has added the given view to its hierarchy and made it visible.
/// @param annotationView The view that has been added and made visible.
- (void)pageView:(PSPDFPageView *)pageView didShowAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

/// Override point to customize the behavior when an annotation view is about to be recycled.
///
/// The default implementation does nothing.
- (void)willRecycleAnnotationView:(UIView<PSPDFAnnotationPresenting> *)annotationView;

// MARK: Customizing Child View Controller Presentation

- (BOOL)delegateShouldShowController:(UIViewController *)viewController options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;
- (void)delegateDidShowController:(UIViewController *)viewController options:(nullable NSDictionary<NSString *, id> *)options animated:(BOOL)animated;

// MARK: ???

- (void)delegateDidChangeControllerState;

// MARK: Customizing Menus

/// Ask the delegate to customize the compose menu. Returns `suggestedMenu` if
/// the delegate doesn't implement the required method.
- (UIMenu *)delegateMenuForCreatingAnnotationAtPoint:(CGPoint)point onPageView:(PSPDFPageView *)pageView appearance:(PSPDFEditMenuAppearance)appearance suggestedMenu:(UIMenu *)suggestedMenu NS_SWIFT_NAME(delegateMenu(forCreatingAnnotationAt:onPageView:appearance:suggestedMenu:));

/// Ask the delegate to customize the annotation menu. Returns `suggestedMenu`
/// if the delegate doesn't implement the required method.
- (UIMenu *)delegateMenuForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView appearance:(PSPDFEditMenuAppearance)appearance suggestedMenu:(UIMenu *)suggestedMenu NS_SWIFT_NAME(delegateMenu(forAnnotations:onPageView:appearance:suggestedMenu:));

// MARK: Deprecations

/// Ask the delegate to customize the legacy compose menu.
- (nullable NSArray<PSPDFMenuItem *> *)delegateShouldShowMenuItems:(NSArray<PSPDFMenuItem *> *)menuItems atSuggestedTargetRect:(CGRect)rect forAnnotations:(nullable NSArray<__kindof PSPDFAnnotation *> *)annotations inRect:(CGRect)textRect onPageView:(PSPDFPageView *)pageView PSPDF_DEPRECATED(12, "Use 'delegateMenu(forAnnotations:onPageView:appearance:suggestedMenu:)' or 'delegateMenu(forCreatingAnnotationAt:onPageView:appearance:suggestedMenu:)' instead.");

@end

NS_ASSUME_NONNULL_END
