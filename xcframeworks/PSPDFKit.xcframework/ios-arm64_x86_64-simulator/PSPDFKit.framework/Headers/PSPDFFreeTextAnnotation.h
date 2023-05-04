//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractLineAnnotation.h>
#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationStyleKey.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFRotatable.h>

NS_ASSUME_NONNULL_BEGIN

/// The free text annotation intent type. (Optional; PDF 1.6)
typedef NS_CLOSED_ENUM(NSInteger, PSPDFFreeTextAnnotationIntent) {
    /// Regular free text annotation (text box comment)
    PSPDFFreeTextAnnotationIntentFreeText,

    /// Callout style
    PSPDFFreeTextAnnotationIntentFreeTextCallout,

    /// Click- to-type or typewriter object
    PSPDFFreeTextAnnotationIntentFreeTextTypeWriter
} PSPDF_ENUM_SWIFT(FreeTextAnnotation.Intent);

/// `NSValueTransformer` to convert between `PSPDFFreeTextAnnotationIntent` enum and string value.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `FreeTextAnnotation` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFFreeTextAnnotationIntentTransformerName NS_SWIFT_NAME(freeTextAnnotationIntent);

/// PDF FreeText Annotation.
///
/// A free text annotation (PDF 1.3) displays text directly on the page. Unlike an ordinary text annotation (see 12.5.6.4, “Text Annotations”), a free text annotation has no open or closed state; instead of being displayed in a pop-up window, the text shall be always visible.
PSPDF_CLASS_SWIFT(FreeTextAnnotation)
@interface PSPDFFreeTextAnnotation : PSPDFAnnotation <PSPDFRotatable, PSPDFOverridable>

/// Convenience initializer for normal free text annotations.
- (instancetype)initWithContents:(NSString *)contents;

/// Convenience initializer for free text callout annotations.
- (instancetype)initWithContents:(NSString *)contents calloutPoint1:(CGPoint)point1;

/// The free text annotation intent type. (Optional; PDF 1.6)
@property (atomic) PSPDFFreeTextAnnotationIntent intentType NS_SWIFT_NAME(intent);

/// Starting point for the line if callout is present.
///
/// @note Shortcut for the first point in the `points` array.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic) CGPoint point1;

/// Knee point (optional) for the line if callout is present.
///
/// @note Shortcut for the second point in the `points` array.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic) CGPoint kneePoint;

/// End point for the line if callout is present.
///
/// @note Shortcut for the third point in the `points` array.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic) CGPoint point2;

/// Line end type for the callout.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic) PSPDFLineEndType lineEnd;

/// Defines the inset for the text. Optional, defaults to `UIEdgeInsetsZero`.
///
/// @note Only positive inset values are allowed.
///
/// As with all annotation properties, post a `.PSPDFAnnotationChanged` notification to propagate changes.
@property (atomic) UIEdgeInsets innerRectInset;

/// Resizes the annotation to fit the entire text by increasing or decreasing the height.
/// The width and origin of the annotation are maintained.
///
/// Calling this method while the annotation is selected and has a rotation other than
/// zero is not supported and will not update the view.
- (void)sizeToFit;

/// Returns the size of the annotation with respect to the given constraints. If you don't want to
/// constrain the height or width, use `CGFLOAT_MAX` for that value. The suggested size does not take the
/// rotation of the annotation into account.
- (CGSize)sizeWithConstraints:(CGSize)constraints;

/// Enables automatic vertical resizing. If this property is set to YES, the annotation will
/// adjust its bounding box as the user types in more text.
/// Defaults to YES.
@property (atomic) BOOL enableVerticalResizing;

/// Enables automatic horizontal resizing. If this property is set to YES, the annotation will
/// adjust its bounding box as the user types in more text.
/// Defaults to YES.
@property (atomic) BOOL enableHorizontalResizing;

/// Optionally transforms the boundingBox and re-calculates the text size with it.
- (void)setBoundingBox:(CGRect)boundingBox transformSize:(BOOL)transformSize;

/// Bounding box for the inner text box if it's a callout or just a bounding box for the whole annotation
/// The textBoundingBox is defined in PDF coordinates.
@property (atomic) CGRect textBoundingBox;

/// Set size for the text bounding box (PDF coordinates) for the inner text box if it's a callout or just a bounding box size for the whole annotation
- (void)setTextBoundingBoxSize:(CGSize)size;

/// Converts the intent of the annotation to the specified value.
///
/// @return A list of property keys that were changed in the process or `nil` if no change was needed.
- (nullable NSArray<PSPDFAnnotationStyleKey> *)convertIntentTypeTo:(PSPDFFreeTextAnnotationIntent)newIntent NS_SWIFT_NAME(convertIntent(to:));

@end

NS_ASSUME_NONNULL_END
