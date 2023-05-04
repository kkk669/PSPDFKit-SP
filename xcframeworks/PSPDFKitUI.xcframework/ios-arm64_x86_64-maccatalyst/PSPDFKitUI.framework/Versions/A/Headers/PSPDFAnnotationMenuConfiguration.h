//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>
#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFAbstractLineAnnotation;
@class PSPDFAnnotation;
@class PSPDFFreeTextAnnotation;
@class PSPDFPageView;

NS_ASSUME_NONNULL_BEGIN

/// An enum that represents one of the color properties of an annotation.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAnnotationMenuConfigurationColorProperty) {
    /// Represents the `color` property of an annotation.
    PSPDFAnnotationMenuConfigurationColorPropertyColor,
    /// Represents the `fillColor` property of an annotation.
    PSPDFAnnotationMenuConfigurationColorPropertyFillColor,
} PSPDF_ENUM_SWIFT(AnnotationMenuConfiguration.ColorProperty);

/// An enum that represents one of the line end properties of an annotation.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAnnotationMenuConfigurationLineEndProperty) {
    /// Represents the `lineEnd1` property of an annotation.
    PSPDFAnnotationMenuConfigurationLineEndPropertyLineEnd1,
    /// Represents the `.lineEnd2` property of an annotation.
    PSPDFAnnotationMenuConfigurationLineEndPropertyLineEnd2,
} PSPDF_ENUM_SWIFT(AnnotationMenuConfiguration.LineEndProperty);

// MARK: -

/// An object that builds ``PSPDFAnnotationMenuConfiguration``.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AnnotationMenuConfiguration.Builder)
@interface PSPDFAnnotationMenuConfigurationBuilder : PSPDFBaseConfigurationBuilder

/// See ``PSPDFAnnotationMenuConfiguration/alphaChoices``.
@property (nonatomic, copy) NSArray<NSNumber /* CGFloat */ *> * (^alphaChoices)(PSPDFAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* CGFloat */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

/// See ``PSPDFAnnotationMenuConfiguration/colorChoices``.
@property (nonatomic, copy) NSArray<UIColor *> * (^colorChoices)(PSPDFAnnotationMenuConfigurationColorProperty property, PSPDFAnnotation *annotation, PSPDFPageView *pageView, NSArray<UIColor *> *defaultChoices);

/// See ``PSPDFAnnotationMenuConfiguration/fontSizeChoices``.
@property (nonatomic, copy) NSArray<NSNumber /* CGFloat */ *> * (^fontSizeChoices)(PSPDFFreeTextAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* CGFloat */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

/// See ``PSPDFAnnotationMenuConfiguration/lineEndChoices``.
@property (nonatomic, copy) NSArray<NSNumber /* PSPDFLineEndType */ *> * (^lineEndChoices)(PSPDFAnnotationMenuConfigurationLineEndProperty property, PSPDFAbstractLineAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* PSPDFLineEndType */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

/// See ``PSPDFAnnotationMenuConfiguration/lineWidthChoices``.
@property (nonatomic, copy) NSArray<NSNumber /* CGFloat */ *> * (^lineWidthChoices)(PSPDFAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* CGFloat */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

@end

// MARK: -

/// An object that configures the annotation menu.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AnnotationMenuConfiguration)
@interface PSPDFAnnotationMenuConfiguration : PSPDFBaseConfiguration<PSPDFAnnotationMenuConfigurationBuilder *>

/// The closure that provides an array of choices that should be included in the
/// menu for changing the `alpha` property of the given annotation.
///
/// - Parameters:
///     - annotation: The annotation in question.
///     - pageView: The page view on which the annotation is.
///     - defaultChoices: The array of default choices.
///
/// - Returns: An array of choices to include in the menu for changing the
///   `alpha` property of the given annotation.
@property (nonatomic, readonly) NSArray<NSNumber /* CGFloat */ *> * (^alphaChoices)(PSPDFAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* CGFloat */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

/// The closure that provides an array of choices that should be included in the
/// menu for changing the given color property of the given annotation.
///
/// - Parameters:
///     - property: The color property.
///     - annotation: The annotation in question.
///     - pageView: The page view on which the annotation is.
///     - defaultChoices: The array of default choices.
///
/// - Returns: An array of choices to include in the menu for changing the given
///   color property of the given annotation.
@property (nonatomic, readonly) NSArray<UIColor *> * (^colorChoices)(PSPDFAnnotationMenuConfigurationColorProperty property, PSPDFAnnotation *annotation, PSPDFPageView *pageView, NSArray<UIColor *> *defaultChoices);

/// The closure that provides an array of choices that should be included in the
/// menu for changing the `fontSize` property of the given annotation.
///
/// - Parameters:
///     - annotation: The annotation in question.
///     - pageView: The page view on which the annotation is.
///     - defaultChoices: The array of default choices.
///
/// - Returns: An array of choices to include in the menu for changing the
///   `fontSize` property of the given annotation.
@property (nonatomic, readonly) NSArray<NSNumber /* CGFloat */ *> * (^fontSizeChoices)(PSPDFFreeTextAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* CGFloat */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

/// The closure that provides an array of choices that should be included in the
/// menu for changing the given line end property of the given annotation.
///
/// - Parameters:
///     - property: The line end property.
///     - annotation: The annotation in question.
///     - pageView: The page view on which the annotation is.
///     - defaultChoices: The array of default choices.
///
/// - Returns: An array of choices to include in the menu for changing the given
///   line end property of the given annotation.
@property (nonatomic, readonly) NSArray<NSNumber /* PSPDFLineEndType */ *> * (^lineEndChoices)(PSPDFAnnotationMenuConfigurationLineEndProperty property, PSPDFAbstractLineAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* PSPDFLineEndType */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

/// The closure that provides an array of choices that should be included in the
/// menu for changing the `lineWidth` property of the given annotation.
///
/// - Parameters:
///     - annotation: The annotation in question.
///     - pageView: The page view on which the annotation is.
///     - defaultChoices: The array of default choices.
///
/// - Returns: An array of choices to include in the menu for changing the
///   `lineWidth` property of the given annotation.
@property (nonatomic, readonly) NSArray<NSNumber /* CGFloat */ *> * (^lineWidthChoices)(PSPDFAnnotation *annotation, PSPDFPageView *pageView, NSArray<NSNumber /* CGFloat */ *> *defaultChoices) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
