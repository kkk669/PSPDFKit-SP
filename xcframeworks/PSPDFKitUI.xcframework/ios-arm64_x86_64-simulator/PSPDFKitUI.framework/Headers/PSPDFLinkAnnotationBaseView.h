//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationPresenting.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFLinkAnnotation;

/// Base class for all link-annotation subclasses.
PSPDF_CLASS_SWIFT(LinkAnnotationBaseView)
@interface PSPDFLinkAnnotationBaseView : UIView<PSPDFAnnotationPresenting>

/// Saves the attached link annotation.
@property (nonatomic, readonly) PSPDFLinkAnnotation *linkAnnotation;

/// Defaults to a zIndex of 1.
@property (nonatomic) NSUInteger zIndex;

/// Internal content view. Subclasses should add content to that view.
@property (nonatomic, readonly) UIView *contentView;

/// Associated weak reference to then `PDFPageView`.
@property (nonatomic, weak) PSPDFPageView *pageView;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFLinkAnnotationBaseView (SubclassingHooks)

/// Called when the annotation changes.
- (void)prepareForReuse NS_REQUIRES_SUPER;

/// Called each time the annotation changes or if the content view is about to be displayed.
- (void)populateContentView;

/// Will show/hide the content view.
- (void)setContentViewVisible:(BOOL)visible animated:(BOOL)animated;
@property (nonatomic, getter=isContentViewVisible, readonly) BOOL contentViewVisible;

@end

NS_ASSUME_NONNULL_END
