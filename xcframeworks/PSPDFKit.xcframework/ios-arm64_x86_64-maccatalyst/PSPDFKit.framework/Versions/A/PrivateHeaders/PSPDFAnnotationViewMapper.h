//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAnnotation;

NS_ASSUME_NONNULL_BEGIN

/// The annotation view mapper is used to look up the appropriate class for displaying an annotation,
/// and rendering it in overlay mode.
///
/// The PSPDFKitUI framework defines a default mapping from annotations to annotation view classes at
/// load time. Depending on the use case, there are several different ways to customize this mapping:
///
/// - Generally replace the default implementation of this protocol with your own object by setting it
/// as the value of the `PSPDFAnnotationManager.defaultAnnotationViewMapper` class property — this
/// object will be used by any `PSPDFAnnotationManager` initialized after the call
/// - Replace the `annotationViewMapper` of a specific `PSPDFAnnotationManager` instance with your own
/// object
/// - Implementing `annotationViewClassForAnnotation:` in your custom `PSPDFAnnotationProvider` class
/// - Implementing `pdfViewController:annotationView:forAnnotation:onPageView:` in your
/// `<PSPDFViewControllerDelegate>`
/// - Overriding `-[PSPDFViewController pageView:customizeAnnotationView:forAnnotation:]`
///
/// Note that the last two options do not actually modify the mapping, but instead allow replacing the
/// exact annotation view instance being used to present the particular annotation.
///
/// When replacing a framework provided annotation view manager, it’s strongly suggested to not build
/// its functionality from scratch. Instead, it is advisable to let the original object do most of the
/// work and only return a custom class for the few cases you need to modify. I.e. instead of this:
/// 
/// ```
/// - (Class)defaultAnnotationViewClassForAnnotation:(PSPDFAnnotation *)annotation {
///     switch (annotation.type) {
///         case PSPDFAnnotationTypeYouDontCareAboutButOhWellA:
///         case PSPDFAnnotationTypeYouDontCareAboutButOhWellB:
///             // many other cases go here
///             return PSPDFAnnotationHostingView.class;
///         case PSPDFAnnotationTypeLink:
///             return CustomLinkView.class;
///             // even more other cases go here
///     }
/// }
/// ```
///
/// prefer:
///
/// ```
/// - (Class)defaultAnnotationViewClassForAnnotation:(PSPDFAnnotation *)annotation {
///     if ([annotation isKindOfClass:PSPDFLinkAnnotation.class]) {
///         return CustomLinkView.class;
///     } else {
///         return [self.originalImplementation defaultAnnotationViewClassForAnnotation:annotation];
///     }
/// }
/// ```
///
/// In order to set `PSPDFAnnotationManager.defaultAnnotationViewMapper`, pick a well defined point
/// during application startup. In particular, do not use implementations of `+load` or `+initialize`
/// to do so, as the exact order in which those are invoked is too dependent on environmental factors
/// that can easily change without you noticing (other than that things start to go sideways).
@protocol PSPDFAnnotationViewMapper <NSObject>

/// The default class to use when displaying the given annotation.
///
/// This method is used in the base implementation of `-[PSPDFAnnotationManager(SubclassingHooks)
/// defaultAnnotationViewClassForAnnotation:]`. It is used when none of the annotation manager’s
/// annotation providers implements or returns non-Nil from `-annotationViewClassForAnnotation:`.
///
/// Unless the delegate of the annotation manager’s document provider specifies an override in
/// `classForClass:`, an instance of the class returned by this method is allocated or retrieved from
/// the cache in order to display the given annotation. If this method returns `Nil`, the annotation
/// will not be displayed.
///
/// @param annotation The annotation to display.
- (nullable Class)defaultAnnotationViewClassForAnnotation:(PSPDFAnnotation *)annotation;

@end

NS_ASSUME_NONNULL_END
