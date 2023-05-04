//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFRenderQueue.h>
#import <PSPDFKitUI/PSPDFAnnotationPresenting.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation;

/// Generic annotation view that listens on annotation changes.
PSPDF_CLASS_SWIFT(AnnotationView)
@interface PSPDFAnnotationView : UIView<PSPDFAnnotationPresenting>

/// The currently set annotation.
@property (nonatomic, nullable) PSPDFAnnotation *annotation;

/// Associated weak reference to the `PDFPageView` the annotation is displayed on.
@property (nonatomic, weak) PSPDFPageView *pageView;

/// Allows adapting to the outer zoomScale. Re-set after zooming.
@property (nonatomic) CGFloat zoomScale;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFAnnotationView (SubclassingHooks)

/// Called when any annotation changes.
- (void)annotationChangedNotification:(NSNotification *)notification NS_REQUIRES_SUPER;

/// Animated change notifications. Defaults to YES.
@property (nonatomic) BOOL shouldAnimatedAnnotationChanges;

/// Triggers a frame recalculation. Usually only called when the annotation is set.
- (void)updateFrame NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
