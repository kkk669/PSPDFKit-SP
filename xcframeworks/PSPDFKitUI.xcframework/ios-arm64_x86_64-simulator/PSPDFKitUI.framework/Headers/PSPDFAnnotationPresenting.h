//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAnnotation, PSPDFAnnotationPlaceholder, PSPDFPageView, PSPDFConfiguration;

NS_ASSUME_NONNULL_BEGIN

/// Conforming to this protocol indicates instances can present an annotation and react to events such as page show/hide (to pause video, for example)
PSPDF_PROTOCOL_SWIFT(AnnotationPresenting)
@protocol PSPDFAnnotationPresenting<NSObject>

@optional

/// Represented annotation this object is presenting.
@property (nonatomic, nullable) PSPDFAnnotation *annotation;

/// Allows ordering of annotation views.
@property (nonatomic) NSUInteger zIndex;

/// Allows adapting to the outer zoomScale. Re-set after zooming.
@property (nonatomic) CGFloat zoomScale;

/// Allows adapting to the initial pdfScale
@property (nonatomic) CGFloat PDFScale;

/// Called when `pageView` is about to be displayed.
- (void)willShowPageView:(PSPDFPageView *)pageView;

/// Called when `pageView` is hidden.
- (void)didHidePageView:(PSPDFPageView *)pageView;

/// Called initially and when the parent page size is changed. (e.g. rotation)
- (void)didChangePageBounds:(CGRect)bounds;

/// Called when the user taps on an annotation and the tap wasn't processed otherwise.
- (void)didTapAtPoint:(CGPoint)point;

/// Queries the view if removing should be in sync or happen instantly.
/// If not implemented, return YES is assumed.
@property (nonatomic, readonly) BOOL shouldSyncRemovalFromSuperview;

/// View is queued for being removed, but still waits for a page sync.
/// This is called regardless of what is returned in `shouldSyncRemovalFromSuperview`.
- (void)willRemoveFromSuperview;

/// A weak reference to the page view responsible for this view.
@property (nonatomic, weak) PSPDFPageView *pageView;

/// A reference to the used configuration.
@property (nonatomic) PSPDFConfiguration *configuration;

/// Indicates if the view is selected.
@property (nonatomic, getter=isSelected) BOOL selected;

/// Width of the border of this annotation view.
@property (nonatomic) CGFloat strokeWidth UI_APPEARANCE_SELECTOR;

/// Border color of the annotation view.
@property (nonatomic, nullable) UIColor *borderColor UI_APPEARANCE_SELECTOR;

/// Placeholder for the annotation until the actual content becomes available.
@property (nonatomic, nullable) PSPDFAnnotationPlaceholder *annotationPlaceholder;

@end

NS_ASSUME_NONNULL_END
